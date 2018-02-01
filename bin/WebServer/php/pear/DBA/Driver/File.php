<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
// +----------------------------------------------------------------------+
// | Copyright (c) 2002-2003 Brent Cook                                        |
// +----------------------------------------------------------------------+
// | This library is free software; you can redistribute it and/or        |
// | modify it under the terms of the GNU Lesser General Public           |
// | License as published by the Free Software Foundation; either         |
// | version 2.1 of the License, or (at your option) any later version.   |
// |                                                                      |
// | This library is distributed in the hope that it will be useful,      |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
// | Lesser General Public License for more details.                      |
// |                                                                      |
// | You should have received a copy of the GNU Lesser General Public     |
// | License along with this library; if not, write to the Free Software  |
// | Foundation, Inc., 59 Temple Place, Suite 330,Boston,MA 02111-1307 USA|
// +----------------------------------------------------------------------+
//
// $Id: File.php,v 1.12 2003/01/27 04:31:42 busterb Exp $

require_once 'DBA.php';

// {{{ constants
/**
 * Location in the index file for a block location
 */
define('DBA_SIMPLE_LOC',0);

/**
 * Location in the index file for a block size
 */
define('DBA_SIMPLE_SIZE',1);

/**
 * Location in the index file for a block value size
 */
define('DBA_SIMPLE_VSIZE',2);

/**
 * Location in the index file for a block key
 */
define('DBA_SIMPLE_KEY',3);
// }}}

/**
 * DBA_Driver_File provides a simple, file-based implementation of a
 * DBM-style database. It uses two files, and index and a data file to
 * manage key/value pairs. These two files use the suffixes '.dat' and
 * '.idx'. When a database is opened, only the index file is read. The
 * index file contains pointers to locations within the data file, which
 * are used to retrieve values.
 *
 * The class uses a concept of blocks for data storage. When the first value
 * is inserted, a new block is created by appending to the data file. If that
 * value is deleted, it remains in the data file, but is marked as empty in
 * the index file. A list of available blocks is kept, so when a new value
 * is inserted, its size is compared to the list of available blocks. If one
 * is of sufficient size, it is reused and marked as used in the index file.
 * Blocks can be of any length.
 *
 * In updating the index, lines are simply appended to the file after each
 * operation. So, the index file might have the same block listed multiple time
 * , just in different states. When the database is closed, it rewrites the
 * index file, removing and duplicate entries for a single block. The index
 * reader only uses the last entry for a block from the index file, so if close
 * is not called for some reason, the index file is still in a valid state.
 *
 * The optimize function merely removes duplicated index entries by rewriting
 * the file, the same as close.
 * The sync function calls fflush on the data and index files.
 *
 * @author  Brent Cook
 * @version 1.0
 * @access  public
 * @package DBA
 */
class DBA_Driver_File extends DBA
{
    // {{{ instance variables
    /**
     * Name of the database
     * @access private
     */
    var $_dbName;

    /**
     * Handle to data file
     * @access private
     */
    var $_datFP;

    /**
     * Handle to index file
     * @access private
     */
    var $_idxFP;

    /**
     * Indicates the current ability for read/write operations
     * @access private
     */
    var $_writable;

    /**
     * Indicates the current ability for read operations
     * @access private
     */
    var $_readable;

    /**
     * Determines if the driver should use an index file
     * @access private
     */
    var $_indexed;
    // }}}

    // {{{ DBA_Driver_File($indexed = true)
    /* Constructor
     *
     * @access public
     * @param   string  $driver dba driver to use
     */
    function DBA_Driver_File($indexed = true)
    {
        // call the base constructor
        $this->DBA();
        $this->_indexed = true;
    }
    // }}}

