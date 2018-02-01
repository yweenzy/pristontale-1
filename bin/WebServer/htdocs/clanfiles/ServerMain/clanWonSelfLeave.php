<?php
/**
* Written by EuphoriA
**/
include 'settings.php';
$CR = chr(13);
$clName = (isset($_GET['clName'])) ? $_GET['clName'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
if ($clName == "" || $gserver == "" || $userid == "" || $chname == "")
{
	die("Code=100$CR");
}
$query = "SELECT ClanName,Permi FROM Clandb.dbo.UL WHERE ChName='$chname'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$clName2 = $row['ClanName'];
	if ($clName2 == "")
	{
		$query = "DELETE FROM Clandb.dbo.UL WHERE ChName='$chname'";
		sqlsrv_query($dbconn, $query);
		sqlsrv_close($dbconn);
		die("Code=0$CR");
	}
	if ($clName2 != $clName)
	{
		sqlsrv_close($dbconn);
		die("Code=0$CR");
	}
}
else
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
$query = "SELECT ClanZang,MemCnt FROM Clandb.dbo.CL WHERE ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query);
$row = sqlsrv_fetch_array($result);
$ClanLeader = $row['ClanZang'];
$ClanMembers = $row['MemCnt'];
$ClanMembers--;
if ($chname == $ClanLeader)
{
	sqlsrv_close($dbconn);
	die("Code=4$CR");
}
$query = "UPDATE clandb.dbo.CL SET MemCnt='$ClanMembers' WHERE ClanName='$clname';
DELETE FROM Clandb.dbo.UL WHERE ChName='$chname'";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>