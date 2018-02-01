<%@ Page Language="VB" AutoEventWireup="false" CodeFile="web_index.aspx.vb" Inherits="web_index" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Web Index System</title>
</head>
<script language="JavaScript">
<!--
function na_open_window(name, url, left, top, width, height, toolbar, menubar, statusbar, scrollbar, resizable)
{
  toolbar_str = toolbar ? 'yes' : 'no';
  menubar_str = menubar ? 'yes' : 'no';
  statusbar_str = statusbar ? 'yes' : 'no';
  scrollbar_str = scrollbar ? 'yes' : 'no';
  resizable_str = resizable ? 'yes' : 'no';
  window.open(url, name,'left='+left+',top='+top+',width='+width+',height='+height+',toolbar='+toolbar_str+',menubar='+menubar_str+',status='+statusbar_str+',scrollbars='+scrollbar_str+',resizable='+resizable_str);
}

// -->
</script>
<BODY LINK=WHITE ALINK=WHITE VLINK=WHITE>
    <form id="form1" runat="server">
        <span style="font-family: Tahoma">
            <asp:Panel ID="Panel1" runat="server" BorderWidth="1px" Height="176px" Width="100%">
                <br />
                &nbsp;Char or ID:
                <asp:TextBox ID="txtChar" runat="server" Width="284px"></asp:TextBox>
                &nbsp;<asp:DropDownList ID="cmbProcurapor" runat="server">
                    <asp:ListItem Selected="True" Value="ID">Search for UserID</asp:ListItem>
                    <asp:ListItem Value="Char">Search for Character Name</asp:ListItem>
                    <asp:ListItem Value="Codigo">Search for Item code</asp:ListItem>
                </asp:DropDownList><br />
                &nbsp;Dates to be searched:<br />
                &nbsp;From:
                <asp:DropDownList ID="cmbDia" runat="server" Width="43px">
                </asp:DropDownList>
                .
                <asp:DropDownList ID="cmbMes" runat="server">
                    <asp:ListItem Value="1">January</asp:ListItem>
                    <asp:ListItem Value="2">February</asp:ListItem>
                    <asp:ListItem Value="3">March</asp:ListItem>
                    <asp:ListItem Value="4">April</asp:ListItem>
                    <asp:ListItem Value="5">May</asp:ListItem>
                    <asp:ListItem Value="6">June</asp:ListItem>
                    <asp:ListItem Value="7">July</asp:ListItem>
                    <asp:ListItem Value="8">August</asp:ListItem>
                    <asp:ListItem Value="9">September</asp:ListItem>
                    <asp:ListItem Value="10">October</asp:ListItem>
                    <asp:ListItem Value="11">November</asp:ListItem>
                    <asp:ListItem Value="12">December</asp:ListItem>
                </asp:DropDownList>
                .
                <asp:DropDownList ID="cmbAno" runat="server">
                    <asp:ListItem>2012</asp:ListItem>
                    <asp:ListItem>2013</asp:ListItem>
                    <asp:ListItem>2014</asp:ListItem>
                    <asp:ListItem>2015</asp:ListItem>
                    <asp:ListItem>2016</asp:ListItem>
                    <asp:ListItem>2017</asp:ListItem>
                    <asp:ListItem>2018</asp:ListItem>
                    <asp:ListItem>2019</asp:ListItem>
                    <asp:ListItem>2020</asp:ListItem>
                    <asp:ListItem>2021</asp:ListItem>
                    <asp:ListItem>2022</asp:ListItem>
                </asp:DropDownList>
                -
                <asp:DropDownList ID="cmbHora" runat="server">
                </asp:DropDownList>
                :
                <asp:DropDownList ID="cmbMinutos" runat="server">
                </asp:DropDownList>
                :<asp:DropDownList ID="cmbSegundos" runat="server">
                </asp:DropDownList> GMT+1<br />
                &nbsp;Till:&nbsp; &nbsp; <asp:DropDownList ID="cmbDia2" runat="server" Width="43px">
                </asp:DropDownList>
                .
                <asp:DropDownList ID="cmbMes2" runat="server">
                    <asp:ListItem Value="1">January</asp:ListItem>
                    <asp:ListItem Value="2">February</asp:ListItem>
                    <asp:ListItem Value="3">March</asp:ListItem>
                    <asp:ListItem Value="4">April</asp:ListItem>
                    <asp:ListItem Value="5">May</asp:ListItem>
                    <asp:ListItem Value="6">June</asp:ListItem>
                    <asp:ListItem Value="7">July</asp:ListItem>
                    <asp:ListItem Value="8">August</asp:ListItem>
                    <asp:ListItem Value="9">September</asp:ListItem>
                    <asp:ListItem Value="10">October</asp:ListItem>
                    <asp:ListItem Value="11">November</asp:ListItem>
                    <asp:ListItem Value="12">December</asp:ListItem>
                </asp:DropDownList>
                .
                <asp:DropDownList ID="cmbAno2" runat="server">
                    <asp:ListItem>2012</asp:ListItem>
                    <asp:ListItem>2013</asp:ListItem>
                    <asp:ListItem>2014</asp:ListItem>
                    <asp:ListItem>2015</asp:ListItem>
                    <asp:ListItem>2016</asp:ListItem>
                    <asp:ListItem>2017</asp:ListItem>
                    <asp:ListItem>2018</asp:ListItem>
                    <asp:ListItem>2019</asp:ListItem>
                    <asp:ListItem>2020</asp:ListItem>
                    <asp:ListItem>2021</asp:ListItem>
                    <asp:ListItem>2022</asp:ListItem>
                </asp:DropDownList>
                -
                <asp:DropDownList ID="cmbHora2" runat="server">
                </asp:DropDownList>
                :
                <asp:DropDownList ID="cmbMinutos2" runat="server">
                </asp:DropDownList>
                :<asp:DropDownList ID="cmbSegundos2" runat="server">
                </asp:DropDownList> GMT+1<br />
                <br />
                &nbsp;Details:&nbsp;<asp:DropDownList ID="cmbDetalhes" runat="server">
                    <asp:ListItem>None</asp:ListItem>
                    <asp:ListItem Value="10">Used items in Aging</asp:ListItem>
                    <asp:ListItem Value="0">Dropped Items</asp:ListItem>
                    <asp:ListItem Value="17">Mature</asp:ListItem>
                    <asp:ListItem Value="12">Matured Item</asp:ListItem>
                    <asp:ListItem Value="5">Bought something from NPC</asp:ListItem>
                    <asp:ListItem Value="6">Dropped Item</asp:ListItem>
                    <asp:ListItem Value="24">Used Force Orb</asp:ListItem>
                    <asp:ListItem Value="7">Sold something in NPC</asp:ListItem>
                    <asp:ListItem Value="25">Sheltom before Forcing</asp:ListItem>
                    <asp:ListItem Value="26">Force Orb after Forced</asp:ListItem>
                    <asp:ListItem Value="9">Used Items to Mix</asp:ListItem>
                    <asp:ListItem Value="3">Mixed Item</asp:ListItem>
                    <asp:ListItem Value="22">Sold item in personal shop</asp:ListItem>
                    <asp:ListItem Value="23">Bought item in personal shop</asp:ListItem>
                    <asp:ListItem Value="2">Received item/gold in a trade</asp:ListItem>
                    <asp:ListItem Value="8">Gave item/gold in a trade</asp:ListItem>
                </asp:DropDownList><br />
                &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp;
                &nbsp; &nbsp; &nbsp;
                <asp:Button ID="cmbMostra" runat="server" Text="Show logs" />
                &nbsp; &nbsp;&nbsp;<br />
                &nbsp;</asp:Panel>
            <br />
            <asp:Panel ID="Panel2" runat="server" BorderWidth="1px" Height="99%" Width="100%">
                        <asp:Datagrid runat="server"
                Id="dg"
                GridLines="Horizontal" AllowPaging="True" AutoGenerateColumns="False" BackColor="White" BorderColor="#CCCCCC" BorderStyle="None" BorderWidth="1px" CellPadding="4" Height="100%" Width="100%" OnPageIndexChanged = "Page_Change" PageSize="25" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" ForeColor="Black">
         <columns>
           <asp:BoundColumn DataField="RegistDay" HeaderText="Date & hour">
               <HeaderStyle HorizontalAlign="Center" />
           </asp:BoundColumn>
                 <asp:TemplateColumn>
                <HeaderTemplate>Action</HeaderTemplate>
                <ItemTemplate>
                     <div align="center"><%#VerificaFlag(Container.DataItem("Flag"))%><br></div>
                </ItemTemplate>
               <HeaderStyle HorizontalAlign="Center" />
           </asp:TemplateColumn>
             <asp:BoundColumn DataField="ItemCount" HeaderText="Count">
             </asp:BoundColumn>
           <asp:TemplateColumn>
                <HeaderTemplate>Item</HeaderTemplate>
                <ItemTemplate>
                     <div align="center"><%#Container.DataItem("ItemINo") & "@" & Container.DataItem("ItemINo_1")%><br></div>
                </ItemTemplate>
               <HeaderStyle HorizontalAlign="Center" />
           </asp:TemplateColumn>
           <asp:TemplateColumn>
                <HeaderTemplate>Show</HeaderTemplate>
                <ItemTemplate>
                     <div align="center"><a href="javascript:na_open_window('win','ver_completo.aspx?id=<%# Container.DataItem("ITEMNo")%>','120','120','560','460',0,0,0,1,0)">Show complete log</a><br></div>
                </ItemTemplate>
               <HeaderStyle HorizontalAlign="Center" BackColor="Black" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" />
               <ItemStyle BackColor="Black" Font-Bold="False" Font-Italic="False" Font-Names="Tahoma"
                   Font-Overline="False" Font-Strikeout="False" Font-Underline="False" ForeColor="White" />
           </asp:TemplateColumn>
   </columns>
                <FooterStyle BackColor="#CCCC99" ForeColor="Black" />
                <SelectedItemStyle BackColor="#CC3333" Font-Bold="True" ForeColor="White" />
                <PagerStyle BackColor="White" ForeColor="Black" HorizontalAlign="Right" />
                <HeaderStyle BackColor="#333333" Font-Bold="True" ForeColor="White" />
 </asp:DataGrid>
            </asp:Panel>
        </span>
    </form>
</body>
</html>
