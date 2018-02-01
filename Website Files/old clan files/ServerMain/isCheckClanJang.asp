<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' isCheckClanJang (userid, gserver)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(userid, "'","")
userid = safeQuery

if userid = "" Or gserver = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT ClanName FROM CL WHERE UserID='" & userid & "'"

Set RS = Server.CreateObject("ADODB.Recordset")
RS.Open QUERY, objConn, 3, 1

Dim strReturn

if RS.RecordCount = 0 Then
	strReturn = "Code=0" & strSplit
Else
	strReturn = "Code=1" & strSplit
End if

RS.Close
Set RS = Nothing
objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>