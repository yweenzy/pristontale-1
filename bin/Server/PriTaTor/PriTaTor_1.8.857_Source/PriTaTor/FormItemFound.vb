Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports PriTaTor.My
Imports System
Imports System.Collections
Imports System.ComponentModel
Imports System.Diagnostics
Imports System.Drawing
Imports System.Runtime.CompilerServices
Imports System.Windows.Forms

Namespace PriTaTor
    <DesignerGenerated> _
    Public Class FormItemFound
        Inherits Form
        ' Methods
        <DebuggerNonUserCode> _
        Public Sub New()
            Me.InitializeComponent
        End Sub

        Private Sub cmdItemFound_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.searchITem
        End Sub

        Private Sub cmdItemsFoundClear_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.LWItemsFound.Items.Clear
        End Sub

        Private Sub CMSItemFound_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            If (((MyProject.Forms.PriTaEditor.TabControl1.SelectedTab.Text = "NPC Editor") And (MyProject.Forms.PriTaEditor.lbNPCMapFileList.SelectedItems.Count > 0)) And (MyProject.Forms.PriTaEditor.lbNPCList.SelectedItems.Count > 0)) Then
                Me.SendToShopToolStripMenuItem.Enabled = True
            Else
                Me.SendToShopToolStripMenuItem.Enabled = False
            End If
        End Sub

        <DebuggerNonUserCode> _
        Protected Overrides Sub Dispose(ByVal disposing As Boolean)
            Try 
                If (disposing AndAlso (Not Me.components Is Nothing)) Then
                    Me.components.Dispose
                End If
            Finally
                MyBase.Dispose(disposing)
            End Try
        End Sub

        <DebuggerStepThrough> _
        Private Sub InitializeComponent()
            Me.components = New Container
            Me.cmdItemsFoundClear = New Button
            Me.tbCommand = New TextBox
            Me.Label1 = New Label
            Me.cmdItemFound = New Button
            Me.tbItemFoundSrachstring = New TextBox
            Me.CMSItemFound = New ContextMenuStrip(Me.components)
            Me.SendToShopToolStripMenuItem = New ToolStripMenuItem
            Me.LWItemsFound = New ListView
            Me.CoItemCode = New ColumnHeader
            Me.CoItemName = New ColumnHeader
            Me.Label2 = New Label
            Me.CMSItemFound.SuspendLayout
            Me.SuspendLayout
            Dim point As New Point(12, 12)
            Me.cmdItemsFoundClear.Location = point
            Me.cmdItemsFoundClear.Name = "cmdItemsFoundClear"
            Dim size As New Size(&H4B, &H17)
            Me.cmdItemsFoundClear.Size = size
            Me.cmdItemsFoundClear.TabIndex = 2
            Me.cmdItemsFoundClear.Text = "Clear list"
            Me.cmdItemsFoundClear.UseVisualStyleBackColor = True
            point = New Point(12, &H13A)
            Me.tbCommand.Location = point
            Me.tbCommand.Name = "tbCommand"
            size = New Size(&HF2, 20)
            Me.tbCommand.Size = size
            Me.tbCommand.TabIndex = 3
            Me.Label1.AutoSize = True
            point = New Point(10, &H12A)
            Me.Label1.Location = point
            Me.Label1.Name = "Label1"
            size = New Size(&H4F, 13)
            Me.Label1.Size = size
            Me.Label1.TabIndex = 4
            Me.Label1.Text = "Drop command"
            point = New Point(14, &H37)
            Me.cmdItemFound.Location = point
            Me.cmdItemFound.Name = "cmdItemFound"
            size = New Size(&H4B, &H17)
            Me.cmdItemFound.Size = size
            Me.cmdItemFound.TabIndex = 5
            Me.cmdItemFound.Text = "Search"
            Me.cmdItemFound.UseVisualStyleBackColor = True
            point = New Point(&H5D, &H39)
            Me.tbItemFoundSrachstring.Location = point
            Me.tbItemFoundSrachstring.Name = "tbItemFoundSrachstring"
            size = New Size(&HA1, 20)
            Me.tbItemFoundSrachstring.Size = size
            Me.tbItemFoundSrachstring.TabIndex = 6
            Me.CMSItemFound.Items.AddRange(New ToolStripItem() { Me.SendToShopToolStripMenuItem })
            Me.CMSItemFound.Name = "CMSItemFound"
            size = New Size(&H99, &H30)
            Me.CMSItemFound.Size = size
            Me.SendToShopToolStripMenuItem.Name = "SendToShopToolStripMenuItem"
            size = New Size(&H98, &H16)
            Me.SendToShopToolStripMenuItem.Size = size
            Me.SendToShopToolStripMenuItem.Text = "Send to shop"
            Me.LWItemsFound.Columns.AddRange(New ColumnHeader() { Me.CoItemCode, Me.CoItemName })
            Me.LWItemsFound.ContextMenuStrip = Me.CMSItemFound
            Me.LWItemsFound.FullRowSelect = True
            point = New Point(13, &H53)
            Me.LWItemsFound.Location = point
            Me.LWItemsFound.Name = "LWItemsFound"
            size = New Size(&HF1, &HD4)
            Me.LWItemsFound.Size = size
            Me.LWItemsFound.TabIndex = &H49
            Me.LWItemsFound.UseCompatibleStateImageBehavior = False
            Me.LWItemsFound.View = View.Details
            Me.CoItemCode.Text = "Code"
            Me.CoItemName.Text = "Name"
            Me.CoItemName.Width = &HAF
            Me.Label2.AutoSize = True
            point = New Point(&H5D, &H26)
            Me.Label2.Location = point
            Me.Label2.Name = "Label2"
            size = New Size(&H5C, 13)
            Me.Label2.Size = size
            Me.Label2.TabIndex = &H4A
            Me.Label2.Text = "Use wildcards: ? *"
            Dim ef As New SizeF(6!, 13!)
            Me.AutoScaleDimensions = ef
            Me.AutoScaleMode = AutoScaleMode.Font
            size = New Size(&H124, &H15A)
            Me.ClientSize = size
            Me.Controls.Add(Me.Label2)
            Me.Controls.Add(Me.LWItemsFound)
            Me.Controls.Add(Me.tbItemFoundSrachstring)
            Me.Controls.Add(Me.Label1)
            Me.Controls.Add(Me.cmdItemFound)
            Me.Controls.Add(Me.tbCommand)
            Me.Controls.Add(Me.cmdItemsFoundClear)
            Me.Name = "FormItemFound"
            Me.Text = "Item searcher"
            Me.CMSItemFound.ResumeLayout(False)
            Me.ResumeLayout(False)
            Me.PerformLayout
        End Sub

        Private Sub lbItemsFoundName_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.LWItemsFound.SelectedItems.Count >= 1) Then
                Me.tbCommand.Text = ("~/@get " & Me.LWItemsFound.SelectedItems.Item(0).Text.Trim(New Char() { """"c }))
            End If
        End Sub

        Public Sub searchITem()
            Dim num As Integer
            Dim text As String = Me.tbItemFoundSrachstring.Text
            Do While (num <> (Konstanten.ItemName.Length - 1))
                If LikeOperator.LikeString(Konstanten.ItemName(num).ToUpper, [text].ToUpper, CompareMethod.Binary) Then
                    Me.LWItemsFound.Items.Add(Konstanten.ItemCodes(num)).SubItems.Add(Konstanten.ItemName(num))
                End If
                num += 1
            Loop
        End Sub

        Private Sub SendToShopToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Try 
                enumerator = Me.LWItemsFound.SelectedItems.GetEnumerator
                Do While enumerator.MoveNext
                    Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                    MyProject.Forms.PriTaEditor.LWNPCshop.Items.Add(current.Text).SubItems.Add(current.SubItems.Item(1).Text)
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub tbItemFoundSrachstring_KeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
            If (Conversions.ToString(e.KeyChar) = ChrW(13)) Then
                Me.searchITem
            End If
        End Sub


        ' Properties
        Friend Overridable Property cmdItemFound As Button
            Get
                Return Me._cmdItemFound
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdItemFound_Click)
                If (Not Me._cmdItemFound Is Nothing) Then
                    RemoveHandler Me._cmdItemFound.Click, handler
                End If
                Me._cmdItemFound = WithEventsValue
                If (Not Me._cmdItemFound Is Nothing) Then
                    AddHandler Me._cmdItemFound.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdItemsFoundClear As Button
            Get
                Return Me._cmdItemsFoundClear
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdItemsFoundClear_Click)
                If (Not Me._cmdItemsFoundClear Is Nothing) Then
                    RemoveHandler Me._cmdItemsFoundClear.Click, handler
                End If
                Me._cmdItemsFoundClear = WithEventsValue
                If (Not Me._cmdItemsFoundClear Is Nothing) Then
                    AddHandler Me._cmdItemsFoundClear.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property CMSItemFound As ContextMenuStrip
            Get
                Return Me._CMSItemFound
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.CMSItemFound_Opening)
                If (Not Me._CMSItemFound Is Nothing) Then
                    RemoveHandler Me._CMSItemFound.Opening, handler
                End If
                Me._CMSItemFound = WithEventsValue
                If (Not Me._CMSItemFound Is Nothing) Then
                    AddHandler Me._CMSItemFound.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property CoItemCode As ColumnHeader
            Get
                Return Me._CoItemCode
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._CoItemCode = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CoItemName As ColumnHeader
            Get
                Return Me._CoItemName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._CoItemName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label1 As Label
            Get
                Return Me._Label1
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label2 As Label
            Get
                Return Me._Label2
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property LWItemsFound As ListView
            Get
                Return Me._LWItemsFound
            End Get
            Set(ByVal WithEventsValue As ListView)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.lbItemsFoundName_SelectedIndexChanged)
                If (Not Me._LWItemsFound Is Nothing) Then
                    RemoveHandler Me._LWItemsFound.SelectedIndexChanged, handler
                End If
                Me._LWItemsFound = WithEventsValue
                If (Not Me._LWItemsFound Is Nothing) Then
                    AddHandler Me._LWItemsFound.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property SendToShopToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._SendToShopToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.SendToShopToolStripMenuItem_Click)
                If (Not Me._SendToShopToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._SendToShopToolStripMenuItem.Click, handler
                End If
                Me._SendToShopToolStripMenuItem = WithEventsValue
                If (Not Me._SendToShopToolStripMenuItem Is Nothing) Then
                    AddHandler Me._SendToShopToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property tbCommand As TextBox
            Get
                Return Me._tbCommand
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbCommand = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItemFoundSrachstring As TextBox
            Get
                Return Me._tbItemFoundSrachstring
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Dim handler As KeyPressEventHandler = New KeyPressEventHandler(AddressOf Me.tbItemFoundSrachstring_KeyPress)
                If (Not Me._tbItemFoundSrachstring Is Nothing) Then
                    RemoveHandler Me._tbItemFoundSrachstring.KeyPress, handler
                End If
                Me._tbItemFoundSrachstring = WithEventsValue
                If (Not Me._tbItemFoundSrachstring Is Nothing) Then
                    AddHandler Me._tbItemFoundSrachstring.KeyPress, handler
                End If
            End Set
        End Property


        ' Fields
        <AccessedThroughProperty("cmdItemFound")> _
        Private _cmdItemFound As Button
        <AccessedThroughProperty("cmdItemsFoundClear")> _
        Private _cmdItemsFoundClear As Button
        <AccessedThroughProperty("CMSItemFound")> _
        Private _CMSItemFound As ContextMenuStrip
        <AccessedThroughProperty("CoItemCode")> _
        Private _CoItemCode As ColumnHeader
        <AccessedThroughProperty("CoItemName")> _
        Private _CoItemName As ColumnHeader
        <AccessedThroughProperty("Label1")> _
        Private _Label1 As Label
        <AccessedThroughProperty("Label2")> _
        Private _Label2 As Label
        <AccessedThroughProperty("LWItemsFound")> _
        Private _LWItemsFound As ListView
        <AccessedThroughProperty("SendToShopToolStripMenuItem")> _
        Private _SendToShopToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("tbCommand")> _
        Private _tbCommand As TextBox
        <AccessedThroughProperty("tbItemFoundSrachstring")> _
        Private _tbItemFoundSrachstring As TextBox
        Private components As IContainer
    End Class
End Namespace

