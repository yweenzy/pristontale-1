<html>

<head>
<title>Relic PristonTale</title>
<style>
#chrissy {
			Position: fixed;
			bottom: 20;
			width: 100%;
			background-color: #9E6939;
			z-index: 100;
		}

#santa {
			Position: fixed;
			bottom: 15;
			width: 100%;
			
			background-image: santa.png;
			overflow-x: auto; /* for horizontal scrolling*/
			overflow-y: auto; /* for vertical scrolling */
			
			     
     
		}		
</style>
<br><br>
<link rel="stylesheet" type="text/css" href="sunnyPT.css">
<link rel="shortcut icon" href="favicon.ico">

<img src= "closed.png">

<!-- #include file ="config/common.asp" -->
<!-- #include file ="config/header.asp" -->
<!-- #include file ="functions/database.asp" -->
<!-- #include file ="functions/injections.asp" -->

<% 'Written by Sandurr

Dim userid, passwd
userid = Request.Form("userid")
passwd = Request.Form("passwd")

%><div class='box'><p><%

Function ReturnMsg(strMessage)
	Response.Write(strMessage & "</p></div>")
End Function

If Len(passwd) > 8 Then
	ReturnMsg("Your password cannot be more than 8 characters")
	Response.End
End If

Dim InjectionsArray(2)
InjectionsArray(1) = userid
InjectionsArray(2) = passwd

If userid<>"" Or passwd<>"" Then
	If userid<>"" And passwd<>"" Then
		If IsNumeric(Left(userid,1)) = False Then
			If Injection(2, InjectionsArray) = True Then
				ReturnMsg("<b><font face=Verdana><font size=2><font color=#FC1304>Please try again.</font>")
			Else
				DBSettings()
				If AccExists(userid) = True Then
					ReturnMsg("<b><font face=Verdana><font size=2><font color=#FC1304>Account already exists.</font>")
				Else
					If AccCreate(userid,passwd) = True Then
						LogDB "Register","Account " & userid & " with password " & passwd & " created"
						ReturnMsg("<b><font face=Verdana><font size=2><font color=#0CCB00>Account successfully created!</font>")
					Else
						ReturnMsg("<b><font face=Verdana><font size=2><font color=#FC1304>Please try again.</font>")
					End If
				End If
			End If
		Else
			ReturnMsg("<b><font face=Verdana><font size=2><font color=#FC1304>Your Username must start with a letter.</font>")
		End If			
	Else
		ReturnMsg("<b><font face=Verdana><font size=2><font color=#FC1304>Please fill in both fields.</font>")
	End If
End If
%>




</head>

<body>
<script language="javascript">
function textboxMultilineMaxNumber(txt,maxLen){
try{
if(txt.value.length > (maxLen-1))return false;
}catch(e){
}
}
</script>
<div id="body">
<div id="html">
</div>

<!--<a href="#" class="register"></a>-->


<!--<img src="reg-off.png"  onmouseover="this.src='reg-off.png'" onmouseout="this.src='reg-off.png'"	width="62" height="18"/>-->




<center>

<form action="registration.asp" method="post">
<font face="Verdana"><font size=2><font color="white">
<input type="text" class="user" value="" size="11" name="userid" maxlength="12">
<input type="password" class="pass" value="" size="11" name="passwd" maxlength="8">
<input type="image" class="register" src="reg-off.png">
 </font>  
</form>

<a href="https://discord.gg/8yHzb8Y" class="download" target=";blank"></a>
<a href="http://relicpt.hopto.org" class="info"></a>

</center>
</div>
</div>


<div id="santa">



</div>

</body>
</html>
