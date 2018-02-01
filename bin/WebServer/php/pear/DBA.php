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
// | Authors: Brent Cook <busterb@mail.utexas.edu>                        |
// |          Olaf Conradi <conrado@drake.bt.co.uk>                       |
// +----------------------------------------------------------------------+
//
// $Id: DBA.php,v 1.36 2004/05/04 04:42:31 busterb Exp $
//

require_once('PEAR.php');

/**
 * If you add an error code here, make sure you also add a textual
 * version of it in DBA::errorMessage().
 */
                                                // userinfo contains:
define('DBA_ERROR',                    -1);
define('DBA_ERROR_UNSUP_DRIVER',       -2);     // drivername
define('DBA_ERROR_UNSUP_PERSISTENCE',  -3);
define('DBA_ERROR_NO_DRIVER',          -4);     // drivername
define('DBA_ERROR_NO_DBNAME',          -5);
define('DBA_ERROR_NOSUCHDB',           -6);     // dbname
define('DBA_ERROR_INVALID_MODE',       -7);     // filemode
define('DBA_ERROR_CANNOT_CREATE',      -8);     // dbname
define('DBA_ERROR_CANNOT_OPEN',        -9);
define('DBA_ERROR_CANNOT_DROP',       -10);
define('DBA_ERROR_NOT_READABLE',      -11);
define('DBA_ERROR_NOT_WRITEABLE',     -12);
define('DBA_ERROR_NOT_OPEN',          -13);
define('DBA_ERROR_NOT_FOUND',         -14);
define('DBA_ERROR_ALREADY_EXISTS',    -15);     // key

/**
 * DBA is a set of classes for handling and extending Berkeley DB style
 * databases. It works around some of the quirks in the built-in dba
 * functions in PHP (e.g. gdbm does not support dba_replace), has a file-based
 * dbm engine for installations where dba support is not included in PHP.
 *
 * @author  Brent Cook <busterb@mail.utexas.edu>
 * @version 1.0
 * @access  public
 * @package DBA
 */
class DBA extends PEAR
{
    /**
     * Default constructor
     */
    function DBA()
    {
        // call the base constructor
        $this->PEAR();
    }

    /**
     * Creates a new DBA object
     *
     * @static
     * @param   string $driver type of storage object to return
     * @return  object DBA storage object, returned by reference
     */
    function &create($driver = 'file')
    {
        if (!function_exists('dba_open') || ($driver=='file')) {
            require_once 'DBA/Driver/File.php';
            return new DBA_Driver_File();
        } elseif (in_array($driver, DBA::getDriverList())) {
            require_once 'DBA/Driver/Builtin.php';
            return new DBA_Driver_Builtin($driver);
        } else {
            return DBA::raiseError(DBA_ERROR_UNSUP_DRIVER, NULL, NULL,
                'driver: '.$driver);
        }
    }

    /**
     * Deletes a DBA database from the filesystem
     *
     * @static
     * @param   string $driver type of storage object to return
     * @return  object DBA storage object, returned by reference
     */
    function db_drop($name, $driver = 'file')
    {
        if (!function_exists('dba_open') || ($driver=='file')) {
            require_once 'DBA/Driver/File.php';
            return DBA_Driver_File::db_drop($name);
        } elseif (in_array($driver, DBA::getDriverList())) {
            require_once 'DBA/Driver/Builtin.php';
            return DBA_Driver_Builtin::db_drop($name);
        } else {
            return DBA::raiseError(DBA_ERROR_UNSUP_DRIVER, NULL, NULL,
                'driver: '.$driver);
        }
    }
    
    /**
     * Returns whether a result code from a DBA method is an error
     *
     * @param   int       $value  result code
     * @return  boolean   whether $value is a DBA_Error
     * @access public
     */
    function isError($value)
    {
        return (is_object($value) &&
            (is_a($value, 'dba_error') || is_subclass_of($value, 'dba_error')));
    }
    
