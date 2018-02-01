<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link rel="stylesheet" type="text/css" href="css/qTip.css">
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<script type="text/javascript" src="js/moeda.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script type="text/javascript">
$(document).ready(function(){
	   $(".itemQtd").keyup(function(){
                var $this = $( this );
				var $preco = $this.parents('.loja').find('.preco');
                $custo = $this.parents('.loja').find('.custo');

                $custo.html('<img src="img/loading.gif"/>');
                $.post("valor.php", {itemQtd: $this.val(), preco: $preco.val()
				}, function(valor){
                        $custo.html(valor);
                        });
        });
});
</script>


<title>Loja Priston - Reloaded Priston Tale</title>


</head>

<body>

<div id="Conteudo">
<?php
//VERIFICA OS CREDITOS NO BANCO DE DADOS
$consult = mysql_query("SELECT *FROM cash WHERE userC = '".$_SESSION[ID]."' AND codC = '".$_SESSION[COD]."'");
$cred = mysql_fetch_array($consult);

 if(isset($_POST['buy'])){ 
			
 					include("injection.php");
					
					//VERIFICA INJEÇÃO DE SCRIPT
					if(anti_sql($_POST['idIt'] != 0)
					or anti_sql($_POST['codIt'] != 0)
					or anti_sql($_POST['charName'] != 0)
					or anti_sql($_POST['spec'] != 0)
					or anti_sql($_POST['qtdIt'] != 0)
					or anti_sql($_POST['precoIt'] != 0)
					or anti_sql($msg != 0)){
										
										
					echo '<meta HTTP-EQUIV="Refresh" CONTENT="0;URL=login.php?sess=logout">';
					//CRIAR INCLUDE DE BAN CONSTATANDO INJECT
					}  else if(isset($_POST['precoIt'])){
						
					$consultPrecoPro = mysql_query("SELECT *FROM item WHERE idIt = '".$_POST[idIt]."'");
					$retorN = mysql_fetch_array($consultPrecoPro);
					
             if($retorN['precoIt'] != $_POST['precoIt'] or $retorN['codIt'] != $_POST['codIt']){ ?>
						
  <div class="error">Operation invalid.</div>
												
<?php } else if($_POST['qtdIt'] <= 0){ ?>
				
  <div class="error">Item Quantity invalid.</div>

	  <?php } else if($_POST['spec'] == "" or empty($_POST['charName'])){ ?>
				
  <div class="error">The spec and char name are required, check and try again.</div>
				
  <?php } else {
				
				//CALCULA QTD DE ITENS VEZES VALOR
				$preco = multi($_POST['qtdIt'], $_POST['precoIt']);
				
				//VERIFICA O CREDITO ATUAL NO BANCO DE DADOS COM O VALOR DA COMPRA CALCULADA
				$credito = credit($cred['creditoC']+$boni['creditoCB'], $preco);
				
				if($credito == 0){ ?>
					
				<div class="error">Credit insufficient to make this purchase.</div>
					
				<?php } else if($credito < $preco){ ?>
					
				<div class="error">Credit insufficient to make this purchase.</div>
					
				<?php } else if($credito >= $preco){
			
			        //TRATANTO OS DADOS DA COMPRA
					$idItem   = $_POST['idIt'];
					$codItem  = $_POST['codIt'];
					$char     = $_POST['charName'];
					$specItem = $_POST['spec'];
					$qtdade   = $_POST['qtdIt'];
					$msg      = '"Make good use of your item."';
					$dat      = $func->numDir($_SESSION['ID']);
					$postbox  = $rootDir."PostBox/".$dat."/".$_SESSION[ID].".dat";
					
					//VERIFICA SE O PRODUTO É O QUE ESTÁ SENDO COMPRADO
					$consultProd = mysql_query("SELECT *FROM item WHERE idIt = '".$idItem."'");
					$price = mysql_fetch_array($consultProd);
					if(mysql_num_rows($consultProd) == 1){					
					
					//ESCRITA DO DAT NA POSTBOX DO PLAYER
					$arquivo = $char." ".$codItem." ".$specItem." ".$msg."\r\n";
					
					for($i = 0; $i < $qtdade; $i++){
						
					
						if(file_exists($postbox)){
						
						$fp = fopen($postbox, "a+",0);
						$escreve = fwrite($fp, $arquivo);
						fclose($fp);
						//SE EFETUAR A GRAVAÇÃO DO ITEM NO .DAT FAZER O DESCONTO DO VALOR
						
						} else if(!file_exists($postbox)){
						
						copy("create/loja.dat",$postbox);
						$fp = fopen($postbox, "r+");
						$escreve = fwrite($fp, $arquivo);
						fclose($fp);
						

						}
					
					}
					
					
					if($escreve){
							
							$compraTotal = $preco;
							$bonusCred   = $boni['creditoCB'];
							$desconta    = $cred['creditoC'];
														
							if($bonusCred <= $compraTotal){
									$restBonus  = 0.00;
									$restCompra = $compraTotal - $bonusCred;
							     	$restCred   = $desconta - $restCompra;
									
							//ATUALIZANDO CREDITO APÓS COMPRA NO BONUS CASH SE HOUVER
							$upBonu = mysql_query("UPDATE bonusCash SET creditoCB = '".$restBonus."' WHERE userCB = '".$_SESSION[ID]."'");
							//ATUALIZANDO CREDITO APÓS COMPRA
							$upCash = mysql_query("UPDATE cash SET creditoC = '".$restCred."' WHERE userC = '".$_SESSION[ID]."'");
								
							} else if($bonusCred >= $compraTotal){
									$restBonus = $bonusCred - $compraTotal;
									$restCred  = $desconta;
							
							//ATUALIZANDO CREDITO APÓS COMPRA NO BONUS CASH SE HOUVER
							$upBonu = mysql_query("UPDATE bonusCash SET creditoCB = '".$restBonus."' WHERE userCB = '".$_SESSION[ID]."'");
							//ATUALIZANDO CREDITO APÓS COMPRA
							$upCash = mysql_query("UPDATE cash SET creditoC = '".$restCred."' WHERE userC = '".$_SESSION[ID]."'");

							}
							//CADASTRANDO NO HISTORICO O ITEM COMPRADO
							$relatorio = mysql_query("INSERT INTO historico (qtdH, itemH, valorH, userH, dataH)
																     VALUES ('".$qtdade."',
																	 		 '".$codItem."',
																			 '".$preco."',
																			 '".$_SESSION[ID]."',
																			 '".date('Y-m-d')."')");
						if($upCash and $upBonu and $relatorio){
							
							echo '<meta HTTP-EQUIV="Refresh" CONTENT="6;URL=login.php?sess=histo&pag=1">'; ?>						
							
                            <div class="sucess">Congratulations, you made ​​the purchase of <?php echo $qtdade." ".$price['nomeIt']; ?></div>
                            <div class="sucess">Now you possess: <?php echo formatMoeda($restBonus+$restCred); ?></div>
                            
						<?php } } else { ?>

							<div class="error">Unable to make the purchase of your item.</div>
                            
						<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=histo&pag=1">';						

						}

					
					} else { ?>

					<div class="error">There is an error with your item, it was not possible to make the purchase.</div>
					
				<?php }
				}
		   }
	 }		
}?>

                
  <div class="lojCont">
<?php if(isset($_GET["it"])){
					 
				$sp = mysql_query("SELECT *FROM item WHERE catIt = '".$_GET[it]."' ORDER BY levelIt ASC");
				$tp = mysql_query("SELECT *FROM categoria WHERE idC = '".$_GET[it]."'");
				
				?>
				
                <div class="titleItemMenu"><?php $titIt = mysql_fetch_array($tp); echo $titIt['cat']; ?></div>
                
				<?php while($item = mysql_fetch_array($sp)){ ?>
                
  <form action="" method="post" enctype="multipart/form-data" name="buyShop" class="loja" id="buyShop">

    <div class="itemTitulo"><?php echo $item['nomeIt']; ?></div>

    <div class="itemImg">
    <a href="javascript:;" title="The item does not possess information."> 
    <img src="<?php echo $pasta_loja.$item['imgIt']; ?>" alt="" />
    </a>
    </div>
 
      <div class="itemLevel">Level required. <?php echo $item['levelIt']; ?></div>
           
    <select name="charName" class="itemSelect">
      <option value="">Select the character</option>
<?php $qCharID  = ($_SESSION["charID"]) ? $_SESSION["charID"] : $_SESSION["ID"];
      $charInfo = $dirUserInfo.($func->numDir($qCharID))."/".$qCharID.".dat";

            if(file_exists($charInfo) && (filesize($charInfo) == 240)){
                $fRead = false;
                $fOpen = fopen($charInfo, "r");
                $fRead = fread($fOpen,filesize($charInfo));
                @fclose($fOpen);

                // list char information
   $charNameArr = array("48"  => trim(substr($fRead,0x30,15),"\x00"),
						"80"  => trim(substr($fRead,0x50,15),"\x00"),
						"112" => trim(substr($fRead,0x70,15),"\x00"),
						"144" => trim(substr($fRead,0x90,15),"\x00"),
						"176" => trim(substr($fRead,0xb0,15),"\x00"));

                if(count($charNameArr) > 0){
                    foreach($charNameArr as $key => $value){
                        $expValue = explode("\x00",$value);
                        if($expValue[0] != ""){ 
?>
<option value="<?php echo $expValue[0]; ?>"><?php echo $expValue[0]; ?></option>
<?php		}
	 	} 
	} 
}
?>          
  
    </select>

    <select name="spec" class="specSelect">
      <option value="">Select the item spec</option>
				  <?php
				  $specItem = mysql_query("SELECT *FROM item WHERE catIt = '".$_GET[it]."' AND idIt = '".$item[idIt]."'"); 
				  $spec = mysql_fetch_array($specItem);
				  $specIt   = $spec['specIt'];
				  $replace = str_replace(" ","", $specIt);
				  $contNum  = strlen($replace);
				  for($i = 0; $i < $contNum; $i++){						
				  ?>
      <option value="<?php echo substClasse($replace[$i]); ?>"><?php echo classes(substClasse($replace[$i])); ?></option>
				  <?php } ?>
    </select>
    
    <div class="itemLinha">
      <div class="itemQtd_nome">Amount</div>
      <span id="sprytextfield1">
      <input name="qtdIt" type="text" class="itemQtd" id="qtdIt" value="01"  maxlength="2" />
      <span class="textfieldRequiredMsg"></span> 
      <span class="textfieldInvalidFormatMsg"></span>
      <span class="textfieldMinCharsMsg"></span>
      <span class="textfieldMaxCharsMsg"></span>
      <span class="textfieldMinValueMsg"></span>
      <span class="textfieldMaxValueMsg"></span>
      </span>
      <input type="hidden" name="precoIt" id="precoIt" value="<?php echo $item["precoIt"]; ?>" class="preco" />
      <div class="custo"><?php echo $item["precoIt"]; ?></div>
    </div>
    
    <div class="itemLinha">
      <div class="compra">Price unit.</div>
      
      <?php if($item["precoIt"] <= $cred['creditoC']+$boni['creditoCB']){ ?>
      <input type="hidden" name="precoIt" value="<?php echo $item["precoIt"]; ?>" />
      <input type="hidden" name="idIt" value="<?php echo $item["idIt"]; ?>" />
      <input type="hidden" name="codIt" value="<?php echo $item["codIt"]; ?>" />
      <input type="submit" name="buy" value="Buy $<?php echo $item["precoIt"]; ?>"  class="btnCompra"/>
      <?php } else if($item["precoIt"] > $cred['creditoC']+$boni['creditoCB']){ ?>
      <input type="button" class="btnCompra" value="No coins">
      <?php } ?>
      
    </div>
    
  </form>
  
  <?php } } ?>
  
</div>
</div>
<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprytextfield1", "integer", {validateOn:["blur"], useCharacterMasking:true, hint:"01"});
</script>
</body>
</html>