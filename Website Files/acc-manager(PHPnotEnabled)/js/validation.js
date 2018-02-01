//FUNÇÃO DE VERIFICAÇÃO DE ID, EMAIL ETC...

pic1 = new Image(16, 16); 
pic1.src = "";

$(document).ready(function(){

$("#id").change(function() { 

var usr = $("#id").val();

if(usr.length >= 3)
{
$("#status").html('<div class="botoes_2"> Verificando...</div>');

$.ajax({ 
type: "POST", 
url: "check.php", 
data: "id="+ usr, 
success: function(msg){ 

$("#status").ajaxComplete(function(event, request, settings){ 

if(msg == 'OK')
{ 
$("#id").removeClass('object_error'); // if necessary
$("#id").addClass("object_ok");
$(this).html('');
} 
else 
{ 
$("#id").removeClass('object_ok'); // if necessary
$("#id").addClass("object_error");
$(this).html(msg);
}});}});}
else
{
$("#status").html('<div class="botoes_2">Mínimo de 3 caracteres</div>');
$("#id").removeClass('object_ok'); // if necessary
$("#id").addClass("object_error");
}});});

//-->
