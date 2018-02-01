<% 'Written by Sandurr
Function STrim(sString)
	Dim strSub, strSub2
	strSub2 = ""

	Dim i 
	i = 1

	Dim iLen
	iLen = Len(sString)

	While i <= iLen
		strSub = Mid(sString,i, 1)
		if strSub <> " " Then
			strSub2 = strSub2 & strSub
		Else
			STrim = strSub2
			Exit Function
		End If
		i = i + 1
	Wend
	STrim = strSub2
End Function
%>