<?php

//FUNÇÃO QUE ADICIONA OS BONUS DE QUANDO O CHAR CHEGA AO LEVEL 110
function bonusCash($sessionID, $Idinvited, $Nick, $Level){
	
	include("mysql.php");
	$valorBonus = 1000.00;
	
	$convite = mysql_query("SELECT *FROM invite WHERE id = '".$sessionID."'");
	if(mysql_num_rows($convite) >= 1){
	
		while($credita = mysql_fetch_array($convite)){
			
			if(!empty($credita['idProvisoria']) and $credita['idConvidada'] != '0'){
				
			$condicao = mysql_query("SELECT *FROM charCash WHERE userChar = '".$Idinvited."'");
			$verBonus = mysql_query("SELECT *FROM bonusCash WHERE userCB = '".$sessionID."'");
			
			//SE NÃO ECONTRAR A ID E O CHAR VERIFICA SE O USER JA TEM UMA ID DE CREDITO
			if(mysql_num_rows($condicao) == 0){
				
				$charinc = mysql_query("INSERT INTO charCash (userChar, charC, levelC)
													  VALUES ('".$Idinvited."', '".$Nick."', '".$Level."')");
													  
				if(mysql_num_rows($verBonus) == 0){
							
			   $bonus = mysql_query("INSERT INTO bonusCash (userCB, statusCB, creditoCB)
													VALUES ('".$sessionID."',
															'1',
															'".$valorBonus."')");	
															
	     } else if(mysql_num_rows($verBonus) == 1){
			 
			 $CREDITO_ATUAL = mysql_fetch_array($verBonus);
			 $somar = $CREDITO_ATUAL['creditoCB'];
			 
			 $INSERT_CREDITO = $somar+$valorBonus;
			 
			 $upbonus = mysql_query("UPDATE bonusCash SET creditoCB = '".$INSERT_CREDITO."' 
			 									    WHERE userCB = '".$sessionID."'");			 
			 
					 }

				}
				
			}
			
		}
		
	}
	
	
	return $Bonus;
}




	$verInvit = mysql_query("SELECT *FROM invite WHERE id = '".$_SESSION[ID]."'");
	if(mysql_num_rows($verInvit) >= 1){
	while($resInv   = mysql_fetch_array($verInvit)){
		
	$qCharID1 = $resInv['idConvidada']; 
      //PEGANDO O CHAR CONVIDADO
            $charInfo1 = $dirUserInfo.($func->numDir($qCharID1))."/".$qCharID1.".dat";
							        
			    if(file_exists($charInfo1) && (filesize($charInfo1) == 240)){
                $fRead = false;
                $fOpen = fopen($charInfo1, "r");
                $fRead = fread($fOpen,filesize($charInfo1));
                @fclose($fOpen);

               //LISTANDO INFORMAÇÕES DOS PERSONAGENS LENDO .DAT
               $charNameArr1 = array("48" => trim(substr($fRead,0x30,15),"\x00"),
									"80" => trim(substr($fRead,0x50,15),"\x00"),
									"112" => trim(substr($fRead,0x70,15),"\x00"),
									"144" => trim(substr($fRead,0x90,15),"\x00"),
									"176" => trim(substr($fRead,0xb0,15),"\x00"));
									
                if(count($charNameArr1) > 0){
					
                    foreach($charNameArr1 as $key => $value){
						
						//DETALHES
                        $expValue = explode("\x00", $value);

						 if($expValue[0] != ""){ 
		
						//CRIAR CONDIÇÃO AQUI
						$charDat1 = $dirUserData.($func->numDir($expValue[0]))."/".$expValue[0].".dat";
						$fOpen = fopen($charDat1, "r");
						$fRead = fread($fOpen,filesize($charDat1));
						@fclose($fOpen);
						
						//DETALHES DO CHAR
						$charLevel = substr($fRead,0xc8,1);
						$charClass = substr($fRead,0xc4,1);
						$charName = trim(substr($fRead,0x10,15),"\x00");
						$charID = trim(substr($fRead,0x2c0,10),"\x00");
                        
						if(ord($charLevel) >= 110){
							
						echo bonusCash($_SESSION['ID'], $qCharID1, $expValue[0], ord($charLevel)); 
    
	 					}
					} 
				} 
			}
		} 
	}
}?>