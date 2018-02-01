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
<link href="SpryAssets/SpryValidationPassword.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationConfirm.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationSelect.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="js/jquery.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationPassword.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationConfirm.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationSelect.js" type="text/javascript"></script>

<script type="text/javascript" src="js/validationKey.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>

<script type="text/javascript">
Shadowbox.init({

handleOversize: "drag",
displayNav: true,	
handleUnsupported: "remove",
modal: true

});

function open_win() 
{
window.open("sendKey.php?ws=<?php echo $_SESSION['ID']; ?>","Send key code in your e-mail.","width=500,height=220");
}
</script>
<title>Account</title>
</head>

<body>

<div id="painel">
<div class="painel">


<?php if(isset($_POST['atualizar'])){
	
	//FILTRAR INJECT
	include("injection.php");
	
    if(anti_sql($_POST['keyCod'])
	or anti_sql($_POST['senhaOld'])
	or anti_sql($_POST['senha'])
	or anti_sql($_POST['senha_copy'])
	or anti_sql($_POST['nome'])
	or anti_sql($_POST['sobre'])
	or anti_sql($_POST['dia'])
	or anti_sql($_POST['mes'])
	or anti_sql($_POST['ano'])
	or anti_sql($_POST['email'])
	or empty($_POST['keyCod'])
	or empty($_POST['senhaOld'])
	or empty($_POST['senha'])
	or empty($_POST['senha_copy'])
	or empty($_POST['nome'])
	or empty($_POST['sobre'])
	or empty($_POST['email'])
	or ($_POST['dia'] == 0)
	or ($_POST['mes'] == 0)
	or ($_POST['ano'] == 0)){
		
	echo '<script type="text/javascript">
			alert("Characters unauthorized or empty fields found.");
			history.back();
		  </script>';	
		
	} else {

//###CONSULTAS####		
$verPW = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '".$_SESSION[ID]."'");
$verific = odbc_fetch_array($verPW);
	
$verKey = odbc_exec($conexao, "SELECT *FROM [ChaveDB].[dbo].[ChaveAccount] WHERE [userid] = '".$_SESSION[ID]."'");
$checkKey = odbc_fetch_array($verKey);
	
$verMAIL = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Email] = '".$_POST[email]."'");
$checkMail = odbc_fetch_array($verMAIL);
##################

		if($verific['Passwd'] != $_POST['senhaOld']){
		
			echo '<script type="text/javascript">
					alert("Your old password is invalid.");
				    window.location.href = "login.php?sess=acc";
				  </script>';
		
 } else if($checkKey['chave'] != $_POST['keyCod']){
	 
			echo '<script type="text/javascript">
					alert("Key entered does not match requested by email.");
				    window.location.href = "login.php?sess=acc";
				  </script>';
				  	
 } else if($checkMail['Email'] != $verific['Email'] and odbc_num_rows($verMAIL) >= 1){
	
			echo '<script type="text/javascript">
					alert("This email is already used by another user.");
				    window.location.href = "login.php?sess=acc";
				  </script>';	
	 
 } else {


					
		
	//DELETA AS CHAVES GERADAS ANTES, POIS O E-MAIL PODE SER ALTERADO, EVITAR BUGS.
	$cleanChave = odbc_exec($conexao, "DELETE FROM [ChaveDB].[dbo].[ChaveAccount] WHERE email = '".$verific[Email]."'
																			   AND userid = '".$verific[Userid]."'");
																			   
																			   

	//EFETUA ALTERAÇÕES DE DADOS, FAZENDO UPDATE NO CAMPO SENHA DAS 4 TABELAS.
	$gameuser = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[".(strtoupper($_SESSION[ID][0]))."GameUser] SET [Passwd] = '".$_POST[senha]."'
																		                             WHERE [userid] = '".$_SESSION[ID]."'");
	
	$allgameuser = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[AllGameUser] SET [Passwd] = '".$_POST[senha]."'
																			 WHERE [userid] = '".$_SESSION[ID]."'");
	
	$personal = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[".(strtoupper($_SESSION[ID][0]))."PersonalMember] SET 
																							[Passwd] = '".$_POST[senha]."', 
																							[CUserName1] = '".$_POST[nome]."', 
																							[CUserName2] = '".$_POST[sobre]."', 
																							[Email] = '".$_POST[email]."'
																							WHERE [Userid] = '".$_SESSION[ID]."'");
	
	$allpersonal = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[AllPersonalMember] SET [Passwd] = '".$_POST[senha]."', 
																						 [CUserName1] = '".$_POST[nome]."', 
																						 [CUserName2] = '".$_POST[sobre]."', 
																						 [Email] = '".$_POST[email]."',
																						 [DiaNasc] = '".$_POST[dia]."',
																						 [MesNasc] = '".$_POST[mes]."',
																						 [AnoNasc] = '".$_POST[ano]."'
																						 WHERE [Userid] = '".$_SESSION[ID]."'");
			
					if($gameuser and $allgameuser and $personal and $allpersonal and $cleanChave){
					
					echo '<script language = "JavaScript">
							alert("Account information changed successfully login again.");
							window.location.href = "logout.php";
						  </script>';
						
					} else {
					
					echo "<script language = 'JavaScript'>
							alert('There was an error, please notify the administrator about what happened.');
							window.location.href = 'logout.php';
						  </script>";
						  	
			} //FIM DAS QUERYS
					
 		} //FIM DAS VERIFICAÇÕES
		
	} // FECHA INJECTION
	
} //FECHA ISSET
?>


<div class="comunicado">

To make any changes to your account, it will be necessary to use a key sent to registered email address and enter your password in the login panel.

