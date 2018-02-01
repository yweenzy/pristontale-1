<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$clName = (isset($_GET['clName'])) ? $_GET['clName'] : "";
if ($chname == "" || $gserver == "" || $clName == "")
{
	die("Code=100$CR");
}
$query = "SELECT userid FROM clandb.dbo.UL WHERE ChName='$chname' AND ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$userid = $row['userid'];
	print("Code=1$CR");
	$query = "UPDATE ClanDB.dbo.CL SET ClanZang='$chname',UserID='$userid' WHERE ClanName='$clName'";
	sqlsrv_query($dbconn, $query);
}
else
{
	print("Code=0$CR");
}
sqlsrv_close($dbconn);
?>