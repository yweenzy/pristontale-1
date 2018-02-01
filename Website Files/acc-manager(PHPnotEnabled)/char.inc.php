<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationSelect.css" rel="stylesheet" type="text/css" />
<title>Criar char</title>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationSelect.js" type="text/javascript"></script>
</head>

<body>
<?php function RandomPass($numchar){
	   $letras = "A,B,C,D,E,F,G,H,I,J,K,1,2,3,4,5,6,7,8,9,0";
	   $array = explode(",", $letras);
	   shuffle($array);
	   $senha = implode($array, "");
	   return substr($senha, 0, $numchar);
	}
	$pgid = RandomPass(5);
	

            $qCharID = ($_SESSION["charID"]) ? $_SESSION["charID"] : $_SESSION["ID"];

//------------------------------------------------------------ CREATE CHARACTER
            if(isset($_POST['criar'])){
				
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
               
					} else {
						
                    if(filesize($charInfo) == 240){
						
						//RECEBENDO NICK DO PERSONAGEM FILTRADO SEM ESPAÇOS E CARACTERES ESPECIAIS
						$newName = trim($func->char_filter(trim($_POST["newchar"])),"\x00");
						
                        //Limpando Caracteres de acentos
                        function strace($a){
							
                        $a = eregi_replace("[àáâäã]","a",$a);
                        $a = eregi_replace("[èéêë]","e",$a);
                        $a = eregi_replace("[ìíîï]","i",$a);
                        $a = eregi_replace("[òóôöõ]","o",$a);
                        $a = eregi_replace("[ùúûü]","u",$a);
                        $a = eregi_replace("[ÀÁÂÄÃ]","A",$a);
                        $a = eregi_replace("[ÈÉÊË]","E",$a);
                        $a = eregi_replace("[ÌÍÎÏ]","I",$a);
                        $a = eregi_replace("[ÒÓÔÖÕ]","O",$a);
                        $a = eregi_replace("[ÙÚÛÜ]","U",$a);
                        $a = eregi_replace("ç","c",$a);
                        $a = eregi_replace("Ç","C",$a);
                        $a = eregi_replace("ñ","n",$a);
                        $a = eregi_replace("Ñ","N",$a);
                        $a = str_replace("´","",$a);
                        $a = str_replace("`","",$a);
                        $a = str_replace("¨","",$a);
                        $a = str_replace("^","",$a);
                        $a = str_replace("~","",$a);
		        		$a = str_replace(";","",$a);
						$a = str_replace(".","",$a);
                        $a = str_replace("!","",$a);
						$a = str_replace("?","",$a);
                        
						return $a;
                        
						}
						
                        $newName = strace($newName);
						
									if(empty($_POST['class'])){
										
                        echo '<script type="text/javascript">
								alert("Choose a character class.");
							  </script>';
										
									} else if(!$func->is_valid_string($newName)){

                            $charDat = $dirUserData.($func->numDir($newName))."/".$newName.".dat";

                            if(!file_exists($charDat)){
								
                                copy("create/char.dat",$dirUserData.($func->numDir($newName))."/".$newName.".dat");

                                $fRead = false;
                                $fOpen = fopen($charInfo, "r");
                                $fRead = fread($fOpen,filesize($charInfo));
                                @fclose($fOpen);

                                // list char information
                                   $charNameArr = array("48" => trim(substr($fRead,0x30,15),"\x00"),
														"80" => trim(substr($fRead,0x50,15),"\x00"),
														"112" => trim(substr($fRead,0x70,15),"\x00"),
														"144" => trim(substr($fRead,0x90,15),"\x00"),
														"176" => trim(substr($fRead,0xb0,15),"\x00"));

                                $chkEmpArr = array();
                                $chkChar = array();
                                foreach($charNameArr as $key => $value){

                                    if(empty($value)){ $chkEmpArr[] = $key; } else { $chkChar[] = $key; }

										                                }

                                if(count($chkChar) < 5){

                                    //ACHANDO O PONTO ONDE IRÁ INICIAR A ESCRITURA DO NICK
                                    $startPoint = $chkEmpArr[0];
                                    $endPoint = $startPoint + 15;

                                     //GRAVANDO NICK NO ARQUIVO DE INFORMAÇÃO
                                    $fRead = false;
                                    $fOpen = fopen($charInfo, "r");
                                    while(!feof($fOpen)){
                                    @$fRead = "$fRead".fread($fOpen, filesize($charInfo));
                                    }
                                    fclose($fOpen);

                                    //PREENCHE COM 00 À ESQUERDA
                                    $addOnLeft = false;
                                    $leftLen = 15 - strlen($newName);
                                    for($i = 0; $i < $leftLen; $i++){
                                        
										$addOnLeft.=pack("h*",00);
                                    
									}
                                    
									$writeName = $newName.$addOnLeft;


                                    $sourceStr = substr($fRead, 0, $startPoint).$writeName.substr($fRead, $endPoint);
                                    $fOpen = fopen($charInfo, "wb"); 
                                    fwrite($fOpen, $sourceStr, strlen($sourceStr));
                                    fclose($fOpen);

                                    //GRAVANDO NO ARQUIVO .DAT
                                    $fRead = false;
                                    $fOpen = fopen($charDat, "r");
                                    while(!feof($fOpen)){
                                    @$fRead = "$fRead".fread($fOpen, filesize($charDat));
                                    }
                                    fclose($fOpen);

                                    $bin = $func->char2Num($_POST["class"]);
                                    $bina = pack("h*",$bin);
						
                                    //SELECIONANDO CLASSE DO PERSONAGEM E ESCREVENDO NO ARQUIVO .DAT
                                    $sourceStr = substr($fRead, 0, 16).$writeName.substr($fRead, 31, 17).($func->charResetHair($_POST['class'], 1)).substr($fRead, 69, 43).($func->charResetHair($_POST['class'], 2)).substr($fRead, 136, 60).$bina.substr($fRead, 197, 7).($func->charResetState($_POST['class'])).substr($fRead, 224, 284).($func->charResetSkill()).substr($fRead, 524, 0).($func->charResetMastery()).substr($fRead, 556, 148).$writeAccName.substr($fRead, 714);
                                    $fOpen = fopen($charDat, "wb"); 
                                    fwrite($fOpen, $sourceStr, strlen($sourceStr));
                                    fclose($fOpen);


	$gravaLog = mysql_query("INSERT INTO logs (userID, charName, classe, level, datahora, operacao)
									   VALUES ('".$_SESSION['ID']."',
									   		   '".$_POST['newchar']."',
									   		   '".$_POST['class']."',
											   '".$levelstart."',
											   '".date('Y-m-d H:i:s')."',
											   'Char criado')");
											   
  
  
  //AO CRIAR O CHAR ELE MUDA OS STATUS E INSERE A ID DO PLAYER QUE ACEITOU O CONVITE
  $verInvite = mysql_query("SELECT *FROM invite WHERE idProvisoria = '".$_SESSION[ID]."'");
  if(mysql_num_rows($verInvite) >= 1){ 
  	 mysql_query("UPDATE invite SET status = '1', 
	  						   idConvidada = '".$_SESSION[ID]."'
					    WHERE idProvisoria = '".$_SESSION[ID]."'");
  }
  
  

                        echo '<script type="text/javascript">
								alert("His character was created successfully.");
							  </script>';
									
                                } else {
                                   
                        echo '<script type="text/javascript">
								alert("His character limit for this account has been reached.");
							  </script>';
                               
							    }
								
                            } else {
								
                        echo '<script type="text/javascript">
								alert("This character exists.");
							  </script>';

                           }

                        } else {
							
                        echo '<script type="text/javascript">
								alert("Choose your character name.");
							  </script>';
                       
					    }


                    } else {
						
                        echo '<script type="text/javascript">
								alert("Your information file is corrupted. Notify the administrator.");
							  </script>';
                    
					}

             }   
			 
			 
                        echo '<script type="text/javascript">
								window.location.href = "login.php";
							  </script>';
					
					
					
            } 
?>

            <form method="post" action="" name="criarChar" enctype="multipart/form-data" >
            
                <div class="linha_2">
                <input type="submit" value="Create" name="criar" class="botoes_4">
                <span id="sprayChar">
                <input name="newchar" type="text" class="campos_2" size="25" maxlength="15" />
                <span class="textfieldRequiredMsg">*</span>
                </span><span id="spryselect1">
                <select name="class">
                  <option value="" selected="selected">Class</option>
                  <option value="Fighter">Fighter</option>
                  <option value="Mechanician">Mechanician</option>
                  <option value="Archer">Archer</option>
                  <option value="Pikeman">Pikeman</option>
                  <option value="Atalanta">Atalanta</option>
                  <option value="Knight">Knight</option>
                  <option value="Magician">Magician</option>
                  <option value="Priestess">Priestess</option>
                </select>
                <span class="selectInvalidMsg">*</span>
                <span class="selectRequiredMsg">*</span>
                </span>
                </div>
  

            </form>
<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprayChar", "none", {validateOn:["blur"], hint:"character name"});
var spryselect1 = new Spry.Widget.ValidationSelect("spryselect1", {invalidValue:" ", validateOn:["blur"]});
</script>
</body>
</html>