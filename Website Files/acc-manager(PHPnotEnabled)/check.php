<?php include("sql.php");

if(isset($_POST['id'])){
	
	$username = $_POST['id'];
	
$sql = odbc_exec($conexao, "SELECT *FROM [accountdb].[dbo].[ALLPersonalMember] WHERE [Userid] = '$username'");

if(odbc_num_rows($sql) >= 1){
	
echo '<div class="indisp">'.$username.' unavailable.</div>';

} else {
	
echo '<div class="disp">'.$username.' available.</div>';
	
	}
}
?>  
