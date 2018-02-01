Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports PriTaTor.My
Imports System
Imports System.Collections
Imports System.ComponentModel
Imports System.Data
Imports System.Diagnostics
Imports System.Drawing
Imports System.Runtime.CompilerServices
Imports System.Windows.Forms

Namespace PriTaTor
    <DesignerGenerated> _
    Public Class Form2
        Inherits Form
        ' Methods
        <DebuggerNonUserCode> _
        Public Sub New()
            AddHandler MyBase.Load, New EventHandler(AddressOf Me.Form2_Load)
            Me.InitializeComponent
        End Sub

        Private Sub cmdClose_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.Close
        End Sub

        Public Sub cmdStartExp_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Dim str2 As String = ""
            Dim expression As String = ""
            Dim flag2 As Boolean = True
            Dim flag As Boolean = False
            Dim str As String = Me.tbExpFormula.Text.ToString.ToUpper
            Try 
                enumerator = DirectCast(Konstanten.ExpSender, IEnumerable).GetEnumerator
                Do While enumerator.MoveNext
                    Dim monsterIndex As Long = Funktionen.GetMonsterIndex(Conversions.ToString(RuntimeHelpers.GetObjectValue(enumerator.Current)))
                    Dim monsterExp As Long = Funktionen.GetMonsterExp(monsterIndex)
                    Dim monsterLVL As Long = Funktionen.GetMonsterLVL(monsterIndex)
                    If str.Contains("EXP") Then
                        str2 = str.Replace("EXP", monsterExp.ToString)
                    Else
                        str2 = str
                    End If
                    If str.Contains("LVL") Then
                        expression = str2.Replace("LVL", monsterLVL.ToString)
                    Else
                        expression = str2
                    End If
                    If ((Not str.Contains("EXP") And Not str.Contains("LVL")) And flag2) Then
                        If Not Funktionen.YesNo("Warning!", "Set all selected monsters to same exp?", 2) Then
                            Interaction.MsgBox("canceled", MsgBoxStyle.OkOnly, Nothing)
                            Return
                        End If
                        flag2 = False
                    End If
                    If (Funktionen.textausrechnung(expression) > Conversions.ToDouble(MySettingsProperty.Settings.MaxExp.ToString)) Then
                        Dim num5 As Single
                        num5 += 1
                        Me.lblWarn.Text = ("Warnings: " & Conversions.ToString(num5))
                        Me.lblWarn.Refresh
                        flag = True
                    End If
                    Funktionen.SetMonsterExp(monsterIndex, CLng(Math.Round(Conversion.Int(Funktionen.textausrechnung(expression)))))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
            If flag Then
                Interaction.MsgBox("Warning! Some monsters have to high EXP, please check options!", MsgBoxStyle.Exclamation, Nothing)
            End If
            If Funktionen.YesNo("Save", "Save all monsters?", 1) Then
                Dim num4 As Double
                Dim enumerator2 As IEnumerator
                Try 
                    enumerator2 = DirectCast(Konstanten.ExpSender, IEnumerable).GetEnumerator
                    Do While enumerator2.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator2.Current)
                        Me.lblSave.Text = Conversions.ToString(objectValue)
                        Me.lblSave.Refresh
                        Funktionen.MonsterSaver(Funktionen.GetMonsterIndex(Conversions.ToString(objectValue)), True)
                        Me.lblSave.Text = ""
                        num4 = Conversions.ToDouble(Operators.AddObject(num4, Operators.DivideObject(100, NewLateBinding.LateGet(Konstanten.ExpSender, Nothing, "Count", New Object(0  - 1) {}, Nothing, Nothing, Nothing))))
                        If (num4 >= 100) Then
                            num4 = 100
                        End If
                        Me.pbExp.Value = CInt(Math.Round(num4))
                        Me.pbExp.Refresh
                    Loop
                Finally
                    If TypeOf enumerator2 Is IDisposable Then
                        TryCast(enumerator2,IDisposable).Dispose
                    End If
                End Try
                num4 = 0
                Interaction.MsgBox(Operators.ConcatenateObject(NewLateBinding.LateGet(Konstanten.ExpSender, Nothing, "Count", New Object(0  - 1) {}, Nothing, Nothing, Nothing), " monster Saved!"), MsgBoxStyle.OkOnly, Nothing)
                Me.Close
            Else
                Interaction.MsgBox("Warning: No monster saved! Press reload button", MsgBoxStyle.OkOnly, Nothing)
                Me.Close
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

        Private Sub Form2_Load(ByVal sender As Object, ByVal e As EventArgs)
            Me.tbExpFormula_TextChanged(RuntimeHelpers.GetObjectValue(sender), e)
        End Sub

        <DebuggerStepThrough> _
        Private Sub InitializeComponent()
            Me.Label1 = New Label
            Me.Label2 = New Label
            Me.tbExpFormula = New TextBox
            Me.Label3 = New Label
            Me.Label4 = New Label
            Me.cmdTestExp = New Button
            Me.cmdStartExp = New Button
            Me.cmdClose = New Button
            Me.lblResu = New Label
            Me.Label5 = New Label
            Me.pbExp = New ProgressBar
            Me.lblSave = New Label
            Me.lblWarn = New Label
            Me.SuspendLayout
            Me.Label1.AutoSize = True
            Dim point As New Point(9, 13)
            Me.Label1.Location = point
            Me.Label1.Name = "Label1"
            Dim size As New Size(&HBC, 13)
            Me.Label1.Size = size
            Me.Label1.TabIndex = 0
            Me.Label1.Text = "EXP = Experience of selected monster"
            Me.Label2.AutoSize = True
            point = New Point(9, &H1A)
            Me.Label2.Location = point
            Me.Label2.Name = "Label2"
            size = New Size(&H9F, 13)
            Me.Label2.Size = size
            Me.Label2.TabIndex = 1
            Me.Label2.Text = "LVL = Level of selected monster"
            Me.tbExpFormula.DataBindings.Add(New Binding("Text", MySettings.Default, "EXPFormel", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(12, &H73)
            Me.tbExpFormula.Location = point
            Me.tbExpFormula.Name = "tbExpFormula"
            size = New Size(&H116, 20)
            Me.tbExpFormula.Size = size
            Me.tbExpFormula.TabIndex = 2
            Me.tbExpFormula.Text = MySettings.Default.EXPFormel
            Me.Label3.AutoSize = True
            point = New Point(9, &H2B)
            Me.Label3.Location = point
            Me.Label3.Name = "Label3"
            size = New Size(&H65, 13)
            Me.Label3.Size = size
            Me.Label3.TabIndex = 3
            Me.Label3.Text = "Example EXP=1500"
            Me.Label4.AutoSize = True
            point = New Point(9, &H38)
            Me.Label4.Location = point
            Me.Label4.Name = "Label4"
            size = New Size(&H57, 13)
            Me.Label4.Size = size
            Me.Label4.TabIndex = 4
            Me.Label4.Text = "Example LVL=60"
            point = New Point(&H86, &H56)
            Me.cmdTestExp.Location = point
            Me.cmdTestExp.Name = "cmdTestExp"
            size = New Size(&H4B, &H17)
            Me.cmdTestExp.Size = size
            Me.cmdTestExp.TabIndex = 5
            Me.cmdTestExp.Text = "Test"
            Me.cmdTestExp.UseVisualStyleBackColor = True
            point = New Point(&HD7, &H56)
            Me.cmdStartExp.Location = point
            Me.cmdStartExp.Name = "cmdStartExp"
            size = New Size(&H4B, &H17)
            Me.cmdStartExp.Size = size
            Me.cmdStartExp.TabIndex = 6
            Me.cmdStartExp.Text = "Start"
            Me.cmdStartExp.UseVisualStyleBackColor = True
            point = New Point(&HD7, 13)
            Me.cmdClose.Location = point
            Me.cmdClose.Name = "cmdClose"
            size = New Size(&H4B, &H17)
            Me.cmdClose.Size = size
            Me.cmdClose.TabIndex = 7
            Me.cmdClose.Text = "Cancel"
            Me.cmdClose.TextImageRelation = TextImageRelation.ImageAboveText
            Me.cmdClose.UseVisualStyleBackColor = True
            Me.lblResu.AutoSize = True
            point = New Point(&H37, &H49)
            Me.lblResu.Location = point
            Me.lblResu.Name = "lblResu"
            size = New Size(13, 13)
            Me.lblResu.Size = size
            Me.lblResu.TabIndex = 8
            Me.lblResu.Text = "0"
            Me.Label5.AutoSize = True
            point = New Point(9, &H49)
            Me.Label5.Location = point
            Me.Label5.Name = "Label5"
            size = New Size(40, 13)
            Me.Label5.Size = size
            Me.Label5.TabIndex = 9
            Me.Label5.Text = "Result:"
            point = New Point(12, &H9E)
            Me.pbExp.Location = point
            Me.pbExp.Name = "pbExp"
            size = New Size(&H115, 15)
            Me.pbExp.Size = size
            Me.pbExp.TabIndex = 10
            Me.lblSave.AutoSize = True
            point = New Point(9, &H8E)
            Me.lblSave.Location = point
            Me.lblSave.Name = "lblSave"
            size = New Size(0, 13)
            Me.lblSave.Size = size
            Me.lblSave.TabIndex = 11
            Me.lblWarn.AutoSize = True
            point = New Point(&HA9, &H8B)
            Me.lblWarn.Location = point
            Me.lblWarn.Name = "lblWarn"
            size = New Size(&H40, 13)
            Me.lblWarn.Size = size
            Me.lblWarn.TabIndex = 12
            Me.lblWarn.Text = "Warnings: 0"
            Dim ef As New SizeF(6!, 13!)
            Me.AutoScaleDimensions = ef
            Me.AutoScaleMode = AutoScaleMode.Font
            size = New Size(&H12E, &HB6)
            Me.ClientSize = size
            Me.ControlBox = False
            Me.Controls.Add(Me.lblWarn)
            Me.Controls.Add(Me.lblSave)
            Me.Controls.Add(Me.pbExp)
            Me.Controls.Add(Me.Label5)
            Me.Controls.Add(Me.lblResu)
            Me.Controls.Add(Me.cmdClose)
            Me.Controls.Add(Me.cmdStartExp)
            Me.Controls.Add(Me.cmdTestExp)
            Me.Controls.Add(Me.Label4)
            Me.Controls.Add(Me.Label3)
            Me.Controls.Add(Me.tbExpFormula)
            Me.Controls.Add(Me.Label2)
            Me.Controls.Add(Me.Label1)
            Me.Name = "Form2"
            Me.Text = "EXP Changer"
            Me.ResumeLayout(False)
            Me.PerformLayout
        End Sub

        Private Sub tbExpFormula_TextChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.lblResu.Text = ""
            Dim str2 As String = ""
            Dim expression As String = ""
            Dim num As Long = &H5DC
            Dim num2 As Long = 60
            Dim str As String = Me.tbExpFormula.Text.ToString.ToUpper
            If str.Contains("EXP") Then
                str2 = str.Replace("EXP", num.ToString)
            Else
                str2 = str
            End If
            If str.Contains("LVL") Then
                expression = str2.Replace("LVL", num2.ToString)
            Else
                expression = str2
            End If
            Me.lblResu.Text = Conversions.ToString(Me.textausrechnung1(expression.ToString))
            If (Me.textausrechnung1(expression) = 0) Then
                Me.lblResu.Text = "0 or error in formula"
            End If
        End Sub

        Public Function textausrechnung1(ByVal expression As String) As Double
            Dim num As Double
            Try 
                Dim table As New DataTable
                num = Conversions.ToDouble(table.Compute(expression, Nothing))
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                num = 0
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function


        ' Properties
        Friend Overridable Property cmdClose As Button
            Get
                Return Me._cmdClose
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdClose_Click)
                If (Not Me._cmdClose Is Nothing) Then
                    RemoveHandler Me._cmdClose.Click, handler
                End If
                Me._cmdClose = WithEventsValue
                If (Not Me._cmdClose Is Nothing) Then
                    AddHandler Me._cmdClose.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdStartExp As Button
            Get
                Return Me._cmdStartExp
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdStartExp_Click)
                If (Not Me._cmdStartExp Is Nothing) Then
                    RemoveHandler Me._cmdStartExp.Click, handler
                End If
                Me._cmdStartExp = WithEventsValue
                If (Not Me._cmdStartExp Is Nothing) Then
                    AddHandler Me._cmdStartExp.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdTestExp As Button
            Get
                Return Me._cmdTestExp
            End Get
            Set(ByVal WithEventsValue As Button)
                Me._cmdTestExp = WithEventsValue
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

        Friend Overridable Property lblResu As Label
            Get
                Return Me._lblResu
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblResu = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lblSave As Label
            Get
                Return Me._lblSave
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblSave = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lblWarn As Label
            Get
                Return Me._lblWarn
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblWarn = WithEventsValue
            End Set
        End Property

        Friend Overridable Property pbExp As ProgressBar
            Get
                Return Me._pbExp
            End Get
            Set(ByVal WithEventsValue As ProgressBar)
                Me._pbExp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbExpFormula As TextBox
            Get
                Return Me._tbExpFormula
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.tbExpFormula_TextChanged)
                If (Not Me._tbExpFormula Is Nothing) Then
                    RemoveHandler Me._tbExpFormula.TextChanged, handler
                End If
                Me._tbExpFormula = WithEventsValue
                If (Not Me._tbExpFormula Is Nothing) Then
                    AddHandler Me._tbExpFormula.TextChanged, handler
                End If
            End Set
        End Property


        ' Fields
        <AccessedThroughProperty("cmdClose")> _
        Private _cmdClose As Button
        <AccessedThroughProperty("cmdStartExp")> _
        Private _cmdStartExp As Button
        <AccessedThroughProperty("cmdTestExp")> _
        Private _cmdTestExp As Button
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
        <AccessedThroughProperty("lblResu")> _
        Private _lblResu As Label
        <AccessedThroughProperty("lblSave")> _
        Private _lblSave As Label
        <AccessedThroughProperty("lblWarn")> _
        Private _lblWarn As Label
        <AccessedThroughProperty("pbExp")> _
        Private _pbExp As ProgressBar
        <AccessedThroughProperty("tbExpFormula")> _
        Private _tbExpFormula As TextBox
        Private components As IContainer
    End Class
End Namespace

