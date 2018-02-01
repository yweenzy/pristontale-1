<?php
ini_set('default_charset', 'EUC-KR');
include 'settings.php';
// Filter Input Array
$_GET = filter_input_array(INPUT_GET, FILTER_SANITIZE_STRING);
// Assign Values
$userid = isset($_GET['userid'])? $_GET['userid']:"";
$gserver = isset($_GET['gserver'])? $_GET['gserver']:"";
$chname = isset($_GET['chname'])? $_GET['chname']:"";
$tTime = " ¿ÀÈÄ ";
$CR = chr(13);

if($userid == "" || $gserver == "" || $chname == "") {
	print "Code=100".$CR;
	sqlsrv_close($dbconn);
	die;
}
$query = "SELECT ClanName FROM clandb.dbo.UL WHERE ChName='$chname'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'buffered'));
$results = sqlsrv_fetch_array($result);
if (sqlsrv_num_rows($result) == 0) {
	print "Code=0".$CR."CMoney=500000".$CR."CNFlag=0".$CR;
	sqlsrv_close($dbconn);
	die;
}
$clname = $results['ClanName'];
if ($clname == "") {
	$query = "DELETE FROM clandb.dbo.UL WHERE ChName='$chname'";
	sqlsrv_query($dbconn, $query);
	print"Code=0".$CR."CMoney=500000".$CR."CNFlag=0".$CR;
}
$query = "SELECT ClanZang,MemCnt,Note,MIconCnt,RegiDate,LimitDate,PFlag,KFlag,ClanMoney,MIconCnt FROM clandb.dbo.CL WHERE ClanName='$clname'";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'buffered'));
$results = sqlsrv_fetch_array($result);
if (sqlsrv_num_rows($result) == 0) {
	$query = "DELETE FROM clandb.dbo.UL WHERE ChName='$chname'";
	sqlsrv_query($dbconn, $query);
	print "Code=0".$CR."CMoney=500000".$CR."CNFlag=01".$CR;
}
$ClanLeader = $results['ClanZang']; $ClanMembers = $results['MemCnt']; $ClanNote = $results['Note']; 
$ClanImg = $results['MIconCnt']; $CreateDate = $results['RegiDate']->format('n/j/Y');
$EndDate = $results['LimitDate']->format('n/j/Y'); $PFlag = $results['PFlag']; $KFlag = $results['KFlag'];
$ClanMoney = $results['ClanMoney']; $iIMG = $ClanImg; $CNFlag = ""; $Pontos = ""; $tclName = "";


$query = "SELECT ClanName,Cpoint FROM clandb.dbo.CL ORDER BY Cpoint DESC";
$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'buffered'));
if (sqlsrv_num_rows($result) > 0) {
	$i = 1;
	while ($row = sqlsrv_fetch_array($result)) {
		$tclName = $row['ClanName'];
		$Points = $row['Cpoint'];
		if ($tclName == $clname) {
			if ($Points > 0) {
				switch ($i) {
					case 1:
						$CNFlag = 1;
						break;
					case 2: 
						$CNFlag = 2;
						break;
					case 3:
						$CNFlag = 3;
						break;
					default:
						$CNFlag = 0;
						break;
				} 
			} else {
				$CNFlag = 0;
			}
		}
		$i++;
	}
}
$tSubDate = "";
$tSubTime = "";
$tSub = "";
$tSub2 = "";
$i = 0;
while ($i < strlen($CreateDate)) {
	$tSub = substr($CreateDate, $i, 1);
	if ($tSub2 == 0) {
		if($tSub != " ") {
			$tSubDate = $tSubDate.$tSub;
		} else {
			$tSub2 = 1;
		}
	} else {
		if ($tSub2 == 1) {
			if ($tSub != " ") {
				$tSubTime = $tSubTime.$tSub;
			} else {
				$tSub2 = 2;
			}
		}
	}
$i++;
}


$CreateDate = $tSubDate.$tTime.$tSubTime;
$tSub = "";
$tSub2 = 0;
$tSubDate = "";
$tSubTime = "";
$y = 0;