    // {{{ open($dbName='', $mode='r', $persistent = false)
    /**
     * Opens a database.
     *
     * @access  public
     * @param   string  $dbName The name of a database
     * @param   string  $mode The mode in which to open a database.
     *                   'r' opens read-only.
     *                   'w' opens read-write.
     *                   'n' creates a new database and opens read-write.
     *                   'c' creates a new database if the database does not
     *                      exist and opens read-write.
     * @param   boolean $persistent Determines whether to open the database
     *                  peristently. Not supported here.
     * @return  object  PEAR_Error on failure
     */
    function open($dbName='', $mode='r', $persistent = false)
    {
        if ($persistent) {
            return $this->raiseError(DBA_ERROR_UNSUP_PERSISTENCE);
        }

        if ($dbName == '') {
            return $this->raiseError(DBA_ERROR_NO_DBNAME);
        } else {
            $this->_dbName = $dbName;
            $dat_name = $dbName.'.dat';
            $idx_name = $dbName.'.idx';
        }

        switch ($mode) {
            case 'r':
                    // open for reading
                    $file_mode = 'rb';
                    $this->_writable = false;
                    $this->_readable = true;
                    break;
            case 'n':
                    // create a new database
                    $file_mode = 'w+b';
                    $this->_writable = true;
                    $this->_readable = true;
                    break;
            case 'c':
                    // should we create a new database?
                    if (!DBA_Driver_File::db_exists($dbName)) {
                        $file_mode = 'w+b';
                        $this->_writable = true;
                        $this->_readable = true;
                        break;
                    } // otherwise, we just open for writing
            case 'w':
                    $file_mode = 'r+b';
                    $this->_writable = true;
                    $this->_readable = true;
                    break;
            default:
                return $this->raiseError(DBA_ERROR_INVALID_MODE, NULL, NULL,
                    'filemode: '.$mode);
        }

        // open the index file
        $this->_idxFP = @fopen($idx_name, $file_mode);
        if ($this->_idxFP === false) {
            $this->_writable = false;
            $this->_readable = false;
            return $this->raiseError(DBA_ERROR_CANNOT_OPEN, NULL, NULL,
                'could not open idx file '.$idx_name);
        }

        // open the data file
        $this->_datFP = @fopen($dat_name, $file_mode);
        if ($this->_datFP === false) {
            fclose ($this->_idxFP);
            $this->_writable = false;
            $this->_readable = false;
            return $this->raiseError(DBA_ERROR_CANNOT_OPEN, NULL, NULL,
                'could not open data file '.$dat_name);
        }

        // get a shared lock if read-only, otherwise get an exclusive lock
        if ($file_mode == 'r') {
            flock ($this -> _idxFP, LOCK_SH);
            flock ($this -> _datFP, LOCK_SH);
        } else {
            flock ($this -> _idxFP, LOCK_EX);
            flock ($this -> _datFP, LOCK_EX);
        }

        // we are writing to a new file, so we do not need to read anything
        if ($file_mode != 'w+') {
            // parse the index file
            $this->_readIdx();
        }
    }
    // }}}

    // {{{ close()
    /**
     * Closes an open database.
     *
     * @access  public
     * @return  object  PEAR_Error on failure
     */
    function close()
    {
        if ($this->isOpen())
        {
            if ($this->isWritable())
            {
                $this->_writeIdx();
            }
            $this->_readable = false;
            $this->_writable = false;
            fclose($this->_idxFP);
            fclose($this->_datFP);
        } else {
            return $this->raiseError(DBA_ERROR_NOT_OPEN);
        }
    }
    // }}}

    // {{{ reopen($mode)
    /**
     * Reopens an already open database in read-only or write mode.
     * If the database is already in the requested mode, then this function
     * does nothing.
     *
     * @access  public
     * @param   string  $mode 'r' for read-only, 'w' for read/write
     * @return  object  PEAR_Error on failure
     */
    function reopen($mode)
    {
        if ($this->isOpen()) {
            if (($mode == 'r') && $this->isWritable()) {
                // Reopening as read-only
                $this->close();
                return $this->open($this->_dbName, 'r');
            } else {
                if (($mode == 'w') && (!$this -> _writable))
                {
                    // Reopening as read-write
                    $this->close();
                    return $this->open($this->_dbName, 'w');
                }
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_OPEN);
        }
    }
    // }}}

    // {{{ _DBA_Driver_File()
    /**
     * PEAR emulated destructor calls close on PHP shutdown
     * @access private
     */
    function _DBA_Driver_File()
    {
        $this->close();
    }
    // }}}

    // {{{ getName()
    /**
     * Returns the name of the opened database. Assumes database is open
     * @returns string the name of the opened database
     */
    function getName()
    {
        return $this->_dbName;
    }
    // }}}

    // {{{ isOpen()
    /**
     * Returns the current open status for the database
     *
     * @access  public
     * @return  boolean true if the database is open, false if it is closed
     */
    function isOpen()
    {
        return($this->_readable || $this->_writable);
    }
    // }}}

