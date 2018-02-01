<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, chname

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' isPFlag (userid, gserver, chname, clName, PFlag, Gubun)
chname = Trim(Request("chname"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT ClanName FROM UL WHERE ChName='" & chname & "'"

Set RS = Server.CreateObject("ADODB.Recordset")
RS.Open QUERY, objConn, 3, 1

Dim strReturn

if RS.RecordCount = 0 Then 'User Not In Clan
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