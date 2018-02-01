<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, chname, gserver, clName

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' clanChipChange (chname, gserver, clName)
chname = Trim(Request("chname")) 'Probably the CharName of new Chief ;)
gserver = Trim(Request("gserver"))
clName = Trim(Request("clName"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery
safeQuery = Replace(clName, "'","")
clName = safeQuery

if chname = "" Or gserver = "" Or clName = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

Set RS = Server.CreateObject("ADODB.Recordset")

QUERY = "SELECT userid FROM UL WHERE ChName='" & chname & "' AND ClanName='" & clName & "'"
RS.Open QUERY, objConn, 3, 1

Dim strReturn, UserID

if RS.RecordCount >= 1 Then
	UserID = RS("userid").Value
	RS.Close
	strReturn = "Code=1" & strSplit

	QUERY = "UPDATE CL SET ClanZang='" & chname & "',UserID='" & UserID & "' WHERE ClanName='" & clName & "'"
	RS.Open QUERY, objConn, 3, 1
Else
	RS.Close
	strReturn = "Code=0" & strSplit
End if

Set RS = Nothing
objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>