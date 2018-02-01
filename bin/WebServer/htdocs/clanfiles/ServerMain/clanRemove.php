<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$clName = (isset($_GET['clName'])) ? $_GET['clName'] : "";
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
if ($chname == "" || $gserver == "" || $clName == "" || $userid == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanZang FROM clandb.dbo.CL WHERE ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (!sqlsrv_num_rows($result) >= 1)
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
$row = sqlsrv_fetch_array($result);
$ClanLeader = $row['ClanZang'];
if ($chname != $ClanLeader) 
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
$query = "DELETE FROM clandb.dbo.CL WHERE ClanName='$clName';
DELETE FROM clandb.dbo.UL WHERE ClanName='$clName'";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>