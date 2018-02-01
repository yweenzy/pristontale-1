Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports PriTaTor.My
Imports System
Imports System.Collections
Imports System.ComponentModel
Imports System.Diagnostics
Imports System.Drawing
Imports System.IO
Imports System.Runtime.CompilerServices
Imports System.Runtime.InteropServices
Imports System.Text
Imports System.Windows.Forms

Namespace PriTaTor
    <DesignerGenerated> _
    Public Class PriTaEditor
        Inherits Form
        ' Methods
        <DebuggerNonUserCode> _
        Public Sub New()
            AddHandler MyBase.Load, New EventHandler(AddressOf Me.PriTaEditor_Load)
            Me.InitializeComponent
        End Sub

        Private Sub AddAsNewBossToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView3.SelectedItems.Count >= 1) Then
                Dim item As ListViewItem = Me.ListView1.Items.Add(Me.ListView3.SelectedItems.Item(0).Text)
                item.SubItems.Add(Me.ListView3.SelectedItems.Item(0).SubItems.Item(1).Text)
                item.SubItems.Add("add a guard")
                item.SubItems.Add("add a guard")
                item.SubItems.Add("7")
                item.SubItems.Add("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23")
                item = Nothing
            End If
        End Sub

        Private Sub AddDroplineToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFiles.SelectedItems.Count = 0) Then
                Interaction.MsgBox("please select an monster", MsgBoxStyle.OkOnly, Nothing)
            Else
                Try 
                    Dim num2 As Long
                    Dim monsterIndex As Long = Funktionen.GetMonsterIndex(Conversions.ToString(Me.lbFiles.SelectedItem))
                    Do While (Konstanten.MonsterDatenListe(CInt(monsterIndex), CInt(num2)) <> "End of File")
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), CInt(num2)).Trim(New Char() { " "c }).Trim(New Char() { ChrW(9) }).Contains(Me.lwItems.SelectedItems.Item(0).SubItems.Item(1).Text.Trim(New Char() { " "c }).Trim(New Char() { ChrW(9) })) Then
                            Dim enumerator As IEnumerator
                            Konstanten.MonsterDatenListe(CInt(monsterIndex), CInt(num2)) = (Konstanten.MonsterDatenListe(CInt(monsterIndex), CInt(num2)) & ChrW(13) & ChrW(10) & "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & " 100" & ChrW(9) & "Free")
                            Funktionen.MonsterSaver(monsterIndex, True)
                            Funktionen.ReloadMonster(monsterIndex)
                            Try 
                                enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                                Do While enumerator.MoveNext
                                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                                    Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                                Loop
                            Finally
                                If TypeOf enumerator Is IDisposable Then
                                    TryCast(enumerator,IDisposable).Dispose
                                End If
                            End Try
                            Me.lbFiles.SelectedItem = Konstanten.MonsterFiles(CInt(monsterIndex))
                            Me.MonsterAuswertung
                            Return
                        End If
                        num2 = (num2 + 1)
                    Loop
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    Interaction.MsgBox(exception.Message, MsgBoxStyle.OkOnly, Nothing)
                    Funktionen.WriteErrorLog((String.Concat(New String() { "Add new dropline: " & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })))
                    ProjectData.ClearProjectError
                End Try
            End If
        End Sub

        Private Sub AddItemsToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            MyProject.Forms.FormItemFound.Show
        End Sub

        Private Sub AddToListToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.cbItemSelector.Text <> "") Then
                Dim flag As Boolean
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.cbItemSelector.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        If (RuntimeHelpers.GetObjectValue(enumerator.Current).ToString.ToUpper = Me.cbItemSelector.Text.ToUpper) Then
                            flag = True
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                If Not flag Then
                    Me.cbItemSelector.Items.Add(Me.cbItemSelector.Text)
                End If
            End If
        End Sub

        Private Sub AddToMapToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView3.SelectedItems.Count >= 1) Then
                If (Me.lbFilesMaps.SelectedItems.Count < 1) Then
                    Interaction.MsgBox("Please select a map first", MsgBoxStyle.OkOnly, Nothing)
                ElseIf Not Versioned.IsNumeric(Me.tbMapSpawnRate.Text) Then
                    Interaction.MsgBox("Spawnrate is not numeric!", MsgBoxStyle.OkOnly, Nothing)
                Else
                    Dim enumerator As IEnumerator
                    Me.tbMapSpawnRate.Text = Conversions.ToString(Math.Abs(Conversions.ToInteger(Me.tbMapSpawnRate.Text)))
                    Try 
                        enumerator = Me.ListView3.SelectedItems.GetEnumerator
                        Do While enumerator.MoveNext
                            Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                            Dim item2 As ListViewItem = Me.ListView2.Items.Add(current.Text)
                            item2.SubItems.Add(current.SubItems.Item(1))
                            item2.SubItems.Add(Me.tbMapSpawnRate.Text)
                            item2 = Nothing
                        Loop
                    Finally
                        If TypeOf enumerator Is IDisposable Then
                            TryCast(enumerator,IDisposable).Dispose
                        End If
                    End Try
                End If
            End If
        End Sub

        Private Sub AddToSelectedBossToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView1.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select a boss!", MsgBoxStyle.OkOnly, Nothing)
            ElseIf (Me.ListView3.SelectedItems.Count >= 1) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.ListView1.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                        If current.Selected Then
                            current.Text = Me.ListView3.SelectedItems.Item(0).Text
                            current.SubItems.Item(1).Text = Me.ListView3.SelectedItems.Item(0).SubItems.Item(1).Text
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub AddToSeletedBossToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView1.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select a boss!", MsgBoxStyle.OkOnly, Nothing)
            ElseIf (Me.ListView3.SelectedItems.Count >= 1) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.ListView1.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                        If current.Selected Then
                            current.SubItems.Item(2).Text = Me.ListView3.SelectedItems.Item(0).Text
                            current.SubItems.Item(3).Text = Me.ListView3.SelectedItems.Item(0).SubItems.Item(1).Text
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub AlleDatenLaden()
            Dim num As Byte
            Konstanten.Anzahl = 0
            Me.lblProg.Text = "Deleting Data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Do While (Konstanten.MonsterFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.MonsterFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Do While (Konstanten.ItemFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.ItemFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Do While (Konstanten.MapFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.MapFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Do While (Konstanten.NPCFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.NPCFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Do While (Konstanten.SPCFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.SPCFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Do While (Konstanten.SPPFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.SPPFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Dim a As Double = 0
            Me.Text = ("PriTaTor V.1.8.857 ServerPath:" & MySettingsProperty.Settings.sspath)
            Me.lblprgV.Text = "PriTaTor V.1.8.857"
            If (Konstanten.sPath = Nothing) Then
                Konstanten.sPath = MySettingsProperty.Settings.sspath
            End If
            Me.MoFound.Text = "0"
            Me.ItemFound.Text = "0"
            Me.Mapsfound.Text = "0"
            Me.lblProg.Text = "Loading monster files"
            Me.lblProg.Refresh
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Monster\*.inf"), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.MonsterFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Me.MoFound.Text = Conversions.ToString(Konstanten.Anzahl)
            Konstanten.MonsterDatenListe = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Me.lblProg.Text = "Reading monster data"
            Me.lblProg.Refresh
            Dim num10 As Integer = (Konstanten.Anzahl - 1)
            Dim i As Integer = 0
            Do While (i <= num10)
                Dim reader As New StreamReader((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MonsterFiles(i)), Konstanten.enc)
                Konstanten.Index = 0
                Konstanten.MonsterName(i) = ""
                Konstanten.MonsterMapName(i) = ""
                Do While (reader.Peek <> -1)
                    Konstanten.MonsterDatenListe(i, Konstanten.Index) = reader.ReadLine
                    If Konstanten.MonsterDatenListe(i, Konstanten.Index).Contains("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                        Konstanten.MoNamePath = Konstanten.MonsterDatenListe(i, Konstanten.Index).Substring(Strings.Len("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207))).ToString.Trim
                        Konstanten.MonsterZhoonFile(i) = (Konstanten.sPath & "GameServer\Monster\" & Konstanten.MoNamePath.Trim(New Char() { """"c }))
                        Konstanten.MonsterName(i) = Funktionen.GetMonsterInGameName(Konstanten.MoNamePath)
                    End If
                    If Konstanten.MonsterDatenListe(i, Konstanten.Index).StartsWith("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)) Then
                        Konstanten.MonsterLevels(i) = Conversions.ToString(Conversions.ToLong(Konstanten.MonsterDatenListe(i, Konstanten.Index).Substring(Strings.Len("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167))).Trim.ToString))
                    End If
                    If Konstanten.MonsterDatenListe(i, Konstanten.Index).StartsWith("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)) Then
                        Konstanten.MonsterMapName(i) = Funktionen.Textausschnitt("""", Konstanten.MonsterDatenListe(i, Konstanten.Index).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167))))
                    End If
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader.ReadToEnd
                        Interaction.MsgBox(("Error in loading Monster File:" & Konstanten.MonsterFiles(i) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Error in loading Monster File:" & Konstanten.MonsterFiles(i) & " File to long!" & ChrW(13) & ChrW(10) & "Index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.MonsterDatenListe(i, Konstanten.Index) = "End of File"
                reader.Close
                a = (a + (20 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(a))
                i += 1
            Loop
            Me.lblProg.Text = "Loading item files"
            Me.lblProg.Refresh
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\OpenItem\*.txt"), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.ItemFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Me.ItemFound.Text = Conversions.ToString(Konstanten.Anzahl)
            Me.lblProg.Text = "Reading item data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Konstanten.ItemDatenListe = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Konstanten.ItemName = New String(((Konstanten.Anzahl - 1) + 1)  - 1) {}
            Dim num11 As Integer = (Konstanten.Anzahl - 1)
            Dim j As Integer = 0
            Do While (j <= num11)
                Dim reader2 As New StreamReader((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemFiles(j)), Konstanten.enc)
                Konstanten.Index = 0
                Konstanten.ItemName(j) = "No name found"
                Do While (reader2.Peek <> -1)
                    Konstanten.ItemDatenListe(j, Konstanten.Index) = reader2.ReadLine
                    If Konstanten.ItemDatenListe(j, Konstanten.Index).Contains("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                        Konstanten.ItemNamePath = Konstanten.ItemDatenListe(j, Konstanten.Index).Substring(Strings.Len("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207))).ToString.Trim
                        If Konstanten.ItemNamePath.Contains(":") Then
                            If File.Exists(Konstanten.ItemNamePath.Trim(New Char() { """"c })) Then
                                Konstanten.ItemZhoonFile(j) = (Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemNamePath.Trim(New Char() { """"c }))
                                Dim reader3 As New StreamReader(Konstanten.ItemNamePath.Trim(New Char() { """"c }), Konstanten.enc)
                                Do While (reader3.Peek <> -1)
                                    Dim str As String = reader3.ReadLine
                                    If str.Contains("*J_") Then
                                        Konstanten.ItemName(j) = str.Substring(7).ToString.Trim
                                        If (Konstanten.ItemName(j) = "") Then
                                            Konstanten.ItemName(j) = "No name found"
                                        End If
                                    End If
                                Loop
                            Else
                                Konstanten.ItemZhoonFile(j) = "No Zhoon found"
                                If Me.cbMoZhoonWarn.Checked Then
                                    Interaction.MsgBox(("No .zhoon File Found! " & Konstanten.ItemNamePath.Trim(New Char() { """"c })), MsgBoxStyle.OkOnly, Nothing)
                                End If
                                Funktionen.WriteErrorLog((("In Loaddata: Warn" & ChrW(13) & ChrW(10) & "No .zhoon file found! " & ChrW(13) & ChrW(10) & "Itemfile: " & Konstanten.ItemFiles(j) & ChrW(13) & ChrW(10) & "Item zhoon Path: " & Konstanten.ItemNamePath)))
                            End If
                        ElseIf File.Exists((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemNamePath.Trim(New Char() { """"c }))) Then
                            Konstanten.ItemZhoonFile(j) = (Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemNamePath.Trim(New Char() { """"c }))
                            Konstanten.ItemNamePath = (Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemNamePath.Trim(New Char() { """"c }))
                            Dim reader4 As New StreamReader(Konstanten.ItemNamePath.Trim(New Char() { """"c }), Konstanten.enc)
                            Do While (reader4.Peek <> -1)
                                Dim str2 As String = reader4.ReadLine
                                If str2.Contains("*J_") Then
                                    Konstanten.ItemName(j) = str2.Substring(7).ToString.Trim
                                    If (Konstanten.ItemName(j) = "") Then
                                        Konstanten.ItemName(j) = "No name found"
                                    End If
                                End If
                            Loop
                            reader4.Close
                        Else
                            Konstanten.ItemNamePath = (Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemNamePath.Trim(New Char() { """"c }))
                            Konstanten.ItemZhoonFile(j) = "No Zhoon found"
                            If Me.cbMoZhoonWarn.Checked Then
                                Interaction.MsgBox(("No .zhoon File Found! " & Konstanten.ItemNamePath), MsgBoxStyle.OkOnly, Nothing)
                            End If
                            Funktionen.WriteErrorLog((("In Loaddata: Warn" & ChrW(13) & ChrW(10) & "No .zhoon file found! " & ChrW(13) & ChrW(10) & "Itemfile: " & Konstanten.ItemFiles(j) & ChrW(13) & ChrW(10) & "Item zhoon Path: " & Konstanten.ItemNamePath)))
                        End If
                    End If
                    If Konstanten.ItemDatenListe(j, Konstanten.Index).StartsWith("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)) Then
                        Konstanten.ItemCodes(j) = Konstanten.ItemDatenListe(j, Konstanten.Index).Substring(Strings.Len("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229))).Trim.Replace(" ", " ").Replace(ChrW(9), " ").ToUpper
                    End If
                    If Konstanten.ItemDatenListe(j, Konstanten.Index).StartsWith("*" & ChrW(185) & ChrW(171) & ChrW(176) & ChrW(212)) Then
                        Konstanten.ItemWeights(j) = Konstanten.ItemDatenListe(j, Konstanten.Index).Substring(Strings.Len("*" & ChrW(185) & ChrW(171) & ChrW(176) & ChrW(212))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(j, Konstanten.Index).StartsWith("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)) Then
                        Konstanten.ItemLevels(j) = Konstanten.ItemDatenListe(j, Konstanten.Index).Substring(Strings.Len("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader2.ReadToEnd
                        Interaction.MsgBox(("Error in loading Item File:" & Konstanten.ItemFiles(j) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((String.Concat(New String() { "Error in loading Item File:", Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemFiles(j), " File to long!" & ChrW(13) & ChrW(10) & "Index=", Conversions.ToString(Konstanten.Index) })))
                    End If
                Loop
                If (Konstanten.ItemLevels(j) = Nothing) Then
                    Konstanten.ItemLevels(j) = ""
                End If
                Konstanten.ItemDatenListe(j, Konstanten.Index) = "End of File"
                reader2.Close
                a = (a + (20 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(a))
                j += 1
            Loop
            Me.lblProg.Text = "Loading map files"
            Me.lblProg.Refresh
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Field\" & Konstanten.NPCPosEndung), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.SPCFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Dim num3 As Integer = 0
            Dim num12 As Integer = (Konstanten.Anzahl - 1)
            Dim k As Integer = 0
            Do While (k <= num12)
                If (Konstanten.SPCFiles(k) <> "") Then
                    Dim stream As New FileStream((Konstanten.sPath & "GameServer\Field\" & Konstanten.SPCFiles(k)), FileMode.Open, FileAccess.Read)
                    Do While (stream.Position <> stream.Length)
                        num = CByte(stream.ReadByte)
                        Konstanten.SPCDaten(k, num3) = num
                        num3 += 1
                    Loop
                    num3 = 0
                    stream.Close
                End If
                k += 1
            Loop
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Field\" & Konstanten.SpawnPosiEndung), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.SPPFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Dim num13 As Integer = (Konstanten.Anzahl - 1)
            Dim m As Integer = 0
            Do While (m <= num13)
                num3 = 0
                If (Konstanten.SPPFiles(m) <> "") Then
                    Dim stream2 As New FileStream((Konstanten.sPath & "GameServer\Field\" & Konstanten.SPPFiles(m)), FileMode.Open, FileAccess.Read)
                    Do While (stream2.Position <> stream2.Length)
                        num = CByte(stream2.ReadByte)
                        Konstanten.SPPDaten(m, num3) = num
                        num3 += 1
                    Loop
                    num3 = 0
                    stream2.Close
                End If
                m += 1
            Loop
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Field\*.spm"), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.MapFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Me.Mapsfound.Text = Conversions.ToString(Konstanten.Anzahl)
            Me.lblProg.Text = "Reading map data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Konstanten.MapDatenListe = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Dim num14 As Integer = (Konstanten.Anzahl - 1)
            Dim n As Integer = 0
            Do While (n <= num14)
                Dim reader5 As New StreamReader((Konstanten.sPath & "GameServer\Field\" & Konstanten.MapFiles(n)), Konstanten.enc)
                Konstanten.Index = 0
                Do While (reader5.Peek <> -1)
                    Konstanten.MapDatenListe(n, Konstanten.Index) = reader5.ReadLine
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader5.ReadToEnd
                        Interaction.MsgBox(("Error in loading Map File:" & Konstanten.MapFiles(n) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Error in loading Map File:" & Konstanten.MapFiles(n) & " File to long!" & ChrW(13) & ChrW(10) & "Index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.MapDatenListe(n, Konstanten.Index) = "End of File"
                Me.lblTextCoding.Text = (reader5.CurrentEncoding.HeaderName & "/" & Encoding.Default.EncodingName)
                reader5.Close
                a = (a + (20 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(a))
                n += 1
            Loop
            Me.lblProg.Text = "Loading NPC files"
            Me.lblProg.Refresh
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCEndung), FileAttribute.Normal)
            Me.tbNPCSetupfile.Items.Clear
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.NPCFiles(Konstanten.Anzahl) = Konstanten.sFile.ToUpper
                    Me.tbNPCSetupfile.Items.Add(Konstanten.NPCFiles(Konstanten.Anzahl))
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Index = 0
            Me.lblProg.Text = "Reading NPC Data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Konstanten.NPCData = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Me.tbNPCModelFile.Items.Clear
            Dim num15 As Integer = (Konstanten.Anzahl - 1)
            Dim num9 As Integer = 0
            Do While (num9 <= num15)
                Dim reader6 As New StreamReader((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCFiles(num9)), Konstanten.enc)
                Konstanten.Index = 0
                Do While (reader6.Peek <> -1)
                    Konstanten.NPCData(num9, Konstanten.Index) = reader6.ReadLine
                    If Konstanten.NPCData(num9, Konstanten.Index).StartsWith(Konstanten.NPCSetupInIErkennung) Then
                        Konstanten.NPCSetupIni(num9) = Funktionen.Textausschnitt("""", Konstanten.NPCData(num9, Konstanten.Index)).ToUpper
                        Me.tbNPCModelFile.Items.Add(Konstanten.NPCSetupIni(num9))
                    End If
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader6.ReadToEnd
                        Interaction.MsgBox(("Error in loading Map File:" & Konstanten.MapFiles(num9) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Error in loading Map File:" & Konstanten.MapFiles(num9) & " File to long!" & ChrW(13) & ChrW(10) & "Index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.NPCData(num9, Konstanten.Index) = "End of File"
                Konstanten.NPCNames(num9) = Me.GetNPCName((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCFiles(num9)))
                Me.lblTextCoding.Text = (reader6.CurrentEncoding.HeaderName & "/" & Encoding.Default.EncodingName)
                reader6.Close
                a = (a + (20 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(a))
                num9 += 1
            Loop
            Dim list As New ArrayList
            Me.tbNPCModelFile.AutoCompleteCustomSource.Clear
            Dim str3 As String
            For Each str3 In Directory.GetFiles((Konstanten.sPath & "\char"), "*.inx", SearchOption.AllDirectories)
                Me.tbNPCSetupfileInI.Items.Add(str3.Replace((Konstanten.sPath & "\"), ""))
            Next
            Me.pbWorking.Value = 100
            Me.lblProg.Text = "Finisched loading"
        End Sub

        Private Sub BackupsToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If ((Me.lbFiles.SelectedItems.Count >= 2) AndAlso Funktionen.YesNo("Load defaults", "Do you want load default for all selected monster?", 1)) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.lbFiles.SelectedItems.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Funktionen.loadBackupMonster(Conversions.ToString(Operators.ConcatenateObject("Default_", objectValue)), Funktionen.GetMonsterIndex(Conversions.ToString(objectValue)))
                        Funktionen.MonsterSaver(Funktionen.GetMonsterIndex(Conversions.ToString(objectValue)), True)
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub BackupsToolStripMenuItem_DropDownItemClicked(ByVal sender As Object, ByVal e As ToolStripItemClickedEventArgs)
            Funktionen.loadBackupMonster(e.ClickedItem.Text.ToString, Funktionen.GetMonsterIndex(Conversions.ToString(Me.lbFiles.SelectedItem)))
            Me.MonsterAuswertung
        End Sub

        Private Sub BringBackToMapToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.tbNPCx.Text = Conversions.ToString(CDbl((Konstanten.Posx + 100)))
            Me.tbNPCz.Text = Conversions.ToString(CDbl((Konstanten.Posy - 100)))
        End Sub

        Private Sub Button3_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFiles.SelectedItems.Count = 0) Then
                Interaction.MsgBox("Please select a monster", MsgBoxStyle.OkOnly, Nothing)
            Else
                Programmstarts.Execute(Konstanten.EditorExe, Konstanten.MonsterZhoonFile(CInt(Funktionen.GetMonsterIndex(Conversions.ToString(Me.lbFiles.SelectedItem)))))
            End If
        End Sub

        Private Sub Button3_Click_1(ByVal sender As Object, ByVal e As EventArgs)
            Dim errorText As String = "Dies ist ein Test"
            Funktionen.WriteErrorLog((errorText))
        End Sub

        Private Sub cbItemMo_Click(ByVal sender As Object, ByVal e As EventArgs)
            If Not Me.cbItemMo.Checked Then
                Me.lbItemMo.Items.Clear
            Else
                Me.ItemAuswertung(Funktionen.GetItemIndex(Me.lbFileListItems.SelectedItem.ToString))
                Me.lbItemsListCount.Text = (Conversions.ToString(Me.lbFileListItems.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFileListItems.Items.Count))
            End If
        End Sub

        Private Sub cbItemSelector_KeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
            If (e.KeyChar = ChrW(13)) Then
                Me.MakeItemFileList
            End If
        End Sub

        Private Sub cbItemSelector_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.lbFileListItems.Items.Clear
            Me.MakeItemFileList
            Me.lbItemsListCount.Text = (Conversions.ToString(Me.lbFileListItems.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFileListItems.Items.Count))
        End Sub

        Private Sub cbMonsterSelector_KeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
            If (e.KeyChar = ChrW(13)) Then
                Dim enumerator As IEnumerator
                Me.lbFiles.Items.Clear
                Try 
                    enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub cbMonsterSelector_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Me.lbFiles.Items.Clear
            Try 
                enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub cbMonsterSelector1_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Me.ListView3.Items.Clear
            Try 
                enumerator = Me.MakeFileList(Me.cbMonsterSelector1.Text).GetEnumerator
                Do While enumerator.MoveNext
                    Dim monsterIndex As Integer = CInt(Funktionen.GetMonsterIndex(Conversions.ToString(RuntimeHelpers.GetObjectValue(enumerator.Current))))
                    If (monsterIndex = -1) Then
                        Return
                    End If
                    Me.ListView3.Items.Add(Konstanten.MonsterFiles(monsterIndex)).SubItems.Add(Konstanten.MonsterName(monsterIndex))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub cbSelectAll_CheckedChanged(ByVal sender As Object, ByVal e As EventArgs)
            Dim num2 As Long = (Me.lbFiles.Items.Count - 1)
            Dim i As Long = 0
            Do While (i <= num2)
                Me.lbFiles.SetSelected(CInt(i), Me.cbSelectAll.Checked)
                i = (i + 1)
            Loop
        End Sub

        Private Sub CBShopItem_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.FillNPCShop
        End Sub

        Private Sub chItemInfo_CheckedChanged(ByVal sender As Object, ByVal e As EventArgs)
            If Not Me.chItemInfo.Checked Then
                Me.lbItemFiles.Items.Clear
                Me.lbItemsRealName.Items.Clear
            Else
                Me.Getitems
            End If
        End Sub

        Private Sub chMapEn_CheckedChanged(ByVal sender As Object, ByVal e As EventArgs)
            If Me.chMapEn.Checked Then
                Konstanten.CheckMap = True
                Me.GefundenMaps
            Else
                Konstanten.CheckMap = False
                Me.lbMaps.Items.Clear
            End If
        End Sub

        Private Sub chNotFound_CheckedChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.GefundenMaps
        End Sub

        Private Sub cmd_Check_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim num As Long
            Dim collection As New Collection
            Me.lbFiles.SelectedItems.Clear
            If Versioned.IsNumeric(Me.tbMaxExp.Text.ToString) Then
                Dim num2 As Long
                Do While (Konstanten.MonsterFiles(CInt(num2)) <> "")
                    If Funktionen.CheckMaxValues(num2, "*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161), Conversions.ToLong(Me.tbMaxExp.Text)) Then
                        collection.Add(Konstanten.MonsterFiles(CInt(num2)), Nothing, Nothing, Nothing)
                        num = (num + 1)
                    End If
                    num2 = (num2 + 1)
                Loop
            Else
                Interaction.MsgBox(("Error: " & Me.tbMaxExp.Text & " is not numeric"), MsgBoxStyle.OkOnly, Nothing)
                Funktionen.WriteErrorLog((("Error in expcheck:" & ChrW(13) & ChrW(10) & "Error: " & Me.tbMaxExp.Text & " is not numeric")))
                Return
            End If
            If (num > 0) Then
                Dim enumerator As IEnumerator
                Interaction.MsgBox(("Found " & Conversions.ToString(num) & " Monsters! All will show now"), MsgBoxStyle.OkOnly, Nothing)
                Me.TabControl1.SelectedIndex = 0
                Me.cbMonsterSelector.Text = "Name="
                Me.lbFiles.Items.Clear
                Try 
                    enumerator = collection.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
            If (num <= 0) Then
                Interaction.MsgBox("Nothing found!", MsgBoxStyle.OkOnly, Nothing)
            End If
        End Sub

        Private Sub CmdCheckDrop_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim monsterIndex As Long = 0
            Dim item As String = ""
            Dim num As Long = 0
            Dim collection As New Collection
            Try 
                Dim enumerator As IEnumerator
                Dim strArray As String() = Strings.Split(Me.tbWarnItem.Text.ToString, ",", -1, CompareMethod.Binary)
                If (strArray.Length = 1) Then
                    Do While (Konstanten.MonsterFiles(CInt(monsterIndex)) <> "")
                        item = Funktionen.FindenText(monsterIndex, "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219), strArray(0))
                        If (item <> "") Then
                            collection.Add(item, Nothing, Nothing, Nothing)
                            num = (num + 1)
                        End If
                        monsterIndex = (monsterIndex + 1)
                    Loop
                    goto Label_00EF
                End If
                Dim num4 As Long = (strArray.Length - 1)
                Dim num3 As Long = 0
                goto Label_00E9
            Label_0094:
                item = Funktionen.FindenText(monsterIndex, "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219), strArray(CInt(num3)))
                If (item <> "") Then
                    collection.Add(item, Nothing, Nothing, Nothing)
                    num = (num + 1)
                End If
                monsterIndex = (monsterIndex + 1)
            Label_00CB:
                If (Konstanten.MonsterFiles(CInt(monsterIndex)) <> "") Then
                    goto Label_0094
                End If
                num3 = (num3 + 1)
            Label_00E9:
                If (num3 <= num4) Then
                    goto Label_00CB
                End If
            Label_00EF:
                Interaction.MsgBox(("Found " & Conversions.ToString(num) & " Monsters! All are selected now"), MsgBoxStyle.OkOnly, Nothing)
                Me.TabControl1.SelectedIndex = 0
                Me.cbMonsterSelector.Text = "Name="
                Me.lbFiles.Items.Clear
                Try 
                    enumerator = collection.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "SetMonsterGold" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub cmdCheckGold_Click_1(ByVal sender As Object, ByVal e As EventArgs)
            Dim num As Long = 0
            Dim collection As New Collection
            If Versioned.IsNumeric(Me.tbMaxGold.Text) Then
                Dim num2 As Long
                Me.lbFiles.SelectedItems.Clear
                Do While (Konstanten.MonsterFiles(CInt(num2)) <> "")
                    If Funktionen.CheckGold(num2, Conversions.ToLong(Me.tbMaxGold.Text)) Then
                        collection.Add(Konstanten.MonsterFiles(CInt(num2)), Nothing, Nothing, Nothing)
                        num = (num + 1)
                    End If
                    num2 = (num2 + 1)
                Loop
            Else
                Interaction.MsgBox(("Error: " & Me.tbMaxGold.Text & " is not numeric"), MsgBoxStyle.OkOnly, Nothing)
                Funktionen.WriteErrorLog((("Error in goldcheck:" & ChrW(13) & ChrW(10) & "Error: " & Me.tbMaxGold.Text & " is not numeric")))
                Return
            End If
            If (num > 0) Then
                Dim enumerator As IEnumerator
                Interaction.MsgBox(("Found " & Conversions.ToString(num) & " Monsters! All Monsters show now!"), MsgBoxStyle.OkOnly, Nothing)
                Me.TabControl1.SelectedIndex = 0
                Me.cbMonsterSelector.Text = "Name="
                Me.lbFiles.Items.Clear
                Try 
                    enumerator = collection.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
            If (num <= 0) Then
                Interaction.MsgBox("Nothing found!", MsgBoxStyle.OkOnly, Nothing)
            End If
        End Sub

        Private Sub cmdConfigEdit_Click(ByVal sender As Object, ByVal e As EventArgs)
            If File.Exists((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt")) Then
                Programmstarts.Execute(Konstanten.EditorExe, (MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"))
            Else
                Me.ReadConfigFile
                Interaction.MsgBox("No Config file found! Default file created", MsgBoxStyle.OkOnly, Nothing)
                Programmstarts.Execute(Konstanten.EditorExe, (MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"))
            End If
        End Sub

        Private Sub cmdDefaultConfig_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim stream As New FileStream((Application.StartupPath & "\PriTaTor.Config.txt"), FileMode.Create, FileAccess.Write)
            Dim writer As New StreamWriter(stream)
            writer.WriteLine(MySettingsProperty.Settings.Config)
            writer.Close
            Interaction.MsgBox("Created default config File", MsgBoxStyle.OkOnly, Nothing)
            Me.ReadConfigFile
        End Sub

        Private Sub cmdDelBackup_Click(ByVal sender As Object, ByVal e As EventArgs)
            If Funktionen.YesNo("Deleting!", "Delete all monster-backupfiles?", 2) Then
                Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MoBackupPath & "\*.inf"), FileAttribute.Normal)
                Do While (Konstanten.sFile <> "")
                    If (((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) AndAlso Konstanten.sFile.Contains(Konstanten.MoBackupNameAdd)) Then
                        File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", Konstanten.sFile }))
                    End If
                    Konstanten.sFile = FileSystem.Dir
                Loop
            End If
            If Funktionen.YesNo("Deleting!", "Delete all item-backupfiles?", 2) Then
                Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemBackupPath & "\*.txt"), FileAttribute.Normal)
                Do While (Konstanten.sFile <> "")
                    If (((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) AndAlso Konstanten.sFile.Contains(Konstanten.ItemBackupNameAdd)) Then
                        File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", Konstanten.sFile }))
                    End If
                    Konstanten.sFile = FileSystem.Dir
                Loop
            End If
        End Sub

        Private Sub cmdEditor_Click(ByVal sender As Object, ByVal e As EventArgs)
            Try 
                If (Me.dlgFile.ShowDialog <> DialogResult.Cancel) Then
                    Me.tbEditorPath.Text = Me.dlgFile.FileName
                    Konstanten.EditorExe = Me.tbEditorPath.Text
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "Button1-EditorFile" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub cmdItemRealName_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFileListItems.SelectedItems.Count = 0) Then
                Interaction.MsgBox("please select a item", MsgBoxStyle.OkOnly, Nothing)
            Else
                Programmstarts.Execute(Konstanten.EditorExe, Konstanten.ItemZhoonFile(CInt(Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem)))))
            End If
        End Sub

        Private Sub cmdItemSave_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ItemSave(Conversions.ToString(Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem))))
        End Sub

        Private Sub cmdLoadConfig_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ReadConfigFile
        End Sub

        Private Sub cmdMapSave_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.SaveMap(Conversions.ToString(Me.lbFilesMaps.SelectedItem))
        End Sub

        Private Sub cmdNPCReload_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.AlleDatenLaden
            Me.lbNPCMapFileList.Items.Clear
            Me.ListeFüllen("GameServer\Field\")
        End Sub

        Private Sub cmdNPCSave_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbNPCList.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select NPC", MsgBoxStyle.OkOnly, Nothing)
            ElseIf (Me.lbNPCMapFileList.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select a map file", MsgBoxStyle.OkOnly, Nothing)
            Else
                Dim selectedIndex As Integer = Me.lbNPCMapFileList.SelectedIndex
                Dim num As Integer = &H48470070
                Dim strArray As String() = New String(&H3E9  - 1) {}
                Dim path As String = Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))
                If Not File.Exists(path) Then
                    Interaction.MsgBox("No NPC File found! Cant save NPC", MsgBoxStyle.OkOnly, Nothing)
                Else
                    Dim num2 As Integer = (&H1F8 * Me.lbNPCList.SelectedIndex)
                    If (Me.tbNPCModelFile.Text.Length > &H40) Then
                        Interaction.MsgBox("Error: Max. 64 chars supported in NPC model file" & ChrW(13) & ChrW(10) & "NPC not saved!", MsgBoxStyle.OkOnly, Nothing)
                    ElseIf (Me.tbNPCSetupfile.Text.Length > &H40) Then
                        Interaction.MsgBox("Error: Max. 64 chars supported in NPC setup file" & ChrW(13) & ChrW(10) & "NPC not saved!", MsgBoxStyle.OkOnly, Nothing)
                    Else
                        If (((Not Versioned.IsNumeric(Me.tbNPCID.Text) Or Not Versioned.IsNumeric(Me.tbNPCx.Text)) Or Not Versioned.IsNumeric(Me.tbNPCy.Text)) Or Not Versioned.IsNumeric(Me.tbNPCz.Text)) Then
                            Interaction.MsgBox("Error: Please check all values, one or some are not numeric!" & ChrW(13) & ChrW(10) & "NPC not saved!", MsgBoxStyle.OkOnly, Nothing)
                        End If
                        If (Conversions.ToDouble(Me.tbNPCID.Text) > 16777215) Then
                            Interaction.MsgBox("Error: ID value is to high!" & ChrW(13) & ChrW(10) & "NPC not saved!", MsgBoxStyle.OkOnly, Nothing)
                        End If
                        If Not Me.cbNPCAktivated.Checked Then
                            num = 0
                        End If
                        Dim bytes As Byte() = BitConverter.GetBytes(num)
                        SentaiFile.WriteBytesInFile((path), (num2 + 4), 4, bytes)
                        Dim text As String = Me.tbNPCModelFile.Text
                        If ([text].Length < &H40) Then
                            Do While ([text].Length <> &H40)
                                [text] = ([text] & ChrW(0))
                            Loop
                        End If
                        bytes = SUmwandlung.TextStringToByteArray(([text]), &H4E4)
                        SentaiFile.WriteBytesInFile((path), (num2 + 40), &H40, bytes)
                        [text] = Me.tbNPCSetupfile.Text
                        If ([text].Length < &H40) Then
                            Do While ([text].Length <> &H40)
                                [text] = ([text] & ChrW(0))
                            Loop
                        End If
                        bytes = SUmwandlung.TextStringToByteArray(([text]), &H4E4)
                        SentaiFile.WriteBytesInFile((path), (num2 + &H68), &H40, bytes)
                        bytes = BitConverter.GetBytes(Conversions.ToInteger(Me.tbNPCID.Text))
                        SentaiFile.WriteBytesInFile((path), (num2 + &H1D8), 3, bytes)
                        bytes = BitConverter.GetBytes(Convert.ToInt32(Me.tbNPCx.Text))
                        bytes(3) = 0
                        SentaiFile.WriteBytesInFile((path), (num2 + &H1DD), 4, bytes)
                        bytes = BitConverter.GetBytes(Convert.ToInt32(Me.tbNPCy.Text))
                        bytes(3) = 0
                        SentaiFile.WriteBytesInFile((path), (num2 + &H1E1), 4, bytes)
                        bytes = BitConverter.GetBytes(Convert.ToInt32(Me.tbNPCz.Text))
                        bytes(3) = 0
                        SentaiFile.WriteBytesInFile((path), (num2 + &H1E5), 4, bytes)
                        bytes = BitConverter.GetBytes(Convert.ToInt32(Me.tbNPCangle.Text))
                        bytes(3) = 0
                        SentaiFile.WriteBytesInFile((path), (num2 + &H1EC), 4, bytes)
                        [text] = (Konstanten.sPath & "GameServer\NPC\" & Funktionen.GetNPCZhoonFile(((Konstanten.sPath & Me.tbNPCSetupfile.Text))))
                        If Not File.Exists([text]) Then
                            If Not Funktionen.YesNo("Warning!", "No Zhoon file found!" & ChrW(13) & ChrW(10) & "Create one for this NPC?", 1) Then
                                Return
                            End If
                            Dim writer As New StreamWriter((Konstanten.sPath & "GameServer\NPC\name\" & Path.GetFileNameWithoutExtension(Me.tbNPCSetupfile.Text) & ".zhoon"), False, Konstanten.enc)
                            writer.WriteLine(("//" & Path.GetFileName(Me.tbNPCSetupfile.Text)))
                            writer.WriteLine("*J_NAME")
                            writer.Close
                            [text] = (Konstanten.sPath & "GameServer\NPC\name\" & Path.GetFileNameWithoutExtension(Me.tbNPCSetupfile.Text) & ".zhoon")
                        End If
                        Try 
                            Dim writer2 As New StreamWriter([text], False, Konstanten.enc)
                            writer2.WriteLine(("//" & Path.GetFileName(Me.tbNPCSetupfile.Text) & ChrW(13) & ChrW(10)))
                            writer2.WriteLine((ChrW(13) & ChrW(10) & "*J_Name" & ChrW(9) & """" & Me.tbNPCName.Text & """" & ChrW(13) & ChrW(10) & ChrW(13) & ChrW(10)))
                            Dim str3 As String
                            For Each str3 In Me.tbNPCJ_Chat.Lines
                                If (str3 <> "") Then
                                    writer2.WriteLine(("*J_Chat" & ChrW(9) & str3 & ChrW(13) & ChrW(10)))
                                End If
                            Next
                            writer2.Flush
                            writer2.Close
                        Catch exception1 As Exception
                            ProjectData.SetProjectError(exception1)
                            Dim exception As Exception = exception1
                            Interaction.MsgBox(("Error: " & exception.Message), MsgBoxStyle.OkOnly, Nothing)
                            ProjectData.ClearProjectError
                        End Try
                        Dim index As Integer = Me.lbNPCList.SelectedIndex
                        Me.reloadThisSPC(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem))
                        Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
                        Me.lbNPCList.SetSelected(index, True)
                    End If
                End If
            End If
        End Sub

        Private Sub CMDNPCShopSave_Click(ByVal sender As Object, ByVal e As EventArgs)
            If Not File.Exists((Konstanten.sPath & Me.tbNPCSetupfile.Text)) Then
                Interaction.MsgBox(("File dont exist: " & Konstanten.sPath & Me.tbNPCSetupfile.Text), MsgBoxStyle.OkOnly, Nothing)
            Else
                Dim num2 As Integer
                Dim enumerator As IEnumerator
                Dim selectedIndex As Integer = Me.lbNPCList.SelectedIndex
                Dim strArray2 As String() = New String() { "*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(177) & ChrW(184) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197), "*" & ChrW(185) & ChrW(171) & ChrW(177) & ChrW(226) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197), "*" & ChrW(192) & ChrW(226) & ChrW(200) & ChrW(173) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197) }
                Dim strArray As String() = New String(&H3E9  - 1) {}
                Dim reader As New StreamReader((Konstanten.sPath & Me.tbNPCSetupfile.Text), Konstanten.enc)
                Do While (reader.Peek <> -1)
                    strArray(num2) = reader.ReadLine
                    num2 += 1
                Loop
                strArray(num2) = "<End>"
                reader.Close
                Dim str As String = ""
                Try 
                    enumerator = Me.LWNPCshop.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                        If (current.Text = "Empty") Then
                            str = ChrW(190) & ChrW(248) & ChrW(192) & ChrW(189)
                        ElseIf (current.Text <> "") Then
                            str = (str & current.Text.Replace("""", "") & " ")
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                num2 = 0
                Do While (strArray(num2) <> "<End>")
                    If strArray(num2).StartsWith(strArray2(Me.CBShopItem.SelectedIndex)) Then
                        strArray(num2) = (strArray2(Me.CBShopItem.SelectedIndex) & ChrW(9) & str)
                    End If
                    If strArray(num2).StartsWith("*" & ChrW(184) & ChrW(240) & ChrW(190) & ChrW(231) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                        strArray(num2) = ("*" & ChrW(184) & ChrW(240) & ChrW(190) & ChrW(231) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207) & ChrW(9) & """" & Me.tbNPCSetupfileInI.Text & """")
                    End If
                    num2 += 1
                Loop
                num2 = 0
                Dim writer As New StreamWriter((Konstanten.sPath & Me.tbNPCSetupfile.Text), False, Konstanten.enc)
                Do While (strArray(num2) <> "<End>")
                    writer.WriteLine(strArray(num2))
                    num2 += 1
                Loop
                writer.Close
                Me.ReloadNPC
                Me.lbNPCList.SetSelected(selectedIndex, True)
            End If
        End Sub

        Private Sub cmdPath_Click_1(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Try 
                If (Me.dlgFolder.ShowDialog = DialogResult.Cancel) Then
                    Return
                End If
                Konstanten.sPath = (Me.dlgFolder.SelectedPath & "\")
                MySettingsProperty.Settings.sspath = Konstanten.sPath
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "cmdPath" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Konstanten.AktuellPath = "GameServer\Monster\"
            Me.AlleDatenLaden
            Me.lbFiles.Items.Clear
            Me.lbItemFiles.Items.Clear
            Try 
                enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub cmdReload1_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Me.lbFiles.Items.Clear
            Me.lbItemFiles.Items.Clear
            Me.MoFound.Text = "0"
            Me.ItemFound.Text = "0"
            Me.Mapsfound.Text = "0"
            Me.AlleDatenLaden
            Me.MakeItemFileList
            Me.MakeMapFileList
            Me.ListView3.Items.Clear
            Try 
                enumerator = Me.MakeFileList(Me.cbMonsterSelector1.Text).GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Dim monsterIndex As Integer = CInt(Funktionen.GetMonsterIndex(Conversions.ToString(objectValue)))
                    Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Me.ListView3.Items.Add(Konstanten.MonsterFiles(monsterIndex)).SubItems.Add(Konstanten.MonsterName(monsterIndex))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub cmdSave_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.MonsterSpeichern(Funktionen.GetMonsterIndex(Conversions.ToString(Me.lbFiles.SelectedItem)))
        End Sub

        Private Sub cmdSaveConfig_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.SaveConfigFile
        End Sub

        Private Sub cmdShowLog_Click(ByVal sender As Object, ByVal e As EventArgs)
            Programmstarts.Execute(Konstanten.EditorExe, (MyProject.Application.Info.DirectoryPath & "\PriTaTor_Errors.log"))
        End Sub

        Private Sub cmFileListItems_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            If (Me.lbFileListItems.SelectedItems.Count <> 0) Then
                Me.LoadBackupToolStripMenuItem.DropDownItems.Clear
                Me.DeleteBackupToolStripMenuItem1.DropDownItems.Clear
                Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemBackupPath & "\*.txt"), FileAttribute.Normal)
                Do While (Konstanten.sFile <> "")
                    If (((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) AndAlso LikeOperator.LikeString(Konstanten.sFile, ("*" & Me.lbFileListItems.SelectedItem.ToString), CompareMethod.Binary)) Then
                        Me.LoadBackupToolStripMenuItem.DropDownItems.Add(Konstanten.sFile)
                        If Not Konstanten.sFile.ToUpper.Contains("DEFAULT") Then
                            Me.DeleteBackupToolStripMenuItem1.DropDownItems.Add(Konstanten.sFile)
                        End If
                    End If
                    Konstanten.sFile = FileSystem.Dir
                Loop
            End If
        End Sub

        Private Sub CMFilterSaver_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            Dim enumerator As IEnumerator
            Try 
                enumerator = Me.cbItemSelector.Items.GetEnumerator
                Do While enumerator.MoveNext
                    If Operators.ConditionalCompareObjectEqual(RuntimeHelpers.GetObjectValue(enumerator.Current), Me.cbItemSelector.Text, False) Then
                        Me.RemoveFromListToolStripMenuItem.Enabled = True
                        Me.AddToListToolStripMenuItem.Enabled = False
                        Return
                    End If
                    Me.RemoveFromListToolStripMenuItem.Enabled = False
                    Me.AddToListToolStripMenuItem.Enabled = True
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub cmItemsMonster_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            If (Me.lbItemMo.SelectedItems.Count = 0) Then
                Me.RemoveItemToolStripMenuItem.Enabled = False
                Me.EditMonsterToolStripMenuItem.Enabled = False
            Else
                Me.RemoveItemToolStripMenuItem.Enabled = True
                Me.EditMonsterToolStripMenuItem.Enabled = True
            End If
        End Sub

        Private Sub cmMapsFiles_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            If (Me.lbFilesMaps.SelectedItems.Count = 0) Then
                Me.ChangeEXPOfMapToolStripMenuItem.Enabled = False
            Else
                Me.ChangeEXPOfMapToolStripMenuItem.Enabled = True
            End If
        End Sub

        Private Sub cmMonsterItem_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            If (Me.lbItemFiles.SelectedItems.Count = 0) Then
                Me.GoToItemEditorToolStripMenuItem.Enabled = False
            Else
                Me.GoToItemEditorToolStripMenuItem.Enabled = True
            End If
        End Sub

        Private Sub cnMonsterFiles_Opening(ByVal sender As Object, ByVal e As CancelEventArgs)
            Me.BackupsToolStripMenuItem.DropDownItems.Clear
            Me.DeleteBackupToolStripMenuItem.DropDownItems.Clear
            If (Me.lbFiles.SelectedItems.Count <> 0) Then
                If (Me.lbFiles.SelectedItems.Count = 1) Then
                    Me.BackupsToolStripMenuItem.Text = "Load Backup"
                    Me.DeleteBackupToolStripMenuItem.Text = "Delete Backup"
                Else
                    Me.BackupsToolStripMenuItem.Text = "Load Default"
                    Me.DeleteBackupToolStripMenuItem.Text = "Delete all Backups"
                End If
                If (Me.lbFiles.SelectedItems.Count < 2) Then
                    Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MoBackupPath & "\*.inf"), FileAttribute.Normal)
                    Do While (Konstanten.sFile <> "")
                        If (((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) AndAlso LikeOperator.LikeString(Konstanten.sFile, ("*" & Me.lbFiles.SelectedItem.ToString), CompareMethod.Binary)) Then
                            Dim info As New FileInfo(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", Konstanten.sFile }))
                            Me.BackupsToolStripMenuItem.DropDownItems.Add(Konstanten.sFile)
                            If Not Konstanten.sFile.ToUpper.Contains("DEFAULT") Then
                                Me.DeleteBackupToolStripMenuItem.DropDownItems.Add(Konstanten.sFile)
                            End If
                        End If
                        Konstanten.sFile = FileSystem.Dir
                    Loop
                End If
            End If
        End Sub

        Private Sub DeleteBackupToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If ((Me.lbFiles.SelectedItems.Count >= 2) AndAlso Funktionen.YesNo("Delete Backups", "Do you want to delete all Backupfiles in each selected monster?", 1)) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.lbFiles.SelectedItems.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MoBackupPath & "\*.inf"), FileAttribute.Normal)
                        Do While (Konstanten.sFile <> "")
                            If (((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) AndAlso (Konstanten.sFile.Contains(Konstanten.MoBackupNameAdd) And Konstanten.sFile.Contains(Conversions.ToString(objectValue)))) Then
                                File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", Konstanten.sFile }))
                            End If
                            Konstanten.sFile = FileSystem.Dir
                        Loop
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub DeleteBackupToolStripMenuItem_DropDownItemClicked(ByVal sender As Object, ByVal e As ToolStripItemClickedEventArgs)
            File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", e.ClickedItem.Text.ToString }))
            Me.BackupsToolStripMenuItem.DropDownItems.Clear
            Me.DeleteBackupToolStripMenuItem.DropDownItems.Clear
        End Sub

        Private Sub DeleteBackupToolStripMenuItem1_DropDownItemClicked(ByVal sender As Object, ByVal e As ToolStripItemClickedEventArgs)
            File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", e.ClickedItem.Text.ToString }))
            Me.LoadBackupToolStripMenuItem.DropDownItems.Clear
            Me.DeleteBackupToolStripMenuItem1.DropDownItems.Clear
        End Sub

        Private Sub DeleteLineToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFiles.SelectedItems.Count = 0) Then
                Interaction.MsgBox("please select an monster", MsgBoxStyle.OkOnly, Nothing)
            Else
                Me.tbDroprate.Clear
                Me.tbDrops.Clear
                Me.lwItems.SelectedItems.Item(0).Remove
            End If
        End Sub

        Private Sub DeleteNPCToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim num As Integer
            Dim num2 As Integer
            Dim enumerator As IEnumerator
            Dim buffer2 As Byte() = New Byte(&H1F8  - 1) {}
            Dim str As String = Interaction.InputBox("NPC name", "Enter a name", "", -1, -1)
            Try 
                enumerator = Me.lbNPCList.Items.GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    If Operators.ConditionalCompareObjectEqual(objectValue, "Empty", False) Then
                        num2 = Me.lbNPCList.Items.IndexOf(RuntimeHelpers.GetObjectValue(objectValue))
                        goto Label_008F
                    End If
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        Label_008F:
            num = num2
            Dim strArray As String() = Strings.Split(Konstanten.DefaultNPCSPC, " ", -1, CompareMethod.Binary)
            Dim inhalt As Byte() = New Byte(&H1F8  - 1) {}
            Dim index As Integer = 0
            Do
                inhalt(index) = Convert.ToByte(Conversions.ToInteger(("&H" & strArray(index).ToString)))
                index += 1
            Loop While (index <= &H1F7)
            If (File.Exists((Konstanten.sPath & Konstanten.NPCPath & str & ".NPC")) AndAlso Not Funktionen.YesNo("Save warning!", "File exist already! Overwrite?", 2)) Then
                str = Interaction.InputBox("NPC name", "Enter a name", "", -1, -1)
                If (str = "") Then
                    Interaction.MsgBox("Canceled", MsgBoxStyle.OkOnly, Nothing)
                    Return
                End If
            End If
            Dim str3 As String = ("GameServer\npc\" & str & ".NPC")
            If (str3.Length < &H40) Then
                Do While (str3.Length <> &H40)
                    str3 = (str3 & ChrW(0))
                Loop
            End If
            Dim buffer3 As Byte() = New Byte(&H40  - 1) {}
            buffer3 = SUmwandlung.TextStringToByteArray((str3), &H4E4)
            Dim num5 As Integer = &H68
            Do
                inhalt(num5) = buffer3((num5 - &H68))
                num5 += 1
            Loop While (num5 <= &HA7)
            Dim fileName As String = SentaiFile.GetFileName((Konstanten.sPath & Konstanten.NPCPath))
            If (fileName = Nothing) Then
                Interaction.MsgBox("Canceled", MsgBoxStyle.OkOnly, Nothing)
            Else
                Dim num3 As Integer
                File.Copy(fileName, (Konstanten.sPath & Konstanten.NPCPath & str & ".NPC"))
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), (num * &H1F8), &H1F8, inhalt)
                Interaction.MsgBox((Konstanten.sPath & Konstanten.NPCPath & str & ".NPC"), MsgBoxStyle.OkOnly, Nothing)
                Dim reader As New StreamReader((Konstanten.sPath & Konstanten.NPCPath & str & ".NPC"), Konstanten.enc)
                Dim strArray2 As String() = New String(&H3E9  - 1) {}
                Do While (reader.Peek <> -1)
                    strArray2(num3) = reader.ReadLine
                    If strArray2(num3).StartsWith("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                        strArray2(num3) = ("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207) & ChrW(9) & """name\" & str & ".zhoon""")
                    End If
                    num3 += 1
                Loop
                reader.Close
                strArray2(num3) = "<End>"
                num3 = 0
                Dim writer As New StreamWriter((Konstanten.sPath & Konstanten.NPCPath & str & ".NPC"), False, Konstanten.enc)
                Do While (strArray2(num3) <> "<End>")
                    writer.WriteLine(strArray2(num3))
                    num3 += 1
                Loop
                writer.Close
                writer = New StreamWriter(String.Concat(New String() { Konstanten.sPath, Konstanten.NPCPath, "Name\", str, ".Zhoon" }), False, Konstanten.enc)
                writer.WriteLine(("*J_Name" & ChrW(9) & """" & str & """" & ChrW(13) & ChrW(10) & ChrW(13) & ChrW(10)))
                writer.WriteLine("*J_Chat" & ChrW(9) & """What im talking?!?""")
                writer.Close
                Me.reloadThisSPC(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem))
                Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
                Me.lbNPCList.SetSelected(num, True)
            End If
        End Sub

        Private Sub DeleteNPCToolStripMenuItem1_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (((Me.lbNPCList.SelectedItems.Count >= 1) AndAlso (Me.lbNPCMapFileList.SelectedItems.Count >= 1)) AndAlso Funktionen.YesNo("Delete", Conversions.ToString(Operators.ConcatenateObject(Operators.ConcatenateObject(Operators.ConcatenateObject("Delete NPC:""", Me.lbNPCList.SelectedItem), """"c), " ?")), 1)) Then
                Dim num3 As Integer
                Dim selectedIndex As Integer = Me.lbNPCList.SelectedIndex
                Dim inhalt As Byte() = New Byte(&H1F8  - 1) {}
                Do While (num3 <> &H1F7)
                    inhalt(num3) = 0
                    num3 += 1
                Loop
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), (&H1F8 * selectedIndex), &H1F8, inhalt)
                Dim index As Integer = Me.lbNPCList.SelectedIndex
                Me.reloadThisSPC(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem))
                Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
                Me.lbNPCList.SetSelected(index, True)
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

        Private Sub DownToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (((Me.lbNPCList.SelectedItems.Count >= 1) AndAlso (Me.lbNPCMapFileList.SelectedItems.Count >= 1)) AndAlso (Me.lbNPCList.SelectedIndex <> &H63)) Then
                Dim inhalt As Byte() = New Byte(&H1F8  - 1) {}
                Dim buffer2 As Byte() = New Byte(&H1F8  - 1) {}
                inhalt = SentaiFile.ReadBytesInFile(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem), CLng(((Me.lbNPCList.SelectedIndex + 1) * &H1F8)), &H1F8)
                buffer2 = SentaiFile.ReadBytesInFile(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem), CLng((Me.lbNPCList.SelectedIndex * &H1F8)), &H1F8)
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), (Me.lbNPCList.SelectedIndex * &H1F8), &H1F8, inhalt)
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), ((Me.lbNPCList.SelectedIndex + 1) * &H1F8), &H1F8, buffer2)
                Dim index As Integer = (Me.lbNPCList.SelectedIndex + 1)
                Me.reloadThisSPC(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem))
                Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
                Me.lbNPCList.SetSelected(index, True)
            End If
        End Sub

        Private Sub Drawpoint(ByVal xx As Integer, ByVal yy As Integer, ByVal Brush As Brush, ByVal Gx As Integer, ByVal gy As Integer, ByVal Optional sx As Double = 0, ByVal Optional sy As Double = 0)
            Dim a As Double = (128 + ((xx - Konstanten.Posx) / Konstanten.TX))
            Dim num7 As Double = (128 + ((Konstanten.Posy - yy) / Konstanten.TY))
            Dim graphics As Graphics = Graphics.FromImage(Me.PictureBox1.Image)
            Dim num6 As Integer = CInt(Math.Round(a))
            Dim num8 As Integer = CInt(Math.Round(num7))
            Dim num3 As Integer = CInt(Math.Round(sx))
            Dim num4 As Integer = CInt(Math.Round(sy))
            Dim num As Integer = CInt(Math.Round(a))
            Dim num2 As Integer = CInt(Math.Round(num7))
            graphics.DrawLine(Pens.Red, num, num2, (num + num3), (num2 + num4))
            graphics.FillEllipse(Brush, (num6 - 2), (num8 - 2), 4, 4)
            graphics.DrawEllipse(Pens.White, (num6 - 2), (num8 - 2), 4, 4)
        End Sub

        Private Sub DropCountToolStripMenuItem1_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim num As Long = Conversions.ToLong(Interaction.InputBox("Enter Dropcount", "", "", -1, -1))
            Try 
                Dim flag As Boolean
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.lbFiles.SelectedIndices.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Dim num3 As Long = 0
                        Do While (Konstanten.MonsterDatenListe(Conversions.ToInteger(objectValue), CInt(num3)) <> "End of File")
                            If ((Konstanten.MonsterDatenListe(Conversions.ToInteger(objectValue), CInt(num3)).Contains("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)) And Not Konstanten.MonsterDatenListe(Conversions.ToInteger(objectValue), CInt(num3)).Contains(ChrW(184) & ChrW(240) & ChrW(181) & ChrW(206))) AndAlso Konstanten.MonsterDatenListe(Conversions.ToInteger(objectValue), CInt(num3)).Substring((Strings.Len("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205)) - 1)).StartsWith(ChrW(205))) Then
                                Konstanten.MonsterDatenListe(Conversions.ToInteger(objectValue), CInt(num3)) = ("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205) & ChrW(9) & num.ToString)
                            End If
                            num3 = (num3 + 1)
                        Loop
                        num3 = 0
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                If Funktionen.YesNo("Save monsters", "Do you want to save all selected monsters?", 1) Then
                    Dim enumerator2 As IEnumerator
                    flag = True
                    Try 
                        enumerator2 = Me.lbFiles.SelectedItems.GetEnumerator
                        Do While enumerator2.MoveNext
                            Funktionen.MonsterSaver(Funktionen.GetMonsterIndex(Conversions.ToString(RuntimeHelpers.GetObjectValue(enumerator2.Current))), True)
                        Loop
                    Finally
                        If TypeOf enumerator2 Is IDisposable Then
                            TryCast(enumerator2,IDisposable).Dispose
                        End If
                    End Try
                    Interaction.MsgBox(("Dropcount changed to " & Conversions.ToString(num)), MsgBoxStyle.OkOnly, Nothing)
                Else
                    Interaction.MsgBox("No Monster Saved! Please press Reload!", MsgBoxStyle.OkOnly, Nothing)
                    flag = False
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub DropList()
            Try 
                If Not Konstanten.SP Then
                    Me.lwItems.Items.Clear
                    Me.lwItems.View = View.Details
                    Me.lwItems.FullRowSelect = True
                    Me.lwItems.Columns.Add("Rate", 80, HorizontalAlignment.Left)
                    Me.lwItems.Columns.Add("Items", 800, HorizontalAlignment.Left)
                    Konstanten.SP = True
                End If
                Me.lwItems.Items.Clear
                Konstanten.ItemComplete = ""
                Dim items As ListViewItemCollection = Me.lwItems.Items
                Dim num3 As Integer = (Konstanten.DropIndex - 1)
                Dim i As Integer = 0
                Do While (i <= num3)
                    Konstanten.ItemSplit = Strings.Split(Konstanten.DropDaten(i).Trim(New Char() { ChrW(9) }), " ", -1, CompareMethod.Binary)
                    Dim item As ListViewItem = items.Add(Konstanten.ItemSplit(0))
                    Dim num4 As Integer = (Konstanten.ItemSplit.Length - 1)
                    Dim j As Integer = 1
                    Do While (j <= num4)
                        If (Konstanten.ItemSplit(j) = ChrW(190) & ChrW(248) & ChrW(192) & ChrW(189)) Then
                            Konstanten.ItemSplit(j) = "Nothing"
                        End If
                        If (Konstanten.ItemSplit(j) = ChrW(181) & ChrW(183)) Then
                            Konstanten.ItemSplit(j) = "Gold"
                        End If
                        If (Konstanten.ItemSplit(j) <> "") Then
                            If (j = (Konstanten.ItemSplit.Length - 1)) Then
                                Konstanten.ItemComplete = Konstanten.ItemComplete.Insert(Strings.Len(Konstanten.ItemComplete), Konstanten.ItemSplit(j))
                            Else
                                Konstanten.ItemComplete = Konstanten.ItemComplete.Insert(Strings.Len(Konstanten.ItemComplete), (Konstanten.ItemSplit(j) & " "))
                            End If
                        End If
                        j += 1
                    Loop
                    item.SubItems.Add(Konstanten.ItemComplete)
                    Konstanten.ItemComplete = ""
                    item = Nothing
                    i += 1
                Loop
                items = Nothing
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = ("DropList" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub EditMonsterToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Me.cbMonsterSelector.Text = ("Name=" & Konstanten.MonsterName(CInt(Funktionen.GetMonsterIndex(Me.lbItemMo.SelectedItem.ToString))).Trim(New Char() { """"c }))
            Me.TabControl1.SelectTab(0)
            Try 
                enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
            Me.lbFiles.SelectedItem = RuntimeHelpers.GetObjectValue(Me.lbItemMo.SelectedItem)
            Me.MonsterAuswertung
        End Sub

        Private Sub EditRateToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView1.SelectedItems.Count >= 1) Then
                Dim item As ListViewItem = Me.ListView1.SelectedItems.Item(0)
                Dim text As String = item.SubItems.Item(4).Text
                item.SubItems.Item(4).Text = Interaction.InputBox("Enter guard count", "", item.SubItems.Item(4).Text, -1, -1)
                If Not Versioned.IsNumeric(item.SubItems.Item(4).Text) Then
                    item.SubItems.Item(4).Text = [text]
                End If
                item = Nothing
            End If
        End Sub

        Private Sub EditSpawnRateToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView2.SelectedItems.Count >= 1) Then
                Dim item As ListViewItem = Me.ListView2.SelectedItems.Item(0)
                Dim text As String = item.SubItems.Item(2).Text
                item.SubItems.Item(2).Text = Interaction.InputBox("Enter spawn rate", "", item.SubItems.Item(2).Text, -1, -1)
                If Not Versioned.IsNumeric(item.SubItems.Item(2).Text) Then
                    item.SubItems.Item(2).Text = [text]
                End If
                item = Nothing
            End If
        End Sub

        Private Sub EditSpawnTimesToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView1.SelectedItems.Count >= 1) Then
                Dim item As ListViewItem = Me.ListView1.SelectedItems.Item(0)
                Dim text As String = item.SubItems.Item(5).Text
                item.SubItems.Item(5).Text = Interaction.InputBox("Enter spawn times", "", item.SubItems.Item(5).Text, -1, -1)
                If (item.SubItems.Item(5).Text = "") Then
                    item.SubItems.Item(5).Text = [text]
                End If
                item = Nothing
            End If
        End Sub

        Private Sub ExperienceToolStripMenuItem1_Click(ByVal sender As Object, ByVal e As EventArgs)
            Konstanten.ExpSender = Me.lbFiles.SelectedItems
            MyProject.Forms.Form2.ShowDialog
        End Sub

        Public Sub FillNPCShop()
            Dim enumerator As IEnumerator
            Me.LWNPCshop.Items.Clear
            Dim strArray As String() = New String() { "*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(177) & ChrW(184) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197), "*" & ChrW(185) & ChrW(171) & ChrW(177) & ChrW(226) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197), "*" & ChrW(192) & ChrW(226) & ChrW(200) & ChrW(173) & ChrW(198) & ChrW(199) & ChrW(184) & ChrW(197) }
            Dim index As Integer = 0
            Try 
                enumerator = Funktionen.GetNPCShopItems((Konstanten.sPath & Me.tbNPCSetupfile.Text), strArray(Me.CBShopItem.SelectedIndex)).GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    If Conversions.ToBoolean(Operators.NotObject(Operators.CompareObjectEqual(objectValue, ChrW(190) & ChrW(248) & ChrW(192) & ChrW(189), False))) Then
                        index = Array.IndexOf(Of String)(Konstanten.ItemCodes, ("""" & objectValue.ToString.ToUpper & """"))
                        If (index = -1) Then
                            Me.LWNPCshop.Items.Add("no code").SubItems.Add("item dont exist")
                        Else
                            Me.LWNPCshop.Items.Add(Konstanten.ItemCodes(index)).SubItems.Add(Konstanten.ItemName(index))
                        End If
                    Else
                        Me.LWNPCshop.Items.Add("Empty")
                    End If
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub GefundenMaps()
            Dim flag As Boolean = False
            If (Me.lbFiles.SelectedItems.Count <> 0) Then
                Dim num2 As Integer = 0
                Dim index As Integer = 0
                Me.lbMaps.Items.Clear
                Try 
                    Do While (Konstanten.MapFiles(index) <> "")
                        num2 = 0
                        Do While (Konstanten.MapDatenListe(index, num2) <> "End of File")
                            If Not Me.chNotFound.Checked Then
                                If (Konstanten.MapDatenListe(index, num2).StartsWith("*") AndAlso Konstanten.MapDatenListe(index, num2).Contains(Me.tbMoMapName.Text)) Then
                                    Me.lbMaps.Items.Add(Konstanten.MapFiles(index))
                                End If
                            ElseIf ((Konstanten.MapDatenListe(index, num2).StartsWith("*") AndAlso Not flag) AndAlso Not Konstanten.MapDatenListe(index, num2).Contains(Me.tbMoMapName.Text)) Then
                                Me.lbMaps.Items.Add(Konstanten.MapFiles(index))
                                flag = True
                            End If
                            num2 += 1
                        Loop
                        index += 1
                        flag = False
                    Loop
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                    Konstanten.ErrorText = ("GefundenMaps" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                    Funktionen.WriteErrorLog((Konstanten.ErrorText))
                    ProjectData.ClearProjectError
                End Try
            End If
        End Sub

        Private Sub Getitems()
            Dim a As Double = 0
            Dim flag2 As Boolean = True
            Dim flag As Boolean = False
            Dim num3 As Integer = 0
            Dim index As Integer = 0
            Try 
                Me.lbItemFiles.Items.Clear
                Me.lbItemsRealName.Items.Clear
                If (Not Me.tbDrops.Text.StartsWith("Gold") AndAlso Not Me.tbDrops.Text.StartsWith("Nothing")) Then
                    Konstanten.ItemsFound = Strings.Split(Me.tbDrops.Text.ToString, " ", -1, CompareMethod.Binary)
                    Dim num5 As Integer = (Konstanten.ItemsFound.Length - 1)
                    Dim i As Integer = 0
                    Do While (i <= num5)
                        index = 0
                        If ((Konstanten.ItemsFound(i).Trim.ToLower <> "") Or (Konstanten.ItemsFound(i) <> " ")) Then
                            Do While (Konstanten.ItemFiles(index) <> "")
                                num3 = 0
                                Do While (Konstanten.ItemDatenListe(index, num3) <> "End of File")
                                    If Konstanten.ItemDatenListe(index, num3).StartsWith("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)) Then
                                        If Konstanten.ItemDatenListe(index, num3).Remove(0, "*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229).Length).Trim(New Char() { ChrW(9) }).Trim(New Char() { " "c }).ToLower.StartsWith(("""" & Konstanten.ItemsFound(i).Trim.ToLower & """")) Then
                                            Me.lbItemFiles.Items.Add(Konstanten.ItemFiles(index))
                                            Me.lbItemsRealName.Items.Add(Konstanten.ItemName(index))
                                            flag = True
                                            Exit Do
                                        End If
                                        flag = False
                                    End If
                                    num3 += 1
                                Loop
                                index += 1
                                If flag Then
                                    flag2 = False
                                    Exit Do
                                End If
                                flag2 = True
                            Loop
                        End If
                        a = (a + (100 / CDbl(Konstanten.ItemsFound.Length)))
                        If (a >= 100) Then
                            a = 100
                        End If
                        Me.pbWorking.Value = CInt(Math.Round(a))
                        If (flag2 And Not flag) Then
                            Me.lbItemFiles.Items.Add(("Item: " & Konstanten.ItemsFound(i) & " not found"))
                            Me.lbItemsRealName.Items.Add(("Item: " & Konstanten.ItemsFound(i) & " not found"))
                            flag2 = True
                            flag = False
                        End If
                        i += 1
                    Loop
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetItems" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Function GetNPCChat(ByVal NPCSetupFile As String) As ArrayList
            Dim list2 As ArrayList
            Dim list As New ArrayList
            Dim flag As Boolean = True
            Dim str As String = ("Cant find " & Path.GetFileName(NPCSetupFile))
            Try 
                Dim reader As New StreamReader(NPCSetupFile, Encoding.GetEncoding(&H4E4))
                Dim str3 As String = ""
                Do While Not (str3.Contains(Konstanten.npcName) Or (reader.Peek = -1))
                    str3 = reader.ReadLine
                Loop
                If ((reader.Peek = -1) And Not str3.Contains(Konstanten.npcName)) Then
                    list.Add("No name found")
                    reader.Close
                    Return list
                End If
                reader.Close
                str = "Cant find .zhoon file"
                reader = New StreamReader((Path.GetDirectoryName(NPCSetupFile) & "\" & str3.Replace(Konstanten.npcName, "").Replace("""", "").Trim), Encoding.GetEncoding(&H4E4))
                str3 = ""
                Do While (reader.Peek <> -1)
                    str3 = reader.ReadLine
                    If str3.ToUpper.StartsWith("*J_CHAT") Then
                        list.Add(str3.Remove(0, "*j_char".Length).Replace(ChrW(9), "").Trim)
                        flag = False
                    End If
                Loop
                If (((reader.Peek = -1) And Not str3.ToUpper.Contains("*J_NAME")) And flag) Then
                    list.Clear
                    list.Add("No chat found")
                    reader.Close
                    Return list
                End If
                reader.Close
                list2 = list
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                list.Add(str)
                list2 = list
                ProjectData.ClearProjectError
            End Try
            Return list2
        End Function

        Private Function GetNPCiniPath(ByVal MapSpcFile As String, ByVal NumberOfNPC As Integer) As String
            Dim str As String
            Dim str3 As String = "Cant find NPC ini File"
            Dim str2 As String = ""
            Dim num As Integer = (&H1F8 * NumberOfNPC)
            Try 
                str3 = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(MapSpcFile, CLng((num + 40)), &H40)), &H4E4)
                If str3.Contains(ChrW(0)) Then
                    Dim num2 As Integer
                    Do While (str3.Chars(num2) <> ChrW(0))
                        str2 = (str2 & Conversions.ToString(str3.Chars(num2)))
                        num2 += 1
                    Loop
                Else
                    str2 = str3
                End If
                str = str2
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                str = "Cant find NPC ini File"
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Function GetNPCMapIncex(ByVal Filename As String) As Integer
            Dim index As Integer = 0
            Do While Not ((Filename = Konstanten.SPCFiles(index)) Or (Konstanten.SPCFiles(index) = Nothing))
                index += 1
            Loop
            Return index
        End Function

        Private Function GetNPCName(ByVal File As String) As String
            Dim str2 As String
            Dim str As String = ("Cant find " & Path.GetFileName(File))
            Try 
                Dim reader As New StreamReader(File, Encoding.GetEncoding(&H4E4))
                Dim str4 As String = ""
                Do While Not (str4.Contains(Konstanten.npcName) Or (reader.Peek = -1))
                    str4 = reader.ReadLine
                Loop
                If ((reader.Peek = -1) And Not str4.Contains(Konstanten.npcName)) Then
                    Return "No name found"
                End If
                reader.Close
                str = "Cant find .zhoon file"
                reader = New StreamReader((Path.GetDirectoryName(File) & "\" & str4.Replace(Konstanten.npcName, "").Replace("""", "").Trim), Encoding.GetEncoding(&H4E4))
                str4 = ""
                Do While Not (str4.ToUpper.Contains("*J_NAME") Or (reader.Peek = -1))
                    str4 = reader.ReadLine
                Loop
                If ((reader.Peek = -1) And Not str4.ToUpper.Contains("*J_NAME")) Then
                    Return "No name found"
                End If
                reader.Close
                str2 = str4.Remove(0, "*j_name".Length).Replace("""", "").Trim
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                str2 = str
                ProjectData.ClearProjectError
            End Try
            Return str2
        End Function

        Private Function GetNPCSetupFile(ByVal MapSpcFile As String, ByVal NumberOfNPC As Integer) As String
            Dim str As String
            Dim str3 As String = "Cant find NPC setup File"
            Dim str2 As String = ""
            Dim num As Integer = (&H1F8 * NumberOfNPC)
            Try 
                str3 = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(MapSpcFile, CLng((num + &H68)), &H40)), &H4E4)
                If str3.Contains(ChrW(0)) Then
                    Dim num2 As Integer
                    Do While (str3.Chars(num2) <> ChrW(0))
                        str2 = (str2 & Conversions.ToString(str3.Chars(num2)))
                        num2 += 1
                    Loop
                Else
                    str2 = str3
                End If
                str = str2
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                str = "Cant find NPC setup File"
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Private Sub GoldToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            MyProject.Forms.Form3.ShowDialog
        End Sub

        Private Sub GoToItemEditorToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.cbItemSelector.Text = Funktionen.GetItemCode(Funktionen.GetItemIndex(Me.lbItemFiles.SelectedItem.ToString)).Trim(New Char() { """"c })
            Me.TabControl1.SelectTab(1)
            Me.MakeItemFileList
            Me.lbFileListItems.SelectedItem = RuntimeHelpers.GetObjectValue(Me.lbItemFiles.SelectedItem)
            Me.ItemAuswertung(Funktionen.GetItemIndex(Me.lbItemFiles.SelectedItem.ToString))
        End Sub

        <DebuggerStepThrough> _
        Private Sub InitializeComponent()
            Me.components = New Container
            Me.cmdSave = New Button
            Me.cmdReload = New Button
            Me.lbFiles = New ListBox
            Me.cnMonsterFiles = New ContextMenuStrip(Me.components)
            Me.SaveMonstersToolStripMenuItem = New ToolStripMenuItem
            Me.ItemToolStripMenuItem = New ToolStripMenuItem
            Me.ChangeToolStripMenuItem = New ToolStripMenuItem
            Me.DropCountToolStripMenuItem1 = New ToolStripMenuItem
            Me.ExperienceToolStripMenuItem1 = New ToolStripMenuItem
            Me.GoldToolStripMenuItem = New ToolStripMenuItem
            Me.BackupsToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteBackupToolStripMenuItem = New ToolStripMenuItem
            Me.lbFound = New Label
            Me.GroupBox1 = New GroupBox
            Me.Label28 = New Label
            Me.tbMoExp = New TextBox
            Me.Label27 = New Label
            Me.tbMoSnd = New TextBox
            Me.Label26 = New Label
            Me.cbMoTyp = New ComboBox
            Me.Label16 = New Label
            Me.tbMoMTyp = New TextBox
            Me.Label9 = New Label
            Me.tbMoMSpd = New TextBox
            Me.Label8 = New Label
            Me.tbMoHp = New TextBox
            Me.Label7 = New Label
            Me.tbMoVision = New TextBox
            Me.Label6 = New Label
            Me.tbMoChar = New TextBox
            Me.Label5 = New Label
            Me.tbMoInt = New TextBox
            Me.Label4 = New Label
            Me.tbMoApp = New TextBox
            Me.Label3 = New Label
            Me.tbMoSpCode = New TextBox
            Me.Label2 = New Label
            Me.tbMoLevel = New TextBox
            Me.Label1 = New Label
            Me.tbMoName = New TextBox
            Me.GroupBox2 = New GroupBox
            Me.Label15 = New Label
            Me.tbMoPAtkRtg = New TextBox
            Me.Label14 = New Label
            Me.tbMoAtkSpd = New TextBox
            Me.Label13 = New Label
            Me.tbMoAtkRtg = New TextBox
            Me.Label12 = New Label
            Me.tbMoAtkCrit = New TextBox
            Me.Label11 = New Label
            Me.tbMoSKAtk = New TextBox
            Me.Label10 = New Label
            Me.tbMoAtkPow = New TextBox
            Me.Label17 = New Label
            Me.tbMoAbs = New TextBox
            Me.GroupBox3 = New GroupBox
            Me.Label25 = New Label
            Me.tbMoMage = New TextBox
            Me.Label24 = New Label
            Me.tbMoPoision = New TextBox
            Me.Label23 = New Label
            Me.tbMoFire = New TextBox
            Me.Label22 = New Label
            Me.tbMoIce = New TextBox
            Me.Label21 = New Label
            Me.tbMoLtg = New TextBox
            Me.Label20 = New Label
            Me.tbMoOrg = New TextBox
            Me.Label19 = New Label
            Me.tbMoBlk = New TextBox
            Me.Label18 = New Label
            Me.tbMoDef = New TextBox
            Me.tbMoNoDrop = New TextBox
            Me.Label37 = New Label
            Me.tbMoMapName = New TextBox
            Me.lwItems = New ListView
            Me.cmsDrops = New ContextMenuStrip(Me.components)
            Me.AddDroplineToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteLineToolStripMenuItem = New ToolStripMenuItem
            Me.Label29 = New Label
            Me.tbDroprate = New TextBox
            Me.Label30 = New Label
            Me.tbDrops = New TextBox
            Me.lbMaps = New ListBox
            Me.chNotFound = New CheckBox
            Me.GroupBox4 = New GroupBox
            Me.cbSelectAll = New CheckBox
            Me.chMapEn = New CheckBox
            Me.TabControl1 = New TabControl
            Me.TabPage1 = New TabPage
            Me.cmdMoRealName = New Button
            Me.cbMonsterSelector = New ComboBox
            Me.cbMoBoss = New CheckBox
            Me.Label80 = New Label
            Me.tbMoSize = New TextBox
            Me.GroupBox5 = New GroupBox
            Me.lblMoListName = New Label
            Me.chItemInfo = New CheckBox
            Me.lbItemFiles = New ListBox
            Me.cmMonsterItem = New ContextMenuStrip(Me.components)
            Me.GoToItemEditorToolStripMenuItem = New ToolStripMenuItem
            Me.lbItemsRealName = New ListBox
            Me.Label35 = New Label
            Me.Label34 = New Label
            Me.TabPage2 = New TabPage
            Me.cmdItemRealName = New Button
            Me.cmdItemSave = New Button
            Me.GroupBox20 = New GroupBox
            Me.cbItemMo = New CheckBox
            Me.lbItemMo = New ListBox
            Me.cmItemsMonster = New ContextMenuStrip(Me.components)
            Me.RemoveItemToolStripMenuItem = New ToolStripMenuItem
            Me.EditMonsterToolStripMenuItem = New ToolStripMenuItem
            Me.cbItemSelector = New ComboBox
            Me.CMFilterSaver = New ContextMenuStrip(Me.components)
            Me.SaveToolStripMenuItem = New ToolStripMenuItem
            Me.LoadFilterToolStripMenuItem = New ToolStripMenuItem
            Me.AddToListToolStripMenuItem = New ToolStripMenuItem
            Me.RemoveFromListToolStripMenuItem = New ToolStripMenuItem
            Me.cmdReload1 = New Button
            Me.GroupBox19 = New GroupBox
            Me.Label86 = New Label
            Me.tbItmLevel = New TextBox
            Me.tbItmStr = New TextBox
            Me.Label85 = New Label
            Me.tbItmSpirit = New TextBox
            Me.Label84 = New Label
            Me.tbItmTalent = New TextBox
            Me.Label83 = New Label
            Me.tbItmAgi = New TextBox
            Me.Label82 = New Label
            Me.tbItmreqHP = New TextBox
            Me.Label81 = New Label
            Me.GroupBox18 = New GroupBox
            Me.Label93 = New Label
            Me.tbItmHPRegen = New TextBox
            Me.tbItmMPRegen = New TextBox
            Me.Label92 = New Label
            Me.tbItmSTMRegen = New TextBox
            Me.Label91 = New Label
            Me.tbItmHPAdd = New TextBox
            Me.Label90 = New Label
            Me.tbItmMPAdd = New TextBox
            Me.Label89 = New Label
            Me.tbItmSTMAdd = New TextBox
            Me.Label88 = New Label
            Me.tbItmAPT = New TextBox
            Me.Label87 = New Label
            Me.GroupBox17 = New GroupBox
            Me.Label94 = New Label
            Me.tbItmRun = New TextBox
            Me.GroupBox16 = New GroupBox
            Me.Label72 = New Label
            Me.tbItmSPatkSpd = New TextBox
            Me.tbItmSPCrt = New TextBox
            Me.Label71 = New Label
            Me.tbItmSPLvl = New TextBox
            Me.Label70 = New Label
            Me.tbItmSPRtg = New TextBox
            Me.Label69 = New Label
            Me.tbItmSPabs = New TextBox
            Me.Label68 = New Label
            Me.tbItmSPdef = New TextBox
            Me.Label67 = New Label
            Me.tbItmSPblk = New TextBox
            Me.Label74 = New Label
            Me.tbItmSPhp = New TextBox
            Me.Label76 = New Label
            Me.tbItmSPMp = New TextBox
            Me.Label75 = New Label
            Me.tbItmSPRun = New TextBox
            Me.Label77 = New Label
            Me.tbItmSPRange = New TextBox
            Me.Label78 = New Label
            Me.GroupBox15 = New GroupBox
            Me.Label63 = New Label
            Me.tbItmAbs = New TextBox
            Me.tbItmdef = New TextBox
            Me.Label66 = New Label
            Me.tbItmBlk = New TextBox
            Me.Label73 = New Label
            Me.tbItmInGameNAme = New TextBox
            Me.GroupBox14 = New GroupBox
            Me.Label60 = New Label
            Me.tbItmAtkPow = New TextBox
            Me.tbItmRange = New TextBox
            Me.Label61 = New Label
            Me.tbItmSpeed = New TextBox
            Me.Label62 = New Label
            Me.tbItmAtkRtg = New TextBox
            Me.Label65 = New Label
            Me.tbItmCrtRtg = New TextBox
            Me.Label64 = New Label
            Me.GroupBox13 = New GroupBox
            Me.Label56 = New Label
            Me.tbItmHPRec = New TextBox
            Me.tbItmManaRec = New TextBox
            Me.Label57 = New Label
            Me.tbItmStmRec = New TextBox
            Me.Label58 = New Label
            Me.tbItmPots = New TextBox
            Me.Label59 = New Label
            Me.Label46 = New Label
            Me.GroupBox12 = New GroupBox
            Me.Label50 = New Label
            Me.tbItmIntegrity = New TextBox
            Me.tbItmWeight = New TextBox
            Me.Label51 = New Label
            Me.tbItmPrice = New TextBox
            Me.Label32 = New Label
            Me.GroupBox11 = New GroupBox
            Me.Label52 = New Label
            Me.tbItmOrganic = New TextBox
            Me.tbItmFire = New TextBox
            Me.Label79 = New Label
            Me.Label53 = New Label
            Me.tbItmFrost = New TextBox
            Me.tbItmLighting = New TextBox
            Me.Label54 = New Label
            Me.tbItmPoision = New TextBox
            Me.Label55 = New Label
            Me.GroupBox10 = New GroupBox
            Me.chSecMech = New CheckBox
            Me.chSecMgs = New CheckBox
            Me.chSecFighter = New CheckBox
            Me.chSecPrs = New CheckBox
            Me.chSecPike = New CheckBox
            Me.chSecAta = New CheckBox
            Me.chSecArcher = New CheckBox
            Me.chSecKnight = New CheckBox
            Me.GroupBox9 = New GroupBox
            Me.chPriMech = New CheckBox
            Me.chPriMgs = New CheckBox
            Me.chPriFighter = New CheckBox
            Me.chPriPrs = New CheckBox
            Me.chPriPike = New CheckBox
            Me.chPriAta = New CheckBox
            Me.chPriArcher = New CheckBox
            Me.chPriKnight = New CheckBox
            Me.GroupBox8 = New GroupBox
            Me.Label44 = New Label
            Me.Label49 = New Label
            Me.tbItmJpName = New TextBox
            Me.tbItmGlow = New TextBox
            Me.tbItmName = New TextBox
            Me.Label48 = New Label
            Me.Label45 = New Label
            Me.tbItmQuest = New TextBox
            Me.Label47 = New Label
            Me.tbItmCode = New TextBox
            Me.GroupBox6 = New GroupBox
            Me.lbFileListItems = New ListBox
            Me.cmFileListItems = New ContextMenuStrip(Me.components)
            Me.LoadBackupToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteBackupToolStripMenuItem1 = New ToolStripMenuItem
            Me.ItemDistribToolStripMenuItem = New ToolStripMenuItem
            Me.SeachForItemNameToolStripMenuItem = New ToolStripMenuItem
            Me.SendToItemSearcherToolStripMenuItem = New ToolStripMenuItem
            Me.lbItemsListCount = New Label
            Me.TabPage3 = New TabPage
            Me.ListView1 = New ListView
            Me.lwBossFileName = New ColumnHeader
            Me.LWBossRealName = New ColumnHeader
            Me.lwBossAddMonster = New ColumnHeader
            Me.lwBossAddMonsterRealName = New ColumnHeader
            Me.LWAddSpawnCount = New ColumnHeader
            Me.LWBossSpawnTimes = New ColumnHeader
            Me.CMSMapBoss = New ContextMenuStrip(Me.components)
            Me.ShowToolStripMenuItem = New ToolStripMenuItem
            Me.RemoveAllToolStripMenuItem1 = New ToolStripMenuItem
            Me.EditRateToolStripMenuItem = New ToolStripMenuItem
            Me.EditSpawnTimesToolStripMenuItem = New ToolStripMenuItem
            Me.cmdMapSave = New Button
            Me.cmdMapReload = New Button
            Me.gb24 = New GroupBox
            Me.tbMapSpawnRate = New TextBox
            Me.Label33 = New Label
            Me.ListView3 = New ListView
            Me.ColumnHeader1 = New ColumnHeader
            Me.ColumnHeader2 = New ColumnHeader
            Me.CMSMapMonsterToAdd = New ContextMenuStrip(Me.components)
            Me.AddToMapToolStripMenuItem = New ToolStripMenuItem
            Me.AddToSelectedBossToolStripMenuItem = New ToolStripMenuItem
            Me.AddToSeletedBossToolStripMenuItem = New ToolStripMenuItem
            Me.AddAsNewBossToolStripMenuItem = New ToolStripMenuItem
            Me.cbMonsterSelector1 = New ComboBox
            Me.GroupBox22 = New GroupBox
            Me.ListView2 = New ListView
            Me.lwMonsterName = New ColumnHeader
            Me.lwMoRealName = New ColumnHeader
            Me.lwSpawnRate = New ColumnHeader
            Me.CMSMonsterInMap = New ContextMenuStrip(Me.components)
            Me.RemoveMonsterToolStripMenuItem = New ToolStripMenuItem
            Me.RemoveAllToolStripMenuItem = New ToolStripMenuItem
            Me.EditSpawnRateToolStripMenuItem = New ToolStripMenuItem
            Me.Label36 = New Label
            Me.tbMapValue1 = New TextBox
            Me.tbMapValue2 = New TextBox
            Me.Label97 = New Label
            Me.tbMapValue3 = New TextBox
            Me.Label98 = New Label
            Me.GroupBox21 = New GroupBox
            Me.lbFilesMaps = New ListBox
            Me.cmMapsFiles = New ContextMenuStrip(Me.components)
            Me.ChangeEXPOfMapToolStripMenuItem = New ToolStripMenuItem
            Me.Label96 = New Label
            Me.TabPage5 = New TabPage
            Me.tbNPCSetupfile = New ComboBox
            Me.tbNPCModelFile = New ComboBox
            Me.Label101 = New Label
            Me.GroupBox23 = New GroupBox
            Me.TextBox1 = New TextBox
            Me.tbNPCSetupfileInI = New ComboBox
            Me.CMDNPCShopSave = New Button
            Me.Label116 = New Label
            Me.Label99 = New Label
            Me.LWNPCshop = New ListView
            Me.CoItemCode = New ColumnHeader
            Me.CoItemName = New ColumnHeader
            Me.CMSAddShopItem = New ContextMenuStrip(Me.components)
            Me.AddItemsToolStripMenuItem = New ToolStripMenuItem
            Me.RemoveToolStripMenuItem = New ToolStripMenuItem
            Me.CBShopItem = New ComboBox
            Me.tbNPCangle = New TextBox
            Me.Label106 = New Label
            Me.cmdNPCReload = New Button
            Me.Label107 = New Label
            Me.tbNPCName = New TextBox
            Me.tbNPCJ_Chat = New TextBox
            Me.Label108 = New Label
            Me.tbNPCID = New TextBox
            Me.Label109 = New Label
            Me.Label110 = New Label
            Me.PictureBox1 = New PictureBox
            Me.CMNPCPicturebox = New ContextMenuStrip(Me.components)
            Me.BringBackToMapToolStripMenuItem = New ToolStripMenuItem
            Me.Label111 = New Label
            Me.Label112 = New Label
            Me.cbNPCAktivated = New CheckBox
            Me.cmdNPCSave = New Button
            Me.lbNPCMapFileList = New ListBox
            Me.lbNPCList = New ListBox
            Me.CMSNPCList = New ContextMenuStrip(Me.components)
            Me.UpToolStripMenuItem = New ToolStripMenuItem
            Me.DownToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteNPCToolStripMenuItem = New ToolStripMenuItem
            Me.DeleteNPCToolStripMenuItem1 = New ToolStripMenuItem
            Me.Label113 = New Label
            Me.Label114 = New Label
            Me.Label115 = New Label
            Me.tbNPCz = New TextBox
            Me.tbNPCy = New TextBox
            Me.tbNPCx = New TextBox
            Me.TabPage4 = New TabPage
            Me.GroupBox7 = New GroupBox
            Me.Label100 = New Label
            Me.cmdDelBackup = New Button
            Me.cbMoZhoonWarn = New CheckBox
            Me.cmdCheckMaps = New Button
            Me.cbWarnMap = New CheckBox
            Me.CmdCheckDrop = New Button
            Me.cmdCheckGold = New Button
            Me.cmd_Check = New Button
            Me.tbWarnItem = New TextBox
            Me.Label43 = New Label
            Me.tbMaxGold = New TextBox
            Me.Label42 = New Label
            Me.tbMaxExp = New TextBox
            Me.Label41 = New Label
            Me.Settings = New GroupBox
            Me.Button3 = New Button
            Me.cmdSaveConfig = New Button
            Me.cmdShowLog = New Button
            Me.cmdDefaultConfig = New Button
            Me.cmdLoadConfig = New Button
            Me.cmdConfigEdit = New Button
            Me.cmdEditorExe = New Button
            Me.tbServerPath = New TextBox
            Me.tbEditorPath = New TextBox
            Me.cmdPath = New Button
            Me.Label31 = New Label
            Me.pbWorking = New ProgressBar
            Me.Mapsfound = New Label
            Me.ItemFound = New Label
            Me.MoFound = New Label
            Me.Label40 = New Label
            Me.Label39 = New Label
            Me.Label38 = New Label
            Me.lblprgV = New Label
            Me.dlgFile = New OpenFileDialog
            Me.dlgFolder = New FolderBrowserDialog
            Me.lblTextCoding = New Label
            Me.ttAll = New ToolTip(Me.components)
            Me.ListBox1 = New ListBox
            Me.Label95 = New Label
            Me.Label117 = New Label
            Me.lblProg = New Label
            Me.cnMonsterFiles.SuspendLayout
            Me.GroupBox1.SuspendLayout
            Me.GroupBox2.SuspendLayout
            Me.GroupBox3.SuspendLayout
            Me.cmsDrops.SuspendLayout
            Me.GroupBox4.SuspendLayout
            Me.TabControl1.SuspendLayout
            Me.TabPage1.SuspendLayout
            Me.GroupBox5.SuspendLayout
            Me.cmMonsterItem.SuspendLayout
            Me.TabPage2.SuspendLayout
            Me.GroupBox20.SuspendLayout
            Me.cmItemsMonster.SuspendLayout
            Me.CMFilterSaver.SuspendLayout
            Me.GroupBox19.SuspendLayout
            Me.GroupBox18.SuspendLayout
            Me.GroupBox17.SuspendLayout
            Me.GroupBox16.SuspendLayout
            Me.GroupBox15.SuspendLayout
            Me.GroupBox14.SuspendLayout
            Me.GroupBox13.SuspendLayout
            Me.GroupBox12.SuspendLayout
            Me.GroupBox11.SuspendLayout
            Me.GroupBox10.SuspendLayout
            Me.GroupBox9.SuspendLayout
            Me.GroupBox8.SuspendLayout
            Me.GroupBox6.SuspendLayout
            Me.cmFileListItems.SuspendLayout
            Me.TabPage3.SuspendLayout
            Me.CMSMapBoss.SuspendLayout
            Me.gb24.SuspendLayout
            Me.CMSMapMonsterToAdd.SuspendLayout
            Me.GroupBox22.SuspendLayout
            Me.CMSMonsterInMap.SuspendLayout
            Me.GroupBox21.SuspendLayout
            Me.cmMapsFiles.SuspendLayout
            Me.TabPage5.SuspendLayout
            Me.GroupBox23.SuspendLayout
            Me.CMSAddShopItem.SuspendLayout
            DirectCast(Me.PictureBox1, ISupportInitialize).BeginInit
            Me.CMNPCPicturebox.SuspendLayout
            Me.CMSNPCList.SuspendLayout
            Me.TabPage4.SuspendLayout
            Me.GroupBox7.SuspendLayout
            Me.Settings.SuspendLayout
            Me.SuspendLayout
            Dim point As New Point(&H57, 7)
            Me.cmdSave.Location = point
            Me.cmdSave.Name = "cmdSave"
            Dim size As New Size(&H4B, &H17)
            Me.cmdSave.Size = size
            Me.cmdSave.TabIndex = 1
            Me.cmdSave.Text = "Save"
            Me.cmdSave.UseVisualStyleBackColor = True
            point = New Point(6, 7)
            Me.cmdReload.Location = point
            Me.cmdReload.Name = "cmdReload"
            size = New Size(&H4B, &H17)
            Me.cmdReload.Size = size
            Me.cmdReload.TabIndex = 2
            Me.cmdReload.Text = "Reload"
            Me.cmdReload.UseVisualStyleBackColor = True
            Me.lbFiles.ContextMenuStrip = Me.cnMonsterFiles
            Me.lbFiles.FormattingEnabled = True
            point = New Point(10, &H37)
            Me.lbFiles.Location = point
            Me.lbFiles.Name = "lbFiles"
            Me.lbFiles.SelectionMode = SelectionMode.MultiExtended
            size = New Size(&H9D, &H156)
            Me.lbFiles.Size = size
            Me.lbFiles.Sorted = True
            Me.lbFiles.TabIndex = 3
            Me.cnMonsterFiles.Items.AddRange(New ToolStripItem() { Me.SaveMonstersToolStripMenuItem, Me.ChangeToolStripMenuItem, Me.BackupsToolStripMenuItem, Me.DeleteBackupToolStripMenuItem })
            Me.cnMonsterFiles.Name = "ContextMenuStrip1"
            size = New Size(&H8F, &H5C)
            Me.cnMonsterFiles.Size = size
            Me.SaveMonstersToolStripMenuItem.DropDownItems.AddRange(New ToolStripItem() { Me.ItemToolStripMenuItem })
            Me.SaveMonstersToolStripMenuItem.Name = "SaveMonstersToolStripMenuItem"
            size = New Size(&H8E, &H16)
            Me.SaveMonstersToolStripMenuItem.Size = size
            Me.SaveMonstersToolStripMenuItem.Text = "Search"
            Me.ItemToolStripMenuItem.Name = "ItemToolStripMenuItem"
            size = New Size(&H60, &H16)
            Me.ItemToolStripMenuItem.Size = size
            Me.ItemToolStripMenuItem.Text = "Item"
            Me.ChangeToolStripMenuItem.DropDownItems.AddRange(New ToolStripItem() { Me.DropCountToolStripMenuItem1, Me.ExperienceToolStripMenuItem1, Me.GoldToolStripMenuItem })
            Me.ChangeToolStripMenuItem.Name = "ChangeToolStripMenuItem"
            size = New Size(&H8E, &H16)
            Me.ChangeToolStripMenuItem.Size = size
            Me.ChangeToolStripMenuItem.Text = "Change"
            Me.DropCountToolStripMenuItem1.Name = "DropCountToolStripMenuItem1"
            size = New Size(&H81, &H16)
            Me.DropCountToolStripMenuItem1.Size = size
            Me.DropCountToolStripMenuItem1.Text = "Drop Count"
            Me.ExperienceToolStripMenuItem1.Name = "ExperienceToolStripMenuItem1"
            size = New Size(&H81, &H16)
            Me.ExperienceToolStripMenuItem1.Size = size
            Me.ExperienceToolStripMenuItem1.Text = "Experience"
            Me.GoldToolStripMenuItem.Name = "GoldToolStripMenuItem"
            size = New Size(&H81, &H16)
            Me.GoldToolStripMenuItem.Size = size
            Me.GoldToolStripMenuItem.Text = "Gold"
            Me.BackupsToolStripMenuItem.Name = "BackupsToolStripMenuItem"
            size = New Size(&H8E, &H16)
            Me.BackupsToolStripMenuItem.Size = size
            Me.BackupsToolStripMenuItem.Text = "Load Backup"
            Me.DeleteBackupToolStripMenuItem.Name = "DeleteBackupToolStripMenuItem"
            size = New Size(&H8E, &H16)
            Me.DeleteBackupToolStripMenuItem.Size = size
            Me.DeleteBackupToolStripMenuItem.Text = "Delete Backup"
            Me.lbFound.AutoSize = True
            point = New Point(7, &H10)
            Me.lbFound.Location = point
            Me.lbFound.Name = "lbFound"
            size = New Size(&H27, 13)
            Me.lbFound.Size = size
            Me.lbFound.TabIndex = 4
            Me.lbFound.Text = "Label1"
            Me.GroupBox1.Controls.Add(Me.Label28)
            Me.GroupBox1.Controls.Add(Me.tbMoExp)
            Me.GroupBox1.Controls.Add(Me.Label27)
            Me.GroupBox1.Controls.Add(Me.tbMoSnd)
            Me.GroupBox1.Controls.Add(Me.Label26)
            Me.GroupBox1.Controls.Add(Me.cbMoTyp)
            Me.GroupBox1.Controls.Add(Me.Label16)
            Me.GroupBox1.Controls.Add(Me.tbMoMTyp)
            Me.GroupBox1.Controls.Add(Me.Label9)
            Me.GroupBox1.Controls.Add(Me.tbMoMSpd)
            Me.GroupBox1.Controls.Add(Me.Label8)
            Me.GroupBox1.Controls.Add(Me.tbMoHp)
            Me.GroupBox1.Controls.Add(Me.Label7)
            Me.GroupBox1.Controls.Add(Me.tbMoVision)
            Me.GroupBox1.Controls.Add(Me.Label6)
            Me.GroupBox1.Controls.Add(Me.tbMoChar)
            Me.GroupBox1.Controls.Add(Me.Label5)
            Me.GroupBox1.Controls.Add(Me.tbMoInt)
            Me.GroupBox1.Controls.Add(Me.Label4)
            Me.GroupBox1.Controls.Add(Me.tbMoApp)
            Me.GroupBox1.Controls.Add(Me.Label3)
            Me.GroupBox1.Controls.Add(Me.tbMoSpCode)
            Me.GroupBox1.Controls.Add(Me.Label2)
            Me.GroupBox1.Controls.Add(Me.tbMoLevel)
            point = New Point(&HBD, &H88)
            Me.GroupBox1.Location = point
            Me.GroupBox1.Name = "GroupBox1"
            size = New Size(200, &H151)
            Me.GroupBox1.Size = size
            Me.GroupBox1.TabIndex = 6
            Me.GroupBox1.TabStop = False
            Me.GroupBox1.Text = "Monster Settings"
            Me.Label28.AutoSize = True
            point = New Point(6, &H11A)
            Me.Label28.Location = point
            Me.Label28.Name = "Label28"
            size = New Size(&H3F, 13)
            Me.Label28.Size = size
            Me.Label28.TabIndex = &H23
            Me.Label28.Text = "Experience:"
            point = New Point(&H63, &H117)
            Me.tbMoExp.Location = point
            Me.tbMoExp.Name = "tbMoExp"
            size = New Size(&H4B, 20)
            Me.tbMoExp.Size = size
            Me.tbMoExp.TabIndex = &H22
            Me.Label27.AutoSize = True
            point = New Point(6, &H100)
            Me.Label27.Location = point
            Me.Label27.Name = "Label27"
            size = New Size(&H48, 13)
            Me.Label27.Size = size
            Me.Label27.TabIndex = &H21
            Me.Label27.Text = "Sound Effekt:"
            point = New Point(&H63, &HFD)
            Me.tbMoSnd.Location = point
            Me.tbMoSnd.Name = "tbMoSnd"
            size = New Size(&H4B, 20)
            Me.tbMoSnd.Size = size
            Me.tbMoSnd.TabIndex = &H20
            Me.Label26.AutoSize = True
            point = New Point(6, &H134)
            Me.Label26.Location = point
            Me.Label26.Name = "Label26"
            size = New Size(&H1C, 13)
            Me.Label26.Size = size
            Me.Label26.TabIndex = &H1F
            Me.Label26.Text = "Typ:"
            Me.cbMoTyp.FormattingEnabled = True
            Me.cbMoTyp.Items.AddRange(New Object() { "Daemon", "Mechanic", "Mutant", "Normal", "Undead" })
            point = New Point(&H43, &H131)
            Me.cbMoTyp.Location = point
            Me.cbMoTyp.Name = "cbMoTyp"
            size = New Size(&H6B, &H15)
            Me.cbMoTyp.Size = size
            Me.cbMoTyp.TabIndex = 30
            Me.Label16.AutoSize = True
            point = New Point(6, 230)
            Me.Label16.Location = point
            Me.Label16.Name = "Label16"
            size = New Size(&H57, 13)
            Me.Label16.Size = size
            Me.Label16.TabIndex = &H13
            Me.Label16.Text = "Movement Type:"
            point = New Point(&H63, &HE3)
            Me.tbMoMTyp.Location = point
            Me.tbMoMTyp.Name = "tbMoMTyp"
            size = New Size(&H4B, 20)
            Me.tbMoMTyp.Size = size
            Me.tbMoMTyp.TabIndex = &H12
            Me.Label9.AutoSize = True
            point = New Point(6, &HCC)
            Me.Label9.Location = point
            Me.Label9.Name = "Label9"
            size = New Size(&H29, 13)
            Me.Label9.Size = size
            Me.Label9.TabIndex = &H11
            Me.Label9.Text = "Speed:"
            point = New Point(&H63, &HC9)
            Me.tbMoMSpd.Location = point
            Me.tbMoMSpd.Name = "tbMoMSpd"
            size = New Size(&H4B, 20)
            Me.tbMoMSpd.Size = size
            Me.tbMoMSpd.TabIndex = &H10
            Me.Label8.AutoSize = True
            point = New Point(6, &HB2)
            Me.Label8.Location = point
            Me.Label8.Name = "Label8"
            size = New Size(&H19, 13)
            Me.Label8.Size = size
            Me.Label8.TabIndex = 15
            Me.Label8.Text = "HP:"
            point = New Point(&H63, &HAF)
            Me.tbMoHp.Location = point
            Me.tbMoHp.Name = "tbMoHp"
            size = New Size(&H4B, 20)
            Me.tbMoHp.Size = size
            Me.tbMoHp.TabIndex = 14
            Me.Label7.AutoSize = True
            point = New Point(6, &H98)
            Me.Label7.Location = point
            Me.Label7.Name = "Label7"
            size = New Size(&H2A, 13)
            Me.Label7.Size = size
            Me.Label7.TabIndex = 13
            Me.Label7.Text = "Range:"
            point = New Point(&H63, &H95)
            Me.tbMoVision.Location = point
            Me.tbMoVision.Name = "tbMoVision"
            size = New Size(&H4B, 20)
            Me.tbMoVision.Size = size
            Me.tbMoVision.TabIndex = 12
            Me.Label6.AutoSize = True
            point = New Point(6, &H7E)
            Me.Label6.Location = point
            Me.Label6.Name = "Label6"
            size = New Size(&H38, 13)
            Me.Label6.Size = size
            Me.Label6.TabIndex = 11
            Me.Label6.Text = "Character:"
            point = New Point(&H63, &H7B)
            Me.tbMoChar.Location = point
            Me.tbMoChar.Name = "tbMoChar"
            size = New Size(&H4B, 20)
            Me.tbMoChar.Size = size
            Me.tbMoChar.TabIndex = 10
            Me.Label5.AutoSize = True
            point = New Point(6, 100)
            Me.Label5.Location = point
            Me.Label5.Name = "Label5"
            size = New Size(&H40, 13)
            Me.Label5.Size = size
            Me.Label5.TabIndex = 9
            Me.Label5.Text = "Intelligence:"
            point = New Point(&H63, &H61)
            Me.tbMoInt.Location = point
            Me.tbMoInt.Name = "tbMoInt"
            size = New Size(&H4B, 20)
            Me.tbMoInt.Size = size
            Me.tbMoInt.TabIndex = 8
            Me.Label4.AutoSize = True
            point = New Point(6, &H4A)
            Me.Label4.Location = point
            Me.Label4.Name = "Label4"
            size = New Size(&H34, 13)
            Me.Label4.Size = size
            Me.Label4.TabIndex = 7
            Me.Label4.Text = "Appering:"
            point = New Point(&H63, &H47)
            Me.tbMoApp.Location = point
            Me.tbMoApp.Name = "tbMoApp"
            size = New Size(&H4B, 20)
            Me.tbMoApp.Size = size
            Me.tbMoApp.TabIndex = 6
            Me.Label3.AutoSize = True
            point = New Point(6, &H30)
            Me.Label3.Location = point
            Me.Label3.Name = "Label3"
            size = New Size(&H49, 13)
            Me.Label3.Size = size
            Me.Label3.TabIndex = 5
            Me.Label3.Text = "Special Code:"
            point = New Point(&H63, &H2D)
            Me.tbMoSpCode.Location = point
            Me.tbMoSpCode.Name = "tbMoSpCode"
            size = New Size(&H4B, 20)
            Me.tbMoSpCode.Size = size
            Me.tbMoSpCode.TabIndex = 4
            Me.Label2.AutoSize = True
            point = New Point(6, &H16)
            Me.Label2.Location = point
            Me.Label2.Name = "Label2"
            size = New Size(&H24, 13)
            Me.Label2.Size = size
            Me.Label2.TabIndex = 3
            Me.Label2.Text = "Level:"
            point = New Point(&H63, &H13)
            Me.tbMoLevel.Location = point
            Me.tbMoLevel.Name = "tbMoLevel"
            size = New Size(&H4B, 20)
            Me.tbMoLevel.Size = size
            Me.tbMoLevel.TabIndex = 2
            Me.Label1.AutoSize = True
            point = New Point(&HC0, &H21)
            Me.Label1.Location = point
            Me.Label1.Name = "Label1"
            size = New Size(&H48, 13)
            Me.Label1.Size = size
            Me.Label1.TabIndex = 1
            Me.Label1.Text = "Zhoon Name:"
            point = New Point(&H11D, 30)
            Me.tbMoName.Location = point
            Me.tbMoName.Name = "tbMoName"
            Me.tbMoName.ReadOnly = True
            size = New Size(&H65, 20)
            Me.tbMoName.Size = size
            Me.tbMoName.TabIndex = 0
            Me.GroupBox2.Controls.Add(Me.Label15)
            Me.GroupBox2.Controls.Add(Me.tbMoPAtkRtg)
            Me.GroupBox2.Controls.Add(Me.Label14)
            Me.GroupBox2.Controls.Add(Me.tbMoAtkSpd)
            Me.GroupBox2.Controls.Add(Me.Label13)
            Me.GroupBox2.Controls.Add(Me.tbMoAtkRtg)
            Me.GroupBox2.Controls.Add(Me.Label12)
            Me.GroupBox2.Controls.Add(Me.tbMoAtkCrit)
            Me.GroupBox2.Controls.Add(Me.Label11)
            Me.GroupBox2.Controls.Add(Me.tbMoSKAtk)
            Me.GroupBox2.Controls.Add(Me.Label10)
            Me.GroupBox2.Controls.Add(Me.tbMoAtkPow)
            point = New Point(&HBD, &H1DF)
            Me.GroupBox2.Location = point
            Me.GroupBox2.Name = "GroupBox2"
            size = New Size(200, &HB0)
            Me.GroupBox2.Size = size
            Me.GroupBox2.TabIndex = 7
            Me.GroupBox2.TabStop = False
            Me.GroupBox2.Text = "Monster Attack"
            Me.Label15.AutoSize = True
            point = New Point(6, &H92)
            Me.Label15.Location = point
            Me.Label15.Name = "Label15"
            size = New Size(&H4E, 13)
            Me.Label15.Size = size
            Me.Label15.TabIndex = &H1D
            Me.Label15.Text = "Perfect Rating:"
            point = New Point(&H63, &H8F)
            Me.tbMoPAtkRtg.Location = point
            Me.tbMoPAtkRtg.Name = "tbMoPAtkRtg"
            size = New Size(&H4B, 20)
            Me.tbMoPAtkRtg.Size = size
            Me.tbMoPAtkRtg.TabIndex = &H1C
            Me.Label14.AutoSize = True
            point = New Point(6, &H10)
            Me.Label14.Location = point
            Me.Label14.Name = "Label14"
            size = New Size(&H4B, 13)
            Me.Label14.Size = size
            Me.Label14.TabIndex = &H1B
            Me.Label14.Text = "Attack Speed:"
            point = New Point(&H63, 13)
            Me.tbMoAtkSpd.Location = point
            Me.tbMoAtkSpd.Name = "tbMoAtkSpd"
            size = New Size(&H4B, 20)
            Me.tbMoAtkSpd.Size = size
            Me.tbMoAtkSpd.TabIndex = &H1A
            Me.Label13.AutoSize = True
            point = New Point(6, 120)
            Me.Label13.Location = point
            Me.Label13.Name = "Label13"
            size = New Size(&H4B, 13)
            Me.Label13.Size = size
            Me.Label13.TabIndex = &H19
            Me.Label13.Text = "Attack Rating:"
            point = New Point(&H63, &H75)
            Me.tbMoAtkRtg.Location = point
            Me.tbMoAtkRtg.Name = "tbMoAtkRtg"
            size = New Size(&H4B, 20)
            Me.tbMoAtkRtg.Size = size
            Me.tbMoAtkRtg.TabIndex = &H18
            Me.Label12.AutoSize = True
            point = New Point(6, &H5E)
            Me.Label12.Location = point
            Me.Label12.Name = "Label12"
            size = New Size(&H4B, 13)
            Me.Label12.Size = size
            Me.Label12.TabIndex = &H17
            Me.Label12.Text = "Critical Attack:"
            point = New Point(&H63, &H5B)
            Me.tbMoAtkCrit.Location = point
            Me.tbMoAtkCrit.Name = "tbMoAtkCrit"
            size = New Size(&H4B, 20)
            Me.tbMoAtkCrit.Size = size
            Me.tbMoAtkCrit.TabIndex = &H16
            Me.Label11.AutoSize = True
            point = New Point(6, &H44)
            Me.Label11.Location = point
            Me.Label11.Name = "Label11"
            size = New Size(&H3E, 13)
            Me.Label11.Size = size
            Me.Label11.TabIndex = &H15
            Me.Label11.Text = "Skill Power:"
            point = New Point(&H63, &H41)
            Me.tbMoSKAtk.Location = point
            Me.tbMoSKAtk.Name = "tbMoSKAtk"
            size = New Size(&H4B, 20)
            Me.tbMoSKAtk.Size = size
            Me.tbMoSKAtk.TabIndex = 20
            Me.Label10.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label10.Location = point
            Me.Label10.Name = "Label10"
            size = New Size(&H4A, 13)
            Me.Label10.Size = size
            Me.Label10.TabIndex = &H13
            Me.Label10.Text = "Attack Power:"
            point = New Point(&H63, &H27)
            Me.tbMoAtkPow.Location = point
            Me.tbMoAtkPow.Name = "tbMoAtkPow"
            size = New Size(&H4B, 20)
            Me.tbMoAtkPow.Size = size
            Me.tbMoAtkPow.TabIndex = &H12
            Me.Label17.AutoSize = True
            point = New Point(6, &H30)
            Me.Label17.Location = point
            Me.Label17.Name = "Label17"
            size = New Size(&H2B, 13)
            Me.Label17.Size = size
            Me.Label17.TabIndex = &H15
            Me.Label17.Text = "Absorb:"
            point = New Point(&H63, &H2D)
            Me.tbMoAbs.Location = point
            Me.tbMoAbs.Name = "tbMoAbs"
            size = New Size(&H4B, 20)
            Me.tbMoAbs.Size = size
            Me.tbMoAbs.TabIndex = 20
            Me.GroupBox3.Controls.Add(Me.Label25)
            Me.GroupBox3.Controls.Add(Me.tbMoMage)
            Me.GroupBox3.Controls.Add(Me.Label24)
            Me.GroupBox3.Controls.Add(Me.tbMoPoision)
            Me.GroupBox3.Controls.Add(Me.Label23)
            Me.GroupBox3.Controls.Add(Me.tbMoFire)
            Me.GroupBox3.Controls.Add(Me.Label22)
            Me.GroupBox3.Controls.Add(Me.tbMoIce)
            Me.GroupBox3.Controls.Add(Me.Label21)
            Me.GroupBox3.Controls.Add(Me.tbMoLtg)
            Me.GroupBox3.Controls.Add(Me.Label20)
            Me.GroupBox3.Controls.Add(Me.tbMoOrg)
            Me.GroupBox3.Controls.Add(Me.Label19)
            Me.GroupBox3.Controls.Add(Me.tbMoBlk)
            Me.GroupBox3.Controls.Add(Me.Label18)
            Me.GroupBox3.Controls.Add(Me.tbMoDef)
            Me.GroupBox3.Controls.Add(Me.Label17)
            Me.GroupBox3.Controls.Add(Me.tbMoAbs)
            point = New Point(&H18B, &H88)
            Me.GroupBox3.Location = point
            Me.GroupBox3.Name = "GroupBox3"
            size = New Size(200, 260)
            Me.GroupBox3.Size = size
            Me.GroupBox3.TabIndex = 8
            Me.GroupBox3.TabStop = False
            Me.GroupBox3.Text = "Monster Defensive"
            Me.Label25.AutoSize = True
            point = New Point(6, 230)
            Me.Label25.Location = point
            Me.Label25.Name = "Label25"
            size = New Size(&H42, 13)
            Me.Label25.Size = size
            Me.Label25.TabIndex = &H25
            Me.Label25.Text = "Resi. Magic:"
            point = New Point(&H63, &HE3)
            Me.tbMoMage.Location = point
            Me.tbMoMage.Name = "tbMoMage"
            size = New Size(&H4B, 20)
            Me.tbMoMage.Size = size
            Me.tbMoMage.TabIndex = &H24
            Me.Label24.AutoSize = True
            point = New Point(6, &HCC)
            Me.Label24.Location = point
            Me.Label24.Name = "Label24"
            size = New Size(&H45, 13)
            Me.Label24.Size = size
            Me.Label24.TabIndex = &H23
            Me.Label24.Text = "Resi. Poison:"
            point = New Point(&H63, &HC9)
            Me.tbMoPoision.Location = point
            Me.tbMoPoision.Name = "tbMoPoision"
            size = New Size(&H4B, 20)
            Me.tbMoPoision.Size = size
            Me.tbMoPoision.TabIndex = &H22
            Me.Label23.AutoSize = True
            point = New Point(6, &HB2)
            Me.Label23.Location = point
            Me.Label23.Name = "Label23"
            size = New Size(&H36, 13)
            Me.Label23.Size = size
            Me.Label23.TabIndex = &H21
            Me.Label23.Text = "Resi. Fire:"
            point = New Point(&H63, &HAF)
            Me.tbMoFire.Location = point
            Me.tbMoFire.Name = "tbMoFire"
            size = New Size(&H4B, 20)
            Me.tbMoFire.Size = size
            Me.tbMoFire.TabIndex = &H20
            Me.Label22.AutoSize = True
            point = New Point(6, &H98)
            Me.Label22.Location = point
            Me.Label22.Name = "Label22"
            size = New Size(&H34, 13)
            Me.Label22.Size = size
            Me.Label22.TabIndex = &H1F
            Me.Label22.Text = "Resi. Ice:"
            point = New Point(&H63, &H95)
            Me.tbMoIce.Location = point
            Me.tbMoIce.Name = "tbMoIce"
            size = New Size(&H4B, 20)
            Me.tbMoIce.Size = size
            Me.tbMoIce.TabIndex = 30
            Me.Label21.AutoSize = True
            point = New Point(6, &H7E)
            Me.Label21.Location = point
            Me.Label21.Name = "Label21"
            size = New Size(&H4A, 13)
            Me.Label21.Size = size
            Me.Label21.TabIndex = &H1D
            Me.Label21.Text = "Resi. Lighting:"
            point = New Point(&H63, &H7B)
            Me.tbMoLtg.Location = point
            Me.tbMoLtg.Name = "tbMoLtg"
            size = New Size(&H4B, 20)
            Me.tbMoLtg.Size = size
            Me.tbMoLtg.TabIndex = &H1C
            Me.Label20.AutoSize = True
            point = New Point(6, 100)
            Me.Label20.Location = point
            Me.Label20.Name = "Label20"
            size = New Size(&H51, 13)
            Me.Label20.Size = size
            Me.Label20.TabIndex = &H1B
            Me.Label20.Text = "Resi. Organism:"
            point = New Point(&H63, &H61)
            Me.tbMoOrg.Location = point
            Me.tbMoOrg.Name = "tbMoOrg"
            size = New Size(&H4B, 20)
            Me.tbMoOrg.Size = size
            Me.tbMoOrg.TabIndex = &H1A
            Me.Label19.AutoSize = True
            point = New Point(6, &H4A)
            Me.Label19.Location = point
            Me.Label19.Name = "Label19"
            size = New Size(&H25, 13)
            Me.Label19.Size = size
            Me.Label19.TabIndex = &H19
            Me.Label19.Text = "Block:"
            point = New Point(&H63, &H47)
            Me.tbMoBlk.Location = point
            Me.tbMoBlk.Name = "tbMoBlk"
            size = New Size(&H4B, 20)
            Me.tbMoBlk.Size = size
            Me.tbMoBlk.TabIndex = &H18
            Me.Label18.AutoSize = True
            point = New Point(6, &H16)
            Me.Label18.Location = point
            Me.Label18.Name = "Label18"
            size = New Size(&H33, 13)
            Me.Label18.Size = size
            Me.Label18.TabIndex = &H17
            Me.Label18.Text = "Defence:"
            point = New Point(&H63, &H13)
            Me.tbMoDef.Location = point
            Me.tbMoDef.Name = "tbMoDef"
            size = New Size(&H4B, 20)
            Me.tbMoDef.Size = size
            Me.tbMoDef.TabIndex = &H16
            point = New Point(&H1EE, &H1A3)
            Me.tbMoNoDrop.Location = point
            Me.tbMoNoDrop.Name = "tbMoNoDrop"
            size = New Size(&H4B, 20)
            Me.tbMoNoDrop.Size = size
            Me.tbMoNoDrop.TabIndex = 11
            Me.Label37.AutoSize = True
            point = New Point(&HC0, 60)
            Me.Label37.Location = point
            Me.Label37.Name = "Label37"
            size = New Size(&H49, 13)
            Me.Label37.Size = size
            Me.Label37.TabIndex = 13
            Me.Label37.Text = "Name in Map:"
            point = New Point(&H11D, &H39)
            Me.tbMoMapName.Location = point
            Me.tbMoMapName.Name = "tbMoMapName"
            size = New Size(&H65, 20)
            Me.tbMoMapName.Size = size
            Me.tbMoMapName.TabIndex = 12
            Me.lwItems.ContextMenuStrip = Me.cmsDrops
            Me.lwItems.FullRowSelect = True
            Me.lwItems.LabelWrap = False
            point = New Point(&H18B, &H1D8)
            Me.lwItems.Location = point
            Me.lwItems.MultiSelect = False
            Me.lwItems.Name = "lwItems"
            size = New Size(&H27F, &HB7)
            Me.lwItems.Size = size
            Me.lwItems.TabIndex = 14
            Me.lwItems.UseCompatibleStateImageBehavior = False
            Me.cmsDrops.Items.AddRange(New ToolStripItem() { Me.AddDroplineToolStripMenuItem, Me.DeleteLineToolStripMenuItem })
            Me.cmsDrops.Name = "cmsDrops"
            size = New Size(&H7D, &H30)
            Me.cmsDrops.Size = size
            Me.AddDroplineToolStripMenuItem.Name = "AddDroplineToolStripMenuItem"
            size = New Size(&H7C, &H16)
            Me.AddDroplineToolStripMenuItem.Size = size
            Me.AddDroplineToolStripMenuItem.Text = "New line"
            Me.DeleteLineToolStripMenuItem.Name = "DeleteLineToolStripMenuItem"
            size = New Size(&H7C, &H16)
            Me.DeleteLineToolStripMenuItem.Size = size
            Me.DeleteLineToolStripMenuItem.Text = "Delete line"
            Me.Label29.AutoSize = True
            point = New Point(&H191, &H1C0)
            Me.Label29.Location = point
            Me.Label29.Name = "Label29"
            size = New Size(&H55, 13)
            Me.Label29.Size = size
            Me.Label29.TabIndex = &H26
            Me.Label29.Text = "Edit Rate-Drops:"
            point = New Point(&H1EE, &H1BD)
            Me.tbDroprate.Location = point
            Me.tbDroprate.Name = "tbDroprate"
            size = New Size(&H4B, 20)
            Me.tbDroprate.Size = size
            Me.tbDroprate.TabIndex = &H26
            Me.Label30.AutoSize = True
            point = New Point(&H191, &H1A6)
            Me.Label30.Location = point
            Me.Label30.Name = "Label30"
            size = New Size(&H3F, 13)
            Me.Label30.Size = size
            Me.Label30.TabIndex = &H27
            Me.Label30.Text = "Drop count:"
            point = New Point(&H23F, &H1BD)
            Me.tbDrops.Location = point
            Me.tbDrops.Name = "tbDrops"
            size = New Size(&H1CB, 20)
            Me.tbDrops.Size = size
            Me.tbDrops.TabIndex = 40
            Me.lbMaps.FormattingEnabled = True
            point = New Point(10, &H1BF)
            Me.lbMaps.Location = point
            Me.lbMaps.Name = "lbMaps"
            size = New Size(&H9D, &H86)
            Me.lbMaps.Size = size
            Me.lbMaps.TabIndex = &H29
            Me.chNotFound.AutoSize = True
            point = New Point(10, &H1AA)
            Me.chNotFound.Location = point
            Me.chNotFound.Name = "chNotFound"
            size = New Size(&H75, &H11)
            Me.chNotFound.Size = size
            Me.chNotFound.TabIndex = &H2C
            Me.chNotFound.Text = "Monster not in Map"
            Me.chNotFound.UseVisualStyleBackColor = True
            Me.GroupBox4.Controls.Add(Me.cbSelectAll)
            Me.GroupBox4.Controls.Add(Me.chNotFound)
            Me.GroupBox4.Controls.Add(Me.lbFiles)
            Me.GroupBox4.Controls.Add(Me.chMapEn)
            Me.GroupBox4.Controls.Add(Me.lbMaps)
            Me.GroupBox4.Controls.Add(Me.lbFound)
            point = New Point(6, 60)
            Me.GroupBox4.Location = point
            Me.GroupBox4.Name = "GroupBox4"
            size = New Size(&HB1, &H253)
            Me.GroupBox4.Size = size
            Me.GroupBox4.TabIndex = &H2D
            Me.GroupBox4.TabStop = False
            Me.GroupBox4.Text = "Files Monsters"
            Me.cbSelectAll.AutoSize = True
            point = New Point(10, &H20)
            Me.cbSelectAll.Location = point
            Me.cbSelectAll.Name = "cbSelectAll"
            size = New Size(&H45, &H11)
            Me.cbSelectAll.Size = size
            Me.cbSelectAll.TabIndex = &H2D
            Me.cbSelectAll.Text = "Select all"
            Me.cbSelectAll.UseVisualStyleBackColor = True
            Me.chMapEn.AutoSize = True
            Me.chMapEn.Checked = MySettings.Default.chMap
            Me.chMapEn.DataBindings.Add(New Binding("Checked", MySettings.Default, "chMap", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(10, &H193)
            Me.chMapEn.Location = point
            Me.chMapEn.Name = "chMapEn"
            size = New Size(&H8B, &H11)
            Me.chMapEn.Size = size
            Me.chMapEn.TabIndex = &H2B
            Me.chMapEn.Text = "Search monster in maps"
            Me.chMapEn.UseVisualStyleBackColor = True
            Me.TabControl1.Controls.Add(Me.TabPage1)
            Me.TabControl1.Controls.Add(Me.TabPage2)
            Me.TabControl1.Controls.Add(Me.TabPage3)
            Me.TabControl1.Controls.Add(Me.TabPage5)
            Me.TabControl1.Controls.Add(Me.TabPage4)
            point = New Point(4, 5)
            Me.TabControl1.Location = point
            Me.TabControl1.Name = "TabControl1"
            Me.TabControl1.SelectedIndex = 0
            size = New Size(&H418, &H2AE)
            Me.TabControl1.Size = size
            Me.TabControl1.TabIndex = &H2E
            Me.TabPage1.Controls.Add(Me.cmdMoRealName)
            Me.TabPage1.Controls.Add(Me.cbMonsterSelector)
            Me.TabPage1.Controls.Add(Me.cbMoBoss)
            Me.TabPage1.Controls.Add(Me.Label80)
            Me.TabPage1.Controls.Add(Me.tbMoSize)
            Me.TabPage1.Controls.Add(Me.GroupBox5)
            Me.TabPage1.Controls.Add(Me.GroupBox4)
            Me.TabPage1.Controls.Add(Me.Label37)
            Me.TabPage1.Controls.Add(Me.GroupBox2)
            Me.TabPage1.Controls.Add(Me.tbMoMapName)
            Me.TabPage1.Controls.Add(Me.tbDrops)
            Me.TabPage1.Controls.Add(Me.cmdReload)
            Me.TabPage1.Controls.Add(Me.cmdSave)
            Me.TabPage1.Controls.Add(Me.Label30)
            Me.TabPage1.Controls.Add(Me.Label1)
            Me.TabPage1.Controls.Add(Me.tbMoNoDrop)
            Me.TabPage1.Controls.Add(Me.tbMoName)
            Me.TabPage1.Controls.Add(Me.tbDroprate)
            Me.TabPage1.Controls.Add(Me.lwItems)
            Me.TabPage1.Controls.Add(Me.Label29)
            Me.TabPage1.Controls.Add(Me.GroupBox1)
            Me.TabPage1.Controls.Add(Me.GroupBox3)
            point = New Point(4, &H16)
            Me.TabPage1.Location = point
            Me.TabPage1.Name = "TabPage1"
            Dim padding As New Padding(3)
            Me.TabPage1.Padding = padding
            size = New Size(&H410, 660)
            Me.TabPage1.Size = size
            Me.TabPage1.TabIndex = 0
            Me.TabPage1.Text = "Monsters"
            Me.TabPage1.UseVisualStyleBackColor = True
            point = New Point(&H188, &H19)
            Me.cmdMoRealName.Location = point
            Me.cmdMoRealName.Name = "cmdMoRealName"
            size = New Size(&H4B, &H17)
            Me.cmdMoRealName.Size = size
            Me.cmdMoRealName.TabIndex = &H38
            Me.cmdMoRealName.Text = "Edit name"
            Me.cmdMoRealName.UseVisualStyleBackColor = True
            Me.cbMonsterSelector.FormattingEnabled = True
            point = New Point(6, &H24)
            Me.cbMonsterSelector.Location = point
            Me.cbMonsterSelector.Name = "cbMonsterSelector"
            size = New Size(&HB1, &H15)
            Me.cbMonsterSelector.Size = size
            Me.cbMonsterSelector.TabIndex = &H37
            Me.cbMoBoss.AutoSize = True
            point = New Point(&HC3, &H71)
            Me.cbMoBoss.Location = point
            Me.cbMoBoss.Name = "cbMoBoss"
            size = New Size(&H5B, &H11)
            Me.cbMoBoss.Size = size
            Me.cbMoBoss.TabIndex = &H36
            Me.cbMoBoss.Text = "Monster Glow"
            Me.cbMoBoss.UseVisualStyleBackColor = True
            Me.Label80.AutoSize = True
            point = New Point(&HC0, &H57)
            Me.Label80.Location = point
            Me.Label80.Name = "Label80"
            size = New Size(&H47, 13)
            Me.Label80.Size = size
            Me.Label80.TabIndex = &H35
            Me.Label80.Text = "Monster Size:"
            point = New Point(&H11D, &H53)
            Me.tbMoSize.Location = point
            Me.tbMoSize.Name = "tbMoSize"
            size = New Size(&H65, 20)
            Me.tbMoSize.Size = size
            Me.tbMoSize.TabIndex = &H34
            Me.GroupBox5.Controls.Add(Me.lblMoListName)
            Me.GroupBox5.Controls.Add(Me.chItemInfo)
            Me.GroupBox5.Controls.Add(Me.lbItemFiles)
            Me.GroupBox5.Controls.Add(Me.lbItemsRealName)
            Me.GroupBox5.Controls.Add(Me.Label35)
            Me.GroupBox5.Controls.Add(Me.Label34)
            point = New Point(&H29D, 12)
            Me.GroupBox5.Location = point
            Me.GroupBox5.Name = "GroupBox5"
            size = New Size(&H170, &H1AB)
            Me.GroupBox5.Size = size
            Me.GroupBox5.TabIndex = &H33
            Me.GroupBox5.TabStop = False
            Me.GroupBox5.Text = "Item Info"
            Me.lblMoListName.AutoSize = True
            point = New Point(6, &H20)
            Me.lblMoListName.Location = point
            Me.lblMoListName.Name = "lblMoListName"
            size = New Size(&H2C, 13)
            Me.lblMoListName.Size = size
            Me.lblMoListName.TabIndex = &H34
            Me.lblMoListName.Text = "Nothing"
            Me.chItemInfo.AutoSize = True
            Me.chItemInfo.Checked = MySettings.Default.chItemInfo
            Me.chItemInfo.DataBindings.Add(New Binding("Checked", MySettings.Default, "chItemInfo", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(7, &H11)
            Me.chItemInfo.Location = point
            Me.chItemInfo.Name = "chItemInfo"
            size = New Size(&H3B, &H11)
            Me.chItemInfo.Size = size
            Me.chItemInfo.TabIndex = 50
            Me.chItemInfo.Text = "Enable"
            Me.chItemInfo.UseVisualStyleBackColor = True
            Me.lbItemFiles.ContextMenuStrip = Me.cmMonsterItem
            Me.lbItemFiles.FormattingEnabled = True
            point = New Point(6, &H40)
            Me.lbItemFiles.Location = point
            Me.lbItemFiles.Name = "lbItemFiles"
            size = New Size(&HAD, &H163)
            Me.lbItemFiles.Size = size
            Me.lbItemFiles.TabIndex = &H2E
            Me.cmMonsterItem.Items.AddRange(New ToolStripItem() { Me.GoToItemEditorToolStripMenuItem })
            Me.cmMonsterItem.Name = "ContextMenuStrip1"
            size = New Size(&H9D, &H1A)
            Me.cmMonsterItem.Size = size
            Me.GoToItemEditorToolStripMenuItem.Name = "GoToItemEditorToolStripMenuItem"
            size = New Size(&H9C, &H16)
            Me.GoToItemEditorToolStripMenuItem.Size = size
            Me.GoToItemEditorToolStripMenuItem.Text = "Go to Item Editor"
            Me.lbItemsRealName.FormattingEnabled = True
            point = New Point(&HB9, &H40)
            Me.lbItemsRealName.Location = point
            Me.lbItemsRealName.Name = "lbItemsRealName"
            size = New Size(&HAD, &H163)
            Me.lbItemsRealName.Size = size
            Me.lbItemsRealName.TabIndex = &H31
            Me.Label35.AutoSize = True
            point = New Point(&HB6, &H30)
            Me.Label35.Location = point
            Me.Label35.Name = "Label35"
            size = New Size(&H3A, 13)
            Me.Label35.Size = size
            Me.Label35.TabIndex = &H30
            Me.Label35.Text = "ItemName:"
            Me.Label34.AutoSize = True
            point = New Point(6, &H30)
            Me.Label34.Location = point
            Me.Label34.Name = "Label34"
            size = New Size(&H34, 13)
            Me.Label34.Size = size
            Me.Label34.TabIndex = &H2F
            Me.Label34.Text = "Filename:"
            Me.TabPage2.Controls.Add(Me.cmdItemRealName)
            Me.TabPage2.Controls.Add(Me.cmdItemSave)
            Me.TabPage2.Controls.Add(Me.GroupBox20)
            Me.TabPage2.Controls.Add(Me.cbItemSelector)
            Me.TabPage2.Controls.Add(Me.cmdReload1)
            Me.TabPage2.Controls.Add(Me.GroupBox19)
            Me.TabPage2.Controls.Add(Me.GroupBox18)
            Me.TabPage2.Controls.Add(Me.GroupBox17)
            Me.TabPage2.Controls.Add(Me.GroupBox16)
            Me.TabPage2.Controls.Add(Me.GroupBox15)
            Me.TabPage2.Controls.Add(Me.tbItmInGameNAme)
            Me.TabPage2.Controls.Add(Me.GroupBox14)
            Me.TabPage2.Controls.Add(Me.GroupBox13)
            Me.TabPage2.Controls.Add(Me.Label46)
            Me.TabPage2.Controls.Add(Me.GroupBox12)
            Me.TabPage2.Controls.Add(Me.GroupBox11)
            Me.TabPage2.Controls.Add(Me.GroupBox10)
            Me.TabPage2.Controls.Add(Me.GroupBox9)
            Me.TabPage2.Controls.Add(Me.GroupBox8)
            Me.TabPage2.Controls.Add(Me.GroupBox6)
            point = New Point(4, &H16)
            Me.TabPage2.Location = point
            Me.TabPage2.Name = "TabPage2"
            padding = New Padding(3)
            Me.TabPage2.Padding = padding
            size = New Size(&H410, 660)
            Me.TabPage2.Size = size
            Me.TabPage2.TabIndex = 1
            Me.TabPage2.Text = "Items"
            Me.TabPage2.UseVisualStyleBackColor = True
            point = New Point(390, &H1B)
            Me.cmdItemRealName.Location = point
            Me.cmdItemRealName.Name = "cmdItemRealName"
            size = New Size(&H4B, &H17)
            Me.cmdItemRealName.Size = size
            Me.cmdItemRealName.TabIndex = &HAC
            Me.cmdItemRealName.Text = "Edit name"
            Me.cmdItemRealName.UseVisualStyleBackColor = True
            point = New Point(&H57, 7)
            Me.cmdItemSave.Location = point
            Me.cmdItemSave.Name = "cmdItemSave"
            size = New Size(&H4B, &H17)
            Me.cmdItemSave.Size = size
            Me.cmdItemSave.TabIndex = &HAB
            Me.cmdItemSave.Text = "Save"
            Me.cmdItemSave.UseVisualStyleBackColor = True
            Me.GroupBox20.Controls.Add(Me.cbItemMo)
            Me.GroupBox20.Controls.Add(Me.lbItemMo)
            point = New Point(&H326, 7)
            Me.GroupBox20.Location = point
            Me.GroupBox20.Name = "GroupBox20"
            size = New Size(&HD3, &H20B)
            Me.GroupBox20.Size = size
            Me.GroupBox20.TabIndex = 170
            Me.GroupBox20.TabStop = False
            Me.GroupBox20.Text = "Can drop by:"
            Me.cbItemMo.AutoSize = True
            Me.cbItemMo.Checked = MySettings.Default.FindMonsters
            Me.cbItemMo.DataBindings.Add(New Binding("Checked", MySettings.Default, "FindMonsters", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(8, &H13)
            Me.cbItemMo.Location = point
            Me.cbItemMo.Name = "cbItemMo"
            size = New Size(&H3B, &H11)
            Me.cbItemMo.Size = size
            Me.cbItemMo.TabIndex = 1
            Me.cbItemMo.Text = "Enable"
            Me.cbItemMo.UseVisualStyleBackColor = True
            Me.lbItemMo.ContextMenuStrip = Me.cmItemsMonster
            Me.lbItemMo.FormattingEnabled = True
            point = New Point(8, &H2A)
            Me.lbItemMo.Location = point
            Me.lbItemMo.Name = "lbItemMo"
            Me.lbItemMo.SelectionMode = SelectionMode.MultiExtended
            size = New Size(&HC7, &H1D8)
            Me.lbItemMo.Size = size
            Me.lbItemMo.TabIndex = 0
            Me.cmItemsMonster.Items.AddRange(New ToolStripItem() { Me.RemoveItemToolStripMenuItem, Me.EditMonsterToolStripMenuItem })
            Me.cmItemsMonster.Name = "ContextMenuStrip1"
            size = New Size(&HAE, &H30)
            Me.cmItemsMonster.Size = size
            Me.RemoveItemToolStripMenuItem.Name = "RemoveItemToolStripMenuItem"
            size = New Size(&HAD, &H16)
            Me.RemoveItemToolStripMenuItem.Size = size
            Me.RemoveItemToolStripMenuItem.Text = "Remove Item"
            Me.EditMonsterToolStripMenuItem.Name = "EditMonsterToolStripMenuItem"
            size = New Size(&HAD, &H16)
            Me.EditMonsterToolStripMenuItem.Size = size
            Me.EditMonsterToolStripMenuItem.Text = "Go to Monster Editor"
            Me.cbItemSelector.ContextMenuStrip = Me.CMFilterSaver
            Me.cbItemSelector.FormattingEnabled = True
            point = New Point(7, &H25)
            Me.cbItemSelector.Location = point
            Me.cbItemSelector.Name = "cbItemSelector"
            size = New Size(&HB0, &H15)
            Me.cbItemSelector.Size = size
            Me.cbItemSelector.TabIndex = &HA9
            Me.CMFilterSaver.Items.AddRange(New ToolStripItem() { Me.SaveToolStripMenuItem, Me.LoadFilterToolStripMenuItem, Me.AddToListToolStripMenuItem, Me.RemoveFromListToolStripMenuItem })
            Me.CMFilterSaver.Name = "CMFilterSaver"
            size = New Size(&H9B, &H5C)
            Me.CMFilterSaver.Size = size
            Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.SaveToolStripMenuItem.Size = size
            Me.SaveToolStripMenuItem.Text = "Save config"
            Me.LoadFilterToolStripMenuItem.Name = "LoadFilterToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.LoadFilterToolStripMenuItem.Size = size
            Me.LoadFilterToolStripMenuItem.Text = "Load config"
            Me.AddToListToolStripMenuItem.Name = "AddToListToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.AddToListToolStripMenuItem.Size = size
            Me.AddToListToolStripMenuItem.Text = "Add to list"
            Me.RemoveFromListToolStripMenuItem.Name = "RemoveFromListToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.RemoveFromListToolStripMenuItem.Size = size
            Me.RemoveFromListToolStripMenuItem.Text = "Remove from list"
            point = New Point(6, 7)
            Me.cmdReload1.Location = point
            Me.cmdReload1.Name = "cmdReload1"
            size = New Size(&H4B, &H17)
            Me.cmdReload1.Size = size
            Me.cmdReload1.TabIndex = &HA8
            Me.cmdReload1.Text = "Reload"
            Me.cmdReload1.UseVisualStyleBackColor = True
            Me.GroupBox19.Controls.Add(Me.Label86)
            Me.GroupBox19.Controls.Add(Me.tbItmLevel)
            Me.GroupBox19.Controls.Add(Me.tbItmStr)
            Me.GroupBox19.Controls.Add(Me.Label85)
            Me.GroupBox19.Controls.Add(Me.tbItmSpirit)
            Me.GroupBox19.Controls.Add(Me.Label84)
            Me.GroupBox19.Controls.Add(Me.tbItmTalent)
            Me.GroupBox19.Controls.Add(Me.Label83)
            Me.GroupBox19.Controls.Add(Me.tbItmAgi)
            Me.GroupBox19.Controls.Add(Me.Label82)
            Me.GroupBox19.Controls.Add(Me.tbItmreqHP)
            Me.GroupBox19.Controls.Add(Me.Label81)
            point = New Point(&H25D, &H15B)
            Me.GroupBox19.Location = point
            Me.GroupBox19.Name = "GroupBox19"
            size = New Size(&HC3, &HB7)
            Me.GroupBox19.Size = size
            Me.GroupBox19.TabIndex = &HA7
            Me.GroupBox19.TabStop = False
            Me.GroupBox19.Text = "Requirements"
            Me.Label86.AutoSize = True
            point = New Point(6, &H11)
            Me.Label86.Location = point
            Me.Label86.Name = "Label86"
            size = New Size(&H24, 13)
            Me.Label86.Size = size
            Me.Label86.TabIndex = &H88
            Me.Label86.Text = "Level:"
            point = New Point(&H63, 14)
            Me.tbItmLevel.Location = point
            Me.tbItmLevel.Name = "tbItmLevel"
            size = New Size(&H4B, 20)
            Me.tbItmLevel.Size = size
            Me.tbItmLevel.TabIndex = &H87
            point = New Point(&H63, 40)
            Me.tbItmStr.Location = point
            Me.tbItmStr.Name = "tbItmStr"
            size = New Size(&H4B, 20)
            Me.tbItmStr.Size = size
            Me.tbItmStr.TabIndex = &H89
            Me.Label85.AutoSize = True
            point = New Point(6, &H2B)
            Me.Label85.Location = point
            Me.Label85.Name = "Label85"
            size = New Size(&H2F, 13)
            Me.Label85.Size = size
            Me.Label85.TabIndex = &H8A
            Me.Label85.Text = "Strengh:"
            point = New Point(&H63, &H42)
            Me.tbItmSpirit.Location = point
            Me.tbItmSpirit.Name = "tbItmSpirit"
            size = New Size(&H4B, 20)
            Me.tbItmSpirit.Size = size
            Me.tbItmSpirit.TabIndex = &H8B
            Me.Label84.AutoSize = True
            point = New Point(6, &H45)
            Me.Label84.Location = point
            Me.Label84.Name = "Label84"
            size = New Size(&H21, 13)
            Me.Label84.Size = size
            Me.Label84.TabIndex = 140
            Me.Label84.Text = "Spirit:"
            point = New Point(&H63, &H5C)
            Me.tbItmTalent.Location = point
            Me.tbItmTalent.Name = "tbItmTalent"
            size = New Size(&H4B, 20)
            Me.tbItmTalent.Size = size
            Me.tbItmTalent.TabIndex = &H8D
            Me.Label83.AutoSize = True
            point = New Point(6, &H5F)
            Me.Label83.Location = point
            Me.Label83.Name = "Label83"
            size = New Size(40, 13)
            Me.Label83.Size = size
            Me.Label83.TabIndex = &H8E
            Me.Label83.Text = "Talent:"
            point = New Point(&H63, &H76)
            Me.tbItmAgi.Location = point
            Me.tbItmAgi.Name = "tbItmAgi"
            size = New Size(&H4B, 20)
            Me.tbItmAgi.Size = size
            Me.tbItmAgi.TabIndex = &H8F
            Me.Label82.AutoSize = True
            point = New Point(6, &H79)
            Me.Label82.Location = point
            Me.Label82.Name = "Label82"
            size = New Size(&H25, 13)
            Me.Label82.Size = size
            Me.Label82.TabIndex = &H90
            Me.Label82.Text = "Agility:"
            point = New Point(&H63, &H90)
            Me.tbItmreqHP.Location = point
            Me.tbItmreqHP.Name = "tbItmreqHP"
            size = New Size(&H4B, 20)
            Me.tbItmreqHP.Size = size
            Me.tbItmreqHP.TabIndex = &H91
            Me.Label81.AutoSize = True
            point = New Point(6, &H93)
            Me.Label81.Location = point
            Me.Label81.Name = "Label81"
            size = New Size(&H29, 13)
            Me.Label81.Size = size
            Me.Label81.TabIndex = &H92
            Me.Label81.Text = "Health:"
            Me.GroupBox18.Controls.Add(Me.Label93)
            Me.GroupBox18.Controls.Add(Me.tbItmHPRegen)
            Me.GroupBox18.Controls.Add(Me.tbItmMPRegen)
            Me.GroupBox18.Controls.Add(Me.Label92)
            Me.GroupBox18.Controls.Add(Me.tbItmSTMRegen)
            Me.GroupBox18.Controls.Add(Me.Label91)
            Me.GroupBox18.Controls.Add(Me.tbItmHPAdd)
            Me.GroupBox18.Controls.Add(Me.Label90)
            Me.GroupBox18.Controls.Add(Me.tbItmMPAdd)
            Me.GroupBox18.Controls.Add(Me.Label89)
            Me.GroupBox18.Controls.Add(Me.tbItmSTMAdd)
            Me.GroupBox18.Controls.Add(Me.Label88)
            Me.GroupBox18.Controls.Add(Me.tbItmAPT)
            Me.GroupBox18.Controls.Add(Me.Label87)
            point = New Point(&H25D, &H80)
            Me.GroupBox18.Location = point
            Me.GroupBox18.Name = "GroupBox18"
            size = New Size(&HC2, &HD3)
            Me.GroupBox18.Size = size
            Me.GroupBox18.TabIndex = &HA6
            Me.GroupBox18.TabStop = False
            Me.GroupBox18.Text = "Accessories"
            Me.Label93.AutoSize = True
            point = New Point(6, &H10)
            Me.Label93.Location = point
            Me.Label93.Name = "Label93"
            size = New Size(60, 13)
            Me.Label93.Size = size
            Me.Label93.TabIndex = &H7A
            Me.Label93.Text = "HP Regen:"
            point = New Point(&H63, 13)
            Me.tbItmHPRegen.Location = point
            Me.tbItmHPRegen.Name = "tbItmHPRegen"
            size = New Size(&H4B, 20)
            Me.tbItmHPRegen.Size = size
            Me.tbItmHPRegen.TabIndex = &H79
            point = New Point(&H63, &H27)
            Me.tbItmMPRegen.Location = point
            Me.tbItmMPRegen.Name = "tbItmMPRegen"
            size = New Size(&H4B, 20)
            Me.tbItmMPRegen.Size = size
            Me.tbItmMPRegen.TabIndex = &H7B
            Me.Label92.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label92.Location = point
            Me.Label92.Name = "Label92"
            size = New Size(&H3D, 13)
            Me.Label92.Size = size
            Me.Label92.TabIndex = &H7C
            Me.Label92.Text = "MP Regen:"
            point = New Point(&H63, &H41)
            Me.tbItmSTMRegen.Location = point
            Me.tbItmSTMRegen.Name = "tbItmSTMRegen"
            size = New Size(&H4B, 20)
            Me.tbItmSTMRegen.Size = size
            Me.tbItmSTMRegen.TabIndex = &H7D
            Me.Label91.AutoSize = True
            point = New Point(6, &H44)
            Me.Label91.Location = point
            Me.Label91.Name = "Label91"
            size = New Size(&H44, 13)
            Me.Label91.Size = size
            Me.Label91.TabIndex = &H7E
            Me.Label91.Text = "STM Regen:"
            point = New Point(&H63, &H5B)
            Me.tbItmHPAdd.Location = point
            Me.tbItmHPAdd.Name = "tbItmHPAdd"
            size = New Size(&H4B, 20)
            Me.tbItmHPAdd.Size = size
            Me.tbItmHPAdd.TabIndex = &H7F
            Me.Label90.AutoSize = True
            point = New Point(6, &H5E)
            Me.Label90.Location = point
            Me.Label90.Name = "Label90"
            size = New Size(&H2F, 13)
            Me.Label90.Size = size
            Me.Label90.TabIndex = &H80
            Me.Label90.Text = "Add HP:"
            point = New Point(&H63, &H75)
            Me.tbItmMPAdd.Location = point
            Me.tbItmMPAdd.Name = "tbItmMPAdd"
            size = New Size(&H4B, 20)
            Me.tbItmMPAdd.Size = size
            Me.tbItmMPAdd.TabIndex = &H81
            Me.Label89.AutoSize = True
            point = New Point(6, 120)
            Me.Label89.Location = point
            Me.Label89.Name = "Label89"
            size = New Size(&H30, 13)
            Me.Label89.Size = size
            Me.Label89.TabIndex = 130
            Me.Label89.Text = "Add MP:"
            point = New Point(&H63, &H8F)
            Me.tbItmSTMAdd.Location = point
            Me.tbItmSTMAdd.Name = "tbItmSTMAdd"
            size = New Size(&H4B, 20)
            Me.tbItmSTMAdd.Size = size
            Me.tbItmSTMAdd.TabIndex = &H83
            Me.Label88.AutoSize = True
            point = New Point(6, &H92)
            Me.Label88.Location = point
            Me.Label88.Name = "Label88"
            size = New Size(&H37, 13)
            Me.Label88.Size = size
            Me.Label88.TabIndex = &H84
            Me.Label88.Text = "Add STM:"
            point = New Point(&H63, &HA9)
            Me.tbItmAPT.Location = point
            Me.tbItmAPT.Name = "tbItmAPT"
            size = New Size(&H4B, 20)
            Me.tbItmAPT.Size = size
            Me.tbItmAPT.TabIndex = &H85
            Me.Label87.AutoSize = True
            point = New Point(6, &HAC)
            Me.Label87.Location = point
            Me.Label87.Name = "Label87"
            size = New Size(&H45, 13)
            Me.Label87.Size = size
            Me.Label87.TabIndex = &H86
            Me.Label87.Text = "Magical Skill:"
            Me.GroupBox17.Controls.Add(Me.Label94)
            Me.GroupBox17.Controls.Add(Me.tbItmRun)
            point = New Point(&H25D, 60)
            Me.GroupBox17.Location = point
            Me.GroupBox17.Name = "GroupBox17"
            size = New Size(&HC2, &H3E)
            Me.GroupBox17.Size = size
            Me.GroupBox17.TabIndex = &HA5
            Me.GroupBox17.TabStop = False
            Me.GroupBox17.Text = "Run Speed"
            Me.Label94.AutoSize = True
            point = New Point(6, &H17)
            Me.Label94.Location = point
            Me.Label94.Name = "Label94"
            size = New Size(&H40, 13)
            Me.Label94.Size = size
            Me.Label94.TabIndex = 120
            Me.Label94.Text = "Run Speed:"
            point = New Point(&H63, 20)
            Me.tbItmRun.Location = point
            Me.tbItmRun.Name = "tbItmRun"
            size = New Size(&H4B, 20)
            Me.tbItmRun.Size = size
            Me.tbItmRun.TabIndex = &H77
            Me.GroupBox16.Controls.Add(Me.Label72)
            Me.GroupBox16.Controls.Add(Me.tbItmSPatkSpd)
            Me.GroupBox16.Controls.Add(Me.tbItmSPCrt)
            Me.GroupBox16.Controls.Add(Me.Label71)
            Me.GroupBox16.Controls.Add(Me.tbItmSPLvl)
            Me.GroupBox16.Controls.Add(Me.Label70)
            Me.GroupBox16.Controls.Add(Me.tbItmSPRtg)
            Me.GroupBox16.Controls.Add(Me.Label69)
            Me.GroupBox16.Controls.Add(Me.tbItmSPabs)
            Me.GroupBox16.Controls.Add(Me.Label68)
            Me.GroupBox16.Controls.Add(Me.tbItmSPdef)
            Me.GroupBox16.Controls.Add(Me.Label67)
            Me.GroupBox16.Controls.Add(Me.tbItmSPblk)
            Me.GroupBox16.Controls.Add(Me.Label74)
            Me.GroupBox16.Controls.Add(Me.tbItmSPhp)
            Me.GroupBox16.Controls.Add(Me.Label76)
            Me.GroupBox16.Controls.Add(Me.tbItmSPMp)
            Me.GroupBox16.Controls.Add(Me.Label75)
            Me.GroupBox16.Controls.Add(Me.tbItmSPRun)
            Me.GroupBox16.Controls.Add(Me.Label77)
            Me.GroupBox16.Controls.Add(Me.tbItmSPRange)
            Me.GroupBox16.Controls.Add(Me.Label78)
            point = New Point(&H18D, &H159)
            Me.GroupBox16.Location = point
            Me.GroupBox16.Name = "GroupBox16"
            size = New Size(&HC2, &H135)
            Me.GroupBox16.Size = size
            Me.GroupBox16.TabIndex = &HA4
            Me.GroupBox16.TabStop = False
            Me.GroupBox16.Text = "Spec Stats"
            Me.Label72.AutoSize = True
            point = New Point(6, &H10)
            Me.Label72.Location = point
            Me.Label72.Name = "Label72"
            size = New Size(&H4B, 13)
            Me.Label72.Size = size
            Me.Label72.TabIndex = &H62
            Me.Label72.Text = "Attack Speed:"
            point = New Point(&H63, 13)
            Me.tbItmSPatkSpd.Location = point
            Me.tbItmSPatkSpd.Name = "tbItmSPatkSpd"
            size = New Size(&H4B, 20)
            Me.tbItmSPatkSpd.Size = size
            Me.tbItmSPatkSpd.TabIndex = &H61
            point = New Point(&H63, &H27)
            Me.tbItmSPCrt.Location = point
            Me.tbItmSPCrt.Name = "tbItmSPCrt"
            size = New Size(&H4B, 20)
            Me.tbItmSPCrt.Size = size
            Me.tbItmSPCrt.TabIndex = &H63
            Me.Label71.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label71.Location = point
            Me.Label71.Name = "Label71"
            size = New Size(&H4B, 13)
            Me.Label71.Size = size
            Me.Label71.TabIndex = 100
            Me.Label71.Text = "Attack Critical:"
            point = New Point(&H63, &H41)
            Me.tbItmSPLvl.Location = point
            Me.tbItmSPLvl.Name = "tbItmSPLvl"
            size = New Size(&H4B, 20)
            Me.tbItmSPLvl.Size = size
            Me.tbItmSPLvl.TabIndex = &H65
            Me.Label70.AutoSize = True
            point = New Point(6, &H44)
            Me.Label70.Location = point
            Me.Label70.Name = "Label70"
            size = New Size(&H53, 13)
            Me.Label70.Size = size
            Me.Label70.TabIndex = &H66
            Me.Label70.Text = "Atk. Power LV/:"
            point = New Point(&H63, &H5B)
            Me.tbItmSPRtg.Location = point
            Me.tbItmSPRtg.Name = "tbItmSPRtg"
            size = New Size(&H4B, 20)
            Me.tbItmSPRtg.Size = size
            Me.tbItmSPRtg.TabIndex = &H67
            Me.Label69.AutoSize = True
            point = New Point(6, &H5E)
            Me.Label69.Location = point
            Me.Label69.Name = "Label69"
            size = New Size(&H54, 13)
            Me.Label69.Size = size
            Me.Label69.TabIndex = &H68
            Me.Label69.Text = "Atk. Rating LV/:"
            point = New Point(&H63, &H75)
            Me.tbItmSPabs.Location = point
            Me.tbItmSPabs.Name = "tbItmSPabs"
            size = New Size(&H4B, 20)
            Me.tbItmSPabs.Size = size
            Me.tbItmSPabs.TabIndex = &H69
            Me.Label68.AutoSize = True
            point = New Point(6, 120)
            Me.Label68.Location = point
            Me.Label68.Name = "Label68"
            size = New Size(&H2B, 13)
            Me.Label68.Size = size
            Me.Label68.TabIndex = &H6A
            Me.Label68.Text = "Absorb:"
            point = New Point(&H63, &H8F)
            Me.tbItmSPdef.Location = point
            Me.tbItmSPdef.Name = "tbItmSPdef"
            size = New Size(&H4B, 20)
            Me.tbItmSPdef.Size = size
            Me.tbItmSPdef.TabIndex = &H6B
            Me.Label67.AutoSize = True
            point = New Point(6, &H92)
            Me.Label67.Location = point
            Me.Label67.Name = "Label67"
            size = New Size(&H3A, 13)
            Me.Label67.Size = size
            Me.Label67.TabIndex = &H6C
            Me.Label67.Text = "Defensive:"
            point = New Point(&H63, &HA9)
            Me.tbItmSPblk.Location = point
            Me.tbItmSPblk.Name = "tbItmSPblk"
            size = New Size(&H4B, 20)
            Me.tbItmSPblk.Size = size
            Me.tbItmSPblk.TabIndex = &H6D
            Me.Label74.AutoSize = True
            point = New Point(6, &HAC)
            Me.Label74.Location = point
            Me.Label74.Name = "Label74"
            size = New Size(&H25, 13)
            Me.Label74.Size = size
            Me.Label74.TabIndex = 110
            Me.Label74.Text = "Block:"
            point = New Point(&H63, &HC3)
            Me.tbItmSPhp.Location = point
            Me.tbItmSPhp.Name = "tbItmSPhp"
            size = New Size(&H4B, 20)
            Me.tbItmSPhp.Size = size
            Me.tbItmSPhp.TabIndex = &H6F
            Me.Label76.AutoSize = True
            point = New Point(6, &HC6)
            Me.Label76.Location = point
            Me.Label76.Name = "Label76"
            size = New Size(&H45, 13)
            Me.Label76.Size = size
            Me.Label76.TabIndex = &H70
            Me.Label76.Text = "HP recovery:"
            point = New Point(&H63, &HDD)
            Me.tbItmSPMp.Location = point
            Me.tbItmSPMp.Name = "tbItmSPMp"
            size = New Size(&H4B, 20)
            Me.tbItmSPMp.Size = size
            Me.tbItmSPMp.TabIndex = &H71
            Me.Label75.AutoSize = True
            point = New Point(6, &HE0)
            Me.Label75.Location = point
            Me.Label75.Name = "Label75"
            size = New Size(70, 13)
            Me.Label75.Size = size
            Me.Label75.TabIndex = &H72
            Me.Label75.Text = "MP recovery:"
            point = New Point(&H63, &HF7)
            Me.tbItmSPRun.Location = point
            Me.tbItmSPRun.Name = "tbItmSPRun"
            size = New Size(&H4B, 20)
            Me.tbItmSPRun.Size = size
            Me.tbItmSPRun.TabIndex = &H73
            Me.Label77.AutoSize = True
            point = New Point(6, 250)
            Me.Label77.Location = point
            Me.Label77.Name = "Label77"
            size = New Size(&H40, 13)
            Me.Label77.Size = size
            Me.Label77.TabIndex = &H74
            Me.Label77.Text = "Run Speed:"
            point = New Point(&H63, &H111)
            Me.tbItmSPRange.Location = point
            Me.tbItmSPRange.Name = "tbItmSPRange"
            size = New Size(&H4B, 20)
            Me.tbItmSPRange.Size = size
            Me.tbItmSPRange.TabIndex = &H75
            Me.Label78.AutoSize = True
            point = New Point(6, &H114)
            Me.Label78.Location = point
            Me.Label78.Name = "Label78"
            size = New Size(&H2A, 13)
            Me.Label78.Size = size
            Me.Label78.TabIndex = &H76
            Me.Label78.Text = "Range:"
            Me.GroupBox15.Controls.Add(Me.Label63)
            Me.GroupBox15.Controls.Add(Me.tbItmAbs)
            Me.GroupBox15.Controls.Add(Me.tbItmdef)
            Me.GroupBox15.Controls.Add(Me.Label66)
            Me.GroupBox15.Controls.Add(Me.tbItmBlk)
            Me.GroupBox15.Controls.Add(Me.Label73)
            point = New Point(&H18D, &HEE)
            Me.GroupBox15.Location = point
            Me.GroupBox15.Name = "GroupBox15"
            size = New Size(&HC3, &H65)
            Me.GroupBox15.Size = size
            Me.GroupBox15.TabIndex = &HA3
            Me.GroupBox15.TabStop = False
            Me.GroupBox15.Text = "Item Defence"
            Me.Label63.AutoSize = True
            point = New Point(6, &H10)
            Me.Label63.Location = point
            Me.Label63.Name = "Label63"
            size = New Size(&H2B, 13)
            Me.Label63.Size = size
            Me.Label63.TabIndex = &H5C
            Me.Label63.Text = "Absorb:"
            point = New Point(&H63, 13)
            Me.tbItmAbs.Location = point
            Me.tbItmAbs.Name = "tbItmAbs"
            size = New Size(&H4B, 20)
            Me.tbItmAbs.Size = size
            Me.tbItmAbs.TabIndex = &H5B
            point = New Point(&H63, &H27)
            Me.tbItmdef.Location = point
            Me.tbItmdef.Name = "tbItmdef"
            size = New Size(&H4B, 20)
            Me.tbItmdef.Size = size
            Me.tbItmdef.TabIndex = &H5D
            Me.Label66.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label66.Location = point
            Me.Label66.Name = "Label66"
            size = New Size(&H3A, 13)
            Me.Label66.Size = size
            Me.Label66.TabIndex = &H5E
            Me.Label66.Text = "Defensive:"
            point = New Point(&H63, &H41)
            Me.tbItmBlk.Location = point
            Me.tbItmBlk.Name = "tbItmBlk"
            size = New Size(&H4B, 20)
            Me.tbItmBlk.Size = size
            Me.tbItmBlk.TabIndex = &H5F
            Me.Label73.AutoSize = True
            point = New Point(6, &H44)
            Me.Label73.Location = point
            Me.Label73.Name = "Label73"
            size = New Size(&H25, 13)
            Me.Label73.Size = size
            Me.Label73.TabIndex = &H60
            Me.Label73.Text = "Block:"
            point = New Point(&H117, &H22)
            Me.tbItmInGameNAme.Location = point
            Me.tbItmInGameNAme.Name = "tbItmInGameNAme"
            size = New Size(&H69, 20)
            Me.tbItmInGameNAme.Size = size
            Me.tbItmInGameNAme.TabIndex = &H33
            Me.GroupBox14.Controls.Add(Me.Label60)
            Me.GroupBox14.Controls.Add(Me.tbItmAtkPow)
            Me.GroupBox14.Controls.Add(Me.tbItmRange)
            Me.GroupBox14.Controls.Add(Me.Label61)
            Me.GroupBox14.Controls.Add(Me.tbItmSpeed)
            Me.GroupBox14.Controls.Add(Me.Label62)
            Me.GroupBox14.Controls.Add(Me.tbItmAtkRtg)
            Me.GroupBox14.Controls.Add(Me.Label65)
            Me.GroupBox14.Controls.Add(Me.tbItmCrtRtg)
            Me.GroupBox14.Controls.Add(Me.Label64)
            point = New Point(&H18D, 60)
            Me.GroupBox14.Location = point
            Me.GroupBox14.Name = "GroupBox14"
            size = New Size(&HC2, &HA6)
            Me.GroupBox14.Size = size
            Me.GroupBox14.TabIndex = &HA2
            Me.GroupBox14.TabStop = False
            Me.GroupBox14.Text = "Item attack stats"
            Me.Label60.AutoSize = True
            point = New Point(6, &H17)
            Me.Label60.Location = point
            Me.Label60.Name = "Label60"
            size = New Size(40, 13)
            Me.Label60.Size = size
            Me.Label60.TabIndex = &H52
            Me.Label60.Text = "Power:"
            point = New Point(&H63, 20)
            Me.tbItmAtkPow.Location = point
            Me.tbItmAtkPow.Name = "tbItmAtkPow"
            size = New Size(&H4B, 20)
            Me.tbItmAtkPow.Size = size
            Me.tbItmAtkPow.TabIndex = &H51
            point = New Point(&H63, &H2E)
            Me.tbItmRange.Location = point
            Me.tbItmRange.Name = "tbItmRange"
            size = New Size(&H4B, 20)
            Me.tbItmRange.Size = size
            Me.tbItmRange.TabIndex = &H53
            Me.Label61.AutoSize = True
            point = New Point(6, &H31)
            Me.Label61.Location = point
            Me.Label61.Name = "Label61"
            size = New Size(&H2A, 13)
            Me.Label61.Size = size
            Me.Label61.TabIndex = &H54
            Me.Label61.Text = "Range:"
            point = New Point(&H63, &H48)
            Me.tbItmSpeed.Location = point
            Me.tbItmSpeed.Name = "tbItmSpeed"
            size = New Size(&H4B, 20)
            Me.tbItmSpeed.Size = size
            Me.tbItmSpeed.TabIndex = &H55
            Me.Label62.AutoSize = True
            point = New Point(6, &H4B)
            Me.Label62.Location = point
            Me.Label62.Name = "Label62"
            size = New Size(&H29, 13)
            Me.Label62.Size = size
            Me.Label62.TabIndex = &H56
            Me.Label62.Text = "Speed:"
            point = New Point(&H63, &H62)
            Me.tbItmAtkRtg.Location = point
            Me.tbItmAtkRtg.Name = "tbItmAtkRtg"
            size = New Size(&H4B, 20)
            Me.tbItmAtkRtg.Size = size
            Me.tbItmAtkRtg.TabIndex = &H57
            Me.Label65.AutoSize = True
            point = New Point(6, &H65)
            Me.Label65.Location = point
            Me.Label65.Name = "Label65"
            size = New Size(&H4B, 13)
            Me.Label65.Size = size
            Me.Label65.TabIndex = &H58
            Me.Label65.Text = "Attack Rating:"
            point = New Point(&H63, &H7C)
            Me.tbItmCrtRtg.Location = point
            Me.tbItmCrtRtg.Name = "tbItmCrtRtg"
            size = New Size(&H4B, 20)
            Me.tbItmCrtRtg.Size = size
            Me.tbItmCrtRtg.TabIndex = &H59
            Me.Label64.AutoSize = True
            point = New Point(6, &H7F)
            Me.Label64.Location = point
            Me.Label64.Name = "Label64"
            size = New Size(&H4B, 13)
            Me.Label64.Size = size
            Me.Label64.TabIndex = 90
            Me.Label64.Text = "Critical Rating:"
            Me.GroupBox13.Controls.Add(Me.Label56)
            Me.GroupBox13.Controls.Add(Me.tbItmHPRec)
            Me.GroupBox13.Controls.Add(Me.tbItmManaRec)
            Me.GroupBox13.Controls.Add(Me.Label57)
            Me.GroupBox13.Controls.Add(Me.tbItmStmRec)
            Me.GroupBox13.Controls.Add(Me.Label58)
            Me.GroupBox13.Controls.Add(Me.tbItmPots)
            Me.GroupBox13.Controls.Add(Me.Label59)
            point = New Point(&HBF, &H20F)
            Me.GroupBox13.Location = point
            Me.GroupBox13.Name = "GroupBox13"
            size = New Size(&HC1, &H7F)
            Me.GroupBox13.Size = size
            Me.GroupBox13.TabIndex = &HA1
            Me.GroupBox13.TabStop = False
            Me.GroupBox13.Text = "Recovery and Potion"
            Me.Label56.AutoSize = True
            point = New Point(6, &H10)
            Me.Label56.Location = point
            Me.Label56.Name = "Label56"
            size = New Size(&H45, 13)
            Me.Label56.Size = size
            Me.Label56.TabIndex = &H4A
            Me.Label56.Text = "HP recovery:"
            point = New Point(&H63, 13)
            Me.tbItmHPRec.Location = point
            Me.tbItmHPRec.Name = "tbItmHPRec"
            size = New Size(&H4B, 20)
            Me.tbItmHPRec.Size = size
            Me.tbItmHPRec.TabIndex = &H49
            point = New Point(&H63, &H27)
            Me.tbItmManaRec.Location = point
            Me.tbItmManaRec.Name = "tbItmManaRec"
            size = New Size(&H4B, 20)
            Me.tbItmManaRec.Size = size
            Me.tbItmManaRec.TabIndex = &H4B
            Me.Label57.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label57.Location = point
            Me.Label57.Name = "Label57"
            size = New Size(70, 13)
            Me.Label57.Size = size
            Me.Label57.TabIndex = &H4C
            Me.Label57.Text = "MP recovery:"
            point = New Point(&H63, &H41)
            Me.tbItmStmRec.Location = point
            Me.tbItmStmRec.Name = "tbItmStmRec"
            size = New Size(&H4B, 20)
            Me.tbItmStmRec.Size = size
            Me.tbItmStmRec.TabIndex = &H4D
            Me.Label58.AutoSize = True
            point = New Point(6, &H44)
            Me.Label58.Location = point
            Me.Label58.Name = "Label58"
            size = New Size(&H4D, 13)
            Me.Label58.Size = size
            Me.Label58.TabIndex = &H4E
            Me.Label58.Text = "STM recovery:"
            point = New Point(&H63, &H5B)
            Me.tbItmPots.Location = point
            Me.tbItmPots.Name = "tbItmPots"
            size = New Size(&H4B, 20)
            Me.tbItmPots.Size = size
            Me.tbItmPots.TabIndex = &H4F
            Me.Label59.AutoSize = True
            point = New Point(6, &H5E)
            Me.Label59.Location = point
            Me.Label59.Name = "Label59"
            size = New Size(&H44, 13)
            Me.Label59.Size = size
            Me.Label59.TabIndex = 80
            Me.Label59.Text = "Potion Store:"
            Me.Label46.AutoSize = True
            point = New Point(&HBA, &H25)
            Me.Label46.Location = point
            Me.Label46.Name = "Label46"
            size = New Size(&H4F, 13)
            Me.Label46.Size = size
            Me.Label46.TabIndex = &H34
            Me.Label46.Text = "In game Name:"
            Me.GroupBox12.Controls.Add(Me.Label50)
            Me.GroupBox12.Controls.Add(Me.tbItmIntegrity)
            Me.GroupBox12.Controls.Add(Me.tbItmWeight)
            Me.GroupBox12.Controls.Add(Me.Label51)
            Me.GroupBox12.Controls.Add(Me.tbItmPrice)
            Me.GroupBox12.Controls.Add(Me.Label32)
            point = New Point(&HBF, &H102)
            Me.GroupBox12.Location = point
            Me.GroupBox12.Name = "GroupBox12"
            size = New Size(&HC0, &H65)
            Me.GroupBox12.Size = size
            Me.GroupBox12.TabIndex = 160
            Me.GroupBox12.TabStop = False
            Me.GroupBox12.Text = "General Information"
            Me.Label50.AutoSize = True
            point = New Point(6, &H10)
            Me.Label50.Location = point
            Me.Label50.Name = "Label50"
            size = New Size(&H2F, 13)
            Me.Label50.Size = size
            Me.Label50.TabIndex = 60
            Me.Label50.Text = "Integrity:"
            point = New Point(&H63, 13)
            Me.tbItmIntegrity.Location = point
            Me.tbItmIntegrity.Name = "tbItmIntegrity"
            size = New Size(&H4B, 20)
            Me.tbItmIntegrity.Size = size
            Me.tbItmIntegrity.TabIndex = &H3B
            point = New Point(&H63, &H27)
            Me.tbItmWeight.Location = point
            Me.tbItmWeight.Name = "tbItmWeight"
            size = New Size(&H4B, 20)
            Me.tbItmWeight.Size = size
            Me.tbItmWeight.TabIndex = &H3D
            Me.Label51.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label51.Location = point
            Me.Label51.Name = "Label51"
            size = New Size(&H2C, 13)
            Me.Label51.Size = size
            Me.Label51.TabIndex = &H3E
            Me.Label51.Text = "Weight:"
            point = New Point(&H63, &H41)
            Me.tbItmPrice.Location = point
            Me.tbItmPrice.Name = "tbItmPrice"
            size = New Size(&H4B, 20)
            Me.tbItmPrice.Size = size
            Me.tbItmPrice.TabIndex = &H3F
            Me.Label32.AutoSize = True
            point = New Point(6, &H44)
            Me.Label32.Location = point
            Me.Label32.Name = "Label32"
            size = New Size(&H22, 13)
            Me.Label32.Size = size
            Me.Label32.TabIndex = &H40
            Me.Label32.Text = "Price:"
            Me.GroupBox11.Controls.Add(Me.Label52)
            Me.GroupBox11.Controls.Add(Me.tbItmOrganic)
            Me.GroupBox11.Controls.Add(Me.tbItmFire)
            Me.GroupBox11.Controls.Add(Me.Label79)
            Me.GroupBox11.Controls.Add(Me.Label53)
            Me.GroupBox11.Controls.Add(Me.tbItmFrost)
            Me.GroupBox11.Controls.Add(Me.tbItmLighting)
            Me.GroupBox11.Controls.Add(Me.Label54)
            Me.GroupBox11.Controls.Add(Me.tbItmPoision)
            Me.GroupBox11.Controls.Add(Me.Label55)
            point = New Point(&HBF, &H16D)
            Me.GroupBox11.Location = point
            Me.GroupBox11.Name = "GroupBox11"
            size = New Size(&HC0, &H9C)
            Me.GroupBox11.Size = size
            Me.GroupBox11.TabIndex = &H9F
            Me.GroupBox11.TabStop = False
            Me.GroupBox11.Text = "Resistance"
            Me.Label52.AutoSize = True
            point = New Point(6, &H10)
            Me.Label52.Location = point
            Me.Label52.Name = "Label52"
            size = New Size(&H2F, 13)
            Me.Label52.Size = size
            Me.Label52.TabIndex = &H42
            Me.Label52.Text = "Organic:"
            point = New Point(&H63, 13)
            Me.tbItmOrganic.Location = point
            Me.tbItmOrganic.Name = "tbItmOrganic"
            size = New Size(&H4B, 20)
            Me.tbItmOrganic.Size = size
            Me.tbItmOrganic.TabIndex = &H41
            point = New Point(&H63, &H27)
            Me.tbItmFire.Location = point
            Me.tbItmFire.Name = "tbItmFire"
            size = New Size(&H4B, 20)
            Me.tbItmFire.Size = size
            Me.tbItmFire.TabIndex = &H43
            Me.Label79.AutoSize = True
            point = New Point(6, &H44)
            Me.Label79.Location = point
            Me.Label79.Name = "Label79"
            size = New Size(&H21, 13)
            Me.Label79.Size = size
            Me.Label79.TabIndex = &H94
            Me.Label79.Text = "Frost:"
            Me.Label53.AutoSize = True
            point = New Point(6, &H2A)
            Me.Label53.Location = point
            Me.Label53.Name = "Label53"
            size = New Size(&H1B, 13)
            Me.Label53.Size = size
            Me.Label53.TabIndex = &H44
            Me.Label53.Text = "Fire:"
            point = New Point(&H63, &H41)
            Me.tbItmFrost.Location = point
            Me.tbItmFrost.Name = "tbItmFrost"
            size = New Size(&H4B, 20)
            Me.tbItmFrost.Size = size
            Me.tbItmFrost.TabIndex = &H93
            point = New Point(&H63, &H5B)
            Me.tbItmLighting.Location = point
            Me.tbItmLighting.Name = "tbItmLighting"
            size = New Size(&H4B, 20)
            Me.tbItmLighting.Size = size
            Me.tbItmLighting.TabIndex = &H45
            Me.Label54.AutoSize = True
            point = New Point(6, &H5E)
            Me.Label54.Location = point
            Me.Label54.Name = "Label54"
            size = New Size(&H2F, 13)
            Me.Label54.Size = size
            Me.Label54.TabIndex = 70
            Me.Label54.Text = "Lighting:"
            point = New Point(&H63, &H75)
            Me.tbItmPoision.Location = point
            Me.tbItmPoision.Name = "tbItmPoision"
            size = New Size(&H4B, 20)
            Me.tbItmPoision.Size = size
            Me.tbItmPoision.TabIndex = &H47
            Me.Label55.AutoSize = True
            point = New Point(6, 120)
            Me.Label55.Location = point
            Me.Label55.Name = "Label55"
            size = New Size(&H2C, 13)
            Me.Label55.Size = size
            Me.Label55.TabIndex = &H48
            Me.Label55.Text = "Poision:"
            Me.GroupBox10.Controls.Add(Me.chSecMech)
            Me.GroupBox10.Controls.Add(Me.chSecMgs)
            Me.GroupBox10.Controls.Add(Me.chSecFighter)
            Me.GroupBox10.Controls.Add(Me.chSecPrs)
            Me.GroupBox10.Controls.Add(Me.chSecPike)
            Me.GroupBox10.Controls.Add(Me.chSecAta)
            Me.GroupBox10.Controls.Add(Me.chSecArcher)
            Me.GroupBox10.Controls.Add(Me.chSecKnight)
            point = New Point(&H32E, &H218)
            Me.GroupBox10.Location = point
            Me.GroupBox10.Name = "GroupBox10"
            size = New Size(&HCB, &H76)
            Me.GroupBox10.Size = size
            Me.GroupBox10.TabIndex = &H9E
            Me.GroupBox10.TabStop = False
            Me.GroupBox10.Text = "Addition Spec:"
            Me.chSecMech.AutoSize = True
            point = New Point(6, &H13)
            Me.chSecMech.Location = point
            Me.chSecMech.Name = "chSecMech"
            size = New Size(&H57, &H11)
            Me.chSecMech.Size = size
            Me.chSecMech.TabIndex = &H95
            Me.chSecMech.Text = "Mechanician"
            Me.chSecMech.UseVisualStyleBackColor = True
            Me.chSecMgs.AutoSize = True
            point = New Point(&H63, 90)
            Me.chSecMgs.Location = point
            Me.chSecMgs.Name = "chSecMgs"
            size = New Size(&H45, &H11)
            Me.chSecMgs.Size = size
            Me.chSecMgs.TabIndex = &H9C
            Me.chSecMgs.Text = "Magician"
            Me.chSecMgs.UseVisualStyleBackColor = True
            Me.chSecFighter.AutoSize = True
            point = New Point(6, &H2A)
            Me.chSecFighter.Location = point
            Me.chSecFighter.Name = "chSecFighter"
            size = New Size(&H3A, &H11)
            Me.chSecFighter.Size = size
            Me.chSecFighter.TabIndex = 150
            Me.chSecFighter.Text = "Fighter"
            Me.chSecFighter.UseVisualStyleBackColor = True
            Me.chSecPrs.AutoSize = True
            point = New Point(&H63, &H43)
            Me.chSecPrs.Location = point
            Me.chSecPrs.Name = "chSecPrs"
            size = New Size(&H44, &H11)
            Me.chSecPrs.Size = size
            Me.chSecPrs.TabIndex = &H9B
            Me.chSecPrs.Text = "Priestess"
            Me.chSecPrs.UseVisualStyleBackColor = True
            Me.chSecPike.AutoSize = True
            point = New Point(6, &H41)
            Me.chSecPike.Location = point
            Me.chSecPike.Name = "chSecPike"
            size = New Size(&H43, &H11)
            Me.chSecPike.Size = size
            Me.chSecPike.TabIndex = &H97
            Me.chSecPike.Text = "Pikeman"
            Me.chSecPike.UseVisualStyleBackColor = True
            Me.chSecAta.AutoSize = True
            point = New Point(&H63, &H2C)
            Me.chSecAta.Location = point
            Me.chSecAta.Name = "chSecAta"
            size = New Size(&H41, &H11)
            Me.chSecAta.Size = size
            Me.chSecAta.TabIndex = &H9A
            Me.chSecAta.Text = "Atalanta"
            Me.chSecAta.UseVisualStyleBackColor = True
            Me.chSecArcher.AutoSize = True
            point = New Point(6, &H58)
            Me.chSecArcher.Location = point
            Me.chSecArcher.Name = "chSecArcher"
            size = New Size(&H39, &H11)
            Me.chSecArcher.Size = size
            Me.chSecArcher.TabIndex = &H98
            Me.chSecArcher.Text = "Archer"
            Me.chSecArcher.UseVisualStyleBackColor = True
            Me.chSecKnight.AutoSize = True
            point = New Point(&H63, &H15)
            Me.chSecKnight.Location = point
            Me.chSecKnight.Name = "chSecKnight"
            size = New Size(&H38, &H11)
            Me.chSecKnight.Size = size
            Me.chSecKnight.TabIndex = &H99
            Me.chSecKnight.Text = "Knight"
            Me.chSecKnight.UseVisualStyleBackColor = True
            Me.GroupBox9.Controls.Add(Me.chPriMech)
            Me.GroupBox9.Controls.Add(Me.chPriMgs)
            Me.GroupBox9.Controls.Add(Me.chPriFighter)
            Me.GroupBox9.Controls.Add(Me.chPriPrs)
            Me.GroupBox9.Controls.Add(Me.chPriPike)
            Me.GroupBox9.Controls.Add(Me.chPriAta)
            Me.GroupBox9.Controls.Add(Me.chPriArcher)
            Me.GroupBox9.Controls.Add(Me.chPriKnight)
            point = New Point(&H25D, &H218)
            Me.GroupBox9.Location = point
            Me.GroupBox9.Name = "GroupBox9"
            size = New Size(&HCB, &H76)
            Me.GroupBox9.Size = size
            Me.GroupBox9.TabIndex = &H9D
            Me.GroupBox9.TabStop = False
            Me.GroupBox9.Text = "Primary Spec:"
            Me.chPriMech.AutoSize = True
            point = New Point(6, &H13)
            Me.chPriMech.Location = point
            Me.chPriMech.Name = "chPriMech"
            size = New Size(&H57, &H11)
            Me.chPriMech.Size = size
            Me.chPriMech.TabIndex = &H95
            Me.chPriMech.Text = "Mechanician"
            Me.chPriMech.UseVisualStyleBackColor = True
            Me.chPriMgs.AutoSize = True
            point = New Point(&H63, 90)
            Me.chPriMgs.Location = point
            Me.chPriMgs.Name = "chPriMgs"
            size = New Size(&H45, &H11)
            Me.chPriMgs.Size = size
            Me.chPriMgs.TabIndex = &H9C
            Me.chPriMgs.Text = "Magician"
            Me.chPriMgs.UseVisualStyleBackColor = True
            Me.chPriFighter.AutoSize = True
            point = New Point(6, &H2A)
            Me.chPriFighter.Location = point
            Me.chPriFighter.Name = "chPriFighter"
            size = New Size(&H3A, &H11)
            Me.chPriFighter.Size = size
            Me.chPriFighter.TabIndex = 150
            Me.chPriFighter.Text = "Fighter"
            Me.chPriFighter.UseVisualStyleBackColor = True
            Me.chPriPrs.AutoSize = True
            point = New Point(&H63, &H43)
            Me.chPriPrs.Location = point
            Me.chPriPrs.Name = "chPriPrs"
            size = New Size(&H44, &H11)
            Me.chPriPrs.Size = size
            Me.chPriPrs.TabIndex = &H9B
            Me.chPriPrs.Text = "Priestess"
            Me.chPriPrs.UseVisualStyleBackColor = True
            Me.chPriPike.AutoSize = True
            point = New Point(6, &H41)
            Me.chPriPike.Location = point
            Me.chPriPike.Name = "chPriPike"
            size = New Size(&H43, &H11)
            Me.chPriPike.Size = size
            Me.chPriPike.TabIndex = &H97
            Me.chPriPike.Text = "Pikeman"
            Me.chPriPike.UseVisualStyleBackColor = True
            Me.chPriAta.AutoSize = True
            point = New Point(&H63, &H2C)
            Me.chPriAta.Location = point
            Me.chPriAta.Name = "chPriAta"
            size = New Size(&H41, &H11)
            Me.chPriAta.Size = size
            Me.chPriAta.TabIndex = &H9A
            Me.chPriAta.Text = "Atalanta"
            Me.chPriAta.UseVisualStyleBackColor = True
            Me.chPriArcher.AutoSize = True
            point = New Point(6, &H58)
            Me.chPriArcher.Location = point
            Me.chPriArcher.Name = "chPriArcher"
            size = New Size(&H39, &H11)
            Me.chPriArcher.Size = size
            Me.chPriArcher.TabIndex = &H98
            Me.chPriArcher.Text = "Archer"
            Me.chPriArcher.UseVisualStyleBackColor = True
            Me.chPriKnight.AutoSize = True
            point = New Point(&H63, &H15)
            Me.chPriKnight.Location = point
            Me.chPriKnight.Name = "chPriKnight"
            size = New Size(&H38, &H11)
            Me.chPriKnight.Size = size
            Me.chPriKnight.TabIndex = &H99
            Me.chPriKnight.Text = "Knight"
            Me.chPriKnight.UseVisualStyleBackColor = True
            Me.GroupBox8.Controls.Add(Me.Label44)
            Me.GroupBox8.Controls.Add(Me.Label49)
            Me.GroupBox8.Controls.Add(Me.tbItmJpName)
            Me.GroupBox8.Controls.Add(Me.tbItmGlow)
            Me.GroupBox8.Controls.Add(Me.tbItmName)
            Me.GroupBox8.Controls.Add(Me.Label48)
            Me.GroupBox8.Controls.Add(Me.Label45)
            Me.GroupBox8.Controls.Add(Me.tbItmQuest)
            Me.GroupBox8.Controls.Add(Me.Label47)
            Me.GroupBox8.Controls.Add(Me.tbItmCode)
            point = New Point(&HBD, 60)
            Me.GroupBox8.Location = point
            Me.GroupBox8.Name = "GroupBox8"
            size = New Size(&HC2, &HC0)
            Me.GroupBox8.Size = size
            Me.GroupBox8.TabIndex = &H3B
            Me.GroupBox8.TabStop = False
            Me.GroupBox8.Text = "Item infomation"
            Me.Label44.AutoSize = True
            point = New Point(6, &H17)
            Me.Label44.Location = point
            Me.Label44.Name = "Label44"
            size = New Size(&H3A, 13)
            Me.Label44.Size = size
            Me.Label44.TabIndex = &H30
            Me.Label44.Text = "Jap Name:"
            Me.Label49.AutoSize = True
            point = New Point(6, &H7F)
            Me.Label49.Location = point
            Me.Label49.Name = "Label49"
            size = New Size(&H3D, 13)
            Me.Label49.Size = size
            Me.Label49.TabIndex = &H3A
            Me.Label49.Text = "Color Glow:"
            point = New Point(&H63, 20)
            Me.tbItmJpName.Location = point
            Me.tbItmJpName.Name = "tbItmJpName"
            size = New Size(&H4B, 20)
            Me.tbItmJpName.Size = size
            Me.tbItmJpName.TabIndex = &H2F
            point = New Point(&H63, &H7C)
            Me.tbItmGlow.Location = point
            Me.tbItmGlow.Name = "tbItmGlow"
            size = New Size(&H4B, 20)
            Me.tbItmGlow.Size = size
            Me.tbItmGlow.TabIndex = &H39
            point = New Point(&H63, &H2E)
            Me.tbItmName.Location = point
            Me.tbItmName.Name = "tbItmName"
            size = New Size(&H4B, 20)
            Me.tbItmName.Size = size
            Me.tbItmName.TabIndex = &H31
            Me.Label48.AutoSize = True
            point = New Point(6, &H65)
            Me.Label48.Location = point
            Me.Label48.Name = "Label48"
            size = New Size(&H34, 13)
            Me.Label48.Size = size
            Me.Label48.TabIndex = &H38
            Me.Label48.Text = "Quest ID:"
            Me.Label45.AutoSize = True
            point = New Point(6, &H31)
            Me.Label45.Location = point
            Me.Label45.Name = "Label45"
            size = New Size(&H26, 13)
            Me.Label45.Size = size
            Me.Label45.TabIndex = 50
            Me.Label45.Text = "Name:"
            point = New Point(&H63, &H62)
            Me.tbItmQuest.Location = point
            Me.tbItmQuest.Name = "tbItmQuest"
            size = New Size(&H4B, 20)
            Me.tbItmQuest.Size = size
            Me.tbItmQuest.TabIndex = &H37
            Me.Label47.AutoSize = True
            point = New Point(6, &H4B)
            Me.Label47.Location = point
            Me.Label47.Name = "Label47"
            size = New Size(&H3A, 13)
            Me.Label47.Size = size
            Me.Label47.TabIndex = &H36
            Me.Label47.Text = "Item Code:"
            point = New Point(&H63, &H48)
            Me.tbItmCode.Location = point
            Me.tbItmCode.Name = "tbItmCode"
            size = New Size(&H4B, 20)
            Me.tbItmCode.Size = size
            Me.tbItmCode.TabIndex = &H35
            Me.GroupBox6.Controls.Add(Me.lbFileListItems)
            Me.GroupBox6.Controls.Add(Me.lbItemsListCount)
            point = New Point(6, 60)
            Me.GroupBox6.Location = point
            Me.GroupBox6.Name = "GroupBox6"
            size = New Size(&HB1, &H253)
            Me.GroupBox6.Size = size
            Me.GroupBox6.TabIndex = &H2E
            Me.GroupBox6.TabStop = False
            Me.GroupBox6.Text = "Files Items"
            Me.lbFileListItems.ContextMenuStrip = Me.cmFileListItems
            Me.lbFileListItems.FormattingEnabled = True
            point = New Point(7, &H25)
            Me.lbFileListItems.Location = point
            Me.lbFileListItems.Name = "lbFileListItems"
            Me.lbFileListItems.SelectionMode = SelectionMode.MultiExtended
            size = New Size(&H9D, 550)
            Me.lbFileListItems.Size = size
            Me.lbFileListItems.TabIndex = 3
            Me.cmFileListItems.Items.AddRange(New ToolStripItem() { Me.LoadBackupToolStripMenuItem, Me.DeleteBackupToolStripMenuItem1, Me.ItemDistribToolStripMenuItem, Me.SeachForItemNameToolStripMenuItem, Me.SendToItemSearcherToolStripMenuItem })
            Me.cmFileListItems.Name = "cmFileListItems"
            size = New Size(190, &H72)
            Me.cmFileListItems.Size = size
            Me.LoadBackupToolStripMenuItem.Name = "LoadBackupToolStripMenuItem"
            size = New Size(&HBD, &H16)
            Me.LoadBackupToolStripMenuItem.Size = size
            Me.LoadBackupToolStripMenuItem.Text = "Load Backup"
            Me.DeleteBackupToolStripMenuItem1.Name = "DeleteBackupToolStripMenuItem1"
            size = New Size(&HBD, &H16)
            Me.DeleteBackupToolStripMenuItem1.Size = size
            Me.DeleteBackupToolStripMenuItem1.Text = "Delete Backup"
            Me.ItemDistribToolStripMenuItem.Name = "ItemDistribToolStripMenuItem"
            size = New Size(&HBD, &H16)
            Me.ItemDistribToolStripMenuItem.Size = size
            Me.ItemDistribToolStripMenuItem.Text = "Send to Item Distributor"
            Me.SeachForItemNameToolStripMenuItem.Name = "SeachForItemNameToolStripMenuItem"
            size = New Size(&HBD, &H16)
            Me.SeachForItemNameToolStripMenuItem.Size = size
            Me.SeachForItemNameToolStripMenuItem.Text = "Seach for item name"
            Me.SendToItemSearcherToolStripMenuItem.Name = "SendToItemSearcherToolStripMenuItem"
            size = New Size(&HBD, &H16)
            Me.SendToItemSearcherToolStripMenuItem.Size = size
            Me.SendToItemSearcherToolStripMenuItem.Text = "Send to item searcher"
            Me.lbItemsListCount.AutoSize = True
            point = New Point(7, &H10)
            Me.lbItemsListCount.Location = point
            Me.lbItemsListCount.Name = "lbItemsListCount"
            size = New Size(&H27, 13)
            Me.lbItemsListCount.Size = size
            Me.lbItemsListCount.TabIndex = 4
            Me.lbItemsListCount.Text = "Label1"
            Me.TabPage3.Controls.Add(Me.ListView1)
            Me.TabPage3.Controls.Add(Me.cmdMapSave)
            Me.TabPage3.Controls.Add(Me.cmdMapReload)
            Me.TabPage3.Controls.Add(Me.gb24)
            Me.TabPage3.Controls.Add(Me.GroupBox22)
            Me.TabPage3.Controls.Add(Me.GroupBox21)
            point = New Point(4, &H16)
            Me.TabPage3.Location = point
            Me.TabPage3.Name = "TabPage3"
            size = New Size(&H410, 660)
            Me.TabPage3.Size = size
            Me.TabPage3.TabIndex = 2
            Me.TabPage3.Text = "Maps"
            Me.TabPage3.UseVisualStyleBackColor = True
            Me.ListView1.Columns.AddRange(New ColumnHeader() { Me.lwBossFileName, Me.LWBossRealName, Me.lwBossAddMonster, Me.lwBossAddMonsterRealName, Me.LWAddSpawnCount, Me.LWBossSpawnTimes })
            Me.ListView1.ContextMenuStrip = Me.CMSMapBoss
            Me.ListView1.FullRowSelect = True
            Me.ListView1.GridLines = True
            Me.ListView1.HeaderStyle = ColumnHeaderStyle.Nonclickable
            Me.ListView1.HideSelection = False
            Me.ListView1.LabelWrap = False
            point = New Point(6, 550)
            Me.ListView1.Location = point
            Me.ListView1.MultiSelect = False
            Me.ListView1.Name = "ListView1"
            size = New Size(&H407, &H6B)
            Me.ListView1.Size = size
            Me.ListView1.TabIndex = &H3E
            Me.ListView1.UseCompatibleStateImageBehavior = False
            Me.ListView1.View = View.Details
            Me.lwBossFileName.Text = "Boss File"
            Me.lwBossFileName.Width = 160
            Me.LWBossRealName.Text = "Boss Zhoon Name"
            Me.LWBossRealName.TextAlign = HorizontalAlignment.Center
            Me.LWBossRealName.Width = 160
            Me.lwBossAddMonster.Text = "Boss guards Spawn File"
            Me.lwBossAddMonster.TextAlign = HorizontalAlignment.Center
            Me.lwBossAddMonster.Width = 160
            Me.lwBossAddMonsterRealName.Text = "Guards Name"
            Me.lwBossAddMonsterRealName.TextAlign = HorizontalAlignment.Center
            Me.lwBossAddMonsterRealName.Width = 160
            Me.LWAddSpawnCount.Text = "Count"
            Me.LWAddSpawnCount.TextAlign = HorizontalAlignment.Center
            Me.LWAddSpawnCount.Width = 70
            Me.LWBossSpawnTimes.Text = "Spawn Times"
            Me.LWBossSpawnTimes.Width = &H13B
            Me.CMSMapBoss.Items.AddRange(New ToolStripItem() { Me.ShowToolStripMenuItem, Me.RemoveAllToolStripMenuItem1, Me.EditRateToolStripMenuItem, Me.EditSpawnTimesToolStripMenuItem })
            Me.CMSMapBoss.Name = "CMSMapBoss"
            size = New Size(&H9B, &H5C)
            Me.CMSMapBoss.Size = size
            Me.ShowToolStripMenuItem.Name = "ShowToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.ShowToolStripMenuItem.Size = size
            Me.ShowToolStripMenuItem.Text = "Remove Boss"
            Me.RemoveAllToolStripMenuItem1.Name = "RemoveAllToolStripMenuItem1"
            size = New Size(&H9A, &H16)
            Me.RemoveAllToolStripMenuItem1.Size = size
            Me.RemoveAllToolStripMenuItem1.Text = "Remove all"
            Me.EditRateToolStripMenuItem.Name = "EditRateToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.EditRateToolStripMenuItem.Size = size
            Me.EditRateToolStripMenuItem.Text = "Edit guard count"
            Me.EditSpawnTimesToolStripMenuItem.Name = "EditSpawnTimesToolStripMenuItem"
            size = New Size(&H9A, &H16)
            Me.EditSpawnTimesToolStripMenuItem.Size = size
            Me.EditSpawnTimesToolStripMenuItem.Text = "Edit spawn times"
            point = New Point(&H57, 7)
            Me.cmdMapSave.Location = point
            Me.cmdMapSave.Name = "cmdMapSave"
            size = New Size(&H4B, &H17)
            Me.cmdMapSave.Size = size
            Me.cmdMapSave.TabIndex = &HAC
            Me.cmdMapSave.Text = "Save"
            Me.cmdMapSave.UseVisualStyleBackColor = True
            point = New Point(6, 7)
            Me.cmdMapReload.Location = point
            Me.cmdMapReload.Name = "cmdMapReload"
            size = New Size(&H4B, &H17)
            Me.cmdMapReload.Size = size
            Me.cmdMapReload.TabIndex = &HA9
            Me.cmdMapReload.Text = "Reload"
            Me.cmdMapReload.UseVisualStyleBackColor = True
            Me.gb24.Controls.Add(Me.tbMapSpawnRate)
            Me.gb24.Controls.Add(Me.Label33)
            Me.gb24.Controls.Add(Me.ListView3)
            Me.gb24.Controls.Add(Me.cbMonsterSelector1)
            point = New Point(&H25C, &H18)
            Me.gb24.Location = point
            Me.gb24.Name = "gb24"
            size = New Size(&H16C, 520)
            Me.gb24.Size = size
            Me.gb24.TabIndex = &H41
            Me.gb24.TabStop = False
            Me.gb24.Text = "All monsters"
            point = New Point(&H4D, &H42)
            Me.tbMapSpawnRate.Location = point
            Me.tbMapSpawnRate.Name = "tbMapSpawnRate"
            size = New Size(50, 20)
            Me.tbMapSpawnRate.Size = size
            Me.tbMapSpawnRate.TabIndex = &H43
            Me.tbMapSpawnRate.Text = "20"
            Me.Label33.AutoSize = True
            point = New Point(7, &H45)
            Me.Label33.Location = point
            Me.Label33.Name = "Label33"
            size = New Size(&H40, 13)
            Me.Label33.Size = size
            Me.Label33.TabIndex = &H42
            Me.Label33.Text = "Spawn rate:"
            Me.ListView3.Columns.AddRange(New ColumnHeader() { Me.ColumnHeader1, Me.ColumnHeader2 })
            Me.ListView3.ContextMenuStrip = Me.CMSMapMonsterToAdd
            Me.ListView3.FullRowSelect = True
            Me.ListView3.GridLines = True
            Me.ListView3.HeaderStyle = ColumnHeaderStyle.Nonclickable
            Me.ListView3.HideSelection = False
            Me.ListView3.LabelWrap = False
            point = New Point(6, &H58)
            Me.ListView3.Location = point
            Me.ListView3.Name = "ListView3"
            size = New Size(&H158, &H1A2)
            Me.ListView3.Size = size
            Me.ListView3.TabIndex = &H3E
            Me.ListView3.UseCompatibleStateImageBehavior = False
            Me.ListView3.View = View.Details
            Me.ColumnHeader1.Text = "Monster Name"
            Me.ColumnHeader1.Width = 160
            Me.ColumnHeader2.Text = "Zhoon Name"
            Me.ColumnHeader2.TextAlign = HorizontalAlignment.Center
            Me.ColumnHeader2.Width = &HB2
            Me.CMSMapMonsterToAdd.Items.AddRange(New ToolStripItem() { Me.AddToMapToolStripMenuItem, Me.AddToSelectedBossToolStripMenuItem, Me.AddToSeletedBossToolStripMenuItem, Me.AddAsNewBossToolStripMenuItem })
            Me.CMSMapMonsterToAdd.Name = "CMSMapMonsterToAdd"
            size = New Size(&HD4, &H5C)
            Me.CMSMapMonsterToAdd.Size = size
            Me.AddToMapToolStripMenuItem.Name = "AddToMapToolStripMenuItem"
            size = New Size(&HD3, &H16)
            Me.AddToMapToolStripMenuItem.Size = size
            Me.AddToMapToolStripMenuItem.Text = "Add to Map"
            Me.AddToSelectedBossToolStripMenuItem.Name = "AddToSelectedBossToolStripMenuItem"
            size = New Size(&HD3, &H16)
            Me.AddToSelectedBossToolStripMenuItem.Size = size
            Me.AddToSelectedBossToolStripMenuItem.Text = "Add as selected boss"
            Me.AddToSeletedBossToolStripMenuItem.Name = "AddToSeletedBossToolStripMenuItem"
            size = New Size(&HD3, &H16)
            Me.AddToSeletedBossToolStripMenuItem.Size = size
            Me.AddToSeletedBossToolStripMenuItem.Text = "Add as selected boss guards"
            Me.AddAsNewBossToolStripMenuItem.Name = "AddAsNewBossToolStripMenuItem"
            size = New Size(&HD3, &H16)
            Me.AddAsNewBossToolStripMenuItem.Size = size
            Me.AddAsNewBossToolStripMenuItem.Text = "Add as new Boss"
            Me.cbMonsterSelector1.FormattingEnabled = True
            point = New Point(6, &H1F)
            Me.cbMonsterSelector1.Location = point
            Me.cbMonsterSelector1.Name = "cbMonsterSelector1"
            size = New Size(&H158, &H15)
            Me.cbMonsterSelector1.Size = size
            Me.cbMonsterSelector1.TabIndex = &H41
            Me.GroupBox22.Controls.Add(Me.ListView2)
            Me.GroupBox22.Controls.Add(Me.Label36)
            Me.GroupBox22.Controls.Add(Me.tbMapValue1)
            Me.GroupBox22.Controls.Add(Me.tbMapValue2)
            Me.GroupBox22.Controls.Add(Me.Label97)
            Me.GroupBox22.Controls.Add(Me.tbMapValue3)
            Me.GroupBox22.Controls.Add(Me.Label98)
            point = New Point(&HBD, &H18)
            Me.GroupBox22.Location = point
            Me.GroupBox22.Name = "GroupBox22"
            size = New Size(&H199, 520)
            Me.GroupBox22.Size = size
            Me.GroupBox22.TabIndex = &H3E
            Me.GroupBox22.TabStop = False
            Me.GroupBox22.Text = "Monster in selected map"
            Me.ListView2.Columns.AddRange(New ColumnHeader() { Me.lwMonsterName, Me.lwMoRealName, Me.lwSpawnRate })
            Me.ListView2.ContextMenuStrip = Me.CMSMonsterInMap
            Me.ListView2.FullRowSelect = True
            Me.ListView2.GridLines = True
            Me.ListView2.HeaderStyle = ColumnHeaderStyle.Nonclickable
            Me.ListView2.HideSelection = False
            Me.ListView2.LabelWrap = False
            point = New Point(6, &H58)
            Me.ListView2.Location = point
            Me.ListView2.MultiSelect = False
            Me.ListView2.Name = "ListView2"
            size = New Size(&H18B, &H1A2)
            Me.ListView2.Size = size
            Me.ListView2.TabIndex = &H3D
            Me.ListView2.UseCompatibleStateImageBehavior = False
            Me.ListView2.View = View.Details
            Me.lwMonsterName.Text = "Monster Filename"
            Me.lwMonsterName.Width = 160
            Me.lwMoRealName.Text = "Zhoon Name"
            Me.lwMoRealName.TextAlign = HorizontalAlignment.Center
            Me.lwMoRealName.Width = 160
            Me.lwSpawnRate.Text = "rate"
            Me.lwSpawnRate.TextAlign = HorizontalAlignment.Center
            Me.lwSpawnRate.Width = 70
            Me.CMSMonsterInMap.Items.AddRange(New ToolStripItem() { Me.RemoveMonsterToolStripMenuItem, Me.RemoveAllToolStripMenuItem, Me.EditSpawnRateToolStripMenuItem })
            Me.CMSMonsterInMap.Name = "CMSMonsterInMap"
            size = New Size(&H9C, 70)
            Me.CMSMonsterInMap.Size = size
            Me.RemoveMonsterToolStripMenuItem.Name = "RemoveMonsterToolStripMenuItem"
            size = New Size(&H9B, &H16)
            Me.RemoveMonsterToolStripMenuItem.Size = size
            Me.RemoveMonsterToolStripMenuItem.Text = "Remove Monster"
            Me.RemoveAllToolStripMenuItem.Name = "RemoveAllToolStripMenuItem"
            size = New Size(&H9B, &H16)
            Me.RemoveAllToolStripMenuItem.Size = size
            Me.RemoveAllToolStripMenuItem.Text = "Remove all"
            Me.EditSpawnRateToolStripMenuItem.Name = "EditSpawnRateToolStripMenuItem"
            size = New Size(&H9B, &H16)
            Me.EditSpawnRateToolStripMenuItem.Size = size
            Me.EditSpawnRateToolStripMenuItem.Text = "Edit spawn rate"
            Me.Label36.AutoSize = True
            point = New Point(3, &H27)
            Me.Label36.Location = point
            Me.Label36.Name = "Label36"
            size = New Size(&H5E, 13)
            Me.Label36.Size = size
            Me.Label36.TabIndex = 50
            Me.Label36.Text = "Unknown value 1:"
            point = New Point(&H67, &H24)
            Me.tbMapValue1.Location = point
            Me.tbMapValue1.Name = "tbMapValue1"
            size = New Size(&H4B, 20)
            Me.tbMapValue1.Size = size
            Me.tbMapValue1.TabIndex = &H31
            point = New Point(&H67, &H3E)
            Me.tbMapValue2.Location = point
            Me.tbMapValue2.Name = "tbMapValue2"
            size = New Size(&H4B, 20)
            Me.tbMapValue2.Size = size
            Me.tbMapValue2.TabIndex = &H33
            Me.Label97.AutoSize = True
            point = New Point(3, &H41)
            Me.Label97.Location = point
            Me.Label97.Name = "Label97"
            size = New Size(&H5E, 13)
            Me.Label97.Size = size
            Me.Label97.TabIndex = &H34
            Me.Label97.Text = "Unknown value 2:"
            point = New Point(&H123, &H24)
            Me.tbMapValue3.Location = point
            Me.tbMapValue3.Name = "tbMapValue3"
            size = New Size(&H4B, 20)
            Me.tbMapValue3.Size = size
            Me.tbMapValue3.TabIndex = &H35
            Me.Label98.AutoSize = True
            point = New Point(&HBF, &H27)
            Me.Label98.Location = point
            Me.Label98.Name = "Label98"
            size = New Size(&H5E, 13)
            Me.Label98.Size = size
            Me.Label98.TabIndex = &H36
            Me.Label98.Text = "Unknown value 3:"
            Me.GroupBox21.Controls.Add(Me.lbFilesMaps)
            Me.GroupBox21.Controls.Add(Me.Label96)
            point = New Point(6, 60)
            Me.GroupBox21.Location = point
            Me.GroupBox21.Name = "GroupBox21"
            size = New Size(&HB1, &H1E4)
            Me.GroupBox21.Size = size
            Me.GroupBox21.TabIndex = &H2F
            Me.GroupBox21.TabStop = False
            Me.GroupBox21.Text = "Map files"
            Me.lbFilesMaps.ContextMenuStrip = Me.cmMapsFiles
            Me.lbFilesMaps.FormattingEnabled = True
            point = New Point(7, &H25)
            Me.lbFilesMaps.Location = point
            Me.lbFilesMaps.Name = "lbFilesMaps"
            size = New Size(&H9D, &H1B1)
            Me.lbFilesMaps.Size = size
            Me.lbFilesMaps.TabIndex = 3
            Me.cmMapsFiles.Items.AddRange(New ToolStripItem() { Me.ChangeEXPOfMapToolStripMenuItem })
            Me.cmMapsFiles.Name = "cmMapsFiles"
            size = New Size(&HA9, &H1A)
            Me.cmMapsFiles.Size = size
            Me.ChangeEXPOfMapToolStripMenuItem.Name = "ChangeEXPOfMapToolStripMenuItem"
            size = New Size(&HA8, &H16)
            Me.ChangeEXPOfMapToolStripMenuItem.Size = size
            Me.ChangeEXPOfMapToolStripMenuItem.Text = "Change EXP of Map"
            Me.Label96.AutoSize = True
            point = New Point(7, &H10)
            Me.Label96.Location = point
            Me.Label96.Name = "Label96"
            size = New Size(&H21, 13)
            Me.Label96.Size = size
            Me.Label96.TabIndex = 4
            Me.Label96.Text = "Maps"
            Me.TabPage5.Controls.Add(Me.tbNPCSetupfile)
            Me.TabPage5.Controls.Add(Me.tbNPCModelFile)
            Me.TabPage5.Controls.Add(Me.Label101)
            Me.TabPage5.Controls.Add(Me.GroupBox23)
            Me.TabPage5.Controls.Add(Me.tbNPCangle)
            Me.TabPage5.Controls.Add(Me.Label106)
            Me.TabPage5.Controls.Add(Me.cmdNPCReload)
            Me.TabPage5.Controls.Add(Me.Label107)
            Me.TabPage5.Controls.Add(Me.tbNPCName)
            Me.TabPage5.Controls.Add(Me.tbNPCJ_Chat)
            Me.TabPage5.Controls.Add(Me.Label108)
            Me.TabPage5.Controls.Add(Me.tbNPCID)
            Me.TabPage5.Controls.Add(Me.Label109)
            Me.TabPage5.Controls.Add(Me.Label110)
            Me.TabPage5.Controls.Add(Me.PictureBox1)
            Me.TabPage5.Controls.Add(Me.Label111)
            Me.TabPage5.Controls.Add(Me.Label112)
            Me.TabPage5.Controls.Add(Me.cbNPCAktivated)
            Me.TabPage5.Controls.Add(Me.cmdNPCSave)
            Me.TabPage5.Controls.Add(Me.lbNPCMapFileList)
            Me.TabPage5.Controls.Add(Me.lbNPCList)
            Me.TabPage5.Controls.Add(Me.Label113)
            Me.TabPage5.Controls.Add(Me.Label114)
            Me.TabPage5.Controls.Add(Me.Label115)
            Me.TabPage5.Controls.Add(Me.tbNPCz)
            Me.TabPage5.Controls.Add(Me.tbNPCy)
            Me.TabPage5.Controls.Add(Me.tbNPCx)
            point = New Point(4, &H16)
            Me.TabPage5.Location = point
            Me.TabPage5.Name = "TabPage5"
            padding = New Padding(3)
            Me.TabPage5.Padding = padding
            size = New Size(&H410, 660)
            Me.TabPage5.Size = size
            Me.TabPage5.TabIndex = 4
            Me.TabPage5.Text = "NPC Editor"
            Me.TabPage5.UseVisualStyleBackColor = True
            Me.tbNPCSetupfile.AutoCompleteMode = AutoCompleteMode.Suggest
            Me.tbNPCSetupfile.AutoCompleteSource = AutoCompleteSource.ListItems
            Me.tbNPCSetupfile.FormattingEnabled = True
            point = New Point(9, &H142)
            Me.tbNPCSetupfile.Location = point
            Me.tbNPCSetupfile.Name = "tbNPCSetupfile"
            size = New Size(&H131, &H15)
            Me.tbNPCSetupfile.Size = size
            Me.tbNPCSetupfile.TabIndex = 80
            Me.tbNPCModelFile.AutoCompleteMode = AutoCompleteMode.Suggest
            Me.tbNPCModelFile.AutoCompleteSource = AutoCompleteSource.ListItems
            Me.tbNPCModelFile.FormattingEnabled = True
            point = New Point(9, &H127)
            Me.tbNPCModelFile.Location = point
            Me.tbNPCModelFile.Name = "tbNPCModelFile"
            size = New Size(&H131, &H15)
            Me.tbNPCModelFile.Size = size
            Me.tbNPCModelFile.TabIndex = &H4F
            Me.Label101.AutoSize = True
            point = New Point(&H207, &H74)
            Me.Label101.Location = point
            Me.Label101.Name = "Label101"
            size = New Size(&H22, 13)
            Me.Label101.Size = size
            Me.Label101.TabIndex = &H4E
            Me.Label101.Text = "Angle"
            Me.GroupBox23.Controls.Add(Me.TextBox1)
            Me.GroupBox23.Controls.Add(Me.tbNPCSetupfileInI)
            Me.GroupBox23.Controls.Add(Me.CMDNPCShopSave)
            Me.GroupBox23.Controls.Add(Me.Label116)
            Me.GroupBox23.Controls.Add(Me.Label99)
            Me.GroupBox23.Controls.Add(Me.LWNPCshop)
            Me.GroupBox23.Controls.Add(Me.CBShopItem)
            point = New Point(8, &H174)
            Me.GroupBox23.Location = point
            Me.GroupBox23.Name = "GroupBox23"
            size = New Size(&H1FC, &H11D)
            Me.GroupBox23.Size = size
            Me.GroupBox23.TabIndex = &H4D
            Me.GroupBox23.TabStop = False
            Me.GroupBox23.Text = "NPC File infos"
            Me.TextBox1.BackColor = SystemColors.InfoText
            Me.TextBox1.Enabled = False
            Me.TextBox1.ForeColor = SystemColors.Menu
            point = New Point(&HFD, &HBC)
            Me.TextBox1.Location = point
            Me.TextBox1.Multiline = True
            Me.TextBox1.Name = "TextBox1"
            size = New Size(&HF9, &H34)
            Me.TextBox1.Size = size
            Me.TextBox1.TabIndex = &H4E
            Me.TextBox1.Text = "--->Waring!<--- " & ChrW(13) & ChrW(10) & "Only Change NPC skinn if you know what you do!" & ChrW(13) & ChrW(10) & "Server may Crash at wrong file!"
            Me.tbNPCSetupfileInI.AutoCompleteMode = AutoCompleteMode.Suggest
            Me.tbNPCSetupfileInI.AutoCompleteSource = AutoCompleteSource.ListItems
            Me.tbNPCSetupfileInI.FormattingEnabled = True
            point = New Point(&H100, 260)
            Me.tbNPCSetupfileInI.Location = point
            Me.tbNPCSetupfileInI.Name = "tbNPCSetupfileInI"
            size = New Size(&HFC, &H15)
            Me.tbNPCSetupfileInI.Size = size
            Me.tbNPCSetupfileInI.TabIndex = &H4D
            point = New Point(&HFD, &H13)
            Me.CMDNPCShopSave.Location = point
            Me.CMDNPCShopSave.Name = "CMDNPCShopSave"
            size = New Size(&H63, &H17)
            Me.CMDNPCShopSave.Size = size
            Me.CMDNPCShopSave.TabIndex = &H4C
            Me.CMDNPCShopSave.Text = "Save NPC setup"
            Me.CMDNPCShopSave.UseVisualStyleBackColor = True
            Me.Label116.AutoSize = True
            point = New Point(250, &H33)
            Me.Label116.Location = point
            Me.Label116.Name = "Label116"
            size = New Size(&H4A, 13)
            Me.Label116.Size = size
            Me.Label116.TabIndex = &H43
            Me.Label116.Text = "Items in Shop:"
            Me.Label99.AutoSize = True
            point = New Point(&HFD, &HF3)
            Me.Label99.Location = point
            Me.Label99.Name = "Label99"
            size = New Size(&H3E, 13)
            Me.Label99.Size = size
            Me.Label99.TabIndex = &H4A
            Me.Label99.Text = "NPC Skinn:"
            Me.LWNPCshop.Columns.AddRange(New ColumnHeader() { Me.CoItemCode, Me.CoItemName })
            Me.LWNPCshop.ContextMenuStrip = Me.CMSAddShopItem
            Me.LWNPCshop.FullRowSelect = True
            point = New Point(6, &H13)
            Me.LWNPCshop.Location = point
            Me.LWNPCshop.Name = "LWNPCshop"
            size = New Size(&HF1, 260)
            Me.LWNPCshop.Size = size
            Me.LWNPCshop.TabIndex = &H48
            Me.LWNPCshop.UseCompatibleStateImageBehavior = False
            Me.LWNPCshop.View = View.Details
            Me.CoItemCode.Text = "Code"
            Me.CoItemName.Text = "Name"
            Me.CoItemName.Width = &HAF
            Me.CMSAddShopItem.Items.AddRange(New ToolStripItem() { Me.AddItemsToolStripMenuItem, Me.RemoveToolStripMenuItem })
            Me.CMSAddShopItem.Name = "CMSAddShopItem"
            size = New Size(&H7A, &H30)
            Me.CMSAddShopItem.Size = size
            Me.AddItemsToolStripMenuItem.Name = "AddItemsToolStripMenuItem"
            size = New Size(&H79, &H16)
            Me.AddItemsToolStripMenuItem.Size = size
            Me.AddItemsToolStripMenuItem.Text = "Add items"
            Me.RemoveToolStripMenuItem.Name = "RemoveToolStripMenuItem"
            size = New Size(&H79, &H16)
            Me.RemoveToolStripMenuItem.Size = size
            Me.RemoveToolStripMenuItem.Text = "Remove"
            Me.CBShopItem.FormattingEnabled = True
            Me.CBShopItem.Items.AddRange(New Object() { "Defence", "Weapons", "Other stuff" })
            point = New Point(&HFD, &H43)
            Me.CBShopItem.Location = point
            Me.CBShopItem.Name = "CBShopItem"
            size = New Size(&HA6, &H15)
            Me.CBShopItem.Size = size
            Me.CBShopItem.TabIndex = &H49
            Me.CBShopItem.Text = "Defence"
            point = New Point(&H239, &H71)
            Me.tbNPCangle.Location = point
            Me.tbNPCangle.Name = "tbNPCangle"
            size = New Size(&H6C, 20)
            Me.tbNPCangle.Size = size
            Me.tbNPCangle.TabIndex = &H47
            Me.Label106.AutoSize = True
            point = New Point(320, 6)
            Me.Label106.Location = point
            Me.Label106.Name = "Label106"
            size = New Size(&H151, 13)
            Me.Label106.Size = size
            Me.Label106.TabIndex = &H41
            Me.Label106.Text = "Chat:   Each line in this text represent a new J_Chat in NPC-zhoon file."
            point = New Point(6, 6)
            Me.cmdNPCReload.Location = point
            Me.cmdNPCReload.Name = "cmdNPCReload"
            size = New Size(&H4B, &H17)
            Me.cmdNPCReload.Size = size
            Me.cmdNPCReload.TabIndex = &H40
            Me.cmdNPCReload.Text = "Reload"
            Me.cmdNPCReload.UseVisualStyleBackColor = True
            Me.Label107.AutoSize = True
            point = New Point(&H13F, &HA1)
            Me.Label107.Location = point
            Me.Label107.Name = "Label107"
            size = New Size(&H3F, 13)
            Me.Label107.Size = size
            Me.Label107.TabIndex = &H3F
            Me.Label107.Text = "NPC Name:"
            point = New Point(&H181, &H9E)
            Me.tbNPCName.Location = point
            Me.tbNPCName.Name = "tbNPCName"
            size = New Size(&H83, 20)
            Me.tbNPCName.Size = size
            Me.tbNPCName.TabIndex = &H3E
            point = New Point(320, &H16)
            Me.tbNPCJ_Chat.Location = point
            Me.tbNPCJ_Chat.Multiline = True
            Me.tbNPCJ_Chat.Name = "tbNPCJ_Chat"
            Me.tbNPCJ_Chat.ScrollBars = ScrollBars.Both
            size = New Size(&H2CA, &H55)
            Me.tbNPCJ_Chat.Size = size
            Me.tbNPCJ_Chat.TabIndex = &H3D
            Me.tbNPCJ_Chat.WordWrap = False
            Me.Label108.AutoSize = True
            point = New Point(&H166, &H74)
            Me.Label108.Location = point
            Me.Label108.Name = "Label108"
            size = New Size(&H15, 13)
            Me.Label108.Size = size
            Me.Label108.TabIndex = 60
            Me.Label108.Text = "ID:"
            point = New Point(&H181, &H71)
            Me.tbNPCID.Location = point
            Me.tbNPCID.Name = "tbNPCID"
            size = New Size(&H83, 20)
            Me.tbNPCID.Size = size
            Me.tbNPCID.TabIndex = &H3B
            Me.Label109.AutoSize = True
            point = New Point(6, &H20)
            Me.Label109.Location = point
            Me.Label109.Name = "Label109"
            size = New Size(&H47, 13)
            Me.Label109.Size = size
            Me.Label109.TabIndex = &H3A
            Me.Label109.Text = "NPC map file:"
            Me.Label110.AutoSize = True
            point = New Point(&H9E, &H20)
            Me.Label110.Location = point
            Me.Label110.Name = "Label110"
            size = New Size(&H3F, 13)
            Me.Label110.Size = size
            Me.Label110.TabIndex = &H39
            Me.Label110.Text = "NPC Name:"
            Me.PictureBox1.BackColor = SystemColors.ControlText
            Me.PictureBox1.ContextMenuStrip = Me.CMNPCPicturebox
            point = New Point(&H20A, &H8E)
            Me.PictureBox1.Location = point
            Me.PictureBox1.Name = "PictureBox1"
            size = New Size(&H200, &H200)
            Me.PictureBox1.Size = size
            Me.PictureBox1.SizeMode = PictureBoxSizeMode.StretchImage
            Me.PictureBox1.TabIndex = &H38
            Me.PictureBox1.TabStop = False
            Me.CMNPCPicturebox.Items.AddRange(New ToolStripItem() { Me.BringBackToMapToolStripMenuItem })
            Me.CMNPCPicturebox.Name = "CMNPCPicturebox"
            size = New Size(160, &H1A)
            Me.CMNPCPicturebox.Size = size
            Me.BringBackToMapToolStripMenuItem.Name = "BringBackToMapToolStripMenuItem"
            size = New Size(&H9F, &H16)
            Me.BringBackToMapToolStripMenuItem.Size = size
            Me.BringBackToMapToolStripMenuItem.Text = "Bring back to Map"
            Me.Label111.AutoSize = True
            point = New Point(&H13F, &H12A)
            Me.Label111.Location = point
            Me.Label111.Name = "Label111"
            size = New Size(&H37, 13)
            Me.Label111.Size = size
            Me.Label111.TabIndex = &H37
            Me.Label111.Text = "Model file:"
            Me.Label112.AutoSize = True
            point = New Point(320, &H145)
            Me.Label112.Location = point
            Me.Label112.Name = "Label112"
            size = New Size(&H4D, 13)
            Me.Label112.Size = size
            Me.Label112.TabIndex = &H35
            Me.Label112.Text = "NPC setup file:"
            Me.cbNPCAktivated.AutoSize = True
            point = New Point(&HF3, &H1F)
            Me.cbNPCAktivated.Location = point
            Me.cbNPCAktivated.Name = "cbNPCAktivated"
            size = New Size(&H47, &H11)
            Me.cbNPCAktivated.Size = size
            Me.cbNPCAktivated.TabIndex = &H33
            Me.cbNPCAktivated.Text = "Activated"
            Me.cbNPCAktivated.UseVisualStyleBackColor = True
            point = New Point(&H57, 6)
            Me.cmdNPCSave.Location = point
            Me.cmdNPCSave.Name = "cmdNPCSave"
            size = New Size(&H4B, &H17)
            Me.cmdNPCSave.Size = size
            Me.cmdNPCSave.TabIndex = 50
            Me.cmdNPCSave.Text = "Save NPC"
            Me.cmdNPCSave.UseVisualStyleBackColor = True
            Me.lbNPCMapFileList.FormattingEnabled = True
            point = New Point(9, &H33)
            Me.lbNPCMapFileList.Location = point
            Me.lbNPCMapFileList.Name = "lbNPCMapFileList"
            size = New Size(&H92, &HEE)
            Me.lbNPCMapFileList.Size = size
            Me.lbNPCMapFileList.TabIndex = &H31
            Me.lbNPCList.ContextMenuStrip = Me.CMSNPCList
            Me.lbNPCList.FormattingEnabled = True
            point = New Point(&HA1, &H33)
            Me.lbNPCList.Location = point
            Me.lbNPCList.Name = "lbNPCList"
            size = New Size(&H99, &HEE)
            Me.lbNPCList.Size = size
            Me.lbNPCList.TabIndex = &H30
            Me.CMSNPCList.Items.AddRange(New ToolStripItem() { Me.UpToolStripMenuItem, Me.DownToolStripMenuItem, Me.DeleteNPCToolStripMenuItem, Me.DeleteNPCToolStripMenuItem1 })
            Me.CMSNPCList.Name = "CMSNPCList"
            size = New Size(140, &H5C)
            Me.CMSNPCList.Size = size
            Me.UpToolStripMenuItem.Name = "UpToolStripMenuItem"
            size = New Size(&H8B, &H16)
            Me.UpToolStripMenuItem.Size = size
            Me.UpToolStripMenuItem.Text = "NPC Up"
            Me.DownToolStripMenuItem.Name = "DownToolStripMenuItem"
            size = New Size(&H8B, &H16)
            Me.DownToolStripMenuItem.Size = size
            Me.DownToolStripMenuItem.Text = "NPC Down"
            Me.DeleteNPCToolStripMenuItem.Name = "DeleteNPCToolStripMenuItem"
            size = New Size(&H8B, &H16)
            Me.DeleteNPCToolStripMenuItem.Size = size
            Me.DeleteNPCToolStripMenuItem.Text = "Add new NPC"
            Me.DeleteNPCToolStripMenuItem1.Name = "DeleteNPCToolStripMenuItem1"
            size = New Size(&H8B, &H16)
            Me.DeleteNPCToolStripMenuItem1.Size = size
            Me.DeleteNPCToolStripMenuItem1.Text = "Delete NPC"
            Me.Label113.AutoSize = True
            point = New Point(&H399, &H74)
            Me.Label113.Location = point
            Me.Label113.Name = "Label113"
            size = New Size(&H11, 13)
            Me.Label113.Size = size
            Me.Label113.TabIndex = &H2F
            Me.Label113.Text = "Z:"
            Me.Label114.AutoSize = True
            point = New Point(&H322, &H74)
            Me.Label114.Location = point
            Me.Label114.Name = "Label114"
            size = New Size(&H11, 13)
            Me.Label114.Size = size
            Me.Label114.TabIndex = &H2E
            Me.Label114.Text = "Y:"
            Me.Label115.AutoSize = True
            point = New Point(&H2AB, &H74)
            Me.Label115.Location = point
            Me.Label115.Name = "Label115"
            size = New Size(&H11, 13)
            Me.Label115.Size = size
            Me.Label115.TabIndex = &H2D
            Me.Label115.Text = "X:"
            point = New Point(&H3B0, &H71)
            Me.tbNPCz.Location = point
            Me.tbNPCz.Name = "tbNPCz"
            size = New Size(90, 20)
            Me.tbNPCz.Size = size
            Me.tbNPCz.TabIndex = &H2C
            Me.tbNPCz.Text = "1"
            point = New Point(&H339, &H71)
            Me.tbNPCy.Location = point
            Me.tbNPCy.Name = "tbNPCy"
            size = New Size(90, 20)
            Me.tbNPCy.Size = size
            Me.tbNPCy.TabIndex = &H2B
            Me.tbNPCy.Text = "1"
            point = New Point(&H2C2, &H71)
            Me.tbNPCx.Location = point
            Me.tbNPCx.Name = "tbNPCx"
            size = New Size(90, 20)
            Me.tbNPCx.Size = size
            Me.tbNPCx.TabIndex = &H2A
            Me.tbNPCx.Text = "1"
            Me.TabPage4.Controls.Add(Me.GroupBox7)
            Me.TabPage4.Controls.Add(Me.Settings)
            point = New Point(4, &H16)
            Me.TabPage4.Location = point
            Me.TabPage4.Name = "TabPage4"
            padding = New Padding(3)
            Me.TabPage4.Padding = padding
            size = New Size(&H410, 660)
            Me.TabPage4.Size = size
            Me.TabPage4.TabIndex = 3
            Me.TabPage4.Text = "Options"
            Me.TabPage4.UseVisualStyleBackColor = True
            Me.GroupBox7.Controls.Add(Me.Label100)
            Me.GroupBox7.Controls.Add(Me.cmdDelBackup)
            Me.GroupBox7.Controls.Add(Me.cbMoZhoonWarn)
            Me.GroupBox7.Controls.Add(Me.cmdCheckMaps)
            Me.GroupBox7.Controls.Add(Me.cbWarnMap)
            Me.GroupBox7.Controls.Add(Me.CmdCheckDrop)
            Me.GroupBox7.Controls.Add(Me.cmdCheckGold)
            Me.GroupBox7.Controls.Add(Me.cmd_Check)
            Me.GroupBox7.Controls.Add(Me.tbWarnItem)
            Me.GroupBox7.Controls.Add(Me.Label43)
            Me.GroupBox7.Controls.Add(Me.tbMaxGold)
            Me.GroupBox7.Controls.Add(Me.Label42)
            Me.GroupBox7.Controls.Add(Me.tbMaxExp)
            Me.GroupBox7.Controls.Add(Me.Label41)
            point = New Point(&H1C5, 6)
            Me.GroupBox7.Location = point
            Me.GroupBox7.Name = "GroupBox7"
            size = New Size(&H100, &HC3)
            Me.GroupBox7.Size = size
            Me.GroupBox7.TabIndex = 6
            Me.GroupBox7.TabStop = False
            Me.GroupBox7.Text = "Monster value warnings"
            Me.Label100.AutoSize = True
            point = New Point(9, &H99)
            Me.Label100.Location = point
            Me.Label100.Name = "Label100"
            size = New Size(&H6D, 13)
            Me.Label100.Size = size
            Me.Label100.TabIndex = 15
            Me.Label100.Text = "Delete all Backupfiles"
            point = New Point(&HAE, &H94)
            Me.cmdDelBackup.Location = point
            Me.cmdDelBackup.Name = "cmdDelBackup"
            size = New Size(&H4B, &H17)
            Me.cmdDelBackup.Size = size
            Me.cmdDelBackup.TabIndex = 14
            Me.cmdDelBackup.Text = "Delete"
            Me.cmdDelBackup.UseVisualStyleBackColor = True
            Me.cbMoZhoonWarn.AutoSize = True
            Me.cbMoZhoonWarn.Checked = MySettings.Default.WarnMoZhoon
            Me.cbMoZhoonWarn.CheckState = CheckState.Checked
            Me.cbMoZhoonWarn.DataBindings.Add(New Binding("Checked", MySettings.Default, "WarnMoZhoon", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(10, &H79)
            Me.cbMoZhoonWarn.Location = point
            Me.cbMoZhoonWarn.Name = "cbMoZhoonWarn"
            size = New Size(150, &H11)
            Me.cbMoZhoonWarn.Size = size
            Me.cbMoZhoonWarn.TabIndex = 13
            Me.cbMoZhoonWarn.Text = "Warn: No zhoon file found"
            Me.cbMoZhoonWarn.UseVisualStyleBackColor = True
            Me.cmdCheckMaps.Enabled = False
            point = New Point(&HAE, &H62)
            Me.cmdCheckMaps.Location = point
            Me.cmdCheckMaps.Name = "cmdCheckMaps"
            size = New Size(&H4B, &H17)
            Me.cmdCheckMaps.Size = size
            Me.cmdCheckMaps.TabIndex = 12
            Me.cmdCheckMaps.Text = "Check Maps"
            Me.cmdCheckMaps.UseVisualStyleBackColor = True
            Me.cbWarnMap.AutoSize = True
            Me.cbWarnMap.Enabled = False
            point = New Point(10, &H62)
            Me.cbWarnMap.Location = point
            Me.cbWarnMap.Name = "cbWarnMap"
            size = New Size(&H98, &H11)
            Me.cbWarnMap.Size = size
            Me.cbWarnMap.TabIndex = 11
            Me.cbWarnMap.Text = "Warn: monster not in maps"
            Me.cbWarnMap.UseVisualStyleBackColor = True
            point = New Point(&HAE, &H45)
            Me.CmdCheckDrop.Location = point
            Me.CmdCheckDrop.Name = "CmdCheckDrop"
            size = New Size(&H4B, &H17)
            Me.CmdCheckDrop.Size = size
            Me.CmdCheckDrop.TabIndex = 10
            Me.CmdCheckDrop.Text = "Check Drop"
            Me.CmdCheckDrop.UseVisualStyleBackColor = True
            point = New Point(&HAE, &H2B)
            Me.cmdCheckGold.Location = point
            Me.cmdCheckGold.Name = "cmdCheckGold"
            size = New Size(&H4B, &H17)
            Me.cmdCheckGold.Size = size
            Me.cmdCheckGold.TabIndex = 9
            Me.cmdCheckGold.Text = "Check Gold"
            Me.cmdCheckGold.UseVisualStyleBackColor = True
            point = New Point(&HAE, 14)
            Me.cmd_Check.Location = point
            Me.cmd_Check.Name = "cmd_Check"
            size = New Size(&H4B, &H17)
            Me.cmd_Check.Size = size
            Me.cmd_Check.TabIndex = 6
            Me.cmd_Check.Text = "Check EXP"
            Me.cmd_Check.UseVisualStyleBackColor = True
            Me.tbWarnItem.DataBindings.Add(New Binding("Text", MySettings.Default, "ItemWarn", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(&H44, &H47)
            Me.tbWarnItem.Location = point
            Me.tbWarnItem.Name = "tbWarnItem"
            size = New Size(100, 20)
            Me.tbWarnItem.Size = size
            Me.tbWarnItem.TabIndex = 5
            Me.tbWarnItem.Text = MySettings.Default.ItemWarn
            Me.Label43.AutoSize = True
            point = New Point(7, &H4A)
            Me.Label43.Location = point
            Me.Label43.Name = "Label43"
            size = New Size(&H35, 13)
            Me.Label43.Size = size
            Me.Label43.TabIndex = 4
            Me.Label43.Text = "Drop Item"
            Me.tbMaxGold.DataBindings.Add(New Binding("Text", MySettings.Default, "MaxGold", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(&H44, &H2D)
            Me.tbMaxGold.Location = point
            Me.tbMaxGold.Name = "tbMaxGold"
            size = New Size(100, 20)
            Me.tbMaxGold.Size = size
            Me.tbMaxGold.TabIndex = 3
            Me.tbMaxGold.Text = MySettings.Default.MaxGold
            Me.Label42.AutoSize = True
            point = New Point(7, &H30)
            Me.Label42.Location = point
            Me.Label42.Name = "Label42"
            size = New Size(&H37, 13)
            Me.Label42.Size = size
            Me.Label42.TabIndex = 2
            Me.Label42.Text = "Max. Gold"
            Me.tbMaxExp.DataBindings.Add(New Binding("Text", MySettings.Default, "MaxExp", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(&H44, &H10)
            Me.tbMaxExp.Location = point
            Me.tbMaxExp.Name = "tbMaxExp"
            size = New Size(100, 20)
            Me.tbMaxExp.Size = size
            Me.tbMaxExp.TabIndex = 1
            Me.tbMaxExp.Text = MySettings.Default.MaxExp
            Me.Label41.AutoSize = True
            point = New Point(7, &H13)
            Me.Label41.Location = point
            Me.Label41.Name = "Label41"
            size = New Size(&H33, 13)
            Me.Label41.Size = size
            Me.Label41.TabIndex = 0
            Me.Label41.Text = "Max. Exp"
            Me.Settings.Controls.Add(Me.Button3)
            Me.Settings.Controls.Add(Me.cmdSaveConfig)
            Me.Settings.Controls.Add(Me.cmdShowLog)
            Me.Settings.Controls.Add(Me.cmdDefaultConfig)
            Me.Settings.Controls.Add(Me.cmdLoadConfig)
            Me.Settings.Controls.Add(Me.cmdConfigEdit)
            Me.Settings.Controls.Add(Me.cmdEditorExe)
            Me.Settings.Controls.Add(Me.tbServerPath)
            Me.Settings.Controls.Add(Me.tbEditorPath)
            Me.Settings.Controls.Add(Me.cmdPath)
            point = New Point(6, 6)
            Me.Settings.Location = point
            Me.Settings.Name = "Settings"
            size = New Size(&H1B9, &HC3)
            Me.Settings.Size = size
            Me.Settings.TabIndex = 5
            Me.Settings.TabStop = False
            Me.Settings.Text = "Settings"
            point = New Point(&H15A, &H8F)
            Me.Button3.Location = point
            Me.Button3.Name = "Button3"
            size = New Size(&H59, &H17)
            Me.Button3.Size = size
            Me.Button3.TabIndex = 10
            Me.Button3.Text = "Test Error.log"
            Me.Button3.UseVisualStyleBackColor = True
            point = New Point(&H57, &H6C)
            Me.cmdSaveConfig.Location = point
            Me.cmdSaveConfig.Name = "cmdSaveConfig"
            size = New Size(&H4B, &H17)
            Me.cmdSaveConfig.Size = size
            Me.cmdSaveConfig.TabIndex = 9
            Me.cmdSaveConfig.Text = "Save Config"
            Me.cmdSaveConfig.UseVisualStyleBackColor = True
            point = New Point(360, &H6C)
            Me.cmdShowLog.Location = point
            Me.cmdShowLog.Name = "cmdShowLog"
            size = New Size(&H4B, &H17)
            Me.cmdShowLog.Size = size
            Me.cmdShowLog.TabIndex = 8
            Me.cmdShowLog.Text = "Error log"
            Me.cmdShowLog.UseVisualStyleBackColor = True
            point = New Point(&H57, &H4E)
            Me.cmdDefaultConfig.Location = point
            Me.cmdDefaultConfig.Name = "cmdDefaultConfig"
            size = New Size(&H4B, &H17)
            Me.cmdDefaultConfig.Size = size
            Me.cmdDefaultConfig.TabIndex = 7
            Me.cmdDefaultConfig.Text = "Default"
            Me.cmdDefaultConfig.UseVisualStyleBackColor = True
            point = New Point(7, &H6C)
            Me.cmdLoadConfig.Location = point
            Me.cmdLoadConfig.Name = "cmdLoadConfig"
            size = New Size(&H4B, &H17)
            Me.cmdLoadConfig.Size = size
            Me.cmdLoadConfig.TabIndex = 6
            Me.cmdLoadConfig.Text = "Load Config"
            Me.cmdLoadConfig.UseVisualStyleBackColor = True
            point = New Point(7, &H4E)
            Me.cmdConfigEdit.Location = point
            Me.cmdConfigEdit.Name = "cmdConfigEdit"
            size = New Size(&H4B, &H17)
            Me.cmdConfigEdit.Size = size
            Me.cmdConfigEdit.TabIndex = 5
            Me.cmdConfigEdit.Text = "Edit Config"
            Me.cmdConfigEdit.UseVisualStyleBackColor = True
            point = New Point(6, &H13)
            Me.cmdEditorExe.Location = point
            Me.cmdEditorExe.Name = "cmdEditorExe"
            size = New Size(&H4B, &H17)
            Me.cmdEditorExe.Size = size
            Me.cmdEditorExe.TabIndex = 1
            Me.cmdEditorExe.Text = "Text Editor"
            Me.cmdEditorExe.UseVisualStyleBackColor = True
            Me.tbServerPath.DataBindings.Add(New Binding("Text", MySettings.Default, "sspath", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(&H57, 50)
            Me.tbServerPath.Location = point
            Me.tbServerPath.Name = "tbServerPath"
            size = New Size(&H131, 20)
            Me.tbServerPath.Size = size
            Me.tbServerPath.TabIndex = 4
            Me.tbServerPath.Text = MySettings.Default.sspath
            Me.tbEditorPath.DataBindings.Add(New Binding("Text", MySettings.Default, "Editor", True, DataSourceUpdateMode.OnPropertyChanged))
            point = New Point(&H57, &H13)
            Me.tbEditorPath.Location = point
            Me.tbEditorPath.Name = "tbEditorPath"
            size = New Size(&H131, 20)
            Me.tbEditorPath.Size = size
            Me.tbEditorPath.TabIndex = 2
            Me.tbEditorPath.Text = MySettings.Default.Editor
            point = New Point(6, &H30)
            Me.cmdPath.Location = point
            Me.cmdPath.Name = "cmdPath"
            size = New Size(&H4B, &H17)
            Me.cmdPath.Size = size
            Me.cmdPath.TabIndex = 3
            Me.cmdPath.Text = "Server Path"
            Me.cmdPath.UseVisualStyleBackColor = True
            Me.Label31.AutoSize = True
            point = New Point(790, 710)
            Me.Label31.Location = point
            Me.Label31.Name = "Label31"
            size = New Size(&H44, 13)
            Me.Label31.Size = size
            Me.Label31.TabIndex = &H34
            Me.Label31.Text = "Progressing :"
            point = New Point(&H360, 710)
            Me.pbWorking.Location = point
            Me.pbWorking.Name = "pbWorking"
            size = New Size(&HBC, 13)
            Me.pbWorking.Size = size
            Me.pbWorking.TabIndex = &H33
            Me.Mapsfound.AutoSize = True
            point = New Point(500, 710)
            Me.Mapsfound.Location = point
            Me.Mapsfound.Name = "Mapsfound"
            size = New Size(13, 13)
            Me.Mapsfound.Size = size
            Me.Mapsfound.TabIndex = &H33
            Me.Mapsfound.Text = "0"
            Me.ItemFound.AutoSize = True
            point = New Point(&H184, 710)
            Me.ItemFound.Location = point
            Me.ItemFound.Name = "ItemFound"
            size = New Size(13, 13)
            Me.ItemFound.Size = size
            Me.ItemFound.TabIndex = 50
            Me.ItemFound.Text = "0"
            Me.MoFound.AutoSize = True
            point = New Point(&H11D, 710)
            Me.MoFound.Location = point
            Me.MoFound.Name = "MoFound"
            size = New Size(13, 13)
            Me.MoFound.Size = size
            Me.MoFound.TabIndex = &H31
            Me.MoFound.Text = "0"
            Me.Label40.AutoSize = True
            Me.Label40.Cursor = Cursors.Hand
            point = New Point(&H1AC, 710)
            Me.Label40.Location = point
            Me.Label40.Name = "Label40"
            size = New Size(&H42, 13)
            Me.Label40.Size = size
            Me.Label40.TabIndex = &H30
            Me.Label40.Text = "Maps found:"
            Me.Label39.AutoSize = True
            Me.Label39.Cursor = Cursors.Hand
            point = New Point(320, 710)
            Me.Label39.Location = point
            Me.Label39.Name = "Label39"
            size = New Size(&H41, 13)
            Me.Label39.Size = size
            Me.Label39.TabIndex = &H2F
            Me.Label39.Text = "Items found:"
            Me.Label38.AutoSize = True
            Me.Label38.Cursor = Cursors.Hand
            point = New Point(&HC4, 710)
            Me.Label38.Location = point
            Me.Label38.Name = "Label38"
            size = New Size(&H53, 13)
            Me.Label38.Size = size
            Me.Label38.TabIndex = &H2E
            Me.Label38.Text = "Monsters found:"
            Me.lblprgV.AutoSize = True
            point = New Point(13, 710)
            Me.lblprgV.Location = point
            Me.lblprgV.Name = "lblprgV"
            size = New Size(&H30, 13)
            Me.lblprgV.Size = size
            Me.lblprgV.TabIndex = &H2D
            Me.lblprgV.Text = "PriTaTor"
            Me.dlgFile.Filter = "File.exe|*.exe"
            Me.dlgFolder.SelectedPath = "c:"
            Me.lblTextCoding.AutoSize = True
            point = New Point(&H218, 710)
            Me.lblTextCoding.Location = point
            Me.lblTextCoding.Name = "lblTextCoding"
            size = New Size(&H20, 13)
            Me.lblTextCoding.Size = size
            Me.lblTextCoding.TabIndex = &H35
            Me.lblTextCoding.Text = "Code"
            Me.ttAll.AutoPopDelay = &H1388
            Me.ttAll.InitialDelay = 50
            Me.ttAll.ReshowDelay = 100
            Me.ttAll.UseAnimation = False
            Me.ttAll.UseFading = False
            Me.ListBox1.FormattingEnabled = True
            point = New Point(7, &H25)
            Me.ListBox1.Location = point
            Me.ListBox1.Name = "ListBox1"
            Me.ListBox1.SelectionMode = SelectionMode.MultiExtended
            size = New Size(&H9D, 550)
            Me.ListBox1.Size = size
            Me.ListBox1.TabIndex = 3
            Me.Label95.AutoSize = True
            point = New Point(7, &H10)
            Me.Label95.Location = point
            Me.Label95.Name = "Label95"
            size = New Size(&H27, 13)
            Me.Label95.Size = size
            Me.Label95.TabIndex = 4
            Me.Label95.Text = "Label1"
            Me.Label117.AutoSize = True
            point = New Point(&H35D, &H2B6)
            Me.Label117.Location = point
            Me.Label117.Name = "Label117"
            size = New Size(&H41, 13)
            Me.Label117.Size = size
            Me.Label117.TabIndex = &H36
            Me.Label117.Text = "Progressing:"
            Me.lblProg.AutoSize = True
            point = New Point(&H3A4, &H2B6)
            Me.lblProg.Location = point
            Me.lblProg.Name = "lblProg"
            size = New Size(&H2C, 13)
            Me.lblProg.Size = size
            Me.lblProg.TabIndex = &H37
            Me.lblProg.Text = "Nothing"
            Dim ef As New SizeF(6!, 13!)
            Me.AutoScaleDimensions = ef
            Me.AutoScaleMode = AutoScaleMode.Font
            size = New Size(&H430, &H2DE)
            Me.ClientSize = size
            Me.Controls.Add(Me.lblProg)
            Me.Controls.Add(Me.Label117)
            Me.Controls.Add(Me.Mapsfound)
            Me.Controls.Add(Me.Label31)
            Me.Controls.Add(Me.lblTextCoding)
            Me.Controls.Add(Me.ItemFound)
            Me.Controls.Add(Me.MoFound)
            Me.Controls.Add(Me.Label40)
            Me.Controls.Add(Me.pbWorking)
            Me.Controls.Add(Me.Label39)
            Me.Controls.Add(Me.lblprgV)
            Me.Controls.Add(Me.Label38)
            Me.Controls.Add(Me.TabControl1)
            size = New Size(&H438, 800)
            Me.MaximumSize = size
            size = New Size(&H438, &H300)
            Me.MinimumSize = size
            Me.Name = "PriTaEditor"
            Me.Text = "Form1"
            Me.cnMonsterFiles.ResumeLayout(False)
            Me.GroupBox1.ResumeLayout(False)
            Me.GroupBox1.PerformLayout
            Me.GroupBox2.ResumeLayout(False)
            Me.GroupBox2.PerformLayout
            Me.GroupBox3.ResumeLayout(False)
            Me.GroupBox3.PerformLayout
            Me.cmsDrops.ResumeLayout(False)
            Me.GroupBox4.ResumeLayout(False)
            Me.GroupBox4.PerformLayout
            Me.TabControl1.ResumeLayout(False)
            Me.TabPage1.ResumeLayout(False)
            Me.TabPage1.PerformLayout
            Me.GroupBox5.ResumeLayout(False)
            Me.GroupBox5.PerformLayout
            Me.cmMonsterItem.ResumeLayout(False)
            Me.TabPage2.ResumeLayout(False)
            Me.TabPage2.PerformLayout
            Me.GroupBox20.ResumeLayout(False)
            Me.GroupBox20.PerformLayout
            Me.cmItemsMonster.ResumeLayout(False)
            Me.CMFilterSaver.ResumeLayout(False)
            Me.GroupBox19.ResumeLayout(False)
            Me.GroupBox19.PerformLayout
            Me.GroupBox18.ResumeLayout(False)
            Me.GroupBox18.PerformLayout
            Me.GroupBox17.ResumeLayout(False)
            Me.GroupBox17.PerformLayout
            Me.GroupBox16.ResumeLayout(False)
            Me.GroupBox16.PerformLayout
            Me.GroupBox15.ResumeLayout(False)
            Me.GroupBox15.PerformLayout
            Me.GroupBox14.ResumeLayout(False)
            Me.GroupBox14.PerformLayout
            Me.GroupBox13.ResumeLayout(False)
            Me.GroupBox13.PerformLayout
            Me.GroupBox12.ResumeLayout(False)
            Me.GroupBox12.PerformLayout
            Me.GroupBox11.ResumeLayout(False)
            Me.GroupBox11.PerformLayout
            Me.GroupBox10.ResumeLayout(False)
            Me.GroupBox10.PerformLayout
            Me.GroupBox9.ResumeLayout(False)
            Me.GroupBox9.PerformLayout
            Me.GroupBox8.ResumeLayout(False)
            Me.GroupBox8.PerformLayout
            Me.GroupBox6.ResumeLayout(False)
            Me.GroupBox6.PerformLayout
            Me.cmFileListItems.ResumeLayout(False)
            Me.TabPage3.ResumeLayout(False)
            Me.CMSMapBoss.ResumeLayout(False)
            Me.gb24.ResumeLayout(False)
            Me.gb24.PerformLayout
            Me.CMSMapMonsterToAdd.ResumeLayout(False)
            Me.GroupBox22.ResumeLayout(False)
            Me.GroupBox22.PerformLayout
            Me.CMSMonsterInMap.ResumeLayout(False)
            Me.GroupBox21.ResumeLayout(False)
            Me.GroupBox21.PerformLayout
            Me.cmMapsFiles.ResumeLayout(False)
            Me.TabPage5.ResumeLayout(False)
            Me.TabPage5.PerformLayout
            Me.GroupBox23.ResumeLayout(False)
            Me.GroupBox23.PerformLayout
            Me.CMSAddShopItem.ResumeLayout(False)
            DirectCast(Me.PictureBox1, ISupportInitialize).EndInit
            Me.CMNPCPicturebox.ResumeLayout(False)
            Me.CMSNPCList.ResumeLayout(False)
            Me.TabPage4.ResumeLayout(False)
            Me.GroupBox7.ResumeLayout(False)
            Me.GroupBox7.PerformLayout
            Me.Settings.ResumeLayout(False)
            Me.Settings.PerformLayout
            Me.ResumeLayout(False)
            Me.PerformLayout
        End Sub

        Public Sub ItemAuswertung(ByVal SelectedItem As Long)
            Me.tbItmAbs.Text = ""
            Me.tbItmCode.Text = ""
            Me.tbItmJpName.Text = ""
            Me.tbItmName.Text = ""
            Me.tbItmQuest.Text = ""
            Me.tbItmGlow.Text = ""
            Me.tbItmIntegrity.Text = ""
            Me.tbItmWeight.Text = ""
            Me.tbItmPrice.Text = ""
            Me.tbItmOrganic.Text = ""
            Me.tbItmFire.Text = ""
            Me.tbItmFrost.Text = ""
            Me.tbItmLighting.Text = ""
            Me.tbItmPoision.Text = ""
            Me.tbItmHPRec.Text = ""
            Me.tbItmManaRec.Text = ""
            Me.tbItmStmRec.Text = ""
            Me.tbItmPots.Text = ""
            Me.tbItmAtkPow.Text = ""
            Me.tbItmRange.Text = ""
            Me.tbItmSpeed.Text = ""
            Me.tbItmAtkRtg.Text = ""
            Me.tbItmreqHP.Text = ""
            Me.tbItmAgi.Text = ""
            Me.tbItmTalent.Text = ""
            Me.tbItmSpirit.Text = ""
            Me.tbItmStr.Text = ""
            Me.tbItmLevel.Text = ""
            Me.tbItmAPT.Text = ""
            Me.tbItmMPAdd.Text = ""
            Me.tbItmHPAdd.Text = ""
            Me.tbItmSTMRegen.Text = ""
            Me.tbItmMPRegen.Text = ""
            Me.tbItmHPRegen.Text = ""
            Me.tbItmRun.Text = ""
            Me.tbItmSPRange.Text = ""
            Me.tbItmSPRun.Text = ""
            Me.tbItmSPMp.Text = ""
            Me.tbItmSPhp.Text = ""
            Me.tbItmSPblk.Text = ""
            Me.tbItmCrtRtg.Text = ""
            Me.tbItmdef.Text = ""
            Me.tbItmBlk.Text = ""
            Me.tbItmSPatkSpd.Text = ""
            Me.tbItmSPCrt.Text = ""
            Me.tbItmSPLvl.Text = ""
            Me.tbItmSPRtg.Text = ""
            Me.tbItmSPabs.Text = ""
            Me.tbItmSPdef.Text = ""
            Me.chPriPrs.Checked = False
            Me.chPriMgs.Checked = False
            Me.chPriAta.Checked = False
            Me.chPriFighter.Checked = False
            Me.chPriPike.Checked = False
            Me.chPriArcher.Checked = False
            Me.chPriKnight.Checked = False
            Me.chPriPike.Checked = False
            Me.chPriMech.Checked = False
            Me.chSecPrs.Checked = False
            Me.chSecMgs.Checked = False
            Me.chSecAta.Checked = False
            Me.chSecFighter.Checked = False
            Me.chSecPike.Checked = False
            Me.chSecArcher.Checked = False
            Me.chSecKnight.Checked = False
            Me.chSecPike.Checked = False
            Me.chSecMech.Checked = False
            Me.tbItmWeight.Text = Konstanten.ItemWeights(CInt(SelectedItem))
            Me.tbItmLevel.Text = Konstanten.ItemLevels(CInt(SelectedItem))
            Me.tbItmCode.Text = Konstanten.ItemCodes(CInt(SelectedItem))
            If Me.cbItemMo.Checked Then
                Dim num As Long
                Me.lbItemMo.Items.Clear
                Do While (Konstanten.MonsterFiles(CInt(num)) <> "")
                    Dim monsterItemInfo As String = Funktionen.GetMonsterItemInfo(num, Konstanten.ItemCodes(CInt(SelectedItem)).ToUpper)
                    If (monsterItemInfo <> "") Then
                        Me.lbItemMo.Items.Add(monsterItemInfo)
                    End If
                    num = (num + 1)
                Loop
                num = 0
            End If
            Dim i As Long = 0
            Do While (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)) <> "End of File")
                If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*") Then
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmAbs.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)) Then
                        Me.tbItmJpName.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167))).Trim
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*Name") Then
                        Me.tbItmName.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*Name")).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    Me.tbItmInGameNAme.Text = Konstanten.ItemName(CInt(SelectedItem))
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169)) Then
                        If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(187) & ChrW(246) & ChrW(187) & ChrW(243)) Then
                            Me.tbItmGlow.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(187) & ChrW(246) & ChrW(187) & ChrW(243))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                        Else
                            Me.tbItmQuest.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                        End If
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(179) & ChrW(187) & ChrW(177) & ChrW(184) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmIntegrity.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(179) & ChrW(187) & ChrW(177) & ChrW(184) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(161) & ChrW(176) & ChrW(221)) Then
                        Me.tbItmPrice.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(176) & ChrW(161) & ChrW(176) & ChrW(221))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)) Then
                        Me.tbItmOrganic.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(210)) Then
                        Me.tbItmFire.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(186) & ChrW(210))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(179) & ChrW(195) & ChrW(177) & ChrW(226)) Then
                        Me.tbItmFrost.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(179) & ChrW(195) & ChrW(177) & ChrW(226))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)) Then
                        Me.tbItmLighting.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(181) & ChrW(182)) Then
                        Me.tbItmPoision.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(181) & ChrW(182))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Me.tbItmHPRec.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Me.tbItmManaRec.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Me.tbItmStmRec.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(184) & ChrW(192) & ChrW(175) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(163)) Then
                        Me.tbItmPots.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(186) & ChrW(184) & ChrW(192) & ChrW(175) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(163))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmAtkPow.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                        Me.tbItmRange.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Me.tbItmSpeed.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmAtkRtg.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)) Then
                        Me.tbItmCrtRtg.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmdef.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                        Me.tbItmBlk.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Me.tbItmSPatkSpd.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)) Then
                        Me.tbItmSPCrt.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmSPLvl.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmSPRtg.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmSPabs.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmSPdef.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                        Me.tbItmSPblk.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Me.tbItmSPdef.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Me.tbItmSPMp.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Me.tbItmSPRun.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                        Me.tbItmSPRange.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Me.tbItmRun.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Me.tbItmHPRegen.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Me.tbItmMPRegen.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Me.tbItmSTMRegen.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Me.tbItmHPAdd.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Me.tbItmMPAdd.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Me.tbItmSTMAdd.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(184) & ChrW(182) & ChrW(185) & ChrW(253) & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(188) & ChrW(247) & ChrW(183) & ChrW(195) & ChrW(181) & ChrW(181)) Then
                        Me.tbItmAPT.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(184) & ChrW(182) & ChrW(185) & ChrW(253) & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(188) & ChrW(247) & ChrW(183) & ChrW(195) & ChrW(181) & ChrW(181))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(200) & ChrW(251)) Then
                        Me.tbItmStr.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(200) & ChrW(251))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(193) & ChrW(164) & ChrW(189) & ChrW(197) & ChrW(183) & ChrW(194)) Then
                        Me.tbItmSpirit.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(193) & ChrW(164) & ChrW(189) & ChrW(197) & ChrW(183) & ChrW(194))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(231) & ChrW(180) & ChrW(201)) Then
                        Me.tbItmTalent.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(192) & ChrW(231) & ChrW(180) & ChrW(201))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(206) & ChrW(195) & ChrW(184) & ChrW(188) & ChrW(186)) Then
                        Me.tbItmAgi.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(185) & ChrW(206) & ChrW(195) & ChrW(184) & ChrW(188) & ChrW(186))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173)) Then
                        Me.tbItmreqHP.Text = Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    If Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173)) Then
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Mechanician")) Then
                            Me.chPriMech.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Fighter")) Then
                            Me.chPriFighter.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Pikeman")) Then
                            Me.chPriPike.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Archer")) Then
                            Me.chPriArcher.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Knight")) Then
                            Me.chPriKnight.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Atalanta")) Then
                            Me.chPriAta.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Priestess")) Then
                            Me.chPriPrs.Checked = True
                        End If
                        If (Not Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Magician")) Then
                            Me.chPriMgs.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Mechanician")) Then
                            Me.chSecMech.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Fighter")) Then
                            Me.chSecFighter.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Pikeman")) Then
                            Me.chSecPike.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Archer")) Then
                            Me.chSecArcher.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Knight")) Then
                            Me.chSecKnight.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Atalanta")) Then
                            Me.chSecAta.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Priestess")) Then
                            Me.chSecPrs.Checked = True
                        End If
                        If (Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Konstanten.ItemDatenListe(CInt(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains("Magician")) Then
                            Me.chSecMgs.Checked = True
                        End If
                    End If
                End If
                i = (i + 1)
            Loop
        End Sub

        Private Sub ItemDistribToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            MyProject.Forms.ItemDistributor.Show
            Try 
                enumerator = Me.lbFileListItems.SelectedItems.GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    MyProject.Forms.ItemDistributor.ListBox1.Items.Add(Konstanten.ItemName(CInt(Funktionen.GetItemIndex(Conversions.ToString(objectValue)))))
                    MyProject.Forms.ItemDistributor.ListBox2.Items.Add(Funktionen.GetItemCode(Funktionen.GetItemIndex(Conversions.ToString(objectValue))).Replace("""", ""))
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Private Sub ItemSave(ByVal SelectedItem As String)
            Dim i As Long = 0
            Do While (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) <> "End of File")
                If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*") Then
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmAbs.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229) & ChrW(9) & Me.tbItmCode.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167) & ChrW(9) & Me.tbItmJpName.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*Name") Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*Name" & ChrW(9) & Me.tbItmName.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169)) Then
                        If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(187) & ChrW(246) & ChrW(187) & ChrW(243)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(187) & ChrW(246) & ChrW(187) & ChrW(243) & ChrW(9) & Me.tbItmGlow.Text.ToString)
                        Else
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(9) & Me.tbItmQuest.Text.ToString)
                        End If
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(179) & ChrW(187) & ChrW(177) & ChrW(184) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(179) & ChrW(187) & ChrW(177) & ChrW(184) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmIntegrity.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(171) & ChrW(176) & ChrW(212)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(185) & ChrW(171) & ChrW(176) & ChrW(212) & ChrW(9) & Me.tbItmWeight.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(161) & ChrW(176) & ChrW(221)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(176) & ChrW(161) & ChrW(176) & ChrW(221) & ChrW(9) & Me.tbItmPrice.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188) & ChrW(9) & Me.tbItmOrganic.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(210)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(186) & ChrW(210) & ChrW(9) & Me.tbItmFire.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(179) & ChrW(195) & ChrW(177) & ChrW(226)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(179) & ChrW(195) & ChrW(177) & ChrW(226) & ChrW(9) & Me.tbItmFrost.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179) & ChrW(9) & Me.tbItmLighting.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(181) & ChrW(182)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(181) & ChrW(182) & ChrW(9) & Me.tbItmPoision.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194) & ChrW(9) & Me.tbItmHPRec.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194) & ChrW(9) & Me.tbItmManaRec.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194) & ChrW(9) & Me.tbItmStmRec.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(184) & ChrW(192) & ChrW(175) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(163)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(186) & ChrW(184) & ChrW(192) & ChrW(175) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(163) & ChrW(9) & Me.tbItmPots.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmAtkPow.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174) & ChrW(9) & Me.tbItmRange.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbItmSpeed.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmAtkRtg.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195) & ChrW(9) & Me.tbItmCrtRtg.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmdef.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178) & ChrW(9) & Me.tbItmBlk.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbItmSPatkSpd.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195) & ChrW(9) & Me.tbItmSPCrt.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmSPLvl.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmSPRtg.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmSPabs.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmSPdef.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178) & ChrW(9) & Me.tbItmSPblk.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253) & ChrW(9) & Me.tbItmSPdef.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253) & ChrW(9) & Me.tbItmSPMp.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbItmSPRun.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174) & ChrW(9) & Me.tbItmSPRange.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("**" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbItmRun.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253) & ChrW(9) & Me.tbItmHPRegen.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253) & ChrW(9) & Me.tbItmMPRegen.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253) & ChrW(9) & Me.tbItmSTMRegen.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(9) & Me.tbItmHPAdd.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(9) & Me.tbItmMPAdd.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(9) & Me.tbItmSTMAdd.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(184) & ChrW(182) & ChrW(185) & ChrW(253) & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(188) & ChrW(247) & ChrW(183) & ChrW(195) & ChrW(181) & ChrW(181)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(184) & ChrW(182) & ChrW(185) & ChrW(253) & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(188) & ChrW(247) & ChrW(183) & ChrW(195) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbItmAPT.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167) & ChrW(9) & Me.tbItmLevel.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(200) & ChrW(251)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(200) & ChrW(251) & ChrW(9) & Me.tbItmStr.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(193) & ChrW(164) & ChrW(189) & ChrW(197) & ChrW(183) & ChrW(194)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(193) & ChrW(164) & ChrW(189) & ChrW(197) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbItmSpirit.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(192) & ChrW(231) & ChrW(180) & ChrW(201)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(192) & ChrW(231) & ChrW(180) & ChrW(201) & ChrW(9) & Me.tbItmTalent.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(185) & ChrW(206) & ChrW(195) & ChrW(184) & ChrW(188) & ChrW(186)) Then
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(185) & ChrW(206) & ChrW(195) & ChrW(184) & ChrW(188) & ChrW(186) & ChrW(9) & Me.tbItmAgi.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173)) Then
                        Me.tbItmreqHP.Text = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                        Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = ("*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173) & ChrW(9) & Me.tbItmreqHP.Text.ToString)
                    End If
                    If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173)) Then
                        Dim flag As Boolean
                        Dim flag2 As Boolean
                        Dim flag3 As Boolean
                        Dim flag4 As Boolean
                        Dim flag5 As Boolean
                        Dim flag6 As Boolean
                        Dim flag7 As Boolean
                        Dim flag8 As Boolean
                        Dim flag9 As Boolean
                        Dim flag10 As Boolean
                        Dim flag11 As Boolean
                        Dim flag12 As Boolean
                        Dim flag13 As Boolean
                        Dim flag14 As Boolean
                        Dim flag15 As Boolean
                        Dim flag16 As Boolean
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriMech.Checked) And Not flag6) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Mech) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag6 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Mech)
                                flag6 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriMech.Checked) And Not flag6) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Mech)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Mech, "")
                            flag6 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriArcher.Checked) And Not flag) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Ars) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Ars)
                                flag = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriArcher.Checked) And Not flag) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Ars)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Ars, "")
                            flag = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriAta.Checked) And Not flag2) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.ata) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag2 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.ata)
                                flag2 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriAta.Checked) And Not flag2) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.ata)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.ata, "")
                            flag2 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriFighter.Checked) And Not flag3) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.fs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag3 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.fs)
                                flag3 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriFighter.Checked) And Not flag3) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.fs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.fs, "")
                            flag3 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriKnight.Checked) And Not flag4) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.ks) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag4 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.ks)
                                flag4 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriKnight.Checked) And Not flag4) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.ks)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.ks, "")
                            flag4 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriMgs.Checked) And Not flag5) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.mgs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag5 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.mgs)
                                flag5 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriMgs.Checked) And Not flag5) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.mgs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.mgs, "")
                            flag5 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriPike.Checked) And Not flag7) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Ps) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag7 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Ps)
                                flag7 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriPike.Checked) And Not flag7) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.Ps)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Ps, "")
                            flag7 = True
                        End If
                        If ((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chPriPrs.Checked) And Not flag8) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.prs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag8 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.prs)
                                flag8 = True
                            End If
                        End If
                        If (((Not Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chPriPrs.Checked) And Not flag8) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173))).Contains(Konstanten.prs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.prs, "")
                            flag8 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecArcher.Checked) And Not flag9) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Ars) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag9 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Ars)
                                flag9 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecArcher.Checked) And Not flag9) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Ars)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Ars, "")
                            flag9 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecAta.Checked) And Not flag10) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.ata) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag10 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.ata)
                                flag10 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecAta.Checked) And Not flag10) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.ata)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.ata, "")
                            flag10 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecFighter.Checked) And Not flag11) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.fs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag11 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.fs)
                                flag11 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecFighter.Checked) And Not flag11) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.fs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.fs, "")
                            flag11 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecKnight.Checked) And Not flag12) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.ks) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag12 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.ks)
                                flag12 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecKnight.Checked) And Not flag12) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.ks)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.ks, "")
                            flag12 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecMech.Checked) And Not flag14) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Mech) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag14 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Mech)
                                flag14 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecMech.Checked) And Not flag14) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Mech)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Mech, "")
                            flag14 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecMgs.Checked) And Not flag13) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.mgs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag13 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.mgs)
                                flag13 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecMgs.Checked) And Not flag13) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.mgs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.mgs, "")
                            flag13 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecPike.Checked) And Not flag15) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Ps) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag15 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.Ps)
                                flag15 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecPike.Checked) And Not flag15) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.Ps)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.Ps, "")
                            flag15 = True
                        End If
                        If ((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Me.chSecPrs.Checked) And Not flag16) Then
                            If Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.prs) Then
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i))
                                flag16 = True
                            Else
                                Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = (Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) & " " & Konstanten.prs)
                                flag16 = True
                            End If
                        End If
                        If (((Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).StartsWith("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)) And Not Me.chSecPrs.Checked) And Not flag16) AndAlso Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Substring(Strings.Len("**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253))).Contains(Konstanten.prs)) Then
                            Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)) = Konstanten.ItemDatenListe(Conversions.ToInteger(SelectedItem), CInt(i)).Replace(Konstanten.prs, "")
                            flag16 = True
                        End If
                    End If
                End If
                i = (i + 1)
            Loop
            Me.ItemSaver(Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem)), True)
            Me.ItemAuswertung(Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem)))
        End Sub

        Private Sub ItemSaver(ByVal ItemIndex As Long, ByVal makebackupfile As Boolean)
            Dim num As Long = 0
            Dim str As String = Strings.Format(DateAndTime.Now.ToLocalTime, "yyyy_MM_dd_HH_mm_ss")
            If (makebackupfile AndAlso File.Exists((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemFiles(CInt(ItemIndex))))) Then
                If Not Directory.Exists((Konstanten.sPath & "GameServer\OpenItem\\" & Konstanten.ItemBackupPath)) Then
                    Directory.CreateDirectory((Konstanten.sPath & "GameServer\OpenItem\\" & Konstanten.ItemBackupPath))
                End If
                File.Copy((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemFiles(CInt(ItemIndex))), String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }))
                If File.Exists(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) })) Then
                    File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }))
                    File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }))
                ElseIf Not File.Exists(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\Default_", Konstanten.ItemFiles(CInt(ItemIndex)) })) Then
                    File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\Default_", Konstanten.ItemFiles(CInt(ItemIndex)) }))
                Else
                    File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\", Konstanten.ItemBackupPath, "\", str, Konstanten.ItemBackupNameAdd, Konstanten.ItemFiles(CInt(ItemIndex)) }))
                End If
            End If
            Dim writer As New StreamWriter((Konstanten.sPath & "GameServer\OpenItem\" & Konstanten.ItemFiles(CInt(ItemIndex))), False, Konstanten.enc)
            num = 0
            Do While (Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)) <> "End of File")
                If (Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)) <> "End of File") Then
                    writer.WriteLine(Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)))
                End If
                num = (num + 1)
            Loop
            num = 0
            writer.Close
        End Sub

        Private Sub ItemToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim monsterIndex As Long = 0
            Dim collection As New Collection
            Me.lbFiles.SelectedItems.Clear
            Try 
                Dim enumerator As IEnumerator
                Dim wert As String = Interaction.InputBox("Enter Itemcode", "", "", -1, -1)
                Do While (Konstanten.MonsterFiles(CInt(monsterIndex)) <> Nothing)
                    Dim item As String = Funktionen.FindenText(monsterIndex, "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219), wert)
                    If (item <> "") Then
                        collection.Add(item, Nothing, Nothing, Nothing)
                    End If
                    monsterIndex = (monsterIndex + 1)
                Loop
                Try 
                    enumerator = collection.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.lbFiles.SelectedItems.Add(RuntimeHelpers.GetObjectValue(objectValue))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                monsterIndex = 0
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub Label38_Click(ByVal sender As Object, ByVal e As EventArgs)
            Programmstarts.Execute(Konstanten.Explorer, (Konstanten.sPath & "GameServer\Monster\"))
        End Sub

        Private Sub Label39_Click(ByVal sender As Object, ByVal e As EventArgs)
            Programmstarts.Execute(Konstanten.Explorer, (Konstanten.sPath & "GameServer\OpenItem\"))
        End Sub

        Private Sub Label40_Click(ByVal sender As Object, ByVal e As EventArgs)
            Programmstarts.Execute(Konstanten.Explorer, (Konstanten.sPath & "GameServer\Field\"))
        End Sub

        Private Sub lbFileListItems_KeyUp(ByVal sender As Object, ByVal e As KeyEventArgs)
            Me.ItemAuswertung(Funktionen.GetItemIndex(Me.lbFileListItems.SelectedItem.ToString))
            Me.lbItemsListCount.Text = (Conversions.ToString(Me.lbFileListItems.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFileListItems.Items.Count))
        End Sub

        Private Sub lbFileListItems_MouseClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (Me.lbFileListItems.Items.Count >= 1) Then
                Me.lbItemsListCount.Text = (Conversions.ToString(Me.lbFileListItems.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFileListItems.Items.Count))
            End If
            If (Me.lbFileListItems.SelectedItems.Count >= 1) Then
                Me.ItemAuswertung(Funktionen.GetItemIndex(Me.lbFileListItems.SelectedItem.ToString))
            End If
        End Sub

        Private Sub lbFileListItems_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (Me.lbFileListItems.SelectedItems.Count >= 1) Then
                Programmstarts.Execute(Konstanten.EditorExe, (Konstanten.sPath & "GameServer\OpenItem\" & Me.lbFileListItems.SelectedItem.ToString))
            End If
        End Sub

        Private Sub lbFiles_KeyUp(ByVal sender As Object, ByVal e As KeyEventArgs)
            If (Me.lbFiles.SelectedIndex <> -1) Then
                Me.tbDrops.Text = ""
                Me.tbDroprate.Text = ""
                Me.MonsterAuswertung
                If Konstanten.CheckMap Then
                    Me.GefundenMaps
                End If
                Me.lbFound.Text = (Conversions.ToString(Me.lbFiles.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFiles.Items.Count))
            End If
        End Sub

        Private Sub lbFiles_MouseClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (Me.lbFiles.SelectedIndex <> -1) Then
                Me.tbDrops.Text = ""
                Me.tbDroprate.Text = ""
                Me.MonsterAuswertung
                If Konstanten.CheckMap Then
                    Me.GefundenMaps
                End If
                Me.lbFound.Text = (Conversions.ToString(Me.lbFiles.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFiles.Items.Count))
            End If
        End Sub

        Private Sub lbFiles_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (Me.lbFiles.SelectedIndex <> -1) Then
                Programmstarts.Execute(Konstanten.EditorExe, (Konstanten.sPath & "GameServer\Monster\" & Me.lbFiles.SelectedItem.ToString))
            End If
        End Sub

        Private Sub lbFiles_MouseDown(ByVal sender As Object, ByVal e As MouseEventArgs)
            Try 
                Me.lbFiles.Refresh
                If (e.Button = MouseButtons.Right) Then
                    Me.cnMonsterFiles.Show(DirectCast(sender, Control), e.X, e.Y)
                End If
                If (Me.lbFiles.SelectedItems.Count < 2) Then
                    Me.DropCountToolStripMenuItem1.Enabled = False
                    Me.ExperienceToolStripMenuItem1.Enabled = False
                    Me.GoldToolStripMenuItem.Enabled = False
                Else
                    Me.DropCountToolStripMenuItem1.Enabled = True
                    Me.ExperienceToolStripMenuItem1.Enabled = True
                    Me.GoldToolStripMenuItem.Enabled = True
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "lbFiles MouseDown" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub lbFiles_SelectedValueChanged(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFiles.SelectedIndex <> -1) Then
                Me.lbFound.Text = (Conversions.ToString(Me.lbFiles.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFiles.Items.Count))
            End If
        End Sub

        Private Sub lbFilesMaps_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            Programmstarts.Execute(Konstanten.EditorExe, Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbFilesMaps.SelectedItem)))
        End Sub

        Private Sub lbFilesMaps_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.MapAuswertung(Funktionen.GetMapIndex(Conversions.ToString(Me.lbFilesMaps.SelectedItem)))
        End Sub

        Private Sub lbItemFiles_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            Programmstarts.Execute(Konstanten.EditorExe, (Konstanten.sPath & "GameServer\OpenItem\" & Me.lbItemFiles.SelectedItem.ToString))
        End Sub

        Private Sub lbItemFiles_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.lbItemsRealName.SelectedIndex = Me.lbItemFiles.SelectedIndex
        End Sub

        Private Sub lbItemMo_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (Me.lbItemMo.Items.Count <> 0) Then
                Programmstarts.Execute(Konstanten.EditorExe, (Konstanten.sPath & "GameServer\Monster\" & Me.lbItemMo.SelectedItem.ToString))
            End If
        End Sub

        Private Sub lbItemsRealName_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            Me.lbItemFiles.SelectedIndex = Me.lbItemsRealName.SelectedIndex
        End Sub

        Private Sub lbMaps_MouseDoubleClick(ByVal sender As Object, ByVal e As MouseEventArgs)
            Programmstarts.Execute(Konstanten.EditorExe, (Konstanten.sPath & "GameServer\Field\" & Me.lbMaps.SelectedItem.ToString))
        End Sub

        Private Sub lbNPCList_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbNPCMapFileList.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select a map", MsgBoxStyle.OkOnly, Nothing)
            Else
                Dim enumerator As IEnumerator
                Me.readnpcInfo(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)), Me.lbNPCList.SelectedIndex)
                Me.tbNPCName.Text = Me.GetNPCName((Konstanten.sPath & Me.GetNPCSetupFile(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)), Me.lbNPCList.SelectedIndex)))
                Dim index As Integer = 0
                Do While (Konstanten.NPCFiles(index) <> Path.GetFileName(Me.tbNPCSetupfile.Text.ToUpper))
                    index += 1
                    If (index = &H3E9) Then
                        Exit Do
                    End If
                Loop
                If (index <> &H3E9) Then
                    Me.tbNPCSetupfileInI.Text = Konstanten.NPCSetupIni(index)
                End If
                index = 0
                Me.tbNPCJ_Chat.Text = ""
                Try 
                    enumerator = Me.GetNPCChat((Konstanten.sPath & Me.GetNPCSetupFile(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)), Me.lbNPCList.SelectedIndex))).GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        Me.tbNPCJ_Chat.Text = Conversions.ToString(Operators.ConcatenateObject(Operators.ConcatenateObject(Me.tbNPCJ_Chat.Text, objectValue), ChrW(13) & ChrW(10)))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                Try 
                    Konstanten.Image = DirectCast(Image.FromFile(Konstanten.imagefile), Bitmap)
                    Me.PictureBox1.Image = Konstanten.Image
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Konstanten.Image = DirectCast(Image.FromFile((Application.StartupPath & "\Maps\error.bmp")), Bitmap)
                    Me.PictureBox1.Image = Konstanten.Image
                    ProjectData.ClearProjectError
                End Try
                Me.RedrawAllNPC
                Dim num As Double = 0.0015339807878856412
                Dim sx As Double = (Math.Sin((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * 10)
                Dim sy As Double = (Math.Cos((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * -10)
                Me.FillNPCShop
                Me.Drawpoint(Conversions.ToInteger(Me.tbNPCx.Text), Conversions.ToInteger(Me.tbNPCz.Text), Brushes.Green, 2, 2, sx, sy)
                Me.PictureBox1.Refresh
            End If
        End Sub

        Private Sub lbNPCMapFileList_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbNPCMapFileList.SelectedItems.Count >= 1) Then
                Konstanten.imagefile = (Application.StartupPath & "\Maps\" & Me.lbNPCMapFileList.SelectedItem.ToString.ToUpper.Replace("ASE.SPC", "BMP"))
                Dim str As String = Me.lbNPCMapFileList.SelectedItem.ToString.ToUpper
                If (str = "fore-3.ase.spc".ToUpper) Then
                    Konstanten.Posx = -14100
                    Konstanten.Posy = -10400
                    Konstanten.TX = 44
                    Konstanten.TY = 42
                ElseIf (str = "fore-2.ase.spc".ToUpper) Then
                    Konstanten.Posx = -4350
                    Konstanten.Posy = -11050
                    Konstanten.TX = 33
                    Konstanten.TY = 33
                ElseIf (str = "fore-1.ase.spc".ToUpper) Then
                    Konstanten.Posx = 3700
                    Konstanten.Posy = -10700
                    Konstanten.TX = 32
                    Konstanten.TY = 35
                ElseIf (str = "castle.ase.spc".ToUpper) Then
                    Konstanten.Posx = 34760
                    Konstanten.Posy = -27455
                    Konstanten.TX = 28
                    Konstanten.TY = 50
                ElseIf (str = "De-3.ase.spc".ToUpper) Then
                    Konstanten.Posx = 32040
                    Konstanten.Posy = -300
                    Konstanten.TX = 40
                    Konstanten.TY = 36
                ElseIf (str = "dun-5.ase.spc".ToUpper) Then
                    Konstanten.Posx = -3650
                    Konstanten.Posy = -39500
                    Konstanten.TX = 34
                    Konstanten.TY = 40
                ElseIf (str = "forever-fall-03.ASE.spc".ToUpper) Then
                    Konstanten.Posx = -2660
                    Konstanten.Posy = 45140
                    Konstanten.TX = 36
                    Konstanten.TY = 37
                ElseIf (str = "ice_ura.ase.spc".ToUpper) Then
                    Konstanten.Posx = 31255
                    Konstanten.Posy = 24400
                    Konstanten.TX = 19
                    Konstanten.TY = 27
                ElseIf (str = "iron-1.ASE.spc".ToUpper) Then
                    Konstanten.Posx = 47800
                    Konstanten.Posy = 16900
                    Konstanten.TX = 32
                    Konstanten.TY = 45
                ElseIf (str = "iron-2.ASE.spc".ToUpper) Then
                    Konstanten.Posx = 40150
                    Konstanten.Posy = 24350
                    Konstanten.TX = 52
                    Konstanten.TY = 45
                ElseIf (str = "pilai.ase.spc".ToUpper) Then
                    Konstanten.Posx = 2050
                    Konstanten.Posy = 74350
                    Konstanten.TX = 31
                    Konstanten.TY = 40
                ElseIf (str = "ruin-1.ase.spc".ToUpper) Then
                    Konstanten.Posx = 14150
                    Konstanten.Posy = 12800
                    Konstanten.TX = 39
                    Konstanten.TY = 49
                ElseIf (str = "ruin-2.ase.spc".ToUpper) Then
                    Konstanten.Posx = 7270
                    Konstanten.Posy = 22200
                    Konstanten.TX = 45
                    Konstanten.TY = 44
                ElseIf (str = "ruin-3.ase.spc".ToUpper) Then
                    Konstanten.Posx = 2200
                    Konstanten.Posy = 10800
                    Konstanten.TX = 44
                    Konstanten.TY = 48
                ElseIf (str = "village-1.ase.spc".ToUpper) Then
                    Konstanten.Posx = 23780
                    Konstanten.Posy = -1050
                    Konstanten.TX = 28
                    Konstanten.TY = 21
                ElseIf (str = "village-2.ase.spc".ToUpper) Then
                    Konstanten.Posx = 1060
                    Konstanten.Posy = -17800
                    Konstanten.TX = 35
                    Konstanten.TY = 34
                    Konstanten.Posx = 1470
                Else
                    Konstanten.Posx = -14100
                    Konstanten.Posy = -10400
                    Konstanten.TX = 44
                    Konstanten.TY = 42
                    Konstanten.Image = DirectCast(Image.FromFile((Application.StartupPath & "\Maps\error.bmp")), Bitmap)
                End If
                Try 
                    Konstanten.Image = DirectCast(Image.FromFile(Konstanten.imagefile), Bitmap)
                    Me.PictureBox1.Image = Konstanten.Image
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Konstanten.Image = DirectCast(Image.FromFile((Application.StartupPath & "\Maps\error.bmp")), Bitmap)
                    Me.PictureBox1.Image = Konstanten.Image
                    ProjectData.ClearProjectError
                End Try
                Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
            End If
        End Sub

        Private Sub LevelToolStripMenuItem1_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim num2 As Long = 0
            Dim collection As New Collection
            Try 
                Dim num As Long
                Dim enumerator2 As IEnumerator
                Me.lbFiles.SelectedItems.Clear
                Try 
                    num = Conversions.ToLong(Interaction.InputBox("Enter Level", "", "", -1, -1))
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Interaction.MsgBox("Canceled", MsgBoxStyle.OkOnly, Nothing)
                    ProjectData.ClearProjectError
                    Return
                End Try
                Funktionen.FindenZahl("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167), CDbl(num))
                Do While (Konstanten.GefundenZahl(CInt(num2)) <> "")
                    Dim enumerator As IEnumerator
                    Try 
                        enumerator = Me.lbFiles.Items.GetEnumerator
                        Do While enumerator.MoveNext
                            Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                            If Operators.ConditionalCompareObjectEqual(objectValue, Konstanten.GefundenZahl(CInt(num2)), False) Then
                                collection.Add(RuntimeHelpers.GetObjectValue(objectValue), Nothing, Nothing, Nothing)
                            End If
                        Loop
                    Finally
                        If TypeOf enumerator Is IDisposable Then
                            TryCast(enumerator,IDisposable).Dispose
                        End If
                    End Try
                    num2 = (num2 + 1)
                Loop
                Try 
                    enumerator2 = collection.GetEnumerator
                    Do While enumerator2.MoveNext
                        Dim obj3 As Object = RuntimeHelpers.GetObjectValue(enumerator2.Current)
                        Me.lbFiles.SelectedItems.Add(RuntimeHelpers.GetObjectValue(obj3))
                    Loop
                Finally
                    If TypeOf enumerator2 Is IDisposable Then
                        TryCast(enumerator2,IDisposable).Dispose
                    End If
                End Try
                num2 = 0
                Do While (Konstanten.GefundenZahl(CInt(num2)) <> "")
                    Konstanten.GefundenZahl(CInt(num2)) = ""
                    num2 = (num2 + 1)
                Loop
            Catch exception2 As Exception
                ProjectData.SetProjectError(exception2)
                Dim exception As Exception = exception2
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Sub ListeFüllen(ByVal path As String)
            Try 
                Dim num As Integer
                Do While (Konstanten.SPCFiles(num) <> Nothing)
                    If (Konstanten.SPCFiles(num) <> "") Then
                        Me.lbNPCMapFileList.Items.Add(Konstanten.SPCFiles(num))
                    End If
                    num += 1
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(exception.Message, MsgBoxStyle.OkOnly, Nothing)
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub LoadBackupToolStripMenuItem_DropDownItemClicked(ByVal sender As Object, ByVal e As ToolStripItemClickedEventArgs)
            Funktionen.LoadBackupItem(e.ClickedItem.Text.ToString, Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem)))
            Me.ItemAuswertung(Funktionen.GetItemIndex(Conversions.ToString(Me.lbFileListItems.SelectedItem)))
        End Sub

        Private Sub LoadFilterToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ReadConfigFile
        End Sub

        Private Sub lwItems_ItemSelectionChanged(ByVal sender As Object, ByVal e As ListViewItemSelectionChangedEventArgs)
            If (Me.lbFiles.SelectedItems.Count = 0) Then
                Interaction.MsgBox("please select an monster", MsgBoxStyle.OkOnly, Nothing)
            Else
                Try 
                    If (Me.lwItems.SelectedItems.Count <> 0) Then
                        Me.tbDroprate.Text = Me.lwItems.SelectedItems.Item(0).SubItems.Item(0).Text
                        Me.tbDrops.Text = Me.lwItems.SelectedItems.Item(0).SubItems.Item(1).Text
                    End If
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                    Konstanten.ErrorText = String.Concat(New String() { "lwItems_SelectedIndexChanged" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                    Funktionen.WriteErrorLog((Konstanten.ErrorText))
                    ProjectData.ClearProjectError
                End Try
            End If
        End Sub

        Private Sub lwItems_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.lbFiles.SelectedItems.Count = 0) Then
                Interaction.MsgBox("please select an monster", MsgBoxStyle.OkOnly, Nothing)
            Else
                Try 
                    If ((Me.lwItems.SelectedItems.Count <> 0) AndAlso Me.chItemInfo.Checked) Then
                        Me.lbItemFiles.Items.Clear
                        Me.Getitems
                        Me.lblMoListName.Text = (Me.tbMoName.Text & " Filename:" & Me.lbFiles.SelectedItem.ToString)
                    End If
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                    Konstanten.ErrorText = String.Concat(New String() { "lwItems_SelectedIndexChanged" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                    Funktionen.WriteErrorLog((Konstanten.ErrorText))
                    ProjectData.ClearProjectError
                End Try
            End If
        End Sub

        Private Function MakeFileList(ByVal Filter As String) As ArrayList
            Dim list2 As ArrayList
            Dim strArray As String()
            Dim index As Integer = 0
            Dim num4 As Integer = 0
            Dim num2 As Long = 0
            Dim list As New ArrayList
            If Not Filter.Contains("=") Then
                list.Add("Error")
                list.Add("No Filter found")
                Return list
            End If
            Dim str As String = Filter.ToUpper
            Try 
                Dim monsterLVL As Long
                Dim num5 As Long
                If (str.StartsWith("LEVEL=") Or str.StartsWith("LVL=")) Then
                    If str.Contains("-") Then
                        Do While (Conversions.ToString(str.Chars(CInt(num2))) <> "=")
                            num2 = (num2 + 1)
                        Loop
                        strArray = Strings.Split(str.Remove(0, CInt((num2 + 1))), "-", -1, CompareMethod.Binary)
                        Do While (Konstanten.MonsterFiles(index) <> "")
                            monsterLVL = Funktionen.GetMonsterLVL(CLng(index))
                            Dim num6 As Long = Conversions.ToLong(strArray(0))
                            num5 = Conversions.ToLong(strArray(1))
                            If ((num6 <= monsterLVL) And (num5 >= monsterLVL)) Then
                                list.Add(Konstanten.MonsterFiles(index))
                                list2 = list
                            End If
                            num4 = 0
                            index += 1
                        Loop
                    End If
                    If str.Contains("=>") Then
                        Do While (Conversions.ToString(str.Chars(CInt(num2))) <> ">")
                            num2 = (num2 + 1)
                        Loop
                        num5 = Conversions.ToLong(str.Remove(0, CInt((num2 + 1))))
                        Do While (Konstanten.MonsterFiles(index) <> "")
                            monsterLVL = Funktionen.GetMonsterLVL(CLng(index))
                            If (num5 < monsterLVL) Then
                                list.Add(Konstanten.MonsterFiles(index))
                                list2 = list
                            End If
                            num4 = 0
                            index += 1
                        Loop
                    End If
                    If str.Contains("=<") Then
                        Do While (Conversions.ToString(str.Chars(CInt(num2))) <> "<")
                            num2 = (num2 + 1)
                        Loop
                        num5 = Conversions.ToLong(str.Remove(0, CInt((num2 + 1))))
                        Do While (Konstanten.MonsterFiles(index) <> "")
                            monsterLVL = Funktionen.GetMonsterLVL(CLng(index))
                            If (num5 > monsterLVL) Then
                                list.Add(Konstanten.MonsterFiles(index))
                                list2 = list
                            End If
                            num4 = 0
                            index += 1
                        Loop
                    End If
                End If
                If (((str.Contains("LEVEL=") And Not str.Contains("=<")) And Not str.Contains("=>")) And Not str.Contains("-")) Then
                    Do While (Conversions.ToString(str.Chars(CInt(num2))) <> "=")
                        num2 = (num2 + 1)
                    Loop
                    num5 = Conversions.ToLong(str.Remove(0, CInt((num2 + 1))))
                    Do While (Konstanten.MonsterFiles(index) <> "")
                        monsterLVL = Funktionen.GetMonsterLVL(CLng(index))
                        If (num5 = monsterLVL) Then
                            list.Add(Konstanten.MonsterFiles(index))
                            list2 = list
                        End If
                        num4 = 0
                        index += 1
                    Loop
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                list.Add("Error")
                list.Add("Check Filter")
                ProjectData.ClearProjectError
            End Try
            index = 0
            Try 
                If (str.StartsWith("NAME=") Or str.StartsWith("=")) Then
                    Do While (Conversions.ToString(str.Chars(CInt(num2))) <> "=")
                        num2 = (num2 + 1)
                    Loop
                    strArray = Strings.Split(str.Remove(0, CInt((num2 + 1))), ",", -1, CompareMethod.Binary)
                    Do While (Konstanten.MonsterFiles(index) <> Nothing)
                        If (strArray.Length = 1) Then
                            If LikeOperator.LikeString(Konstanten.MonsterName(index).Trim(New Char() { """"c }).ToUpper, ("*" & strArray(0) & "*"), CompareMethod.Binary) Then
                                list.Add(Konstanten.MonsterFiles(index))
                                list2 = list
                            End If
                        Else
                            Do
                                If LikeOperator.LikeString(Konstanten.MonsterName(index).Trim(New Char() { """"c }).ToUpper, ("*" & strArray(num4) & "*"), CompareMethod.Binary) Then
                                    list.Add(Konstanten.MonsterFiles(index))
                                    list2 = list
                                End If
                                num4 += 1
                            Loop While (num4 <> strArray.Length)
                        End If
                        num4 = 0
                        index += 1
                    Loop
                End If
            Catch exception2 As Exception
                ProjectData.SetProjectError(exception2)
                list.Add("Error")
                list.Add("Check Filter")
                ProjectData.ClearProjectError
            End Try
            If (list.Count <= 0) Then
                list.Add("Nothing found")
            End If
            list2 = list
            Me.lbFound.Text = (Conversions.ToString(Me.lbFiles.SelectedItems.Count) & "/" & Conversions.ToString(Me.lbFiles.Items.Count))
            Return list2
        End Function

        Private Sub MakeItemFileList()
            Me.lbFileListItems.Items.Clear
            Dim index As Integer = 0
            Dim num3 As Integer = 0
            Dim num As Long = 0
            Dim expression As String = Me.cbItemSelector.Text.ToUpper
            Try 
                Dim strArray As String()
                If expression.Contains("=") Then
                    Do While (Conversions.ToString(expression.Chars(CInt(num))) <> "=")
                        num = (num + 1)
                    Loop
                    strArray = Strings.Split(expression.Remove(0, CInt((num + 1))), ",", -1, CompareMethod.Binary)
                Else
                    strArray = Strings.Split(expression, ",", -1, CompareMethod.Binary)
                End If
                Do While (Konstanten.ItemFiles(index) <> "")
                    Dim str As String = Funktionen.GetItemCode(CLng(index)).Trim(New Char() { """"c }).ToUpper
                    If (strArray.Length = 1) Then
                        If str.StartsWith(strArray(0)) Then
                            Me.lbFileListItems.Items.Add(Konstanten.ItemFiles(index))
                        End If
                    Else
                        Do
                            If str.StartsWith(strArray(num3)) Then
                                Me.lbFileListItems.Items.Add(Konstanten.ItemFiles(index))
                            End If
                            num3 += 1
                        Loop While (num3 <> strArray.Length)
                    End If
                    num3 = 0
                    index += 1
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = ("MakeItemFileList" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub MakeMapFileList()
            Dim selectedIndex As Integer = Me.lbNPCMapFileList.SelectedIndex
            If (selectedIndex <> -1) Then
                Me.lbNPCMapFileList.SetSelected(selectedIndex, True)
            End If
            Dim num2 As Long = 0
            Me.lbFilesMaps.Items.Clear
            Do While (Konstanten.MapFiles(CInt(num2)) <> "")
                Me.lbFilesMaps.Items.Add(Konstanten.MapFiles(CInt(num2)))
                num2 = (num2 + 1)
            Loop
        End Sub

        Private Sub MapAuswertung(ByVal MapIndex As Long)
            Dim num As Long = 0
            Me.tbMapValue1.Clear
            Me.tbMapValue2.Clear
            Me.tbMapValue3.Clear
            Me.ListView2.Items.Clear
            Me.ListView1.Items.Clear
            Try 
                Do While (Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)) <> "End of File")
                    If Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).StartsWith("*" & ChrW(195) & ChrW(214) & ChrW(180) & ChrW(235) & ChrW(181) & ChrW(191) & ChrW(189) & ChrW(195) & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246)) Then
                        Me.tbMapValue1.Text = Strings.Replace(Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).Substring("*" & ChrW(195) & ChrW(214) & ChrW(180) & ChrW(235) & ChrW(181) & ChrW(191) & ChrW(189) & ChrW(195) & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246).Length).Trim(New Char() { ChrW(9) }), ChrW(9), " ", 1, -1, CompareMethod.Binary)
                    End If
                    If Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).StartsWith("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(176) & ChrW(163) & ChrW(176) & ChrW(221)) Then
                        Me.tbMapValue2.Text = Strings.Replace(Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).Substring("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(176) & ChrW(163) & ChrW(176) & ChrW(221).Length).Trim(New Char() { ChrW(9) }), ChrW(9), " ", 1, -1, CompareMethod.Binary)
                    End If
                    If Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).StartsWith("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246)) Then
                        Me.tbMapValue3.Text = Strings.Replace(Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).Substring("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246).Length).Trim(New Char() { ChrW(9) }), ChrW(9), " ", 1, -1, CompareMethod.Binary)
                    End If
                    If Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).StartsWith("*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218)) Then
                        Dim str As String
                        If Not Konstanten.MapDatenListe(CInt(MapIndex), CInt(num)).StartsWith("*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218) & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)) Then
                            str = Konstanten.MapDatenListe(CInt(MapIndex), CInt(num))
                            str = str.Replace("*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218), "")
                            str = str.Replace(Funktionen.Textausschnitt("""", str), "")
                            str = str.Remove(str.IndexOf(""""c), 2).Trim
                            Dim index As Integer = Array.IndexOf(Of String)(Konstanten.MonsterMapName, Funktionen.Textausschnitt("""", Konstanten.MapDatenListe(CInt(MapIndex), CInt(num))))
                            If (index <> -1) Then
                                Dim item As ListViewItem = Me.ListView2.Items.Add(Konstanten.MonsterFiles(index))
                                item.SubItems.Add(Konstanten.MonsterName(index))
                                item.SubItems.Add(str)
                                item = Nothing
                            Else
                                Dim item2 As ListViewItem = Me.ListView2.Items.Add(("Monster:<" & Funktionen.Textausschnitt("""", Konstanten.MapDatenListe(CInt(MapIndex), CInt(num))) & "> dont exist"))
                                item2.ForeColor = Color.Red
                                item2.SubItems.Add("Monster dont exist")
                                item2.SubItems.Add(str)
                                item2 = Nothing
                            End If
                        Else
                            Dim str4 As String
                            Dim str5 As String
                            Dim str7 As String
                            Dim str8 As String
                            Dim flag2 As Boolean
                            Dim num6 As Integer
                            Dim text As String = ""
                            str = Konstanten.MapDatenListe(CInt(MapIndex), CInt(num))
                            str = str.Replace("*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218) & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241), "")
                            Dim str2 As String = Funktionen.Textausschnitt("""", str)
                            Dim num5 As Integer = Array.IndexOf(Of String)(Konstanten.MonsterMapName, str2)
                            If (num5 <> -1) Then
                                str7 = Konstanten.MonsterFiles(num5)
                                str8 = Konstanten.MonsterName(num5)
                            Else
                                str7 = ("Monster <" & str2 & "> dont exist")
                                str8 = ("Monster <" & str2 & "> dont exist")
                                flag2 = True
                            End If
                            str = str.Remove(0, ((str.IndexOf(str2) + str2.Length) + 1))
                            Dim str3 As String = Funktionen.Textausschnitt("""", str)
                            num5 = Array.IndexOf(Of String)(Konstanten.MonsterMapName, str3)
                            If (num5 <> -1) Then
                                str4 = Konstanten.MonsterFiles(num5)
                                str5 = Konstanten.MonsterName(num5)
                            Else
                                str4 = ("Monster <" & str3 & "> dont exist")
                                str5 = ("Monster <" & str3 & "> dont exist")
                                flag2 = True
                            End If
                            str = str.Remove(0, ((str.IndexOf(str3) + str3.Length) + 1)).Replace(ChrW(9), " ").Trim
                            Do While Not ((str.Chars(num6) = " "c) Or (num6 = (str.Length - 1)))
                                [text] = ([text] & Conversions.ToString(str.Chars(num6)))
                                num6 += 1
                            Loop
                            Dim str9 As String = str.Remove(0, num6).Trim
                            num6 = 0
                            If flag2 Then
                                Dim item3 As ListViewItem = Me.ListView1.Items.Add(str7)
                                item3.ForeColor = Color.Red
                                item3.SubItems.Add(str8)
                                item3.SubItems.Add(str4)
                                item3.SubItems.Add(str5)
                                item3.SubItems.Add([text])
                                item3.SubItems.Add(str9)
                                item3 = Nothing
                            Else
                                Dim item4 As ListViewItem = Me.ListView1.Items.Add(str7)
                                item4.SubItems.Add(str8)
                                item4.SubItems.Add(str4)
                                item4.SubItems.Add(str5)
                                item4.SubItems.Add([text])
                                item4.SubItems.Add(str9)
                                item4 = Nothing
                            End If
                        End If
                    End If
                    num = (num + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error! :" & exception.Message), MsgBoxStyle.OkOnly, Nothing)
                Funktionen.WriteErrorLog((String.Concat(New String() { exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Sub MonsterAuswertung()
            Me.tbMoLevel.Text = ""
            Me.tbMoSpCode.Text = ""
            Me.tbMoApp.Text = ""
            Me.tbMoInt.Text = ""
            Me.tbMoChar.Text = ""
            Me.tbMoVision.Text = ""
            Me.tbMoHp.Text = ""
            Me.tbMoAtkPow.Text = ""
            Me.tbMoSKAtk.Text = ""
            Me.tbMoAtkCrit.Text = ""
            Me.tbMoAbs.Text = ""
            Me.tbMoBlk.Text = ""
            Me.tbMoDef.Text = ""
            Me.tbMoAtkSpd.Text = ""
            Me.tbMoAtkRtg.Text = ""
            Me.tbMoPAtkRtg.Text = ""
            Me.tbMoOrg.Text = ""
            Me.tbMoLtg.Text = ""
            Me.tbMoIce.Text = ""
            Me.tbMoFire.Text = ""
            Me.tbMoPoision.Text = ""
            Me.tbMoMage.Text = ""
            Me.cbMoTyp.Text = ""
            Me.tbMoMSpd.Text = ""
            Me.tbMoMTyp.Text = ""
            Me.tbMoSnd.Text = ""
            Me.tbMoExp.Text = ""
            Me.tbMoMapName.Text = ""
            Me.tbMoName.Text = ""
            Me.tbMoNoDrop.Text = ""
            Me.tbMoName.Text = ""
            Me.tbMoSize.Text = ""
            Me.cbMoBoss.Checked = False
            Konstanten.SetMoTyp = True
            Konstanten.DropIndex = 0
            Dim monsterIndex As Long = Funktionen.GetMonsterIndex(Me.lbFiles.SelectedItem.ToString)
            Dim num2 As Integer = 0
            Me.tbMoLevel.Text = Konstanten.MonsterLevels(CInt(monsterIndex))
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(monsterIndex), num2) <> "End of File")
                    If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).StartsWith("*") Then
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)) Then
                            Me.cbMoBoss.Checked = True
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226)) Then
                            Me.tbMoSize.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)) Then
                            Me.tbMoMapName.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(177) & ChrW(184) & ChrW(186) & ChrW(176) & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)) Then
                            Me.tbMoSpCode.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(177) & ChrW(184) & ChrW(186) & ChrW(176) & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(193) & ChrW(182) & ChrW(193) & ChrW(247)) Then
                            Me.tbMoApp.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(193) & ChrW(182) & ChrW(193) & ChrW(247))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(193) & ChrW(246) & ChrW(180) & ChrW(201)) Then
                            Me.tbMoInt.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(193) & ChrW(246) & ChrW(180) & ChrW(201))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(199) & ChrW(176) & ChrW(188) & ChrW(186)) Then
                            Me.tbMoChar.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(199) & ChrW(176) & ChrW(188) & ChrW(186))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(189) & ChrW(195) & ChrW(190) & ChrW(223)) Then
                            Me.tbMoVision.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(189) & ChrW(195) & ChrW(190) & ChrW(223))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194)) Then
                            Me.tbMoHp.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                            Me.tbMoMSpd.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(197) & ChrW(184) & ChrW(192) & ChrW(212)) Then
                            Me.tbMoMTyp.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(197) & ChrW(184) & ChrW(192) & ChrW(212))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(200) & ChrW(191) & ChrW(176) & ChrW(250) & ChrW(192) & ChrW(189)) Then
                            Me.tbMoSnd.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(200) & ChrW(191) & ChrW(176) & ChrW(250) & ChrW(192) & ChrW(189))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161)) Then
                            Me.tbMoExp.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183)) Then
                            If (Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183))).Trim = ChrW(181) & ChrW(240) & ChrW(184) & ChrW(213)) Then
                                Me.cbMoTyp.SelectedText = "Daemon"
                                Konstanten.SetMoTyp = False
                            End If
                            If (Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183))).Trim = ChrW(190) & ChrW(240) & ChrW(181) & ChrW(165) & ChrW(181) & ChrW(229)) Then
                                Me.cbMoTyp.SelectedText = "Undead"
                                Konstanten.SetMoTyp = False
                            End If
                            If (Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183))).Trim = ChrW(185) & ChrW(194) & ChrW(197) & ChrW(207) & ChrW(198) & ChrW(174)) Then
                                Me.cbMoTyp.SelectedText = "Mutant"
                                Konstanten.SetMoTyp = False
                            End If
                            If (Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183))).Trim = ChrW(184) & ChrW(222) & ChrW(196) & ChrW(171) & ChrW(180) & ChrW(208)) Then
                                Me.cbMoTyp.SelectedText = "Mechanic"
                                Konstanten.SetMoTyp = False
                            End If
                            If Konstanten.SetMoTyp Then
                                Me.cbMoTyp.SelectedText = "Normal"
                            End If
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                            Me.tbMoAtkSpd.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                            Me.tbMoAtkPow.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                            Me.tbMoSKAtk.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                            Me.tbMoAtkCrit.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                            Me.tbMoAtkRtg.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(198) & ChrW(175) & ChrW(188) & ChrW(246) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(252)) Then
                            Me.tbMoPAtkRtg.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(198) & ChrW(175) & ChrW(188) & ChrW(246) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(252))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                            Me.tbMoDef.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(192) & ChrW(178)) Then
                            Me.tbMoAbs.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(192) & ChrW(178))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                            Me.tbMoBlk.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)) Then
                            Me.tbMoOrg.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)) Then
                            Me.tbMoLtg.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(190) & ChrW(243) & ChrW(192) & ChrW(189)) Then
                            Me.tbMoIce.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(190) & ChrW(243) & ChrW(192) & ChrW(189))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(186) & ChrW(210)) Then
                            Me.tbMoFire.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(186) & ChrW(210))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(181) & ChrW(182)) Then
                            Me.tbMoPoision.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(181) & ChrW(182))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(184) & ChrW(197) & ChrW(193) & ChrW(247)) Then
                            Me.tbMoMage.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(184) & ChrW(197) & ChrW(193) & ChrW(247))).Trim.Trim(New Char() { ChrW(9) })
                        End If
                        Me.tbMoName.Text = Konstanten.MonsterName(CInt(monsterIndex))
                        If ((Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Contains("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)) Or Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).StartsWith("*" & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) And Not Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(206))) Then
                            If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205)) Then
                                Me.tbMoNoDrop.Text = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205))).Trim.Trim(New Char() { ChrW(9) })
                            Else
                                If Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).StartsWith("*" & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)) Then
                                    Konstanten.DropDaten(Konstanten.DropIndex) = "Extra Drop"
                                    Konstanten.DropIndex += 1
                                    Konstanten.DropDaten(Konstanten.DropIndex) = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))).Trim
                                Else
                                    Konstanten.DropDaten(Konstanten.DropIndex) = Konstanten.MonsterDatenListe(CInt(monsterIndex), num2).Substring(Strings.Len("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))).Trim
                                    Konstanten.DropDaten(Konstanten.DropIndex) = Strings.Replace(Konstanten.DropDaten(Konstanten.DropIndex), ChrW(9), " ", 1, -1, CompareMethod.Binary)
                                End If
                                Konstanten.DropIndex += 1
                            End If
                        End If
                    End If
                    num2 += 1
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = ("MonsterAuswertung" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Me.DropList
        End Sub

        Private Sub MonsterSpeichern(ByVal slindex As Long)
            Dim num As Long = 0
            Dim flag As Boolean = False
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) <> "End of File")
                    If Not flag Then
                        If Me.cbMoBoss.Checked Then
                            If Funktionen.MonsterTextFinder(slindex, "*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)) Then
                                Funktionen.SetMonsterCommandValue(slindex, "*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241), "")
                            Else
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) & ChrW(13) & ChrW(10) & "*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241))
                                Funktionen.MonsterSaver(slindex, False)
                                Funktionen.ReloadMonster(slindex)
                            End If
                        End If
                        If Funktionen.MonsterTextFinder(slindex, "*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226)) Then
                            Funktionen.SetMonsterCommandValue(slindex, "*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226), Me.tbMoSize.Text.ToString)
                        Else
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) & ChrW(13) & ChrW(10) & "*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226) & ChrW(9) & Me.tbMoSize.Text.ToString)
                            Funktionen.MonsterSaver(slindex, False)
                            Funktionen.ReloadMonster(slindex)
                        End If
                        flag = True
                    End If
                    If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).StartsWith("*") Then
                        If (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).StartsWith("*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)) And Not Me.cbMoBoss.Checked) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ""
                        End If
                        If (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).StartsWith("*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226)) And (Me.tbMoSize.Text.Length = 0)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ""
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167) & ChrW(9) & Me.tbMoMapName.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167) & ChrW(9) & Me.tbMoLevel.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(177) & ChrW(184) & ChrW(186) & ChrW(176) & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(177) & ChrW(184) & ChrW(186) & ChrW(176) & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229) & ChrW(9) & Me.tbMoSpCode.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(193) & ChrW(182) & ChrW(193) & ChrW(247)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(193) & ChrW(182) & ChrW(193) & ChrW(247) & ChrW(9) & Me.tbMoApp.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(193) & ChrW(246) & ChrW(180) & ChrW(201)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(193) & ChrW(246) & ChrW(180) & ChrW(201) & ChrW(9) & Me.tbMoInt.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(199) & ChrW(176) & ChrW(188) & ChrW(186)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(199) & ChrW(176) & ChrW(188) & ChrW(186) & ChrW(9) & Me.tbMoChar.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(189) & ChrW(195) & ChrW(190) & ChrW(223)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(189) & ChrW(195) & ChrW(190) & ChrW(223) & ChrW(9) & Me.tbMoVision.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbMoHp.Text)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbMoMSpd.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(197) & ChrW(184) & ChrW(192) & ChrW(212)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(197) & ChrW(184) & ChrW(192) & ChrW(212) & ChrW(9) & Me.tbMoMTyp.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(200) & ChrW(191) & ChrW(176) & ChrW(250) & ChrW(192) & ChrW(189)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(200) & ChrW(191) & ChrW(176) & ChrW(250) & ChrW(192) & ChrW(189) & ChrW(9) & Me.tbMoSnd.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161) & ChrW(9) & Me.tbMoExp.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183)) Then
                            If (Me.cbMoTyp.Text.Trim = "Daemon") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = "*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183) & ChrW(9) & ChrW(181) & ChrW(240) & ChrW(184) & ChrW(213)
                                Konstanten.SetMoTyp = False
                            End If
                            If (Me.cbMoTyp.Text.Trim = "Undead") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = "*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183) & ChrW(9) & ChrW(190) & ChrW(240) & ChrW(181) & ChrW(165) & ChrW(181) & ChrW(229)
                                Konstanten.SetMoTyp = False
                            End If
                            If (Me.cbMoTyp.Text.Trim = "Mutant") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = "*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183) & ChrW(9) & ChrW(185) & ChrW(194) & ChrW(197) & ChrW(207) & ChrW(198) & ChrW(174)
                                Konstanten.SetMoTyp = False
                            End If
                            If (Me.cbMoTyp.Text.Trim = "Mechanic") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = "*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183) & ChrW(9) & ChrW(184) & ChrW(222) & ChrW(196) & ChrW(171) & ChrW(180) & ChrW(208)
                                Konstanten.SetMoTyp = False
                            End If
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181) & ChrW(9) & Me.tbMoAtkSpd.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbMoAtkPow.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbMoSKAtk.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174) & ChrW(9) & Me.tbMoAtkCrit.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbMoAtkRtg.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(198) & ChrW(175) & ChrW(188) & ChrW(246) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(252)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(198) & ChrW(175) & ChrW(188) & ChrW(246) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(252) & ChrW(9) & Me.tbMoPAtkRtg.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194) & ChrW(9) & Me.tbMoDef.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(192) & ChrW(178)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(192) & ChrW(178) & ChrW(9) & Me.tbMoAbs.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178) & ChrW(9) & Me.tbMoBlk.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188) & ChrW(9) & Me.tbMoOrg.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179) & ChrW(9) & Me.tbMoLtg.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(190) & ChrW(243) & ChrW(192) & ChrW(189)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(190) & ChrW(243) & ChrW(192) & ChrW(189) & ChrW(9) & Me.tbMoIce.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(186) & ChrW(210)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(186) & ChrW(210) & ChrW(9) & Me.tbMoFire.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(181) & ChrW(182)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(181) & ChrW(182) & ChrW(9) & Me.tbMoPoision.Text.ToString)
                        End If
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(184) & ChrW(197) & ChrW(193) & ChrW(247)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(184) & ChrW(197) & ChrW(193) & ChrW(247) & ChrW(9) & Me.tbMoMage.Text.ToString)
                        End If
                    End If
                    num = (num + 1)
                Loop
                num = 0
                Dim num2 As Integer = 0
                Do While (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)) And Not Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains(ChrW(184) & ChrW(240) & ChrW(181) & ChrW(206))) Then
                        If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Substring((Strings.Len("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205)) - 1)).StartsWith(ChrW(205)) Then
                            Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205) & ChrW(9) & Me.tbMoNoDrop.Text.ToString)
                        ElseIf (num2 <= (Me.lwItems.Items.Count - 1)) Then
                            If ((Me.lwItems.Items.Item(num2).Text.Length = 0) And (Me.lwItems.Items.Item(num2).SubItems.Item(1).Text.Length = 0)) Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ""
                            Else
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = ("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(9) & Me.lwItems.Items.Item(num2).Text & " " & Me.lwItems.Items.Item(num2).SubItems.Item(1).Text)
                            End If
                            num2 += 1
                            If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("Gold") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = Strings.Replace(Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)), "Gold", ChrW(181) & ChrW(183), 1, -1, CompareMethod.Binary)
                            End If
                            If Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)).Contains("Nothing") Then
                                Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)) = Strings.Replace(Konstanten.MonsterDatenListe(CInt(slindex), CInt(num)), "Nothing", ChrW(190) & ChrW(248) & ChrW(192) & ChrW(189), 1, -1, CompareMethod.Binary)
                            End If
                        End If
                    End If
                    num = (num + 1)
                Loop
                num = 0
                Konstanten.Index = 0
                Funktionen.MonsterSaver(slindex, True)
                Funktionen.ReloadMonster(slindex)
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = ("MonsterSpeichern" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub PictureBox1_MouseLeave(ByVal sender As Object, ByVal e As EventArgs)
            If Not ((Me.lbNPCMapFileList.SelectedItems.Count < 1) Or (Me.lbNPCList.SelectedItems.Count < 1)) Then
                Me.RedrawAllNPC
            End If
        End Sub

        Private Sub PictureBox1_MouseMove(ByVal sender As Object, ByVal e As MouseEventArgs)
            If (((Me.lbNPCList.SelectedItems.Count >= 1) AndAlso Not ((Not Versioned.IsNumeric(Me.tbNPCx.Text) Or Not Versioned.IsNumeric(Me.tbNPCy.Text)) Or Not Versioned.IsNumeric(Me.tbNPCz.Text))) AndAlso File.Exists(Konstanten.imagefile)) Then
                Me.PictureBox1.Focus
                Konstanten.Image = DirectCast(Image.FromFile(Konstanten.imagefile), Bitmap)
                If (e.Button <> MouseButtons.Left) Then
                    Dim num As Double = 0.0015339807878856412
                    Dim sx As Double = (Math.Sin((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * 10)
                    Dim sy As Double = (Math.Cos((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * -10)
                    Me.PictureBox1.Image = Konstanten.Image
                    Me.Drawpoint(Conversions.ToInteger(Me.tbNPCx.Text), Conversions.ToInteger(Me.tbNPCz.Text), Brushes.Green, 2, 2, sx, sy)
                    Me.PictureBox1.Refresh
                    Me.PictureBox1.Cursor = Cursors.Default
                Else
                    Dim num4 As Double = 0.0015339807878856412
                    Dim num5 As Double = (Math.Sin((num4 * Conversions.ToDouble(Me.tbNPCangle.Text))) * 10)
                    Dim num6 As Double = (Math.Cos((num4 * Conversions.ToDouble(Me.tbNPCangle.Text))) * -10)
                    Me.PictureBox1.Cursor = Cursors.Cross
                    Me.tbNPCx.Text = Conversions.ToString(CInt(Math.Round(CDbl((Conversions.ToDouble(Me.tbNPCx.Text) - ((Konstanten.mouseposx - e.X) * (Konstanten.TX / 2)))))))
                    Me.tbNPCz.Text = Conversions.ToString(CInt(Math.Round(CDbl((Conversions.ToDouble(Me.tbNPCz.Text) - ((e.Y - Konstanten.mouseposy) * (Konstanten.TY / 2)))))))
                    Me.PictureBox1.Image = Konstanten.Image
                    Me.Drawpoint(Conversions.ToInteger(Me.tbNPCx.Text), Conversions.ToInteger(Me.tbNPCz.Text), Brushes.Green, 2, 2, num5, num6)
                End If
                Me.tbNPCx.Refresh
                Me.tbNPCz.Refresh
                Konstanten.mouseposx = e.X
                Konstanten.mouseposy = e.Y
            End If
        End Sub

        Private Sub PictureBox1_PreviewKeyDown(ByVal sender As Object, ByVal e As PreviewKeyDownEventArgs)
            Me.PictureBox1.Focus
            If (e.KeyCode = Keys.Prior) Then
                Me.tbNPCangle.Text = Conversions.ToString(CDbl((Conversions.ToDouble(Me.tbNPCangle.Text) + 8)))
            End If
            If (e.KeyCode = Keys.Next) Then
                Me.tbNPCangle.Text = Conversions.ToString(CDbl((Conversions.ToDouble(Me.tbNPCangle.Text) - 8)))
            End If
            If (Conversions.ToDouble(Me.tbNPCangle.Text) < 0) Then
                Me.tbNPCangle.Text = Conversions.ToString(&H1000)
            End If
            If (Conversions.ToDouble(Me.tbNPCangle.Text) > 4096) Then
                Me.tbNPCangle.Text = Conversions.ToString(0)
            End If
            Me.PictureBox1.Focus
            Konstanten.Image = DirectCast(Image.FromFile(Konstanten.imagefile), Bitmap)
            Dim num As Double = 0.0015339807878856412
            Dim sx As Double = (Math.Sin((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * 10)
            Dim sy As Double = (Math.Cos((num * Conversions.ToDouble(Me.tbNPCangle.Text))) * -10)
            Me.PictureBox1.Image = Konstanten.Image
            Me.Drawpoint(Conversions.ToInteger(Me.tbNPCx.Text), Conversions.ToInteger(Me.tbNPCz.Text), Brushes.Green, 2, 2, sx, sy)
            Me.PictureBox1.Refresh
            Me.PictureBox1.Cursor = Cursors.Default
        End Sub

        Private Sub PriTaEditor_Load(ByVal sender As Object, ByVal e As EventArgs)
            Konstanten.EditorExe = Me.tbEditorPath.Text
            Konstanten.sPath = Me.tbServerPath.Text.ToString
            Me.ReadConfigFile
            If (Me.tbEditorPath.Text.ToString = "") Then
                If File.Exists((Environment.GetEnvironmentVariable("windir") & "\Notepad.exe")) Then
                    MySettingsProperty.Settings.Editor = (Environment.GetEnvironmentVariable("windir") & "\Notepad.exe")
                    Me.tbEditorPath.Text = (Environment.GetEnvironmentVariable("windir") & "\Notepad.exe")
                    Konstanten.EditorExe = Me.tbEditorPath.Text
                Else
                    Interaction.MsgBox("Please check options to assign an texteditor", MsgBoxStyle.OkOnly, Nothing)
                    Funktionen.WriteErrorLog((("No texteditor found" & ChrW(13) & ChrW(10) & Environment.GetEnvironmentVariable("windir") & "\Notepad.exe")))
                End If
            End If
            Me.Text = ("PriTaTor V.1.8.857 ServerPath:" & MySettingsProperty.Settings.sspath)
        End Sub

        Public Sub ReadConfigFile()
            Try 
                Dim item As String = ""
                If Not File.Exists((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt")) Then
                    Dim stream As New FileStream((Application.StartupPath & "\PriTaTor.Config.txt"), FileMode.Create, FileAccess.Write)
                    Dim writer As New StreamWriter(stream)
                    writer.WriteLine(MySettingsProperty.Settings.Config)
                    writer.Close
                    Interaction.MsgBox("No config File found!" & ChrW(13) & ChrW(10) & "Created default config File", MsgBoxStyle.OkOnly, Nothing)
                End If
                Me.cbItemSelector.Items.Clear
                Me.cbMonsterSelector.Items.Clear
                Me.cbMonsterSelector1.Items.Clear
                Dim reader As New StreamReader((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"))
                Do While (reader.Peek <> -1)
                    item = reader.ReadLine
                    If item.ToUpper.StartsWith("ItemSelector:".ToUpper) Then
                        Do While (item <> "<End>")
                            item = reader.ReadLine
                            If (item <> "<End>") Then
                                Me.cbItemSelector.Items.Add(item)
                            End If
                        Loop
                    End If
                    If item.ToUpper.StartsWith("MonsterSelector:".ToUpper) Then
                        Do While Not ((item = "<End>") Or (reader.Peek = -1))
                            item = reader.ReadLine
                            If (item <> "<End>") Then
                                Me.cbMonsterSelector.Items.Add(item)
                                Me.cbMonsterSelector1.Items.Add(item)
                            End If
                        Loop
                    End If
                    If item.ToUpper.StartsWith("Server-Path=".ToUpper) Then
                        Konstanten.sPath = item.Substring(Strings.Len("Server-Path=".ToUpper)).Trim
                        Me.tbServerPath.Text = Konstanten.sPath
                        MySettingsProperty.Settings.sspath = Konstanten.sPath
                    End If
                    If item.ToUpper.StartsWith("Max-Exp=".ToUpper) Then
                        If Versioned.IsNumeric(item.Substring(Strings.Len("Max-Exp=".ToUpper)).Trim.ToString) Then
                            Me.tbMaxExp.Text = item.Substring(Strings.Len("Max-Exp=".ToUpper)).Trim
                            MySettingsProperty.Settings.MaxExp = Me.tbMaxExp.Text
                        Else
                            Interaction.MsgBox("Error in loading config file at command: <Max-Exp=>" & ChrW(13) & ChrW(10) & "Not numberic", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Max-Exp=>" & ChrW(13) & ChrW(10) & "Not numberic: " & item.Substring(Strings.Len("Max-Exp=".ToUpper)).Trim)))
                        End If
                    End If
                    If item.ToUpper.StartsWith("Max-Gold=".ToUpper) Then
                        If Versioned.IsNumeric(item.ToUpper.Substring(Strings.Len("Max-Gold=".ToUpper)).Trim.ToString) Then
                            Me.tbMaxGold.Text = item.Substring(Strings.Len("Max-Gold=".ToUpper)).Trim
                            MySettingsProperty.Settings.MaxGold = Me.tbMaxGold.Text
                        Else
                            Interaction.MsgBox("Error in loading config file at command: <Max-Gold=>" & ChrW(13) & ChrW(10) & "Not numberic", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Max-Gold=>" & ChrW(13) & ChrW(10) & "Not numberic: " & item.Substring(Strings.Len("Max-Gold=".ToUpper)).Trim)))
                        End If
                    End If
                    If item.ToUpper.StartsWith("Text-Editor=".ToUpper) Then
                        If File.Exists(item.Substring(Strings.Len("Text-Editor=".ToUpper)).Trim) Then
                            Me.tbEditorPath.Text = item.Substring(Strings.Len("Text-Editor=".ToUpper)).Trim
                            MySettingsProperty.Settings.Editor = Me.tbEditorPath.Text
                        Else
                            Interaction.MsgBox("Error in loading config file at command: <Text-Editor=>" & ChrW(13) & ChrW(10) & "Programm not found", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Text-Editor=>" & ChrW(13) & ChrW(10) & "Programm not found: " & item.Substring(Strings.Len("Text-Editor=".ToUpper)).Trim)))
                        End If
                    End If
                    If item.ToUpper.StartsWith("Drop-warnings=".ToUpper) Then
                        Me.tbWarnItem.Text = item.Substring(Strings.Len("Drop-warnings=".ToUpper)).Trim
                        MySettingsProperty.Settings.ItemWarn = Me.tbWarnItem.Text
                    End If
                    If item.ToUpper.StartsWith("Monster.zhoon not found=".ToUpper) Then
                        If ((item.Substring(Strings.Len("Monster.zhoon not found=".ToUpper)).ToUpper.Trim <> "TRUE") And (item.Substring(Strings.Len("Monster.zhoon not found=".ToUpper)).ToUpper.Trim <> "FALSE")) Then
                            Interaction.MsgBox("Error in loading config file at command: <Monster.zhoon not found=>", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Monster.zhoon not found=>" & ChrW(13) & ChrW(10) & "Wrong command: " & item.Substring(Strings.Len("Monster.zhoon not found=".ToUpper)).Trim)))
                        Else
                            Me.cbMoZhoonWarn.Checked = Conversions.ToBoolean(item.Substring(Strings.Len("Monster.zhoon not found=".ToUpper)).Trim)
                            MySettingsProperty.Settings.WarnMoZhoon = Conversions.ToBoolean(item.Substring(Strings.Len("Monster.zhoon not found=".ToUpper)).Trim)
                        End If
                    End If
                    If item.ToUpper.StartsWith("Monstereditor: Find maps=".ToUpper) Then
                        If ((item.Substring(Strings.Len("Monstereditor: Find maps=".ToUpper)).ToUpper.Trim <> "TRUE") And (item.Substring(Strings.Len("Monstereditor: Find maps=".ToUpper)).ToUpper.Trim <> "FALSE")) Then
                            Interaction.MsgBox("Error in loading config file at command: <Monstereditor: Find maps=>", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Monstereditor: Find maps=>" & ChrW(13) & ChrW(10) & "Wrong command: " & item.Substring(Strings.Len("Monstereditor: Find maps=".ToUpper)).Trim)))
                        Else
                            Me.chMapEn.Checked = Conversions.ToBoolean(item.Substring(Strings.Len("Monstereditor: Find maps=".ToUpper)).ToUpper.Trim)
                            MySettingsProperty.Settings.chMap = Conversions.ToBoolean(item.Substring(Strings.Len("Monstereditor: Find maps=".ToUpper)).ToUpper.Trim)
                        End If
                    End If
                    If item.ToUpper.StartsWith("Monstereditor: Find Items=".ToUpper) Then
                        If ((item.Substring(Strings.Len("Monstereditor: Find Items=".ToUpper)).ToUpper.Trim <> "TRUE") And (item.Substring(Strings.Len("Monstereditor: Find Items=".ToUpper)).ToUpper.Trim <> "FALSE")) Then
                            Interaction.MsgBox("Error in loading config file at command: <Monstereditor: Find Items=>", MsgBoxStyle.OkOnly, Nothing)
                            Funktionen.WriteErrorLog((("Error in loading config file at command: <Monstereditor: Find Items=>" & ChrW(13) & ChrW(10) & "Wrong command: " & item.Substring(Strings.Len("Monstereditor: Find Items=".ToUpper)).Trim)))
                        Else
                            Me.chItemInfo.Checked = Conversions.ToBoolean(item.Substring(Strings.Len("Monstereditor: Find Items=".ToUpper)).ToUpper.Trim)
                            MySettingsProperty.Settings.chItemInfo = Conversions.ToBoolean(item.Substring(Strings.Len("Monstereditor: Find Items=".ToUpper)).ToUpper.Trim)
                        End If
                    End If
                Loop
                Me.cbItemSelector.SelectedIndex = 0
                Me.cbMonsterSelector.SelectedIndex = 0
                Me.cbMonsterSelector1.SelectedIndex = 0
                reader.Close
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "ReadConfigFile" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub ReadNPC(ByVal Filee As String)
            Dim num6 As Integer = 0
            Dim num As Integer = &H1F8
            Dim str As String = ""
            Dim num4 As Integer = 0
            Me.lbNPCList.Items.Clear
            Do While (num6 <> &HC4E0)
                If (BitConverter.ToInt32(SentaiFile.ReadBytesInFile(Filee, CLng(num6), 4), 0) <> 0) Then
                    Dim str2 As String = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(Filee, CLng((num6 + &H68)), &H40)), &H4E4)
                    If str2.Contains(ChrW(0)) Then
                        str2 = str2.Replace(ChrW(0), "?")
                        Do While (Conversions.ToString(str2.Chars(num4)) <> "?")
                            str = (str & Conversions.ToString(str2.Chars(num4)))
                            num4 += 1
                        Loop
                    Else
                        str = str2
                    End If
                    num4 = 0
                    If (SentaiFile.GetNPCIndex(Path.GetFileName((Konstanten.sPath & str))) = -1) Then
                        Me.lbNPCList.Items.Add("NPC File not found!")
                    Else
                        Me.lbNPCList.Items.Add(Konstanten.NPCNames(SentaiFile.GetNPCIndex(Path.GetFileName((Konstanten.sPath & str)))))
                    End If
                    str = ""
                    Dim buffer As Byte() = SentaiFile.ReadBytesInFile(Filee, CLng((&H1DD + num6)), 4)
                    buffer(3) = 0
                    Dim xx As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                    If (xx < -8388607.5) Then
                        xx = BitConverter.ToInt32(buffer, 0)
                    End If
                    buffer = SentaiFile.ReadBytesInFile(Filee, CLng((&H1E5 + num6)), 4)
                    buffer(3) = 0
                    Dim yy As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                    If (yy < -8388607.5) Then
                        yy = BitConverter.ToInt32(buffer, 0)
                    End If
                    Me.Drawpoint(xx, yy, Brushes.Red, 2, 2, 0, 0)
                Else
                    Me.lbNPCList.Items.Add("Empty")
                End If
                num6 = (num6 + num)
            Loop
        End Sub

        Private Sub ReadNPC1(ByVal Filee As String)
            Dim num5 As Integer = 0
            Dim num As Integer = &H1F8
            Dim str As String = ""
            Dim num3 As Integer = 0
            Me.lbNPCList.Items.Clear
            Do While (BitConverter.ToInt32(SentaiFile.ReadBytesInFile(Filee, CLng(num5), 4), 0) <> 0)
                Dim str2 As String = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(Filee, CLng((num5 + &H68)), &H40)), &H4E4)
                If str2.Contains(ChrW(0)) Then
                    str2 = str2.Replace(ChrW(0), "?")
                    Do While (Conversions.ToString(str2.Chars(num3)) <> "?")
                        str = (str & Conversions.ToString(str2.Chars(num3)))
                        num3 += 1
                    Loop
                Else
                    str = str2
                End If
                num3 = 0
                If (SentaiFile.GetNPCIndex(Path.GetFileName((Konstanten.sPath & str))) = -1) Then
                    Me.lbNPCList.Items.Add("NPC File not found!")
                Else
                    Me.lbNPCList.Items.Add(Konstanten.NPCNames(SentaiFile.GetNPCIndex(Path.GetFileName((Konstanten.sPath & str)))))
                End If
                str = ""
                Dim buffer As Byte() = SentaiFile.ReadBytesInFile(Filee, CLng((&H1DD + num5)), 4)
                buffer(3) = 0
                Dim xx As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (xx < -8388607.5) Then
                    xx = BitConverter.ToInt32(buffer, 0)
                End If
                buffer = SentaiFile.ReadBytesInFile(Filee, CLng((&H1E5 + num5)), 4)
                buffer(3) = 0
                Dim yy As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (yy < -8388607.5) Then
                    yy = BitConverter.ToInt32(buffer, 0)
                End If
                Me.Drawpoint(xx, yy, Brushes.Red, 4, 4, 0, 0)
                num5 = (num5 + num)
            Loop
        End Sub

        Private Sub ReadNPCFast(ByVal Filee As String)
            Dim num5 As Integer = 0
            Dim num As Integer = &H1F8
            Dim str As String = ""
            Dim num3 As Integer = 0
            Me.lbNPCList.Items.Clear
            Do While (BitConverter.ToInt32(SentaiFile.ReadBytesInFile(Filee, CLng(num5), 4), 0) <> 0)
                Dim str2 As String = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(Filee, CLng((num5 + &H68)), &H40)), &H4E4)
                If str2.Contains(ChrW(0)) Then
                    str2 = str2.Replace(ChrW(0), "?")
                    Do While (Conversions.ToString(str2.Chars(num3)) <> "?")
                        str = (str & Conversions.ToString(str2.Chars(num3)))
                        num3 += 1
                    Loop
                Else
                    str = str2
                End If
                num3 = 0
                Me.lbNPCList.Items.Add(Me.GetNPCName((Konstanten.sPath & str)))
                str = ""
                Dim buffer As Byte() = SentaiFile.ReadBytesInFile(Filee, CLng((&H1DD + num5)), 4)
                buffer(3) = 0
                Dim xx As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (xx < -8388607.5) Then
                    xx = BitConverter.ToInt32(buffer, 0)
                End If
                buffer = SentaiFile.ReadBytesInFile(Filee, CLng((&H1E5 + num5)), 4)
                buffer(3) = 0
                Dim yy As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (yy < -8388607.5) Then
                    yy = BitConverter.ToInt32(buffer, 0)
                End If
                Me.Drawpoint(xx, yy, Brushes.Red, 2, 2, 0, 0)
                num5 = (num5 + num)
            Loop
        End Sub

        Public Sub readnpcInfo(ByVal file As String, ByVal NPCoffset As Integer)
            Dim num As Integer = (NPCoffset * &H1F8)
            If (BitConverter.ToInt32(SentaiFile.ReadBytesInFile(file, CLng((4 + num)), 4), 0) <> &H48470070) Then
                Me.cbNPCAktivated.Checked = False
            Else
                Me.cbNPCAktivated.Checked = True
            End If
            Me.tbNPCModelFile.Text = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(file, CLng((num + 40)), &H40)), &H4E4)
            Me.tbNPCSetupfile.Text = SUmwandlung.ByteArrayToTextString((SentaiFile.ReadBytesInFile(file, CLng((num + &H68)), &H40)), &H4E4)
            Dim buffer As Byte() = SentaiFile.ReadBytesInFile(file, CLng((&H1D8 + num)), 4)
            buffer(3) = 0
            Me.tbNPCID.Text = Conversions.ToString(BitConverter.ToInt32(buffer, 0))
            buffer = SentaiFile.ReadBytesInFile(file, CLng((&H1DD + num)), 4)
            buffer(3) = 0
            Me.tbNPCx.Text = Conversions.ToString(CInt(((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)))
            If (Conversions.ToDouble(Me.tbNPCx.Text) < -8388607.5) Then
                Me.tbNPCx.Text = Conversions.ToString(BitConverter.ToInt32(buffer, 0))
            End If
            buffer = SentaiFile.ReadBytesInFile(file, CLng((&H1E1 + num)), 4)
            buffer(3) = 0
            Me.tbNPCy.Text = Conversions.ToString(CInt(((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)))
            If (Conversions.ToDouble(Me.tbNPCy.Text) < -8388607.5) Then
                Me.tbNPCy.Text = Conversions.ToString(BitConverter.ToInt32(buffer, 0))
            End If
            buffer = SentaiFile.ReadBytesInFile(file, CLng((&H1E5 + num)), 4)
            buffer(3) = 0
            Me.tbNPCz.Text = Conversions.ToString(CInt(((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)))
            If (Conversions.ToDouble(Me.tbNPCz.Text) < -8388607.5) Then
                Me.tbNPCz.Text = Conversions.ToString(BitConverter.ToInt32(buffer, 0))
            End If
            buffer = SentaiFile.ReadBytesInFile(file, CLng((&H1EC + num)), 4)
            Me.tbNPCangle.Text = Conversions.ToString(BitConverter.ToInt32(buffer, 0))
        End Sub

        Private Sub RedrawAllNPC()
            Dim num5 As Integer = (Me.lbNPCList.Items.Count - 1)
            Dim i As Integer = 0
            Do While (i <= num5)
                Dim num As Integer = (&H1F8 * i)
                Dim path As String = Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))
                Dim buffer As Byte() = SentaiFile.ReadBytesInFile(path, CLng((&H1DD + num)), 4)
                buffer(3) = 0
                Dim xx As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (xx < -8388607.5) Then
                    xx = BitConverter.ToInt32(buffer, 0)
                End If
                buffer = SentaiFile.ReadBytesInFile(path, CLng((&H1E5 + num)), 4)
                buffer(3) = 0
                Dim yy As Integer = ((BitConverter.ToInt32(buffer, 0) - &HFFFFFF) - 1)
                If (yy < -8388607.5) Then
                    yy = BitConverter.ToInt32(buffer, 0)
                End If
                Me.Drawpoint(xx, yy, Brushes.Red, 2, 2, 0, 0)
                i += 1
            Loop
        End Sub

        Public Sub ReloadMaps()
            Do While (Konstanten.MapFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.MapFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Me.lblProg.Text = "Loading map files"
            Me.lblProg.Refresh
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Field\*.spm"), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.MapFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Me.Mapsfound.Text = Conversions.ToString(Konstanten.Anzahl)
            Me.lblProg.Text = "Reading map data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Konstanten.MapDatenListe = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Dim num3 As Integer = (Konstanten.Anzahl - 1)
            Dim i As Integer = 0
            Do While (i <= num3)
                Dim num As Double
                Dim reader As New StreamReader((Konstanten.sPath & "GameServer\Field\" & Konstanten.MapFiles(i)), Konstanten.enc)
                Konstanten.Index = 0
                Do While (reader.Peek <> -1)
                    Konstanten.MapDatenListe(i, Konstanten.Index) = reader.ReadLine
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader.ReadToEnd
                        Interaction.MsgBox(("Error in loading Map File:" & Konstanten.MapFiles(i) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Error in loading Map File:" & Konstanten.MapFiles(i) & " File to long!" & ChrW(13) & ChrW(10) & "Index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.MapDatenListe(i, Konstanten.Index) = "End of File"
                Me.lblTextCoding.Text = (reader.CurrentEncoding.HeaderName & "/" & Encoding.Default.EncodingName)
                reader.Close
                num = (num + (100 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(num))
                i += 1
            Loop
            Me.pbWorking.Value = 100
        End Sub

        Public Sub ReloadNPC()
            Do While (Konstanten.NPCFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.NPCFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Me.lblProg.Text = "Loading NPC files"
            Me.lblProg.Refresh
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCEndung), FileAttribute.Normal)
            Me.tbNPCSetupfile.Items.Clear
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.NPCFiles(Konstanten.Anzahl) = Konstanten.sFile.ToUpper
                    Me.tbNPCSetupfile.Items.Add(Konstanten.NPCFiles(Konstanten.Anzahl))
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Index = 0
            Me.lblProg.Text = "Reading NPC Data" & ChrW(180) & "s"
            Me.lblProg.Refresh
            Konstanten.NPCData = New String(((Konstanten.Anzahl - 1) + 1)  - 1, &H1F5  - 1) {}
            Me.tbNPCModelFile.Items.Clear
            Dim num3 As Integer = (Konstanten.Anzahl - 1)
            Dim i As Integer = 0
            Do While (i <= num3)
                Dim num As Double
                Dim reader As New StreamReader((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCFiles(i)), Konstanten.enc)
                Konstanten.Index = 0
                Do While (reader.Peek <> -1)
                    Konstanten.NPCData(i, Konstanten.Index) = reader.ReadLine
                    If Konstanten.NPCData(i, Konstanten.Index).StartsWith(Konstanten.NPCSetupInIErkennung) Then
                        Konstanten.NPCSetupIni(i) = Funktionen.Textausschnitt("""", Konstanten.NPCData(i, Konstanten.Index)).ToUpper
                        Me.tbNPCModelFile.Items.Add(Konstanten.NPCSetupIni(i))
                    End If
                    Konstanten.Index += 1
                    If (Konstanten.Index = &H1F3) Then
                        reader.ReadToEnd
                        Interaction.MsgBox(("Error in loading Map File:" & Konstanten.MapFiles(i) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Error in loading Map File:" & Konstanten.MapFiles(i) & " File to long!" & ChrW(13) & ChrW(10) & "Index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.NPCData(i, Konstanten.Index) = "End of File"
                Konstanten.NPCNames(i) = Me.GetNPCName((Konstanten.sPath & Konstanten.NPCPath & Konstanten.NPCFiles(i)))
                Me.lblTextCoding.Text = (reader.CurrentEncoding.HeaderName & "/" & Encoding.Default.EncodingName)
                reader.Close
                num = (num + (100 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(num))
                i += 1
            Loop
            Me.pbWorking.Value = 100
        End Sub

        Public Sub reloadSPC()
            Do While (Konstanten.SPCFiles(Konstanten.Anzahl) <> Nothing)
                Konstanten.SPCFiles(Konstanten.Anzahl) = ""
                Konstanten.Anzahl += 1
            Loop
            Konstanten.Anzahl = 0
            Konstanten.sFile = FileSystem.Dir((Konstanten.sPath & "GameServer\Field\" & Konstanten.NPCPosEndung), FileAttribute.Normal)
            Do While (Konstanten.sFile <> "")
                If ((Konstanten.sFile <> ".") And (Konstanten.sFile <> "..")) Then
                    Konstanten.SPCFiles(Konstanten.Anzahl) = Konstanten.sFile
                End If
                Konstanten.sFile = FileSystem.Dir
                Konstanten.Anzahl += 1
            Loop
            Dim num3 As Integer = 0
            Dim num5 As Integer = (Konstanten.Anzahl - 1)
            Dim i As Integer = 0
            Do While (i <= num5)
                Dim num2 As Double
                If (Konstanten.SPCFiles(i) <> "") Then
                    Dim stream As New FileStream((Konstanten.sPath & "GameServer\Field\" & Konstanten.SPCFiles(i)), FileMode.Open, FileAccess.Read)
                    Do While (stream.Position <> stream.Length)
                        Dim num As Byte = CByte(stream.ReadByte)
                        Konstanten.SPCDaten(i, num3) = num
                        num3 += 1
                    Loop
                    num3 = 0
                    stream.Close
                End If
                num2 = (num2 + (100 / CDbl(Konstanten.Anzahl)))
                Me.pbWorking.Value = CInt(Math.Round(num2))
                i += 1
            Loop
            Konstanten.Anzahl = 0
        End Sub

        Public Sub reloadThisSPC(ByVal File As String)
            Konstanten.Anzahl = 0
            Do While (Konstanten.SPCFiles(Konstanten.Anzahl) <> File)
                Konstanten.Anzahl += 1
            Loop
            Dim num2 As Integer = 0
            Dim stream As New FileStream((Konstanten.sPath & "GameServer\Field\" & Konstanten.SPCFiles(Konstanten.Anzahl)), FileMode.Open, FileAccess.Read)
            Do While (stream.Position <> stream.Length)
                Dim num As Byte = CByte(stream.ReadByte)
                Konstanten.SPCDaten(Konstanten.Anzahl, num2) = num
                num2 += 1
            Loop
            num2 = 0
            stream.Close
            Konstanten.Anzahl = 0
        End Sub

        Private Sub RemoveAllToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ListView2.Items.Clear
        End Sub

        Private Sub RemoveAllToolStripMenuItem1_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.ListView1.Items.Clear
        End Sub

        Private Sub RemoveFromListToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.cbItemSelector.Items.Remove(Me.cbItemSelector.Text)
        End Sub

        Public Sub RemoveItem(ByVal MonsterIndex As Long, ByVal ItemCode As String)
            Dim i As Long = 0
            Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)) <> "End of File")
                If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)) Or Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)).StartsWith("*" & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)).ToUpper.Contains(ItemCode.ToUpper)) Then
                    Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)) = Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(i)).ToUpper.Replace(ItemCode, "")
                End If
                i = (i + 1)
            Loop
        End Sub

        Private Sub RemoveItemToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim itemIndex As Long = Funktionen.GetItemIndex(Me.lbFileListItems.SelectedItem.ToString)
            If Funktionen.YesNo("Save Monster", "Do you want remove this Item in all selected monsters?", 1) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.lbItemMo.SelectedItems.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim monsterIndex As Long = Funktionen.GetMonsterIndex(RuntimeHelpers.GetObjectValue(enumerator.Current).ToString)
                        Me.RemoveItem(monsterIndex, Funktionen.GetItemCode(itemIndex).Trim(New Char() { """"c }))
                        Funktionen.MonsterSaver(monsterIndex, True)
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                Interaction.MsgBox(("Item " & Funktionen.GetItemCode(itemIndex).Trim(New Char() { """"c }) & " removed in all selected monsters!"), MsgBoxStyle.OkOnly, Nothing)
                Me.MakeItemFileList
                Me.lbFileListItems.SelectedItem = Konstanten.ItemFiles(CInt(itemIndex))
                Me.ItemAuswertung(itemIndex)
            Else
                Interaction.MsgBox("Monster not saved! Press reload", MsgBoxStyle.OkOnly, Nothing)
            End If
        End Sub

        Private Sub RemoveMonsterToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView2.SelectedItems.Count >= 1) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.ListView2.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                        If current.Selected Then
                            current.Remove
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub RemoveToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            Try 
                enumerator = Me.LWNPCshop.SelectedItems.GetEnumerator
                Do While enumerator.MoveNext
                    DirectCast(enumerator.Current, ListViewItem).Remove
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Public Sub SaveConfigFile()
            Dim num As Long = 0
            Dim strArray As String() = New String(&H3E9  - 1) {}
            Dim str As String = ""
            Dim reader2 As New StreamReader((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), Konstanten.enc)
            Do While (reader2.Peek <> -1)
                str = reader2.ReadToEnd
            Loop
            reader2.Close
            If Not str.Contains("Server-Path=") Then
                str = (str & ChrW(13) & ChrW(10) & "Server-Path=")
            End If
            If Not str.Contains("Max-Exp=") Then
                str = (str & ChrW(13) & ChrW(10) & "Max-Exp=")
            End If
            If Not str.Contains("Max-Gold=") Then
                str = (str & ChrW(13) & ChrW(10) & "Max-Gold=")
            End If
            If Not str.Contains("Text-Editor=") Then
                str = (str & ChrW(13) & ChrW(10) & "Text-Editor=")
            End If
            If Not str.Contains("Drop-warnings=") Then
                str = (str & ChrW(13) & ChrW(10) & "Drop-warnings=")
            End If
            If Not str.Contains("Monster.zhoon not found=") Then
                str = (str & ChrW(13) & ChrW(10) & "Monster.zhoon not found=")
            End If
            If Not str.Contains("Monstereditor: Find maps=") Then
                str = (str & ChrW(13) & ChrW(10) & "Monstereditor: Find maps=")
            End If
            If Not str.Contains("Monstereditor: Find Items=") Then
                str = (str & ChrW(13) & ChrW(10) & "Monstereditor: Find Items=")
            End If
            Dim writer2 As New StreamWriter((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), False)
            writer2.Write(str)
            writer2.Close
            Dim reader As New StreamReader((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), Konstanten.enc)
            Do While (reader.Peek <> -1)
                strArray(CInt(num)) = reader.ReadLine
                num = (num + 1)
            Loop
            reader.Close
            strArray(CInt(num)) = "End of File"
            num = 0
            Do While (strArray(CInt(num)) <> "End of File")
                If strArray(CInt(num)).ToUpper.StartsWith("Server-Path=".ToUpper) Then
                    strArray(CInt(num)) = ("Server-Path=" & Me.tbServerPath.Text)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Max-Exp=".ToUpper) Then
                    strArray(CInt(num)) = ("Max-Exp=" & Me.tbMaxExp.Text)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Max-Gold=".ToUpper) Then
                    strArray(CInt(num)) = ("Max-Gold=" & Me.tbMaxGold.Text)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Text-Editor=".ToUpper) Then
                    strArray(CInt(num)) = ("Text-Editor=" & Me.tbEditorPath.Text)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Drop-warnings=".ToUpper) Then
                    strArray(CInt(num)) = ("Drop-warnings=" & Me.tbWarnItem.Text)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Monster.zhoon not found=".ToUpper) Then
                    strArray(CInt(num)) = ("Monster.zhoon not found=" & Me.cbMoZhoonWarn.Checked.ToString)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Monstereditor: Find maps=".ToUpper) Then
                    strArray(CInt(num)) = ("Monstereditor: Find maps=" & Me.chMapEn.Checked.ToString)
                End If
                If strArray(CInt(num)).ToUpper.StartsWith("Monstereditor: Find Items=".ToUpper) Then
                    strArray(CInt(num)) = ("Monstereditor: Find Items=" & Me.chItemInfo.Checked.ToString)
                End If
                num = (num + 1)
            Loop
            num = 0
            Dim writer As New StreamWriter((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), False)
            Do While (strArray(CInt(num)) <> "End of File")
                writer.WriteLine(strArray(CInt(num)))
                num = (num + 1)
            Loop
            writer.Close
        End Sub

        Private Sub SaveFilter()
            Try 
                Dim enumerator As IEnumerator
                Dim reader As New StreamReader((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), Konstanten.enc)
                Dim contents As String = ""
                Dim left As String = ""
                Do While (reader.Peek <> -1)
                    contents = (contents & ChrW(13) & ChrW(10) & reader.ReadLine)
                Loop
                reader.Close
                Dim startIndex As Integer = (contents.ToUpper.IndexOf("ItemSelector:".ToUpper) + "ItemSelector:".Length)
                Dim count As Integer = (contents.ToUpper.IndexOf("<End>".ToUpper) - startIndex)
                contents = contents.Remove(startIndex, count)
                Try 
                    enumerator = Me.cbItemSelector.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                        left = Conversions.ToString(Operators.ConcatenateObject(left, Operators.ConcatenateObject(ChrW(13) & ChrW(10), objectValue)))
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
                left = (left & ChrW(13) & ChrW(10))
                contents = contents.Insert(startIndex, left)
                File.WriteAllText((MyProject.Application.Info.DirectoryPath & "\PriTaTor.Config.txt"), contents, Konstanten.enc)
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(exception.Message, MsgBoxStyle.OkOnly, Nothing)
                Funktionen.WriteErrorLog((String.Concat(New String() { "Error in SaveFilter" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Sub SaveMap(ByVal MapFile As String)
            If (Me.lbFilesMaps.SelectedItems.Count < 1) Then
                Interaction.MsgBox("Please select a Map", MsgBoxStyle.OkOnly, Nothing)
            Else
                Dim current As ListViewItem
                Dim monsterIndex As Integer
                Dim mapIndex As Integer = CInt(Funktionen.GetMapIndex(MapFile))
                Dim str2 As String = ""
                Dim str As String = ""
                If (Me.ListView2.Items.Count >= 1) Then
                    Dim enumerator As IEnumerator
                    Dim items As ListViewItemCollection = Me.ListView2.Items
                    Try 
                        enumerator = Me.ListView2.Items.GetEnumerator
                        Do While enumerator.MoveNext
                            current = DirectCast(enumerator.Current, ListViewItem)
                            monsterIndex = CInt(Funktionen.GetMonsterIndex(current.Text))
                            str2 = String.Concat(New String() { str2, "*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218) & ChrW(9) & """", Konstanten.MonsterMapName(monsterIndex), """" & ChrW(9) & ChrW(9), current.SubItems.Item(2).Text, ChrW(13) & ChrW(10) })
                        Loop
                    Finally
                        If TypeOf enumerator Is IDisposable Then
                            TryCast(enumerator,IDisposable).Dispose
                        End If
                    End Try
                    items = Nothing
                End If
                If (Me.ListView1.Items.Count >= 1) Then
                    Dim enumerator2 As IEnumerator
                    Dim items2 As ListViewItemCollection = Me.ListView1.Items
                    Try 
                        enumerator2 = Me.ListView1.Items.GetEnumerator
                        Do While enumerator2.MoveNext
                            current = DirectCast(enumerator2.Current, ListViewItem)
                            monsterIndex = CInt(Funktionen.GetMonsterIndex(current.Text))
                            Dim index As Integer = CInt(Funktionen.GetMonsterIndex(current.SubItems.Item(2).Text))
                            str = String.Concat(New String() { str, "*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218) & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241) & ChrW(9) & """", Konstanten.MonsterMapName(monsterIndex), """" & ChrW(9) & """", Konstanten.MonsterMapName(index), """" & ChrW(9), current.SubItems.Item(4).Text, ChrW(9), current.SubItems.Item(5).Text, ChrW(13) & ChrW(10) })
                        Loop
                    Finally
                        If TypeOf enumerator2 Is IDisposable Then
                            TryCast(enumerator2,IDisposable).Dispose
                        End If
                    End Try
                    items2 = Nothing
                End If
                Dim writer As New StreamWriter((Konstanten.sPath & "GameServer\Field\" & MapFile), False, Konstanten.enc)
                writer.WriteLine("//" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & " " & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & " " & ChrW(186) & ChrW(241) & ChrW(192) & ChrW(178) & ChrW(13) & ChrW(10))
                writer.WriteLine(("*" & ChrW(195) & ChrW(214) & ChrW(180) & ChrW(235) & ChrW(181) & ChrW(191) & ChrW(189) & ChrW(195) & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246) & ChrW(9) & Me.tbMapValue1.Text))
                writer.WriteLine("//" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(176) & ChrW(163) & ChrW(176) & ChrW(221) & " " & ChrW(185) & ChrW(252) & ChrW(192) & ChrW(167) & " 9-1 1" & ChrW(194) & ChrW(247) & ChrW(192) & ChrW(204) & ChrW(180) & ChrW(231) & " 2" & ChrW(185) & ChrW(232) & ChrW(190) & ChrW(191) & " " & ChrW(187) & ChrW(161) & ChrW(182) & ChrW(243) & ChrW(193) & ChrW(252))
                writer.WriteLine(("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(176) & ChrW(163) & ChrW(176) & ChrW(221) & ChrW(9) & Me.tbMapValue2.Text))
                writer.WriteLine(("*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246) & ChrW(9) & Me.tbMapValue3.Text & ChrW(13) & ChrW(10)))
                writer.WriteLine("//" & ChrW(9) & ChrW(9) & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & " " & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167) & "          " & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(186) & ChrW(243) & ChrW(181) & ChrW(181) & ChrW(13) & ChrW(10))
                writer.WriteLine(str2)
                writer.WriteLine(str)
                writer.Close
            End If
        End Sub

        Private Sub SaveToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Me.SaveFilter
        End Sub

        Private Sub SeachForItemNameToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            MyProject.Forms.FormItemFound.Show
        End Sub

        Private Sub SendToItemSearcherToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            Dim enumerator As IEnumerator
            MyProject.Forms.FormItemFound.Show
            Try 
                enumerator = Me.lbFileListItems.SelectedItems.GetEnumerator
                Do While enumerator.MoveNext
                    Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                    Dim index As Integer = 0
                    Do While Operators.ConditionalCompareObjectNotEqual(Konstanten.ItemFiles(index), objectValue, False)
                        index += 1
                        If (index = Konstanten.ItemFiles.Length) Then
                            Exit Do
                        End If
                    Loop
                    If (index <> Konstanten.ItemFiles.Length) Then
                        MyProject.Forms.FormItemFound.LWItemsFound.Items.Add(Konstanten.ItemCodes(index)).SubItems.Add(Konstanten.ItemName(index))
                    End If
                Loop
            Finally
                If TypeOf enumerator Is IDisposable Then
                    TryCast(enumerator,IDisposable).Dispose
                End If
            End Try
        End Sub

        Public Sub SetMonsterGold(ByVal MonsterIndex As Long, ByVal Value As String)
            Dim num2 As Long = 0
            Dim num As Long = 0
            Dim str As String = ""
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)) <> "End of File")
                    If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Contains(ChrW(181) & ChrW(183))) Then
                        Do While (Conversions.ToString(Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Chars(CInt(num))) <> ChrW(181))
                            num = (num + 1)
                        Loop
                        str = Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Remove(CInt((num + 2)), CInt(((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Length - num) - 2)))
                        Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)) = (str & ChrW(9) & Value)
                    End If
                    num2 = (num2 + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "SetMonsterGold" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub ShowToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (Me.ListView1.Items.Count >= 1) Then
                Dim enumerator As IEnumerator
                Try 
                    enumerator = Me.ListView1.Items.GetEnumerator
                    Do While enumerator.MoveNext
                        Dim current As ListViewItem = DirectCast(enumerator.Current, ListViewItem)
                        If current.Selected Then
                            current.Remove
                        End If
                    Loop
                Finally
                    If TypeOf enumerator Is IDisposable Then
                        TryCast(enumerator,IDisposable).Dispose
                    End If
                End Try
            End If
        End Sub

        Private Sub TabControl1_Selected(ByVal sender As Object, ByVal e As TabControlEventArgs)
            Try 
                If (Me.TabControl1.SelectedTab.Text = "Monsters") Then
                    Dim enumerator As IEnumerator
                    Me.lbFiles.Items.Clear
                    Try 
                        enumerator = Me.MakeFileList(Me.cbMonsterSelector.Text).GetEnumerator
                        Do While enumerator.MoveNext
                            Dim objectValue As Object = RuntimeHelpers.GetObjectValue(enumerator.Current)
                            Me.lbFiles.Items.Add(RuntimeHelpers.GetObjectValue(objectValue))
                        Loop
                    Finally
                        If TypeOf enumerator Is IDisposable Then
                            TryCast(enumerator,IDisposable).Dispose
                        End If
                    End Try
                End If
                If (Me.TabControl1.SelectedTab.Text = "Items") Then
                    Me.MakeItemFileList
                End If
                If (Me.TabControl1.SelectedTab.Text = "Maps") Then
                    Dim enumerator2 As IEnumerator
                    Me.MakeMapFileList
                    Me.ListView3.Items.Clear
                    Try 
                        enumerator2 = Me.MakeFileList(Me.cbMonsterSelector1.Text).GetEnumerator
                        Do While enumerator2.MoveNext
                            Dim monsterIndex As Integer = CInt(Funktionen.GetMonsterIndex(Conversions.ToString(RuntimeHelpers.GetObjectValue(enumerator2.Current))))
                            If (monsterIndex <> -1) Then
                                Me.ListView3.Items.Add(Konstanten.MonsterFiles(monsterIndex)).SubItems.Add(Konstanten.MonsterName(monsterIndex))
                            End If
                        Loop
                    Finally
                        If TypeOf enumerator2 Is IDisposable Then
                            TryCast(enumerator2,IDisposable).Dispose
                        End If
                    End Try
                End If
                If (Me.TabControl1.SelectedTab.Text = "NPC Editor") Then
                    Me.lbNPCMapFileList.Items.Clear
                    Me.ListeFüllen("GameServer\Field\")
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "TabControl1_selected" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Private Sub tbDroprate_KeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
            Me.lwItems.SelectedItems.Item(0).Text = Me.tbDroprate.Text
            Me.lwItems.SelectedItems.Item(0).SubItems.Item(1).Text = Me.tbDrops.Text
        End Sub

        Private Sub tbDrops_KeyPress(ByVal sender As Object, ByVal e As KeyPressEventArgs)
            If ((e.KeyChar = ChrW(13)) And (Me.lwItems.SelectedItems.Count > 0)) Then
                Me.lwItems.SelectedItems.Item(0).SubItems.Item(1).Text = Me.tbDrops.Text
                Me.lwItems.SelectedItems.Item(0).Text = Me.tbDroprate.Text
                Me.Getitems
            End If
        End Sub

        Private Sub UpToolStripMenuItem_Click(ByVal sender As Object, ByVal e As EventArgs)
            If (((Me.lbNPCList.SelectedItems.Count >= 1) AndAlso (Me.lbNPCMapFileList.SelectedItems.Count >= 1)) AndAlso (Me.lbNPCList.SelectedIndex <> 0)) Then
                Dim inhalt As Byte() = New Byte(&H1F8  - 1) {}
                Dim buffer2 As Byte() = New Byte(&H1F8  - 1) {}
                inhalt = SentaiFile.ReadBytesInFile(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem), CLng(((Me.lbNPCList.SelectedIndex - 1) * &H1F8)), &H1F8)
                buffer2 = SentaiFile.ReadBytesInFile(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem), CLng((Me.lbNPCList.SelectedIndex * &H1F8)), &H1F8)
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), (Me.lbNPCList.SelectedIndex * &H1F8), &H1F8, inhalt)
                SentaiFile.WriteBytesInFile((Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem))), ((Me.lbNPCList.SelectedIndex - 1) * &H1F8), &H1F8, buffer2)
                Dim index As Integer = (Me.lbNPCList.SelectedIndex - 1)
                Me.reloadThisSPC(Conversions.ToString(Me.lbNPCMapFileList.SelectedItem))
                Me.ReadNPC(Conversions.ToString(Operators.ConcatenateObject((Konstanten.sPath & "GameServer\Field\"), Me.lbNPCMapFileList.SelectedItem)))
                Me.lbNPCList.SetSelected(index, True)
            End If
        End Sub


        ' Properties
        Friend Overridable Property AddAsNewBossToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddAsNewBossToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddAsNewBossToolStripMenuItem_Click)
                If (Not Me._AddAsNewBossToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddAsNewBossToolStripMenuItem.Click, handler
                End If
                Me._AddAsNewBossToolStripMenuItem = WithEventsValue
                If (Not Me._AddAsNewBossToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddAsNewBossToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddDroplineToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddDroplineToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddDroplineToolStripMenuItem_Click)
                If (Not Me._AddDroplineToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddDroplineToolStripMenuItem.Click, handler
                End If
                Me._AddDroplineToolStripMenuItem = WithEventsValue
                If (Not Me._AddDroplineToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddDroplineToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddItemsToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddItemsToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddItemsToolStripMenuItem_Click)
                If (Not Me._AddItemsToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddItemsToolStripMenuItem.Click, handler
                End If
                Me._AddItemsToolStripMenuItem = WithEventsValue
                If (Not Me._AddItemsToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddItemsToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddToListToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddToListToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddToListToolStripMenuItem_Click)
                If (Not Me._AddToListToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddToListToolStripMenuItem.Click, handler
                End If
                Me._AddToListToolStripMenuItem = WithEventsValue
                If (Not Me._AddToListToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddToListToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddToMapToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddToMapToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddToMapToolStripMenuItem_Click)
                If (Not Me._AddToMapToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddToMapToolStripMenuItem.Click, handler
                End If
                Me._AddToMapToolStripMenuItem = WithEventsValue
                If (Not Me._AddToMapToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddToMapToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddToSelectedBossToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddToSelectedBossToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddToSelectedBossToolStripMenuItem_Click)
                If (Not Me._AddToSelectedBossToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddToSelectedBossToolStripMenuItem.Click, handler
                End If
                Me._AddToSelectedBossToolStripMenuItem = WithEventsValue
                If (Not Me._AddToSelectedBossToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddToSelectedBossToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property AddToSeletedBossToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._AddToSeletedBossToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.AddToSeletedBossToolStripMenuItem_Click)
                If (Not Me._AddToSeletedBossToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._AddToSeletedBossToolStripMenuItem.Click, handler
                End If
                Me._AddToSeletedBossToolStripMenuItem = WithEventsValue
                If (Not Me._AddToSeletedBossToolStripMenuItem Is Nothing) Then
                    AddHandler Me._AddToSeletedBossToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property BackupsToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._BackupsToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.BackupsToolStripMenuItem_Click)
                Dim handler2 As ToolStripItemClickedEventHandler = New ToolStripItemClickedEventHandler(AddressOf Me.BackupsToolStripMenuItem_DropDownItemClicked)
                If (Not Me._BackupsToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._BackupsToolStripMenuItem.Click, handler
                    RemoveHandler Me._BackupsToolStripMenuItem.DropDownItemClicked, handler2
                End If
                Me._BackupsToolStripMenuItem = WithEventsValue
                If (Not Me._BackupsToolStripMenuItem Is Nothing) Then
                    AddHandler Me._BackupsToolStripMenuItem.Click, handler
                    AddHandler Me._BackupsToolStripMenuItem.DropDownItemClicked, handler2
                End If
            End Set
        End Property

        Friend Overridable Property BringBackToMapToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._BringBackToMapToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.BringBackToMapToolStripMenuItem_Click)
                If (Not Me._BringBackToMapToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._BringBackToMapToolStripMenuItem.Click, handler
                End If
                Me._BringBackToMapToolStripMenuItem = WithEventsValue
                If (Not Me._BringBackToMapToolStripMenuItem Is Nothing) Then
                    AddHandler Me._BringBackToMapToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property Button3 As Button
            Get
                Return Me._Button3
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.Button3_Click_1)
                If (Not Me._Button3 Is Nothing) Then
                    RemoveHandler Me._Button3.Click, handler
                End If
                Me._Button3 = WithEventsValue
                If (Not Me._Button3 Is Nothing) Then
                    AddHandler Me._Button3.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cbItemMo As CheckBox
            Get
                Return Me._cbItemMo
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cbItemMo_Click)
                If (Not Me._cbItemMo Is Nothing) Then
                    RemoveHandler Me._cbItemMo.Click, handler
                End If
                Me._cbItemMo = WithEventsValue
                If (Not Me._cbItemMo Is Nothing) Then
                    AddHandler Me._cbItemMo.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cbItemSelector As ComboBox
            Get
                Return Me._cbItemSelector
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cbItemSelector_SelectedIndexChanged)
                Dim handler2 As KeyPressEventHandler = New KeyPressEventHandler(AddressOf Me.cbItemSelector_KeyPress)
                If (Not Me._cbItemSelector Is Nothing) Then
                    RemoveHandler Me._cbItemSelector.SelectedIndexChanged, handler
                    RemoveHandler Me._cbItemSelector.KeyPress, handler2
                End If
                Me._cbItemSelector = WithEventsValue
                If (Not Me._cbItemSelector Is Nothing) Then
                    AddHandler Me._cbItemSelector.SelectedIndexChanged, handler
                    AddHandler Me._cbItemSelector.KeyPress, handler2
                End If
            End Set
        End Property

        Friend Overridable Property cbMoBoss As CheckBox
            Get
                Return Me._cbMoBoss
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._cbMoBoss = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cbMonsterSelector As ComboBox
            Get
                Return Me._cbMonsterSelector
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Dim handler As KeyPressEventHandler = New KeyPressEventHandler(AddressOf Me.cbMonsterSelector_KeyPress)
                Dim handler2 As EventHandler = New EventHandler(AddressOf Me.cbMonsterSelector_SelectedIndexChanged)
                If (Not Me._cbMonsterSelector Is Nothing) Then
                    RemoveHandler Me._cbMonsterSelector.KeyPress, handler
                    RemoveHandler Me._cbMonsterSelector.SelectedIndexChanged, handler2
                End If
                Me._cbMonsterSelector = WithEventsValue
                If (Not Me._cbMonsterSelector Is Nothing) Then
                    AddHandler Me._cbMonsterSelector.KeyPress, handler
                    AddHandler Me._cbMonsterSelector.SelectedIndexChanged, handler2
                End If
            End Set
        End Property

        Friend Overridable Property cbMonsterSelector1 As ComboBox
            Get
                Return Me._cbMonsterSelector1
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cbMonsterSelector1_SelectedIndexChanged)
                If (Not Me._cbMonsterSelector1 Is Nothing) Then
                    RemoveHandler Me._cbMonsterSelector1.SelectedIndexChanged, handler
                End If
                Me._cbMonsterSelector1 = WithEventsValue
                If (Not Me._cbMonsterSelector1 Is Nothing) Then
                    AddHandler Me._cbMonsterSelector1.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property cbMoTyp As ComboBox
            Get
                Return Me._cbMoTyp
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._cbMoTyp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cbMoZhoonWarn As CheckBox
            Get
                Return Me._cbMoZhoonWarn
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._cbMoZhoonWarn = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cbNPCAktivated As CheckBox
            Get
                Return Me._cbNPCAktivated
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._cbNPCAktivated = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cbSelectAll As CheckBox
            Get
                Return Me._cbSelectAll
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cbSelectAll_CheckedChanged)
                If (Not Me._cbSelectAll Is Nothing) Then
                    RemoveHandler Me._cbSelectAll.CheckedChanged, handler
                End If
                Me._cbSelectAll = WithEventsValue
                If (Not Me._cbSelectAll Is Nothing) Then
                    AddHandler Me._cbSelectAll.CheckedChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property CBShopItem As ComboBox
            Get
                Return Me._CBShopItem
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.CBShopItem_SelectedIndexChanged)
                If (Not Me._CBShopItem Is Nothing) Then
                    RemoveHandler Me._CBShopItem.SelectedIndexChanged, handler
                End If
                Me._CBShopItem = WithEventsValue
                If (Not Me._CBShopItem Is Nothing) Then
                    AddHandler Me._CBShopItem.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property cbWarnMap As CheckBox
            Get
                Return Me._cbWarnMap
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._cbWarnMap = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ChangeEXPOfMapToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ChangeEXPOfMapToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Me._ChangeEXPOfMapToolStripMenuItem = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ChangeToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ChangeToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Me._ChangeToolStripMenuItem = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chItemInfo As CheckBox
            Get
                Return Me._chItemInfo
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.chItemInfo_CheckedChanged)
                If (Not Me._chItemInfo Is Nothing) Then
                    RemoveHandler Me._chItemInfo.CheckedChanged, handler
                End If
                Me._chItemInfo = WithEventsValue
                If (Not Me._chItemInfo Is Nothing) Then
                    AddHandler Me._chItemInfo.CheckedChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property chMapEn As CheckBox
            Get
                Return Me._chMapEn
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.chMapEn_CheckedChanged)
                If (Not Me._chMapEn Is Nothing) Then
                    RemoveHandler Me._chMapEn.CheckedChanged, handler
                End If
                Me._chMapEn = WithEventsValue
                If (Not Me._chMapEn Is Nothing) Then
                    AddHandler Me._chMapEn.CheckedChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property chNotFound As CheckBox
            Get
                Return Me._chNotFound
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.chNotFound_CheckedChanged)
                If (Not Me._chNotFound Is Nothing) Then
                    RemoveHandler Me._chNotFound.CheckedChanged, handler
                End If
                Me._chNotFound = WithEventsValue
                If (Not Me._chNotFound Is Nothing) Then
                    AddHandler Me._chNotFound.CheckedChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property chPriArcher As CheckBox
            Get
                Return Me._chPriArcher
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriArcher = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriAta As CheckBox
            Get
                Return Me._chPriAta
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriAta = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriFighter As CheckBox
            Get
                Return Me._chPriFighter
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriFighter = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriKnight As CheckBox
            Get
                Return Me._chPriKnight
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriKnight = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriMech As CheckBox
            Get
                Return Me._chPriMech
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriMech = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriMgs As CheckBox
            Get
                Return Me._chPriMgs
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriMgs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriPike As CheckBox
            Get
                Return Me._chPriPike
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriPike = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chPriPrs As CheckBox
            Get
                Return Me._chPriPrs
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chPriPrs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecArcher As CheckBox
            Get
                Return Me._chSecArcher
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecArcher = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecAta As CheckBox
            Get
                Return Me._chSecAta
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecAta = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecFighter As CheckBox
            Get
                Return Me._chSecFighter
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecFighter = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecKnight As CheckBox
            Get
                Return Me._chSecKnight
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecKnight = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecMech As CheckBox
            Get
                Return Me._chSecMech
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecMech = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecMgs As CheckBox
            Get
                Return Me._chSecMgs
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecMgs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecPike As CheckBox
            Get
                Return Me._chSecPike
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecPike = WithEventsValue
            End Set
        End Property

        Friend Overridable Property chSecPrs As CheckBox
            Get
                Return Me._chSecPrs
            End Get
            Set(ByVal WithEventsValue As CheckBox)
                Me._chSecPrs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cmd_Check As Button
            Get
                Return Me._cmd_Check
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmd_Check_Click)
                If (Not Me._cmd_Check Is Nothing) Then
                    RemoveHandler Me._cmd_Check.Click, handler
                End If
                Me._cmd_Check = WithEventsValue
                If (Not Me._cmd_Check Is Nothing) Then
                    AddHandler Me._cmd_Check.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property CmdCheckDrop As Button
            Get
                Return Me._CmdCheckDrop
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.CmdCheckDrop_Click)
                If (Not Me._CmdCheckDrop Is Nothing) Then
                    RemoveHandler Me._CmdCheckDrop.Click, handler
                End If
                Me._CmdCheckDrop = WithEventsValue
                If (Not Me._CmdCheckDrop Is Nothing) Then
                    AddHandler Me._CmdCheckDrop.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdCheckGold As Button
            Get
                Return Me._cmdCheckGold
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdCheckGold_Click_1)
                If (Not Me._cmdCheckGold Is Nothing) Then
                    RemoveHandler Me._cmdCheckGold.Click, handler
                End If
                Me._cmdCheckGold = WithEventsValue
                If (Not Me._cmdCheckGold Is Nothing) Then
                    AddHandler Me._cmdCheckGold.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdCheckMaps As Button
            Get
                Return Me._cmdCheckMaps
            End Get
            Set(ByVal WithEventsValue As Button)
                Me._cmdCheckMaps = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cmdConfigEdit As Button
            Get
                Return Me._cmdConfigEdit
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdConfigEdit_Click)
                If (Not Me._cmdConfigEdit Is Nothing) Then
                    RemoveHandler Me._cmdConfigEdit.Click, handler
                End If
                Me._cmdConfigEdit = WithEventsValue
                If (Not Me._cmdConfigEdit Is Nothing) Then
                    AddHandler Me._cmdConfigEdit.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdDefaultConfig As Button
            Get
                Return Me._cmdDefaultConfig
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdDefaultConfig_Click)
                If (Not Me._cmdDefaultConfig Is Nothing) Then
                    RemoveHandler Me._cmdDefaultConfig.Click, handler
                End If
                Me._cmdDefaultConfig = WithEventsValue
                If (Not Me._cmdDefaultConfig Is Nothing) Then
                    AddHandler Me._cmdDefaultConfig.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdDelBackup As Button
            Get
                Return Me._cmdDelBackup
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdDelBackup_Click)
                If (Not Me._cmdDelBackup Is Nothing) Then
                    RemoveHandler Me._cmdDelBackup.Click, handler
                End If
                Me._cmdDelBackup = WithEventsValue
                If (Not Me._cmdDelBackup Is Nothing) Then
                    AddHandler Me._cmdDelBackup.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdEditorExe As Button
            Get
                Return Me._cmdEditorExe
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdEditor_Click)
                If (Not Me._cmdEditorExe Is Nothing) Then
                    RemoveHandler Me._cmdEditorExe.Click, handler
                End If
                Me._cmdEditorExe = WithEventsValue
                If (Not Me._cmdEditorExe Is Nothing) Then
                    AddHandler Me._cmdEditorExe.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdItemRealName As Button
            Get
                Return Me._cmdItemRealName
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdItemRealName_Click)
                If (Not Me._cmdItemRealName Is Nothing) Then
                    RemoveHandler Me._cmdItemRealName.Click, handler
                End If
                Me._cmdItemRealName = WithEventsValue
                If (Not Me._cmdItemRealName Is Nothing) Then
                    AddHandler Me._cmdItemRealName.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdItemSave As Button
            Get
                Return Me._cmdItemSave
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdItemSave_Click)
                If (Not Me._cmdItemSave Is Nothing) Then
                    RemoveHandler Me._cmdItemSave.Click, handler
                End If
                Me._cmdItemSave = WithEventsValue
                If (Not Me._cmdItemSave Is Nothing) Then
                    AddHandler Me._cmdItemSave.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdLoadConfig As Button
            Get
                Return Me._cmdLoadConfig
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdLoadConfig_Click)
                If (Not Me._cmdLoadConfig Is Nothing) Then
                    RemoveHandler Me._cmdLoadConfig.Click, handler
                End If
                Me._cmdLoadConfig = WithEventsValue
                If (Not Me._cmdLoadConfig Is Nothing) Then
                    AddHandler Me._cmdLoadConfig.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdMapReload As Button
            Get
                Return Me._cmdMapReload
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdReload1_Click)
                If (Not Me._cmdMapReload Is Nothing) Then
                    RemoveHandler Me._cmdMapReload.Click, handler
                End If
                Me._cmdMapReload = WithEventsValue
                If (Not Me._cmdMapReload Is Nothing) Then
                    AddHandler Me._cmdMapReload.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdMapSave As Button
            Get
                Return Me._cmdMapSave
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdMapSave_Click)
                If (Not Me._cmdMapSave Is Nothing) Then
                    RemoveHandler Me._cmdMapSave.Click, handler
                End If
                Me._cmdMapSave = WithEventsValue
                If (Not Me._cmdMapSave Is Nothing) Then
                    AddHandler Me._cmdMapSave.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdMoRealName As Button
            Get
                Return Me._cmdMoRealName
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.Button3_Click)
                If (Not Me._cmdMoRealName Is Nothing) Then
                    RemoveHandler Me._cmdMoRealName.Click, handler
                End If
                Me._cmdMoRealName = WithEventsValue
                If (Not Me._cmdMoRealName Is Nothing) Then
                    AddHandler Me._cmdMoRealName.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdNPCReload As Button
            Get
                Return Me._cmdNPCReload
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdNPCReload_Click)
                If (Not Me._cmdNPCReload Is Nothing) Then
                    RemoveHandler Me._cmdNPCReload.Click, handler
                End If
                Me._cmdNPCReload = WithEventsValue
                If (Not Me._cmdNPCReload Is Nothing) Then
                    AddHandler Me._cmdNPCReload.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdNPCSave As Button
            Get
                Return Me._cmdNPCSave
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdNPCSave_Click)
                If (Not Me._cmdNPCSave Is Nothing) Then
                    RemoveHandler Me._cmdNPCSave.Click, handler
                End If
                Me._cmdNPCSave = WithEventsValue
                If (Not Me._cmdNPCSave Is Nothing) Then
                    AddHandler Me._cmdNPCSave.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property CMDNPCShopSave As Button
            Get
                Return Me._CMDNPCShopSave
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.CMDNPCShopSave_Click)
                If (Not Me._CMDNPCShopSave Is Nothing) Then
                    RemoveHandler Me._CMDNPCShopSave.Click, handler
                End If
                Me._CMDNPCShopSave = WithEventsValue
                If (Not Me._CMDNPCShopSave Is Nothing) Then
                    AddHandler Me._CMDNPCShopSave.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdPath As Button
            Get
                Return Me._cmdPath
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdPath_Click_1)
                If (Not Me._cmdPath Is Nothing) Then
                    RemoveHandler Me._cmdPath.Click, handler
                End If
                Me._cmdPath = WithEventsValue
                If (Not Me._cmdPath Is Nothing) Then
                    AddHandler Me._cmdPath.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdReload As Button
            Get
                Return Me._cmdReload
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdReload1_Click)
                If (Not Me._cmdReload Is Nothing) Then
                    RemoveHandler Me._cmdReload.Click, handler
                End If
                Me._cmdReload = WithEventsValue
                If (Not Me._cmdReload Is Nothing) Then
                    AddHandler Me._cmdReload.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdReload1 As Button
            Get
                Return Me._cmdReload1
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdReload1_Click)
                If (Not Me._cmdReload1 Is Nothing) Then
                    RemoveHandler Me._cmdReload1.Click, handler
                End If
                Me._cmdReload1 = WithEventsValue
                If (Not Me._cmdReload1 Is Nothing) Then
                    AddHandler Me._cmdReload1.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdSave As Button
            Get
                Return Me._cmdSave
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdSave_Click)
                If (Not Me._cmdSave Is Nothing) Then
                    RemoveHandler Me._cmdSave.Click, handler
                End If
                Me._cmdSave = WithEventsValue
                If (Not Me._cmdSave Is Nothing) Then
                    AddHandler Me._cmdSave.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdSaveConfig As Button
            Get
                Return Me._cmdSaveConfig
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdSaveConfig_Click)
                If (Not Me._cmdSaveConfig Is Nothing) Then
                    RemoveHandler Me._cmdSaveConfig.Click, handler
                End If
                Me._cmdSaveConfig = WithEventsValue
                If (Not Me._cmdSaveConfig Is Nothing) Then
                    AddHandler Me._cmdSaveConfig.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmdShowLog As Button
            Get
                Return Me._cmdShowLog
            End Get
            Set(ByVal WithEventsValue As Button)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.cmdShowLog_Click)
                If (Not Me._cmdShowLog Is Nothing) Then
                    RemoveHandler Me._cmdShowLog.Click, handler
                End If
                Me._cmdShowLog = WithEventsValue
                If (Not Me._cmdShowLog Is Nothing) Then
                    AddHandler Me._cmdShowLog.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmFileListItems As ContextMenuStrip
            Get
                Return Me._cmFileListItems
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.cmFileListItems_Opening)
                If (Not Me._cmFileListItems Is Nothing) Then
                    RemoveHandler Me._cmFileListItems.Opening, handler
                End If
                Me._cmFileListItems = WithEventsValue
                If (Not Me._cmFileListItems Is Nothing) Then
                    AddHandler Me._cmFileListItems.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property CMFilterSaver As ContextMenuStrip
            Get
                Return Me._CMFilterSaver
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.CMFilterSaver_Opening)
                If (Not Me._CMFilterSaver Is Nothing) Then
                    RemoveHandler Me._CMFilterSaver.Opening, handler
                End If
                Me._CMFilterSaver = WithEventsValue
                If (Not Me._CMFilterSaver Is Nothing) Then
                    AddHandler Me._CMFilterSaver.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmItemsMonster As ContextMenuStrip
            Get
                Return Me._cmItemsMonster
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.cmItemsMonster_Opening)
                If (Not Me._cmItemsMonster Is Nothing) Then
                    RemoveHandler Me._cmItemsMonster.Opening, handler
                End If
                Me._cmItemsMonster = WithEventsValue
                If (Not Me._cmItemsMonster Is Nothing) Then
                    AddHandler Me._cmItemsMonster.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmMapsFiles As ContextMenuStrip
            Get
                Return Me._cmMapsFiles
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.cmMapsFiles_Opening)
                If (Not Me._cmMapsFiles Is Nothing) Then
                    RemoveHandler Me._cmMapsFiles.Opening, handler
                End If
                Me._cmMapsFiles = WithEventsValue
                If (Not Me._cmMapsFiles Is Nothing) Then
                    AddHandler Me._cmMapsFiles.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property cmMonsterItem As ContextMenuStrip
            Get
                Return Me._cmMonsterItem
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.cmMonsterItem_Opening)
                If (Not Me._cmMonsterItem Is Nothing) Then
                    RemoveHandler Me._cmMonsterItem.Opening, handler
                End If
                Me._cmMonsterItem = WithEventsValue
                If (Not Me._cmMonsterItem Is Nothing) Then
                    AddHandler Me._cmMonsterItem.Opening, handler
                End If
            End Set
        End Property

        Friend Overridable Property CMNPCPicturebox As ContextMenuStrip
            Get
                Return Me._CMNPCPicturebox
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMNPCPicturebox = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CMSAddShopItem As ContextMenuStrip
            Get
                Return Me._CMSAddShopItem
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMSAddShopItem = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cmsDrops As ContextMenuStrip
            Get
                Return Me._cmsDrops
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._cmsDrops = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CMSMapBoss As ContextMenuStrip
            Get
                Return Me._CMSMapBoss
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMSMapBoss = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CMSMapMonsterToAdd As ContextMenuStrip
            Get
                Return Me._CMSMapMonsterToAdd
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMSMapMonsterToAdd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CMSMonsterInMap As ContextMenuStrip
            Get
                Return Me._CMSMonsterInMap
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMSMonsterInMap = WithEventsValue
            End Set
        End Property

        Friend Overridable Property CMSNPCList As ContextMenuStrip
            Get
                Return Me._CMSNPCList
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Me._CMSNPCList = WithEventsValue
            End Set
        End Property

        Friend Overridable Property cnMonsterFiles As ContextMenuStrip
            Get
                Return Me._cnMonsterFiles
            End Get
            Set(ByVal WithEventsValue As ContextMenuStrip)
                Dim handler As CancelEventHandler = New CancelEventHandler(AddressOf Me.cnMonsterFiles_Opening)
                If (Not Me._cnMonsterFiles Is Nothing) Then
                    RemoveHandler Me._cnMonsterFiles.Opening, handler
                End If
                Me._cnMonsterFiles = WithEventsValue
                If (Not Me._cnMonsterFiles Is Nothing) Then
                    AddHandler Me._cnMonsterFiles.Opening, handler
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

        Friend Overridable Property ColumnHeader1 As ColumnHeader
            Get
                Return Me._ColumnHeader1
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._ColumnHeader1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ColumnHeader2 As ColumnHeader
            Get
                Return Me._ColumnHeader2
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._ColumnHeader2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property DeleteBackupToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._DeleteBackupToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DeleteBackupToolStripMenuItem_Click)
                Dim handler2 As ToolStripItemClickedEventHandler = New ToolStripItemClickedEventHandler(AddressOf Me.DeleteBackupToolStripMenuItem_DropDownItemClicked)
                If (Not Me._DeleteBackupToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._DeleteBackupToolStripMenuItem.Click, handler
                    RemoveHandler Me._DeleteBackupToolStripMenuItem.DropDownItemClicked, handler2
                End If
                Me._DeleteBackupToolStripMenuItem = WithEventsValue
                If (Not Me._DeleteBackupToolStripMenuItem Is Nothing) Then
                    AddHandler Me._DeleteBackupToolStripMenuItem.Click, handler
                    AddHandler Me._DeleteBackupToolStripMenuItem.DropDownItemClicked, handler2
                End If
            End Set
        End Property

        Friend Overridable Property DeleteBackupToolStripMenuItem1 As ToolStripMenuItem
            Get
                Return Me._DeleteBackupToolStripMenuItem1
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As ToolStripItemClickedEventHandler = New ToolStripItemClickedEventHandler(AddressOf Me.DeleteBackupToolStripMenuItem1_DropDownItemClicked)
                If (Not Me._DeleteBackupToolStripMenuItem1 Is Nothing) Then
                    RemoveHandler Me._DeleteBackupToolStripMenuItem1.DropDownItemClicked, handler
                End If
                Me._DeleteBackupToolStripMenuItem1 = WithEventsValue
                If (Not Me._DeleteBackupToolStripMenuItem1 Is Nothing) Then
                    AddHandler Me._DeleteBackupToolStripMenuItem1.DropDownItemClicked, handler
                End If
            End Set
        End Property

        Friend Overridable Property DeleteLineToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._DeleteLineToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DeleteLineToolStripMenuItem_Click)
                If (Not Me._DeleteLineToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._DeleteLineToolStripMenuItem.Click, handler
                End If
                Me._DeleteLineToolStripMenuItem = WithEventsValue
                If (Not Me._DeleteLineToolStripMenuItem Is Nothing) Then
                    AddHandler Me._DeleteLineToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property DeleteNPCToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._DeleteNPCToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DeleteNPCToolStripMenuItem_Click)
                If (Not Me._DeleteNPCToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._DeleteNPCToolStripMenuItem.Click, handler
                End If
                Me._DeleteNPCToolStripMenuItem = WithEventsValue
                If (Not Me._DeleteNPCToolStripMenuItem Is Nothing) Then
                    AddHandler Me._DeleteNPCToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property DeleteNPCToolStripMenuItem1 As ToolStripMenuItem
            Get
                Return Me._DeleteNPCToolStripMenuItem1
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DeleteNPCToolStripMenuItem1_Click)
                If (Not Me._DeleteNPCToolStripMenuItem1 Is Nothing) Then
                    RemoveHandler Me._DeleteNPCToolStripMenuItem1.Click, handler
                End If
                Me._DeleteNPCToolStripMenuItem1 = WithEventsValue
                If (Not Me._DeleteNPCToolStripMenuItem1 Is Nothing) Then
                    AddHandler Me._DeleteNPCToolStripMenuItem1.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property dlgFile As OpenFileDialog
            Get
                Return Me._dlgFile
            End Get
            Set(ByVal WithEventsValue As OpenFileDialog)
                Me._dlgFile = WithEventsValue
            End Set
        End Property

        Friend Overridable Property dlgFolder As FolderBrowserDialog
            Get
                Return Me._dlgFolder
            End Get
            Set(ByVal WithEventsValue As FolderBrowserDialog)
                Me._dlgFolder = WithEventsValue
            End Set
        End Property

        Friend Overridable Property DownToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._DownToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DownToolStripMenuItem_Click)
                If (Not Me._DownToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._DownToolStripMenuItem.Click, handler
                End If
                Me._DownToolStripMenuItem = WithEventsValue
                If (Not Me._DownToolStripMenuItem Is Nothing) Then
                    AddHandler Me._DownToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property DropCountToolStripMenuItem1 As ToolStripMenuItem
            Get
                Return Me._DropCountToolStripMenuItem1
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.DropCountToolStripMenuItem1_Click)
                If (Not Me._DropCountToolStripMenuItem1 Is Nothing) Then
                    RemoveHandler Me._DropCountToolStripMenuItem1.Click, handler
                End If
                Me._DropCountToolStripMenuItem1 = WithEventsValue
                If (Not Me._DropCountToolStripMenuItem1 Is Nothing) Then
                    AddHandler Me._DropCountToolStripMenuItem1.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property EditMonsterToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._EditMonsterToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.EditMonsterToolStripMenuItem_Click)
                If (Not Me._EditMonsterToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._EditMonsterToolStripMenuItem.Click, handler
                End If
                Me._EditMonsterToolStripMenuItem = WithEventsValue
                If (Not Me._EditMonsterToolStripMenuItem Is Nothing) Then
                    AddHandler Me._EditMonsterToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property EditRateToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._EditRateToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.EditRateToolStripMenuItem_Click)
                If (Not Me._EditRateToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._EditRateToolStripMenuItem.Click, handler
                End If
                Me._EditRateToolStripMenuItem = WithEventsValue
                If (Not Me._EditRateToolStripMenuItem Is Nothing) Then
                    AddHandler Me._EditRateToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property EditSpawnRateToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._EditSpawnRateToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.EditSpawnRateToolStripMenuItem_Click)
                If (Not Me._EditSpawnRateToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._EditSpawnRateToolStripMenuItem.Click, handler
                End If
                Me._EditSpawnRateToolStripMenuItem = WithEventsValue
                If (Not Me._EditSpawnRateToolStripMenuItem Is Nothing) Then
                    AddHandler Me._EditSpawnRateToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property EditSpawnTimesToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._EditSpawnTimesToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.EditSpawnTimesToolStripMenuItem_Click)
                If (Not Me._EditSpawnTimesToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._EditSpawnTimesToolStripMenuItem.Click, handler
                End If
                Me._EditSpawnTimesToolStripMenuItem = WithEventsValue
                If (Not Me._EditSpawnTimesToolStripMenuItem Is Nothing) Then
                    AddHandler Me._EditSpawnTimesToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property ExperienceToolStripMenuItem1 As ToolStripMenuItem
            Get
                Return Me._ExperienceToolStripMenuItem1
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ExperienceToolStripMenuItem1_Click)
                If (Not Me._ExperienceToolStripMenuItem1 Is Nothing) Then
                    RemoveHandler Me._ExperienceToolStripMenuItem1.Click, handler
                End If
                Me._ExperienceToolStripMenuItem1 = WithEventsValue
                If (Not Me._ExperienceToolStripMenuItem1 Is Nothing) Then
                    AddHandler Me._ExperienceToolStripMenuItem1.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property gb24 As GroupBox
            Get
                Return Me._gb24
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._gb24 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GoldToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._GoldToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.GoldToolStripMenuItem_Click)
                If (Not Me._GoldToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._GoldToolStripMenuItem.Click, handler
                End If
                Me._GoldToolStripMenuItem = WithEventsValue
                If (Not Me._GoldToolStripMenuItem Is Nothing) Then
                    AddHandler Me._GoldToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property GoToItemEditorToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._GoToItemEditorToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.GoToItemEditorToolStripMenuItem_Click)
                If (Not Me._GoToItemEditorToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._GoToItemEditorToolStripMenuItem.Click, handler
                End If
                Me._GoToItemEditorToolStripMenuItem = WithEventsValue
                If (Not Me._GoToItemEditorToolStripMenuItem Is Nothing) Then
                    AddHandler Me._GoToItemEditorToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property GroupBox1 As GroupBox
            Get
                Return Me._GroupBox1
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox10 As GroupBox
            Get
                Return Me._GroupBox10
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox10 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox11 As GroupBox
            Get
                Return Me._GroupBox11
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox11 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox12 As GroupBox
            Get
                Return Me._GroupBox12
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox12 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox13 As GroupBox
            Get
                Return Me._GroupBox13
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox13 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox14 As GroupBox
            Get
                Return Me._GroupBox14
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox14 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox15 As GroupBox
            Get
                Return Me._GroupBox15
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox15 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox16 As GroupBox
            Get
                Return Me._GroupBox16
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox16 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox17 As GroupBox
            Get
                Return Me._GroupBox17
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox17 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox18 As GroupBox
            Get
                Return Me._GroupBox18
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox18 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox19 As GroupBox
            Get
                Return Me._GroupBox19
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox19 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox2 As GroupBox
            Get
                Return Me._GroupBox2
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox20 As GroupBox
            Get
                Return Me._GroupBox20
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox20 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox21 As GroupBox
            Get
                Return Me._GroupBox21
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox21 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox22 As GroupBox
            Get
                Return Me._GroupBox22
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox22 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox23 As GroupBox
            Get
                Return Me._GroupBox23
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox23 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox3 As GroupBox
            Get
                Return Me._GroupBox3
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox3 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox4 As GroupBox
            Get
                Return Me._GroupBox4
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox4 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox5 As GroupBox
            Get
                Return Me._GroupBox5
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox5 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox6 As GroupBox
            Get
                Return Me._GroupBox6
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox6 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox7 As GroupBox
            Get
                Return Me._GroupBox7
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox7 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox8 As GroupBox
            Get
                Return Me._GroupBox8
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox8 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property GroupBox9 As GroupBox
            Get
                Return Me._GroupBox9
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._GroupBox9 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ItemDistribToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ItemDistribToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ItemDistribToolStripMenuItem_Click)
                If (Not Me._ItemDistribToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._ItemDistribToolStripMenuItem.Click, handler
                End If
                Me._ItemDistribToolStripMenuItem = WithEventsValue
                If (Not Me._ItemDistribToolStripMenuItem Is Nothing) Then
                    AddHandler Me._ItemDistribToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property ItemFound As Label
            Get
                Return Me._ItemFound
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._ItemFound = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ItemToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ItemToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ItemToolStripMenuItem_Click)
                If (Not Me._ItemToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._ItemToolStripMenuItem.Click, handler
                End If
                Me._ItemToolStripMenuItem = WithEventsValue
                If (Not Me._ItemToolStripMenuItem Is Nothing) Then
                    AddHandler Me._ItemToolStripMenuItem.Click, handler
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

        Friend Overridable Property Label10 As Label
            Get
                Return Me._Label10
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label10 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label100 As Label
            Get
                Return Me._Label100
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label100 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label101 As Label
            Get
                Return Me._Label101
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label101 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label106 As Label
            Get
                Return Me._Label106
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label106 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label107 As Label
            Get
                Return Me._Label107
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label107 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label108 As Label
            Get
                Return Me._Label108
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label108 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label109 As Label
            Get
                Return Me._Label109
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label109 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label11 As Label
            Get
                Return Me._Label11
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label11 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label110 As Label
            Get
                Return Me._Label110
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label110 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label111 As Label
            Get
                Return Me._Label111
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label111 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label112 As Label
            Get
                Return Me._Label112
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label112 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label113 As Label
            Get
                Return Me._Label113
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label113 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label114 As Label
            Get
                Return Me._Label114
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label114 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label115 As Label
            Get
                Return Me._Label115
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label115 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label116 As Label
            Get
                Return Me._Label116
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label116 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label117 As Label
            Get
                Return Me._Label117
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label117 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label12 As Label
            Get
                Return Me._Label12
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label12 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label13 As Label
            Get
                Return Me._Label13
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label13 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label14 As Label
            Get
                Return Me._Label14
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label14 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label15 As Label
            Get
                Return Me._Label15
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label15 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label16 As Label
            Get
                Return Me._Label16
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label16 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label17 As Label
            Get
                Return Me._Label17
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label17 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label18 As Label
            Get
                Return Me._Label18
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label18 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label19 As Label
            Get
                Return Me._Label19
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label19 = WithEventsValue
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

        Friend Overridable Property Label20 As Label
            Get
                Return Me._Label20
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label20 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label21 As Label
            Get
                Return Me._Label21
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label21 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label22 As Label
            Get
                Return Me._Label22
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label22 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label23 As Label
            Get
                Return Me._Label23
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label23 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label24 As Label
            Get
                Return Me._Label24
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label24 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label25 As Label
            Get
                Return Me._Label25
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label25 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label26 As Label
            Get
                Return Me._Label26
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label26 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label27 As Label
            Get
                Return Me._Label27
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label27 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label28 As Label
            Get
                Return Me._Label28
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label28 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label29 As Label
            Get
                Return Me._Label29
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label29 = WithEventsValue
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

        Friend Overridable Property Label30 As Label
            Get
                Return Me._Label30
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label30 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label31 As Label
            Get
                Return Me._Label31
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label31 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label32 As Label
            Get
                Return Me._Label32
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label32 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label33 As Label
            Get
                Return Me._Label33
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label33 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label34 As Label
            Get
                Return Me._Label34
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label34 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label35 As Label
            Get
                Return Me._Label35
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label35 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label36 As Label
            Get
                Return Me._Label36
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label36 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label37 As Label
            Get
                Return Me._Label37
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label37 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label38 As Label
            Get
                Return Me._Label38
            End Get
            Set(ByVal WithEventsValue As Label)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.Label38_Click)
                If (Not Me._Label38 Is Nothing) Then
                    RemoveHandler Me._Label38.Click, handler
                End If
                Me._Label38 = WithEventsValue
                If (Not Me._Label38 Is Nothing) Then
                    AddHandler Me._Label38.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property Label39 As Label
            Get
                Return Me._Label39
            End Get
            Set(ByVal WithEventsValue As Label)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.Label39_Click)
                If (Not Me._Label39 Is Nothing) Then
                    RemoveHandler Me._Label39.Click, handler
                End If
                Me._Label39 = WithEventsValue
                If (Not Me._Label39 Is Nothing) Then
                    AddHandler Me._Label39.Click, handler
                End If
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

        Friend Overridable Property Label40 As Label
            Get
                Return Me._Label40
            End Get
            Set(ByVal WithEventsValue As Label)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.Label40_Click)
                If (Not Me._Label40 Is Nothing) Then
                    RemoveHandler Me._Label40.Click, handler
                End If
                Me._Label40 = WithEventsValue
                If (Not Me._Label40 Is Nothing) Then
                    AddHandler Me._Label40.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property Label41 As Label
            Get
                Return Me._Label41
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label41 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label42 As Label
            Get
                Return Me._Label42
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label42 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label43 As Label
            Get
                Return Me._Label43
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label43 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label44 As Label
            Get
                Return Me._Label44
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label44 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label45 As Label
            Get
                Return Me._Label45
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label45 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label46 As Label
            Get
                Return Me._Label46
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label46 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label47 As Label
            Get
                Return Me._Label47
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label47 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label48 As Label
            Get
                Return Me._Label48
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label48 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label49 As Label
            Get
                Return Me._Label49
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label49 = WithEventsValue
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

        Friend Overridable Property Label50 As Label
            Get
                Return Me._Label50
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label50 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label51 As Label
            Get
                Return Me._Label51
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label51 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label52 As Label
            Get
                Return Me._Label52
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label52 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label53 As Label
            Get
                Return Me._Label53
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label53 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label54 As Label
            Get
                Return Me._Label54
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label54 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label55 As Label
            Get
                Return Me._Label55
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label55 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label56 As Label
            Get
                Return Me._Label56
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label56 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label57 As Label
            Get
                Return Me._Label57
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label57 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label58 As Label
            Get
                Return Me._Label58
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label58 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label59 As Label
            Get
                Return Me._Label59
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label59 = WithEventsValue
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

        Friend Overridable Property Label60 As Label
            Get
                Return Me._Label60
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label60 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label61 As Label
            Get
                Return Me._Label61
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label61 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label62 As Label
            Get
                Return Me._Label62
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label62 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label63 As Label
            Get
                Return Me._Label63
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label63 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label64 As Label
            Get
                Return Me._Label64
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label64 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label65 As Label
            Get
                Return Me._Label65
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label65 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label66 As Label
            Get
                Return Me._Label66
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label66 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label67 As Label
            Get
                Return Me._Label67
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label67 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label68 As Label
            Get
                Return Me._Label68
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label68 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label69 As Label
            Get
                Return Me._Label69
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label69 = WithEventsValue
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

        Friend Overridable Property Label70 As Label
            Get
                Return Me._Label70
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label70 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label71 As Label
            Get
                Return Me._Label71
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label71 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label72 As Label
            Get
                Return Me._Label72
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label72 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label73 As Label
            Get
                Return Me._Label73
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label73 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label74 As Label
            Get
                Return Me._Label74
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label74 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label75 As Label
            Get
                Return Me._Label75
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label75 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label76 As Label
            Get
                Return Me._Label76
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label76 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label77 As Label
            Get
                Return Me._Label77
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label77 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label78 As Label
            Get
                Return Me._Label78
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label78 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label79 As Label
            Get
                Return Me._Label79
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label79 = WithEventsValue
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

        Friend Overridable Property Label80 As Label
            Get
                Return Me._Label80
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label80 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label81 As Label
            Get
                Return Me._Label81
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label81 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label82 As Label
            Get
                Return Me._Label82
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label82 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label83 As Label
            Get
                Return Me._Label83
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label83 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label84 As Label
            Get
                Return Me._Label84
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label84 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label85 As Label
            Get
                Return Me._Label85
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label85 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label86 As Label
            Get
                Return Me._Label86
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label86 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label87 As Label
            Get
                Return Me._Label87
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label87 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label88 As Label
            Get
                Return Me._Label88
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label88 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label89 As Label
            Get
                Return Me._Label89
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label89 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label9 As Label
            Get
                Return Me._Label9
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label9 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label90 As Label
            Get
                Return Me._Label90
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label90 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label91 As Label
            Get
                Return Me._Label91
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label91 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label92 As Label
            Get
                Return Me._Label92
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label92 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label93 As Label
            Get
                Return Me._Label93
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label93 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label94 As Label
            Get
                Return Me._Label94
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label94 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label95 As Label
            Get
                Return Me._Label95
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label95 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label96 As Label
            Get
                Return Me._Label96
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label96 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label97 As Label
            Get
                Return Me._Label97
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label97 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label98 As Label
            Get
                Return Me._Label98
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label98 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Label99 As Label
            Get
                Return Me._Label99
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Label99 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lbFileListItems As ListBox
            Get
                Return Me._lbFileListItems
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As KeyEventHandler = New KeyEventHandler(AddressOf Me.lbFileListItems_KeyUp)
                Dim handler2 As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFileListItems_MouseDoubleClick)
                Dim handler3 As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFileListItems_MouseClick)
                If (Not Me._lbFileListItems Is Nothing) Then
                    RemoveHandler Me._lbFileListItems.KeyUp, handler
                    RemoveHandler Me._lbFileListItems.MouseDoubleClick, handler2
                    RemoveHandler Me._lbFileListItems.MouseClick, handler3
                End If
                Me._lbFileListItems = WithEventsValue
                If (Not Me._lbFileListItems Is Nothing) Then
                    AddHandler Me._lbFileListItems.KeyUp, handler
                    AddHandler Me._lbFileListItems.MouseDoubleClick, handler2
                    AddHandler Me._lbFileListItems.MouseClick, handler3
                End If
            End Set
        End Property

        Friend Overridable Property lbFiles As ListBox
            Get
                Return Me._lbFiles
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFiles_MouseDoubleClick)
                Dim handler2 As KeyEventHandler = New KeyEventHandler(AddressOf Me.lbFiles_KeyUp)
                Dim handler3 As EventHandler = New EventHandler(AddressOf Me.lbFiles_SelectedValueChanged)
                Dim handler4 As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFiles_MouseClick)
                Dim handler5 As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFiles_MouseDown)
                If (Not Me._lbFiles Is Nothing) Then
                    RemoveHandler Me._lbFiles.MouseDoubleClick, handler
                    RemoveHandler Me._lbFiles.KeyUp, handler2
                    RemoveHandler Me._lbFiles.SelectedValueChanged, handler3
                    RemoveHandler Me._lbFiles.MouseClick, handler4
                    RemoveHandler Me._lbFiles.MouseDown, handler5
                End If
                Me._lbFiles = WithEventsValue
                If (Not Me._lbFiles Is Nothing) Then
                    AddHandler Me._lbFiles.MouseDoubleClick, handler
                    AddHandler Me._lbFiles.KeyUp, handler2
                    AddHandler Me._lbFiles.SelectedValueChanged, handler3
                    AddHandler Me._lbFiles.MouseClick, handler4
                    AddHandler Me._lbFiles.MouseDown, handler5
                End If
            End Set
        End Property

        Friend Overridable Property lbFilesMaps As ListBox
            Get
                Return Me._lbFilesMaps
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbFilesMaps_MouseDoubleClick)
                Dim handler2 As EventHandler = New EventHandler(AddressOf Me.lbFilesMaps_SelectedIndexChanged)
                If (Not Me._lbFilesMaps Is Nothing) Then
                    RemoveHandler Me._lbFilesMaps.MouseDoubleClick, handler
                    RemoveHandler Me._lbFilesMaps.SelectedIndexChanged, handler2
                End If
                Me._lbFilesMaps = WithEventsValue
                If (Not Me._lbFilesMaps Is Nothing) Then
                    AddHandler Me._lbFilesMaps.MouseDoubleClick, handler
                    AddHandler Me._lbFilesMaps.SelectedIndexChanged, handler2
                End If
            End Set
        End Property

        Friend Overridable Property lbFound As Label
            Get
                Return Me._lbFound
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lbFound = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lbItemFiles As ListBox
            Get
                Return Me._lbItemFiles
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.lbItemFiles_SelectedIndexChanged)
                Dim handler2 As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbItemFiles_MouseDoubleClick)
                If (Not Me._lbItemFiles Is Nothing) Then
                    RemoveHandler Me._lbItemFiles.SelectedIndexChanged, handler
                    RemoveHandler Me._lbItemFiles.MouseDoubleClick, handler2
                End If
                Me._lbItemFiles = WithEventsValue
                If (Not Me._lbItemFiles Is Nothing) Then
                    AddHandler Me._lbItemFiles.SelectedIndexChanged, handler
                    AddHandler Me._lbItemFiles.MouseDoubleClick, handler2
                End If
            End Set
        End Property

        Friend Overridable Property lbItemMo As ListBox
            Get
                Return Me._lbItemMo
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbItemMo_MouseDoubleClick)
                If (Not Me._lbItemMo Is Nothing) Then
                    RemoveHandler Me._lbItemMo.MouseDoubleClick, handler
                End If
                Me._lbItemMo = WithEventsValue
                If (Not Me._lbItemMo Is Nothing) Then
                    AddHandler Me._lbItemMo.MouseDoubleClick, handler
                End If
            End Set
        End Property

        Friend Overridable Property lbItemsListCount As Label
            Get
                Return Me._lbItemsListCount
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lbItemsListCount = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lbItemsRealName As ListBox
            Get
                Return Me._lbItemsRealName
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.lbItemsRealName_SelectedIndexChanged)
                If (Not Me._lbItemsRealName Is Nothing) Then
                    RemoveHandler Me._lbItemsRealName.SelectedIndexChanged, handler
                End If
                Me._lbItemsRealName = WithEventsValue
                If (Not Me._lbItemsRealName Is Nothing) Then
                    AddHandler Me._lbItemsRealName.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property lblMoListName As Label
            Get
                Return Me._lblMoListName
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblMoListName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lblprgV As Label
            Get
                Return Me._lblprgV
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblprgV = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lblProg As Label
            Get
                Return Me._lblProg
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblProg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lblTextCoding As Label
            Get
                Return Me._lblTextCoding
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._lblTextCoding = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lbMaps As ListBox
            Get
                Return Me._lbMaps
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As MouseEventHandler = New MouseEventHandler(AddressOf Me.lbMaps_MouseDoubleClick)
                If (Not Me._lbMaps Is Nothing) Then
                    RemoveHandler Me._lbMaps.MouseDoubleClick, handler
                End If
                Me._lbMaps = WithEventsValue
                If (Not Me._lbMaps Is Nothing) Then
                    AddHandler Me._lbMaps.MouseDoubleClick, handler
                End If
            End Set
        End Property

        Friend Overridable Property lbNPCList As ListBox
            Get
                Return Me._lbNPCList
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.lbNPCList_SelectedIndexChanged)
                If (Not Me._lbNPCList Is Nothing) Then
                    RemoveHandler Me._lbNPCList.SelectedIndexChanged, handler
                End If
                Me._lbNPCList = WithEventsValue
                If (Not Me._lbNPCList Is Nothing) Then
                    AddHandler Me._lbNPCList.SelectedIndexChanged, handler
                End If
            End Set
        End Property

        Friend Overridable Property lbNPCMapFileList As ListBox
            Get
                Return Me._lbNPCMapFileList
            End Get
            Set(ByVal WithEventsValue As ListBox)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.lbNPCMapFileList_SelectedIndexChanged)
                If (Not Me._lbNPCMapFileList Is Nothing) Then
                    RemoveHandler Me._lbNPCMapFileList.SelectedIndexChanged, handler
                End If
                Me._lbNPCMapFileList = WithEventsValue
                If (Not Me._lbNPCMapFileList Is Nothing) Then
                    AddHandler Me._lbNPCMapFileList.SelectedIndexChanged, handler
                End If
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

        Friend Overridable Property ListView1 As ListView
            Get
                Return Me._ListView1
            End Get
            Set(ByVal WithEventsValue As ListView)
                Me._ListView1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ListView2 As ListView
            Get
                Return Me._ListView2
            End Get
            Set(ByVal WithEventsValue As ListView)
                Me._ListView2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ListView3 As ListView
            Get
                Return Me._ListView3
            End Get
            Set(ByVal WithEventsValue As ListView)
                Me._ListView3 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property LoadBackupToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._LoadBackupToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As ToolStripItemClickedEventHandler = New ToolStripItemClickedEventHandler(AddressOf Me.LoadBackupToolStripMenuItem_DropDownItemClicked)
                If (Not Me._LoadBackupToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._LoadBackupToolStripMenuItem.DropDownItemClicked, handler
                End If
                Me._LoadBackupToolStripMenuItem = WithEventsValue
                If (Not Me._LoadBackupToolStripMenuItem Is Nothing) Then
                    AddHandler Me._LoadBackupToolStripMenuItem.DropDownItemClicked, handler
                End If
            End Set
        End Property

        Friend Overridable Property LoadFilterToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._LoadFilterToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.LoadFilterToolStripMenuItem_Click)
                If (Not Me._LoadFilterToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._LoadFilterToolStripMenuItem.Click, handler
                End If
                Me._LoadFilterToolStripMenuItem = WithEventsValue
                If (Not Me._LoadFilterToolStripMenuItem Is Nothing) Then
                    AddHandler Me._LoadFilterToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property LWAddSpawnCount As ColumnHeader
            Get
                Return Me._LWAddSpawnCount
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._LWAddSpawnCount = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwBossAddMonster As ColumnHeader
            Get
                Return Me._lwBossAddMonster
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwBossAddMonster = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwBossAddMonsterRealName As ColumnHeader
            Get
                Return Me._lwBossAddMonsterRealName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwBossAddMonsterRealName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwBossFileName As ColumnHeader
            Get
                Return Me._lwBossFileName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwBossFileName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property LWBossRealName As ColumnHeader
            Get
                Return Me._LWBossRealName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._LWBossRealName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property LWBossSpawnTimes As ColumnHeader
            Get
                Return Me._LWBossSpawnTimes
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._LWBossSpawnTimes = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwItems As ListView
            Get
                Return Me._lwItems
            End Get
            Set(ByVal WithEventsValue As ListView)
                Dim handler As ListViewItemSelectionChangedEventHandler = New ListViewItemSelectionChangedEventHandler(AddressOf Me.lwItems_ItemSelectionChanged)
                Dim handler2 As EventHandler = New EventHandler(AddressOf Me.lwItems_SelectedIndexChanged)
                If (Not Me._lwItems Is Nothing) Then
                    RemoveHandler Me._lwItems.ItemSelectionChanged, handler
                    RemoveHandler Me._lwItems.SelectedIndexChanged, handler2
                End If
                Me._lwItems = WithEventsValue
                If (Not Me._lwItems Is Nothing) Then
                    AddHandler Me._lwItems.ItemSelectionChanged, handler
                    AddHandler Me._lwItems.SelectedIndexChanged, handler2
                End If
            End Set
        End Property

        Friend Overridable Property lwMonsterName As ColumnHeader
            Get
                Return Me._lwMonsterName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwMonsterName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwMoRealName As ColumnHeader
            Get
                Return Me._lwMoRealName
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwMoRealName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property LWNPCshop As ListView
            Get
                Return Me._LWNPCshop
            End Get
            Set(ByVal WithEventsValue As ListView)
                Me._LWNPCshop = WithEventsValue
            End Set
        End Property

        Friend Overridable Property lwSpawnRate As ColumnHeader
            Get
                Return Me._lwSpawnRate
            End Get
            Set(ByVal WithEventsValue As ColumnHeader)
                Me._lwSpawnRate = WithEventsValue
            End Set
        End Property

        Friend Overridable Property Mapsfound As Label
            Get
                Return Me._Mapsfound
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._Mapsfound = WithEventsValue
            End Set
        End Property

        Friend Overridable Property MoFound As Label
            Get
                Return Me._MoFound
            End Get
            Set(ByVal WithEventsValue As Label)
                Me._MoFound = WithEventsValue
            End Set
        End Property

        Friend Overridable Property pbWorking As ProgressBar
            Get
                Return Me._pbWorking
            End Get
            Set(ByVal WithEventsValue As ProgressBar)
                Me._pbWorking = WithEventsValue
            End Set
        End Property

        Public Overridable Property PictureBox1 As PictureBox
            Get
                Return Me._PictureBox1
            End Get
            Set(ByVal WithEventsValue As PictureBox)
                Dim handler As PreviewKeyDownEventHandler = New PreviewKeyDownEventHandler(AddressOf Me.PictureBox1_PreviewKeyDown)
                Dim handler2 As MouseEventHandler = New MouseEventHandler(AddressOf Me.PictureBox1_MouseMove)
                Dim handler3 As EventHandler = New EventHandler(AddressOf Me.PictureBox1_MouseLeave)
                If (Not Me._PictureBox1 Is Nothing) Then
                    RemoveHandler Me._PictureBox1.PreviewKeyDown, handler
                    RemoveHandler Me._PictureBox1.MouseMove, handler2
                    RemoveHandler Me._PictureBox1.MouseLeave, handler3
                End If
                Me._PictureBox1 = WithEventsValue
                If (Not Me._PictureBox1 Is Nothing) Then
                    AddHandler Me._PictureBox1.PreviewKeyDown, handler
                    AddHandler Me._PictureBox1.MouseMove, handler2
                    AddHandler Me._PictureBox1.MouseLeave, handler3
                End If
            End Set
        End Property

        Friend Overridable Property RemoveAllToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._RemoveAllToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveAllToolStripMenuItem_Click)
                If (Not Me._RemoveAllToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._RemoveAllToolStripMenuItem.Click, handler
                End If
                Me._RemoveAllToolStripMenuItem = WithEventsValue
                If (Not Me._RemoveAllToolStripMenuItem Is Nothing) Then
                    AddHandler Me._RemoveAllToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property RemoveAllToolStripMenuItem1 As ToolStripMenuItem
            Get
                Return Me._RemoveAllToolStripMenuItem1
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveAllToolStripMenuItem1_Click)
                If (Not Me._RemoveAllToolStripMenuItem1 Is Nothing) Then
                    RemoveHandler Me._RemoveAllToolStripMenuItem1.Click, handler
                End If
                Me._RemoveAllToolStripMenuItem1 = WithEventsValue
                If (Not Me._RemoveAllToolStripMenuItem1 Is Nothing) Then
                    AddHandler Me._RemoveAllToolStripMenuItem1.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property RemoveFromListToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._RemoveFromListToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveFromListToolStripMenuItem_Click)
                If (Not Me._RemoveFromListToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._RemoveFromListToolStripMenuItem.Click, handler
                End If
                Me._RemoveFromListToolStripMenuItem = WithEventsValue
                If (Not Me._RemoveFromListToolStripMenuItem Is Nothing) Then
                    AddHandler Me._RemoveFromListToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property RemoveItemToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._RemoveItemToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveItemToolStripMenuItem_Click)
                If (Not Me._RemoveItemToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._RemoveItemToolStripMenuItem.Click, handler
                End If
                Me._RemoveItemToolStripMenuItem = WithEventsValue
                If (Not Me._RemoveItemToolStripMenuItem Is Nothing) Then
                    AddHandler Me._RemoveItemToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property RemoveMonsterToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._RemoveMonsterToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveMonsterToolStripMenuItem_Click)
                If (Not Me._RemoveMonsterToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._RemoveMonsterToolStripMenuItem.Click, handler
                End If
                Me._RemoveMonsterToolStripMenuItem = WithEventsValue
                If (Not Me._RemoveMonsterToolStripMenuItem Is Nothing) Then
                    AddHandler Me._RemoveMonsterToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property RemoveToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._RemoveToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.RemoveToolStripMenuItem_Click)
                If (Not Me._RemoveToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._RemoveToolStripMenuItem.Click, handler
                End If
                Me._RemoveToolStripMenuItem = WithEventsValue
                If (Not Me._RemoveToolStripMenuItem Is Nothing) Then
                    AddHandler Me._RemoveToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property SaveMonstersToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._SaveMonstersToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Me._SaveMonstersToolStripMenuItem = WithEventsValue
            End Set
        End Property

        Friend Overridable Property SaveToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._SaveToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.SaveToolStripMenuItem_Click)
                If (Not Me._SaveToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._SaveToolStripMenuItem.Click, handler
                End If
                Me._SaveToolStripMenuItem = WithEventsValue
                If (Not Me._SaveToolStripMenuItem Is Nothing) Then
                    AddHandler Me._SaveToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property SeachForItemNameToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._SeachForItemNameToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.SeachForItemNameToolStripMenuItem_Click)
                If (Not Me._SeachForItemNameToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._SeachForItemNameToolStripMenuItem.Click, handler
                End If
                Me._SeachForItemNameToolStripMenuItem = WithEventsValue
                If (Not Me._SeachForItemNameToolStripMenuItem Is Nothing) Then
                    AddHandler Me._SeachForItemNameToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property SendToItemSearcherToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._SendToItemSearcherToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.SendToItemSearcherToolStripMenuItem_Click)
                If (Not Me._SendToItemSearcherToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._SendToItemSearcherToolStripMenuItem.Click, handler
                End If
                Me._SendToItemSearcherToolStripMenuItem = WithEventsValue
                If (Not Me._SendToItemSearcherToolStripMenuItem Is Nothing) Then
                    AddHandler Me._SendToItemSearcherToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property Settings As GroupBox
            Get
                Return Me._Settings
            End Get
            Set(ByVal WithEventsValue As GroupBox)
                Me._Settings = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ShowToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._ShowToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.ShowToolStripMenuItem_Click)
                If (Not Me._ShowToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._ShowToolStripMenuItem.Click, handler
                End If
                Me._ShowToolStripMenuItem = WithEventsValue
                If (Not Me._ShowToolStripMenuItem Is Nothing) Then
                    AddHandler Me._ShowToolStripMenuItem.Click, handler
                End If
            End Set
        End Property

        Friend Overridable Property TabControl1 As TabControl
            Get
                Return Me._TabControl1
            End Get
            Set(ByVal WithEventsValue As TabControl)
                Dim handler As TabControlEventHandler = New TabControlEventHandler(AddressOf Me.TabControl1_Selected)
                If (Not Me._TabControl1 Is Nothing) Then
                    RemoveHandler Me._TabControl1.Selected, handler
                End If
                Me._TabControl1 = WithEventsValue
                If (Not Me._TabControl1 Is Nothing) Then
                    AddHandler Me._TabControl1.Selected, handler
                End If
            End Set
        End Property

        Friend Overridable Property TabPage1 As TabPage
            Get
                Return Me._TabPage1
            End Get
            Set(ByVal WithEventsValue As TabPage)
                Me._TabPage1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property TabPage2 As TabPage
            Get
                Return Me._TabPage2
            End Get
            Set(ByVal WithEventsValue As TabPage)
                Me._TabPage2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property TabPage3 As TabPage
            Get
                Return Me._TabPage3
            End Get
            Set(ByVal WithEventsValue As TabPage)
                Me._TabPage3 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property TabPage4 As TabPage
            Get
                Return Me._TabPage4
            End Get
            Set(ByVal WithEventsValue As TabPage)
                Me._TabPage4 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property TabPage5 As TabPage
            Get
                Return Me._TabPage5
            End Get
            Set(ByVal WithEventsValue As TabPage)
                Me._TabPage5 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbDroprate As TextBox
            Get
                Return Me._tbDroprate
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Dim handler As KeyPressEventHandler = New KeyPressEventHandler(AddressOf Me.tbDroprate_KeyPress)
                If (Not Me._tbDroprate Is Nothing) Then
                    RemoveHandler Me._tbDroprate.KeyPress, handler
                End If
                Me._tbDroprate = WithEventsValue
                If (Not Me._tbDroprate Is Nothing) Then
                    AddHandler Me._tbDroprate.KeyPress, handler
                End If
            End Set
        End Property

        Friend Overridable Property tbDrops As TextBox
            Get
                Return Me._tbDrops
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Dim handler As KeyPressEventHandler = New KeyPressEventHandler(AddressOf Me.tbDrops_KeyPress)
                If (Not Me._tbDrops Is Nothing) Then
                    RemoveHandler Me._tbDrops.KeyPress, handler
                End If
                Me._tbDrops = WithEventsValue
                If (Not Me._tbDrops Is Nothing) Then
                    AddHandler Me._tbDrops.KeyPress, handler
                End If
            End Set
        End Property

        Friend Overridable Property tbEditorPath As TextBox
            Get
                Return Me._tbEditorPath
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbEditorPath = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmAbs As TextBox
            Get
                Return Me._tbItmAbs
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmAbs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmAgi As TextBox
            Get
                Return Me._tbItmAgi
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmAgi = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmAPT As TextBox
            Get
                Return Me._tbItmAPT
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmAPT = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmAtkPow As TextBox
            Get
                Return Me._tbItmAtkPow
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmAtkPow = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmAtkRtg As TextBox
            Get
                Return Me._tbItmAtkRtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmAtkRtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmBlk As TextBox
            Get
                Return Me._tbItmBlk
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmBlk = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmCode As TextBox
            Get
                Return Me._tbItmCode
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmCode = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmCrtRtg As TextBox
            Get
                Return Me._tbItmCrtRtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmCrtRtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmdef As TextBox
            Get
                Return Me._tbItmdef
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmdef = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmFire As TextBox
            Get
                Return Me._tbItmFire
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmFire = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmFrost As TextBox
            Get
                Return Me._tbItmFrost
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmFrost = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmGlow As TextBox
            Get
                Return Me._tbItmGlow
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmGlow = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmHPAdd As TextBox
            Get
                Return Me._tbItmHPAdd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmHPAdd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmHPRec As TextBox
            Get
                Return Me._tbItmHPRec
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmHPRec = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmHPRegen As TextBox
            Get
                Return Me._tbItmHPRegen
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmHPRegen = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmInGameNAme As TextBox
            Get
                Return Me._tbItmInGameNAme
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmInGameNAme = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmIntegrity As TextBox
            Get
                Return Me._tbItmIntegrity
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmIntegrity = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmJpName As TextBox
            Get
                Return Me._tbItmJpName
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmJpName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmLevel As TextBox
            Get
                Return Me._tbItmLevel
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmLevel = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmLighting As TextBox
            Get
                Return Me._tbItmLighting
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmLighting = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmManaRec As TextBox
            Get
                Return Me._tbItmManaRec
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmManaRec = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmMPAdd As TextBox
            Get
                Return Me._tbItmMPAdd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmMPAdd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmMPRegen As TextBox
            Get
                Return Me._tbItmMPRegen
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmMPRegen = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmName As TextBox
            Get
                Return Me._tbItmName
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmOrganic As TextBox
            Get
                Return Me._tbItmOrganic
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmOrganic = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmPoision As TextBox
            Get
                Return Me._tbItmPoision
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmPoision = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmPots As TextBox
            Get
                Return Me._tbItmPots
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmPots = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmPrice As TextBox
            Get
                Return Me._tbItmPrice
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmPrice = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmQuest As TextBox
            Get
                Return Me._tbItmQuest
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmQuest = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmRange As TextBox
            Get
                Return Me._tbItmRange
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmRange = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmreqHP As TextBox
            Get
                Return Me._tbItmreqHP
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmreqHP = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmRun As TextBox
            Get
                Return Me._tbItmRun
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmRun = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPabs As TextBox
            Get
                Return Me._tbItmSPabs
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPabs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPatkSpd As TextBox
            Get
                Return Me._tbItmSPatkSpd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPatkSpd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPblk As TextBox
            Get
                Return Me._tbItmSPblk
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPblk = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPCrt As TextBox
            Get
                Return Me._tbItmSPCrt
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPCrt = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPdef As TextBox
            Get
                Return Me._tbItmSPdef
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPdef = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSpeed As TextBox
            Get
                Return Me._tbItmSpeed
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSpeed = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPhp As TextBox
            Get
                Return Me._tbItmSPhp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPhp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSpirit As TextBox
            Get
                Return Me._tbItmSpirit
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSpirit = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPLvl As TextBox
            Get
                Return Me._tbItmSPLvl
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPLvl = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPMp As TextBox
            Get
                Return Me._tbItmSPMp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPMp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPRange As TextBox
            Get
                Return Me._tbItmSPRange
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPRange = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPRtg As TextBox
            Get
                Return Me._tbItmSPRtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPRtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSPRun As TextBox
            Get
                Return Me._tbItmSPRun
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSPRun = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSTMAdd As TextBox
            Get
                Return Me._tbItmSTMAdd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSTMAdd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmStmRec As TextBox
            Get
                Return Me._tbItmStmRec
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmStmRec = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmSTMRegen As TextBox
            Get
                Return Me._tbItmSTMRegen
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmSTMRegen = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmStr As TextBox
            Get
                Return Me._tbItmStr
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmStr = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmTalent As TextBox
            Get
                Return Me._tbItmTalent
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmTalent = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbItmWeight As TextBox
            Get
                Return Me._tbItmWeight
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbItmWeight = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMapSpawnRate As TextBox
            Get
                Return Me._tbMapSpawnRate
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMapSpawnRate = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMapValue1 As TextBox
            Get
                Return Me._tbMapValue1
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMapValue1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMapValue2 As TextBox
            Get
                Return Me._tbMapValue2
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMapValue2 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMapValue3 As TextBox
            Get
                Return Me._tbMapValue3
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMapValue3 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMaxExp As TextBox
            Get
                Return Me._tbMaxExp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMaxExp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMaxGold As TextBox
            Get
                Return Me._tbMaxGold
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMaxGold = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoAbs As TextBox
            Get
                Return Me._tbMoAbs
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoAbs = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoApp As TextBox
            Get
                Return Me._tbMoApp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoApp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoAtkCrit As TextBox
            Get
                Return Me._tbMoAtkCrit
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoAtkCrit = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoAtkPow As TextBox
            Get
                Return Me._tbMoAtkPow
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoAtkPow = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoAtkRtg As TextBox
            Get
                Return Me._tbMoAtkRtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoAtkRtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoAtkSpd As TextBox
            Get
                Return Me._tbMoAtkSpd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoAtkSpd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoBlk As TextBox
            Get
                Return Me._tbMoBlk
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoBlk = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoChar As TextBox
            Get
                Return Me._tbMoChar
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoChar = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoDef As TextBox
            Get
                Return Me._tbMoDef
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoDef = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoExp As TextBox
            Get
                Return Me._tbMoExp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoExp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoFire As TextBox
            Get
                Return Me._tbMoFire
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoFire = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoHp As TextBox
            Get
                Return Me._tbMoHp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoHp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoIce As TextBox
            Get
                Return Me._tbMoIce
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoIce = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoInt As TextBox
            Get
                Return Me._tbMoInt
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoInt = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoLevel As TextBox
            Get
                Return Me._tbMoLevel
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoLevel = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoLtg As TextBox
            Get
                Return Me._tbMoLtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoLtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoMage As TextBox
            Get
                Return Me._tbMoMage
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoMage = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoMapName As TextBox
            Get
                Return Me._tbMoMapName
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoMapName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoMSpd As TextBox
            Get
                Return Me._tbMoMSpd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoMSpd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoMTyp As TextBox
            Get
                Return Me._tbMoMTyp
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoMTyp = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoName As TextBox
            Get
                Return Me._tbMoName
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoNoDrop As TextBox
            Get
                Return Me._tbMoNoDrop
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoNoDrop = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoOrg As TextBox
            Get
                Return Me._tbMoOrg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoOrg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoPAtkRtg As TextBox
            Get
                Return Me._tbMoPAtkRtg
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoPAtkRtg = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoPoision As TextBox
            Get
                Return Me._tbMoPoision
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoPoision = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoSize As TextBox
            Get
                Return Me._tbMoSize
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoSize = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoSKAtk As TextBox
            Get
                Return Me._tbMoSKAtk
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoSKAtk = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoSnd As TextBox
            Get
                Return Me._tbMoSnd
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoSnd = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoSpCode As TextBox
            Get
                Return Me._tbMoSpCode
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoSpCode = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbMoVision As TextBox
            Get
                Return Me._tbMoVision
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbMoVision = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCangle As TextBox
            Get
                Return Me._tbNPCangle
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCangle = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCID As TextBox
            Get
                Return Me._tbNPCID
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCID = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCJ_Chat As TextBox
            Get
                Return Me._tbNPCJ_Chat
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCJ_Chat = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCModelFile As ComboBox
            Get
                Return Me._tbNPCModelFile
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._tbNPCModelFile = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCName As TextBox
            Get
                Return Me._tbNPCName
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCName = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCSetupfile As ComboBox
            Get
                Return Me._tbNPCSetupfile
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._tbNPCSetupfile = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCSetupfileInI As ComboBox
            Get
                Return Me._tbNPCSetupfileInI
            End Get
            Set(ByVal WithEventsValue As ComboBox)
                Me._tbNPCSetupfileInI = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCx As TextBox
            Get
                Return Me._tbNPCx
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCx = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCy As TextBox
            Get
                Return Me._tbNPCy
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCy = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbNPCz As TextBox
            Get
                Return Me._tbNPCz
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbNPCz = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbServerPath As TextBox
            Get
                Return Me._tbServerPath
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbServerPath = WithEventsValue
            End Set
        End Property

        Friend Overridable Property tbWarnItem As TextBox
            Get
                Return Me._tbWarnItem
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._tbWarnItem = WithEventsValue
            End Set
        End Property

        Friend Overridable Property TextBox1 As TextBox
            Get
                Return Me._TextBox1
            End Get
            Set(ByVal WithEventsValue As TextBox)
                Me._TextBox1 = WithEventsValue
            End Set
        End Property

        Friend Overridable Property ttAll As ToolTip
            Get
                Return Me._ttAll
            End Get
            Set(ByVal WithEventsValue As ToolTip)
                Me._ttAll = WithEventsValue
            End Set
        End Property

        Friend Overridable Property UpToolStripMenuItem As ToolStripMenuItem
            Get
                Return Me._UpToolStripMenuItem
            End Get
            Set(ByVal WithEventsValue As ToolStripMenuItem)
                Dim handler As EventHandler = New EventHandler(AddressOf Me.UpToolStripMenuItem_Click)
                If (Not Me._UpToolStripMenuItem Is Nothing) Then
                    RemoveHandler Me._UpToolStripMenuItem.Click, handler
                End If
                Me._UpToolStripMenuItem = WithEventsValue
                If (Not Me._UpToolStripMenuItem Is Nothing) Then
                    AddHandler Me._UpToolStripMenuItem.Click, handler
                End If
            End Set
        End Property


        ' Fields
        <AccessedThroughProperty("AddAsNewBossToolStripMenuItem")> _
        Private _AddAsNewBossToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddDroplineToolStripMenuItem")> _
        Private _AddDroplineToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddItemsToolStripMenuItem")> _
        Private _AddItemsToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddToListToolStripMenuItem")> _
        Private _AddToListToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddToMapToolStripMenuItem")> _
        Private _AddToMapToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddToSelectedBossToolStripMenuItem")> _
        Private _AddToSelectedBossToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("AddToSeletedBossToolStripMenuItem")> _
        Private _AddToSeletedBossToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("BackupsToolStripMenuItem")> _
        Private _BackupsToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("BringBackToMapToolStripMenuItem")> _
        Private _BringBackToMapToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("Button3")> _
        Private _Button3 As Button
        <AccessedThroughProperty("cbItemMo")> _
        Private _cbItemMo As CheckBox
        <AccessedThroughProperty("cbItemSelector")> _
        Private _cbItemSelector As ComboBox
        <AccessedThroughProperty("cbMoBoss")> _
        Private _cbMoBoss As CheckBox
        <AccessedThroughProperty("cbMonsterSelector")> _
        Private _cbMonsterSelector As ComboBox
        <AccessedThroughProperty("cbMonsterSelector1")> _
        Private _cbMonsterSelector1 As ComboBox
        <AccessedThroughProperty("cbMoTyp")> _
        Private _cbMoTyp As ComboBox
        <AccessedThroughProperty("cbMoZhoonWarn")> _
        Private _cbMoZhoonWarn As CheckBox
        <AccessedThroughProperty("cbNPCAktivated")> _
        Private _cbNPCAktivated As CheckBox
        <AccessedThroughProperty("cbSelectAll")> _
        Private _cbSelectAll As CheckBox
        <AccessedThroughProperty("CBShopItem")> _
        Private _CBShopItem As ComboBox
        <AccessedThroughProperty("cbWarnMap")> _
        Private _cbWarnMap As CheckBox
        <AccessedThroughProperty("ChangeEXPOfMapToolStripMenuItem")> _
        Private _ChangeEXPOfMapToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("ChangeToolStripMenuItem")> _
        Private _ChangeToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("chItemInfo")> _
        Private _chItemInfo As CheckBox
        <AccessedThroughProperty("chMapEn")> _
        Private _chMapEn As CheckBox
        <AccessedThroughProperty("chNotFound")> _
        Private _chNotFound As CheckBox
        <AccessedThroughProperty("chPriArcher")> _
        Private _chPriArcher As CheckBox
        <AccessedThroughProperty("chPriAta")> _
        Private _chPriAta As CheckBox
        <AccessedThroughProperty("chPriFighter")> _
        Private _chPriFighter As CheckBox
        <AccessedThroughProperty("chPriKnight")> _
        Private _chPriKnight As CheckBox
        <AccessedThroughProperty("chPriMech")> _
        Private _chPriMech As CheckBox
        <AccessedThroughProperty("chPriMgs")> _
        Private _chPriMgs As CheckBox
        <AccessedThroughProperty("chPriPike")> _
        Private _chPriPike As CheckBox
        <AccessedThroughProperty("chPriPrs")> _
        Private _chPriPrs As CheckBox
        <AccessedThroughProperty("chSecArcher")> _
        Private _chSecArcher As CheckBox
        <AccessedThroughProperty("chSecAta")> _
        Private _chSecAta As CheckBox
        <AccessedThroughProperty("chSecFighter")> _
        Private _chSecFighter As CheckBox
        <AccessedThroughProperty("chSecKnight")> _
        Private _chSecKnight As CheckBox
        <AccessedThroughProperty("chSecMech")> _
        Private _chSecMech As CheckBox
        <AccessedThroughProperty("chSecMgs")> _
        Private _chSecMgs As CheckBox
        <AccessedThroughProperty("chSecPike")> _
        Private _chSecPike As CheckBox
        <AccessedThroughProperty("chSecPrs")> _
        Private _chSecPrs As CheckBox
        <AccessedThroughProperty("cmd_Check")> _
        Private _cmd_Check As Button
        <AccessedThroughProperty("CmdCheckDrop")> _
        Private _CmdCheckDrop As Button
        <AccessedThroughProperty("cmdCheckGold")> _
        Private _cmdCheckGold As Button
        <AccessedThroughProperty("cmdCheckMaps")> _
        Private _cmdCheckMaps As Button
        <AccessedThroughProperty("cmdConfigEdit")> _
        Private _cmdConfigEdit As Button
        <AccessedThroughProperty("cmdDefaultConfig")> _
        Private _cmdDefaultConfig As Button
        <AccessedThroughProperty("cmdDelBackup")> _
        Private _cmdDelBackup As Button
        <AccessedThroughProperty("cmdEditorExe")> _
        Private _cmdEditorExe As Button
        <AccessedThroughProperty("cmdItemRealName")> _
        Private _cmdItemRealName As Button
        <AccessedThroughProperty("cmdItemSave")> _
        Private _cmdItemSave As Button
        <AccessedThroughProperty("cmdLoadConfig")> _
        Private _cmdLoadConfig As Button
        <AccessedThroughProperty("cmdMapReload")> _
        Private _cmdMapReload As Button
        <AccessedThroughProperty("cmdMapSave")> _
        Private _cmdMapSave As Button
        <AccessedThroughProperty("cmdMoRealName")> _
        Private _cmdMoRealName As Button
        <AccessedThroughProperty("cmdNPCReload")> _
        Private _cmdNPCReload As Button
        <AccessedThroughProperty("cmdNPCSave")> _
        Private _cmdNPCSave As Button
        <AccessedThroughProperty("CMDNPCShopSave")> _
        Private _CMDNPCShopSave As Button
        <AccessedThroughProperty("cmdPath")> _
        Private _cmdPath As Button
        <AccessedThroughProperty("cmdReload")> _
        Private _cmdReload As Button
        <AccessedThroughProperty("cmdReload1")> _
        Private _cmdReload1 As Button
        <AccessedThroughProperty("cmdSave")> _
        Private _cmdSave As Button
        <AccessedThroughProperty("cmdSaveConfig")> _
        Private _cmdSaveConfig As Button
        <AccessedThroughProperty("cmdShowLog")> _
        Private _cmdShowLog As Button
        <AccessedThroughProperty("cmFileListItems")> _
        Private _cmFileListItems As ContextMenuStrip
        <AccessedThroughProperty("CMFilterSaver")> _
        Private _CMFilterSaver As ContextMenuStrip
        <AccessedThroughProperty("cmItemsMonster")> _
        Private _cmItemsMonster As ContextMenuStrip
        <AccessedThroughProperty("cmMapsFiles")> _
        Private _cmMapsFiles As ContextMenuStrip
        <AccessedThroughProperty("cmMonsterItem")> _
        Private _cmMonsterItem As ContextMenuStrip
        <AccessedThroughProperty("CMNPCPicturebox")> _
        Private _CMNPCPicturebox As ContextMenuStrip
        <AccessedThroughProperty("CMSAddShopItem")> _
        Private _CMSAddShopItem As ContextMenuStrip
        <AccessedThroughProperty("cmsDrops")> _
        Private _cmsDrops As ContextMenuStrip
        <AccessedThroughProperty("CMSMapBoss")> _
        Private _CMSMapBoss As ContextMenuStrip
        <AccessedThroughProperty("CMSMapMonsterToAdd")> _
        Private _CMSMapMonsterToAdd As ContextMenuStrip
        <AccessedThroughProperty("CMSMonsterInMap")> _
        Private _CMSMonsterInMap As ContextMenuStrip
        <AccessedThroughProperty("CMSNPCList")> _
        Private _CMSNPCList As ContextMenuStrip
        <AccessedThroughProperty("cnMonsterFiles")> _
        Private _cnMonsterFiles As ContextMenuStrip
        <AccessedThroughProperty("CoItemCode")> _
        Private _CoItemCode As ColumnHeader
        <AccessedThroughProperty("CoItemName")> _
        Private _CoItemName As ColumnHeader
        <AccessedThroughProperty("ColumnHeader1")> _
        Private _ColumnHeader1 As ColumnHeader
        <AccessedThroughProperty("ColumnHeader2")> _
        Private _ColumnHeader2 As ColumnHeader
        <AccessedThroughProperty("DeleteBackupToolStripMenuItem")> _
        Private _DeleteBackupToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("DeleteBackupToolStripMenuItem1")> _
        Private _DeleteBackupToolStripMenuItem1 As ToolStripMenuItem
        <AccessedThroughProperty("DeleteLineToolStripMenuItem")> _
        Private _DeleteLineToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("DeleteNPCToolStripMenuItem")> _
        Private _DeleteNPCToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("DeleteNPCToolStripMenuItem1")> _
        Private _DeleteNPCToolStripMenuItem1 As ToolStripMenuItem
        <AccessedThroughProperty("dlgFile")> _
        Private _dlgFile As OpenFileDialog
        <AccessedThroughProperty("dlgFolder")> _
        Private _dlgFolder As FolderBrowserDialog
        <AccessedThroughProperty("DownToolStripMenuItem")> _
        Private _DownToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("DropCountToolStripMenuItem1")> _
        Private _DropCountToolStripMenuItem1 As ToolStripMenuItem
        <AccessedThroughProperty("EditMonsterToolStripMenuItem")> _
        Private _EditMonsterToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("EditRateToolStripMenuItem")> _
        Private _EditRateToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("EditSpawnRateToolStripMenuItem")> _
        Private _EditSpawnRateToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("EditSpawnTimesToolStripMenuItem")> _
        Private _EditSpawnTimesToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("ExperienceToolStripMenuItem1")> _
        Private _ExperienceToolStripMenuItem1 As ToolStripMenuItem
        <AccessedThroughProperty("gb24")> _
        Private _gb24 As GroupBox
        <AccessedThroughProperty("GoldToolStripMenuItem")> _
        Private _GoldToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("GoToItemEditorToolStripMenuItem")> _
        Private _GoToItemEditorToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("GroupBox1")> _
        Private _GroupBox1 As GroupBox
        <AccessedThroughProperty("GroupBox10")> _
        Private _GroupBox10 As GroupBox
        <AccessedThroughProperty("GroupBox11")> _
        Private _GroupBox11 As GroupBox
        <AccessedThroughProperty("GroupBox12")> _
        Private _GroupBox12 As GroupBox
        <AccessedThroughProperty("GroupBox13")> _
        Private _GroupBox13 As GroupBox
        <AccessedThroughProperty("GroupBox14")> _
        Private _GroupBox14 As GroupBox
        <AccessedThroughProperty("GroupBox15")> _
        Private _GroupBox15 As GroupBox
        <AccessedThroughProperty("GroupBox16")> _
        Private _GroupBox16 As GroupBox
        <AccessedThroughProperty("GroupBox17")> _
        Private _GroupBox17 As GroupBox
        <AccessedThroughProperty("GroupBox18")> _
        Private _GroupBox18 As GroupBox
        <AccessedThroughProperty("GroupBox19")> _
        Private _GroupBox19 As GroupBox
        <AccessedThroughProperty("GroupBox2")> _
        Private _GroupBox2 As GroupBox
        <AccessedThroughProperty("GroupBox20")> _
        Private _GroupBox20 As GroupBox
        <AccessedThroughProperty("GroupBox21")> _
        Private _GroupBox21 As GroupBox
        <AccessedThroughProperty("GroupBox22")> _
        Private _GroupBox22 As GroupBox
        <AccessedThroughProperty("GroupBox23")> _
        Private _GroupBox23 As GroupBox
        <AccessedThroughProperty("GroupBox3")> _
        Private _GroupBox3 As GroupBox
        <AccessedThroughProperty("GroupBox4")> _
        Private _GroupBox4 As GroupBox
        <AccessedThroughProperty("GroupBox5")> _
        Private _GroupBox5 As GroupBox
        <AccessedThroughProperty("GroupBox6")> _
        Private _GroupBox6 As GroupBox
        <AccessedThroughProperty("GroupBox7")> _
        Private _GroupBox7 As GroupBox
        <AccessedThroughProperty("GroupBox8")> _
        Private _GroupBox8 As GroupBox
        <AccessedThroughProperty("GroupBox9")> _
        Private _GroupBox9 As GroupBox
        <AccessedThroughProperty("ItemDistribToolStripMenuItem")> _
        Private _ItemDistribToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("ItemFound")> _
        Private _ItemFound As Label
        <AccessedThroughProperty("ItemToolStripMenuItem")> _
        Private _ItemToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("Label1")> _
        Private _Label1 As Label
        <AccessedThroughProperty("Label10")> _
        Private _Label10 As Label
        <AccessedThroughProperty("Label100")> _
        Private _Label100 As Label
        <AccessedThroughProperty("Label101")> _
        Private _Label101 As Label
        <AccessedThroughProperty("Label106")> _
        Private _Label106 As Label
        <AccessedThroughProperty("Label107")> _
        Private _Label107 As Label
        <AccessedThroughProperty("Label108")> _
        Private _Label108 As Label
        <AccessedThroughProperty("Label109")> _
        Private _Label109 As Label
        <AccessedThroughProperty("Label11")> _
        Private _Label11 As Label
        <AccessedThroughProperty("Label110")> _
        Private _Label110 As Label
        <AccessedThroughProperty("Label111")> _
        Private _Label111 As Label
        <AccessedThroughProperty("Label112")> _
        Private _Label112 As Label
        <AccessedThroughProperty("Label113")> _
        Private _Label113 As Label
        <AccessedThroughProperty("Label114")> _
        Private _Label114 As Label
        <AccessedThroughProperty("Label115")> _
        Private _Label115 As Label
        <AccessedThroughProperty("Label116")> _
        Private _Label116 As Label
        <AccessedThroughProperty("Label117")> _
        Private _Label117 As Label
        <AccessedThroughProperty("Label12")> _
        Private _Label12 As Label
        <AccessedThroughProperty("Label13")> _
        Private _Label13 As Label
        <AccessedThroughProperty("Label14")> _
        Private _Label14 As Label
        <AccessedThroughProperty("Label15")> _
        Private _Label15 As Label
        <AccessedThroughProperty("Label16")> _
        Private _Label16 As Label
        <AccessedThroughProperty("Label17")> _
        Private _Label17 As Label
        <AccessedThroughProperty("Label18")> _
        Private _Label18 As Label
        <AccessedThroughProperty("Label19")> _
        Private _Label19 As Label
        <AccessedThroughProperty("Label2")> _
        Private _Label2 As Label
        <AccessedThroughProperty("Label20")> _
        Private _Label20 As Label
        <AccessedThroughProperty("Label21")> _
        Private _Label21 As Label
        <AccessedThroughProperty("Label22")> _
        Private _Label22 As Label
        <AccessedThroughProperty("Label23")> _
        Private _Label23 As Label
        <AccessedThroughProperty("Label24")> _
        Private _Label24 As Label
        <AccessedThroughProperty("Label25")> _
        Private _Label25 As Label
        <AccessedThroughProperty("Label26")> _
        Private _Label26 As Label
        <AccessedThroughProperty("Label27")> _
        Private _Label27 As Label
        <AccessedThroughProperty("Label28")> _
        Private _Label28 As Label
        <AccessedThroughProperty("Label29")> _
        Private _Label29 As Label
        <AccessedThroughProperty("Label3")> _
        Private _Label3 As Label
        <AccessedThroughProperty("Label30")> _
        Private _Label30 As Label
        <AccessedThroughProperty("Label31")> _
        Private _Label31 As Label
        <AccessedThroughProperty("Label32")> _
        Private _Label32 As Label
        <AccessedThroughProperty("Label33")> _
        Private _Label33 As Label
        <AccessedThroughProperty("Label34")> _
        Private _Label34 As Label
        <AccessedThroughProperty("Label35")> _
        Private _Label35 As Label
        <AccessedThroughProperty("Label36")> _
        Private _Label36 As Label
        <AccessedThroughProperty("Label37")> _
        Private _Label37 As Label
        <AccessedThroughProperty("Label38")> _
        Private _Label38 As Label
        <AccessedThroughProperty("Label39")> _
        Private _Label39 As Label
        <AccessedThroughProperty("Label4")> _
        Private _Label4 As Label
        <AccessedThroughProperty("Label40")> _
        Private _Label40 As Label
        <AccessedThroughProperty("Label41")> _
        Private _Label41 As Label
        <AccessedThroughProperty("Label42")> _
        Private _Label42 As Label
        <AccessedThroughProperty("Label43")> _
        Private _Label43 As Label
        <AccessedThroughProperty("Label44")> _
        Private _Label44 As Label
        <AccessedThroughProperty("Label45")> _
        Private _Label45 As Label
        <AccessedThroughProperty("Label46")> _
        Private _Label46 As Label
        <AccessedThroughProperty("Label47")> _
        Private _Label47 As Label
        <AccessedThroughProperty("Label48")> _
        Private _Label48 As Label
        <AccessedThroughProperty("Label49")> _
        Private _Label49 As Label
        <AccessedThroughProperty("Label5")> _
        Private _Label5 As Label
        <AccessedThroughProperty("Label50")> _
        Private _Label50 As Label
        <AccessedThroughProperty("Label51")> _
        Private _Label51 As Label
        <AccessedThroughProperty("Label52")> _
        Private _Label52 As Label
        <AccessedThroughProperty("Label53")> _
        Private _Label53 As Label
        <AccessedThroughProperty("Label54")> _
        Private _Label54 As Label
        <AccessedThroughProperty("Label55")> _
        Private _Label55 As Label
        <AccessedThroughProperty("Label56")> _
        Private _Label56 As Label
        <AccessedThroughProperty("Label57")> _
        Private _Label57 As Label
        <AccessedThroughProperty("Label58")> _
        Private _Label58 As Label
        <AccessedThroughProperty("Label59")> _
        Private _Label59 As Label
        <AccessedThroughProperty("Label6")> _
        Private _Label6 As Label
        <AccessedThroughProperty("Label60")> _
        Private _Label60 As Label
        <AccessedThroughProperty("Label61")> _
        Private _Label61 As Label
        <AccessedThroughProperty("Label62")> _
        Private _Label62 As Label
        <AccessedThroughProperty("Label63")> _
        Private _Label63 As Label
        <AccessedThroughProperty("Label64")> _
        Private _Label64 As Label
        <AccessedThroughProperty("Label65")> _
        Private _Label65 As Label
        <AccessedThroughProperty("Label66")> _
        Private _Label66 As Label
        <AccessedThroughProperty("Label67")> _
        Private _Label67 As Label
        <AccessedThroughProperty("Label68")> _
        Private _Label68 As Label
        <AccessedThroughProperty("Label69")> _
        Private _Label69 As Label
        <AccessedThroughProperty("Label7")> _
        Private _Label7 As Label
        <AccessedThroughProperty("Label70")> _
        Private _Label70 As Label
        <AccessedThroughProperty("Label71")> _
        Private _Label71 As Label
        <AccessedThroughProperty("Label72")> _
        Private _Label72 As Label
        <AccessedThroughProperty("Label73")> _
        Private _Label73 As Label
        <AccessedThroughProperty("Label74")> _
        Private _Label74 As Label
        <AccessedThroughProperty("Label75")> _
        Private _Label75 As Label
        <AccessedThroughProperty("Label76")> _
        Private _Label76 As Label
        <AccessedThroughProperty("Label77")> _
        Private _Label77 As Label
        <AccessedThroughProperty("Label78")> _
        Private _Label78 As Label
        <AccessedThroughProperty("Label79")> _
        Private _Label79 As Label
        <AccessedThroughProperty("Label8")> _
        Private _Label8 As Label
        <AccessedThroughProperty("Label80")> _
        Private _Label80 As Label
        <AccessedThroughProperty("Label81")> _
        Private _Label81 As Label
        <AccessedThroughProperty("Label82")> _
        Private _Label82 As Label
        <AccessedThroughProperty("Label83")> _
        Private _Label83 As Label
        <AccessedThroughProperty("Label84")> _
        Private _Label84 As Label
        <AccessedThroughProperty("Label85")> _
        Private _Label85 As Label
        <AccessedThroughProperty("Label86")> _
        Private _Label86 As Label
        <AccessedThroughProperty("Label87")> _
        Private _Label87 As Label
        <AccessedThroughProperty("Label88")> _
        Private _Label88 As Label
        <AccessedThroughProperty("Label89")> _
        Private _Label89 As Label
        <AccessedThroughProperty("Label9")> _
        Private _Label9 As Label
        <AccessedThroughProperty("Label90")> _
        Private _Label90 As Label
        <AccessedThroughProperty("Label91")> _
        Private _Label91 As Label
        <AccessedThroughProperty("Label92")> _
        Private _Label92 As Label
        <AccessedThroughProperty("Label93")> _
        Private _Label93 As Label
        <AccessedThroughProperty("Label94")> _
        Private _Label94 As Label
        <AccessedThroughProperty("Label95")> _
        Private _Label95 As Label
        <AccessedThroughProperty("Label96")> _
        Private _Label96 As Label
        <AccessedThroughProperty("Label97")> _
        Private _Label97 As Label
        <AccessedThroughProperty("Label98")> _
        Private _Label98 As Label
        <AccessedThroughProperty("Label99")> _
        Private _Label99 As Label
        <AccessedThroughProperty("lbFileListItems")> _
        Private _lbFileListItems As ListBox
        <AccessedThroughProperty("lbFiles")> _
        Private _lbFiles As ListBox
        <AccessedThroughProperty("lbFilesMaps")> _
        Private _lbFilesMaps As ListBox
        <AccessedThroughProperty("lbFound")> _
        Private _lbFound As Label
        <AccessedThroughProperty("lbItemFiles")> _
        Private _lbItemFiles As ListBox
        <AccessedThroughProperty("lbItemMo")> _
        Private _lbItemMo As ListBox
        <AccessedThroughProperty("lbItemsListCount")> _
        Private _lbItemsListCount As Label
        <AccessedThroughProperty("lbItemsRealName")> _
        Private _lbItemsRealName As ListBox
        <AccessedThroughProperty("lblMoListName")> _
        Private _lblMoListName As Label
        <AccessedThroughProperty("lblprgV")> _
        Private _lblprgV As Label
        <AccessedThroughProperty("lblProg")> _
        Private _lblProg As Label
        <AccessedThroughProperty("lblTextCoding")> _
        Private _lblTextCoding As Label
        <AccessedThroughProperty("lbMaps")> _
        Private _lbMaps As ListBox
        <AccessedThroughProperty("lbNPCList")> _
        Private _lbNPCList As ListBox
        <AccessedThroughProperty("lbNPCMapFileList")> _
        Private _lbNPCMapFileList As ListBox
        <AccessedThroughProperty("ListBox1")> _
        Private _ListBox1 As ListBox
        <AccessedThroughProperty("ListView1")> _
        Private _ListView1 As ListView
        <AccessedThroughProperty("ListView2")> _
        Private _ListView2 As ListView
        <AccessedThroughProperty("ListView3")> _
        Private _ListView3 As ListView
        <AccessedThroughProperty("LoadBackupToolStripMenuItem")> _
        Private _LoadBackupToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("LoadFilterToolStripMenuItem")> _
        Private _LoadFilterToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("LWAddSpawnCount")> _
        Private _LWAddSpawnCount As ColumnHeader
        <AccessedThroughProperty("lwBossAddMonster")> _
        Private _lwBossAddMonster As ColumnHeader
        <AccessedThroughProperty("lwBossAddMonsterRealName")> _
        Private _lwBossAddMonsterRealName As ColumnHeader
        <AccessedThroughProperty("lwBossFileName")> _
        Private _lwBossFileName As ColumnHeader
        <AccessedThroughProperty("LWBossRealName")> _
        Private _LWBossRealName As ColumnHeader
        <AccessedThroughProperty("LWBossSpawnTimes")> _
        Private _LWBossSpawnTimes As ColumnHeader
        <AccessedThroughProperty("lwItems")> _
        Private _lwItems As ListView
        <AccessedThroughProperty("lwMonsterName")> _
        Private _lwMonsterName As ColumnHeader
        <AccessedThroughProperty("lwMoRealName")> _
        Private _lwMoRealName As ColumnHeader
        <AccessedThroughProperty("LWNPCshop")> _
        Private _LWNPCshop As ListView
        <AccessedThroughProperty("lwSpawnRate")> _
        Private _lwSpawnRate As ColumnHeader
        <AccessedThroughProperty("Mapsfound")> _
        Private _Mapsfound As Label
        <AccessedThroughProperty("MoFound")> _
        Private _MoFound As Label
        <AccessedThroughProperty("pbWorking")> _
        Private _pbWorking As ProgressBar
        <AccessedThroughProperty("PictureBox1")> _
        Private _PictureBox1 As PictureBox
        <AccessedThroughProperty("RemoveAllToolStripMenuItem")> _
        Private _RemoveAllToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("RemoveAllToolStripMenuItem1")> _
        Private _RemoveAllToolStripMenuItem1 As ToolStripMenuItem
        <AccessedThroughProperty("RemoveFromListToolStripMenuItem")> _
        Private _RemoveFromListToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("RemoveItemToolStripMenuItem")> _
        Private _RemoveItemToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("RemoveMonsterToolStripMenuItem")> _
        Private _RemoveMonsterToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("RemoveToolStripMenuItem")> _
        Private _RemoveToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("SaveMonstersToolStripMenuItem")> _
        Private _SaveMonstersToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("SaveToolStripMenuItem")> _
        Private _SaveToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("SeachForItemNameToolStripMenuItem")> _
        Private _SeachForItemNameToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("SendToItemSearcherToolStripMenuItem")> _
        Private _SendToItemSearcherToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("Settings")> _
        Private _Settings As GroupBox
        <AccessedThroughProperty("ShowToolStripMenuItem")> _
        Private _ShowToolStripMenuItem As ToolStripMenuItem
        <AccessedThroughProperty("TabControl1")> _
        Private _TabControl1 As TabControl
        <AccessedThroughProperty("TabPage1")> _
        Private _TabPage1 As TabPage
        <AccessedThroughProperty("TabPage2")> _
        Private _TabPage2 As TabPage
        <AccessedThroughProperty("TabPage3")> _
        Private _TabPage3 As TabPage
        <AccessedThroughProperty("TabPage4")> _
        Private _TabPage4 As TabPage
        <AccessedThroughProperty("TabPage5")> _
        Private _TabPage5 As TabPage
        <AccessedThroughProperty("tbDroprate")> _
        Private _tbDroprate As TextBox
        <AccessedThroughProperty("tbDrops")> _
        Private _tbDrops As TextBox
        <AccessedThroughProperty("tbEditorPath")> _
        Private _tbEditorPath As TextBox
        <AccessedThroughProperty("tbItmAbs")> _
        Private _tbItmAbs As TextBox
        <AccessedThroughProperty("tbItmAgi")> _
        Private _tbItmAgi As TextBox
        <AccessedThroughProperty("tbItmAPT")> _
        Private _tbItmAPT As TextBox
        <AccessedThroughProperty("tbItmAtkPow")> _
        Private _tbItmAtkPow As TextBox
        <AccessedThroughProperty("tbItmAtkRtg")> _
        Private _tbItmAtkRtg As TextBox
        <AccessedThroughProperty("tbItmBlk")> _
        Private _tbItmBlk As TextBox
        <AccessedThroughProperty("tbItmCode")> _
        Private _tbItmCode As TextBox
        <AccessedThroughProperty("tbItmCrtRtg")> _
        Private _tbItmCrtRtg As TextBox
        <AccessedThroughProperty("tbItmdef")> _
        Private _tbItmdef As TextBox
        <AccessedThroughProperty("tbItmFire")> _
        Private _tbItmFire As TextBox
        <AccessedThroughProperty("tbItmFrost")> _
        Private _tbItmFrost As TextBox
        <AccessedThroughProperty("tbItmGlow")> _
        Private _tbItmGlow As TextBox
        <AccessedThroughProperty("tbItmHPAdd")> _
        Private _tbItmHPAdd As TextBox
        <AccessedThroughProperty("tbItmHPRec")> _
        Private _tbItmHPRec As TextBox
        <AccessedThroughProperty("tbItmHPRegen")> _
        Private _tbItmHPRegen As TextBox
        <AccessedThroughProperty("tbItmInGameNAme")> _
        Private _tbItmInGameNAme As TextBox
        <AccessedThroughProperty("tbItmIntegrity")> _
        Private _tbItmIntegrity As TextBox
        <AccessedThroughProperty("tbItmJpName")> _
        Private _tbItmJpName As TextBox
        <AccessedThroughProperty("tbItmLevel")> _
        Private _tbItmLevel As TextBox
        <AccessedThroughProperty("tbItmLighting")> _
        Private _tbItmLighting As TextBox
        <AccessedThroughProperty("tbItmManaRec")> _
        Private _tbItmManaRec As TextBox
        <AccessedThroughProperty("tbItmMPAdd")> _
        Private _tbItmMPAdd As TextBox
        <AccessedThroughProperty("tbItmMPRegen")> _
        Private _tbItmMPRegen As TextBox
        <AccessedThroughProperty("tbItmName")> _
        Private _tbItmName As TextBox
        <AccessedThroughProperty("tbItmOrganic")> _
        Private _tbItmOrganic As TextBox
        <AccessedThroughProperty("tbItmPoision")> _
        Private _tbItmPoision As TextBox
        <AccessedThroughProperty("tbItmPots")> _
        Private _tbItmPots As TextBox
        <AccessedThroughProperty("tbItmPrice")> _
        Private _tbItmPrice As TextBox
        <AccessedThroughProperty("tbItmQuest")> _
        Private _tbItmQuest As TextBox
        <AccessedThroughProperty("tbItmRange")> _
        Private _tbItmRange As TextBox
        <AccessedThroughProperty("tbItmreqHP")> _
        Private _tbItmreqHP As TextBox
        <AccessedThroughProperty("tbItmRun")> _
        Private _tbItmRun As TextBox
        <AccessedThroughProperty("tbItmSPabs")> _
        Private _tbItmSPabs As TextBox
        <AccessedThroughProperty("tbItmSPatkSpd")> _
        Private _tbItmSPatkSpd As TextBox
        <AccessedThroughProperty("tbItmSPblk")> _
        Private _tbItmSPblk As TextBox
        <AccessedThroughProperty("tbItmSPCrt")> _
        Private _tbItmSPCrt As TextBox
        <AccessedThroughProperty("tbItmSPdef")> _
        Private _tbItmSPdef As TextBox
        <AccessedThroughProperty("tbItmSpeed")> _
        Private _tbItmSpeed As TextBox
        <AccessedThroughProperty("tbItmSPhp")> _
        Private _tbItmSPhp As TextBox
        <AccessedThroughProperty("tbItmSpirit")> _
        Private _tbItmSpirit As TextBox
        <AccessedThroughProperty("tbItmSPLvl")> _
        Private _tbItmSPLvl As TextBox
        <AccessedThroughProperty("tbItmSPMp")> _
        Private _tbItmSPMp As TextBox
        <AccessedThroughProperty("tbItmSPRange")> _
        Private _tbItmSPRange As TextBox
        <AccessedThroughProperty("tbItmSPRtg")> _
        Private _tbItmSPRtg As TextBox
        <AccessedThroughProperty("tbItmSPRun")> _
        Private _tbItmSPRun As TextBox
        <AccessedThroughProperty("tbItmSTMAdd")> _
        Private _tbItmSTMAdd As TextBox
        <AccessedThroughProperty("tbItmStmRec")> _
        Private _tbItmStmRec As TextBox
        <AccessedThroughProperty("tbItmSTMRegen")> _
        Private _tbItmSTMRegen As TextBox
        <AccessedThroughProperty("tbItmStr")> _
        Private _tbItmStr As TextBox
        <AccessedThroughProperty("tbItmTalent")> _
        Private _tbItmTalent As TextBox
        <AccessedThroughProperty("tbItmWeight")> _
        Private _tbItmWeight As TextBox
        <AccessedThroughProperty("tbMapSpawnRate")> _
        Private _tbMapSpawnRate As TextBox
        <AccessedThroughProperty("tbMapValue1")> _
        Private _tbMapValue1 As TextBox
        <AccessedThroughProperty("tbMapValue2")> _
        Private _tbMapValue2 As TextBox
        <AccessedThroughProperty("tbMapValue3")> _
        Private _tbMapValue3 As TextBox
        <AccessedThroughProperty("tbMaxExp")> _
        Private _tbMaxExp As TextBox
        <AccessedThroughProperty("tbMaxGold")> _
        Private _tbMaxGold As TextBox
        <AccessedThroughProperty("tbMoAbs")> _
        Private _tbMoAbs As TextBox
        <AccessedThroughProperty("tbMoApp")> _
        Private _tbMoApp As TextBox
        <AccessedThroughProperty("tbMoAtkCrit")> _
        Private _tbMoAtkCrit As TextBox
        <AccessedThroughProperty("tbMoAtkPow")> _
        Private _tbMoAtkPow As TextBox
        <AccessedThroughProperty("tbMoAtkRtg")> _
        Private _tbMoAtkRtg As TextBox
        <AccessedThroughProperty("tbMoAtkSpd")> _
        Private _tbMoAtkSpd As TextBox
        <AccessedThroughProperty("tbMoBlk")> _
        Private _tbMoBlk As TextBox
        <AccessedThroughProperty("tbMoChar")> _
        Private _tbMoChar As TextBox
        <AccessedThroughProperty("tbMoDef")> _
        Private _tbMoDef As TextBox
        <AccessedThroughProperty("tbMoExp")> _
        Private _tbMoExp As TextBox
        <AccessedThroughProperty("tbMoFire")> _
        Private _tbMoFire As TextBox
        <AccessedThroughProperty("tbMoHp")> _
        Private _tbMoHp As TextBox
        <AccessedThroughProperty("tbMoIce")> _
        Private _tbMoIce As TextBox
        <AccessedThroughProperty("tbMoInt")> _
        Private _tbMoInt As TextBox
        <AccessedThroughProperty("tbMoLevel")> _
        Private _tbMoLevel As TextBox
        <AccessedThroughProperty("tbMoLtg")> _
        Private _tbMoLtg As TextBox
        <AccessedThroughProperty("tbMoMage")> _
        Private _tbMoMage As TextBox
        <AccessedThroughProperty("tbMoMapName")> _
        Private _tbMoMapName As TextBox
        <AccessedThroughProperty("tbMoMSpd")> _
        Private _tbMoMSpd As TextBox
        <AccessedThroughProperty("tbMoMTyp")> _
        Private _tbMoMTyp As TextBox
        <AccessedThroughProperty("tbMoName")> _
        Private _tbMoName As TextBox
        <AccessedThroughProperty("tbMoNoDrop")> _
        Private _tbMoNoDrop As TextBox
        <AccessedThroughProperty("tbMoOrg")> _
        Private _tbMoOrg As TextBox
        <AccessedThroughProperty("tbMoPAtkRtg")> _
        Private _tbMoPAtkRtg As TextBox
        <AccessedThroughProperty("tbMoPoision")> _
        Private _tbMoPoision As TextBox
        <AccessedThroughProperty("tbMoSize")> _
        Private _tbMoSize As TextBox
        <AccessedThroughProperty("tbMoSKAtk")> _
        Private _tbMoSKAtk As TextBox
        <AccessedThroughProperty("tbMoSnd")> _
        Private _tbMoSnd As TextBox
        <AccessedThroughProperty("tbMoSpCode")> _
        Private _tbMoSpCode As TextBox
        <AccessedThroughProperty("tbMoVision")> _
        Private _tbMoVision As TextBox
        <AccessedThroughProperty("tbNPCangle")> _
        Private _tbNPCangle As TextBox
        <AccessedThroughProperty("tbNPCID")> _
        Private _tbNPCID As TextBox
        <AccessedThroughProperty("tbNPCJ_Chat")> _
        Private _tbNPCJ_Chat As TextBox
        <AccessedThroughProperty("tbNPCModelFile")> _
        Private _tbNPCModelFile As ComboBox
        <AccessedThroughProperty("tbNPCName")> _
        Private _tbNPCName As TextBox
        <AccessedThroughProperty("tbNPCSetupfile")> _
        Private _tbNPCSetupfile As ComboBox
        <AccessedThroughProperty("tbNPCSetupfileInI")> _
        Private _tbNPCSetupfileInI As ComboBox
        <AccessedThroughProperty("tbNPCx")> _
        Private _tbNPCx As TextBox
        <AccessedThroughProperty("tbNPCy")> _
        Private _tbNPCy As TextBox
        <AccessedThroughProperty("tbNPCz")> _
        Private _tbNPCz As TextBox
        <AccessedThroughProperty("tbServerPath")> _
        Private _tbServerPath As TextBox
        <AccessedThroughProperty("tbWarnItem")> _
        Private _tbWarnItem As TextBox
        <AccessedThroughProperty("TextBox1")> _
        Private _TextBox1 As TextBox
        <AccessedThroughProperty("ttAll")> _
        Private _ttAll As ToolTip
        <AccessedThroughProperty("UpToolStripMenuItem")> _
        Private _UpToolStripMenuItem As ToolStripMenuItem
        Private components As IContainer
    End Class
End Namespace

