<%@ Page Language="vb" AutoEventWireup="false" CodeBehind="LogReader.aspx.vb" Inherits="For_Baris.LogReader" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body style="font-family: Tahoma; font-size:12px">
    <form id="form1" runat="server">
    <div>
        <asp:Panel ID="Panel1" runat="server" style="text-align: center;color:white">
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
        <asp:Panel ID="Panel2" runat="server" style="text-align: center;color:white" 
            Visible="False">
        <table width="100%">
            <tr>
                <td>What to search for:</td>
                <td align="left"><asp:TextBox ID="TextSearch" runat="server" Width="20%"></asp:TextBox>(Its case sensitive so the Caps order matter)</td>
            </tr>
            <tr>
                <td>Search in:</td>
                <td align="left">
                    <asp:DropDownList ID="LogsList" runat="server" AutoPostBack="True">
                        <asp:ListItem Value="1">Aging logs</asp:ListItem>
                        <asp:ListItem Value="2">Mixing logs</asp:ListItem>
                        <asp:ListItem Value="4">Item logs</asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td>Date:</td>
                <td align="left"><asp:TextBox ID="TextFrom" runat="server" Width="10%"></asp:TextBox> (Change the order of Day/Month coz still bugged XD)</td>
            </tr>
            <tr>
                <td valign="top">Logs found:</td>
                <td align="left">
                    <asp:ListBox ID="ListLogs" runat="server" Height="350px" Width="1100px">
                    </asp:ListBox>
                </td>
            </tr>
            <tr>
                <td></td>
                <td>
                    <asp:Button ID="ButtonSearch" runat="server" Text="Search" />
                    <br />
                    <asp:Label ID="Label3" runat="server" ForeColor="Red"></asp:Label>
                </td>
            </tr>
        </table>
        </asp:Panel>
        <br />
    </div>
    </form>
</body>
</html>