    // {{{ isReadable()
    /**
     * Returns the current read status for the database
     *
     * @access  public
     * @return  boolean true if the database is readable, false if it is not
     */
    function isReadable()
    {
        return $this->_readable;
    }
    // }}}

    // {{{ isWritable()
    /**
     * Returns the current write status for the database
     *
     * @access  public
     * @return  boolean true if the database is writable, false if it is not
     */
     function isWritable()
     {
         return $this->_writable;
     }
    // }}}

    // {{{ remove($key)
    /**
     * Removes the value at location $key
     *
     * @access  public
     * @param   string  $key key to remove
     * @return  object  PEAR_Error on failure
     */
    function remove($key)
    {
        if ($this->isWritable()) {
            if (isset($this->_usedBlocks[$key])) {
                $this->_freeUsedBlock($key);
            } else {
                return $this->raiseError(DBA_ERROR_NOT_FOUND, NULL, NULL, 'key: '.$key);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_WRITEABLE);
        }
    }
    // }}}

    // {{{ &fetch($key)
    /**
     * Returns the value that is stored at $key.
     *
     * @access  public
     * @param   string $key key to examine
     * @return  mixed  the requested value on success, false on failure
     */
    function &fetch($key)
    {
        if ($this->isReadable()) {
            if (!isset($this->_usedBlocks[$key])) {
                return $this->raiseError(DBA_ERROR_NOT_FOUND, NULL, NULL, 'key: '.$key);
            } else {
                fseek($this->_datFP, $this->_usedBlocks[$key][DBA_SIMPLE_LOC]);
                return fread($this->_datFP,$this->_usedBlocks[$key][DBA_SIMPLE_VSIZE]);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_READABLE);
        }
    }
    // }}}

    // {{{ firstkey()
    /**
     * Returns the first key in the database
     *
     * @access  public
     * @return  mixed  string on success, false on failure
     */
    function firstkey()
    {
        if ($this->isReadable() && ($this->size() > 0)) {
            reset($this->_usedBlocks);
            return key($this->_usedBlocks);
        } else {
            return false;
        }
    }
    // }}}

    // {{{ nextkey()
    /**
     * Returns the next key in the database, false if there is a problem
     *
     * @access  public
     * @return  mixed  string on success, false on failure
     */
    function nextkey()
    {
        if ($this->isReadable() && ($this->size() > 0)
            && next($this->_usedBlocks)) {
            return key($this->_usedBlocks);
        } else {
            return false;
        }
    }
    // }}}


    // {{{ getkeys()
    /**
     * Returns all keys in the database
     *
     * @access  public
     * @return  mixed  array
     */
    function getkeys()
    {
        if ($this->isReadable() && ($this->size() > 0)) {
            return array_keys($this->_usedBlocks);
        } else {
            return array();
        }
    }
    // }}}

    // {{{ size()
    /**
     * Calculates the size of the database in number of keys
     *
     * @access  public
     * @return  int    number of keys in the database
     */
    function size()
    {
        if (is_array($this->_usedBlocks)) {
            return sizeof($this->_usedBlocks);
        } else {
            return 0;
        }
    }
    // }}}

    // {{{ insert($key, $value)
    /**
     * Inserts a new value at $key. Will not overwrite if the key/value pair
     * already exist
     *
     * @access  public
     * @param   string  $key key to insert
     * @param   string  $value value to store
     * @return  object  PEAR_Error on failure
     */
    function insert($key, $value)
    {
        if ($this->exists($key)) {
            return $this->raiseError(DBA_ERROR_ALREADY_EXISTS, NULL, NULL,
                'key: '.$key);
        } else {
            return $this->replace($key, $value);
        }
    }
    // }}}

    // {{{ replace($key, $value)
    /**
     * Inserts a new value at key. If the key/value pair
     * already exist, overwrites the value
     *
     * @access  public
     * @param   $key    string the key to insert
     * @param   $val    string the value to store
     * @return  object  PEAR_Error on failure
     */
    function replace($key, $value)
    {
        // is the database in a usable state?
        if ($this->isWritable()) {
            // get how much space we need
            $vsize = strlen($value);

            if (!isset($this->_usedBlocks[$key])) {
                // the value is new
                $this->_writeNewBlock($key, $value, $vsize);

            } else {
                // the value is not new
                $size = $this->_usedBlocks[$key][DBA_SIMPLE_SIZE];

                // is the value smaller or equal in size to its block size
                if ($size >= $vsize) {
                    // move to the block's location in the data file
                    $loc = $this->_usedBlocks[$key][DBA_SIMPLE_LOC];
                    fseek($this->_datFP, $loc);

                    // write to the data file
                    fwrite($this->_datFP, str_pad($value, $size), $size);

                    // update internal indecies
                    $this->_usedBlocks[$key][DBA_SIMPLE_VSIZE] = $vsize;
                    $this->_writeIdxEntry($loc, $size, $vsize, $key);

                // the value is larger than its allocated space
                } else {
                    // free this value's allocated block
                    $this->_freeUsedBlock($key);

                    $this->_writeNewBlock($key, $value, $vsize);
                }
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_WRITEABLE);
        }
    }
    // }}}
    
