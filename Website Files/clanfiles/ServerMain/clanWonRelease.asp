<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname, clName, clwon1, ticket

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' clanWonRelease (userid, gserver, chname, clName, clwon1)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))
clName = Trim(Request("clName"))
clwon1 = Trim(Request("clwon1"))
ticket = Trim(Request("ticket"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(clwon1, "'","")
clwon1 = safeQuery
safeQuery = Replace(clName, "'","")
clName = safeQuery

if userid = "" Or gserver = "" Or chname = "" Or clName = "" Or clwon1="" Or ticket="" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "SELECT ClanName FROM UL WHERE ChName='" & clwon1 & "'"
RS.Open QUERY, objConn, 3, 1

Dim strReturn
Dim clName2

if RS.RecordCount >= 1 Then
	clName2 = RS("ClanName").Value
	if clName2 = "" Then
		QUERY = "DELETE FROM UL WHERE ChName='" & clwon1 & "'"
		RS.Open QUERY, objConn, 3, 1
		SET RS = Nothing
		objConn.Close
		SET objConn = Nothing
		strReturn = "Code=0" & strSplit
		Response.Write(strReturn)
		Response.End
	End if
	if Not clName2 = clName Then
		RS.Close
		SET RS = Nothing
		objConn.Close
		SET objConn = Nothing
		strReturn = "Code=0" & strSplit
		Response.Write(strReturn)
		Response.End
	End if
Else
	RS.Close
	SET RS = Nothing
	objConn.Close
	SET objConn = Nothing
	strReturn = "Code=0" & strSplit
	Response.Write(strReturn)
	Response.End
End if

RS.Close
QUERY = "SELECT ClanZang,MemCnt FROM CL WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

Dim ClanLeader, ClanMembers
ClanLeader = RS("ClanZang").Value
ClanMembers = CInt(RS("MemCnt").Value)
ClanMembers = ClanMembers - 1

if clwon1 = ClanLeader Then
	RS.Close
	SET RS = Nothing
	objConn.Close
	SET objConn = Nothing
	strReturn = "Code=4" & strSplit
	Response.Write(strReturn)
	Response.End
End if

QUERY = "UPDATE CL SET MemCnt='" & ClanMembers & "' WHERE ClanName='" & clName & "'"
Dim QUERY2
QUERY2 = "DELETE FROM UL WHERE ChName='" & clwon1 & "'"
RS.Close
RS.Open QUERY, objConn, 3, 1
RS.Open QUERY2, objConn, 3, 1

SET RS = Nothing
objConn.Close
SET objConn = Nothing
strReturn = "Code=1" & strSplit

Response.Write(strReturn)
%>