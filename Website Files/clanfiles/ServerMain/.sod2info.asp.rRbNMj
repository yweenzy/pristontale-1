<!-- #include file ="SODsettings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 1.0 NOVEMBER 2006 (Clan 2.0 SoD 1.0)

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname1, dbname2, userid, gserver, chname, index

FillSettings()

Dim strSplit, strSplit2
strSplit = Chr("&H" & "0D")
strSplit2 = Chr("&H" & "7C")

' Parameter Variables
' sod2info (userid, gserver, chname, index)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))
index = Trim(Request("index"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery

if userid = "" Or gserver = "" Or chname = ""Then
	Response.Write("Code=100")
	Response.End
End if

if index = "" Then
	Response.Write("Code=104")
	Response.End
End if

Dim QUERY, RS, objConn, strReturn, i

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname1 & "; User ID=" & dbuser & "; Password=" & dbpass
Set RS = Server.CreateObject("ADODB.Recordset")

Dim ClanIMG, ClanName, ClanPoint, ClanDate, ClanNote, ClanMoney, ClanLeader, ClanSubChief
Dim iNum, ClanSub, ClanSubLeader

Select Case index
	Case "1" 'Main Karina Page
		QUERY = "SELECT * FROM CL ORDER BY Cpoint DESC"
		RS.Open QUERY, objConn, 3, 1

		If RS.RecordCount > 0 Then
			ClanPoint = RS("Cpoint").Value
			ClanNote = RS("Note").Value
			ClanName = RS("ClanName").Value
			ClanIMG = RS("MIconCnt").Value
			ClanLeader = RS("ClanZang").Value
			ClanMoney = RS("ClanMoney").Value

			RS.Close
			QUERY = "SELECT * FROM UL WHERE chname='" & chname & "'"
			RS.Open QUERY, objConn, 3, 1

			If Not RS.RecordCount > 0 Then
				iNum = 0
				strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2
			Else
				ClanSub = RS("ClanName").Value
				ClanSubChief = RS("Permi").Value

				If ClanName = ClanSub Then
					If ClanLeader = chname Then
						iNum = 1
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=" & ClanMoney & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2 & "TotalEMoney=" & ClanMoney & strSplit2 & "TotalMoney=" & ClanMoney & strSplit2
					ElseIf ClanSubChief = 2 Then
						iNum = 2
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2 & "TotalEMoney=" & ClanMoney & strSplit2 & "TotalMoney=" & ClanMoney & strSplit2
					Else
						iNum = 3
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2 & "TotalEMoney=" & ClanMoney & strSplit2 & "TotalMoney=" & ClanMoney & strSplit2
					End If
				Else
					RS.Close
					QUERY = "SELECT ClanZang FROM CL WHERE ClanName='" & ClanSub & "'"
					RS.Open QUERY, objConn, 3, 1
					ClanSubLeader = RS("ClanZang").Value
					If ClanSubLeader = chname Then
						iNum = 4
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2
					ElseIf ClanSubChief = 2 Then
						iNum = 5
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2
					Else
						iNum = 6
						strReturn = "Code=" & iNum & strSplit2 & "CClanMoney=0" & strSplit2 & "CTax=0" & strSplit2 & "CName=" & ClanName & strSplit2 & "CNote=" & ClanNote & strSplit2 & "CZang=" & ClanLeader & strSplit2 & "CIMG=" & ClanIMG & strSplit2
					End If
					RS.Close
				End If
			End If
		Else
			strReturn = "Code=0"
		End If		
	Case "3" 'High Score Clan List
		QUERY = "SELECT * FROM CL ORDER BY Cpoint DESC"
		RS.Open QUERY, objConn, 3, 1

		If Not RS.RecordCount > 0 Then
			strReturn = "Code=0"
		Else
			Dim tSub, tSubRegiDate, tSub2, tSub3, x

			strReturn = "Code=1" & strSplit
			While i < RS.RecordCount
				If i >= 9 Then
					i = RS.RecordCount
				End If
				tSubRegiDate = ""
				tSub2 = ""
				tSub3 = 0

				ClanName = RS("ClanName").Value
				tSub = RS("RegiDate").Value
				For x = 1 To Len(tSub)
					If tSub3 = 0 Then
						tSub2 = Mid(tSub,x,1)
						If tSub2 <> " " Then
							tSubRegiDate = tSubRegiDate & tSub2
						Else
							tSub3 = 1
						End If
					End If
				Next

				If Not InStr(strReturn, ClanName) > 0 And RS("Cpoint").Value > 0 Then
					strReturn = strReturn & "CIMG=" & RS("MIconCnt").Value & strSplit & "CName=" & ClanName & strSplit & "CPoint=" & RS("Cpoint").Value & strSplit & "CRegistDay=" & tSubRegiDate & strSplit
				End If

				i = i + 1

				If i <= RS.RecordCount Then
					RS.MoveNext
				End If
			Wend 
		End If
		RS.Close
	Case Else
		strReturn = "Code=104"
		Response.Write(strReturn)
End Select

objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>