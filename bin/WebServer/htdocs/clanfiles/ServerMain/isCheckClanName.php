<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$clname = (isset($_GET['ClName'])) ? $_GET['ClName'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
if ($clname == "" || $gserver == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanZang FROM ClanDB.dbo.CL WHERE ClanName='$clname'";
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