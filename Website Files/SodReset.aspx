<%@ Page Language="vb" AutoEventWireup="false" CodeBehind="SodReset.aspx.vb" Inherits="For_Baris.SodReset" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body style="font-family: Tahoma; font-size:12px;">
    <form id="form1" runat="server">
    <div>
    <asp:Panel ID="Panel1" runat="server" style="text-align: center">
        <center>
        <table>
            <tr>
            <td>
            Login:
            </td>
            <td>
            <asp:TextBox ID="TextLogin" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" 
                ControlToValidate="TextLogin" ErrorMessage="*"></asp:RequiredFieldValidator>
            </td>
            </tr>
            <tr>
            <td>
             Password:
            </td>
            <td>
            <asp:TextBox ID="TextPassword" runat="server" TextMode="Password"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" 
                ControlToValidate="TextPassword" ErrorMessage="*"></asp:RequiredFieldValidator>
            </td>
             </tr>
        </table>
            </center>
            
            <asp:Button ID="ButtonLogin" runat="server" Text="Login" />
            <br />
            <asp:Label ID="Label2" runat="server" ForeColor="Red"></asp:Label>
        </asp:Panel>
        <br />
        <asp:Panel ID="Panel2" runat="server" style="text-align: center" 
            Visible="False">
            <asp:Button ID="ButtonReset" runat="server" Text="Reset SOD" />
            <br />
            <asp:Label ID="Label3" runat="server" ForeColor="Red"></asp:Label>
            <br />
            <br />
            <asp:Button ID="Button1" runat="server" Text="Logout" />
        </asp:Panel>
        <br />

    </div>
    </form>
</body>
</html>
