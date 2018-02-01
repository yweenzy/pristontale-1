<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Documento sem título</title>

</head>
<?php include("mysql.php"); ?>
<body>
<style type="text/css">

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
    <td height="250" align="center" valign="top">
    <table width="615" border="0" align="center" cellpadding="2" cellspacing="3">
      <tr>
        <td height="39" colspan="3">&nbsp;</td>
        </tr>
      <tr>
        <td>&nbsp;</td>
        <td><strong>Seu e-mail:</strong> '.$_POST['emailrec'].'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
        <td width="441">
		Hello,
		Are you getting your key for account recovery.
		To continue recovering your data click the button below.
		If not that you asked this email, please disregard.
		</td>
      <tr>
        <td>&nbsp;</td>
        <td>
		<a href="'.$urlrec.'">
		<img src="'.$site.'/themes/reloadedpt/img/msg/autenticar.png" width="157" height="43" border="0" />
		</a>
		</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>Enviado em: '.date("d/m/Y H:m:s").'</td>
        <td>&nbsp;</td>
      </tr>
        <td width="87">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
</table>

<br />
<br />

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
        <td><strong>Seu e-mail:</strong> '.$_POST['email'].'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
        <td width="441">Hello,<br />
          Are you getting your verification key legitimate email.
          To continue your registration click the button below.
          If not that you asked this email, please disregard.
          </td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><a href="'.$urlacesso.'"> <img src="'.$site.'/themes/reloadedpt/img/msg/autenticar.png" width="157" height="43" border="0" /> </a></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>Enviado em: '.date("d/m/Y H:m:s").'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
</table>

<br />
<br />

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
        <td><strong>Hello '.$nome.'</strong></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
        <td width="441">
		You have successfully logged in Register '.$ServerName.'. <br />
		Your data access are: <br />
<br />
<strong>User: </strong>'.$login.' <br />
<strong>Password: </strong>'.$senha.' <br />
<br />
<br />
<br />
The team '.$ServerName.'  wishes you a good UP. </td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td><a href="'.$urllogin.'"> <img src="'.$site.'/themes/reloadedpt/img/msg/logar.png" width="157" height="43" border="0" /> </a></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>Sent: '.date("d/m/Y H:m:s").'</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td width="87">&nbsp;</td>
      </tr>
    </table></td>
  </tr>
</table>


</body>
</html>