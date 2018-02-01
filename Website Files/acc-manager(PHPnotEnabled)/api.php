<?php if(XPT != 1) exit; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

<link rel="stylesheet" type="text/css" href="css/loja.css"/>
<link rel="stylesheet" type="text/css" href="css/default.css"/>
<link href="SpryAssets/SpryValidationTextField.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="js/jquery.js"></script>
<script src="SpryAssets/SpryValidationTextField.js" type="text/javascript"></script>
<script type="text/javascript" src="js/functions.js"></script>
<script type="text/javascript" src="js/shadowbox.js"></script>
<script type="text/javascript" src="js/qTip.js"></script>
<script type="text/javascript" src="js/moeda.js"></script>

<title>API de pagamentos</title>

doa&ccedil;&atilde;o do usu&aacute;rio
</head>

<body>
<?php 		$email 			  = 'donate@reloadedpt.net'; //e-mail do vendedor pagseguro
			$idPaypal 	      = 'QMWXMG2KDAZ6Q'; //ID vendedor paypal
			$currency 		  = 'BRL'; //moeda a ser paga
			$currency_1		  = 'EUR'; //moeda a ser paga
			$itemId1 		  = "Donate"; //nome do produto
			$itemDescription1 = "Doacao do usuario ".$_SESSION['ID']." ReloadedPT"; //descrição do produto
			$itemQuantity1 	  = 1;
			$reference 		  = "User: ".$_SESSION['ID']; //Pin number do cadastro do cliente
			$redict_url 	  = 'http://www.reloadedpt.net';
?>
<div id="painel">
<div class="painel">
<div class="comunicado"> 
Hello Warrior,<br />
It is very easy to make a donation, we are providing two ways to do them via online payment API, using a totally secure environment to prevent potential fraud. <br />
PagSeguro: Top rated for both intend to make donations in Brazilian currency (USD). <br />
PayPal: One of the largest management company payments with your domain you can make international payments in any currency that converts to own PayPal you receive by default in euro (EUR). <br />
To use our Payment API is very simple, just put the value in Kind and confirm that you want to donate, you will be redirected to the website of the company responsible for the online transaction, making the payment not bother to confirm your donation, our team is watching for you. and your credits will be added to your account as soon as possible. 
</div>
  
<div class="linha">
<a href="tutorial_donation.php" rel="shadowbox;height=480;width=853">
<img src="themes/reloadedpt/img/btn_tutorial.png" width="281" height="113" />
</a>
</div>
  
<br />
<br />
<br />
 

<div class="moedas_real">R$ 1,00 vale 100.00 Coins</div>
<div class="moedas_euro">&#8364; 1,00 worth 250.00 Coins</div>

<div id="formPagseguro">
  <form action="https://pagseguro.uol.com.br/v2/checkout/payment.html" method="post" enctype="application/x-www-form-urlencoded" target="pagseguro" class="formPagseguro">  
          
        <input type="hidden" name="receiverEmail" value="<?php echo $email; ?>">  
        <input type="hidden" name="currency" value="<?php echo $currency; ?>">  
        <input type="hidden" name="itemQuantity1" value="<?php echo $itemQuantity1; ?>">  
        <input type="hidden" name="reference" value="<?php echo $reference; ?>">  
        <input type="hidden" name="itemId1" value="<?php echo $itemId1; ?>">  
        <input type="hidden" name="itemDescription1" value="<?php echo $itemDescription1; ?>">
        <div class="linhaAPI">
        <strong>Valor a ser doado</strong>
        <span id="sprytextfield1">
        <input type="text" name="itemAmount1" class="campoAPI" maxlength="13"
        onkeypress="reais(this,event)" onkeydown="backspace(this,event)" />
        <span class="textfieldRequiredMsg">*</span> <span class="textfieldInvalidFormatMsg">*</span>
        <span class="textfieldMinValueMsg">*</span>
        <span class="textfieldMaxValueMsg">*</span></span>
        </div> 
        
        <div class="linhaAPI_2">                     
        <input type="submit" name="submit" alt="Pague com PagSeguro" value="" class="bntPagSeg">  
        </div>
      
  </form>  
</div>

<div id="formPaypal">
  <form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="PayPal" id="paypalPag" class="formPaypal"> 
         
         <!-- Identify your business so that you can collect the payments. --> 
         <input type="hidden" name="business" value="<?php echo $email; ?>"> 
         <!-- Specify a Buy Now button. --> 
         <input type="hidden" name="cmd" value="_xclick"> 
         <input type="hidden" name="return" value="https://www.reloadedpt.net">
         <!-- Specify details about the item that buyers will purchase. --> 
         <input type="hidden" name="item_name" value="<?php echo $itemId1; ?>"> 
         <input type="hidden" name="currency_code" value="<?php echo $currency_1; ?>"> 
         <input type="hidden" name="item_number" value="<?php echo $reference; ?>"> 
         
         <div class="linhaAPI">
         <strong>value of the donation</strong>
         <span id="sprytextfield2">
         <input type="text" name="amount" class="campoAPI" maxlength="13"
         onkeypress="reais(this,event)" onkeydown="backspace(this,event)"/>
         <span class="textfieldRequiredMsg">*</span>
         <span class="textfieldInvalidFormatMsg">*.</span>
         <span class="textfieldMinValueMsg">*</span>
         <span class="textfieldMaxValueMsg">*</span>
         </span>
         </div>
    
        <div class="linhaAPI_2">       
        <input type="submit" name="submit" alt="Pay with PayPal online" value="" class="btnPaypal"> 
        </div>
    
  </form>
</div>

<div class="moedas_real"><strong>Doação minima aceita: R$ 5,00</strong></div>
<div class="moedas_euro"><strong>Minimum donate accepted &#8364; 5,00</strong></div>

</div>

</div>
<script type="text/javascript">
var sprytextfield1 = new Spry.Widget.ValidationTextField("sprytextfield1", "currency", {validateOn:["blur"], hint:"0.00", minValue:5, maxValue:999});
var sprytextfield2 = new Spry.Widget.ValidationTextField("sprytextfield2", "currency", {validateOn:["blur"], hint:"0.00", minValue:5, maxValue:999});
</script>
</body>
</html>
