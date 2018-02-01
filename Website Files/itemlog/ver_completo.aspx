<%@ Page Language="VB" AutoEventWireup="false" CodeFile="ver_completo.aspx.vb" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Ver Log Completo</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <asp:Panel ID="Panel1" runat="server" BorderWidth="1px" Height="119px" Width="100%">
            &nbsp;<span style="font-family: Tahoma">Date and hour:
                <asp:Label ID="lblDataHora" runat="server"></asp:Label><br />
                &nbsp;Detailed action:
                <asp:Label ID="lblAcao" runat="server"></asp:Label><br />
                &nbsp;Item:
                <asp:Label ID="lblItem" runat="server"></asp:Label><br />
                &nbsp;Quantity:
                <asp:Label ID="lblQtd" runat="server"></asp:Label><br />
                &nbsp;Item ID:
                <asp:Label ID="lblID" runat="server"></asp:Label><br />
                &nbsp;IP:
                <asp:Label ID="lblIP" runat="server"></asp:Label></span></asp:Panel>
    
    </div>
        <br />
        <br />
        <asp:Panel ID="Panel2" runat="server" BorderWidth="1px" Height="137px" Width="100%">
            <span style="font-family: Tahoma">&nbsp;ID from 
                <asp:Label ID="lblIDDo" runat="server"></asp:Label>
                :
                <asp:Label ID="lblIDRecebedor" runat="server"></asp:Label><br />
                &nbsp;Char name 
                <asp:Label ID="lblCharDo" runat="server"></asp:Label>
                :
                <asp:Label ID="lblNomeCharRec" runat="server"></asp:Label><br />
                &nbsp;IP from 
                <asp:Label ID="lblIpDO" runat="server"></asp:Label>:
                <asp:Label ID="lblIPRec" runat="server"></asp:Label><br />
                &nbsp;Item ID:
                <asp:Label ID="lblIDItemRec" runat="server"></asp:Label><br />
                &nbsp;Total exchanged gold:
                <asp:Label ID="lblDinheiro" runat="server"></asp:Label><br />
                &nbsp;Trade action:
                <asp:Label ID="lblAcaoTroca" runat="server"></asp:Label><br />
                &nbsp;Change status:
                <asp:Label ID="lblStatus" runat="server"></asp:Label></span></asp:Panel>
    </form>
</body>
</html>
