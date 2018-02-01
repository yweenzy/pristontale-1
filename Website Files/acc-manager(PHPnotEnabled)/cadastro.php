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
<link href="SpryAssets/SpryValidationSelect.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="js/jquery.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationPassword.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationConfirm.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationSelect.js" type="text/javascript"></script>

<script type="text/javascript" src="js/validation.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>

<script type="text/javascript">
Shadowbox.init({

handleOversize: "drag",
displayNav: true,	
handleUnsupported: "remove",
modal: true

});
</script>

<title><?php echo $version; ?></title>

</head>
<?php  ?>

<body>
<?php include("sql.php");
	  include("functions.php");
	  include("mysql.php");


if(isset($_GET['ws'])){ ?>
		
    <form action="" method="post" enctype="multipart/form-data" name="cadastro">
   
    
      <div class="titulo_guias">Account Information</div>  
                  
<?php $getChave = $_GET['ws'];

	if(filtro($getChave) != 0){
		
		echo "<script language = 'JavaScript'>
				alert('Characters unauthorized found.');
				window.location.href = 'login.php';
			  </script>";
		
	} else {
		
		//VERIFICA CHAVE E PEGA O E-MAIL
		$query = odbc_exec($conexao, "SELECT *FROM [ChaveDB].[dbo].[ChaveCad] WHERE [chave] = '".$getChave."'") or die (odbc_error());
		if(odbc_num_rows($query) == 0){ ?>
			
			<div class='linha_2'>
            <div class="error">Its key was not identified.</div>
            
            <br />
			<br />
            <br />
			<br />

            <a href="cadastro.php">
            <div class="botoes_2">Register</div>
            </a>
            
            
      </div>
			
<?php } else if(odbc_num_rows($query) == 1){ $linha = odbc_fetch_array($query); 

		if(isset($_POST['cadastrar'])){
			
		//VERIFICA SE TEM CONVITE E VERIFICA SE ELE EXISTE
		if(isset($_GET['invite'])){
		
		$keyInvite = $_GET['invite'];
		$verInvit = mysql_query("SELECT *FROM invite WHERE chave = '".$keyInvite."'");
			
		if(mysql_num_rows($verInvit) == 0){ ?>
			
         <div class="error">Your invitation does not exist or is invalid.</div> 
              
		<?php } echo '<meta HTTP-EQUIV="Refresh" CONTENT="2;URL=login.php">'; } 
		
		//GUARDA POST EM VARIAVEIS E VERIFICA INJEÇÃO E CAMPOS VAZIOS
		$email   = $_POST['email'];
		$login   = $_POST['id'];
		$senha   = $_POST['senha'];
		$senha_2 = $_POST['senha_copy'];
		$nome 	 = $_POST['nome'];
		$sobre 	 = $_POST['sobre'];
		$dia     = $_POST['dia'];
		$mes	 = $_POST['mes'];
		$ano	 = $_POST['ano'];
		
		$regisDay = date("m-d-y H:m:s");
		$seuip    = $_SERVER["REMOTE_ADDR"];
		
		if(empty($email) or filtro($email) != 0
		or empty($login) or filtro($login) != 0
		or empty($senha) or filtro($senha) != 0
		or empty($senha_2) or filtro($senha_2) != 0
		or empty($nome) or filtro($nome) != 0
		or empty($sobre) or filtro($sobre) != 0
		or empty($dia) or filtro($dia) != 0
		or empty($mes) or filtro($mes) != 0
		or empty($ano) or filtro($ano) != 0){
			
		echo "<script language = 'JavaScript'>
				alert('Required fields empty or unauthorized characters were found.');
				history.back(-1);
			  </script>";
			  
		} else {
			
		
		//CONSULTAS DE VERIFICAÇÕES
		$viewEmail = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Email] = '$email'");
		$viewID    = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '$login'");
		
		//VERIFICA SE A ID JÁ ESTÁ CADASTRADA
		if(odbc_num_rows($viewID) >= 1){
			
		echo "<script language = 'JavaScript'>
				alert('There is already another user using this login name.');
				history.back(-1);
			  </script>";
		
		
		//VERIFICA SE AS SENHAS SÃO IGUAIS
		} else if($senha != $senha_2){

		echo "<script language = 'JavaScript'>
				alert('The passwords entered do not match.');
				history.back(-1);
			  </script>";

		//VERIFICA SE O E-MAIL JÁ ESTÁ CADASTRADO		
		} else if(odbc_num_rows($viewEmail) >= 1){
		
		echo "<script language = 'JavaScript'>
				alert('The email address is already in use, please request a new key with a different email.');
				window.location.href = 'cadastro.php';
			  </script>";

		} else if(odbc_num_rows($viewID) == 0 and odbc_num_rows($viewEmail) == 0){
			
        $gameuser = odbc_exec($conexao, "INSERT INTO [accountdb].[dbo].[".(strtoupper($login[0]))."GameUser]([userid],
																											 [Passwd],
																											 [GPCode],
																											 [RegistDay],
																											 [DisuseDay],
																											 [inuse],
																											 [Grade],
																											 [EventChk],
																											 [SelectChk],
																											 [BlockChk],
																											 [SpecialChk],
																											 [Credit],
																											 [DelChk],
																											 [Channel]) 
																									 VALUES ('".$login."',
																											 '".$senha."',
																											 'PTP-RUD001',
																											 '".$regisDay."',
																											 '12-12-2020',
																											 '0',
																											 'U',
																											 '0',
																											 '0',
																											 '0',
																											 '0',
																											 '0',
																											 '0',
																											 '".$seuip."')");

   $allgameuser = odbc_exec($conexao, "INSERT INTO [accountdb].[dbo].[AllGameUser] ([userid],
																					[Passwd],
																					[GPCode],
																					[RegistDay],
																					[DisuseDay],
																					[inuse],
																					[Grade],
																					[EventChk],
																					[SelectChk],
																					[BlockChk],
																					[SpecialChk],
																					[Credit],
																					[DelChk],
																					[Channel]) 
																			VALUES ('".$login."',
																					'".$senha."',
																					'PTP-RUD001',
																					'".$regisDay."',
																					'12-12-2020',
																					'0',
																					'U',
																					'0',
																					'0',
																					'0',
																					'0',
																					'0',
																					'0',
																					'".$seuip."')");
															
	$allpersonal = odbc_exec($conexao, "INSERT INTO [accountdb].[dbo].[AllPersonalMember]([PMNo],
																						  [Userid],
																						  [Passwd],
																						  [CUserName1],
																						  [CUserName2],
																						  [Email],
																						  [RegistDay],
																						  [DiaNasc],
																						  [MesNasc],
																						  [AnoNasc],
																						  [ip]) 
																				  VALUES ('0',
																						  '".$login."',
																						  '".$senha."',
																						  '".$nome."',
																						  '".$sobre."',
																						  '".$email."',
																						  '".$regisDay."',
																						  '".$dia."',
																						  '".$mes."',
																						  '".$ano."',
																						  '".$seuip."')");
					
  $personal = odbc_exec($conexao, "INSERT INTO [accountdb].[dbo].[".(strtoupper($login[0]))."PersonalMember]([PMNo],
																											 [Userid],
																											 [Passwd],
																											 [CUserName1],
																											 [CUserName2],
																											 [Email],
																											 [RegistDay]) 
																									 VALUES ('0',
																											 '".$login."',
																											 '".$senha."',
																											 '".$nome."',
																											 '".$sobre."',
																											 '".$email."',
																											 '".$regisDay."')");
																											 
	if(isset($_GET['invite'])){				
	//SE O PLAYER FOI CONVIDADO, VERIFICAR A CHAVE DE CONVITE E FAZER UPDATE NA ID CONVIDADA
	  $convites = mysql_query("UPDATE invite SET status = '1', 
										   idProvisoria = '".$login."'
										    WHERE chave = '".$_GET[invite]."'");
					
	}
					//SE O CADASTRO FOR EFETUADO, ELE DELETA TODOAS AS CHAVES GERADAS PARA O E-MAIL SOLICITADO.
					$cleanChave = odbc_exec($conexao, "DELETE FROM [ChaveDB].[dbo].[ChaveCad] WHERE email = '".$email."'");
					
					if($allgameuser and $allpersonal and $gameuser and $personal and $cleanChave){ 
					
					//SE TODOS OS CADASTROS FORAM EFETUADOS ELE GERA A MENSAGEM DE BOAS VINDAS NO E-MAIL DO PLAYERS
					include_once("sendWelcome.php");
					
					
					?>
						
						<div class='linha_2'>
                        
                        <div class="sucess">Account created successfully.</div>
                        
                        <br />
						<br />
                        <br />
						<br />
													
                                               <a href="login.php">
                                               <div class="botoes_2">Access Your Account</div>
                          </a>
                                               
                        </div>
												
					<?php } else {  /* CRIAR FUNÇÃO QUE DELETA OQUE FOI REGISTRADO SE HOUVER UM ERRO. */ ?>
					
						<div class='linha_2'>
                        
                        <div class="error">There was an error, please notify the administrator</div>

                        <br />
						<br />
                        <br />
						<br />
													
                                               <a href="mailto:support@reloadedpt.net">
                                               <div class="botoes_2">Notify administrator</div>
                                               </a>
                        </div>
						
<?php } } 
		} //FECHA VERIFICAÇÕES
				
			} else {

?>   		
    
    <div class="formCad">
    
    	<div class="linha_2">
        <strong>E-mail:</strong> 
        <input name="email" type="text" class="campos_2" value="<?php echo $linha['email']; ?>" size="50" maxlength="50" readonly="readonly" />
        </div>

    
   	  <div class="linha_2">
        <strong>Login of the game</strong>

        <div id="status"></div>
        
        <span id="loginSpray">
        <input name="id" id="id" type="text" class="campos_2" size="25" maxlength="10" autocomplete="off" />
        <span class="textfieldRequiredMsg">*</span> 
        <span class="textfieldMaxCharsMsg">*</span> 
        <span class="textfieldMinCharsMsg">*</span>
        </span>
        
        </div>
        

    	<div class="linha_2">
        <strong>Password of the game:</strong>
        <span id="senhaSpray_1">
        <input name="senha" type="password" class="campos_2" size="25" maxlength="8" id="senha" autocomplete="off"/>
        <span class="passwordRequiredMsg">*</span> <span class="passwordMinCharsMsg">Mínimo de 6 caracteres.</span><span class="passwordMaxCharsMsg">Máximo de 8 caracteres.</span></span>
        </div>

    
    	<div class="linha_2">
        <strong>Confirm password:</strong>
        <span id="senhaSpray_2">
        <input name="senha_copy" type="password" class="campos_2" size="25" maxlength="8" id="senha_copy" autocomplete="off"/>
        <span class="confirmRequiredMsg">*</span>
        <span class="confirmInvalidMsg">Passwords are different.</span>
        </span>
        </div>

    
   	  <div class="linha_2">
        <strong>First name:</strong>
        <span id="nomeSpray">
        <input name="nome" type="text" class="campos_2" size="30" maxlength="30" autocomplete="off"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>

    
    	<div class="linha_2">
        <strong>Last name:</strong>
        <span id="sprytextfield4">
        <input name="sobre" type="text" class="campos_2" size="50" maxlength="50" autocomplete="off"/>
        <span class="textfieldRequiredMsg">*</span>
        </span>
        </div>

    
    	<div class="linha_2">
        
        <strong>Date of birth:</strong>
        <span id="spryselect1">
        <select name="dia">
          <option value="0" selected="selected">Day </option>
          <?php for($dia = 1; $dia <= 31; $dia++){ ?>
          <option value="<?php echo $dia; ?>"><?php echo $dia; ?></option>
          <?php } ?>
        </select>
        
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        
        <span id="spryselect2">
        <select name="mes">
          <option value="0" selected="selected">Month </option>
          <?php for($mes = 1; $mes <= 12; $mes++){ ?>
          <option value="<?php echo $mes; ?>"><?php echo DateExtenso($mes); ?></option>
          <?php } ?>
        </select>
        
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        
        <span id="spryselect3">
        <select name="ano">
          <option value="0" selected="selected">Year </option>
          <?php for($ano = 1900; $ano <= date("Y")-8; $ano++){ ?>
          <option value="<?php echo $ano; ?>"><?php echo $ano; ?></option>
          <?php } ?>
        </select>
        <span class="selectInvalidMsg">*</span>
        <span class="selectRequiredMsg">*</span>
        </span>
        </div>


			<div class="linha"><input type="submit" name="cadastrar" value="Register" class="botoes_1" /></div>

</div>

<?php } ?>
    
    </form>


<?php } } } else { ?>


<form action="" method="post" enctype="multipart/form-data" name="chave">

<?php if(isset($_POST['enviar'])){
	
$query = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [email] = '".$_POST[email]."'") or die (odbc_error());
if(odbc_num_rows($query) >= 1){ ?>
	
	<div class='error'>This email is already used by another user.</div>
	
<?php } else if(odbc_num_rows($query) == 0){
	
$chave = strtoupper(substr(sha1(date("d-M-Y H:M:S").time().$_POST['email']),0,100));
$gravaChave = odbc_exec($conexao, "INSERT INTO [ChaveDB].[dbo].[ChaveCad] ([email],[chave])
													                VALUES('".$_POST[email]."','".$chave."')") or die (odbc_error());
														 
	
	if($gravaChave){
		
		//LINK DE VALIDAÇÃO DO E-MAIL ENVIADO
		$urlacesso = $urlmanager.$paramento.'='.$chave;
		
		if(isset($_GET['invite'])){
			
			$keyInvite = $_GET['invite'];
			
			//VERIFICA SE A CHAVE DE CONVITE É VÁLIDA
			$verInvit = mysql_query("SELECT *FROM invite WHERE chave = '".$keyInvite."'");
			
			if(mysql_num_rows($verInvit) == 0){ ?>
			
            <div class="error">Your invitation does not exist or is invalid.</div>
            
<?php } else if(mysql_num_rows($verInvit) >= 1){ 
			
		include_once("sendChave_2.php");
		
		echo "<script language = 'JavaScript'>
				alert('Follow the instructions sent in the email informed.');
				window.location.href = 'login.php';
			  </script>";
			  
			}
			  

		} else {
			
		include_once("sendChave.php");
		
		echo "<script language = 'JavaScript'>
				alert('Follow the instructions sent in the email informed.');
				window.location.href = 'login.php';
			  </script>";
		}
		
	} else { 
	
		echo "<script language = 'JavaScript'>
				alert('There was an error generating your key, try again later.');
				window.location.href = 'login.php';
			  </script>";
	
	}

} 

}

?>

      <div class="titulo_guias">Terms of account creation</div>  


<div class="formCad">

<div class="linha">
  <textarea name="textarea" readonly="readonly" class="termos">
Terms of Agreement:
  
These rules are written in hopes that all gamers in the community will do their best to respect each other and show good sportsmanship for all of our competitive games. Let's promote a fun and friendly atmosphere for everyone to enjoy.

Naming

 Do not use character names to impersonate other players or GMs. Remember that GMs will never ask for your account information or personal information.

 Do not create character names that would insult other cultures, religions, race, gender, or groups.

Behavior

 Treat each other with the same amount of respect you expect for yourself to be treated. If that expectation of respect is low, you should still value others opinions, beliefs and values.

 Be kind to new players and offer assistance when appropriate. Random acts of kindness pay off in the future, especially if a GM is feeling generous that day!

 Threats or extortion will not be tolerated. If you are a victim to any such abuse, please send unaltered screenshots to customer support. Distasteful acts may result in game account suspension, or system wide suspension, lasting from one week, or as long as a lifetime.

Setting up Private Shops

 Please avoid setting up private shops on locations in any games where you may cause inconvenience to other players. Do not set up shop in front of NPCs causing other players to click on you or blocking functions in-game needed by others. Players doing this will either be moved or logged out of the game.

 Avoid using other languages other than English when giving a name to your private shop. If you are discovered or another player reports you for an inappropriate name, you may be subject to a account suspension.

Bugs and exploits

 If you know of a bug or exploit in the game, then please report it as soon as possible to customer support or GMs. Using bugs to your advantage, especially those that would give you a competitive advantage over others will result in immediate account bans.

Bots and hacking

 The use of any programs for bots, hacks or cheating is prohibited. Do not use any such programs that break the rules set by the game for your advantage or even for testing. Report programs you find right away to customer support. Do not ever try to download them yourself as you may also expose your own computer to Internet attacks.

Game Items

 GMs will not help players to hold their items for any reason including transferring items from one account to another. Transfer items with other players at your own risk. GMs and customer support will not restore items mistakenly traded to others.

</textarea>
</div>
    <?php if(isset($_GET['invite'])){ 
		$keyInvite = $_GET['invite'];
		$verInvit  = mysql_query("SELECT *FROM invite WHERE chave = '".$keyInvite."'");
		$contInvit = mysql_num_rows($verInvit);
		$resInvit  = mysql_fetch_array($verInvit);
		
		if($contInvit == 0 or $resInvit['status'] == 1){ ?>
		<div class="error">This invitation does not exist or has already been accepted.</div>	
	<?php } else if(mysql_num_rows($verInvit) >= 1){  ?>
    <div class="linha">
    
    <span id="SprayEmail">
    <input name="email" type="text" class="campos_1" value="<?php echo $resInvit['email']; ?>" readonly="readonly" />
    <span class="textfieldRequiredMsg">*</span> 
    <span class="textfieldMaxCharsMsg">*</span>
    <span class="textfieldInvalidFormatMsg">Email invalid.</span>
    </span>
    
    </div>
<?php } } else { ?>
    <div class="linha">
    
    <span id="SprayEmail">
    <input name="email" type="text" class="campos_1" />
    <span class="textfieldRequiredMsg">*</span> 
    <span class="textfieldMaxCharsMsg">*</span>
    <span class="textfieldInvalidFormatMsg">Email invalid.</span>
    </span>
    
    </div>
<?php } ?>    
  <div class="linha">
    <input name="enviar" type="submit" value="Generate key" class="botoes_1" />
  </div>
  
  
  
</div>

</form>



<?php } ?>


<a href="http://www.websystens.com" target="_blank" title="Power by Web systens®"><div class="rodape"></div></a>

<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("SprayEmail", "email", {validateOn:["blur"], hint:"Enter your e-mail", maxChars:50});
var sprytextfield2 = new Spry.Widget.ValidationTextField("loginSpray", "none", {validateOn:["blur"], hint:"Login"});
var sprytextfield3 = new Spry.Widget.ValidationTextField("nomeSpray", "none", {validateOn:["blur"], hint:"First name"});
var sprytextfield4 = new Spry.Widget.ValidationTextField("sprytextfield4", "none", {validateOn:["blur"], hint:"Last name"});
var sprypassword1 = new Spry.Widget.ValidationPassword("senhaSpray_1", {validateOn:["blur"]});
var spryconfirm1 = new Spry.Widget.ValidationConfirm("senhaSpray_2", "senha", {validateOn:["blur"]});
var spryselect1 = new Spry.Widget.ValidationSelect("spryselect1", {invalidValue:"0", validateOn:["blur"]});
var spryselect2 = new Spry.Widget.ValidationSelect("spryselect2", {invalidValue:"0", validateOn:["blur"]});
var spryselect3 = new Spry.Widget.ValidationSelect("spryselect3", {invalidValue:"0", validateOn:["blur"]});
</script>

</body>
</html>