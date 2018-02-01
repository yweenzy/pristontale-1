<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/shadowbox.css">
<link rel="stylesheet" type="text/css" href="css/qTip.css">
<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript" src="js/validationKey.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script type="text/javascript">
Shadowbox.init({

handleOversize: "drag",
displayNav: true,	
handleUnsupported: "remove",
modal: true

});

</script>
<title>Account</title>
</head>

<body>

<div id="painel">
<?php if(isset($_GET['terms'])){ ?>

<div class="painel">

    <div class="TopInvit">Terms of use Invite a friend</div>

            <div class="comunicado">
            
            EDITE AQUI
            
            </div>
	
    		<a href="login.php?sess=invite&send"><div class="botoes_6">Send invitation</div></a>

</div>

<?php } else if(isset($_GET['send'])){ ?>

<div class="painel">
		
        <div class="TopInvit">Send the invitation of his friend</div>

		<div class="comunicado">
		Enter your friend's name and email below to be invited, 
        and click submit when your friend accepts your invitation to play, 
        you can follow the progress of his level in my invitations
        </div>
 
 		<?php if(isset($_POST['convite'])){ 
		
			$nameInv  = $_POST['nomeInvit'];
			$emailInv = $_POST['emailInvit'];
			
			//GERAR CHAVE E DATA DO CONVITE
			$keyInvite = substr(md5($_SESSION['ID'].date("d-m-Y").time()),0,35);
			$dataagora = date('m-d-Y');
		
			if(filtro($nameInv != 0) or filtro($emailInv != 0)){ 
			
			echo "<script language = 'JavaScript'>
					alert('Characters unauthorized found.');
					window.location.href = 'login.php';
				  </script>";
			
			} else {
				
			//CONSULTA E-MAIL
		    $viewEmail      = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Email] = '".$emailInv."'");
		    $viewEmailInvit = mysql_query("SELECT *FROM invite WHERE email = '".$emailInv."'");
			
			if(odbc_num_rows($viewEmail) >= 1){ ?>
		
			<div class="error">This email already exists on the server, try another.</div>
					
			<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=invite&send">';
				  
			} else if(mysql_num_rows($viewEmailInvit) >= 1){ ?>
				
			<div class="error">This email has already received an invitation.</div>
	
			<?php  echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=invite&send">';
			
			} else if(mysql_num_rows($viewEmailInvit) == 0){
			
							           $MYSQLinvite = mysql_query("INSERT INTO invite (id,
																					   email,
																					   data,
																					   status,
																					   idConvidada,
																					   chave)
																			  VALUES ('".$_SESSION[ID]."',
																			  		  '".$emailInv."',
																					  '".$dataagora."',
																					  '0',
																					  '0',
																					  '".$keyInvite."')");
																					  
			if($MYSQLinvite){
				
				//SE GRAVAR CORRETAMENTE, ENVIA E-MAIL.
				include_once("sendInvite.php"); 
				echo '<meta HTTP-EQUIV="Refresh" CONTENT="2;URL=login.php?sess=invite&invit">';
				?>
				
                <div class="sucess">Invitation sent successfully</div>
                
			<?php } else { ?>
			
				<div class="error">There was an error sending the invitation. Notify the administrator.</div>
				
			<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="2;URL=login.php?sess=invite&send">'; 
			} }
					   
			}

		}?>
        
<form action="" method="post" name="invited" enctype="multipart/form-data">
        
      <div class="linha_6">
        <strong>Name:</strong>
        <span id="SprayNameInvite">
        <input name="nomeInvit" type="text" class="campos_1" maxlength="100"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>
    
      <div class="linha_6">
        <strong>E-mail:</strong>
        <span id="SprayEmailInvite">
        <input name="emailInvit" type="text" class="campos_1" maxlength="100"/>
        <span class="textfieldRequiredMsg">*</span>
        <span class="textfieldInvalidFormatMsg">Inválid email.</span>
        </span>
      </div>
        
      <div class="linha_6">
        <input type="submit" name="convite" value="Send" class="botoes_6" />
      </div>
      
</form>
        
</div>

