<?php session_start();
	  
	  include_once("start.php");
	  
	  include_once("sql.php");
	  
			if($_GET['sess'] == 'logout'){
				
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
					  
				header("location: login.php");
			
			exit();
			
			}


	if(!$_SESSION['CODACESS']){
		
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link href="favicon.ico" rel="shortcut icon" />
<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/shadowbox.css">
<link rel="stylesheet" type="text/css" href="css/qTip.css">
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script type="text/javascript" src="js/functions.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<script type="text/javascript" src="js/moeda.js"></script>

<title><?php echo $version; ?></title>


</head>

<body>


<?php if(isset($_POST['logar'])){

             $login = $_POST['id'];
			 $senha = $_POST['senha'];
			
			if(empty($login) or filtro($login) or empty($senha) or filtro($senha)){
				
					echo "<script language = 'JavaScript'>
							alert('Special characters found.');
							window.location.href = 'login.php';
						  </script>";

			} else {
			
$verificarConta = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[".(strtoupper($login[0]))."GameUser] WHERE [userid] = '$login' AND [Passwd] = '$senha'");
			$qt = odbc_do($conexao, "SELECT *FROM [accountdb].[dbo].[".(strtoupper($login[0]))."GameUser] WHERE [userid] = '$login' AND [Passwd] = '$senha'");
				if(odbc_fetch_row($qt) == 1){
				
				//GERA UM CÓDIGO DE SESSÃO E REGISTRA	
				$pin = date("d-m-Y").time().$linha['RegistDay'];
			    $_SESSION["CODACESS"] = (strtoupper(substr(md5($pin),0,32)));

                $linha = odbc_fetch_array($verificarConta);
				
                $_SESSION["ID"]  = $linha['userid'];
                
				//GRAVA O CODIGO DE ACESSO E CADASTRO AO SHOPPING
				$_SESSION["COD"] = substr(md5($linha['userid']),0,32);
				
 					echo "<script language = 'JavaScript'>
							alert('Access allowed.');
							window.location.href = 'login.php';
						  </script>";
					  
				
            } else if(odbc_fetch_row($verificarConta) == 0){
				
					echo "<script language = 'JavaScript'>
							alert('Acess danied.');
							window.location.href = 'login.php';
						  </script>";

			}
	 }
			
} else {
		
?>
<form action="" method="post" enctype="multipart/form-data" name="account_Management" class="loginPanel">

<a href="http://www.reloadedpt.net"><div class="logo"></div></a>

<div id="acesso">

    	<div class="linha_3">
        <strong>User:</strong>
        <span id="sprytextfield1">
        <input name="id" type="text" class="campos_3" size="20" maxlength="10" id="id" autocomplete="off" autofocus="autofocus" />
        <span class="textfieldRequiredMsg">*</span>
        <span class="textfieldMinCharsMsg">*</span>
        <span class="textfieldMaxCharsMsg">*</span>
        </span>
        </div>
        
    	<div class="linha_3">
        <strong>Password:</strong>
        <span id="sprytextfield2">
        <input name="senha" type="password" class="campos_3" size="15" maxlength="8" id="senha" />
        <span class="textfieldRequiredMsg">*</span>
        <span class="textfieldMinCharsMsg">*</span>
        <span class="textfieldMaxCharsMsg">*</span>
        </span>
        </div>
        
   	<input type="submit" name="logar" value="Login" class="botoes_3" > 
   		
    <div class="linha_4"><a href="enviaSenha.php">Recovery password</a></div>
    <div class="linha_4"><a href="cadastro.php">Create account</a></div>

    
    


</div>

</form>
<?php } ?>


<a href="http://www.websystens.com" target="_blank" title="Power by Web systens®"><div class="rodape"></div></a>


<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprytextfield1", "none", {validateOn:["blur"]});
var sprytextfield2 = new Spry.Widget.ValidationTextField("sprytextfield2", "none", {validateOn:["blur"]});
</script>
</body>
</html>
<?php exit;
	}
	
		include_once ("principal.php");
		include("rotinas.php");
		
	ob_end_flush();
?>