</div>


<form action="" method="post" name="updateDados" enctype="multipart/form-data" class="formPainel">

<?php //CONSULTA DAS INFOS DA CONTA
	
	$peg = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '".$_SESSION[ID]."'");
	$res = odbc_fetch_array($peg);


?>
<div class="titulo">Account Information</div>

	   	<div class="linha_2">
        <strong>User ID</strong>
        <input name="loginID" id="loginID" type="text" class="campos_2" value="<?php echo $_SESSION["ID"]; ?>" size="15" maxlength="8" readonly="readonly" />
        </div>

	   	<div class="linha_2">
        <strong>Key code</strong>
        <div id="status_key"></div>
        <span id="sprytextfield5">
        <input name="keyCod" id="keyCod" type="text" class="campos_2" size="25" maxlength="20" autocomplete="off"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        <br />
        <br />
        <input type="button" value="Request key" onclick="open_win()" class="botoes_5">

      </div>

    	<div class="linha_2">
        <strong>Old password:</strong>
        <span id="SprayOLDsenha">
        <input name="senhaOld" type="password" class="campos_2" size="25" maxlength="8" id="senhaOld" autocomplete="off"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>

    	<div class="linha_2">
        <strong>New password:</strong>
        <span id="senhaSpray_1">
        <input name="senha" type="password" class="campos_2" size="25" maxlength="8" id="senha" autocomplete="off"/>
        <span class="passwordRequiredMsg">*</span> 
        </span>
        </div>

    
    	<div class="linha_2">
        <strong>Confirm new password:</strong>
        <span id="senhaSpray_2">
        <input name="senha_copy" type="password" class="campos_2" size="25" maxlength="8" id="senha_copy" autocomplete="off"/>
        <span class="confirmRequiredMsg">*</span>
        <span class="confirmInvalidMsg">Passwords are different.</span>
        </span>
        </div>

        <div class="titulo">Personal data</div>

      <div class="linha_2">
        <strong>First name:</strong>
        <span id="nomeSpray">
        <input name="nome" type="text" class="campos_2" autocomplete="off" value="<?php echo $res["CUserName1"]; ?>" size="30" maxlength="30"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>

    
    	<div class="linha_2">
        <strong>Last name:</strong>
        <span id="sprytextfield4">
        <input name="sobre" type="text" class="campos_2" value="<?php echo $res["CUserName2"]; ?>" size="50" maxlength="50" autocomplete="off"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>

    
    	<div class="linha_2">
        
        <strong>Date of birth:</strong>
        <span id="spryselect1">
        <select name="dia">
          <option value="0">Day </option>
          <?php for($dia = 1; $dia <= 31; $dia++){ ?>
          <option <?php if($dia == $res['DiaNasc']){ echo 'selected="selected"'; } ?> 
           value="<?php echo $dia; ?>"><?php echo $dia; ?></option>
          <?php } ?>
        </select>
        
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        
        <span id="spryselect2">
        <select name="mes">
          <option value="0">Month </option>
          <?php for($mes = 1; $mes <= 12; $mes++){ ?>
          <option <?php if($mes == $res['MesNasc']){ echo 'selected="selected"'; } ?> 
           value="<?php echo $mes; ?>"><?php echo DateExtenso($mes); ?></option>
          <?php } ?>
        </select>
        
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        
        <span id="spryselect3">
        <select name="ano">
          <option value="0">Year </option>
          <?php for($ano = 1900; $ano <= date("Y")-8; $ano++){ ?>
          <option <?php if($ano == $res['AnoNasc']){ echo 'selected="selected"'; } ?> 
           value="<?php echo $ano; ?>"><?php echo $ano; ?></option>
          <?php } ?>
        </select>
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        </div>

    <div class="linha_2">
    
    <span id="SprayEmail">
    <strong>Email</strong>
    <input name="email" type="text" class="campos_1" value="<?php echo $res["Email"]; ?>" />
    <span class="textfieldRequiredMsg">*</span> 
    <span class="textfieldMaxCharsMsg">*</span>
    <span class="textfieldInvalidFormatMsg">Email invalid.</span>
    </span>
    
    </div>


		<div class="linha"><input type="submit" name="atualizar" value="Update" class="botoes_1" /></div>


</form>

</div>
</div>


<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("SprayEmail", "email", {validateOn:["blur"], hint:"Enter your e-mail", maxChars:50});
var sprytextfield3 = new Spry.Widget.ValidationTextField("nomeSpray", "none", {validateOn:["blur"], hint:"First name"});
var sprytextfield4 = new Spry.Widget.ValidationTextField("sprytextfield4", "none", {validateOn:["blur"], hint:"Last name"});
var sprypassword1 = new Spry.Widget.ValidationPassword("senhaSpray_1", {validateOn:["blur"]});
var spryconfirm1 = new Spry.Widget.ValidationConfirm("senhaSpray_2", "senha", {validateOn:["blur"]});
var spryselect1 = new Spry.Widget.ValidationSelect("spryselect1", {invalidValue:"0", validateOn:["blur"]});
var spryselect2 = new Spry.Widget.ValidationSelect("spryselect2", {invalidValue:"0", validateOn:["blur"]});
var spryselect3 = new Spry.Widget.ValidationSelect("spryselect3", {invalidValue:"0", validateOn:["blur"]});
var sprytextfield2 = new Spry.Widget.ValidationTextField("SprayOLDsenha", "none", {validateOn:["blur"]});
var sprytextfield5 = new Spry.Widget.ValidationTextField("sprytextfield5", "none", {validateOn:["blur"], hint:"Key code here"});
</script>
</body>
</html>