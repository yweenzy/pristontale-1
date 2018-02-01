<?php
/**
 * File translation.str_mgmt.php
 *
 * Additional functions for Translation class
 *
 * Functions allowing user to create the new language, translation for specific
 * strings and full management of the languages database.
 *
 * @author Wojciech Zieliñski <voyteck@caffe.com.pl>
 * @author Lorenzo Alberton   <l dot alberton at quipo dot it>
 * @version 1.3
 * @access public
 * @package Translation
 */
/**
 * require PEAR::DB
 */
require_once 'DB.php';

/**
 * helper method
 */
function setDefaultTableDefinitions($LangID, $CustomTables)
{
    //set defaults
	$TableDefinitions = array(
        'langsavail' => array(
            'name'      => 'tr_langsavail',
            'lang_id'   => 'lang_id',
	        'lang_name' => 'name',
	        'metatags'  => 'metatags',
	        'errortext' => 'errortext'
        ),
        'strings_'.$LangID => array(
            'name'      => 'strings_'.$LangID,
            'page_id'   => 'page_id',
            'string_id' => 'string_id',
            'string'    => 'string'
        )
    );
    if (is_array($CustomTables['langsavail'])) {
	    $TableDefinitions['langsavail']['name']      = isset($CustomTables['langsavail']['name'])      ? $CustomTables['langsavail']['name']      : 'tr_langsavail';
		$TableDefinitions['langsavail']['lang_id']   = isset($CustomTables['langsavail']['lang_id'])   ? $CustomTables['langsavail']['lang_id']   : 'lang_id';
		$TableDefinitions['langsavail']['lang_name'] = isset($CustomTables['langsavail']['lang_name']) ? $CustomTables['langsavail']['lang_name'] : 'lang_name';
		$TableDefinitions['langsavail']['metatags']  = isset($CustomTables['langsavail']['metatags'])  ? $CustomTables['langsavail']['metatags']  : 'metatags';
		$TableDefinitions['langsavail']['errortext'] = isset($CustomTables['langsavail']['errortext']) ? $CustomTables['langsavail']['errortext'] : 'errortext';
	} elseif (!empty($CustomTables['langsavail'])) {
		$TableDefinitions['langsavail']['name'] = $CustomTables['langsavail'];
    }

    if (is_array($CustomTables['strings_'.$LangID])) {
	    $TableDefinitions['strings_'.$LangID]['name']      = isset($CustomTables['strings_'.$LangID]['name'])      ? $CustomTables['strings_'.$LangID]['name']      : 'strings_'.$LangID;
		$TableDefinitions['strings_'.$LangID]['page_id']   = isset($CustomTables['strings_'.$LangID]['page_id'])   ? $CustomTables['strings_'.$LangID]['page_id']   : 'page_id';
		$TableDefinitions['strings_'.$LangID]['string_id'] = isset($CustomTables['strings_'.$LangID]['string_id']) ? $CustomTables['strings_'.$LangID]['string_id'] : 'string_id';
		$TableDefinitions['strings_'.$LangID]['string']    = isset($CustomTables['strings_'.$LangID]['string'])    ? $CustomTables['strings_'.$LangID]['string']    : 'string';
    } elseif (!empty($CustomTables['strings_'.$LangID])) {
	    $TableDefinitions['strings_'.$LangID]['name'] = $CustomTables['strings_'.$LangID];
    }
    return $TableDefinitions;
}


/**
 * New language creation
 *
 * Creates new language in the system.
 * Creates lang entry in the languages table and the table for language strings.
 * If other langs have been created before and their tables were filled with
 * strings, function addTranslation should be executed for each of the added
 * strings just after calling this function and before using the Translation class
 * for any purpose.
 *
 * @param string $LangID   Language identifier
 * @param string $LangName Language name - store the language name of the lang,
 *                         possibly in the language described. This name can be later
 *                         retrieved by calling getLangName and getOtherLangs methods
 *                         and used for hyperlinks changing the site language.
 * @param string $METATags Tags that may describe the language codepage etc.
 *                         These tags can be retrieved by calling getMetaTags method.
 * @param string $pear_DSN PEAR DSN string for database connection
 * @param array  $CustomTables Custom table definitions
 * @return mixed Return 1 if everything went OK, a PEAR::DB_Error object if not.
 */
