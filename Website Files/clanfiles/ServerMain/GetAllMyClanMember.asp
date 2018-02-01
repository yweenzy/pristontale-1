<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' GetAllMyClanMember (userid, gserver, chname)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery

if userid = "" Or gserver = "" Or chname = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT ClanName FROM UL WHERE ChName='" & chname & "'"
Set RS = Server.CreateObject("ADODB.Recordset")
RS.Open QUERY, objConn, 3, 1

Dim strReturn

if RS.RecordCount = 0 Then
	strReturn = "Code=0" & strSplit
	
	RS.Close
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	
	Response.Write(strReturn)
	Response.End
End if

Dim clname, ClanLeader
clname = RS("ClanName").Value

Response.Write("Code=1" & strSplit & "CClanName=" & clname & strSplit)

RS.Close

QUERY = "SELECT ClanZang FROM CL WHERE ClanName='" & clname & "'"
RS.Open QUERY, objConn, 3, 1

ClanLeader = RS("ClanZang").Value

RS.Close

Response.Write("CClanZang=" & ClanLeader & strSplit)

QUERY = "SELECT ChName FROM UL WHERE ClanName='" & clname & "'"
RS.Open QUERY, objConn, 3, 1

Dim i, CharName
i = 1

While i <= RS.RecordCount
	CharName = RS("ChName").Value
	Response.Write("CMem=" & CharName & strSplit)
		
	if Not i = RS.RecordCount Then
		RS.MoveNext
	End if
	i = i + 1
Wend

RS.Close
Set RS = Nothing
objConn.Close
Set objConn = Nothing
%>