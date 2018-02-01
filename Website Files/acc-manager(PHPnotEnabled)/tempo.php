<?php session_start();

 if(!$_SESSION["TEMPO_FIM"]){ $_SESSION["TEMPO_FIM"] = mktime(date('H:i:s')); }

$agora = mktime(date('H:i:s'));

// subtraimos o tempo em que o usuário entrou, do tempo atual "a diferença é em segundos"
$segundos = (is_numeric($_SESSION['TEMPO_FIM']) and is_numeric($agora)) ? ($agora-$_SESSION['TEMPO_FIM']):false;

//definimos os segundos que o usuário deverá ficar logado
define('TEMPO_FIM',1200);

if($segundos > TEMPO_FIM){

	echo "<script language = 'JavaScript'>
			alert('The time this session is over, log in again.');
			window.location.href = 'login.php?sess=logout'
		 </script>";

} else {
	
	
	$TempoLogado = str_replace(".", " ", substr($segundos/60, 0, 2)-20)." Min";
	echo str_replace("-", " ", $TempoLogado);
	
}
?>