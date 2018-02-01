<?php session_start();
						
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


?>