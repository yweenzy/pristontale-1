<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>

<title>Historico de comrpras</title>
</head>

<body>

<div id="painel">
<div class="painel">

<div class="titleItemMenu">Extract spending</div>

<?php 

		$total_reg = 10;
		$pagina = $_GET['pag'];
		
		if(!$pagina){ $pc = 1; } else { $pc = $pagina; }
		
		$inicio = $pc - 1;
		$inicio = $inicio * $total_reg;

 $listExtra = mysql_query("SELECT *FROM historico WHERE userH = '".$_SESSION[ID]."' ORDER BY idH DESC LIMIT $inicio,$total_reg");
 $todos     = mysql_query("SELECT *FROM historico WHERE userH = '".$_SESSION[ID]."'");

	$cont_Reg = mysql_num_rows($todos);
	$cont_Pag = $cont_Reg / $total_reg;

	  if($cont_Reg == 0){ ?>
		
        <div class="error">Not yet performed any purchase.</div>
        
<?php } else { ?> 

	<div class="linha_10">
        <div class="info_10"><img src="themes/reloadedpt/img/topItemOp.png" width="152" height="43" /></div>
        <div class="info_11"><img src="themes/reloadedpt/img/topCoinsused.png" width="126" height="43" /></div>
        <div class="info_12"><img src="themes/reloadedpt/img/topDateCompra.png" width="109" height="43" /></div>        
        </div>

<?php while($ordem = mysql_fetch_array($listExtra)){ ?>

<div class="linha_9"> 
   
   		<div class="info_7">      
		<?php echo "<strong>".$ordem['qtdH']." -</strong> "; if(strlen(itemExibe($ordem['itemH'])) == 5){
				
				echo 'Item not found.';
				
			} else { echo itemExibe($ordem['itemH']); } ?>
		</div>
        
        <div class="info_8">
        <?php echo $ordem['valorH']; ?>
        </div>
        
        <div class="info_9">
        <?php echo $ordem['dataH']; ?>
        </div>
        
</div>

<?php } } ?>


<div class="content_av">
        
<?php //PAGINAÇÃO
for($page = 1; $page <= ceil($cont_Pag); $page++){ 
		
	  if($_GET['pag'] == $page){
?>
	  <div class="pag_2"><?php echo $page."  "; ?></div>
        
<?php } if($_GET['pag'] != $page){ ?>
      <a href='login.php?sess=histo&amp;pag=<?php echo $page; ?>'>
		<div class="pag"><?php echo $page."  "; ?></div>
		</a>


<?php } } ?>

</div>


</div>
</div>

</body>
</html>