    /**
     * Return a textual error message for a DBA error code
     *
     * @param   int     $value error code
     * @return  string  error message, or false if the error code was
     *                  not recognized
     * @access public
     */
    function errorMessage($value)
    {
        static $errorMessages;
        if (!isset($errorMessages)) {
            $errorMessages = array(
                DBA_ERROR                   => 'unknown error',
                DBA_ERROR_UNSUP_DRIVER      => 'unsupported database driver',
                DBA_ERROR_UNSUP_PERSISTENCE => 'persistent connections not supported',
                DBA_ERROR_NO_DRIVER         => 'no driver loaded',
                DBA_ERROR_NO_DBNAME         => 'no databasename given',
                DBA_ERROR_NOSUCHDB          => 'database not found',
                DBA_ERROR_INVALID_MODE      => 'invalid file mode',
                DBA_ERROR_CANNOT_CREATE     => 'can not create database',
                DBA_ERROR_CANNOT_OPEN       => 'can not open database',
                DBA_ERROR_CANNOT_DROP       => 'can not drop database',
                DBA_ERROR_NOT_READABLE      => 'database not readable',
                DBA_ERROR_NOT_WRITEABLE     => 'database not writeable',
                DBA_ERROR_NOT_OPEN          => 'database not open',
                DBA_ERROR_NOT_FOUND         => 'key not found',
                DBA_ERROR_ALREADY_EXISTS    => 'key already exists',
            );
        }

        if (DBA::isError($value)) {
            $value = $value->getCode();
        }

        return isset($errorMessages[$value]) ?
            $errorMessages[$value] : $errorMessages[DBA_ERROR];
    }

    /**
     * This method is used to communicate an error and invoke error
     * callbacks etc.  Basically a wrapper for PEAR::raiseError
     * without the message string.
     *
     * @param mixed $code integer error code, or a PEAR error object (all
     *      other parameters are ignored if this parameter is an object
     * @param int $mode error mode, see PEAR_Error docs
     * @param mixed $options If error mode is PEAR_ERROR_TRIGGER, this is the
     *      error level (E_USER_NOTICE etc).  If error mode is
     *      PEAR_ERROR_CALLBACK, this is the callback function, either as a
     *      function name, or as an array of an object and method name. For
     *      other error modes this parameter is ignored.
     * @param string $userinfo Extra debug information.
     * @return object a PEAR error object
     * @access public
     * @see PEAR_Error
     */
    function &raiseError($code = DBA_ERROR, $mode = NULL, $options = NULL,
        $userinfo = NULL)
    {
        // The error is yet a DBA error object
        if (is_object($code)) {
            return PEAR::raiseError($code, NULL, NULL, NULL, NULL, NULL, TRUE);
        }

        return PEAR::raiseError(NULL, $code, $mode, $options, $userinfo,
            'DBA_Error', TRUE);
    }
    
    /**
     * Returns whether a database exists
     *
     * @param  string $name name of the database to find
     * @param  string @driver driver to test for
     * @return boolean true if the database exists
     */
    function db_exists($name, $driver = 'file')
    {
        if (!function_exists('dba_open') || ($driver=='file')) {
            // the file driver stores data in two files
            return (file_exists($name.'.dat') && file_exists($name.'.idx'));
        } elseif (in_array($driver, array('db2', 'db3', 'db4', 'gdbm'))) {
            // these drivers store data in one file
            return file_exists($name);
        } else {
            // do not know how other drivers store data
            return DBA::raiseError(DBA_ERROR_NO_DRIVER, NULL, NULL, 'driver: '.$driver);
        }
    }

    /**
     * Returns an array of the currently supported drivers
     *
     * @return array
     */
    function getDriverList()
    {
        if (function_exists('dba_handlers')) {
            return array_merge(dba_handlers(), array('file'));
        } else {
            return array('file');
        }
    }
}

/**
 * DBA_Error implements a class for reporting portable database error
 * messages. Based on the PEAR::MDB implementation.
 *
 * @package DBA
 * @author  Olaf Conradi <conradi@cs.utwente.nl>
 */
class DBA_Error extends PEAR_Error
{
    
    /**
     * DBA_Error constructor.
     *
     * @param mixed   $code      DBA error code, or string with error message.
     * @param integer $mode      what "error mode" to operate in
     * @param integer $level     what error level to use for
     *                           $mode & PEAR_ERROR_TRIGGER
     * @param smixed  $debuginfo additional debug info, such as the last query
     */
    function DBA_Error($code = DBA_ERROR, $mode = PEAR_ERROR_RETURN,
              $level = E_USER_NOTICE, $debuginfo = NULL)
    {
        if (is_int($code)) {
            $this->PEAR_Error('DBA Error: '.DBA::errorMessage($code), $code,
                $mode, $level, $debuginfo);
        } else {
            $this->PEAR_Error('DBA Error: '.$code, DBA_ERROR, $mode, $level,
                $debuginfo);
        }
    }
}

?>
