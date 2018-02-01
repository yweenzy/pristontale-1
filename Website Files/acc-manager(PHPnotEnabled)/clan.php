<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryCollapsiblePanel.css" rel="stylesheet" type="text/css" />
<link href="SpryAssets/SpryValidationSelect.css" rel="stylesheet" type="text/css" />
<title>Clan</title>


<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script src="SpryAssets/SpryCollapsiblePanel.js" type="text/javascript"></script>
<script src="SpryAssets/SpryValidationSelect.js" type="text/javascript"></script>
</head>

<body>


<div class="includes">

<?php 	
	
	$queryQT = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE ChName = '".$_SESSION[charName]."'");
	$qtlider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE ChName = '".$_SESSION[charName]."'");
	$contador = odbc_num_rows($qtlider);
	
	if($contador == 0){
?>
<div class="error">This character does not possess Clan.</div>

<?php } else { 
	 
	    //VERIFICA SE É O LIDER E PEGA INFOS DO CLAN
		$query = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[CL]  WHERE UserID = '".$_SESSION[ID]."' 
																		AND ClanZang = '".$_SESSION[charName]."'");
																		
		$qtlider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[CL]  WHERE UserID = '".$_SESSION[ID]."' 
																		AND ClanZang = '".$_SESSION[charName]."'");

		$lider = odbc_fetch_array($query);
		$contLider = odbc_fetch_row($qtlider);	

		$nomeclan = $lider['ClanName'];
		$fraseclan = $lider['Note'];
		$idlider = $lider['UserID'];
		$nomelider = $lider['ClanZang'];
		$numeroMembros = $lider['MemCnt'];
		$numeroclan = $lider['MIconCnt'];
		$dataclan = substr(ConvertDateEUA($lider['RegiDate']), 0, 10);
		
		
		//PEGANDO O VICE LIDER DO CLAN
		$queryVice = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE Permi = '2' AND ClanName = '".$lider['ClanName']."'");
		$qtvicelider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE Permi = '2' AND ClanName = '".$lider['ClanName']."'");
		$contVice = odbc_num_rows($qtvicelider);
		$consVc = odbc_fetch_array($queryVice);
			
			if($contVice == 0){ $vice = "Não delegado."; }
	   else if($contVice == 1){ $vice = $consVc['ChName']; } 
	   else { echo "Não localizado."; }
	   
	   //LISTANDO MEMBROS PARA DELEGAÇÃO DE VICE LIDER MENOS O PROPRIO LIDER
	   $listMemVice = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE ClanName = '".$nomeclan."' 
	   																		   AND ChName <> '".$nomelider."' ORDER BY JoinDate ASC");

		
		
if($contLider == 1){ ?>

<form action="" method="post" enctype="multipart/form-data" >   	
    <div class="titulo"> Clan Master <?php echo $nomeclan; ?></div>


<?php if(isset($_POST['deleteClan'])){
	
	$clanDel = $_POST['clandel'];
	
	if(filtro($clanDel != 0)){ ?>

	<div class="error">Characters not allowed.</div>

	<?php } else {
		
	$ul = odbc_exec($conexao, "DELETE FROM [ClanDb].dbo.UL WHERE ClanName = '".$clanDel."'");
	$cl = odbc_exec($conexao, "DELETE FROM [ClanDb].dbo.CL WHERE ClanName = '".$clanDel."' AND UserID = '".$_SESSION[ID]."'");
	
	if($ul and $cl){

?>

	<div class="sucess">The clan <?php echo $nomeclan; ?> was deleted from the server.</div>

<?php 

		echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

 } else {

?>

	<div class="error">Error while deleting the Clan <?php echo $nomeclan; ?>, notify the administrator.</div>
    
<?php } } 
	
	echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

} ?>


    
    <div class="clanDescOp">
    
    <?php if($contLider == 1){  ?>
    
    <input type="submit" name="deleteClan" value="Delete Clan" class="botoes_6" 
     onclick="return confirm('Do you really want delete this Clan server?');">
    <input type="hidden" value="<?php echo $nomeclan; ?>" name="clandel" />
    
    <?php } else if($contLider == 0){ ?>
    
    <input type="submit" name="logoutClan" value="Leave Clan" class="botoes_6"
    onclick="return confirm('Really remove character <?php echo $_SESSION['ID']; ?> Clan <?php echo $nomeclan; ?>?');">
    <input type="hidden" value="<?php echo $nomeclan; ?>" name="clan" />
    
    <?php } ?>
    
    </div>
    
          <div class="clanname">
          <img src="<?php echo $urltagsClan.$numeroclan; ?>.bmp" width="32" height="32">
          <?php echo $nomeclan; ?>
          </div>
          <div class="clanlider"><strong>Leader:</strong> <?php echo $nomelider; ?></div>
          <div class="clandate"><strong>Created in:</strong> <?php echo $dataclan; ?></div>
          <div class="clanmember"><strong>Members:</strong> <?php echo $numeroMembros; ?></div>
          <div class="clanmember"><strong>Sub-chief:</strong> <?php echo $vice; ?></div>

</form>

<?php if(isset($_POST['mudarfrase'])){

	if(filtro($_POST['Note']) != 0){ ?>
			
	<div class="error">Special characters are not allowed, check.</div>
			
<?php } else {

	$queryMudar = odbc_exec($conexao, "UPDATE [ClanDb].[dbo].[CL] SET [Note] = '".$_POST[Note]."' WHERE [UserID] = '".$_SESSION[ID]."'");
	
	if($queryMudar){ ?>
    
	<div class="sucess">Slogan Clan changed successfully.</div>
    
<?php } else { ?>

	<div class="error">There was an error changing the phrase, notify the administrator.</div> 
	
<?php } } 

	echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

} ?>


<form action="" method="post" name="fraseclan" enctype="multipart/form-data">
        
        <!-- FRASE DO CLAN -->
      <div class="linha_6">
        <strong>Current sentence: <b><?php echo $fraseclan; ?><b></strong>
        
        <span id="SprayFrase">
        
        <input name="Note" type="text" class="campos_1" maxlength="100"/>
        <span class="textfieldRequiredMsg">*</span>
        
        </span>
        <input type="submit" name="mudarfrase" value="Change" class="botoes_7" />
    </div>
      
</form>



<!--Delegando vice lider -->

<?php if(isset($_POST['viceLider'])){
	
	if(filtro($_POST['lider'] != 0) or empty($_POST['lider'])){ ?>

	<div class="error">Invalid characters were found, and no one was selected.</div>
		
<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

 } else if($_POST['lider'] == "no"){
	
	//DEIXAR SEM VICE LIDER
	$upNo_vice = odbc_exec($conexao, "UPDATE [ClanDb].[dbo].[UL] SET [Permi] = '0' WHERE [Permi] = '2' AND ClanName = '".$nomeclan."'");
	if($upNo_vice){
?>

<div class="sucess">The clan <?php echo $nomeclan; ?>, not possess more Sub-chief.</div>

<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

 } else { ?>

<div class="error">There was an error, please notify the administrator.</div>

<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';
 } } else { 
		
		//SETA TODOS OS PERMI = 2 PARA 0 E SETA O NOVO VICE LIDER PARA 2
		$sqlZero = odbc_exec($conexao, "UPDATE [ClanDb].[dbo].[UL] SET [Permi] = '0' WHERE [Permi] = '2' AND ClanName = '".$nomeclan."'");
		$sqlDois = odbc_exec($conexao, "UPDATE [ClanDb].[dbo].[UL] SET [Permi] = '2' WHERE [ChName] = '".$_POST[lider]."' 
																					   AND [ClanName] = '".$nomeclan."'");
																					   
				if($sqlZero and $sqlDois){

?> 

<div class="sucess"><?php echo $_POST['lider']; ?> is now the new Sub-chief of Clan, <?php echo $nomeclan; ?>.</div>

<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

 } else { ?>

<div class="error">There was an error, please notify the administrator.</div>

<?php echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';
 } } } ?>

<form action="" method="post" name="fraseclan" enctype="multipart/form-data">

<div class="linha_6">
				
              <strong>Delegate Sub-chief:</strong>
              
              <span id="spryselect1">
              <select name="lider" >
                <option value="0" selected="selected">Select</option>
                <option value="no">Leave no Sub-chief</option>
                <?php while($indvice = odbc_fetch_array($listMemVice)){ ?>
                <option value="<?php echo($indvice['ChName']); ?>"><?php echo($indvice['ChName']);?></option>
                <?php } ?>
              </select>
              <span class="selectInvalidMsg">*</span>
              <span class="selectRequiredMsg">*</span>
              </span>
              
              <input type="submit" name="viceLider" value="Delegate" class="botoes_7" /> 

</div>

</form>     

<!--Fim vice lider -->

  
<?php //INICIO DO UPLOAD

if(isset($_POST['upload'])){
	
	$img  = $_FILES['img'];
	$x    = 32;
	$y    = 32;
	$bits = 4068;
	$ext  = $img['type'];
	$extp = 'image/bmp';

	$imgSize = getimagesize($img['tmp_name']);
	
				 //INICIA VERIFICAÇÃO DA IMAGEM SE É VÁLIDA 32X32 ATÉ 4KB EXTENSÃO BMP
				 if($ext != $extp){ ?>
					 
					  <div class="error">Extension of the image should be (bmp).</div>
					  
    <?php } else if($x != $imgSize[0] or $y != $imgSize[1]){ ?>
			
					  <div class="error"> The image does not meet the standard size of 32x32 pixels.</div> 
					  
    <?php } else if($img['size'] >= $bits){ ?>
			
					 <div class="error">The image should be a maximum of 4 KB.</div>
					  
<?php } else {
		    
			//MONTANDO NOME E EXTENSÃO DO ARQUIVO NOVO
			$nome = $numeroclan.'.bmp';

			//DIFININDO AS CONFIGURAÇÕES DO UPLOAD EM CAMINHO FISICO E NOME DA IMAGEM EX: c:\...\...\XXX.BMP
			$dirFisico = $dirCContent.$nome;
			
			if(file_exists($dirFisico)){ unlink($dirFisico); }
	
					//SE DELETOU O ARQUIVO ANTIGO ELE FAZ O UPLOAD
					$uploadBmp = move_uploaded_file($img["tmp_name"], $dirFisico);
					if($uploadBmp){ 
?>
					
					<div class="sucess">His image of clan successfully changed.</div>
					
<?php } else { ?>
					
					<div class="error">There was an error uploading, please notify the administrator.</div>
						
<?php 
		}		
	}
	
	echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';

} //FECHA ISSET UPLOAD
?>
       
       
<form action="" method="post" name="admClan" enctype="multipart/form-data">

        <!-- IMAGEM DO CLAN -->
        <div class="linha_6">
        
        <strong>Change the banner of Clan</strong>
        
        <span id="SprayUpload">
        
          <input id="fakeupload" name="fakeupload" class="fakeupload" type="text"/>
          <span class="textfieldRequiredMsg">There was no image selected.</span>
          
          </span>
          <input id="img" name="img" class="realupload" type="file" size="5"
           onchange="this.form.fakeupload.value = this.value;" />

        <input name="upload" type="submit" value="upload" class="botoes_7" />
    </div>
        
        
</form>

<?php if(isset($_POST['kickMember'])){
		
		$contArray = count($_POST['kick']);
		
		if($contArray == 0){ ?>
		
        <div class="error">No member was selected.</div>
        	
<?php } else {
		
		for($i = 0; $i < $contArray; $i++){
		
		$nomesKick = $_POST['kick'][$i];
		
		//DELETA MEMBRO DO CLAN
		$sqlD = odbc_exec($conexao, "DELETE FROM [ClanDB].[dbo].[UL] WHERE ChName = '$nomesKick'");
		
		if($sqlD){
		
		//ATUALIZA NUMERO DE MEMBROS
		$kickNum = ($numeroMembros - $contArray);
		$sqlU = odbc_exec($conexao, "UPDATE [ClanDB].[dbo].[CL] SET [MemCnt] = '$kickNum' WHERE ClanName = '$nomeclan'");
		
?>
        
		<div class="sucess"><?php echo $nomesKick; ?> removed.</div>
		
<?php } else { ?>
			
			<div class="error">There was an error removing the character of the Clan.</div>
            
<?php } } } //FECHA FOR ?>

<div class="linha_5">
<a href="?sess=clan" class="botoes_5">OK</a>
</div>

<?php } /*FECHA ISSET DELETE MEMBRO */ ?>

<form action="" method="post" name="ListMem" enctype="multipart/form-data">

        <!-- LISTA DE MEMBROS ADM -->
        <div class="linha_8">
                  <div id="CollapsiblePanel1" class="CollapsiblePanel">
                  
                    <div class="CollapsiblePanelTab" tabindex="0">
                    List of members of the Clan<?php echo $nomeclan; ?>
                    <div class="exibir"><img src="img/btn_exibir.png" width="91" height="20" alt="Exibir" /></div>
                    </div>
                    
                    <div class="CollapsiblePanelContent">
                    
                    <div class="guiaTitles_2">
                    <div class="info_1">Character</div>
                    <div class="info_2">Class</div>
                    <div class="info_3">Level</div>
                    <div class="info_4">Registration Date</div>                    
                    <div class="info_5">Status</div>
                    <div class="info_6">Delete</div>
         			</div>
                    
        <!-- MEMBROS -->


<?php

	function StatusCT($var){
		
			 if($var == 0){ $var = '<div class="statusOFF">Offline</div>'; 
			       } else { $var = '<div class="statusON">Online</div>'; }
		
	return $var;	
	}
 
$queryMembros = odbc_exec($conexao, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE ClanName = '".$nomeclan."' 
																	     AND ChName <> '".$nomelider."' ORDER BY JoinDate ASC");

while($listar = odbc_fetch_array($queryMembros)){
	
	  $Lnick    = $listar["ChName"];
	  $Lclasse  = $listar["ChType"];
	  $Llevel   = $listar["ChLv"];
	  $Ldatainc = $listar["JoinDate"];

   	    //VENDO QUEM ESTÁ ONLINE
		$queryOff = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[CT] WHERE [ChName] = '".$Lnick."'");
		$contOn = odbc_num_rows($queryOff);
			
?>                  
                    <div class="titleListMember_1">
					<div class="Lnick"><?php echo $Lnick; ?></div>
                    <div class="Lclasse"><?php echo CharImgMini($Lclasse); ?></div>
                    <div class="Llevel"><?php echo $Llevel; ?></div>
                    <div class="Ldatainc"><?php echo substr(ConvertDateEUA($Ldatainc), 0, 10); ?></div>
                    <div class="Lstatus"><?php echo StatusCT($contOn); ?></div>
                    <div class="Lexcluir"><input type="checkbox" name="kick[]" value="<?php echo $Lnick; ?>" /></div>
                    </div>
<?php } ?>                    
         <!-- FIM MEMBROS -->
                    
                    <div class="linha_7">
                    <input type="submit" value="Remove members marked" name="kickMember"  class="botoes_7"/>
                    </div>
                    
                    </div>
                    
              		</div>     
                    </div> 
</form>           
        
<?php } else if($contLider == 0){ 
 
        //VERIFICA SE É O LIDER E PEGA INFOS DO CLAN
		$query = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE ChName = '".$_SESSION[charName]."'");
																		
		$qtlider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[UL]  WHERE ChName = '".$_SESSION[charName]."'");
																		
		$lider = odbc_fetch_array($query);
		
				//PEGA AS INFORMAÇÕES DO CLAN
				$queryDados = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[CL]  WHERE ClanName = '".$lider[ClanName]."'");
				$dadosClan = odbc_fetch_array($queryDados);
				
		$nomeclan 	   = $dadosClan['ClanName'];
		$fraseclan     = $dadosClan['Note'];
		$nomelider     = $dadosClan['ClanZang'];
		$numeroMembros = $dadosClan['MemCnt'];
		$numeroclan    = $dadosClan['MIconCnt'];
		$dataclan      = substr(ConvertDateEUA($dadosClan['RegiDate']), 0, 10);
				
		//PEGANDO O VICE LIDER DO CLAN
		$queryVice = odbc_exec($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE Permi = '2' AND ClanName = '".$lider['ClanName']."'");
		$qtvicelider = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[UL] WHERE Permi = '2' AND ClanName = '".$lider['ClanName']."'");
		$contVice = odbc_num_rows($qtvicelider);
		$consVc = odbc_fetch_array($queryVice);
			
			if($contVice == 0){ $vice = "Não delegado."; }
	   else if($contVice == 1){ $vice = $consVc['ChName']; } 
	   else { echo "Não localizado."; }


 if(isset($_POST['logoutClan'])){ 

	$clanDel = $_POST['clan'];
	$idDel   = $_SESSION['ID'];
	$charDel = $_SESSION['charName'];
	
	if(filtro($clanDel) != 0 
	or filtro($idDel != 0) 
	or filtro($charDel != 0)
	or empty($clanDel)
	or empty($idDel)
	or empty($charDel)){
?>
		
<div class="error">Missing information or special characters were detected.</div>
		
<?php } else {
	
		$sair = odbc_exec($conexao, "DELETE FROM [ClanDB].[dbo].[UL] WHERE [userid] = '".$idDel."'
																	   AND [ChName] = '".$charDel."' 
																	   AND [ClanName] = '".$clanDel."'");

		if($sair){
			
		//ATUALIZA NUMERO DE MEMBROS
		$kickNum = ($numeroMembros - 1);
		odbc_exec($conexao, "UPDATE [ClanDB].[dbo].[CL] SET [MemCnt] = '$kickNum' WHERE ClanName = '".$clanDel."'");
		
?>

<div class="sucess"><?php echo $charDel; ?> the character was removed from the clan <?php echo $clanDel; ?>.</div>
										   
<?php 

echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';
 
 } else { 
 
?>

<div class="error">There was an error removing the character of the Clan.</div>

<?php

	 echo '<meta HTTP-EQUIV="Refresh" CONTENT="3;URL=login.php?sess=clan">';
	
	 		} /*FECHA CONDIÇÕES */
	  } /* FECCHA VERIFICAÇÃO DE CARACTERES */
 } /*FECHA ISSET SAIR DO CLAN */ 
?>

<form action="" method="post" name="SairClan" enctype="multipart/form-data">
    	
    <div class="titulo"> Clan Master <?php echo $nomeclan; ?></div>
    
    <!-- INFORMAÇÕES DO CLAN -->
    <div class="clanDescOp">
    
    <?php if($contLider == 1){  ?>
    
    <input type="submit" name="deletClan" value="Delete Clan" class="botoes_6" 
     onclick="return confirm('Do you really want delete this Clan server?');">
    <input type="hidden" value="<?php echo $nomeclan; ?>" name="clandel" />
    
    <?php } else if($contLider == 0){ ?>
    
    <input type="submit" name="logoutClan" value="leave Clan" class="botoes_6"
    onclick="return confirm('Really remove character <?php echo $_SESSION['charName']; ?> Clan <?php echo $nomeclan; ?>?');">
    <input type="hidden" value="<?php echo $nomeclan; ?>" name="clan" />
   
    <?php } ?>
    
    </div>
    
          <div class="clanname">
          <img src="<?php echo $urltagsClan.$numeroclan; ?>.bmp" width="32" height="32">
          <?php echo $nomeclan; ?>
          </div>
          <div class="clanlider"><strong>Leader:</strong> <?php echo $nomelider; ?></div>
          <div class="clandate"><strong>Created in:</strong> <?php echo $dataclan; ?></div>
          <div class="clanmember"><strong>Members:</strong> <?php echo $numeroMembros; ?></div>
          <div class="clanmember"><strong>Sub-chief:</strong> <?php echo $vice; ?></div>

          </form>


                <!-- LISTA DE MEMBROS PLAYER -->
                  <div class="linha_7">
                    <div id="CollapsiblePanel1" class="CollapsiblePanel">
                      <div class="CollapsiblePanelTab" tabindex="0"> List of members of the Clan <?php echo $nomeclan; ?>
                        <div class="exibir"><img src="img/btn_exibir.png" width="91" height="20" alt="Exibir" /></div>
                      </div>
                      <div class="CollapsiblePanelContent">
                        <div class="guiaTitles">
                          <div class="info_1">Character</div>
                          <div class="info_2">Class</div>
                          <div class="info_3">Level</div>
                          <div class="info_4">Registration Date</div>
                          <div class="info_5">Status</div>
                        </div>
                        <!-- MEMBROS -->
                        <?php

	function StatusCT($var){
		
			 if($var == 0){ $var = '<div class="statusOFF">Offline</div>'; 
			       } else { $var = '<div class="statusON">Online</div>'; }
		
	return $var;	
	}
 
$queryMembros = odbc_exec($conexao, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE ClanName = '".$nomeclan."' 
																	     AND ChName <> '".$nomelider."' ORDER BY JoinDate ASC");

while($listar = odbc_fetch_array($queryMembros)){
	
	  $Lnick    = $listar["ChName"];
	  $Lclasse  = $listar["ChType"];
	  $Llevel   = $listar["ChLv"];
	  $Ldatainc = $listar["JoinDate"];

   	    //VENDO QUEM ESTÁ ONLINE
		$queryOff = odbc_do($conexao, "SELECT *FROM [ClanDB].[dbo].[CT] WHERE [ChName] = '".$Lnick."'");
		$contOn = odbc_num_rows($queryOff);
			
?>
                        <div class="titleListMember">
                          <div class="Lnick"><?php echo $Lnick; ?></div>
                          <div class="Lclasse"><?php echo CharImgMini($Lclasse); ?></div>
                          <div class="Llevel"><?php echo $Llevel; ?></div>
                          <div class="Ldatainc"><?php echo substr(ConvertDateEUA($Ldatainc), 0, 10); ?></div>
                          <div class="Lstatus"><?php echo StatusCT($contOn); ?></div>
                        </div>
                        <?php } ?>
                        <!-- FIM MEMBROS -->
                      </div>
                    </div>
</div>

<?php } } ?>

                </div>


<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("SprayFrase", "none", {validateOn:["blur"], hint:"Enter your Slogan for the clan"});
var sprytextfield2 = new Spry.Widget.ValidationTextField("SprayUpload", "none", {validateOn:["blur"]});
var CollapsiblePanel1 = new Spry.Widget.CollapsiblePanel("CollapsiblePanel1", {contentIsOpen:false});
var spryselect1 = new Spry.Widget.ValidationSelect("spryselect1", {invalidValue:"0", validateOn:["blur"]});
</script>

</body>
</html>