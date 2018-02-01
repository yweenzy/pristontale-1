<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<title>Documento sem título</title>
</head>

<body>

<?php if($_SESSION["charLevel"] < 70){ ?>

<div class="includes">

<div class="comunicado">
It is mandatory that your character has more than level 70 to
have access to our system of alteration and distribution skills from the control panel. <BR> back to try this option when you have your character above level 70.
</div>

</div>

<?php } else { ?>
	
<div class="includes">
    
<?php       $fOpen = fopen($_SESSION["charDir"], "r");
            $fRead = fread($fOpen, 4096);
            @fclose($fOpen);

            //DETALHES 
            $tier0_1 = ord(substr($fRead,0x1fd,2));
            $tier0_2 = ord(substr($fRead,0x1fe,2));
            $tier0_3 = ord(substr($fRead,0x1ff,2));
            $tier0_4 = ord(substr($fRead,0x200,2));

            $tier1_1 = ord(substr($fRead,0x201,2));
            $tier1_2 = ord(substr($fRead,0x202,2));
            $tier1_3 = ord(substr($fRead,0x203,2));
            $tier1_4 = ord(substr($fRead,0x204,2));

            $tier2_1 = ord(substr($fRead,0x205,2));
            $tier2_2 = ord(substr($fRead,0x206,2));
            $tier2_3 = ord(substr($fRead,0x207,2));
            $tier2_4 = ord(substr($fRead,0x208,2));

            $tier3_1 = ord(substr($fRead,0x209,2));
            $tier3_2 = ord(substr($fRead,0x20A,2));
            $tier3_3 = ord(substr($fRead,0x20B,2));
            $tier3_4 = ord(substr($fRead,0x1fc,2));

            $defaultSP = $func-> checkSkillPoints($_SESSION["charLevel"],'SP');
            $defaultEP = $func-> checkSkillPoints($_SESSION["charLevel"],'EP');

            $totalSP = $tier0_1 + $tier0_2 + $tier0_3 + $tier0_4 +
            $tier1_1 + $tier1_2 + $tier1_3 + $tier1_4 +
            $tier2_1 + $tier2_2 + $tier2_3 + $tier2_4;

            $totalEP = $tier3_1 + $tier3_2 + $tier3_3 + $tier3_4;

            if($_SESSION["charClass"] == "Fighter"){
               
			    $src = "img/skill/fs/";

				$t0_1 = "Meele  Mastery";
				$t0_2 = "Fire  Attribute";
				$t0_3 = "Raving";
				$t0_4 = "Impact";

				$t1_1 = "Tripple Impact";
				$t1_2 = "Brutal Swing";
				$t1_3 = "Roar";
				$t1_4 = "Rage Zecram";

				$t2_1 = "Concentration";
				$t2_2 = "Avenging Crash";
				$t2_3 = "Swift Axe";
				$t2_4 = "Bone Crash";

				$t3_1 = "Destroyer";
				$t3_2 = "Berserker";
				$t3_3 = "Cyclone Strike";
				$t3_4 = "Boost Health";

            } else if($_SESSION["charClass"] == "Mechanician"){

            	$src = "img/skill/ms/";
				
				$t0_1 = "Extreme Shield";
				$t0_2 = "Mechanic Bomb";
				$t0_3 = "Poison Attribute";
				$t0_4 = "Physical Absorbtion";

				$t1_1 = "Great Smash";
				$t1_2 = "Maximize";
				$t1_3 = "Automation";
				$t1_4 = "Spark";

				$t2_1 = "Metal Armor";
				$t2_2 = "Grand Smash";
				$t2_3 = "Mechanic Mastery";
				$t2_4 = "Spark Shield";

				$t3_1 = "Impulsion";
				$t3_2 = "Compulsion";
				$t3_3 = "Magnetic Sphere";
				$t3_4 = "Metal Golem";


                } else if($_SESSION["charClass"] == "Archer"){

            	$src = "img/skill/as/";

				$t0_1 = "Scout Hawk";
				$t0_2 = "Shooting Mastery";
				$t0_3 = "Wind Arrow";
				$t0_4 = "Perfect  Aim";

				$t1_1 = "Dion's Eye";
				$t1_2 = "Falcon";
				$t1_3 = "Arrow Of Rage";
				$t1_4 = "Avalanche";

				$t2_1 = "Elemental Shot";
				$t2_2 = "Golden Falcon";
				$t2_3 = "Bomb Shot";
				$t2_4 = "Perforation";

				$t3_1 = "Wolverine_";
				$t3_2 = "Evasion Master";
				$t3_3 = "Phoenix Shot";
				$t3_4 = "Force Of Nature";

            } else if($_SESSION["charClass"] == "Pikeman"){

            	$src = "img/skill/ps/";

				$t0_1 = "Pike Wind";
				$t0_2 = "Ice Attriute";
				$t0_3 = "Critical Hit";
				$t0_4 = "Jumping Crash";

				$t1_1 = "Ground Pike";
				$t1_2 = "Tornado";
				$t1_3 = "Block Mastery";
				$t1_4 = "Expansion";

				$t2_1 = "Venom Spear";
				$t2_2 = "Vanish";
				$t2_3 = "Critical Mastery";
				$t2_4 = "Chain Lance";

				$t3_1 = "Assasin's Eye";
				$t3_2 = "Charging Strike";
				$t3_3 = "Vague";
				$t3_4 = "Shadow Master";

            } else if($_SESSION["charClass"] == "Atalanta"){

            	$src = "img/skill/at/";

				$t0_1 = "Shield Strike";
				$t0_2 = "Farina";
				$t0_3 = "Throwing Mastery";
				$t0_4 = "Vigor Spear";

				$t1_1="Windy";
				$t1_2="Twisted Javelin";
				$t1_3="Soul Sucker";
				$t1_4="Fire Javelin";

				$t2_1="Split Javelin";
				$t2_2="Trimph Of Valhalla";
				$t2_3="Light Javelin";
				$t2_4="Storm Javelin";

				$t3_1="Hall Of Valhalla";
				$t3_2="Extreme Rage";
				$t3_3="Frost Javelin";
				$t3_4="Vengeance";

            }
        	elseif ($_SESSION["charClass"]=="Knight")
            {

            	$src="img/skill/ks/";

				$t0_1="Sword Blast";
				$t0_2="Holy Body";
				$t0_3="Physical Training";
				$t0_4="DoubleCrash";

				$t1_1="HolyValor";
				$t1_2="Brandish";
				$t1_3="Piercing";
				$t1_4="Drastic Spirit";

				$t2_1="Sword Mastery";
				$t2_2="Devine Shield";
				$t2_3="Holy Incantation";
				$t2_4="Grand Cross";

				$t3_1="Sword Of Justice";
				$t3_2="Godly Shield";
				$t3_3="God's Blessing";
				$t3_4="Divine Piercing";

            }
        	elseif ($_SESSION["charClass"]=="Magician")
            {

            	$src="img/skill/mgs/";

				$t0_1="Agony";
				$t0_2="Fire Bolt";
				$t0_3="Zenith";
				$t0_4="Fire Ball";

				$t1_1="Mental Mastery";
				$t1_2="Waternado";
				$t1_3="Enchant Weapon";
				$t1_4="Death Ray";

				$t2_1="Enery Shield";
				$t2_2="Diastrophism";
				$t2_3="Spirit Elemental";
				$t2_4="Dancing Sword";

				$t3_1="Fire Elemental";
				$t3_2="Flame Wave";
				$t3_3="Distortion";
				$t3_4="Meteorite";

            }
        	elseif ($_SESSION["charClass"]=="Priestess")
        	{

        		$src="img/skill/prs/";

				$t0_1="Healing";
				$t0_2="Holy Bolt";
				$t0_3="Multi Spark";
				$t0_4="Holy Mind";

				$t1_1="Meditation";
				$t1_2="Divine Lightening";
				$t1_3="Holy Reflection";
				$t1_4="Grand Healing";

				$t2_1="Vigor Ball";
				$t2_2="Resurrection";
				$t2_3="Extinction";
				$t2_4="Virtual Life";

				$t3_1="Glacial Spike";
				$t3_2="Regen Field";
				$t3_3="Chain Lightening";
				$t3_4="Summon Muspell";

        	} else { 
			
				$src="img/skill/";			
}

?>


<div class="titleTier"><img src="themes/reloadedpt/img/tier__r1_c1.png" width="561" height="43" /></div>


<div class="linha_11">

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier0_1; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_01.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t0_1; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier0_2; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_02.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t0_2; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier0_3; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_03.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t0_3; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier0_4; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_04.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t0_4; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

</div>


<div class="titleTier"><img src="themes/reloadedpt/img/tier__r3_c1.png" width="561" height="43" /></div>


<div class="linha_11">

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier1_1; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_05.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t1_1; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier1_2; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_06.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t1_2; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier1_3; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_07.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t1_3; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier1_4; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_08.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t1_4; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

</div>


<div class="titleTier"><img src="themes/reloadedpt/img/tier__r5_c2.png" width="561" height="43" /></div>


<div class="linha_11">

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier2_1; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_09.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t2_1; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier2_2; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_10.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t2_2; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier2_3; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_11.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t2_3; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier2_4; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_12.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t2_4; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

</div>


<div class="titleTier"><img src="themes/reloadedpt/img/tier__r7_c2.png" width="561" height="43" /></div>


<div class="linha_11">

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier3_1; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_13.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t3_1; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier3_2; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_14.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t3_2; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier3_3; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_15.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t3_3; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

<div class="tier">

	<div class="imgTier">
    <div class="levelTier">
	<?php /* if($tier0_1 != 0){ */ echo $tier3_4; /* } else { echo "1"; } */ ?></div>
    <img src="img/skill/<?php echo $_SESSION["charClass"]; ?>_16.jpg" width="39" height="39">
    </div>
    
    <div class="nomeTier"><?php echo $t3_4; ?></div>
    <a href="javascript:;" title="Information not available at the moment"><div class="descTier">Description...</div></a>

</div>

</div>


<div class="linha_11">

<div class="point_2Tier"><?php echo $defaultEP-$totalEP; ?></div>
<div class="pointTier"><?php echo $defaultSP-$totalSP; ?></div>

</div>


</div>

<?php } ?>

</body>
</html>