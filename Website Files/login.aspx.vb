Imports System.Data.SqlClient
Imports ClsCrypto
Partial Class _Default
    Inherits System.Web.UI.Page
    Dim pwd As String = "6A6o05B"
    Dim usera As String = "Ja7Mok0"
    Protected Sub cmdLoga_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmdLoga.Click
        txtLogin.Text = Replace(txtLogin.Text, "'", "")
        txtSenha.Text = Replace(txtSenha.Text, "'", "")
        Dim cifrado As New ClsCrypto()
        Dim login_cifrado As String = cifrado.clsCrypto(txtLogin.Text, True)
        Dim senha_cifrada As String = cifrado.clsCrypto(txtSenha.Text, True)
'	Response.Write(login_cifrado & "<Br>")
'	Response.Write(senha_cifrada)
'	Exit Sub
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
        Dim cmd As New SqlCommand("Select login,senha From tbl_admins Where login='" & cifrado.clsCrypto(login_cifrado, False) & "' And senha='" & cifrado.clsCrypto(senha_cifrada, False) & "'", cn)
        cn.Open()
        Dim dr As SqlDataReader
        dr = cmd.ExecuteReader
	dr.Read()
        If dr.HasRows = False Then
            lblMsg.Text = "<font color=red>You are not allowed to log in!</font>"
        Else
            Session("login_adm") = txtLogin.Text
            Response.Redirect("web_index.aspx")
        End If
        cn.Close()
        dr.Close()
        'cn.Dispose()
    End Sub
End Class
