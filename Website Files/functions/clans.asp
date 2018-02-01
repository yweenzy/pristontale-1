<!-- #include file = "database.asp" -->

<% 'Written by Sandurr
DBSettings()

Function IconPath(Icon)
	IconPath = "<img src=ClanContent/" & Icon & ".bmp width=12px height=12px>"
End Function

Function ClanTable(Results)
	If Results <= 0 Then
		Results = 250
	End If

	Dim gIcon(250)
	Dim gName(250)
	Dim gLeader(250)
	Dim gMembers(250)

	Dim iC, strClanTable

	QUERY = "SELECT * FROM CL ORDER BY MemCnt DESC"

	OpenConnection(dbname2)
	RS.Open QUERY, objConn, 3, 1

	If Not RS.RecordCount >= 1 Then
		strClanTable = "No clans"
	Else
		Dim i
		For i = 1 To RS.RecordCount
			gIcon(i) = RS("MIconCnt").Value
			gName(i) = RS("ClanName").Value
			gLeader(i) = RS("ClanZang").Value
			gMembers(i) = RS("MemCnt").Value

			If i < RS.RecordCount Then
				RS.MoveNext
			End If

			iC = i
		Next

		strClanTable = "<table width=100% ><tr><td><tr><td><font face=Verdana><BR>"
		For i = 1 To iC
			If i <= Results Then
				strClanTable = strClanTable & i & "<font face=Verdana><BR>"
			End If
		Next
		strClanTable = strClanTable & "</td><font face=Verdana><td><BR>"
		For i = 1 To iC
			If i <= Results Then
				strClanTable = strClanTable & IconPath(gIcon(i)) & "<BR>"
			End If
		Next
		strClanTable = strClanTable & "</td><td><strong><font face=Verdana>Clan</strong><BR>"
		For i = 1 To iC
			If i <= Results Then
				strClanTable = strClanTable & gName(i) & "<BR>"
			End If
		Next
		strClanTable = strClanTable & "</td><td><strong><font face=Verdana>Members</strong><BR>"
		For i = 1 To iC
			If i <= Results Then
				strClanTable = strClanTable & gMembers(i) & "<BR>"
			End If
		Next
		strClanTable = strClanTable & "</td></tr></td></tr></table></font>"
	End If
	Response.Write(strClanTable)
	CloseConnection()
End Function
%>