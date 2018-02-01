<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$clwon = (isset($_GET['clwon'])) ? $_GET['clwon'] : "";
if ($clwon == "" || $gserver == "")
{
	die("Code=100$CR");
}
print("Code=1$CR");
?>