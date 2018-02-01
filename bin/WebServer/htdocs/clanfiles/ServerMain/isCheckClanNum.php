<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
(int)$num = (isset($_GET['num'])) ? $_GET['num'] : "";
if ($num == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanName,Note FROM Clandb.dbo.CL WHERE MIconCnt='$num'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) <= 0)
{
	print("Code=0$CR");
}
else
{
	$row = sqlsrv_fetch_array($result);
	$ClanName = $row['ClanName'];
	$ClanNote = $row['Note'];
	print("Code=1 $CR CName=$ClanName $CR CNote=$ClanNote$CR");
}
sqlsrv_close($dbconn);
?>