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
$clwon = (isset($_GET['clwon'])) ? $_GET['clwon'] : "";
$clwonUserid = (isset($_GET['clwonUserid'])) ? $_GET['clwonUserid'] : "";
$lv = (isset($_GET['lv'])) ? $_GET['lv'] : "";
$chtype = (isset($_GET['chtype'])) ? $_GET['chtype'] : ""; 
$chlv = (isset($_GET['chlv'])) ? $_GET['chlv'] : "";
$chipflag = (isset($_GET['chipflag'])) ? $_GET['chipflag'] : "";
$date = date('m-d-y');
if ($chname == ""|| $gserver == "" || $clName == "" || $userid == "" || $clwon == "" || $clwonUserid == "" || $lv == "" || $chtype == "" || $chlv == "" || $chipflag == "")
{
	die("Code=100$CR");
}
$query = "SELECT IDX,ClanZang,MemCnt FROM clandb.dbo.CL WHERE ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$ClanLeader = $row['ClanZang'];
	$MemCount = $row['MemCnt'];
	$IDX = $row['IDX'];
}
else
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
if (((int)$MemCount +1) > 100)
{
	sqlsrv_close($dbconn);
	die("Code=2$CR");
}
$query = "SELECT ChName FROM clandb.dbo.UL WHERE Permi=2 AND ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query);
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$SubChief = $row['ChName'];
}
else
{
	$SubChief = "";
}
if ($ClanLeader != $chname && (string)$SubChief != $chname)
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
$query = "SELECT ClanName FROM clandb.dbo.UL WHERE ChName='$clwon'";
$result = sqlsrv_query($dbconn, $query);
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$uclname = $row['ClanName'];
}
else
{
	$uclname = "";
}
if ((string)$uclname != "")
{
	sqlsrv_close($dbconn);
	die("Code=0$CR");
}
else
{
	if ((string)$uclname == "" && sqlsrv_num_rows($result) >= 1)
	{
		$query = "DELETE FROM clandb.dbo.UL WHERE ChName='$clwon'";
		sqlsrv_query($dbconn, $query);
	}
}
$iMIDX = "";
$query = "SELECT MAX(MIDX) FROM clandb.dbo.UL";
$result = sqlsrv_query($dbconn, $query);
if (sqlsrv_num_rows($result) >= 1)
{
	$row = sqlsrv_fetch_array($result);
	$iMIDX = $row['MIDX'];
}
$iMIDX++;
$MemCount++;
$query = "UPDATE ClanDB.dbo.CL SET MemCnt='$MemCount' WHERE ClanName='$clName'";
sqlsrv_query($dbconn, $query);
$query = "INSERT INTO ClanDB.dbo.UL ([IDX],[MIDX],[userid],[ChName],[ClanName],[ChType],[ChLv],[Permi],[JoinDate],[DelActive],[PFlag],[KFlag],[MIconCnt]) values('$IDX','$iMIDX','$clwonUserid','$clwon','$clName','$chtype','$chlv','0',$date,'0','0','0','0')";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>