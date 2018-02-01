<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>

<title>Status</title>
</head>

<body>

<div class="includes">

<div class="titleItemMenu">Stats</div>
<?php $fOpen = fopen($_SESSION["charDir"], "r");
            $fRead = fread($fOpen, 4096);
            @fclose($fOpen);

            // DETALHES
            $str1 = bin2hex(substr($fRead,0xcc,1));
            $str2 = bin2hex(substr($fRead,0xcd,1));
            $strength = hexdec("$str2"."$str1");

            $spi1 = bin2hex(substr($fRead,0xd0,1));
            $spi2 = bin2hex(substr($fRead,0xd1,1));
            $spirit = hexdec("$spi2"."$spi1");

            $tal1 = bin2hex(substr($fRead,0xd4,1));
            $tal2 = bin2hex(substr($fRead,0xd5,1));
            $talent = hexdec("$tal2"."$tal1");

            $agi1 = bin2hex(substr($fRead,0xd8,1));
            $agi2 = bin2hex(substr($fRead,0xd9,1));
            $agility = hexdec("$agi2"."$agi1");

            $hea1 = bin2hex(substr($fRead,0xdc,1));
            $hea2 = bin2hex(substr($fRead,0xdd,1));
            $health = hexdec("$hea2"."$hea1");

            $defaultP = $func-> checkStatePoints($_SESSION["charLevel"]);

            $totalP = ($strength + $spirit + $talent + $agility + $health) -99;
 ?>

 <div class="linha_10">
 
 	<div class="forca"><?php echo $strength; ?></div>
    <div class="espirito"><?php echo $spirit; ?></div>
    <div class="talento"><?php echo $talent; ?></div>
    <div class="agilidade"><?php echo $agility; ?></div>
    <div class="vitalidade"><?php echo $health; ?></div>
 
 </div> 
 
 <div class="linha_10">
   <div class="points"><?php echo $defaultP - $totalP; ?></div>
 
 </div>
 

</div>

</body>
</html>