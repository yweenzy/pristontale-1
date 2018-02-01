<style type="text/css">
#manu{ font-size:30px;
color:#FFF;
}
</style>
<?php

$servidor = "websystens.com:3306";
$usuario  = "lojapris_rpt";
$passW    = "ws963852741";
$bd  	  = "lojapris_reloaded";


$conexaoMysql = mysql_connect($servidor, $usuario, $passW) or die ("<div id='manu'>Maintenance</div>");
		        mysql_select_db($bd, $conexaoMysql) or die ("Erro ao acessar o banco de dados");

	
	//CONFIGURAÇÕES BD.
	$sigla = "RPT";
	$pasta = "http://upload.lojapriston.com/reloadedpt/";
	$pasta_loja = "http://upload.lojapriston.com/reloadedpt/";
	$logo = "http://management.reloadedpt.net/manager/img/logo_info.png";
	$site = "http://management.reloadedpt.net/manager";
		   
?>
