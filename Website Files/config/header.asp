<br>
<br>
<head>
	<link href="config/style.css" type="text/css" rel="stylesheet" media="all" />

<%
Dim dbhost, dbuser, dbpass, dbname1, dbname2, dbname3, UIP
Dim objConn, RS, QUERY

UIP = Request.ServerVariables("remote_addr")

Dim gText2, gFileSystemObject2, gFile2

Set gFileSystemObject2=Server.CreateObject("Scripting.FileSystemObject")
Set gFile2=gFileSystemObject2.OpenTextFile(Server.MapPath("BanList.txt"), 1)

Do While gFile2.AtEndOfStream = False
	gText2 = gText2 & gFile2.ReadLine & vbNewLine
Loop

if InStr(gText2,UIP) > 0 Then
	Response.Write("<meta http-equiv='refresh' content='0;url=http://www.mysterypt.com'>")
	Response.End
End if

%>
</head>
<td align='center'>