<?php } else if(isset($_GET['invit'])){ ?>

<div class="painel">

	    <div class="TopInvit">All my invitations</div>

<br />
<br />

<?php

		$total_reg = 5;
		$pagina = $_GET['invit'];
		
		if(!$pagina){ $pc = 1; } else { $pc = $pagina; }
		
		$inicio = $pc - 1;
		$inicio = $inicio * $total_reg;

 $listExtra = mysql_query("SELECT *FROM invite WHERE id = '".$_SESSION[ID]."' ORDER BY email ASC LIMIT $inicio,$total_reg");
 $verInvit  = mysql_query("SELECT *FROM invite WHERE id = '".$_SESSION[ID]."'");
	   
	$cont_Reg = mysql_num_rows($verInvit);
	$cont_Pag = $cont_Reg / $total_reg;

	  if($cont_Reg == 0){ ?>
		
        <div class="error">You do not even possess invitations sent.</div>
        
<?php } else {  

		while($resInv   = mysql_fetch_array($listExtra)){
		
		  $qCharID1 = $resInv['idConvidada']; 
		  
		  if($qCharID1 == '0' and ($resInv['status'] == '0')){
?>
		
<div class="bgInvitedtop"><?php echo $resInv['email']; ?></div>
<div class="boxInv">

	<div class="charInv"><?php echo CharImgInv($charClass); ?></div>
    
    <div class="statusInv"><?php echo statsInv($resInv['status'], $expValue[0], $resInv['idConvidada']); ?></div>
    <div class="nickInv">Information not updated.</div>
    <div class="levelInv">Information not updated.</div>
    <div class="dataInv"><?php echo $resInv['data']; ?></div>

</div>


<?php } if($qCharID1 == '0' and ($resInv['status'] == '1')){
?>
		
<div class="bgInvitedtop"><?php echo $resInv['email']; ?></div>
<div class="boxInv">

	<div class="charInv"><?php echo CharImgInv($charClass); ?></div>
    
    <div class="statusInv"><?php echo statsInv($resInv['status'], $expValue[0], $resInv['idConvidada']); ?></div>
    <div class="nickInv">Information not updated.</div>
    <div class="levelInv">Information not updated.</div>
    <div class="dataInv"><?php echo $resInv['data']; ?></div>

</div>


<?php }     //PEGANDO O CHAR CONVIDADO
            $charInfo1 = $dirUserInfo.($func->numDir($qCharID1))."/".$qCharID1.".dat";
							        
			    if(file_exists($charInfo1) && (filesize($charInfo1) == 240)){
                $fRead = false;
                $fOpen = fopen($charInfo1, "r");
                $fRead = fread($fOpen,filesize($charInfo1));
                @fclose($fOpen);

               //LISTANDO INFORMAÇÕES DOS PERSONAGENS LENDO .DAT
               $charNameArr1 = array("48" => trim(substr($fRead,0x30,15),"\x00"),
									"80" => trim(substr($fRead,0x50,15),"\x00"),
									"112" => trim(substr($fRead,0x70,15),"\x00"),
									"144" => trim(substr($fRead,0x90,15),"\x00"),
									"176" => trim(substr($fRead,0xb0,15),"\x00"));
									
                if(count($charNameArr1) > 0){
					
                    foreach($charNameArr1 as $key => $value){
						
						//DETALHES
                        $expValue = explode("\x00", $value);

						 if($expValue[0] != ""){ 
		
						//CRIAR CONDIÇÃO AQUI
						$charDat1 = $dirUserData.($func->numDir($expValue[0]))."/".$expValue[0].".dat";
						$fOpen = fopen($charDat1, "r");
						$fRead = fread($fOpen,filesize($charDat1));
						@fclose($fOpen);
						
						//DETALHES DO CHAR
						$charLevel = substr($fRead,0xc8,1);
						$charClass = substr($fRead,0xc4,1);
						$charName = trim(substr($fRead,0x10,15),"\x00");
						$charID = trim(substr($fRead,0x2c0,10),"\x00");
                        
						if(ord($charLevel) >= $levelstart){
    
?> 
         
<div class="bgInvitedtop"><?php echo $resInv['email']; ?></div>
<div class="boxInv">

	<div class="charInv"><?php echo CharImgInv(ord($charClass)); ?></div>
    
    <div class="statusInv"><?php echo statsInv($resInv['status'], $expValue[0], $resInv['idConvidada']); ?></div>
    <div class="nickInv"><?php echo VarEmpty($expValue[0]); ?></div>
    <div class="levelInv"><?php echo VarEmpty(ord($charLevel)); ?></div>
    <div class="dataInv"><?php echo $resInv['data']; ?></div>

</div>

<?php 					}
					} 
				} 
			}
		}
	} 
?>
                                            <div class="content_av">
                                                    
                                            <?php //PAGINAÇÃO
                                            for($page = 1; $page <= ceil($cont_Pag); $page++){ 
                                                    
                                                  if($_GET['invit'] == $page){
                                            ?>
                                                  <div class="pag_2"><?php echo $page."  "; ?></div>
                                                    
                                            <?php } if($_GET['invit'] != $page){ ?>
                                                  <a href='login.php?sess=invite&amp;invit=<?php echo $page; ?>'>
                                                    <div class="pag"><?php echo $page."  "; ?></div>
                                                    </a>
                                            
                                            
                                            <?php } } ?>
                                            
                                            </div>
<?php } ?>

</div>

<?php } ?>


</div>
<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("SprayNameInvite", "none", {validateOn:["blur"]});
var sprytextfield2 = new Spry.Widget.ValidationTextField("SprayEmailInvite", "email", {validateOn:["blur"]});
</script>
</body>
</html>