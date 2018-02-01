<?php
$server = "localhost\CLASSICPT"; //Enter SQL Instance or IP with port (i.e. 192.168.0.1,1433)
$UID = 'c8master'; // Enter User ID For SQL Login
$PWD = 'c8master'; // Enter SQL Password
$dbconn = sqlsrv_connect($server, array('UID' => "$UID", 'PWD' => "$PWD", 'CharacterSet' => 'UTF-8'));
?>