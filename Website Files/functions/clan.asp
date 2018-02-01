<% 'Written by Sandurr
Function YouOutput()
	Dim strReturn
	strReturn = "<table width=100% ><tr><td><p align=center><B><font face=Verdana>Logged in as</B>: " & userid & "<BR></font>"
	strReturn = strReturn & "<B><font face=Verdana>Character</B>: " & chname & "</font><BR><BR>"
	strReturn = strReturn & "<B><font face=Verdana>Rank</B>: " & GetRank(chname) & "</font></p></td></tr></table><BR>"

	Response.Write(strReturn)
End Function

Function ClanManage()
	Dim strReturn

	strReturn = "<img src=ClanContent/" & ClanIMG & ".bmp width=24px height=24px />   <strong>" & ClanName & "</strong><BR>"
	strReturn = strReturn & " <strong> <font size=1>Clan Note:</strong> <U>" & ClanNote & "</U>"
	
	If IsClanLeader(chname) = True Then
		strReturn = strReturn & "<form action=clan.asp method=post><input name=userid type=text value=" & userid & " style=VISIBILITY:hidden><input name=passwd type=text value=" & passwd & " style=VISIBILITY:hidden><input name=chname type=text value=" & chname & " style=VISIBILITY:hidden><BR>"
		strReturn = strReturn & "<input name=Note type=Submit Class=btn value='Update Note'> <input name=Icon type=Submit Class=btn Value='Update Icon'></form>"
	Else
		strReturn = strReturn & "<BR><BR>"
	End If

	Response.Write(strReturn)
End Function

Function MemberTable()
	Dim strReturn

	strReturn = "<B>Member List:</B><BR><table width=100% ><tr><td><tr><td>"
	
	Dim gRank(200), gName(200), gClass(200), gLevel(200)
	Dim tRank, tName, tClass, tLevel

	gRank(1) = GetRank(ClanLeader)
	gName(1) = ClanLeader
	gRanK(2) = GetRank(ClanSubChief)
	gName(2) = ClanSubChief

	OpenConnection(dbname2)

	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(ClanName, "'","")
	ClanName = safeQuery

	QUERY = "SELECT * FROM UL WHERE ClanName='" & ClanName & "'"
	RS.Open QUERY, objConn, 3, 1

	Dim iSub
	If gName(2) = "" Then
		iSub = 2
	Else
		iSub = 3
	End If

	If Not RS.RecordCount >= 1 Then
		strReturn = strReturn & "Error No Members In Clan!</td></tr></td></tr></table>"
	Else
		Dim i
		For i = 1 To RS.RecordCount
			tName = RS("ChName").Value
			tClass = GetCharType(RS("ChType").Value)
			tLevel = RS("ChLv").Value
			tRank = GetRank(tName)

			If tName = ClanLeader Then
				gClass(1) = tClass
				gLevel(1) = tLevel
			ElseIf tName = ClanSubChief Then
				gClass(2) = tClass
				gLevel(2) = tLevel
			Else
				gRank(iSub) = tRank
				gName(iSub) = tName
				gClass(iSub) = tClass
				gLevel(iSub) = tLevel

				iSub = iSub + 1
			End If

			If i < RS.RecordCount Then
				RS.MoveNext
			End If
		Next
		
		strReturn = strReturn & "<strong><font face=Verdana>Rank</strong><BR>"
		For i = 1 To (iSub - 1)
			strReturn = strReturn & gRank(i) & "<BR>"
		Next
		strReturn = strReturn & "</td><td><strong><font face=Verdana>Character</strong><BR>"
		For i = 1 To (iSub - 1)
			strReturn = strReturn & gName(i) & "<BR>"
		Next
		strReturn = strReturn & "</td><td><strong><font face=Verdana>Class</strong><BR>"
		For i = 1 To (iSub - 1)
			strReturn = strReturn & gClass(i) & "<BR>"
		Next
		strReturn = strReturn & "</td><td><strong><font face=Verdana>Level</strong><BR>"
		For i = 1 To (iSub - 1)
			strReturn = strReturn & gLevel(i) & "<BR>"
		Next
		strReturn = strReturn & "</td></tr></td></tr></font></table>"
	End If

	CloseConnection()
	Response.Write(strReturn)
End Function

Function NoteForm()
	Dim strReturn

	strReturn = "<form action=clan.asp method=post><input name=userid type=text value=" & userid & " style=VISIBILITY:hidden><input name=passwd type=text value=" & passwd & " style=VISIBILITY:hidden><input name=chname type=text value=" & chname & " style=VISIBILITY:hidden><BR>"
	strReturn = strReturn & "<input type=text class=txtinput name=nNote><BR><BR>"
	strReturn = strReturn & "<input type=Submit class=btn value='Update Note'></form>"

	Response.Write(strReturn)
End Function

Function IconForm()
	Dim strReturn

	Response.Cookies("userid") = userid
	Response.Cookies("MIconCnt") = ClanIMG

	strReturn = "<p><a href='#' onclick=window.open('uploadTester.asp?MIconCnt=" & ClanIMG & "&userid=" & userid & "','','height=280,width=514')><font face=Verdana>Upload File</a></p></font><BR>"
	strReturn = strReturn & "<form action=clan.asp method=post><input name=userid type=text value=" & userid & " style=VISIBILITY:hidden><input name=passwd type=text value=" & passwd & " style=VISIBILITY:hidden><input name=chname type=text value=" & chname & " style=VISIBILITY:hidden><BR>"
	strReturn = strReturn & "<input name=Back type=Submit Class=btn value='Back'></form>"

	Response.Write(strReturn)
End Function

Function SelectClanChar()
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(userid, "'","")
	userid = safeQuery

	OpenConnection(dbname2)
	QUERY = "SELECT ChName FROM UL WHERE userid='" & userid & "'"

	Dim i
	i = 1

	RS.Open QUERY, objConn, 3, 1

	Dim strReturn, tName

	If Not RS.RecordCount >= 1 Then
		strReturn = "<B>No characters in clan</B>"
	Else
		strReturn = "<form action=clan.asp method=post><input name=userid type=text value=" & userid & " style=VISIBILITY:hidden><input name=passwd type=text value=" & passwd & " style=VISIBILITY:hidden><BR>"
		strReturn = strReturn & "<SELECT ID=ChName Name=ChName>"

		For i = 1 To RS.RecordCount
			tName = RS("ChName").Value
			strReturn = strReturn & "<OPTION>" & tName & "</OPTION>"

			If i < RS.RecordCount Then
				RS.MoveNext
			End If
		Next

		strReturn = strReturn & "</SELECT><BR><BR>"
		strReturn = strReturn & "<input type=Submit class=btn Value=Continue></form>"
	End If
	CloseConnection()
	Response.Write(strReturn)
End Function

Function LoginClan()
%>
<form action="clan.asp" method="post">Account Name:<BR><input type="text" class="txtbox" value="" name="userid"><BR>
<BR>Password:<BR><input type="password" class="txtbox" value="" name="passwd"><BR><BR>
<input type="Submit" value="Login" class="btn"></form>
<%
End Function
%>