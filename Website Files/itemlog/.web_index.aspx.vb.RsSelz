Imports System.Data.SqlClient
Partial Class web_index
    Inherits System.Web.UI.Page
    Dim pwd As String = "6A6o05B"
    Dim usera As String = "Ja7Mok0"
    Dim preencheu As Boolean
    Protected Sub Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        If Session("login_adm") = "" Then
            Response.Redirect("login.aspx")
        End If
	If page.IsPostBack = False Then
            PreencheListas()
        End If
    End Sub
    Public Sub PreencheListas()
        Dim b As Integer = 0 'declara a variavel de for
        For b = 1 To 31 'dias do ano
            cmbDia.Items.Add(b)
        Next
        cmbDia.SelectedIndex = Day(Now) - 1 'seleciona o dia
        b = 0 'seta 0 para prevenir erros
        For b = 0 To 23 'horas
            If b <= 9 Then 'se for menor que 9 horas AM
                cmbHora.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbHora.Items.Add(b)
            End If
        Next
        cmbHora.SelectedIndex = Hour(Now) 'seleciona a hora
        b = 0 'seta 0 para prevenir erros
        For b = 1 To 59 'minutos
            If b <= 9 Then 'se for menor ou igual a 9 minutos
                cmbMinutos.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbMinutos.Items.Add(b)
            End If
        Next
        cmbMinutos.SelectedIndex = Minute(Now) - 1
        b = 0
        For b = 0 To 59 'segundos
            If b <= 9 Then 'se for menor ou igual a 9 minutos
                cmbSegundos.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbSegundos.Items.Add(b)
            End If
        Next
        cmbSegundos.SelectedIndex = Second(Now)
        For b = 1 To 31 'dias do ano
            cmbDia2.Items.Add(b)
        Next
        cmbDia2.SelectedIndex = Day(Now) - 1 'seleciona o dia
        b = 0 'seta 0 para prevenir erros
        For b = 0 To 23 'horas
            If b <= 9 Then 'se for menor que 9 horas AM
                cmbHora2.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbHora2.Items.Add(b)
            End If
        Next
        cmbHora2.SelectedIndex = Hour(Now) 'seleciona a hora
        b = 0 'seta 0 para prevenir erros
        For b = 1 To 59 'minutos
            If b <= 9 Then 'se for menor ou igual a 9 minutos
                cmbMinutos2.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbMinutos2.Items.Add(b)
            End If
        Next
        cmbMinutos2.SelectedIndex = Minute(Now) - 1
        b = 0
        For b = 0 To 59 'segundos
            If b <= 9 Then 'se for menor ou igual a 9 minutos
                cmbSegundos2.Items.Add("0" & b) 'adiciona um zero na frente
            ElseIf b >= 10 Then 'se for maior adiciona normal
                cmbSegundos2.Items.Add(b)
            End If
        Next
        cmbSegundos2.SelectedIndex = Second(Now)
        preencheu = True
    End Sub
    Protected Sub Page_Change(ByVal source As Object, ByVal e As System.Web.UI.WebControls.DataGridPageChangedEventArgs) Handles dg.PageIndexChanged
        dg.CurrentPageIndex = e.NewPageIndex
        BindData()
    End Sub
    Protected Sub cmbMostra_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmbMostra.Click
        BindData()
    End Sub
    Public Sub BindData()
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=ItemLogDB")
        Dim regist_day As String = cmbMes.SelectedValue.ToString + "/" + cmbDia.SelectedItem.ToString + "/" + cmbAno.SelectedItem.ToString + " " + cmbHora.SelectedItem.ToString + ":" + cmbMinutos.SelectedItem.ToString + ":" + cmbSegundos.SelectedItem.ToString
        Dim regist_day2 As String = cmbMes2.SelectedValue.ToString + "/" + cmbDia2.SelectedItem.ToString + "/" + cmbAno2.SelectedItem.ToString + " " + cmbHora2.SelectedItem.ToString + ":" + cmbMinutos2.SelectedItem.ToString + ":" + cmbSegundos2.SelectedItem.ToString
        Dim cmd As SqlCommand
        If cmbProcurapor.SelectedValue = "Char" Then
            If cmbDetalhes.SelectedValue = "None" Then
                cmd = New SqlCommand("Select * From IL Where CharName='" & txtChar.Text & "' And RegistDay Between '" & regist_day & "' And '" & regist_day2 & "'", cn)
                cmd.CommandTimeout = 0
            Else
                cmd = New SqlCommand("Select * From IL Where CharName='" & txtChar.Text & "' And RegistDay Between '" & regist_day & "' And '" & regist_day2 & "' And Flag='" & cmbDetalhes.SelectedValue.ToString & "'", cn)
                cmd.CommandTimeout = 0
            End If
        ElseIf cmbProcurapor.SelectedValue = "ID" Then
            If cmbDetalhes.SelectedValue = "None" Then
                cmd = New SqlCommand("Select * From IL Where UserID='" & txtChar.Text & "' And RegistDay Between '" & regist_day & "' And '" & regist_day2 & "'", cn)
                cmd.CommandTimeout = 0
            Else
                cmd = New SqlCommand("Select * From IL Where UserID='" & txtChar.Text & "' And RegistDay Between '" & regist_day & "' And '" & regist_day2 & "' And Flag='" & cmbDetalhes.SelectedValue.ToString & "'", cn)
                cmd.CommandTimeout = 0
            End If
        ElseIf cmbProcurapor.SelectedValue = "Codigo" Then
            Dim s() As String = Split(txtChar.Text, "@")
            If cmbDetalhes.SelectedValue = "None" Then
                cmd = New SqlCommand("Select * From IL Where ItemINo='" & s(0) & "' And ItemINo_1='" & s(1) & "'", cn)
                cmd.CommandTimeout = 0
            Else
                cmd = New SqlCommand("Select * From IL Where Where ItemINo='" & s(0) & "' And ItemINo_1='" & s(1) & "' And Flag='" & cmbDetalhes.SelectedValue.ToString & "'", cn)
                cmd.CommandTimeout = 0
            End If
        End If
        cn.Open()
        Dim da As New SqlDataAdapter
        Dim ds As New Data.DataSet
        da.SelectCommand = cmd
        da.Fill(ds)
        dg.DataSource = ds
        dg.DataBind()
        cn.Close()
    End Sub
    Public Function VerificaFlag(ByVal flag As String) As String
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
        Dim cmd As New SqlCommand("Select * from tbl_acoes Where codigo_acao='" & flag & "'", cn)
        cn.Open()
        Dim dr As SqlDataReader
        dr = cmd.ExecuteReader
        If Not dr.Read Then
            VerificaFlag = "Unknown action"
        Else
            VerificaFlag = dr("detalhe_acao")
        End If
        cn.Close()
        dr.Close()
    End Function
End Class
