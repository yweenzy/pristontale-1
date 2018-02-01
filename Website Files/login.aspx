<%@ Page Language="VB" AutoEventWireup="false" CodeFile="login.aspx.vb" Inherits="_Default" debug="true" %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Login Web System</title>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align: center">
        <span style="font-family: Tahoma">Special ID:<br />
            <asp:TextBox ID="txtLogin" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtLogin">*</asp:RequiredFieldValidator><br />
            <br />
            Special Password:<br />
            <asp:TextBox ID="txtSenha" runat="server" TextMode="Password"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtSenha">*</asp:RequiredFieldValidator><br />
            <br />
            <asp:Button ID="cmdLoga" runat="server" Text="Login" /><br />
            <br />
            <asp:Label ID="lblMsg" runat="server"></asp:Label>
        </span>
    
    </div>
    </form>
</body>
</html>
