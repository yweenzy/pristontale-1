Imports System.IO
Imports System.Data.SqlClient
Partial Class verifica_delimitador
    Inherits System.Web.UI.Page
    Dim pwd As String = "6A6o05B"
    Dim usera As String = "Ja7Mok0"
    Protected Sub Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        'On Error Resume Next
        Dim a
        a = Split(System.IO.File.OpenText("C:\Inetpub\wwwroot\itens_db.txt").ReadToEnd(), vbCrLf)
        Dim i As Integer
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
        cn.Open()
        For i = 0 To UBound(a) Step 2
            Response.Write("Insert Into tbl_itens (nome_item,codigo_item) values('" & a(i) & "','" & a(i + 1) & "')" & "<Br>")
            Dim cmd As New SqlCommand("Insert Into tbl_itens (nome_item,codigo_item) values('" & a(i) & "','" & a(i + 1) & "')", cn)
            cmd.ExecuteNonQuery()
        Next
        cn.Close()
        cn.Dispose()
    End Sub
End Class
