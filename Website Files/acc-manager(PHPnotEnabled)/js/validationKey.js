//FUNÇÃO DE VERIFICAÇÃO DE ID, EMAIL ETC...

pic1 = new Image(16, 16); 
pic1.src = "";

$(document).ready(function(){

$("#keyCod").change(function() { 

var usr = $("#keyCod").val();

if(usr.length >= 20)
{
$("#status_key").html('<div class="botoes_2"> checking...</div>');

$.ajax({ 
type: "POST", 
url: "checkKey.php", 
data: "keyCod="+ usr, 
success: function(msg){ 

$("#status_key").ajaxComplete(function(event, request, settings){ 

if(msg == 'OK')
{ 
$("#keyCod").removeClass('object_error'); // if necessary
$("#keyCod").addClass("object_ok");
$(this).html('');
} 
else 
{ 
$("#keyCod").removeClass('object_ok'); // if necessary
$("#keyCod").addClass("object_error");
$(this).html(msg);
}});}});}
else
{
$("#status_key").html('<div class="botoes_2">Key composed of 20 characters</div>');
$("#keyCod").removeClass('object_ok'); // if necessary
$("#keyCod").addClass("object_error");
}});});

//-->
