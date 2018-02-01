<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname, clName, ticket

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' clanRemove (userid, gserver, chname, clName)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))
clName = Trim(Request("clName"))
ticket = Trim(Request("ticket"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(clName, "'","")
clName = safeQuery

if userid = "" Or gserver = "" Or chname = "" Or clName = "" Or ticket = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "SELECT ClanZang FROM CL WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

Dim strReturn

if Not RS.RecordCount >= 1 Then
	strReturn = "Code=0" & strSplit
	
	RS.Close
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	
	Response.Write(strReturn)
	Response.End
End if

Dim ClanLeader
ClanLeader = RS("ClanZang").Value

if Not chName = ClanLeader Then
	strReturn = "Code=0" & strSplit
	
	RS.Close
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	
	Response.Write(strReturn)
	Response.End
End if

RS.Close

QUERY = "DELETE FROM CL WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

strReturn = "Code=1" & strSplit

QUERY = "DELETE FROM UL WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

Set RS = Nothing
objConn.Close
Set objConn = Nothing
Response.Write(strReturn)
%>