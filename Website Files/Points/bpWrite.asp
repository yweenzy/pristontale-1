<!-- #include file ="settings.asp" -->
<%
'Escrito por Daniel C.
'Versão 1.0

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname, bps, deads, chlvl, check

Dim tTime
tTime = " ¿ÀÈÄ "

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' bpInsert (userid, gserver, chname, bps)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))
chtype = Trim(Request("chtype"))
bps = Trim(Request("bps"))
deads = Trim(Request("deads"))
chlvl = Trim(Request("lvl"))
check = Trim(Request("check"))

if check <> "isPlayer" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

if userid = "" Or gserver = "" Or chname = "" Or bps = "" Or chlvl="" Or chtype="" Or deads="" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim QUERY, RS, objConn
Set objConn = Server.CreateObject("ADODB.Connection")
Set RS = Server.CreateObject("ADODB.Recordset")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT BPS FROM BPS WHERE ChName='" & chname & "'"
RS.Open QUERY, objConn, 3, 1

if RS.RecordCount = 0 Then
	RS.Close
	QUERY = "INSERT INTO BPS ([UserID],[ChName],[ChLvl],[ChType],[BPS],[Mortes]) values ('" & userid & "','" & chname & "','" & chlvl & "','" & chtype & "','" & bps & "','" & deads & "')			"
	RS.Open QUERY, objConn, 3, 1
	Response.Write("Code=1" & strSplit)
	Response.End
Else
	RS.Close
	QUERY = "UPDATE BPS SET BPS = '" & bps & "', ChLvl = '" & chlvl & "', Mortes = '" & deads & "' WHERE ChName = '" & chname & "'"
	RS.Open QUERY, objConn, 3, 1
	Response.Write("Code=1" & strSplit)
	Response.End
End If

RS.Close
Set RS = Nothing
objConn.Close
Set objConn = Nothing

%>