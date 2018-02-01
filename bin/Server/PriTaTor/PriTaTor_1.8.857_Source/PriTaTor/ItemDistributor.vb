Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports System
Imports System.Collections
Imports System.ComponentModel
Imports System.Diagnostics
Imports System.Drawing
Imports System.IO
Imports System.Runtime.CompilerServices
Imports System.Text
Imports System.Windows.Forms

Namespace PriTaTor
    <DesignerGenerated> _
    Public Class ItemDistributor
        Inherits Form
        ' Methods
        Public Sub New()
            AddHandler MyBase.Activated, New EventHandler(AddressOf Me.ItemDistributor_Activated)
            AddHandler MyBase.FormClosing, New FormClosingEventHandler(AddressOf Me.ItemDistributor_FormClosing)
            Me.Accounts = Directory.GetFiles((Konstanten.sPath & "\DataServer\userinfo"), "*", SearchOption.AllDirectories)
            Me.InitializeComponent
        End Sub

        Private Sub ClearListToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ListBox1.Items.Clear
            Me.ListBox2.Items.Clear
        End Sub

        Private Sub cmdFindAccount_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ComboBox3.Text <> "") Then
                Dim num As Integer
                Dim enumerator As IEnumerator
                Dim str As String = ""
                Try 
                    enumerator = Me.ListBox2.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim num2 As Integer
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Do While (objectValue.ToString.ToUpper <> str.Replace("""", "").ToUpper)
                            str = Konstanten.ItemCodes(num2).ToUpper
                            num2 += 1
                        Loop
                        num = CInt(Math.Round(CDbl((num + Conversions.ToDouble(Konstanten.ItemWeights((num2 - 1)))))))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                Me.TextBox2.Text = ("Total items weight: " & num.ToString)
                Dim accountDatFile As String = Me.FindAccount((Konstanten.sPath & "\DataServer\userinfo"))
                If (accountDatFile = "Not found") Then
                    Me.ComboBox2.Enabled = False
                    Me.ComboBox1.Enabled = False
                    Me.cmdSendItems.Enabled = False
                    Interaction.MsgBox("Cant find the Account!", MsgBoxStyle.OkOnly, Nothing)
                Else
                    Dim enumerator2 As IEnumerator
                    Me.ComboBox2.Enabled = True
                    Me.ComboBox1.Enabled = True
                    Me.ComboBox2.Items.Clear
                    Me.File = accountDatFile
                    Try 
                        enumerator2 = Me.FindeChars((accountDatFile), Me.ComboBox3.Text).GetEnumerator
                        Do While enumerator2.MoveNext
                            Dim obj3 As Object = RuntimeHelpers.GetObjectValue(enumerator2.Current)
                            Me.ComboBox2.Items.Add(RuntimeHelpers.GetObjectValue(obj3))
                        Loop
                    Finally
                        If TypeOf enumerator2 Is IDisposable Then
                            TryCast(enumerator2,IDisposable).Dispose
                        End If
                    End Try
                    Me.cmdSendItems.Enabled = True
                End If
            End If
        End Sub

        Private Sub cmdSendItems_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.WriteItemDistrData(Me.File)
        End Sub

        Private Sub ComboBox3_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.ComboBox1.Enabled = False
            Me.ComboBox2.Enabled = False
            Me.cmdSendItems.Enabled = False
        End Sub

        Private Sub ComboBox3_TextChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.ComboBox1.Enabled = False
            Me.ComboBox2.Enabled = False
            Me.cmdSendItems.Enabled = False
        End Sub

        Private Sub DeleteItemToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim selectedIndex As Integer = Me.ListBox2.SelectedIndex
            Me.ListBox1.Items.RemoveAt(selectedIndex)
            Me.ListBox2.Items.RemoveAt(selectedIndex)
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

        Private Function FindAccount(ByVal Path As String) As String
            Dim str2 As String
            For Each str2 In Me.Accounts
                If (Path.GetFileName(str2).ToString.ToUpper = (Me.ComboBox3.Text.ToUpper & ".DAT")) Then
                    Return str2
                End If
            Next
            Return "Not found"
        End Function

        Private Function FindeChars(ByRef AccountDatFile As String, ByVal AccountName As String) As ArrayList
            Dim list As New ArrayList
            Dim stream As New FileStream(AccountDatFile, FileMode.Open)
            Dim list2 As New ArrayList
            Dim array As Byte() = New Byte((CInt(stream.Length) + 1)  - 1) {}
            stream.Read(array, 0, CInt(stream.Length))
            Dim num2 As Integer = CInt((stream.Length - &H10))
            Dim i As Integer = &H30
            Do While (i <= num2)
                If (Encoding.ASCII.GetString(array, i, 15).Trim.Replace(ChrW(0), "") <> "") Then
                    list2.Add(Encoding.ASCII.GetString(array, i, 15).Trim)
                End If
                i = (i + &H20)
            Loop
            stream.Close
            Return list2
        End Function

        <DebuggerStepThrough> _
        Private Sub InitializeComponent()
            Me.components = New Container
            Me.ComboBox1 = New ComboBox
            Me.Label1 = New Label
            Me.ListBox1 = New ListBox
            Me.Label2 = New Label
            Me.ListBox2 = New ListBox
            Me.CMItemDistri = New ContextMenuStrip(Me.components)
            Me.ClearListToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteItemToolStripMenuItem = New ToolStripMenuItem
            Me.Label3 = New Label
            Me.Label4 = New Label
            Me.cmdFindAccount = New Button
            Me.ComboBox2 = New ComboBox
            Me.Label5 = New Label
            Me.cmdSendItems = New Button
            Me.Label6 = New Label
            Me.TextBox2 = New TextBox
            Me.ComboBox3 = New ComboBox
            Me.Label7 = New Label
            Me.Label8 = New Label
            Me.CMItemDistri.SuspendLayout
            Me.SuspendLayout
            Me.ComboBox1.DropDownStyle = ComboBoxStyle.DropDownList
            Me.ComboBox1.FormattingEnabled = True
            Me.ComboBox1.Items.AddRange(New Object() { "0=Nothing", "1=Fighter", "2=Mechanician", "3=Archer", "4=Pikeman", "5=Atalanta", "6=Knight", "7=Magician", "8=Priestess" })
            Dim point As New Point(&H5C, &HB8)
            Me.ComboBox1.Location = point
            Me.ComboBox1.Name = "ComboBox1"
            Dim size As New Size(&HB9, &H15)
            Me.ComboBox1.Size = size
            Me.ComboBox1.TabIndex = 0
            Me.Label1.AutoSize = True
            point = New Point(12, &HBB)
            Me.Label1.Location = point
            Me.Label1.Name = "Label1"
            size = New Size(&H41, 13)
            Me.Label1.Size = size
            Me.Label1.TabIndex = 1
            Me.Label1.Text = "Select Spec"
            Me.ListBox1.Enabled = False
            Me.ListBox1.FormattingEnabled = True
            point = New Point(100, &H1D)
            Me.ListBox1.Location = point
            Me.ListBox1.Name = "ListBox1"
            size = New Size(&HB1, &H5F)
            Me.ListBox1.Size = size
            Me.ListBox1.TabIndex = 2
            Me.Label2.AutoSize = True
            point = New Point(&H61, 9)
            Me.Label2.Location = point
            Me.Label2.Name = "Label2"
            size = New Size(&H3D, 13)
            Me.Label2.Size = size
            Me.Label2.TabIndex = 3
            Me.Label2.Text = "Itemnames:"
            Me.ListBox2.ContextMenuStrip = Me.CMItemDistri
            Me.ListBox2.FormattingEnabled = True
            point = New Point(12, &H1D)
            Me.ListBox2.Location = point
            Me.ListBox2.Name = "ListBox2"
            size = New Size(&H52, &H5F)
            Me.ListBox2.Size = size
            Me.ListBox2.TabIndex = 4
            Me.CMItemDistri.Items.AddRange(New ToolStripItem() { Me.ClearListToolStripMenuItem, Me.DeleteItemToolStripMenuItem })
            Me.CMItemDistri.Name = "CMItemDistri"
            size = New Size(&H83, &H30)
            Me.CMItemDistri.Size = size
            Me.ClearListToolStripMenuItem.Name = "ClearListToolStripMenuItem"
            size = New Size(130, &H16)
            Me.ClearListToolStripMenuItem.Size = size
            Me.ClearListToolStripMenuItem.Text = "Clear List"
            Me.DeleteItemToolStripMenuItem.Name = "DeleteItemToolStripMenuItem"
            size = New Size(130, &H16)
            Me.DeleteItemToolStripMenuItem.Size = size
            Me.DeleteItemToolStripMenuItem.Text = "Delete Item"
            Me.Label3.AutoSize = True
            point = New Point(9, 9)
            Me.Label3.Location = point
            Me.Label3.Name = "Label3"
            size = New Size(&H37, 13)
            Me.Label3.Size = size
            Me.Label3.TabIndex = 5
            Me.Label3.Text = "ItemCode:"
            Me.Label4.AutoSize = True
            point = New Point(12, &H85)
            Me.Label4.Location = point
            Me.Label4.Name = "Label4"
            size = New Size(50, 13)
            Me.Label4.Size = size
            Me.Label4.TabIndex = 7
            Me.Label4.Text = "Account:"
            point = New Point(&HCA, &H80)
            Me.cmdFindAccount.Location = point
            Me.cmdFindAccount.Name = "cmdFindAccount"
            size = New Size(&H4B, &H17)
            Me.cmdFindAccount.Size = size
            Me.cmdFindAccount.TabIndex = 8
            Me.cmdFindAccount.Text = "Find"
            Me.cmdFindAccount.UseVisualStyleBackColor = True
            Me.ComboBox2.DropDownStyle = ComboBoxStyle.DropDownList
            Me.ComboBox2.Enabled = False
            Me.ComboBox2.FormattingEnabled = True
            point = New Point(&H5C, &H9D)
            Me.ComboBox2.Location = point
            Me.ComboBox2.Name = "ComboBox2"
            size = New Size(&HB9, &H15)
            Me.ComboBox2.Size = size
            Me.ComboBox2.TabIndex = 9
            Me.Label5.AutoSize = True
            point = New Point(12, 160)
            Me.Label5.Location = point
            Me.Label5.Name = "Label5"
            size = New Size(&H20, 13)
            Me.Label5.Size = size
            Me.Label5.TabIndex = 10
            Me.Label5.Text = "Char:"
            Me.cmdSendItems.Enabled = False
            point = New Point(12, &HEE)
            Me.cmdSendItems.Location = point
            Me.cmdSendItems.Name = "cmdSendItems"
            size = New Size(&H4B, &H17)
            Me.cmdSendItems.Size = size
            Me.cmdSendItems.TabIndex = 11
            Me.cmdSendItems.Text = "Send"
            Me.cmdSendItems.UseVisualStyleBackColor = True
            Me.Label6.AutoSize = True
            point = New Point(12, &HD5)
            Me.Label6.Location = point
            Me.Label6.Name = "Label6"
            size = New Size(&H35, 13)
            Me.Label6.Size = size
            Me.Label6.TabIndex = 12
            Me.Label6.Text = "Message:"
            point = New Point(&H5C, 210)
            Me.TextBox2.Location = point
            Me.TextBox2.Name = "TextBox2"
            size = New Size(&HB9, 20)
            Me.TextBox2.Size = size
            Me.TextBox2.TabIndex = 13
            Me.ComboBox3.AutoCompleteMode = AutoCompleteMode.SuggestAppend
            Me.ComboBox3.AutoCompleteSource = AutoCompleteSource.ListItems
            Me.ComboBox3.FormattingEnabled = True
            point = New Point(&H5C, 130)
            Me.ComboBox3.Location = point
            Me.ComboBox3.Name = "ComboBox3"
            size = New Size(&H68, &H15)
            Me.ComboBox3.Size = size
            Me.ComboBox3.TabIndex = 14
            Me.Label7.AutoSize = True
            point = New Point(&H5D, &HF3)
            Me.Label7.Location = point
            Me.Label7.Name = "Label7"
            size = New Size(&H55, 13)
            Me.Label7.Size = size
            Me.Label7.TabIndex = 15
            Me.Label7.Text = "Accounts found:"
            Me.Label8.AutoSize = True
            point = New Point(&HB7, &HF3)
            Me.Label8.Location = point
            Me.Label8.Name = "Label8"
            size = New Size(13, 13)
            Me.Label8.Size = size
            Me.Label8.TabIndex = &H10
            Me.Label8.Text = "0"
            Dim ef As New SizeF(6!, 13!)
            Me.AutoScaleDimensions = ef
            Me.AutoScaleMode = AutoScaleMode.Font
            size = New Size(&H11C, &H10C)
            Me.ClientSize = size
            Me.Controls.Add(Me.Label8)
            Me.Controls.Add(Me.Label7)
            Me.Controls.Add(Me.ComboBox3)
            Me.Controls.Add(Me.TextBox2)
            Me.Controls.Add(Me.Label6)
            Me.Controls.Add(Me.cmdSendItems)
            Me.Controls.Add(Me.ComboBox2)
            Me.Controls.Add(Me.Label5)
            Me.Controls.Add(Me.Label4)
            Me.Controls.Add(Me.cmdFindAccount)
            Me.Controls.Add(Me.Label3)
            Me.Controls.Add(Me.ListBox2)
            Me.Controls.Add(Me.Label2)
            Me.Controls.Add(Me.ListBox1)
            Me.Controls.Add(Me.ComboBox1)
            Me.Controls.Add(Me.Label1)
            size = New Size(300, &H130)
            Me.MaximumSize = size
            Me.Name = "ItemDistributor"
            Me.Text = "ItemDistributor"
            Me.CMItemDistri.ResumeLayout(False)
            Me.ResumeLayout(False)
            Me.PerformLayout
        End Sub

        Private Sub ItemDistributor_Activated(ByVal sender As Object, ByVal e As EventArgs)
            Me.ComboBox1.Enabled = False
            Me.ComboBox2.Enabled = False
            Me.Label8.Text = Conversions.ToString(Me.Accounts.Length)
            Me.Makelist
        End Sub

        Private Sub ItemDistributor_FormClosing(ByVal sender As Object, ByVal e As FormClosingEventArgs)
            Me.ComboBox1.Enabled = False
            Me.ComboBox2.Enabled = False
        End Sub

        Private Sub ListBox2_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Dim num As Integer
            Dim enumerator As IEnumerator
            Me.ListBox1.SelectedIndex = Me.ListBox2.SelectedIndex
            Dim str As String = ""
            Try 
                enumerator = Me.ListBox2.Items.GetEnumerator
                Do While enumerator.MoveNext
                    Dim num2 As Integer
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Do While (objectValue.ToString.ToUpper <> str.Replace("""", "").ToUpper)
                        str = Konstanten.ItemCodes(num2).ToUpper
                        num2 += 1
                    Loop
                    num = CInt(Math.Round(CDbl((num + Conversions.ToDouble(Konstanten.ItemWeights((num2 - 1)))))))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
            Me.TextBox2.Text = ("Total items weight: " & num.ToString)
        End Sub

        Public Sub Makelist()
            Me.ComboBox3.Items.Clear
            Dim str As String
            For Each str In Me.Accounts
                Me.ComboBox3.Items.Add(Path.GetFileName(str).Remove((Path.GetFileName(str).Length - 4)))
            Next
        End Sub

        Private Sub WriteItemDistrData(ByVal AccountFileDat As String)
            Try 
                If (Me.ComboBox2.Text = "") Then
                    Interaction.MsgBox("Please select a Char", MsgBoxStyle.OkOnly, Nothing)
                ElseIf (Me.ComboBox1.Text = "") Then
                    Interaction.MsgBox("Please select a Spec", MsgBoxStyle.OkOnly, Nothing)
                Else
                    Dim enumerator As IEnumerator
                    Dim directoryName As String = Path.GetDirectoryName(AccountFileDat)
                    Dim count As Integer = (directoryName.Length - 1)
                    Do While (Conversions.ToString(directoryName.Chars(count)) <> "\")
                        count -= 1
                    Loop
                    Dim path As String = String.Concat(New String() { Konstanten.sPath, "PostBox", directoryName.Remove(0, count), "\", Path.GetFileName(AccountFileDat) })
                    If File.Exists(path) Then
                        If Funktionen.YesNo("Warning", "There is a gift alreay in this account, delete it?", 1) Then
                            File.Delete(path)
                        Else
                            If Funktionen.YesNo("Sending caneled", "Load the data into ItemDistributor?", 1) Then
                                Interaction.MsgBox("Loading", MsgBoxStyle.OkOnly, Nothing)
                            End If
                            Return
                        End If
                    End If
                    Dim writer As New StreamWriter(path, True)
                    Try 
                        enumerator = Me.ListBox2.Items.GetEnumerator
                        Do While enumerator.MoveNext
                            Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                            Dim str2 As String = Conversions.ToString(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject((Me.ComboBox2.Text & " "), objectValue), " "c), Me.ComboBox1.Text.Chars(0)), " "c), """"c), Me.TextBox2.Text), """"c), ChrW(13)), ChrW(10)))
                            writer.Write(str2)
                        Loop
                    Finally
                        If TypeOf enumerator Is IDisposable Then
                            TryCast(enumerator,IDisposable).Dispose
                        End If
                    End Try
                    writer.Close
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "Write ItemDistributor Data:" & ChrW(13) & ChrW(10) & "Path:", Me.File, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub


        ' Properties
        Friend Overridable Property ClearListToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ClearListToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ClearListToolStripMenuItem_Click)
                If (Not Me._ClearListToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._ClearListToolStripMenuItem.Click, handler
                End If
                Me._ClearListToolStripMenuItem = WithEventsValue
                If (Not Me._ClearListToolStripMenuItem Is Nothing) Then
                    AddHandler Me._ClearListToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdFindAccount As Button
            Get
                Return Me._cmdFindAccount
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdFindAccount_Click)
                If (Not Me._cmdFindAccount Is Nothing) Then
                    RemoveHandler Me._cmdFindAccount.Click, handler
                End If
                Me._cmdFindAccount = WithEventsValue
                If (Not Me._cmdFindAccount Is Nothing) Then
                    AddHandler Me._cmdFindAccount.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdSendItems As Button
            Get
                Return Me._cmdSendItems
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdSendItems_Click)
                If (Not Me._cmdSendItems Is Nothing) Then
                    RemoveHandler Me._cmdSendItems.Click, handler
                End If
                Me._cmdSendItems = WithEventsValue
                If (Not Me._cmdSendItems Is Nothing) Then
                    AddHandler Me._cmdSendItems.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property CMItemDistri As ContextMenuStrip
            Get
                Return Me._CMItemDistri
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMItemDistri = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ComboBox1 As ComboBox
            Get
                Return Me._ComboBox1
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._ComboBox1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ComboBox2 As ComboBox
            Get
                Return Me._ComboBox2
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._ComboBox2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ComboBox3 As ComboBox
            Get
                Return Me._ComboBox3
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ComboBox3_TextChanged)
                Dim handler2 As EventHandler = New EventHandler(AddressOf Me.ComboBox3_SelectedIndexChanged)
                If (Not Me._ComboBox3 Is Nothing) Then
                    RemoveHandler Me._ComboBox3.TextChanged, handler
                    RemoveHandler Me._ComboBox3.SelectedIndexChanged, handler2
                End If
                Me._ComboBox3 = WithEventsValue
                If (Not Me._ComboBox3 Is Nothing) Then
                    AddHandler Me._ComboBox3.TextChanged, handler
                    AddHandler Me._ComboBox3.SelectedIndexChanged, handler2
                End If
            End Set
        End Property

        Friend Overridable Property DeleteItemToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._DeleteItemToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DeleteItemToolStripMenuItem_Click)
                If (Not Me._DeleteItemToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._DeleteItemToolStripMenuItem.Click, handler
                End If
                Me._DeleteItemToolStripMenuItem = WithEventsValue
                If (Not Me._DeleteItemToolStripMenuItem Is Nothing) Then
                    AddHandler Me._DeleteItemToolStripMenuItem.Click, handler
                End If
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

        Friend Overridable Property Label3 As Label
            Get
                Return Me._Label3
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label3 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label4 As Label
            Get
                Return Me._Label4
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label4 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label5 As Label
            Get
                Return Me._Label5
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label5 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label6 As Label
            Get
                Return Me._Label6
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label6 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label7 As Label
            Get
                Return Me._Label7
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label7 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label8 As Label
            Get
                Return Me._Label8
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label8 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ListBox1 As ListBox
            Get
                Return Me._ListBox1
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Me._ListBox1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ListBox2 As ListBox
            Get
                Return Me._ListBox2
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ListBox2_SelectedIndexChanged)
                If (Not Me._ListBox2 Is Nothing) Then
                    RemoveHandler Me._ListBox2.SelectedIndexChanged, handler
                End If
                Me._ListBox2 = WithEventsValue
                If (Not Me._ListBox2 Is Nothing) Then
                    AddHandler Me._ListBox2.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property TextBox2 As TextBox
            Get
                Return Me._TextBox2
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._TextBox2 = WithEventsValue
            End Set
        End Property


        ' Fields
        <AccessedThroughProperty("ClearListToolStripMenuItem")> _
        Private _ClearListToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("cmdFindAccount")> _
        Private _cmdFindAccount As Button
        <AccessedThroughProperty("cmdSendItems")> _
        Private _cmdSendItems As Button
        <AccessedThroughProperty("CMItemDistri")> _
        Private _CMItemDistri As ContextMenuStrip
        <AccessedThroughProperty("ComboBox1")> _
        Private _ComboBox1 As ComboBox
        <AccessedThroughProperty("ComboBox2")> _
        Private _ComboBox2 As ComboBox
        <AccessedThroughProperty("ComboBox3")> _
        Private _ComboBox3 As ComboBox
        <AccessedThroughProperty("DeleteItemToolStripMenuItem")> _
        Private _DeleteItemToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("Label1")> _
        Private _Label1 As Label
        <AccessedThroughProperty("Label2")> _
        Private _Label2 As Label
        <AccessedThroughProperty("Label3")> _
        Private _Label3 As Label
        <AccessedThroughProperty("Label4")> _
        Private _Label4 As Label
        <AccessedThroughProperty("Label5")> _
        Private _Label5 As Label
        <AccessedThroughProperty("Label6")> _
        Private _Label6 As Label
        <AccessedThroughProperty("Label7")> _
        Private _Label7 As Label
        <AccessedThroughProperty("Label8")> _
        Private _Label8 As Label
        <AccessedThroughProperty("ListBox1")> _
        Private _ListBox1 As ListBox
        <AccessedThroughProperty("ListBox2")> _
        Private _ListBox2 As ListBox
        <AccessedThroughProperty("TextBox2")> _
        Private _TextBox2 As TextBox
        Private Accounts As String()
        Private components As IContainer
        Private File As String
    End Class
End Namespace

