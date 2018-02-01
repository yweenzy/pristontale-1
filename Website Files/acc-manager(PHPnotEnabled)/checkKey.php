<?php include("sql.php");

if(isset($_POST['keyCod'])){
	
$sql = odbc_do($conexao, "SELECT *FROM [ChaveDB].[dbo].[ChaveAccount] WHERE [chave] = '".$_POST[keyCod]."' ");

if(odbc_num_rows($sql) == 1){ echo '<div class="disp">Valid key.</div>';
					 } else { echo '<div class="indisp">Invalid key.</div>';
	}
}
?>  
