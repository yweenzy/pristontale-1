<!-- #include file ="settings.asp" -->
<% 'Written by Sandurr
Dim userid, password, newpassword
userid = Request.Form("accountname")
password = Request.Form("password")
newpassword = Request.Form("newpassword")

if userid = "" Or password = "" Or newpassword = "" Then
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<link href="style.css" type="text/css" rel="stylesheet" media="all" />
<META http-equiv=Content-Type content="text/html; charset=unicode">
<META content="MSHTML 6.00.2900.2963" name=GENERATOR>
<title>Change Password</title>
</HEAD>
<BODY>
<P><BR>&nbsp;</P><p>
<form action="cp.asp" method="post" id=cpform name=cpform>
Account Name:<BR>
<input class="txtinput" name="accountname" maxLength=32 ><BR>
Old Password:<BR>
<input class="txtinput" name="password" maxLength=32 ><BR>
New Password:<BR>
<input class="txtinput" name="newpassword" maxLength=32 ><BR>
<input class="btn" type="submit" value="Change Password!"  id=submit1 name=submit1> 
</form></p>
</BODY>
</HTML>
<%
Else
	If InStr(userid,"'") => 1 Or InStr(password,"'") => 1 Or InStr(newpassword,"'") => 1 Then
		Response.Write("<script>alert('Please use proper characters only!')</script>")
		Response.End
	End If

	Dim dbhost, dbuser, dbpass, dbname1
	FillSettings()

	Dim QUERY, QUERY2
	Dim objRS, objConn

	Set objConn = Server.CreateObject("ADODB.Connection")
	Set objRS = Server.CreateObject("ADODB.Recordset")
	
	OpenConnection(dbname1)
	QUERY = "SELECT Passwd FROM AllGameUser WHERE userid='" & userid & "'"
	objRS.Open QUERY, objConn, 3, 1
	
	If Not objRS.RecordCount => 1 Then
		objRS.Close
		CloseConnection()
		Response.Write("<script>alert('Account does not exist!')</script>")
		Response.End
	End If

	Dim password2
	password2 = objRS("Passwd").Value

	If password <> password2 Then
		objRS.Close
		CloseConnection()
		Response.Write("<script>alert('Incorrect old password!')</script>")
		Response.End
	End If
	
	objRS.Close
	
	Dim UPDATE, GAMEUSER, UPDATE2
	GAMEUSER = ucase(left(userid,1)) & "GameUser"	
	UPDATE = "UPDATE AllGameUser SET Passwd='" & newpassword & "' WHERE userid='" & userid & "'"
	UPDATE2 = "UPDATE " & GAMEUSER & " SET Passwd='" & newpassword & "' WHERE userid='" & userid & "'"

	QUERY2 = UPDATE2
	QUERY = UPDATE
	
	objRS.Open QUERY, objConn, 3, 1
	objRS.Open QUERY2, objConn, 3, 1
	
	Set objRS = Nothing
	CloseConnection()

	Response.Write("<script>alert('Successfully changed password!')</script>")
End If
%>