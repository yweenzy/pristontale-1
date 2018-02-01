<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, userid, gserver, chname

Dim tTime
tTime = " ¿ÀÈÄ "

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' isClanMember (userid, gserver, chname)
userid = Trim(Request("userid"))
gserver = Trim(Request("gserver"))
chname = Trim(Request("chname"))

'sql injection stuff
Dim safeQuery
safeQuery = Replace(chname, "'","")
chname = safeQuery

if userid = "" Or gserver = "" Or chname = "" Then
	 Response.Write("Code=100" & strSplit)
	 Response.End
End if

Dim QUERY, RS, objConn

Set objConn = Server.CreateObject("ADODB.Connection")
objConn.Open "Provider=SQLOLEDB; Data Source=" & dbhost & "; Initial Catalog=" & dbname & "; User ID=" & dbuser & "; Password=" & dbpass

QUERY = "SELECT ClanName FROM UL WHERE ChName='" & chname & "'"

Set RS = Server.CreateObject("ADODB.Recordset")
RS.Open QUERY, objConn, 3, 1

if RS.RecordCount = 0 Then
	 RS.Close
	 Set RS = Nothing
	 objConn.Close
	 Set objConn = Nothing
	 Response.Write("Code=0" & strSplit & "CMoney=500000" & strSplit & "CNFlag=0" & strSplit)
	 Response.End
End if

Dim clname
clname = RS("ClanName").Value
if clname = "" Then
	 RS.Close
	 QUERY = "DELETE FROM UL WHERE ChName='" & chname & "'"
	 RS.Open QUERY, objConn, 3, 1
	 Set RS = Nothing
	 objConn.Close
	 Set objConn = Nothing
	 Response.Write("Code=0" & strSplit & "CMoney=500000" & strSplit & "CNFlag=0" & strSplit)
	 Response.End
End if

RS.Close
QUERY = "SELECT ClanZang,MemCnt,Note,MIconCnt,RegiDate,LimitDate,PFlag,KFlag,ClanMoney,MIconCnt FROM CL WHERE ClanName='" & clname & "'"
RS.Open QUERY, objConn, 3, 1

if RS.RecordCount = 0 Then
	 RS.Close
	 QUERY = "DELETE FROM UL WHERE ChName='" & chname & "'"
	 RS.Open QUERY, objConn, 3, 1
	 Set RS = Nothing
	 objConn.Close
	 Set objConn = Nothing
	 Response.Write("Code=0" & strSplit & "CMoney=500000" & strSplit & "CNFlag=0" & strSplit)
	 Response.End
End if

Dim ClanLeader, ClanMembers, ClanNote, ClanIMG, CreateDate, ClanSubChief, EndDate, PFlag, KFlag, ClanMoney, iIMG
ClanLeader = RS("ClanZang").Value
ClanMembers = RS("MemCnt").Value
ClanNote = RS("Note").Value
ClanIMG = RS("MIconCnt").Value
CreateDate = RS("RegiDate").Value
EndDate = RS("LimitDate").Value
PFlag = RS("PFlag").Value
KFlag = RS("KFlag").Value
ClanMoney = RS("ClanMoney").Value
iIMG = RS("MIconCnt").Value

Dim strReturn

RS.Close

QUERY = "SELECT ClanName,Cpoint FROM CL ORDER BY Cpoint DESC"
RS.Open QUERY, objConn, 3, 1

Dim tclName, CNFlag
Dim Pontos, Rows, i

If RS.RecordCount > 0 Then
	 Rows = RS.RecordCount
	 For i = 1 To Rows
		 RS.AbsolutePosition = i
		 tclName = RS("ClanName").Value
		 Pontos = RS("Cpoint").Value
		 If (tclName = clname) Then
			 If Pontos > 0 Then
				 Select Case i
					 Case 1
						 CNFlag = 1
						 Exit For
					 Case 2
						 CNFlag = 2
						 Exit For
					 Case 3
						 CNFlag = 3
						 Exit For
					 Case Else
						 CNFlag = 0
						 Exit For
				 End Select
			 Else
				 CNFlag = 0
			 End If
		 End If
	 Next
	 RS.Close
End If

Dim tSubDate, tSubTime, y, tSub, tSub2
For y = 1 To Len(CreateDate)
	 tSub = Mid(CreateDate,y,1)
	 If tSub2 = 0 Then
		 If Not tSub = " " Then
			 tSubDate = tSubDate & tSub
		 Else
			 tSub2 = 1
		 End If
	 Else
		 If tSub2 = 1 Then
			 If Not tSub = " " Then
				 tSubTime = tSubTime & tSub
			 Else
				 tSub2 = 2
			 End If
		 End If
	 End If
Next

CreateDate = tSubDate & tTime & tSubTime
y = 1
tSub = ""
tSub2 = 0
tSubDate = ""
tSubTime = ""

