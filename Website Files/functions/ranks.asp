<!-- #include file = "database.asp" -->

<% 'Written by Sandurr
DBSettings()

Function RankTable(Results, Min, Max, ChType)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ChType, "'","")
	ChType = safeQuery

	If Results <= 0 Or Results > 250 Then
		Results = 250
	End If
	If Min=0 Or Max=0 Then
		Min = 0
		Max = 250
	End If
	If ChType="" Then
		QUERY = "SELECT * FROM LevelList ORDER BY CharLevel DESC"
	Else
		QUERY = "SELECT * FROM LevelList WHERE CharClass='" & ChType & "' ORDER BY CharLevel DESC"
	End If

	Dim gName(250)
	Dim gLevel(250)
	Dim gClass(250)

	Dim tName, tLevel, tClass

	Dim iC, strRankTable
	iC = 1

	OpenConnection(dbname1)
	RS.Open QUERY, objConn, 3, 1

	If Not RS.RecordCount >= 1 Then
		strRankTable = "No characters"
	Else
		Dim i
		For i = 1 To RS.RecordCount
			If iC <= 250 Then
				tName = RS("CharName").Value
				tLevel = RS("CharLevel").Value
				tClass = RS("CharClass").Value

				If CInt(tLevel) >= CInt(Min) And CInt(tLevel) <= CInt(Max) And tClass <> "Unknown ID: 0" Then
					If Not ucase(left(tName,3)) = "GM-" Then
						gName(iC) = tName
						gLevel(iC) = tLevel
						gClass(iC) = tClass
						iC = iC + 1
					End If
				End If

				If i < RS.RecordCount Then
					RS.MoveNext
				End If
			End If
		Next

		strRankTable = "<table width=100% ><tr><td><tr><td><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strRankTable = strRankTable & i & "<BR>"
			End If
		Next
		strRankTable = strRankTable & "</td><td><strong>Class</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strRankTable = strRankTable & gClass(i) & "<BR>"
			End If
		Next
		strRankTable = strRankTable & "</td><td><strong>Character</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strRankTable = strRankTable & gName(i) & "<BR>"
			End If
		Next
		strRankTable = strRankTable & "</td><td><strong>Level</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strRankTable = strRankTable & gLevel(i) & "<BR>"
			End If
		Next
		strRankTable = strRankTable & "</td></tr></td></tr></table>"
	End If
	Response.Write(strRankTable)
	CloseConnection()
End Function
%>