function createNewLang($LangID, $LangName, $METATags, $pear_DSN, $CustomTables=0)
{
	$TableDefinitions = setDefaultTableDefinitions($LangID, $CustomTables);

	$db = DB::connect($pear_DSN);
	if (DB::isError($db)) {
		return $db;
	}
	$query = sprintf('INSERT INTO %s (%s, %s, %s) VALUES ("%s", "%s", "%s")',
	                $TableDefinitions['langsavail']['name'],
	                $TableDefinitions['langsavail']['lang_id'],
	                $TableDefinitions['langsavail']['lang_name'],
	                $TableDefinitions['langsavail']['metatags'],
	                addslashes($LangID),
	                addslashes($LangName),
	                addslashes($METATags)
    );
	$result = $db->query($query);
	if (DB::isError($result)) {
		return $result;
	}

	//check if the table already exists
	$exists = false;
    $res = $db->query('SHOW TABLES');
	if (DB::isError($res)) {
	    return $res;
	}
	while ($row = $res->fetchRow()) {
		if ($row[0] == 'tr_strings_'.$LangID) {
		    $exists = true;
		    break;
		}
	}
	if (!$exists) {
    	$query = 'CREATE TABLE '. $TableDefinitions['strings_'.$LangID]['name'] .'('
    			. $TableDefinitions['strings_'.$LangID]['page_id']  .' VARCHAR(16) default NULL, '
    			. $TableDefinitions['strings_'.$LangID]['string_id'].' VARCHAR(32) NOT NULL, '
   			    . $TableDefinitions['strings_'.$LangID]['string']   .' TEXT, '
    			.'UNIQUE KEY page_id ('.$TableDefinitions['strings_'.$LangID]['page_id'].', '
    			                       .$TableDefinitions['strings_'.$LangID]['string_id'].'))';
        $result = $db->query($query);
    	if (DB::isError($result)) {
    		$query = sprintf('DELETE FROM %s WHERE %s="%s"',
                            $TableDefinitions['langsavail']['name'],
	                        $TableDefinitions['langsavail']['lang_id'],
	                        addslashes($LangID)
	                 );
    		$delresult = $db->query($query);
    		return $result;
    	}
	}
	return 1;
}

/**
 * Language removal
 *
 * Removes language from system.
 * This function should be used carefully - it will permanently remove all the
 * strings that has been added to the language table by dropping this table.
 * If other langs are stored in the table, then only this lang column will be dropped.
 *
 * @param string  $LangID       Language identifier
 * @param string  $pear_DSN     PEAR DSN string for database connection
 * @param array   $CustomTables Custom table definitions
 * @param boolean $force        If true, the table is dropped without checks
 * @return mixed  Return 1 if everything went OK, a PEAR::DB_Error object if not.
 */
function removeLang($LangID, $pear_DSN, $CustomTables=0, $force=false)
{
	$db = DB::connect($pear_DSN);
	if (DB::isError($db)) {
		return $db;
	}

	$TableDefinitions = setDefaultTableDefinitions($LangID, $CustomTables);

	if (!$force) {
    	//check if other langs are stored in this table
    	//'DESCRIBE' == 'SHOW COLUMNS FROM'
    	$res = $db->query('DESCRIBE '.$TableDefinitions['strings_'.$LangID]['name']);
    	if (DB::isError($res)) {
    	    return $res;
    	}
    	if ($res->numRows() > 3) {
            $query = 'ALTER TABLE '. $TableDefinitions['strings_'.$LangID]['name']
                   .' DROP COLUMN '. $TableDefinitions['strings_'.$LangID]['string'];
            $res = $db->query('DESCRIBE '.$TableDefinitions['strings_'.$LangID]['name']);
    	    if (DB::isError($res)) {
    	        return $res;
    	    }
    	    return 1;
    	}
    }

	$result = $db->query('DROP TABLE '.$TableDefinitions['strings_'.$LangID]['name']);
	if (DB::isError($result)) {
		return $result;
	}
	$query = sprintf('DELETE FROM %s WHERE %s="%s"',
	                $TableDefinitions['langsavail']['name'],
	                $TableDefinitions['langsavail']['lang_id'],
	                $LangID);
	$result = $db->query($query);
	if (DB::isError($result)) {
		return $result;
	}
	return 1;
}

