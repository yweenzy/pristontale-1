<?php
	$lang = $_SERVER['QUERY_STRING'];
	if (($lang == "de") || ($lang == "en") || ($lang == "es") || ($lang == "fr") || ($lang == "jp") || ($lang == "nl") || ($lang == "no") || ($lang == "pl") || ($lang == "pt") || ($lang == "pt_br") || ($lang == "sl") || ($lang == "zh")) {
		$fp = fopen("lang.tmp", "w");
		fwrite($fp, basename($_SERVER['QUERY_STRING']));
		fclose($fp);
		header("Location: index.php");
	}
?>