    // {{{ _writeNewBlock($key, $value, $vsize)
    /**
     * Allocates a new block of at least $vsize and writes $key=>$val
     * to the database
     *
     * @access  private
     * @param   string $key
     * @param   string $value
     * @param   int    $vsize
     */
    function _writeNewBlock($key, $value, $vsize)
    {
        // is there is a sufficiently sized block free ?
        $loc = $this->_getFreeBlock($vsize);
        if ($loc !== false) {
            // update free block list
            $size = $this->_freeBlocks[$loc];
            unset($this->_freeBlocks[$loc]);

            // move to the block's location in the data file
            fseek($this->_datFP, $loc, SEEK_SET);

            // write to the data file
            fwrite($this->_datFP, str_pad($value,$size), $size);

            $this->_usedBlocks[$key] = array($loc, $size, $vsize);
            $this->_writeIdxEntry($loc, $size, $vsize, $key);

        // there is not a sufficiently sized block free
        } else {
            // move to the end of the data file
            fseek($this ->_datFP, 0, SEEK_END);
            $loc = ftell($this->_datFP);

            // write to the data file
            $size = $vsize + ceil($vsize / 20); // make size 5% larger

            // add a useless "\n" to new values. This makes the data file
            // readable in any text editor. Useful when things go wrong :P
            fwrite($this->_datFP, str_pad($value, $size)."\n", $size+1);

            // update internal block lists
            $this->_usedBlocks[$key] = array($loc, $size, $vsize);
            $this->_writeIdxEntry($loc, $size, $vsize, $key);
        }
    }
    // }}}

    // {{{ _getFreeBlock($reqsize)
    /**
     * Returns a block location from the free list
     *
     * @access  private
     * @param   int     $reqsize Requested size
     * @returns mixed  location of free block, false if there are no free blocks
     */
    function _getFreeBlock($reqsize)
    {
        // check if we have any blocks to choose from
        if (is_array($this->_freeBlocks)) {
            // iterate through the blocks in blockIndex to find
            // a free block
            foreach ($this->_freeBlocks as $loc=>$size) {
                if ($size >= $reqsize) {
                    return $loc;
                }
            }
        }
        // no blocks available
        return false;
    }
    // }}}

    // {{{ _freeUsedBlock($key)
    /**
     * Places a used block on the free list, updates indicies accordingly
     *
     * @access  private
     * @param   string $key
     * @returns mixed
     */
    function _freeUsedBlock($key)
    {
        $loc = $this->_usedBlocks[$key][DBA_SIMPLE_LOC];
        $size = $this->_usedBlocks[$key][DBA_SIMPLE_SIZE];
        unset($this->_usedBlocks[$key]);

        $this->_freeBlocks[$loc] = $size;
        $this->_writeIdxEntry($loc, $size);
    }
    // }}}

    // {{{ create($dbName)
    /**
     * Creates a new database file if one does not exist. If it already exists,
     * updates the last-updated timestamp on the database
     *
     * @access  public
     * @param   string  $dbName the database to create
     * @return  object  PEAR_Error on failure
     */
    function create($dbName)
    {
        if (!(@touch($dbName.'.dat') && @touch($dbName.'.idx'))) {
           return $this->raiseError('Could not create database: '.$dbName);
        }
    }
    // }}}

    // {{{ db_exists($dbName)
    /**
     * Indicates whether a database with given name exists
     *
     * @access  public
     * @param   string   $dbName the database name to check for existence
     * @return  boolean true if the database exists, false if it doesn't
     */
    function db_exists($dbName)
    {
        return(file_exists($dbName.'.dat') && file_exists($dbName.'.idx'));
    }
    // }}}

