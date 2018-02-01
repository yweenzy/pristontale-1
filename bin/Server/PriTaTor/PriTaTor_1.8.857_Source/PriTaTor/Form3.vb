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
    Public Class Form3
        Inherits Form
        ' Methods
        <DebuggerNonUserCode> _
        Public Sub New()
            Me.InitializeComponent
        End Sub

        Private Sub cmdClose_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.Close
        End Sub

        Public Sub cmdStartExp_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Dim str4 As String = ""
            Dim expression As String = ""
            Dim str2 As String = ""
            Dim str3 As String = ""
            Dim flag3 As Boolean = True
            Dim flag2 As Boolean = False
            Dim flag As Boolean = False
            Dim str As String = Me.tbGoldFormula.Text.ToString.ToUpper
            Try 
                enumerator = MyProject.Forms.PriTaEditor.lbFiles.SelectedItems.GetEnumerator
                Do While enumerator.MoveNext
                    Dim num As Long
                    Dim num2 As Long
                    Dim monsterIndex As Long = Funktionen.GetMonsterIndex(Conversions.ToString(RuntimeHelpers.GetObjectValue(enumerator.Current)))
                    Dim strArray As String() = Strings.Split(Funktionen.GetMonsterGold(monsterIndex), " ", -1, CompareMethod.Binary)
                    If (strArray.Length = 1) Then
                        strArray = Strings.Split(Funktionen.GetMonsterGold(monsterIndex), ChrW(9), -1, CompareMethod.Binary)
                    End If
                    If ((strArray.Length = 1) And (strArray(0) <> "")) Then
                        num = Conversions.ToLong(strArray(0))
                        flag = True
                    Else
                        Dim num8 As Long = (strArray.Length - 1)
                        Dim i As Long = 0
                        Do While (i <= num8)
                            If (strArray(CInt(i)) <> "") Then
                                num2 = Conversions.ToLong(strArray(CInt(i)))
                                num = Conversions.ToLong(strArray(CInt((i + 1))))
                                i = (strArray.Length - 1)
                            End If
                            i = (i + 1)
                        Loop
                    End If
                    Dim monsterLVL As Long = Funktionen.GetMonsterLVL(monsterIndex)
                    If str.Contains("GOLD") Then
                        str4 = str.Replace("GOLD", num.ToString)
                    Else
                        str4 = str
                    End If
                    If str.Contains("LVL") Then
                        expression = str4.Replace("LVL", monsterLVL.ToString)
                    Else
                        expression = str4
                    End If
                    str2 = Funktionen.textausrechnung(expression).ToString
                    If Not flag Then
                        If str.Contains("GOLD") Then
                            str4 = str.Replace("GOLD", num2.ToString)
                        Else
                            str4 = str
                        End If
                        If str.Contains("LVL") Then
                            expression = str4.Replace("LVL", monsterLVL.ToString)
                        Else
                            expression = str4
                        End If
                        str3 = Funktionen.textausrechnung(expression).ToString
                    End If
                    If (Not str.Contains("GOLD") And Not str.Contains("LVL")) Then
                        If (Not Funktionen.YesNo("Warning!", "Set all selected monsters to same Gold?", 2) And flag3) Then
                            Interaction.MsgBox("canceled", MsgBoxStyle.OkOnly, Nothing)
                            Return
                        End If
                        flag3 = False
                    End If
                    If (MyProject.Forms.PriTaEditor.tbMaxGold.Text.ToString = "") Then
                        MyProject.Forms.PriTaEditor.tbMaxGold.Text = MySettingsProperty.Settings.MaxGold
                    End If
                    If (Funktionen.textausrechnung(expression) > Conversions.ToDouble(MyProject.Forms.PriTaEditor.tbMaxGold.Text.ToString)) Then
                        Dim num6 As Single
                        num6 += 1
                        Me.lblWarn.Text = ("Warnings: " & Conversions.ToString(num6))
                        Me.lblWarn.Refresh
                        flag2 = True
                    End If
                    If (str2 <> "") Then
                        MyProject.Forms.PriTaEditor.SetMonsterGold(monsterIndex, (str3 & ChrW(9) & str2))
                    End If
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
            If flag2 Then
                Interaction.MsgBox("Warning! Some monsters have to high Gold, please check options!", MsgBoxStyle.Exclamation, Nothing)
            End If
            If Funktionen.YesNo("Save", "Save all monsters?", 1) Then
                Dim num5 As Double
                Dim enumerator2 As IEnumerator
                Try 
                    enumerator2 = MyProject.Forms.PriTaEditor.lbFiles.SelectedItems.GetEnumerator
                    Do While enumerator2.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator2.Current)
                        Me.lblSave.Text = Conversions.ToString(objectValue)
                        Me.lblSave.Refresh
                        Funktionen.MonsterSaver(Funktionen.GetMonsterIndex(Conversions.ToString(objectValue)), True)
                        Me.lblSave.Text = ""
                        num5 = (num5 + (100 / CDbl(MyProject.Forms.PriTaEditor.lbFiles.SelectedItems.Count)))
                        If (num5 >= 100) Then
                            num5 = 100
                        End If
                        Me.pbExp.Value = CInt(Math.Round(num5))
                        Me.pbExp.Refresh
                    Loop
                Finally
                    If TypeOf enumerator2 Is IDisposable Then
                        TryCast(enumerator2,IDisposable).Dispose
                    End If
                End Try
                num5 = 0
                Interaction.MsgBox((Conversions.ToString(MyProject.Forms.PriTaEditor.lbFiles.SelectedItems.Count) & " monster Saved!"), MsgBoxStyle.OkOnly, Nothing)
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

        <DebuggerStepThrough> _
        Private Sub InitializeComponent()
            Me.lblWarn = New Label
            Me.lblSave = New Label
            Me.pbExp = New ProgressBar
            Me.Label2 = New Label
            Me.Label1 = New Label
            Me.cmdClose = New Button
            Me.cmdStartExp = New Button
            Me.tbGoldFormula = New TextBox
            Me.SuspendLayout
            Me.lblWarn.AutoSize = True
            Dim point As New Point(&HA8, &H8B)
            Me.lblWarn.Location = point
            Me.lblWarn.Name = "lblWarn"
            Dim size As New Size(&H40, 13)
            Me.lblWarn.Size = size
            Me.lblWarn.TabIndex = 15
            Me.lblWarn.Text = "Warnings: 0"
            Me.lblSave.AutoSize = True
            point = New Point(8, &H8E)
            Me.lblSave.Location = point
            Me.lblSave.Name = "lblSave"
            size = New Size(0, 13)
            Me.lblSave.Size = size
            Me.lblSave.TabIndex = 14
            point = New Point(11, &H9E)
            Me.pbExp.Location = point
            Me.pbExp.Name = "pbExp"
            size = New Size(&H117, 15)
            Me.pbExp.Size = size
            Me.pbExp.TabIndex = 13
            Me.Label2.AutoSize = True
            point = New Point(9, 90)
            Me.Label2.Location = point
            Me.Label2.Name = "Label2"
            size = New Size(&H9F, 13)
            Me.Label2.Size = size
            Me.Label2.TabIndex = &H11
            Me.Label2.Text = "LVL = Level of selected monster"
            Me.Label1.AutoSize = True
            point = New Point(8, &H4D)
            Me.Label1.Location = point
            Me.Label1.Name = "Label1"
            size = New Size(&H9E, 13)
            Me.Label1.Size = size
            Me.Label1.TabIndex = &H10
            Me.Label1.Text = "Gold = Gold of selected monster"
            point = New Point(&HD7, 12)
            Me.cmdClose.Location = point
            Me.cmdClose.Name = "cmdClose"
            size = New Size(&H4B, &H17)
            Me.cmdClose.Size = size
            Me.cmdClose.TabIndex = &H17
            Me.cmdClose.Text = "Cancel"
            Me.cmdClose.TextImageRelation = TextImageRelation.ImageAboveText
            Me.cmdClose.UseVisualStyleBackColor = True
            point = New Point(&HD7, &H55)
            Me.cmdStartExp.Location = point
            Me.cmdStartExp.Name = "cmdStartExp"
            size = New Size(&H4B, &H17)
            Me.cmdStartExp.Size = size
            Me.cmdStartExp.TabIndex = &H16
            Me.cmdStartExp.Text = "Start"
            Me.cmdStartExp.UseVisualStyleBackColor = True
            Me.tbGoldFormula.DataBindings.Add(New Binding("Text", MySettings.Default, "GoldFormel", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(11, &H74)
            Me.tbGoldFormula.Location = point
            Me.tbGoldFormula.Name = "tbGoldFormula"
            size = New Size(&H117, 20)
            Me.tbGoldFormula.Size = size
            Me.tbGoldFormula.TabIndex = 3
            Me.tbGoldFormula.Text = MySettings.Default.GoldFormel
            Dim ef As New SizeF(6!, 13!)
            Me.AutoScaleDimensions = ef
            Me.AutoScaleMode = AutoScaleMode.Font
            size = New Size(&H12E, &HB6)
            Me.ClientSize = size
            Me.Controls.Add(Me.cmdClose)
            Me.Controls.Add(Me.cmdStartExp)
            Me.Controls.Add(Me.Label2)
            Me.Controls.Add(Me.Label1)
            Me.Controls.Add(Me.lblWarn)
            Me.Controls.Add(Me.lblSave)
            Me.Controls.Add(Me.pbExp)
            Me.Controls.Add(Me.tbGoldFormula)
            Me.Name = "Form3"
            Me.Text = "Gold Changer"
            Me.ResumeLayout(False)
            Me.PerformLayout
        End Sub


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

        Friend Overridable Property tbGoldFormula As TextBox
            Get
                Return Me._tbGoldFormula
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbGoldFormula = WithEventsValue
            End Set
        End Property


        ' Fields
        <AccessedThroughProperty("cmdClose")> _
        Private _cmdClose As Button
        <AccessedThroughProperty("cmdStartExp")> _
        Private _cmdStartExp As Button
        <AccessedThroughProperty("Label1")> _
        Private _Label1 As Label
        <AccessedThroughProperty("Label2")> _
        Private _Label2 As Label
        <AccessedThroughProperty("lblSave")> _
        Private _lblSave As Label
        <AccessedThroughProperty("lblWarn")> _
        Private _lblWarn As Label
        <AccessedThroughProperty("pbExp")> _
        Private _pbExp As ProgressBar
        <AccessedThroughProperty("tbGoldFormula")> _
        Private _tbGoldFormula As TextBox
        Private components As IContainer
    End Class
End Namespace

