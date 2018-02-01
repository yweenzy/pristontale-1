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
// $Id: Builtin.php,v 1.14 2007/04/16 07:52:30 davidc Exp $

require_once 'DBA.php';

/**
 * DBA_Driver_Builtin uses the builtin dba functions of PHP as the underlying
 * driver for a DBA class. Depending on the driver, this can be faster or
 * slower than the DBA_Driver_File class.
 *
 * This class has been tested with DB3 and GDBM and probably works with DB2.
 * Other drivers may have quirks that this class does not address yet. CDB
 * is known to be unsuitable as a driver due to its lack of write ability.
 *
 * @author  Brent Cook <busterb@mail.utexas.edu>
 * @version 1.0
 * @access  public
 * @package DBA
 */
class DBA_Driver_Builtin extends DBA
{

    // {{{ instance variables
    /**
     * Name of the database
     * @access private
     */
    var $_dbName;

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
     * Name of the builtin dba driver to use
     * @access private
     */
    var $_driver;

    /**
     * Indicates the ability of the dba driver to replace values
     * @access private
     */
    var $_hasReplace;
    // }}}

    // {{{ DBA_Driver_Builtin($driver = 'gdbm')
    /* Constructor
     *
     * @access public
     * @param   string  $driver dba driver to use
     */
    function DBA_Driver_Builtin($driver = 'gdbm')
    {
        // call the base constructor
        $this->DBA();
        $this->_driver = $driver;
    }
    // }}}

    // {{{ open($dbName='', $mode='r', $persistent=false)
    /**
     * Opens a database.
     *
     * @access public
     * @param   string  $dbName The name of a database
     * @param   string  $mode The mode in which to open a database.
     *                   'r' opens read-only.
     *                   'w' opens read-write.
     *                   'n' creates a new database and opens read-write.
     *                   'c' creates a new database if the database does not
     *                      exist and opens read-write.
     * @param   boolean $persistent Determines whether to open the database
     *                  peristently. Not supported here.
     * @return  object PEAR_Error on failure
     */
    function open($dbName='', $mode='r', $persistent = false)
    {
        if (is_null($this->_driver)) {
            return $this->raiseError(DBA_ERROR_NO_DRIVER);
        }

        if ($this->_driver == 'gdbm') {
            $this->_hasReplace = false;
        } else {
            $this->_hasReplace = true;
        }

        if ($dbName == '') {
            return $this->raiseError(DBA_ERROR_NO_DBNAME);
        } else {
            $this->_dbName = $dbName;
        }

        switch ($mode) {
            case 'r':
                    // open for reading
                    $this->_writable = false;
                    $this->_readable = true;
                    break;
            case 'n':
            case 'c':
            case 'w':
                    $this->_writable = true;
                    $this->_readable = true;
                    break;
            default:
                return $this->raiseError(DBA_ERROR_INVALID_MODE, NULL, NULL,
                    'filemode: '.$mode);
        }

        // open the index file
        $params = array($dbname, $mode, $this->_driver);
        
        $connect_function = !is_null($persistent) ? 'dba_popen' : 'dba_open';
        $connector        = @call_user_func($connect_function, $params); 
        
        if (PEAR::isError($connector)) {
            $this->_writable = false;
            $this->_readable = false;
            return $this->raiseError(DBA_ERROR_CANNOT_OPEN, null, null,
                                     'DB Name: ' . $dbName . ' filemode: ' . $mode);
        }
        
        if ($connector === false) {
            $this->_writable = false;
            $this->_readable = false;
            return $this->raiseError(DBA_ERROR_CANNOT_OPEN, NULL, NULL,
                'dbname: '.$dbName.' filemode: '.$mode);
        }

        $this->_dba = $connector;
    }
    // }}}

