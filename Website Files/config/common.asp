<% 'Written by Sandurr
Function Common()
Dim gText, gFileSystemObject, gFile
Dim gMenu

Set gFileSystemObject=Server.CreateObject("Scripting.FileSystemObject")
Set gFile=gFileSystemObject.OpenTextFile(Server.MapPath("news.txt"), 1)

Do While gFile.AtEndOfStream = False
	gText = gText & gFile.ReadLine
Loop

gFile.Close
Set gFile=Nothing

Set gFile=gFileSystemObject.OpenTextFile(Server.MapPath("menu.txt"), 1)

Do While gFile.AtEndOfStream = False
	gMenu = gMenu & gFile.ReadLine
Loop

gFile.Close
Set gFile=Nothing
Set gFileSystemObject=Nothing
%>
<%
End Function
%>