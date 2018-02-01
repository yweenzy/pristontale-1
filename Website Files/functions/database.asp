<% 'Written by Sandurr   sunny....go on discord really quick 
Sub DBSettings()
	Set objConn = Server.CreateObject("ADODB.Connection")
	Set RS = Server.CreateObject("ADODB.Recordset")

	dbhost = "WIN-MQ9JQN10MNQ\SQLEXPRESS"
	dbuser = "mordech1"
	dbpass = "Kad1791$$**"

	dbname1 = "accountdb"
	dbname2 = "ClanDB"
	dbname3 = "SoDDb"
End Sub

Function OpenConnection(Database)
	objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & database & "; User ID=" & dbuser & "; Password=" & dbpass
End Function

Function CloseConnection()
	objConn.Close()
End Function

Function LoadVar()
	OpenConnection(dbname2)
	ClanLeader = GetClanLeader(ClanName)
	ClanSubChief = GetClanSubChief(ClanName)
	ClanMembers = GetClanMembers(ClanName)
	ClanIMG = GetClanIMG(ClanName)
	ClanNote = GetClanNote(ClanName)
	CloseConnection()
End Function

Function UpdateClanNote()
	OpenConnection(dbname2)

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(nNote, "'","")
	nNote = safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "UPDATE CL SET Note='" & nNote & "' WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1

	ClanNote = nNote

	CloseConnection()
End Function

Function AccExists(AccountName)
	OpenConnection(dbname1)

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery

	QUERY = "SELECT * FROM AllGameUser WHERE userid='" & AccountName & "'"
	RS.Open QUERY, objConn, 3, 1

	If RS.RecordCount > 0 Then
		AccExists = True
	Else
		AccExists = False
	End If
	
	RS.Close()
	CloseConnection()
End Function

Function GetAccountIP(AccountName)
	OpenConnection(dbname1)

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery

	QUERY = "SELECT Channel FROM AllGameUser WHERE userid='" & AccountName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If RS.RecordCount < 1 Then
		GetAccountIP = ""
	Else
		Dim accountIP
		accountIP = RS("Channel").Value
		GetAccountIP = accountIP
	End if
	RS.Close()
	CloseConnection()	
End Function

Function SetAccountIP(AccountName,NIP)
	OpenConnection(dbname1)

	Dim IGameUser 
	IGameUser = ucase(left(AccountName,1)) & "GameUser"

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(NIP, "'","")
	NIP = safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery

	Dim UPDATE
	UPDATE = " SET Channel='" & NIP & "' WHERE userid='" & AccountName & "'"

	QUERY = "UPDATE AllGameUser" & UPDATE
	RS.Open QUERY, objConn, 3, 1

	QUERY = "UPDATE " & IGameUser & UPDATE
	RS.Open QUERY, objConn, 3, 1

	CloseConnection()	
End Function

Function LogDB(strDB, strLine)
	OpenConnection("LogDB")

	QUERY = "INSERT INTO " & strDB & " VALUES('" & UIP & "','" & strLine & "')"
	RS.Open QUERY, objConn, 3, 1

	CloseConnection()
End Function

Function ChangePassword(AccountName,Password)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(Password, "'","")
	Password = safeQuery
	safeQuery = Replace(AccountName, "'", "")
	AccountName = safeQuery

	LogDB "ChangePassword","Changed password to " & Password & " for account " & AccountName

	OpenConnection(dbname1)

	Dim IGameUser 
	IGameUser = ucase(left(AccountName,1)) & "GameUser"

	Dim UPDATE
	UPDATE = " SET Passwd='" & Password & "' WHERE userid='" & AccountName & "'"

	QUERY = "UPDATE AllGameUser" & UPDATE
	RS.Open QUERY, objConn, 3, 1

	QUERY = "UPDATE " & IGameUser & UPDATE
	RS.Open QUERY, objConn, 3, 1

	CloseConnection()
	ChangePassword = True
End Function

Function AccCreate(AccountName,Password)
	OpenConnection(dbname1)
	
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery
	safeQuery = Replace(Password, "'", "")
	Password = safeQuery

	Dim IGameUser 
	IGameUser = ucase(left(AccountName,1)) & "GameUser"

	Dim UPDATE

	UPDATE = " ([userid],[Passwd],[RegistDay],[DisuseDay],[inuse],[Grade],[EventChk],[SelectChk],[BlockChk],[SpecialChk],[Credit],[DelChk],[Channel]) values('" & AccountName & "','" & Password & "',getdate(),'12-12-2030','0','U','0','0','0','0','0','0','" & UIP & "')"

	QUERY = "INSERT INTO AllGameUser" & UPDATE
	RS.Open QUERY, objConn, 3, 1

	QUERY = "INSERT INTO " & IGameUser & UPDATE
	RS.Open QUERY, objConn, 3, 1

	CloseConnection()
	AccCreate = True
