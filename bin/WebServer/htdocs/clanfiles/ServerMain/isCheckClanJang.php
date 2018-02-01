<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
if ($userid == "" || $gserver == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanName FROM clandb.dbo.CL WHERE UserID='$userid'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) < 1)
{
	print("Code=0$CR");
}
else
{
	print("Code=1$CR");
}
sqlsrv_close($dbconn);
?>