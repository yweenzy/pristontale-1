<?php if(XPT != 1) exit;

//PROCESSO DE CRIAÇÃO DO ARQUIVO .DAT INICIAL

                // PREENCHE COM 00 À ESQUERDA
                $leftLen = 10 -strlen($qCharID);
                for($i = 0; $i < $leftLen; $i++){
					
                    $addOnLeft.=pack("h*",00);
                
				}
				
                $writeAccName = $qCharID.$addOnLeft;
				
				//RECEBENDO NOME E ENDEREÇO DO ARQUIVO .DAT
                $charInfo = $dirUserInfo.($func->numDir($qCharID))."/".$qCharID.".dat";

                if(!file_exists($charInfo)){
					
                    copy("create/info.dat",$dirUserInfo.($func->numDir($qCharID))."/".$qCharID. ".dat");

                    $fRead = false;
                    $fOpen = fopen($charInfo, "r");
                    while(!feof($fOpen)){
                    @$fRead = "$fRead".fread($fOpen, filesize($charInfo));
                    }
                    
					fclose($fOpen);

                    //CRIANDO .DAT COM O NOME DA ID DA CONTA
                    $sourceStr = substr($fRead, 0, 16).$writeAccName.substr($fRead, 26);
                    $fOpen = fopen($charInfo, "wb"); 
                    fwrite($fOpen, $sourceStr, strlen($sourceStr));
                    fclose($fOpen);

					echo '<meta HTTP-EQUIV="Refresh" CONTENT="0;URL=login.php">';

				}




?>