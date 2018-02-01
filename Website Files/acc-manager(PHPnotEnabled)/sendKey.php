<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="themes/reloadedpt/css/reloaded.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link rel="stylesheet" type="text/css" href="css/qTip.css"/>

<title>Key code</title>
</head>
<body>
<?php if(isset($_GET['close'])){ ?>

<br />
<br />
<br />
<br />
<br />


<div class="sucess">Key sent, close this window and check your email.</div>

<?php } else if(isset($_GET['ws'])){

require_once("smtp/class.phpmailer.php");
include_once("mysql.php");
include_once("sql.php");


//LINK DE VALIDAÇÃO DO E-MAIL ENVIADO
$chave = strtoupper(substr(sha1(date("d-M-Y H:M:S").time().$_GET["ws"]), 0, 20));
$query = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '".$_GET[ws]."'");
$ret = odbc_fetch_array($query);

//DELETA AS CHAVES GERADAS ANTES DE CRIAR A NOVA.
$cleanChave = odbc_exec($conexao, "DELETE FROM [ChaveDB].[dbo].[ChaveAccount] WHERE email = '".$ret[Email]."'
																				AND userid = '".$ret[Userid]."'");

$gravaChave = odbc_exec($conexao, "INSERT INTO [ChaveDB].[dbo].[ChaveAccount] ([email],[chave],[userid])
													                VALUES('".$ret[Email]."',
																		   '".$chave."',
																		   '".$_GET[ws]."')");
																		   
		if($gravaChave){						   												   

		echo '<meta HTTP-EQUIV="Refresh" CONTENT="5;URL=sendKey.php?close">'; 
 ?>	       
 
		<div class="loading"></div>
		<div class="sucess">Sending Key...</div>

<?php																					   
$mail = new PHPMailer();
$mail->SetLanguage("br", "smtp/"); //Idioma
$mail->IsSMTP();

$mail->SMTPAuth = true;
$mail->Host = "mail.reloadedpt.net"; //Host do servidor SMTP
$mail->Port = "25";
$mail->Username = "no-reply@reloadedpt.net"; //Nome do usuario SMTP
$mail->Password = "Jona240993";     //Senha do usuario SMTP
$mail->From = "no-reply@reloadedpt.net"; //Email de quem envia
$mail->FromName = utf8_decode($ServerName);    //nome de quem ta enviando, vai aparecer na coluna "De:"

//INICIO --- Quem vai receber-----------------------------------------------
$mail->AddAddress($ret["Email"]);
//FIM --- Quem vai receber--------------------------------------------------

$mail->AddReplyTo("no-reply@reloadedpt.net"); //Quem irá receber a resposta (quando a pessoal responder)
$mail->IsHTML(true);

//Assunto
$mail->Subject = utf8_decode("Key code ".$ServerName."");
//Corpo da mensagem, pode usar tags html
$mail->Body = utf8_decode(
'<style type="text/css">

table
{
	font-family:Arial;
	font-size:14px;
}
a:link {
	color: #630;
	text-decoration: none;
}
a:visited {
	text-decoration: none;
	color: #630;
}
a:hover {
	text-decoration: none;
	color: #930;
}
a:active {
	text-decoration: none;
	color: #930;
}

</style>

<table width="615" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td><img src="'.$site.'/themes/reloadedpt/img/msg/bgMSG_r1_c1.png" width="615" height="107" /></td>
  </tr>
  <tr>
    <td height="250" align="center" valign="top"><table width="615" border="0" align="center" cellpadding="2" cellspacing="3">
      <tr>
        <td height="39" colspan="3">&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><strong>Your email:</strong> '.$ret[Email].'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
        <td width="441">Hello '.$ret[CUserName1].',<br />
          you&acute;re getting the key to change the data in your account
		  type the following key into my account on account 
		  administrator to validate your changes.
		  <br />
		  <br />
          <strong>Key: </strong>'.$chave.'
		  </td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>Sent: '.date("Y/m/d H:m:s").'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
</table>
');

if(!$mail->Send()){  echo $mail->ErrorInfo; 

exit; 

} //FIM E-MAIL

		} else if(!$gravaChave){ ?>
			
		<div class="error">There was an error, please notify the administrator.</div>
			
	<?php } } else { ?>
	
		<div class="error">There was an error, please notify the administrator.</div>
		
<?php } ?>

</body>
</html>