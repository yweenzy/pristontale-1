<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, chname, gserver

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' clanSubChipUpdate (chname, gserver)
chname = Trim(Request("chname"))
gserver = Trim(Request("gserver"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery

if chname = "" Or gserver = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "UPDATE UL SET Permi=0 WHERE ClanName IN (SELECT ClanName FROM UL WHERE ChName='" & chname & "')"
RS.Open QUERY, objConn, 3, 1

QUERY = "UPDATE UL SET Permi='2' WHERE ChName='" & chname & "'"
RS.Open QUERY, objConn, 3, 1

strReturn = "Code=1" & strSplit

Set RS = Nothing
objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>