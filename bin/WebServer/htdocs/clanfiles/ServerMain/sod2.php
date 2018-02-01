<?php
/**
*  Clan SoD Score - Written By Phatkone/EuphoriA
*  Credit to Vormav for Query Strings
**/
include 'settings.php';
$SNo = isset($_GET['SNo']) ? $_GET['SNo'] : "";
$yyMM = date('ym');
$today = new DateTime();
$today = $today->format('m-d-y H:i');

$addtime = new DateTime();
$negtime = new DateTime();
$addtime->add(new DateInterval('PT' . 2 . 'M'));
$negtime->sub(new DateInterval('PT' . 2 . 'M'));
$addtime = $addtime->format('m-d-y H:i:s');
$negtime = $negtime->format('m-d-y H:i:s');

if ($dbconn) {
	$query = "INSERT INTO soddb.dbo.sod2clan$yyMM SELECT
	clandb.dbo.ul.ChName,Point, RegistDay, ClanName FROM
	clandb.dbo.ul, soddb.dbo.sod2record$yyMM WHERE 
	clandb.dbo.ul.ChName = soddb.dbo.sod2record$yyMM.charname
	AND SNo = '$SNo' AND RegistDay BETWEEN '$negtime' AND
	'$addtime'";
	
	sqlsrv_query($dbconn, $query);
	
	$query2 = "	SELECT clandb.dbo.UL.ChName, Point, RegistDay, ClanName
	FROM clandb.dbo.UL, soddb.dbo.sod2record$yyMM WHERE
	clandb.dbo.UL.ChName = soddb.dbo.sod2record$yyMM.charname
	AND RegistDay BETWEEN '$negtime' AND '$addtime' and
	ClanName = (SELECT clandb.dbo.UL.ClanName FROM ClanDB.dbo.UL 
	INNER JOIN soddb.dbo.sod2record$yyMM ON SNo = '$SNo' AND 
	clandb.dbo.UL.ChName = soddb.dbo.sod2record$yyMM.CharName WHERE
	ClanName=(SELECT clandb.dbo.UL.ClanName FROM clandb.dbo.UL INNER 
	JOIN soddb.dbo.sod2record$yyMM ON SNo = '$SNo' AND
	clandb.dbo.UL.ChName = soddb.dbo.sod2record$yyMM.CharName))";
	
	$results = sqlsrv_query($dbconn, $query2, array(), array('Scrollable' => 'static'));
		if (sqlsrv_num_rows($results) >= 2) {
		$query3 = "UPDATE ClanDb.dbo.CL SET RegiDate =
		'$today', Cpoint = (SELECT SUM(Point) FROM
		SodDb.dbo.Sod2Clan$yyMM WHERE SodDb.dbo.Sod2Clan$yyMM.
		RegistDay BETWEEN '$negtime' AND '$addtime' AND	
		ClanName = (SELECT clandb.dbo.ul.ClanName FROM 
		ClanDB.dbo.UL INNER JOIN soddb.dbo.sod2record$yyMM ON
		SNo = '$SNo' AND clandb.dbo.ul.ChName = 
		soddb.dbo.sod2record$yyMM.CharName)) WHERE 
		ClanName=(SELECT clandb.dbo.ul.ClanName FROM
		clandb.dbo.UL INNER JOIN soddb.dbo.sod2record$yyMM ON
		SNo = '$SNo' AND	clandb.dbo.ul.ChName = 
		soddb.dbo.sod2record$yyMM.charname) AND 
		ClanDB.dbo.CL.Cpoint <= (SELECT SUM(Point)
		FROM SodDb.dbo.sod2clan$yyMM WHERE 
		SodDb.dbo.Sod2Clan$yyMM.RegistDay BETWEEN 
		'$negtime' AND '$addtime' AND ClanName = 
		(SELECT clandb.dbo.ul.ClanName FROM clandb.dbo.ul 
		INNER JOIN soddb.dbo.sod2record$yyMM ON SNo = 
		'$SNo' AND clandb.dbo.ul.ChName =
		soddb.dbo.sod2record$yyMM.charname))"; 
		
		sqlsrv_query($dbconn, $query3);
		print "Bellatra";
	}
	sqlsrv_close($dbconn);
} else {
	print "Unable to Connect";
}
?>
