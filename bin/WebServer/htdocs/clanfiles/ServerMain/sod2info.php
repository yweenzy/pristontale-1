<?php
include 'settings.php';
$CR = chr(13);
$CR2 = chr(124);
$userid = (isset($_GET['userid'])) ? $_GET['userid'] : "";
$gserver = (isset($_GET['gserver'])) ? $_GET['gserver'] : "";
$chname = (isset($_GET['chname'])) ? $_GET['chname'] : "";
$index = (isset($_GET['index'])) ? $_GET['index'] : "";
if ($userid == "" || $gserver == "" || $chname == "")
{
	die("Code=100");
}
if ($index == "")
{
	die("Code=104");
}
switch ($index)
{
	case "1": //Main Karina Page
		$query = "SELECT * FROM ClanDB.dbo.CL ORDER BY Cpoint DESC";
		$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
		if (sqlsrv_num_rows($result) > 0)
		{
			$row = sqlsrv_fetch_array($result);
			$ClanPoint = $row['Cpoint'];
			$ClanNote = $row['Note'];
			$ClanName = $row['ClanName'];
			$ClanIMG = $row['MIconCnt'];
			$ClanLeader = $row['ClanZang'];
			$ClanMoney = $row['ClanMoney'];
			
			$query = "SELECT * FROM ClanDB.dbo.UL WHERE chname='$chname'";
			$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
			if (!sqlsrv_num_rows($result) > 0)
			{
				$iNum = 0;
				$return = "Code=".$iNum.$CR2."CClanMoney=0 $CR 2CTax=0 $CR2 CName= $CR2 CNote= $CR2 CZang= $CR2 CIMG= $CR2";
			}
			else
			{				
				$row = sqlsrv_fetch_array($result);
				$ClanSub = $row['ClanName'];
				$ClanSubChief = $row['Permi'];
				if ($ClanName == $ClanSub)
				{
					if ($ClanLeader == $chname)
					{
						$iNum = 1;
						$return = "Code=$iNum".$CR2."CClanMoney=$ClanMoney".$CR2."CTax=0".$CR2."CName=$ClanName".$CR2."CNote=$ClanNote".$CR2."CZang=$ClanLeader".$CR2."CIMG=$ClanIMG".$CR2."TotalEMoney=$ClanMoney".$CR2."TotalMoney=$ClanMoney".$CR2;
					}
					elseif ($ClanSubChief = 2)
					{
						$iNum = 2;
						$return = "Code=$iNum".$CR2."CClanMoney=0".$CR2."CTax=0".$CR2."CName=$ClanName".$CR2."CNote=$ClanNote".$CR2."CZang=$ClanLeader".$CR2."CIMG=$ClanIMG".$CR2."TotalEMoney=$ClanMoney".$CR2."TotalMoney=$ClanMoney".$CR2;
					}
					else 
					{
						$iNum = 3;
						$return = "Code=$iNum".$CR2."CClanMoney=0".$CR2."CTax=0".$CR2."CName=$ClanName".$CR2."CNote=$ClanNote".$CR2."CZang=$ClanLeader".$CR2."CIMG=$ClanIMG".$CR2."TotalEMoney=$ClanMoney".$CR2."TotalMoney=$ClanMoney".$CR2;
					}
				}
				else
				{
					$query = "SELECT ClanZang FROM Clandb.dbo.CL WHERE ClanName='$ClanSub'";
					$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
					$row = sqlsrv_fetch_array($result);
					$ClanSubLeader = $row['ClanZang'];
					if ($ClanSubLeader == $chname)
					{
						$iNum = 4;
						$return = "Code=$iNum".$CR2."CClanMoney=0".$CR2."CTax=0".$CR2."CName=".$ClanName.$CR2."CNote=".$ClanNote.$CR2."CZang=".$ClanLeader.$CR2."CIMG=$ClanIMG".$CR2;
					}
					elseif ($ClanSubChief == 2)
					{
						$iNum = 5;
						$return = "Code=$iNum".$CR2."CClanMoney=0".$CR2."CTax=0".$CR2."CName=".$ClanName.$CR2."CNote=".$ClanNote.$CR2."CZang=".$ClanLeader.$CR2."CIMG=$ClanIMG".$CR2;
					}
					else
					{
						$iNum = 6;
						$return = "Code=$iNum".$CR2."CClanMoney=0".$CR2."CTax=0".$CR2."CName=".$ClanName.$CR2."CNote=".$ClanNote.$CR2."CZang=".$ClanLeader.$CR2."CIMG=$ClanIMG".$CR2;
					}
				}
			}
		}
		else
		{
			$return = "Code=0";
		}
		break;
	Case "3": //High Score Clan List
		$query = "SELECT * FROM ClanDB.dbo.CL ORDER BY Cpoint DESC";
		$result = sqlsrv_query($dbconn, $query, array(), array('Scrollable' => 'Static'));
		if (!sqlsrv_num_rows($result) > 0)
		{
			$return = "Code=0";
		}
		else
		{
			$return = "Code=1$CR";
			$i = 0;
			$rescount = sqlsrv_num_rows($result);
			while ($i < $rescount)
			{
				if ($i >= 9)
				{
					$i = sqlsrv_num_rows($result);
				}
				$tSubRegiDate = "";
				$tSub2 = "";
				$tSub3 = 0;
				$row = sqlsrv_fetch_array($result);
				$ClanName = $row['ClanName'];
				$tSub = $row['RegiDate']->format('n/j/Y');
				$x = 0;
				while ($x <= strlen($tSub))
				{
					if ($tSub3 == 0)
					{
						$tSub2 = substr($tSub, $x, 1);
						if ($tSub2 != " ")
						{
							$tSubRegiDate .= $tSub2;
						}
						else
						{
							$tSub3 = 1;
						}
					}
					$x++;
				}
				if (!stripos($return, $ClanName) !== false && $row['Cpoint'] > 0)
				{
					$return = $return."CIMG=".$row['MIconCnt'].$CR."CName=$ClanName $CR CPoint=".$row['Cpoint'].$CR."CRegistDay=$tSubRegiDate $CR";
				}
				$i++;
			}
		}
		break;
	default: 
		$return = "Code=104";
}
sqlsrv_close($dbconn);
print($return);
?>