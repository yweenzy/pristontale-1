<% 'Written by Sandurr
Function Injection(iStrings, strArray)
	Dim iInjection
	For iInjection = 1 To iStrings
		If InStr(strArray(iInjection),"'") => 1 Then
			Injection = True
		End If
	Next
End Function
%>