/**
 * Translation adding
 * Adds string to one or more language tables.
 *
 * @param string $PageID   page identifier. Might be "" if the string is to be
 *                         available from any page, independendly from translation
 *                         object creation parameters.
 * @param string $StringID string identifier. Must be unique for the same PageID
 *                         and strings that were created without PageID's.
 *                         This rule must be respected to prevent ambiguities.
 * @param array  $String   array of strings - the array keys should be languages id's,
 *                         the values - the sttrings in these languages - e.g.:
 *                         ("en"->"English text", "pl"->"Tekst polski", ...)
 * @param string $pear_DSN PEAR DSN string for database connection
 * @param array  $CustomTables Custom table definitions
 * @return mixed Return 1 if everything went OK, a PEAR::DB_Error object if not.
 */
function addTranslation($PageID, $StringID, $String, $pear_DSN, $CustomTables=0)
{
	$db = DB::connect($pear_DSN);
	if (DB::isError($db)) {
		return $db;
	}
    $TableDefinitions = array();
    $langs = array_keys($String);
    foreach ($langs as $aLang) {
	    $TableDefinitions = array_merge_recursive(
	        $TableDefinitions,
	        setDefaultTableDefinitions($aLang, $CustomTables)
        );
    }

	foreach ($String as $LangID => $Text) {
		$data[] = array($TableDefinitions['strings_'.$LangID]['name'], $Text);
	}
	$query = sprintf('INSERT INTO ! (%s, %s, %s) VALUES ("%s", "%s", ?)',
	                $TableDefinitions['strings_'.$LangID]['page_id'],
    			    $TableDefinitions['strings_'.$LangID]['string_id'],
   			        $TableDefinitions['strings_'.$LangID]['string'],
   			        addslashes($PageID),
   			        addslashes($StringID)
             );
	$result = $db->executeMultiple(($db->prepare($query)), $data);
	if (DB::isError($result)) {
		return $result;
	}
	return 1;
}

/**
 * Translation removal
 *
 * Removes string from all of string tables
 * @param string $PageID   page identifier.
 * @param string $StringID string identifier.
* @param string $pear_DSN PEAR DSN string for database connection
 * @param array  $CustomTables Custom table definitions
 * @return mixed Return 1 if everything went OK, a PEAR::DB_Error object if not.
 */
function removeTranslation($PageID, $StringID, $pear_DSN, $CustomTables=0)
{
	$db = DB::connect($pear_DSN);
	if (DB::isError($db)) {
		return $db;
	}

	$result = $db->query('SELECT '. $TableDefinitions['langsavail']['lang_id']
	                     .' FROM '. $TableDefinitions['langsavail']['name']);
	if (DB::isError($result)) {
		return $result;
	}
	while ($row = $result->fetchRow()) {
		$languages[] = $row[0];
	}
	$TableDefinitions = array();
	foreach ($langs as $LangID) {
	    $TableDefinitions = array_merge_recursive(
	        $TableDefinitions,
	        setDefaultTableDefinitions($LangID, $CustomTables)
        );
        $query = sprintf('DELETE FROM %s WHERE %s="%s" AND %s="%s"',
                        $TableDefinitions['strings_'.$LangID]['name'],
                        $TableDefinitions['strings_'.$LangID]['page_id'],
                        addslashes($PageID),
                        $TableDefinitions['strings_'.$LangID]['string_id'],
                        addslashes($StringID)
                 );
        $result = $db->query($query);
        if (DB::isError($result)) {
            return $result;
        }
	}
	return 1;
}
?>