End Function

Function Login(AccountName,Password)	
	OpenConnection(dbname1)

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery
	safeQuery = Replace(Password, "'", "")
	Password = safeQuery
	
	QUERY = "SELECT Passwd FROM AllGameUser WHERE userid='" & AccountName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If RS.RecordCount < 1 Then
		Login = False
	Else
		Dim Password2
		Password2 = RS("Passwd").Value
		If Not Password2 = Password Then
			Login = False
		Else
			Login = True
		End if
	End if
	RS.Close()
	CloseConnection()
End Function

Function isClanMember(AccountName,CharName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(AccountName, "'","")
	AccountName = safeQuery
	safeQuery = Replace(CharName, "'", "")
	CharName = safeQuery

	OpenConnection(dbname2)
	QUERY = "SELECT ClanName FROM UL WHERE ChName='" & CharName & "' AND userid='" & AccountName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If RS.RecordCount < 1 Then
		isClanMember = "-1"
	Else
		Dim clName
		clName = RS("ClanName").Value
		isClanMember = clName
	End if
	RS.Close()
	CloseConnection()
End Function

Function GetClanLeader(ClanName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT ClanZang FROM CL WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If Not RS.RecordCount < 1 Then
		GetClanLeader = RS("ClanZang").Value
	End if
	RS.Close()
End Function

Function GetClanSubChief(ClanName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT ChName FROM UL WHERE ClanName='" & ClanName & "' AND Permi=2"
	RS.Open QUERY, objConn, 3, 1
	
	If Not RS.RecordCount < 1 Then
		GetClanSubChief = RS("ChName").Value
	End if
	RS.Close()
End Function

Function GetClanIMG(ClanName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT MIconCnt FROM CL WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If Not RS.RecordCount < 1 Then
		GetClanIMG = RS("MIconCnt").Value
	End if
	RS.Close()
End Function

Function GetClanNote(ClanName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT Note FROM CL WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If Not RS.RecordCount < 1 Then
		GetClanNote = RS("Note").Value
	End if
	RS.Close()
End Function

Function GetClanMembers(ClanName)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT MemCnt FROM CL WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1
	
	If Not RS.RecordCount < 1 Then
		GetClanMembers = RS("MemCnt").Value
	End if
	RS.Close()
End Function

Function GetCharType(ID)
	Select Case ID
		Case "1"
			GetCharType = "Fighter"
		Case "2"
			GetCharType = "Mechanician"
		Case "3"
			GetCharType = "Archer"
		Case "4"
			GetCharType = "Pikeman"
		Case "5"
			GetCharType = "Atalanta"
		Case "6"
			GetCharType = "Knight"
		Case "7"
			GetCharType = "Magician"
		Case "8"
			GetCharType = "Priestess"
	End Select
End Function

Function GetCharTypeInt(ID)
	Select Case ID
		Case "Fighter"
			GetCharTypeInt = 1
		Case "Mechanician"
			GetCharTypeInt = 2
		Case "Archer"
			GetCharTypeInt = 3
		Case "Pikeman"
			GetCharTypeInt = 4
		Case "Atalanta"
			GetCharTypeInt = 5
		Case "Knight"
			GetCharTypeInt = 6
		Case "Magician"
			GetCharTypeInt = 7
		Case "Priestess"
			GetCharTypeInt = 8
	End Select
End Function

Function IsClanLeader(CharName)
	If CharName = ClanLeader Then
		IsClanLeader = True
	Else
		IsClanLeader = False
	End If
End Function

Function IsClanSubChief(CharName)
	If CharName = ClanSubChief Then
		IsClanSubChief = True
	Else
		IsClanSubChief = False
	End If
End Function

Function GetRank(CharName)
	If IsClanLeader(CharName) = True Then
		GetRank = "Clan Chief"
	ElseIf IsClanSubChief(CharName) = True Then
		GetRank = "Clan Vice Chief"
	Else
		GetRank = "Clan Member"
	End If
End Function
%>