<?php //FUNÇÃO QUE CONVERTE OS VALORES DA DATA DE FORMATO INGLES PARA PORTUGUES E VICE-VERSA

	function ConvertDateEUA($data){
		
		//$data = "2011/11/01";
		
		$dataEUAy = substr($data, 0,4);
		$dataEUAm = substr($data, 4,4);
		$dataEUAd = substr($data, 8,2);
		
		//echo $dataEUAy;
		//echo $dataEUAm;
		//echo $dataEUAd;
		
		$data = $dataEUAd.$dataEUAm.$dataEUAy;
		
		return $data;
	}

	function ConvertDateBR($data){

		//$data = "01/11/2011";

	$dataBRd = substr($data, 0,2);
	$dataBRm = substr($data, 2,4);
	$dataBRy = substr($data, 6,4);
	
		$data = $dataBRy.$dataBRm.$dataBRd;
		
		return $data;	
		
	}

//FUNÇÃO QUE CONVERTE DATA NUMERICA EM DATA ALPHA

	function DateExtenso($mes){
		
	       if($mes == 1){ $mes =  "January";
	
	} else if($mes == 2){ $mes = "February";	
		
	} else if($mes == 3){ $mes = "March";	
		
	} else if($mes == 4){ $mes = "April";	
		
	} else if($mes == 5){ $mes = "May";	
		
	} else if($mes == 6){ $mes = "June";	
		
	} else if($mes == 7){ $mes = "July";	
		
	} else if($mes == 8){ $mes = "August";	
		
	} else if($mes == 9){ $mes = "September";	
		
	} else if($mes == 10){ $mes = "October";	
		
	} else if($mes == 11){ $mes = "November";	
		
	} else if($mes == 12){ $mes = "December";	
		
	}
	
	return $mes;		
		
	}
	
	
	//FUNÇÃO ARMAZENA O NUMERO DAS CLASSE DENTRO DE UMA VARIAVEL

	function montClasse($post){
	
		$lut = $post[0].","; 
		$mec = $post[1].","; 
		$arq = $post[2].","; 
		$pik = $post[3].","; 
		$ata = $post[4].","; 
		$cav = $post[5].","; 
		$sac = $post[6].","; 
		$mag = $post[7].","; 
		
		$post = $lut.$mec.$arq.$pik.$ata.$cav.$mag;	

		$post = str_replace(",", " ", $post);
		
		return $post;
	}
	
	//FUNÇÃO QUE RETORNA O NOME DA CLASSE DE ACORDO COM O NUMERO PEGO NO ARRAY
	
	function classes($array){

	     if($array == 0){ $array = "No spec"; }
	else if($array == 1){ $array = "Fighter"; }
    else if($array == 2){ $array = "Mechanician"; }
    else if($array == 3){ $array = "Archer"; }
	else if($array == 4){ $array = "Pikeman"; }
	else if($array == 5){ $array = "Atalanta"; }
	else if($array == 6){ $array = "Knight"; }
	else if($array == 7){ $array = "Magician"; }
	else if($array == 8){ $array = "Priestess"; }
		
		return $array;
	}
	
	

	//FUNÇÃO QUE RETORNA O NOME DA CLASSE DE ACORDO COM O NUMERO PEGO NO ARRAY DA CONSULTA NO BD
	
	function substClasse($array){
		
		 $clas = array(0,1,2,3,4,5,6,7,8);
		
	  	 if($clas[0] == substr($array, 0, 1)){ $array = 0; }
    else if($clas[1] == substr($array, 1, 2)){ $array = 1; }
    else if($clas[2] == substr($array, 2, 3)){ $array = 2; }
	else if($clas[3] == substr($array, 3, 4)){ $array = 3; }
	else if($clas[4] == substr($array, 4, 5)){ $array = 4; }
	else if($clas[5] == substr($array, 5, 6)){ $array = 5; }
	else if($clas[6] == substr($array, 6, 7)){ $array = 6; }
	else if($clas[7] == substr($array, 7, 8)){ $array = 7; }
	else if($clas[8] == substr($array, 8, 9)){ $array = 8; }
		
		return $array;
	}
	
	
	
	//FUNÇÃO QUE CONVERTE O . DA MOEDA PARA , 

      function moeda($get_valor) {  
              $source = array('.', ',');  
              $replace = array('', '.');  
              $valor = str_replace($source, $replace, $get_valor); 

       return $valor;
	  }
	  
	  
	  //FUNÇÃO QUE MULTIPLICA O VALOR DA QTD E RETORNA O RESULTADO.
	  
	  function multi($qtd, $preco){
		  
		  $resultado = $qtd*$preco;
		  
		  //TRATANDO O RESULTADO APOS A VIRGULA
		  $resultado = explode(".", $resultado);
		  
		  $decimal_10 = $resultado[0];
		  $decimal_2  = $resultado[1];
		  
		  if(strlen($decimal_2) == 1){ $resultado = $decimal_10.".".$decimal_2."0"; }
	 else if(strlen($decimal_2) == 2){ $resultado = $decimal_10.".".$decimal_2; }
	 else if(strlen($decimal_2) == 0){ $resultado = $decimal_10.".00"; }
		  
		  return $resultado;
	  }
	  
	  //FUNÇÃO QUE VERIFICA O CREDITO DO CLIENTE E RETORNA A COMPRA OU SEM CREDITO
	  function credit($credito, $preco){
		  
				if($preco > $credito){ $retorno = 0; }
		   else if($preco <= $credito){ $retorno = $preco; }
		  
		  return $retorno;
	  }
	  
	  //FUNÇÃO QUE DEFINE O NIVEL DO USUARIO
	  function nivel($nivel){
		  
		if($nivel == 1){ $nivel = "Administrador"; }
   else if($nivel == 2){ $nivel = "Moderador"; }
 		
		return $nivel;
	  }



	  function formatMoeda($valor){
		  
		  
		  //TRATANDO O RESULTADO APOS A VIRGULA
		  $resultado = explode(".", $valor);
		  
		  $decimal_10 = $resultado[0];
		  $decimal_2  = $resultado[1];
		  
		  if(strlen($decimal_2) == 1){ $resultado = $decimal_10.".".$decimal_2."0"; }
	 else if(strlen($decimal_2) == 2){ $resultado = $decimal_10.".".$decimal_2; }
	 else if(strlen($decimal_2) == 0){ $resultado = $decimal_10.".00"; }
		  
		  return $resultado;
	  }


	//FUNÇÃO QUE REMOVE CRÉDITOS DE UMA CONTA E INSERE NA OUTRA SOMA E SUBTRAI
	function transferCred($id_1, $id_2, $credito){
		
		include("mysql.php");
		$conta_1 = mysql_query("SELECT *FROM cash WHERE userC = '$id_2'");
		$acc_1 = mysql_fetch_array($conta_1);
		
		$removeCred = $acc_1['creditoC'] - $credito;
		
		$up_1 = mysql_query("UPDATE cash SET creditoC = '$removeCred' WHERE userC = '$id_2'");
		if($up_1){
			
			$conta_2 = mysql_query("SELECT *FROM cash WHERE userC = '$id_1'");
			$acc_2 = mysql_fetch_array($conta_2);
			
			$addCred = $acc_2['creditoC'] + $credito;
			
			$up_2 = mysql_query("UPDATE cash SET creditoC = '$addCred' WHERE userC = '$id_1'"); 
			
        echo '<div class="sucess">Credits transferred successfully.</div>';
			
		} else {
		
        echo '<div class="error">Failed to transfer the credits.</div>';
			
		}

		
	}


	function itemExibe($item){
		
		include("mysql.php");
		
			$listIte = mysql_query("SELECT *FROM item WHERE codIt = '$item'");
			$volta = mysql_fetch_array($listIte);
			if(mysql_num_rows($listIte) == 0){ $var = $item;
			} else if(mysql_num_rows($listIte) >= 1){ $var = $volta['nomeIt']; } 
		
		return $var;
		
	}


 ##DETERMINA SE O USUARIO TEM CLAN OU NÃO E RETORNA COM OU SEM BOTÃO DE ACESSO##

	function HabilitaClan($sessao){
		
	//CONECTA NO BANCO DE DADOS E VERIFICA SE O CARA EXISTE EM ALGUM CLAN	
	include("sql.php");
	$queryQT = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL]  WHERE ChName = '".$_SESSION[charName]."'");
	$qtlider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[UL]  WHERE ChName = '".$_SESSION[charName]."'");
	$contador = odbc_num_rows($qtlider);

		if($contador == 1){ $sessao = '<a href="?sess=clan" ><img src="themes/reloadedpt/img/btn_group_2_r1_c14.png" width="124" height="43" border="0"/></a>'; }
   else if($contador == 0){ $sessao = '<a href="javascript:;" ><img src="themes/reloadedpt/img/no_clan.png" width="124" height="43" border="0"/></a>'; }
	
	return $sessao;	
	
	}
	
	
	//FUNÇÃO QUE TRATA O STATUS DO CONVITE
	function statsInv($var, $var_1, $var_2){
		
		include("mysql.php");
		$verif = mysql_query("SELECT *FROM charCash WHERE charC = '".$var_1."' AND userChar = '".$var_2."'");
		if(mysql_num_rows($verif) >= 1){
		
		$var = "Credit received";
		
		} else {
		
		if($var == 0){ $var = "Waiting for confirmation"; }
   else if($var == 1){ $var = "Invitation accepted"; }
		
		}
		
		return $var;
	}

function emptyVar($var, $var2){
	
	if(empty($var) or $var == "Other Subjects"){ $var = $var2; 
            } else { $var = $var; }

	return $var;	
}

function emptyCat($var){
	
	if(empty($var)){ $var = "Não selecionado"; 
            } else { $var = $var; }

	return $var;	
}

function emptyChar($var){
	
	if(empty($var)){ $var = "Not selected";
            } else { $var = $var; }

	return $var;	
}

function emptyData($var){
	
	if(empty($var)){ $var = "00/00/0000";
            } else { $var = $var; }

	return $var;	
}
	
?>