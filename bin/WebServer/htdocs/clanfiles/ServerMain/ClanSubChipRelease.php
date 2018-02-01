<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$chname = (isset($_POST['chname'])) ? $_POST['chname'] : "";
$gserver = (isset($_POST['gserver'])) ? $_POST['gserver'] : "";
if ($chname == "" || $gserver == "")
{
	die("Code=100$CR");
}
$query = "UPDATE clandb.dbo.UL SET Permi='0' WHERE ChName='$chname'";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>