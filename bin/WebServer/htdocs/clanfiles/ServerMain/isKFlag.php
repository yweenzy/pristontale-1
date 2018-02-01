<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$chname = (isset($_GET['chName'])) ? $_GET['chName'] : "";
if ($chname == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanName FROM Clandb.dbo.UL WHERE ChName='$chname'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) <= 0)
{
	print("Code=0$CR");
}
else
{
	print("Code=1$CR");
}
sqlsrv_close($dbconn);
?>