<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
if ($gserver == "" || $userid == "" || $chname == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanName FROM Clandb.dbo.UL WHERE ChName='$chname'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));

if (sqlsrv_num_rows($result) <= 0)
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
$row = sqlsrv_fetch_array($result);
$clname = $row['ClanName'];
print("Code=1 $CR CClanName=$clname$CR");
$query = "SELECT ClanZang FROM Clandb.dbo.CL WHERE ClanName='$clname'";
$result = sqlsrv_query($dbconn, $query);
$row = sqlsrv_fetch_array($result);
$ClanLeader = $row['ClanZang'];
print("CClanZang=$ClanLeader$CR");
$query = "SELECT ChName FROM Clandb.dbo.UL WHERE ClanName='$clname'";
$result = sqlsrv_query($dbconn, $query);
while ($row = sqlsrv_fetch_array($result))
{
	$CharName = $row['ChName'];
	print("CMem=$CharName$CR");
}
sqlsrv_close($dbconn);
?>