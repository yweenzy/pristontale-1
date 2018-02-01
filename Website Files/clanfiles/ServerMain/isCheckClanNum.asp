<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, num, gserver

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' isCheckClanNum (num, gserver)
num = Trim(Request("num"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(num, "'","")
num = safeQuery

if num = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT ClanName,Note FROM CL WHERE MIconCnt='" & num & "'"

Set RS = Server.CreateObject("ADODB.Recordset")
RS.Open QUERY, objConn, 3, 1

Dim strReturn, ClanName, ClanNote

If Not RS.RecordCount > 0 Then
	strReturn = "Code=0" & strSplit
Else
	ClanName = RS("ClanName").Value
	ClanNote = RS("Note").Value
	strReturn = "Code=1" & strSplit & "CName=" & ClanName & strSplit & "CNote=" & ClanNote & strSplit
End if

RS.Close
Set RS = Nothing
objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>