    // {{{ close()
    /**
     * Closes an open database.
     *
     * @access  public
     * @return  object PEAR_Error on failure
     */
    function close()
    {
        if ($this->isOpen()) {
            $this->_readable = false;
            $this->_writable = false;
            dba_sync($this->_dba); // db2 is known to require syncs
            dba_close($this->_dba);
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
     * @return  object PEAR_Error on failure
     */
    function reopen($mode)
    {
        if ($this->isOpen()) {
            if (($mode == 'r') && $this->isWritable()) {
                // Reopening as read-only
                $this->close();
                return $this->open($this->_dbName, 'r');
            } elseif (($mode == 'w') && (!$this->isWritable)) {
                // Reopening as read-write
                $this->close();
                return $this->open($this->_dbName, 'w');
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_OPEN);
        }
    }
    // }}}

    // {{{ _DBA_Driver_Builtin()
    /**
     * PEAR emulated destructor calls close on PHP shutdown
     * @access private
     */
    function _DBA_Driver_Builtin()
    {
        $this->close();
    }
    // }}}

    // {{{ isOpen()
    /**
     * Returns the current open status for the database
     *
     * @access  public
     * @return  boolean true if open, false if closed 
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
     * @return  boolean true if readable, false if not
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
     * @return  boolean true if writable, false if not
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
     * @param   string  $key key to delete
     * @return  object PEAR_Error on failure
     */
    function remove($key)
    {
        if ($this->isWritable()) {
            if (!dba_delete($key, $this->_dba)) {
                return $this->raiseError(DBA_ERROR_NOT_FOUND, NULL, NULL, 'key: '.$key);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_WRITEABLE);
        }
    }
    // }}}

    // {{{ fetch($key)
    /**
     * Returns the value that is stored at $key.
     *
     * @access  public
     * @param   string $key key to examine
     * @return  mixed the requested value on success, false on failure
     */
    function fetch($key)
    {
        if ($this->isReadable()) {
            if (dba_exists($key, $this->_dba)) {
                return dba_fetch($key, $this->_dba);
            } else {
                return $this->raiseError(DBA_ERROR_NOT_FOUND, NULL, NULL, 'key: '.$key);
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
     * @return  mixed string on success, false on failure
     */
    function firstkey()
    {
        if ($this->isReadable()) {
            return dba_firstkey($this->_dba);
        } else {
            return false;
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
        $key = dba_firstkey($this->_dba);
        $size = 0;
        while ($key !== false) {
            ++$size;
            $key = dba_nextkey($this->_dba);
        }
        return $size;
    }
    // }}}

    // {{{ nextkey()
    /**
     * Returns the next key in the database, false if there is a problem
     *
     * @access  public
     * @return  mixed string on success, false on failure
     */
    function nextkey()
    {
        if ($this->isReadable()) {
            return dba_nextkey($this->_dba);
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
        $keys = array();
        if ($this->isReadable()) {
            $key = $this->firstkey();
            while ($key !== FALSE) {
                $keys[] = $key;
                $key = $this->nextkey($key);
            }
        }
        return $keys;
    }
    // }}}

    // {{{ insert($key, $value)
    /**
     * Inserts a new value at $key. Will not overwrite if the key/value pair
     * already exist
     *
     * @access public
     * @param   string  $key key to insert
     * @param   string  $value value to store
     * @return  object PEAR_Error on failure
     */
    function insert($key, $value)
    {
        if ($this->isWritable()) {

            if ((!$this->_hasReplace && dba_exists($key, $this->_dba)) ||
                (!dba_insert($key, $value, $this->_dba))) {
                return $this->raiseError(DBA_ERROR_ALREADY_EXISTS, NULL, NULL,
                    'key: '.$key);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOT_WRITEABLE);
        }
    }
    // }}}

    // {{{ replace($key, $value)
    /**
     * Inserts a new value at key. If the key/value pair
     * already exist, overwrites the value
     *
     * @access public
     * @param   $key    string the key to insert
     * @param   $value  string the value to store
     * @return  object  PEAR_Error on failure
     */
    function replace($key, $value)
    {
        if ($this->isWritable()) {

            if ($this->_hasReplace) {
                return dba_replace($key, $value, $this->_dba);
            } else {
                $r = true;
                if (dba_exists($key, $this->_dba)) {
                    $r = dba_delete($key, $this->_dba);
                }
                return $r && dba_insert($key, $value, $this->_dba);
            }

        } else {
            return $this->raiseError(DBA_ERROR_NOT_WRITEABLE);
        }
    }
    // }}}
    
    // {{{ create($dbName, $driver='gdbm')
    /**
     * Creates a new database file if one does not exist. If it already exists,
     * updates the last-updated timestamp on the database
     *
     * @access  public
     * @param   string  $dbName the database to create
     * @param   string  $driver the dba driver to use
     * @return  object  PEAR_Error on failure
     */
    function create($dbName, $driver='gdbm')
    {
        $db = dba_open($dbName, 'n', $driver);

        if (PEAR::isError($db)) {
            return $this->raiseError(DBA_ERROR_CANNOT_CREATE, NULL, NULL,
                                     'dbname: '.$dbname);
        }

        if (!(($db !== false) && dba_close($db))) {
            return $this->raiseError(DBA_ERROR_CANNOT_CREATE, NULL, NULL,
                'dbname: '.$dbname);
        }
    }
    // }}}

    // {{{ db_exists($dbName)
    /**
     * Indicates whether a database with given name exists
     *
     * @access  public
     * @param   string  $dbName the database name to check for existence
     * @return  boolean true if the database exists, false if it doesn't
     */
    function db_exists($dbName)
    {
        return file_exists($dbName);
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
        if (DBA_Driver_Builtin::db_exists($dbName)) {
            if (!unlink($dbName)) {
                return $this->raiseError(DBA_ERROR_CANNOT_DROP, NULL, NULL,
                    'dbname: '.$dbName);
            }
        } else {
            return $this->raiseError(DBA_ERROR_NOSUCHDB, NULL, NULL,
                'dbname: '.$dbName);
        }
    }
    // }}}

    // {{{ drop()
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
        return($this->isOpen() && dba_exists($key, $this->_dba));
    }
    // }}}

    // {{{ sync()
    /**
     * Synchronizes an open database to disk
     * @access public
     */
    function sync()
    {
        return dba_sync($this->_dba);
    }
    // }}}

    // {{{ optimize()
    /**
     * Optimizes an open database
     * @access public
     */
    function optimize()
    {
        return dba_optimize($this->_dba);
    }
    // }}}
}
?>