For y = 1 To Len(EndDate)
	 tSub = Mid(EndDate,y,1)
	 If tSub2 = 0 Then
		 If Not tSub = " " Then
			 tSubDate = tSubDate & tSub
		 Else
			 tSub2 = 1
		 End If
	 Else
		 If tSub2 = 1 Then
			 If Not tSub = " " Then
				 tSubTime = tSubTime & tSub
			 Else
				 tSub2 = 2
			 End If
		 End If
	 End If
Next

EndDate = tSubDate & tTime & tSubTime

QUERY = "SELECT ChName FROM UL WHERE ClanName='" & clname & "' AND Permi=2"
RS.Open QUERY, objConn, 3, 1

If RS.RecordCount = 0 Then
	 ClanSubChief = ""
Else
	 ClanSubChief = RS("ChName").Value
End If

If ClanLeader = chname Then
	 if ClanSubChief = "" Then
		 strReturn = "Code=2" & strSplit & "CName=" & clname & strSplit & "CNote=" & ClanNote & strSplit & "CZang=" & ClanLeader & strSplit & "CStats=1" & strSplit & "CMCnt=" & ClanMembers & strSplit & "CIMG=" & ClanIMG & strSplit & "CSec=60" & strSplit & "CRegiD=" & CreateDate & strSplit & "CLimitD=" & EndDate & strSplit & "CDelActive=0" & strSplit & "CPFlag=" & PFlag & strSplit & "CKFlag=" & KFlag & strSplit & "CMoney=" & ClanMoney & strSplit & "CNFlag=" & CNFlag & strSplit
	 Else
		 strReturn = "Code=2" & strSplit & "CName=" & clname & strSplit & "CNote=" & ClanNote & strSplit & "CZang=" & ClanLeader & strSplit & "CSubChip=" & ClanSubChief & strSplit & "CStats=1" & strSplit & "CMCnt=" & ClanMembers & strSplit & "CIMG=" & ClanIMG & strSplit & "CSec=60" & strSplit & "CRegiD=" & CreateDate & strSplit & "CLimitD=" & EndDate & strSplit & "CDelActive=0" & strSplit & "CPFlag=" & PFlag & strSplit & "CKFlag=" & KFlag & strSplit & "CMoney=" & ClanMoney & strSplit & "CNFlag=" & CNFlag & strSplit
	 End if
Else
	 if ClanSubChief = "" Then
		 strReturn = "Code=1" & strSplit & "CName=" & clname & strSplit & "CNote=" & ClanNote & strSplit & "CZang=" & ClanLeader & strSplit & "CStats=1" & strSplit & "CMCnt=" & ClanMembers & strSplit & "CIMG=" & ClanIMG & strSplit & "CSec=60" & strSplit & "CRegiD=" & CreateDate & strSplit & "CLimitD=" & EndDate & strSplit & "CDelActive=0" & strSplit & "CPFlag=0" & strSplit & "CKFlag=0" & strSplit & "CMoney=" & ClanMoney & strSplit & "CNFlag=" & CNFlag & strSplit
	 Else
		 strReturn = "Code=1" & strSplit & "CName=" & clname & strSplit & "CNote=" & ClanNote & strSplit & "CZang=" & ClanLeader & strSplit & "CSubChip=" & ClanSubChief & strSplit & "CStats=1" & strSplit & "CMCnt=" & ClanMembers & strSplit & "CIMG=" & ClanIMG & strSplit & "CSec=60" & strSplit & "CRegiD=" & CreateDate & strSplit & "CLimitD=" & EndDate & strSplit & "CDelActive=0" & strSplit & "CPFlag=0" & strSplit & "CKFlag=0" & strSplit & "CMoney=" & ClanMoney & strSplit & "CNFlag=" & CNFlag & strSplit
	 End if
End if

RS.Close

If ClanSubChief = chname Then
	 If Not ClanLeader = chname Then
		 strReturn = "Code=5" & strSplit & "CName=" & clname & strSplit & "CNote=" & ClanNote & strSplit & "CZang=" & ClanLeader & strSplit & "CSubChip=" & ClanSubChief & strSplit & "CStats=1" & strSplit & "CMCnt=" & ClanMembers & strSplit & "CIMG=" & ClanIMG & strSplit & "CSec=60" & strSplit & "CRegiD=" & CreateDate & strSplit & "CLimitD=" & EndDate & strSplit & "CDelActive=0" & strSplit & "CPFlag=" & PFlag & strSplit & "CKFlag=" & KFlag & strSplit & "CMoney=" & ClanMoney & strSplit & "CNFlag=" & CNFlag & strSplit
	 End If
End if

QUERY = "UPDATE UL SET MIconCnt='" & iIMG & "' WHERE ChName='" & chname & "'"
RS.Open QUERY, objConn, 3, 1

Set RS = Nothing
objConn.Close
Set objConn = Nothing

Response.Write(strReturn)
%>