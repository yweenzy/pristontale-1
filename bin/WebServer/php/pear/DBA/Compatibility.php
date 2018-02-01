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
// $Id: Compatibility.php,v 1.10 2003/01/04 11:54:51 mj Exp $

/** 
 * dba compatibility layer
 * This works in reverse of the rest of the DBA classes. If you have code
 * that requires the PHP dba functions, but are using a system where they
 * are not available, including this file will define a set for you.
 * See the PHP documentation on dba for explanation of how these functions
 * work.
 *
 * @author Brent Cook <busterb@mail.utexas.edu>
 * @version 1.0
 * @access public
 * @package DBA
 * @see PHP dba Documentation
 */

if (!function_exists('dba_open')) {

    require_once 'PEAR.php';
    require_once 'DBA/Driver/File.php';

    function dba_close(&$dba)
    {
        $result = !PEAR::isError($dba->close());
        unset($dba);
        return $result;
    }

    function dba_delete($key, &$dba)
    {
        return !PEAR::isError($dba->remove($key));
    }

    function dba_exists($key, &$dba)
    {
        return !PEAR::isError($dba->exists($key));
    }

    function dba_fetch($key, &$dba)
    {
        return !PEAR::isError($dba->fetch($key));
    }

    function dba_firstkey(&$dba)
    {
        return $dba->firstkey();
    }

    function dba_insert($key, $value, &$dba)
    {
        return !PEAR::isError($dba->insert($key, $value));
    }

    function dba_nextkey(&$dba)
    {
        return $dba->nextkey();
    }

    function dba_open($filename, $mode, $handler)
    {
        $dba = new DBA_Driver_File();
        $dba->open($filename, $mode);
        if (PEAR::isError($dba)) {
            return false;
        } else {
            return $dba;
        }
    }

    function dba_popen(&$dba)
    {
        return FALSE;
    }

    function dba_replace($key, $value, &$dba)
    {
        return !PEAR::isError($dba->replace($key, $value));
    }

    function dba_sync(&$dba)
    {
        $dba->sync();
    }

    function dba_optimize(&$dba)
    {
        $dba->optimize();
    }
}
?>
