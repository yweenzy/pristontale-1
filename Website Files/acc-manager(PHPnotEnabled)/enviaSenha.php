<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/shadowbox.css">
<link rel="stylesheet" type="text/css" href="css/qTip.css">
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationPassword.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationConfirm.css" rel="stylesheet" type="text/css" />
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationPassword.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationConfirm.js" type="text/javascript"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<title>RecuperarConta</title>

</head>

<body>
<form action="" method="post" enctype="multipart/form-data" name="RecCad" id="RecCad">
<?php 
	include_once("sql.php");
	if(isset($_GET['ws'])){ 
?>


            <div class="titulo_guias">Account Recovery</div>

<?php	
	
	$chaveRecupera = $_GET['ws'];
	

if(filtro($chaveRecupera) != 0){
		
		echo "<script language = 'JavaScript'>
				alert('Unauthorized characters were found.');
				window.location.href = 'login.php';
			  </script>";
		
	} else {
		
		//VERIFICA CHAVE E PEGA O E-MAIL
		$query = odbc_exec($conexao, "SELECT *FROM [ChaveDB].[dbo].[ChaveEdit] WHERE [chave] = '".$chaveRecupera."'") or die (odbc_error());
		if(odbc_num_rows($query) == 0){ ?>
			


<div class="formCad">

			<div class='linha_2'>
            <strong>Its key was not identified.</strong>
            
            <br />
			<br />
            <br />
			<br />

            <a href="enviaSenha.php">
            <div class="botoes_2">Try again</div></a>
            </div>
</div>

          
<?php } else { 
		$result = odbc_fetch_array($query);
		
		if(isset($_POST['updatePass'])){
			
			$iduser    = $_POST['userid'];
			$emailuser = $_POST['email'];
			$senha     = $_POST['senha'];
			$senhaConf = $_POST['senha_conf'];
			
		if(empty($senha) or filtro($senha) != 0
		or empty($senhaConf) or filtro($senhaConf) != 0
		or empty($iduser) or filtro($iduser) != 0
		or empty($emailuser) or filtro($emailuser) != 0){
			
					echo "<script language = 'JavaScript'>
							alert('Unauthorized characters were found, empty fields.');
							history.back(void);
						  </script>";
						  
		} else {
			
			
	//FAZENDO UPDATE NO CAMPO SENHA DAS 4 TABELAS.
	$gameuser = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[".(strtoupper($iduser[0]))."GameUser] 
													SET [Passwd] = '".$senha."' WHERE [Userid] = '".$iduser."'");
	
	$allgameuser = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[AllGameUser] 
													SET [Passwd] = '".$senha."' WHERE [Userid] = '".$iduser."'");
	
	$personal = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[".(strtoupper($iduser[0]))."PersonalMember] 
													SET [Passwd] = '".$senha."' WHERE [Userid] = '".$iduser."'");
	
	$allpersonal = odbc_exec($conexao, "UPDATE [accountdb].[dbo].[AllPersonalMember] 
													SET [Passwd] = '".$senha."' WHERE [Userid] = '".$iduser."'");
			
			
					if($gameuser and $allgameuser and $personal and $allpersonal){
					
					echo "<script language = 'JavaScript'>
							alert('Password changed successfully.');
							window.location.href = 'logout.php';
						  </script>";
						
					//SE O CADASTRO FOR EFETUADO, ELE DELETA TODOAS AS CHAVES GERADAS PARA O E-MAIL SOLICITADO.
					$cleanChave = odbc_exec($conexao, "DELETE FROM [ChaveDB].[dbo].[ChaveEdit] WHERE email = '".$emailuser."'");
					
			
					} else {
					
					echo "<script language = 'JavaScript'>
							alert('There was an error, please notify the administrator about what happened.');
							window.location.href = 'logout.php';
						  </script>";
						
					}
		}

}
		
		
		
		//VERIFICA SE O E-MAIL EXISTE NO BANCO
		$viewDados = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Email] = '".$result[email]."'");
		$consult = odbc_fetch_array($viewDados);
?> 
<div class="formCad">           
           <div class="linha_2">
           <strong>ID</strong>
           <input name="userid" type="text" class="campos_2" id="userid" value="<?php echo $consult['Userid']; ?>" size="30" readonly="readonly"  />
           </div>
           
           <div class="linha_2">
           <strong>E-mail</strong>
           <input name="email" type="text" class="campos_2" value="<?php echo $consult['Email']; ?>" size="40" readonly="readonly"  />
           </div>

           <div class="linha_2">
           <strong>New password</strong>
           <span id="spraySenha">
           <input name="senha" id="senha" type="password" class="campos_2" size="25" maxlength="8" autofocus="autofocus" />
           <span class="passwordRequiredMsg">*</span>
           </span>
           </div>

           <div class="linha_2">
           <strong>Confirm password</strong><span id="spryConfirmRec">
           <input name="senha_conf" type="password" class="campos_2" size="25" maxlength="8" />
           <span class="confirmRequiredMsg">*</span>
           <span class="confirmInvalidMsg">Passwords are different.</span>
           </span>
           </div>
           
           <div class="linha">
           <input name="updatePass" value="Confirm" class="botoes_1" type="submit" />
           </div>
</div>

</form>

<?php } } } else if(isset($_POST['recConta'])){ 

		//VERIFICA INJEÇÃO E CAMPOS VAZIOS
		$emailrec = $_POST['emailrec'];

		
		if(empty($emailrec) or filtro($emailrec) != 0){
				
					echo "<script language = 'JavaScript'>
							alert('Special characters found.');
							window.location.href = 'enviaSenha.php';
						  </script>";

		} else {

		//VERIFICA SE O E-MAIL EXISTE NO BANCO
		$viewEmail = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Email] = '".$emailrec."'");
		
		if(odbc_num_rows($viewEmail) == 0){

					echo "<script language = 'JavaScript'>
							alert('This email is not registered in our records.');
							window.location.href = 'enviaSenha.php';
						  </script>";

		} else if(odbc_num_rows($viewEmail) >= 1){
			
			
			
			//GERA CHAVE DE RECUPERAÇÃO DE CONTA
			$chave = strtoupper(substr(sha1(date("d-M-Y H:M:S").time().$_POST['emailrec']),0,100));
			
			//GERA LINK DE ALTERAÇÃO DE SENHA
			$urlrec = $urlrecConta.$paramento.'='.$chave;
			
$gravaChave = odbc_exec($conexao, "INSERT INTO [ChaveDB].[dbo].[ChaveEdit] ([email],[chave])
													                VALUES('".$_POST[emailrec]."','".$chave."')") or die (odbc_error());
														 
	
	if($gravaChave){
		
			
			include_once("sendRecupera.php");
			
					echo "<script language = 'JavaScript'>
							alert('Follow the instructions sent in the email informed.');
							window.location.href = 'login.php';
						  </script>";


				session_unset();
				session_destroy();
				
				unset($_SESSION["charDir"], 
					  $_SESSION["charNum"],
					  $_SESSION["charID"],
					  $_SESSION["charName"],
					  $_SESSION["charLevel"],
					  $_SESSION["charClass"],
					  $_SESSION["CODACESS"],
					  $_SESSION["COD"],
					  $_SESSION["TEMPO_FIM"]);

				} else { 
				
					echo "<script language = 'JavaScript'>
							alert('There was an error generating your key, try again later.');
							window.location.href = 'login.php';
						  </script>";
	
							}
					}
			}
} else { ?>
<form action="" method="post" enctype="multipart/form-data" name="recDados">

            <div class="titulo_guias">Account Recovery</div>
            
            
            <div class="formCad">
            
            
            <div class="textos">
            <p>This is the recovery system server account <?php echo $ServerName; ?>.</p>
            
            <p>
            To regain access to your account you will need to know your email account. If you forget to contact the server administrator.</p>
            
            </div>

			<div class="linha">
            <span id="sprayRecConta">
            <input name="emailrec" type="text" class="campos_2" size="50" maxlength="50" />
            <span class="textfieldRequiredMsg">*</span>
            <span class="textfieldInvalidFormatMsg">E-mail inválido.</span>
            </span>
            </div>

			<div class="linha">
			<input type="submit" class="botoes_1" value="Send" name="recConta" />
			</div>
            
      </div>
            
</form>
<?php } ?>

<a href="http://www.websystens.com" target="_blank" title="Power by Web systens®"><div class="rodape"></div></a>

<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprayRecConta", "email", {validateOn:["blur"], hint:"Enter your e-mail"});
var sprypassword1 = new Spry.Widget.ValidationPassword("spraySenha", {validateOn:["blur"]});
var spryconfirm1 = new Spry.Widget.ValidationConfirm("spryConfirmRec", "senha", {validateOn:["blur"]});
</script>

</body>
</html>