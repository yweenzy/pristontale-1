<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/shadowbox.css">
<link rel="stylesheet" type="text/css" href="css/qTip.css">
<link href="SpryAssets/SpryAccordion.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript" src="js/moeda.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<script src="SpryAssets/SpryAccordion.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>

<title><?php echo $version; ?></title>

<script type="text/javascript">
Shadowbox.init({

handleOversize: "drag",
displayNav: true,	
handleUnsupported: "remove",
modal: false
});
</script>

<?php 
include("mysql.php");
include("sql.php");
include("functions.php");
include("bonusCash.php");
?>
</head>

<body>

<div id="SecontBg">
<div id="contentPanel">

<a href="http://www.reloadedpt.net"><div id="logo"></div></a>


<div class="tempoLogued"><?php include("tempo.php"); ?></div>

<div id="welcome">
<?php 
$userName = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '".$_SESSION[ID]."'");
$listUser = odbc_fetch_array($userName);

 echo $listUser['CUserName2']; ?>
,  welcome to the account management Reloaded Priston Tale.<br />
</div>

<div id="creditos">
<?php
//VERIFICA OS CREDITOS NO BANCO DE DADOS
$bonusCB = mysql_query("SELECT *FROM bonusCash WHERE userCB = '".$_SESSION[ID]."' AND statusCB = '1'");
$consult = mysql_query("SELECT *FROM cash WHERE userC = '".$_SESSION[ID]."' AND codC = '".$_SESSION[COD]."'");
$cred = mysql_fetch_array($consult);
$boni = mysql_fetch_array($bonusCB);
		
		if(!$cred['creditoC']){
			
			echo "0.00";
			
		} else {

			$credTotal = ($cred['creditoC']) + ($boni['creditoCB']); 
			
			echo formatMoeda($credTotal);

		}
?>
</div>

<div class="menu">
<a href="?sess=char"><img src="themes/reloadedpt/img/btn_group_1_r1_c1.png" width="106" height="43" alt="" border="0" /></a><a href="?sess=donate"><img src="themes/reloadedpt/img/btn_group_1_r1_c6.png" width="149" height="43" border="0"/></a><a href="?sess=acc"><img src="themes/reloadedpt/img/btn_group_1_r1_c10.png" width="160" height="43" border="0"/></a><a href="?sess=help"><img src="themes/reloadedpt/img/btn_group_1_r1_c14.png" width="124" height="43" border="0"/></a><a href="?sess=logout" onclick="return confirm('Log out of the panel?');"><img src="themes/reloadedpt/img/btn_group_1_r1_c18.png" width="106" height="43" border="0"/></a></div>

