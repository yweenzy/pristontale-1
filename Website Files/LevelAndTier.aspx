<%@ Page Language="vb" AutoEventWireup="false" CodeBehind="LevelAndTier.aspx.vb" Inherits="For_Baris.LevelAndTier" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body style="font-family: Tahoma; font-size:12px; color: #000000;">
    <form id="form1" runat="server">
    <div style="text-align: center">
    
        <asp:Panel ID="Panel2" runat="server">
        <center>
        <table>
        <tr>
        <td>
            Login:
        </td>
        <td>
                    <asp:TextBox ID="TextLogin" runat="server"></asp:TextBox>
&nbsp;<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                ControlToValidate="TextLogin" ErrorMessage="*"></asp:RequiredFieldValidator>
        </td>
        </tr>
        <tr>
        <td>
        Password:
        </td>
        <td>
            <asp:TextBox ID="TextPassword" runat="server" TextMode="Password"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" 
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
        <br />
        <asp:Panel ID="Panel1" runat="server" Enabled="False" Visible="False">
            Select your char:
            <asp:DropDownList ID="CharList" runat="server" AutoPostBack="True">
            </asp:DropDownList>
            <br />
            <asp:Button ID="ButtonMake" runat="server" Text="Make level 100 and tier 4" />
            <br />
            <asp:Label ID="Label1" runat="server" ForeColor="Red"></asp:Label>
            <br />
            <asp:Button ID="Button1" runat="server" Text="Logout" />
        </asp:Panel>
    
    </div>
    </form>
</body>
</html>
