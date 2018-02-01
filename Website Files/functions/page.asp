<% 'Written by Sandurr
Function pageRedirect(fMessage, fUrl, fContent)
	If fMessage <> "" Then
		Response.Write("<p>" & fMessage & "<meta http-equiv='refresh' content='" & fContent & ";url=" & fUrl & "'></p>")
	Else
		Response.Write("<meta http-equiv='refresh' content='" & fContent & ";url=" & fUrl & "'>")
	End If
End Function
%>