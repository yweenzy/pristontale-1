<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname, clName, clwon, clwonUserid, lv, ticket, chtype, chlv, chipflag

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' clanInsertClanWon (userid, gserver, chname, clName, clwon, clwonUserid, lv, chtype, chlv, chipflag)
userid = Trim(Request("userid")) 'Userid of Leader
gserver = Trim(Request("gserver")) 
chname = Trim(Request("chname")) 'Char name of Leader
clName = Trim(Request("clName"))
clwon = Trim(Request("clwon")) 'Char name of invited player
clwonUserid = Trim(Request("clwonUserid")) 'Userid of invited player
lv = Trim(Request("lv")) 'unimportant
chtype = Trim(Request("chtype"))
chlv = Trim(Request("chlv"))
chipflag = Trim(Request("chipflag")) 'char IP flag ? unimportant
ticket = Trim(Request("ticket"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(clName, "'","")
clName = safeQuery
safeQuery = Replace(clwon, "'","")
clwon = safeQuery

if userid = "" Or gserver = "" Or chname = "" Or clName = "" Or clwon = "" Or clwonUserid = "" Or lv = "" Or chtype = "" Or chlv = "" Or ticket = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "SELECT IDX,ClanZang,MemCnt FROM CL WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

Dim strReturn
Dim ClanLeader, ClanMembers, ClanSubChief, IDX
if RS.RecordCount >= 1 Then
	ClanLeader = RS("ClanZang").Value
	ClanMembers = CInt(RS("MemCnt").Value)
	IDX = RS("IDX").Value
	RS.Close
Else
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	strReturn = "Code=0" & strSplit
	Response.Write(strReturn)
	Response.End
End if

If (CInt(MemCnt) + 1) > 100 Then
	Set RS=Nothing
	objConn.Close
	Set objConn = Nothing
	strReturn = "Code=2" & strSplit
	Response.Write(strReturn)
	Response.End
End If


QUERY = "SELECT ChName FROM UL WHERE Permi=2 AND ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

If RS.RecordCount >= 1 Then
	ClanSubChief = RS("ChName").Value
Else
	ClanSubChief = ""
End If

if ClanLeader <> chname And ClanSubChief <> chname Then
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	strReturn = "Code=0" & strSplit
	Response.Write(strReturn)
	Response.End
End if

RS.Close

QUERY = "SELECT ClanName FROM UL WHERE ChName='" & clwon & "'"
RS.Open QUERY, objConn, 3, 1

Dim UclName
if RS.RecordCount >= 1 Then
	UclName = RS("ClanName").Value
Else
	UclName = ""
End if

if Not UclName = "" Then
	RS.Close
	Set RS = Nothing
	objConn.Close
	Set objConn = Nothing
	strReturn = "Code=0" & strSplit
	Response.Write(strReturn)
	Response.End
Else
	if UclName = "" And RS.RecordCount >= 1 Then
		RS.Close
		QUERY = "DELETE FROM UL WHERE ChName='" & clwon & "'"
		RS.Open QUERY, objConn, 3, 1
	End if
End if
RS.Close

ClanMembers = ClanMembers + 1

If ClanMembers > 40 Then
    Set RS=Nothing
    objConn.Close
    Set objConn = Nothing
    strReturn = "Code=4" & strSplit
    Response.Write(strReturn)
    Response.End
Else

QUERY = "UPDATE CL SET MemCnt='" & ClanMembers & "' WHERE ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

QUERY = "INSERT INTO UL ([IDX],[userid],[ChName],[ClanName],[ChType],[ChLv],[Permi],[JoinDate],[DelActive],[PFlag],[KFlag],[MIconCnt]) values('" & IDX & "','" & clwonUserid & "','" & clwon & "','" & clName & "','" & chtype & "','" & chlv & "','0',getdate(),'0','0','0','0')"
RS.Open QUERY, objConn, 3, 1

End if

strReturn = "Code=1" & strSplit
SET RS = Nothing
objConn.Close
SET objConn = Nothing

Response.Write(strReturn)
%>