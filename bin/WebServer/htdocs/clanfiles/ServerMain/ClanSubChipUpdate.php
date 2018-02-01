<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
if ($chname == "" || $gserver == "")
{
	die("Code=100$CR");
}
$query = "UPDATE clandb.dbo.UL SET Permi='0' WHERE ClanName IN (SELECT ClanName FROM clandb.dbo.UL WHERE ChName='$chname');
UPDATE clandb.dbo.UL SET Permi='2' WHERE ChName='$chname'";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>