<!-- chamadas para verificar a transferencia de creditos -->
<div class="includes_MSG">
<?php if($_POST['transferir']){
		
		$idT = $_POST['idTrans'];
		$idR = $_SESSION['ID'];
		$cdT = $_POST['credTrans'];
		

		include("injection.php");

		//VERIFICAR INJEÇÃO DE SCRIPT
		if(anti_sql($idT != 0) or anti_sql($cdT != 0) or $_POST['credTrans'] < 0){ ?>
		
        <div class="error">invalid operation.</div>
		
		<?php //VERIFICAR SE O PLAYER POSSUÍ CRÉDITOS 
		} else if($cred['creditoC'] < $cdT){ ?>
		
        <div class="error">Insufficient funds transfer.</div>
		
  <?php } else if($cred['creditoC'] >= $cdT){
	  
		//VERIFICAR SE A ID EXISTE SQL	
		$viewID    = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '$idT'");
		if(odbc_num_rows($viewID) == 0){ ?>
		
        <div class="error">ID is not there.</div>
        	
<?php } else if(odbc_num_rows($viewID) >= 1){
		//VERIFICA SE A ID JÁ ESTÁ CADASTRADA
		
		//SE EXISTIR NO SQL VERIFICAR NO MYSQL
		$verMysql = mysql_query("SELECT *FROM cash WHERE userC = '$idT'");
		
		//CASO NÃO EXISTA CRIAR AGORA E FAZER A TRANSAÇÃO DA TRANSFERENCIA
		if(mysql_num_rows($verMysql) == 0){
			
		$insert = mysql_query("INSERT INTO cash (userC, codC, creditoC, statusC)
										 VALUES ('$idT', '00000000000000000000000', '0.00', '1')");
										 
		if($insert){	
		
		//REMOVER DE UMA CONTA E INSERIR NA OUTRA.
		
		transferCred($idT, $idR, $cdT);
		
		//CADASTRANDO NO HISTORICO O ITEM COMPRADO
				    $trans = 'Transfer of credits to the user, '.$idT;
		            mysql_query("INSERT INTO historico (qtdH, itemH, valorH, userH, dataH)
												 VALUES ('1',
														 '".$trans."',
														 '".$cdT."',
														 '".$idR."',
														 '".date('Y-m-d')."')");
			
		} else { ?>
			
			<div class="error">There was an error accessing your account information.</div>
			
  <?php }
			
			
		} else if(mysql_num_rows($verMysql) == 1){
		//CASO JÁ EXISTA FAZER A TRANSAÇÃO DOS CREDITOS REMOVER DE UMA CONTA E INSERIR NA OUTRA.
		
		transferCred($idT, $idR, $cdT);
		
		//CADASTRANDO NO HISTORICO O ITEM COMPRADO
				    $trans = 'Transfer of credits to the user, '.$idT;
		            mysql_query("INSERT INTO historico (qtdH, itemH, valorH, userH, dataH)
												 VALUES ('1',
														 '".$trans."',
														 '".$cdT."',
														 '".$idR."',
														 '".date('Y-m-d')."')");
		}
		
		
		
}
  }
		
	echo '<meta HTTP-EQUIV="Refresh" CONTENT="2;URL=login.php?sess=histo&pag=1">';
		
}?> 

</div>
<!-- fim da transferencia -->


<?php	 //INICIO DAS CHAMADAS PARA A LOJA DE ITENS
		 if($_GET['sess'] == 'shop'){ include("verificaCad.php");		
  } else if($_GET['sess'] == 'donate'){ include("api.php");		
  } else if($_GET['sess'] == 'histo'){ include("extrato.php");
  
  		//INCIO DAS CHAMADAS PARA PAGINAS ADICIONAIS SEM CHAR E INFOS OFFGAME 
  } else if($_GET['sess'] == 'acc'){ include("account.php");
  } else if($_GET['sess'] == 'help'){ include("ticket.php");
  } else if($_GET['sess'] == 'invite'){ include("invited.php");
  } else {
  
?>     
        
<div id="painel">
<div class="painel">
  
<?php 
	
	  $CHAR = ($_GET["char"]) ? $_GET["char"] : $_POST["char"];
      $qCharID = ($_SESSION["charID"]) ? $_SESSION["charID"] : $_SESSION["ID"];
	  
	
	 if(isset($_POST['deletar'])){

                $charInfo = $dirUserInfo.($func->numDir($qCharID))."/".$qCharID.".dat";

                $fRead = false;
                $fOpen = fopen($charInfo, "r");
                $fRead = fread($fOpen,filesize($charInfo));
                @fclose($fOpen);

                //LISTANDO INFORMAÇÕES DO PERSONAGEM LENDO O .DAT
                 $charNameArr=array("48" => trim(substr($fRead,0x30,15),"\x00"),
									"80" => trim(substr($fRead,0x50,15),"\x00"),
									"112" => trim(substr($fRead,0x70,15),"\x00"),
									"144" => trim(substr($fRead,0x90,15),"\x00"),
									"176" => trim(substr($fRead,0xb0,15),"\x00"));

                $chkCharLine = array();
                foreach($charNameArr as $key => $value){
					
                    if($_SESSION["charName"] == $value) $chkCharLine[] = $key;
					
					                }

                // Remove character from information file--------------------------------------

                // Fill in 00 to left character
                $addOnLeft = false;
                for($i = 0; $i < 15; $i++){
					
                    $addOnLeft.=pack("h*",00);
					
                }

                $startPoint = $chkCharLine[0];
                $endPoint = $startPoint + 15;

                $fRead = false;
                $fOpen = fopen($charInfo, "r");
                while(!feof($fOpen)){
                
				@$fRead = "$fRead".fread($fOpen, filesize($charInfo));
				
                }
                fclose($fOpen);

                $sourceStr = substr($fRead, 0, $startPoint).$addOnLeft.substr($fRead, $endPoint);
                $fOpen = fopen($charInfo, "wb"); 
                fwrite($fOpen, $sourceStr, strlen($sourceStr));
                fclose($fOpen);

                copy($dirUserData.($func->numDir($_SESSION["charName"]))."/".$_SESSION["charName"].".dat" ,$dirUserDelete."/".$_SESSION["charName"].".dat");
    $deletado = unlink($dirUserData.($func->numDir($_SESSION["charName"]))."/".$_SESSION["charName"].".dat");
				
				
//GRAVAR LOGS NO MYSQL DO CHAR QUE FOI DELETADO
if($deletado){
	
	
	
	$gravaLog = mysql_query("INSERT INTO logs (userID, charName, classe, level, datahora, operacao)
									   VALUES ('".$_SESSION[ID]."',
									   		   '".$_SESSION[charName]."',
									   		   '".$_SESSION[charClass]."',
											   '".$_SESSION[charLevel]."',
											   '".date('Y-m-d H:i:s')."',
											   'Char deletado')");
	
                        echo '<script type="text/javascript">
								alert("Character '.$_SESSION["charName"].', was deleted!");
							  </script>';

                  unset($_SESSION["charDir"],
						$_SESSION["charNum"],
						$_SESSION["charID"],
						$_SESSION["charName"],
						$_SESSION["charLevel"],
						$_SESSION["charClass"]);

                        echo '<script type="text/javascript">
								window.location.href = "login.php";
							  </script>';
}
            } else if($CHAR){

    $charDat = $dirUserData.($func->numDir($CHAR))."/".$CHAR.".dat";

    if(file_exists($charDat) && ((filesize($charDat) == 16384) || (filesize($charDat) == 111376) || (filesize($charDat) == 220976))){

        $fOpen = fopen($charDat, "r");
        $fRead = fread($fOpen,filesize($charDat));
        @fclose($fOpen);

        //DETALHES DO CHAR
        $charLevel = substr($fRead,0xc8,1);
        $charClass = substr($fRead,0xc4,1);
        $charName = trim(substr($fRead,0x10,15),"\x00");
        $charID = trim(substr($fRead,0x2c0,10),"\x00");

        if($charID == $_SESSION["ID"]){

            if($CHAR == $charName){

                switch (ord($charClass)){
					
                    case 1: $class = 'Fighter'; break;
                    case 2: $class = 'Mechanician'; break;
                    case 3: $class = 'Archer'; break;
                    case 4: $class = 'Pikeman'; break;
                    case 5: $class = 'Atalanta'; break;
                    case 6: $class = 'Knight'; break;
                    case 7: $class = 'Magician'; break;
                    case 8: $class = 'Priestess'; break;
                
				}

                $_SESSION["charDir"]   = $charDat;
                $_SESSION["charNum"]   = $func->numDir($CHAR);
                $_SESSION["charID"]    = $charID;
                $_SESSION["charName"]  = $charName;
                $_SESSION["charLevel"] = ord($charLevel);
                $_SESSION["charClass"] = $class;
				
                header("location: login.php");
				
            } else {
				
                $expName = explode("\x00",$charName);

                $fRead = false;
                $fOpen = fopen($charDat, "r");
                while(!feof($fOpen)){
					
                @$fRead = "$fRead".fread($fOpen, filesize($charDat));
                
				}
				
                fclose($fOpen);

                // Fill in 00 to left character
                $addOnLeft = false;
                $leftLen = 32 - strlen($expName[0]);
                for($i = 0; $i < $leftLen; $i++){
					
                    $addOnLeft.=pack("h*",00);
                
				}
				
                $writeName = $expName[0].$addOnLeft;

                $sourceStr = substr($fRead, 0, 16).$writeName.substr($fRead, 48);
                $fOpen = fopen($charDat, "wb"); 
                fwrite($fOpen, $sourceStr, strlen($sourceStr));
                fclose($fOpen);

					echo "<script language = 'JavaScript'>
							alert('Clean file, access the account again.');
							window.location.href = 'login.php?sess=logout';
						  </script>";

            }

        } else {
			
					echo "<script language = 'JavaScript'>
							alert('This character does not belong to this account.');
							window.location.href = 'login.php?sess=logout';
						  </script>";
       
	    }
		
    } else {
		
					echo "<script language = 'JavaScript'>
							alert('File corrupted or nonexistent character.');
							window.location.href = 'login.php';
						  </script>";
    
	}


}

if($_SESSION["charDir"]){ ?>
  
  <div class="includes">


<div class="perfilleft">

	<?php echo CharImg($_SESSION["charClass"]); ?>
    
<div class="formAuto">
      
            <form method="post" action="" enctype="multipart/form-data" name="delChar" class="formAuto">
                <input type="image" src="themes/reloadedpt/img/btn_group_2_r1_c1.png" name="deletar"
                onclick="return confirm('Really remove character <?php echo $_SESSION['charName']; ?> server?');">
                <input type="hidden" value="<?php echo $_SESSION['charName']; ?>" name="charname" />
                <input type="hidden" name="deletar" />
            </form>

</div>
</div>




<div class="perfilrigth">
	
    <div id="nickbg"> 
    <strong><?php echo $_SESSION["charName"]; ?></strong>
    </div>
 
 
    <div id="levelbg"> 
	<strong><?php echo $_SESSION["charLevel"]; ?></strong>
    </div>

	<div id="classebg"> 
    <strong><?php echo charName($_SESSION["charClass"]); ?></strong>
    </div>
    
    <div id="options">
    <a href="?sess=skill" ><img src="themes/reloadedpt/img/btn_group_2_r1_c6.png" width="124" height="43" border="0"/></a>
    &nbsp;&nbsp;&nbsp;&nbsp;
    <a href="?sess=state" ><img src="themes/reloadedpt/img/btn_group_2_r1_c10.png" width="124" height="43" border="0"/></a>
    &nbsp;&nbsp;&nbsp;&nbsp;
    <?php echo HabilitaClan($_SESSION['charName']); ?>
    </div>

</div>


</div>


<?php } ?>


<div class="includes">

<div id="charsSelect">
    <?php   $qCharID = ($_SESSION["charID"]) ? $_SESSION["charID"] : $_SESSION["ID"];
            $charInfo = $dirUserInfo.($func->numDir($qCharID))."/".$qCharID.".dat";

            if(file_exists($charInfo) && (filesize($charInfo) == 240)){
                $fRead = false;
                $fOpen = fopen($charInfo, "r");
                $fRead = fread($fOpen,filesize($charInfo));
                @fclose($fOpen);

               //LISTANDO INFORMAÇÕES DOS PERSONAGENS LENDO .DAT
               $charNameArr = array("48" => trim(substr($fRead,0x30,15),"\x00"),
									"80" => trim(substr($fRead,0x50,15),"\x00"),
									"112" => trim(substr($fRead,0x70,15),"\x00"),
									"144" => trim(substr($fRead,0x90,15),"\x00"),
									"176" => trim(substr($fRead,0xb0,15),"\x00"));

                if(count($charNameArr) > 0){
					
                    foreach($charNameArr as $key => $value){
						
                        $expValue = explode("\x00", $value);
						
                        if($expValue[0] != ""){ 
                        
						echo '<a href="?char='.$expValue[0].'">'.$expValue[0].'</a>&nbsp;&nbsp;&nbsp;&nbsp;';
                    
					} 
				}
                
				} else {
					
                    echo "vague";
                
				}

            } else {
				
                echo "vague";
            
			}

?>          
</div>

<?php $sess = (!$_GET['sess']) ? "char" : $_GET['sess'];

	switch($sess){

    case "char":
        include_once "char.inc.php";
    break;

    case "skill":
        ($_SESSION["charDir"])?include_once "skill.inc.php":"";
    break;

    case "state":
        ($_SESSION["charDir"])?include_once "state.inc.php":"";
    break;

    case "clan":
        include_once "clan.php";
    break;

}


?> 


</div>

</div>

</div>

<?php } ?>

<div id="ListaShopping">


<div id="Accordion1" class="Accordion" tabindex="0">
  <div class="AccordionPanel">
    <div class="AccordionPanelTab"><img src="themes/reloadedpt/img/TopShop.png" width="235" height="49" /></div>
    <div class="AccordionPanelContent">
      <?php $cs = mysql_query("SELECT *FROM categoria ORDER BY cat ASC");
                while($rs = mysql_fetch_array($cs)){ ?>
      <a href="login.php?sess=shop&amp;it=<?php echo $rs['idC']; ?>">
        <div class="lojItems"> <?php echo $rs['cat']; ?> </div>
        </a>
      <?php } ?>
    </div>
  </div>
<div class="AccordionPanel">
  <div class="AccordionPanelTab"><img src="themes/reloadedpt/img/TopTransfers.png" width="235" height="52" /></div>
    <div class="AccordionPanelContent">
      <div class="Campo_trans">
        <div class="texto_trans"> Enter the ID and value in Coins you want to transfer. 
        <br />
		Coins available for transfer: <strong><?php echo $cred['creditoC']; ?></strong>
        </div>
        <form action="" method="post" enctype="multipart/form-data" name="transCred">
          <strong>ID:</strong> <br />
          <span id="sprytextfield3">
            <input name="idTrans" type="text" class="campos_2" size="20" maxlength="10" />
            <span class="textfieldRequiredMsg">*</span> </span> <br />
          <strong>Coins:</strong> <br />
          <span id="sprytextfield4">
            <input name="credTrans" type="text" class="campos_2" size="20" maxlength="13"
      onkeypress="reais(this,event)" onkeydown="backspace(this,event)"/>
            <span class="textfieldRequiredMsg">*</span> </span> <br />
          <input type="submit" name="transferir" value="Transfer" class="botoes_5" 
     onclick="return confirm('Do you really want to transfer credits to account <?php echo $_SESSION['ID']; ?>?');"/>
        </form>
      </div>
    </div>
</div>
<div class="AccordionPanel">
  <div class="AccordionPanelTab"><img src="themes/reloadedpt/img/TopOptions.png" width="235" height="50" /></div>
    <div class="AccordionPanelContent">
      <div class="lojItems"><a href="?sess=histo&amp;pag=1">Extract coins</a></div>
    </div>
</div>
  <div class="AccordionPanel">
    <div class="AccordionPanelTab"><img src="themes/reloadedpt/img/TopInvite.png" width="235" height="59" /></div>
    <div class="AccordionPanelContent">
      <div class="lojItems"><a href="?sess=invite&amp;terms">Regulation Event</a></div>
      <div class="lojItems"><a href="?sess=invite&amp;send">Send an invitation</a></div>
      <div class="lojItems"><a href="?sess=invite&amp;invit">My invitations</a></div>
    </div>
  </div>
</div>

</div>
</div>

<a href="http://www.websystens.com" target="_blank" title="Power by Web systens®">
<div class="rodape"></div>
</a>

</div>

<script type="text/javascript">
var Accordion1 = new Spry.Widget.Accordion("Accordion1");
var sprytextfield3 = new Spry.Widget.ValidationTextField("sprytextfield3", "none", {validateOn:["blur"], hint:"transfer to ID"});
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprytextfield4", "none", {validateOn:["blur"], hint:"0.00"});
</script>

</body>
</html>
