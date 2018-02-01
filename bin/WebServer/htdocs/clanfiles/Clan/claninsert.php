<?php
	/** 
	*	     ClanInsert PHP Script
	*	Written By EuphoriA / Phatkone
	**/
$server = "localhost\CLASSICPT"; //Enter SQL Instance or IP with port (i.e. 192.168.0.1,1433)
$UID = 'c8master'; // Enter User ID For SQL Login
$PWD = 'c8master'; // Enter SQL Password
/**
* Main Script - Nothing needs to be edited past here.
* If your CL table is auto incrementing the IDX value 
* Then remove the IDX fields from the query string at line 91.
**/
$dbconn = sqlsrv_connect($server, array('UID' => "$UID", 'PWD' => "$PWD", 'CharacterSet' => 'UTF-8'));
$CR = chr(13);	
$_GET = filter_input_array(INPUT_GET, FILTER_SANITIZE_STRING);
if ($dbconn) {	
	if (isset($_GET)) {
		$userid = isset($_GET['userid'])? $_GET['userid']:"";
		$gserver = isset($_GET['gserver'])? $_GET['gserver']:"";
		$chname = isset($_GET['chname'])? $_GET['chname']:"";
		$clname = isset($_GET['clName'])? $_GET['clName']:"";
		$chtype = isset($_GET['chtype'])? $_GET['chtype']:"";
		$lv = isset($_GET['lv'])? $_GET['lv']:"";
		$ticket = isset($_GET['ticket'])? $_GET['ticket']:"";
				
		$expl = "Pristontale Clan";
		
		if ($userid=="" || $gserver =="" || $chname=="" || $clname=="" || $chtype=="" || $lv=="" || $ticket=="") {
			print("Code=102".$CR);
			die;
		}
		$ctcheck = "SELECT SNo FROM clandb.dbo.CT WHERE ChName='$chname' AND UserID='$userid'";
		$tticket = sqlsrv_query($dbconn, $ctcheck, array());
		$tticket1 = sqlsrv_fetch_array($tticket);
		
		if ($dbconn) {
			if ($ticket != $tticket1[0]) {
				print("Code=101".$CR);
				die;
				sqlsrv_close($dbconn);
			} else {
			}
		} else {
			sqlsrv_close($dbconn);
			print("Code=103".$CR);
			die;
		}
		$clancheck = "SELECT ClanName FROM clandb.dbo.UL WHERE ChName='$chname'";
		$clancheck1 = sqlsrv_query($dbconn, $clancheck);
		if ($dbconn) {
			if ($clancheck1 != "") {
				$delete = "DELETE FROM clandb.dbo.UL WHERE ChName='$chname'";
			} else { 
				print("Code=2".$CR."CMoney=0".$CR);
				sqlsrv_close($dbconn);
				die;
			}
		}
		$leader = "SELECT ClanZang FROM clandb.dbo.CL WHERE ClanName='$clname'";
		$leadercheck = sqlsrv_query($dbconn, $leader);
		$leadercheck1 = sqlsrv_fetch_array($leadercheck);
		if ($leadercheck1[0] != "") {
			sqlsrv_close($dbconn);
			print("Code=3".$CR."CMoney=0".$CR);
			die;
		}
		
		$LI = "SELECT IMG FROM clandb.dbo.LI WHERE ID=1";
		$IMG = sqlsrv_query($dbconn,$LI, array());
		$IMG1 = sqlsrv_fetch_array($IMG);
		if ($IMG1[0] != "") {
			$iIMG = $IMG1[0];
		} else {
			$iIMG = 1000000000;
			$imginsert = "INSERT INTO clandb.dbo.LI ('$iIMG','1')";
			sqlsrv_query($dbconn,$imginsert);
		}
		$iIMG = $iIMG + 1;
		$imginsert = "UPDATE clandb.dbo.LI SET IMG='$iIMG' WHERE ID=1";
		sqlsrv_query($dbconn, $imginsert);
		$IDX = "SELECT MAX(IDX) FROM clandb.dbo.CL";
		$IDX1 = sqlsrv_query($dbconn,$IDX, array());
		$IDX2 = sqlsrv_fetch_array($IDX1);
		if ($IDX2[0] != "") {
			$iIDX = $IDX2[0];
		}
		$iIDX = @$iIDX + 1;
		$sdate = date("Y-m-d");
		$edate = date('Y-m-d', strtotime('+20 years'));
		/* Check if IDX Value auto increments in CL table */
		$autoidxquery = "SELECT is_identity FROM sys.columns WHERE object_id = object_id('clandb.dbo.cl') AND name = 'IDX'";
		$autoidxresult = sqlsrv_query($dbconn, $autoidxquery, array());
		$autoidxresult = sqlsrv_fetch_array($autoidxresult);
		if ($autoidxresult[0] == 1)
		{
			$CLInsert = "INSERT INTO clandb.dbo.CL ([ClanName],[UserID],[ClanZang],[MemCnt],[Note],[MIconCnt],[RegiDate],[LimitDate],[DelActive],[PFlag],[KFlag],[Flag],[NoteCnt],[Cpoint],[CWin],[CFail],[ClanMoney],[CNFlag],[SiegeMoney]) values('$clname','$userid','$chname','1','$expl','$iIMG','$sdate','$edate','0','0','0','0','1','0','0','0','0','0','0')";
		}
		else
		{
			$CLInsert = "INSERT INTO clandb.dbo.CL ([IDX],[ClanName],[UserID],[ClanZang],[MemCnt],[Note],[MIconCnt],[RegiDate],[LimitDate],[DelActive],[PFlag],[KFlag],[Flag],[NoteCnt],[Cpoint],[CWin],[CFail],[ClanMoney],[CNFlag],[SiegeMoney]) values('$iIDX','$clname','$userid','$chname','1','$expl','$iIMG','$sdate','$edate','0','0','0','0','1','0','0','0','0','0','0')";
		}
		sqlsrv_query($dbconn, $CLInsert);
		$IDXCheck = "SELECT IDX FROM clandb.dbo.CL WHERE ClanName='$clname'";
		$IDXC = sqlsrv_query($dbconn, $IDXCheck, array());
		$IDXC1 = sqlsrv_fetch_array($IDXC);
		if ($IDXC1[0] != "") {
			$IDX = $IDXC1[0];
		}
		$autoidxquery = "SELECT is_identity FROM sys.columns WHERE object_id = object_id('clandb.dbo.ul') AND name = 'IDX'";
		$autoidxresult = sqlsrv_query($dbconn, $autoidxquery, array());
		$autoidxresult = sqlsrv_fetch_array($autoidxresult);
		if ($autoidxresult[0] == 1)
		{
			$ULInsert = "INSERT INTO clandb.dbo.UL ([MIDX],[userid],[ChName],[ClanName],[ChType],[ChLv],[Permi],[JoinDate],[DelActive],[PFlag],[KFlag],[MIconCnt]) values('3','$userid','$chname','$clname','$chtype','$lv','0','$sdate','0','0','0','$iIMG')";
		}
		else
		{
			$ULInsert = "INSERT INTO clandb.dbo.UL ([IDX],[MIDX],[userid],[ChName],[ClanName],[ChType],[ChLv],[Permi],[JoinDate],[DelActive],[PFlag],[KFlag],[MIconCnt]) values('$IDX','3','$userid','$chname','$clname','$chtype','$lv','0','$sdate','0','0','0','$iIMG')";
		}
		sqlsrv_query($dbconn,$ULInsert);
		print("Code=1".$CR."CMoney=500000".$CR);
		sqlsrv_close($dbconn);
	} else {
		print "Missing GET Data";
	}
} else {
	print("Unable To Connect");
}
?>