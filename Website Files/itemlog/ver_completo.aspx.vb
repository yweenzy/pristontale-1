Imports System.Data.SqlClient
Partial Class _Default
    Inherits System.Web.UI.Page
    Dim pwd As String = "6A6o05B"
    Dim usera As String = "Ja7Mok0"
    Protected Sub Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
	If Session("login_adm") = "" Then
	    Response.Redirect("http://www.pudim.com.br")
	End If
	Try
	        Dim flag As String
	        Dim item_code As String
	        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=ItemLogDB")
	        Dim cn2 As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
	        Dim cmd As New SqlCommand("Select * from IL Where ITEMNo='" & Request.QueryString("id") & "'", cn)
		cmd.CommandTimeout = 0
	        cn.Open()
	        Dim dr As SqlDataReader
	        dr = cmd.ExecuteReader
	        dr.Read()
	        lblDataHora.Text = dr("RegistDay")
	        lblAcao.Text = VerificaFlag(dr("Flag"))
	        lblItem.Text = VerificaItem(dr("ItemCode"))
	        lblQtd.Text = dr("ItemCount")
	        lblID.Text = dr("ItemINo") & "@" & dr("ItemINo_1")
	        lblIP.Text = dr("IP")
	        If dr("Flag") = "8" Then
                lblIDDo.Text = "receiver"
                lblCharDo.Text = "receiver"
                lblIpDO.Text = "receiver"
	            lblIDRecebedor.Text = dr("TUserID")
	            lblNomeCharRec.Text = dr("TCharName")
	            lblIPRec.Text = dr("TIP")
	            lblIDItemRec.Text = lblItem.Text
	            lblDinheiro.Text = dr("TMoney")
                lblAcaoTroca.Text = "Gave a item on trade"
                lblStatus.Text = "Completed trade"
	        ElseIf dr("Flag") = "2" Then
                lblIDDo.Text = "sender"
                lblCharDo.Text = "sender"
                lblIpDO.Text = "sender"
        	    lblIDRecebedor.Text = dr("TUserID")
	            lblNomeCharRec.Text = dr("TCharName")
        	    lblIPRec.Text = dr("TIP")
	            lblIDItemRec.Text = lblItem.Text
	            lblDinheiro.Text = dr("TMoney")
                lblAcaoTroca.Text = "Gave a item on trade"
                lblStatus.Text = "Completed trade"
		Else
		    lblIDdo.Text = "char"
		    lblCharDo.Text = "char"
		    lblNomeCharRec.Text = dr("CharName")
		    lblIDRecebedor.Text = dr("UserID")
		    lblIPRec.Text = dr("IP")
	        End If
	Catch ex As Exception
		Response.Write(ex.Message)
	End Try
	    End Sub
    Private Function VerificaFlag(ByVal strFlag As String) As String
	On Error Resume Next
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
        Dim cmd As New SqlCommand("Select detalhe_acao, codigo_acao From tbl_acoes Where codigo_acao='" & strFlag & "'", cn)
        Dim dr As SqlDataReader
	cn.Open()
        dr = cmd.ExecuteReader
        dr.Read()
	Return dr("detalhe_acao")
	cn.Close()
        dr.Close()
    End Function
    Public Function VerificaItem(ByVal strItemCode As String) As String
	On Error Resume Next
        Dim cn As New SqlConnection("server=J4YM0KO-PQ\SQLEXPRESS;uid='" & usera & "';pwd='" & pwd & "';database=WebSystemDB")
        Dim cmd As New SqlCommand("Select nome_item,codigo_item From tbl_itens Where codigo_item='" & strItemCode & "'", cn)
        Dim dr As SqlDataReader
	cn.Open()
        dr = cmd.ExecuteReader
        dr.Read()
        If String.IsNullOrEmpty(dr("nome_item")) Then
            VerificaItem = "Unknown item"
        Else
            VerificaItem = dr("nome_item")
        End If
        cn.Close()
        dr.Close()
    End Function
End Class
