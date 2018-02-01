<!-- #include file ="settings.asp" -->
<%
'Escrito por Daniel C.
'Versão 1.0

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname, bps, mortes

Dim tTime
tTime = " ¿ÀÈÄ "

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))

if userid = "" Or gserver = "" Or chname = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass
Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "SELECT BPS,Mortes FROM BPS WHERE ChName='" & chname & "' AND UserID = '"& userid& "'"
RS.Open QUERY, objConn, 3, 1

if RS.RecordCount = 0 Then
	bps = 0
	mortes = 0	
Else
	bps = RS("BPS").Value
	mortes = RS("Mortes").Value
End If
RS.Close

strReturn = "CBPs=" & bps & strSplit & "CDeads=" & mortes & strSplit

Response.Write(strReturn)
%>