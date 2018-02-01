<!-- #include file = "database.asp" -->

<% 'Written by Sandurr
DBSettings()

Function InArray(What, TheArray)
	Dim iArray

	For iArray = 1 To 250
		If TheArray(iArray) = What Then
			InArray = True
			Exit Function
		End If
	Next
	InArray = False
End Function

Function SoDTablePersonal(Results, ChType)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ChType, "'","")
	ChType = safeQuery

	If Results <= 0 Or Results > 250 Then
		Results = 250
	End If

	If ChType="" Then
		QUERY = "SELECT * FROM SoD2RecBySandurr ORDER BY Point DESC"
	Else
		QUERY = "SELECT * FROM SoD2RecBySandurr WHERE CharType='" & GetCharTypeInt(ChType) & "' ORDER BY Point DESC"
	End If

	Dim gName(250)
	Dim gLevel(250)
	Dim gPoints(250)
	Dim gKills(250)
	Dim gClass(250)

	Dim tName, tLevel, tPoints, tKills, tClass

	Dim iC, strSoDTablePersonal
	iC = 1

	OpenConnection(dbname3)
	RS.Open QUERY, objConn, 3, 1

	If Not RS.RecordCount >= 1 Then
		strSoDTablePersonal = "No scores"
	Else
		Dim i
		For i = 1 To RS.RecordCount
			If iC <= 250 Then
				tName = RS("CharName").Value
				tLevel = RS("GLevel").Value
				tPoints = RS("Point").Value
				tKills = RS("KillCount").Value
				tClass = GetCharType(RS("CharType").Value)

				If InArray(tName, gName) = False And tPoints > 0 Then
					If Not ucase(left(tName,3)) = "GM-" Then
						gName(iC) = tName
						gLevel(iC) = tLevel
						gPoints(iC) = tPoints
						gKills(iC) = tKills
						gClass(iC) = tClass
						iC = iC + 1
					End If
				End If

				If i < RS.RecordCount Then
					RS.MoveNext
				End If
			End If
		Next

		strSoDTablePersonal = "<table width=100% ><tr><td><tr><td><font face=Verdana><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & i & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td><td><font face=Verdana><strong>Class</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & gClass(i) & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td><td><font face=Verdana><strong>Character</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & gName(i) & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td><td><font face=Verdana><strong>Points</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & gPoints(i) & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td><td><font face=Verdana><strong>Kills</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & gKills(i) & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td><td><font face=Verdana><strong>Level</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTablePersonal = strSoDTablePersonal & gLevel(i) & "<BR>"
			End If
		Next
		strSoDTablePersonal = strSoDTablePersonal & "</td></tr></td></tr></font></table>"
	End If
	Response.Write(strSoDTablePersonal)
	CloseConnection()
End Function
%>