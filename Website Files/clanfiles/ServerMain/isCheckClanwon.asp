<!-- #include file ="settings.asp" -->
<%
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Written By Sandurr COPYRIGHT Sandurr 2006
'Version 2.0 NOVEMBER 2006

' Assign Global Variables
Dim dbhost, dbuser, dbpass, dbname, clwon, gserver

FillSettings()

Dim strSplit
strSplit = Chr("&H" & "0D")

' Parameter Variables
' isCheckClanwon (clwon, gserver)
clwon = Trim(Request("clwon"))
gserver = Trim(Request("gserver"))

if clwon = "" Or gserver = "" Then
	Response.Write("Code=100" & strSplit)
	Response.End
End if

Dim strReturn
strReturn = "Code=1" & strSplit

Response.Write(strReturn)
%>