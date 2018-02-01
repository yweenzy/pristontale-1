<?php
/** 
*	Clan Kick User Script 
*	By EuphoriA
**/
include 'settings.php';
$logfile = ini_get('error_log');
/* Prevent WSS */
$_GET = filter_input_array(INPUT_GET, FILTER_SANITIZE_STRING); 
/* Setting GET Values to Variables */
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$clwon1 = (isset($_GET['clwon1'])) ? $_GET['clwon1'] : "";
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
$ticket = (isset($_GET['ticket'])) ? $_GET['ticket'] : "";
$clName = (isset($_GET['clName'])) ? $_GET['clName'] : "";
$CR = chr(13);
foreach ($_GET as $k => $v)
{
	if (substr($k,0,7) == "clwon1=")
	{
		$clwon1 = substr($k, 7);
	}
}
/* Stop script if one or more of the variables are not set. */
$GET = array($userid, $gserver, $clwon1, $chname, $ticket, $clName);
if ($userid == "" || $gserver == "" || $clwon1 == "" || $chname == "" || $ticket == "" || $clName == "")
{
	$getdata = "";
	print("Code=100$CR");
	$ip = $_SERVER['REMOTE_ADDR'];
	foreach ($_GET as $k => $v)
	{
		$getdata .= "$k => $v, "; 
	}
	error_log("Missing GET Data: $getdata FROM $ip \n",3,"$logfile");
	die();
}
$query = "SELECT ClanName FROM ClanDB.dbo.UL WHERE ChName='$clwon1'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
if (sqlsrv_num_rows($result) != false)
{
	$clName2 = sqlsrv_fetch_array($result);
	$clName2 = $clName2['ClanName'];
	if ($clName2 == "")
	{
		$query = "DELETE FROM ClanDB.dbo.UL WHERE ChName='$clwon1'";
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
$query = "SELECT ClanZang,MemCnt FROM ClanDB.dbo.CL WHERE ClanName='$clName'";
$result = sqlsrv_query($dbconn, $query);
$results = sqlsrv_fetch_array($result);
$ClanLeader = $results['ClanZang'];
$ClanMembers = $results['MemCnt'];
$ClanMembers = $ClanMembers - 1;
if ($clwon1 == $ClanLeader)
{
	sqlsrv_close($dbconn);
	die("Code=4$CR");
}
$query = "UPDATE ClanDB.dbo.CL SET MemCnt='$ClanMembers' WHERE ClanName='$clName';
DELETE FROM ClanDB.dbo.UL WHERE ChName='$clwon1';";
sqlsrv_query($dbconn, $query);
sqlsrv_close($dbconn);
print("Code=1$CR");
?>