while ($y < strlen($EndDate)) {
	$tSub = substr($EndDate, $y, 1);
	if ($tSub2 == 0) {
		if($tSub != " ") {
			$tSubDate = $tSubDate.$tSub;
		} else {
			$tSub2 = 1;
		}
	} else {
		if ($tSub2 == 1) {
			if ($tSub != " ") {
				$tSubTime = $tSubTime.$tSub;
			} else {
				$tSub2 = 2;
			}
		}
	}
$y++;
}
$EndDate = $tSubDate.$tTime.$tSubTime;

$query = "SELECT ChName FROM clandb.dbo.UL WHERE ClanName='$clname' AND Permi=2";
$result = sqlsrv_query ($dbconn, $query, array(), array('Scrollable' => 'buffered'));
$result1 = sqlsrv_fetch_array($result);
if (sqlsrv_num_rows($result) == 0) {
	$ClanSubChief = 0;
} else {
	$ClanSubChief = $result1['ChName'];
}
if ($ClanLeader == $chname) {
	if ($ClanSubChief == "") {
		$return = "Code=2".$CR."CName=".$clname.$CR."CNote=".$ClanNote.$CR."CZang=".$ClanLeader.$CR."CStats=1".$CR."CMCnt=".$ClanMembers.$CR."CIMG=".$ClanImg.$CR."CSec=60".$CR."CRegiD=".$CreateDate.$CR."CLimitD=".$EndDate.$CR."CDelActive=0".$CR."CPFlag=".$PFlag.$CR."CKFlag=".$KFlag.$CR."CMoney=".$ClanMoney.$CR."CNFlag=".$CNFlag.$CR;
	} Else {
		$return = "Code=2".$CR."CName=".$clname.$CR."CNote=".$ClanNote.$CR."CZang=".$ClanLeader.$CR."CSubChip=".$ClanSubChief.$CR."CStats=1".$CR."CMCnt=".$ClanMembers.$CR."CIMG=".$ClanImg.$CR."CSec=60".$CR."CRegiD=".$CreateDate.$CR."CLimitD=".$EndDate.$CR."CDelActive=0".$CR."CPFlag=".$PFlag.$CR."CKFlag=".$KFlag.$CR."CMoney=".$ClanMoney.$CR."CNFlag=".$CNFlag.$CR;
	}
} else {
	if ($ClanSubChief == "") {
		$return = "Code=1".$CR."CName=".$clname.$CR."CNote=".$ClanNote.$CR."CZang=".$ClanLeader.$CR."CStats=1".$CR."CMCnt=".$ClanMembers.$CR."CIMG=".$ClanImg.$CR."CSec=60".$CR."CRegiD=".$CreateDate.$CR."CLimitD=".$EndDate.$CR."CDelActive=0".$CR."CPFlag=0".$CR."CKFlag=0".$CR."CMoney=".$ClanMoney.$CR."CNFlag=".$CNFlag.$CR;
	} else {
		$return = "Code=1".$CR."CName=".$clname.$CR."CNote=".$ClanNote.$CR."CZang=".$ClanLeader.$CR."CSubChip=".$ClanSubChief.$CR."CStats=1".$CR."CMCnt=".$ClanMembers.$CR."CIMG=".$ClanImg.$CR."CSec=60".$CR."CRegiD=".$CreateDate.$CR."CLimitD=".$EndDate.$CR."CDelActive=0".$CR."CPFlag=0".$CR."CKFlag=0".$CR."CMoney=".$ClanMoney.$CR."CNFlag=".$CNFlag.$CR;
	}
}

if ($ClanSubChief == $chname) {
	if ($ClanLeader != $chname) {
		$return = "Code=5".$CR."CName=".$clname.$CR."CNote=".$ClanNote.$CR."CZang=".$ClanLeader.$CR."CSubChip=".$ClanSubChief.$CR."CStats=1".$CR."CMCnt=".$ClanMembers.$CR."CIMG=".$ClanImg.$CR."CSec=60".$CR."CRegiD=".$CreateDate.$CR."CLimitD=".$EndDate.$CR."CDelActive=0".$CR."CPFlag=".$PFlag.$CR."CKFlag=".$KFlag.$CR."CMoney=".$ClanMoney.$CR."CNFlag=".$CNFlag.$CR;
	}
}
$query = "UPDATE clandb.dbo.UL SET MIconCnt='$iIMG' WHERE ChName='$chname'";
sqlsrv_query($dbconn, $query);
print($return);
sqlsrv_close($dbconn);
?>