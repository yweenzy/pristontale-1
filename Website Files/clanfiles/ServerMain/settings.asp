<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

Sub FillSettings()
	dbhost = "MorrKadoch\SQLEXPRESS"
            dbuser = "sa"
            dbpass = "kadoch"
	dbname = "ClanDB"
End Sub

Sub CheckTicket(useridcheck, ticketcheck)
	'sql injection stuff
	Dim safeQuery
	safeQuery = Replace(useridcheck, "'","")
	useridcheck = safeQuery

	QUERY = "SELECT SNo FROM CT WHERE UserID='" & useridcheck & "' AND ServerName='" & gserver & "'"
	RS.Open QUERY, objConn, 3, 1

	Dim tticket

	If RS.RecordCount >= 1 Then
		tticket = RS("SNo").Value
		If CInt(ticketcheck) = CInt(tticket) Then
			RS.Close
		Else
			RS.Close
			Set RS = Nothing
			objConn.Close
			Set objConn = Nothing
			Response.Write("Code=100" & strSplit)
			Response.End
		End If
	Else
		RS.Close
		Set RS = Nothing
		objConn.Close
		Set objConn = Nothing
		Response.Write("Code=100" & strSplit)
		Response.End
	End If
End Sub
%>