    // {{{ db_drop($dbName)
    /**
     * Removes a database from existence
     *
     * @access  public
     * @param   string  $dbName the database name to drop
     * @return  object  PEAR_Error on failure
     */
    function db_drop($dbName)
    {
        if (DBA_Driver_File::db_exists($dbName)) {
            if (!unlink($dbName.'.dat') || !unlink($dbName.'.idx')) {
                return $this->raiseError(DBA_ERROR_CANNOT_DROP, NULL, NULL,
                    'dbname: '.$dbName);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOSUCHDB, NULL, NULL,
                'dbname: '.$dbName);
        }
    }
    // }}}

    // {{{ drop($dbName)
    /**
     * Removes the last open database from existence
     *
     * @access  public
     * @return  object  PEAR_Error on failure
     */
    function drop()
    {
        $this->close();
        return $this->db_drop($this->_dbName);
    }
    // }}}

    // {{{ exists($key)
    /**
     * Check whether key exists
     *
     * @access  public
     * @param   string   $key
     * @return  boolean true if the key exists, false if it doesn't
     */
    function exists($key)
    {
        return($this->isOpen() && isset($this->_usedBlocks[$key]));
    }
    // }}}

    // {{{ sync()
    /**
     * Synchronizes an open database to disk
     * @access  public
     */
    function sync()
    {
        if ($this->isWritable()) {
            fflush($this->_datFP);
            fflush($this->_idxFP);
        }
    }
    // }}}

    // {{{ optimize()
    /**
     * Optimizes an open database
     * @access  public
     */
    function optimize()
    {
        if ($this->isWritable()) {
            $this->_writeIdx();
        }
    }
    // }}}
 
    // {{{ _readIdx()
    /**
     * Reads the entries in an index file
     * Assumes that $this->_idxFP is valid and readable
     * @access private
     */
    function _readIdx()
    {
        // clear out old data if a previous database was opened
        $this->_usedBlocks = array();
        $this->_freeBlocks = array();
        $usedBlocks = array(); // temporary used index
        $key = '';            // reset key

        while (fscanf($this->_idxFP, '%u|%u|%u|%s', $loc, $size, $vsize, $key))
        {
            // is this an free block?
            if ($key == '') {
                // check if this block had been previously marked as used
                if (isset($usedBlocks[$loc])) {
                    unset($this->_usedBlocks[$usedBlocks[$loc]]);
                    unset($usedBlocks[$loc]);
                }

                $this->_freeBlocks[$loc] = $size;
            } else {
                // check if this block had been previously marked as free
                if (isset($this->_freeBlocks[$loc])) {
                    unset($this->_freeBlocks[$loc]);
                }

                $this->_usedBlocks[$key] = array($loc, $size, $vsize);
                $usedBlocks[$loc] = $key;
            }
            $key = ''; // reset key for the next iteration
        }
    }
    // }}}

    // {{{ _writeIdx()
    /**
     * Rewrites the index file, removing free entries
     * Assumes that $this->_idxFP is valid and writable
     *
     * @access private
     */
    function _writeIdx()
    {
        // move the file pointer to the beginning; ftruncate does not do this
        fseek($this->_idxFP, 0);

        // clear the index
        ftruncate($this->_idxFP, 0);

        // write the free blocks
        if (isset($this->_freeBlocks)) {
            foreach ($this->_freeBlocks as $loc=>$size) {
                $this->_writeIdxEntry($loc,$size);
            }
        }

        // write the used blocks
        if (isset($this->_usedBlocks)) {
            foreach ($this->_usedBlocks as $key=>$block) {
                $this->_writeIdxEntry($block[DBA_SIMPLE_LOC],
                                      $block[DBA_SIMPLE_SIZE],
                                      $block[DBA_SIMPLE_VSIZE], $key);
            }
        }
        fflush($this->_idxFP);
    }
    // }}}

    // {{{ _writeIdxEntry($loc, $size, $vsize=NULL, $key=NULL)
    /**
     * Writes a used block entry to an index file
     *
     * @access private
     */
    function _writeIdxEntry($loc, $size, $vsize=NULL, $key=NULL)
    {
        if (is_null($vsize)) {
            // write a free block entry
            fputs($this->_idxFP, "$loc|$size\n");
        } else {
            // write a used block entry
            fputs($this->_idxFP, "$loc|$size|$vsize|$key\n");
        }
    }
    // }}}
}
?>
