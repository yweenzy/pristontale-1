<!-- #include file = "database.asp" -->
<!-- #include file = "clans.asp" -->
<font face="Verdana"><font size=2>
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

Function SoDTableClan(Results)
	If Results <= 0 Or Results > 250 Then
		Results = 250
	End If

	QUERY = "SELECT * FROM CL ORDER BY Cpoint DESC"

	Dim gIMG(250)
	Dim gName(250)
	Dim gPoints(250)

	Dim tIMG, tName, tPoints

	Dim iC, strSoDTableClan
	iC = 1

	OpenConnection(dbname2)
	RS.Open QUERY, objConn, 3, 1

	If Not RS.RecordCount >= 1 Then
		strSoDTableClan = "No clans"
	Else
		Dim i
		For i = 1 To RS.RecordCount
			If iC <= 250 Then
				tIMG = RS("MIconCnt").Value
				tName = RS("ClanName").Value
				tPoints = RS("Cpoint").Value

				If InArray(tName, gName) = False And tPoints > 0 Then
					gIMG(iC) = tIMG
					gName(iC) = tName
					gPoints(iC) = tPoints
					iC = iC + 1
				End If

				If i < RS.RecordCount Then
					RS.MoveNext
				End If
			End If
		Next

		strSoDTableClan = "<table width=100% ><tr><td><tr><td><font face=Verdana><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTableClan = strSoDTableClan & i & "<BR>"
			End If
		Next
		strSoDTableClan = strSoDTableClan & "</td><td><font face=Verdana><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTableClan = strSoDTableClan & IconPath(gIMG(i)) & "<BR>"
			End If
		Next
		strSoDTableClan = strSoDTableClan & "</td><td><strong><font face=Verdana>Clan Name</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTableClan = strSoDTableClan & gName(i) & "<BR>"
			End If
		Next
		strSoDTableClan = strSoDTableClan & "</td><td><strong><font face=Verdana>Points</strong><BR>"
		For i = 1 To (iC - 1)
			If i <= Results Then
				strSoDTableClan = strSoDTableClan & gPoints(i) & "<BR>"
			End If
		Next
		strSoDTableClan = strSoDTableClan & "</td></tr></td></tr></table></font>"
	End If
	Response.Write(strSoDTableClan)
	CloseConnection()
End Function
%>