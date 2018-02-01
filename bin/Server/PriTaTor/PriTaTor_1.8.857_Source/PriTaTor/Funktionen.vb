Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports PriTaTor.My
Imports System
Imports System.Collections
Imports System.Data
Imports System.IO
Imports System.Runtime.InteropServices
Imports System.Text
Imports System.Windows.Forms

Namespace PriTaTor
    <StandardModule> _
    Friend NotInheritable Class Funktionen
        ' Methods
        Public Shared Function CheckGold(ByVal MonsterIndex As Long, ByVal MaxGold As Long) As Boolean
            Dim strArray As String() = New String(&H3E9  - 1) {}
            Dim flag As Boolean = False
            Try 
                Dim num2 As Long
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)) <> "End of File")
                    If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Contains(ChrW(181) & ChrW(183))) Then
                        strArray = Strings.Split(Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Substring(Strings.Len("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))).Trim(New Char() { ChrW(9) }).Replace(ChrW(9), " "), " ", -1, CompareMethod.Binary)
                        Dim num4 As Long = (strArray.Length - 1)
                        Dim i As Long = 2
                        Do While (i <= num4)
                            If Not strArray(CInt(i)).Contains(ChrW(181) & ChrW(183)) Then
                                Dim num As Long
                                Try 
                                    num = Conversions.ToLong(strArray(CInt(i)))
                                Catch exception1 As Exception
                                    ProjectData.SetProjectError(exception1)
                                    ProjectData.ClearProjectError
                                End Try
                                If (num > MaxGold) Then
                                    flag = True
                                End If
                            End If
                            i = (i + 1)
                        Loop
                    End If
                    num2 = (num2 + 1)
                Loop
                num2 = 0
            Catch exception2 As Exception
                ProjectData.SetProjectError(exception2)
                Dim exception As Exception = exception2
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "Button Check Drops" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return flag
        End Function

        Public Shared Function CheckMaxValues(ByVal MonsterIndex As Long, ByVal ToCheck As String, ByVal Maximum As Long) As Boolean
            Dim flag As Boolean
            Dim strArray As String() = New String(&H3E9  - 1) {}
            Try 
                Dim num2 As Long
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith(ToCheck)) Then
                        Dim num As Long
                        Try 
                            num = Conversions.ToLong(Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Substring(Strings.Len(ToCheck)))
                        Catch exception1 As Exception
                            ProjectData.SetProjectError(exception1)
                            ProjectData.ClearProjectError
                        End Try
                        If (num > Maximum) Then
                            flag = True
                        Else
                            flag = False
                        End If
                    End If
                    num2 = (num2 + 1)
                Loop
                num2 = 0
            Catch exception2 As Exception
                ProjectData.SetProjectError(exception2)
                Dim exception As Exception = exception2
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "CheckMaxValues" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return flag
        End Function

        Public Shared Function FindenText(ByVal MonsterIndex As Long, ByVal Such As String, ByVal wert As String) As String
            Dim str As String
            Dim num As Long = 0
            Try 
                str = ""
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)) <> "End of File")
                    If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).StartsWith(Such)) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).ToLower.Contains(wert.ToLower)) Then
                        Return Konstanten.MonsterFiles(CInt(MonsterIndex))
                    End If
                    num = (num + 1)
                Loop
                str = ""
                num = 0
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "FindenText" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function FindenZahl(ByVal Such As String, ByVal wert As Double) As Double
            Dim num2 As Double
            Dim num3 As Long = 0
            Dim num4 As Long = 0
            Dim num As Long = 0
            Try 
                goto Label_00AD
            Label_000E:
                If (Konstanten.MonsterDatenListe(CInt(num3), CInt(num4)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(num3), CInt(num4)).StartsWith(Such)) Then
                    If (Conversions.ToLong(Konstanten.MonsterDatenListe(CInt(num3), CInt(num4)).Substring(Strings.Len(Such))) = wert) Then
                        Konstanten.GefundenZahl(CInt(num)) = Konstanten.MonsterFiles(CInt(num3))
                        num = (num + 1)
                    Else
                        num2 = 0
                    End If
                End If
                num4 = (num4 + 1)
            Label_0086:
                If (Konstanten.MonsterDatenListe(CInt(num3), CInt(num4)) <> "End of File") Then
                    goto Label_000E
                End If
                num4 = 0
                num3 = (num3 + 1)
            Label_00AD:
                If (Konstanten.MonsterFiles(CInt(num3)) <> "") Then
                    goto Label_0086
                End If
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "FindenZahl" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num2
        End Function

        Public Shared Function GetItemCode(ByVal ItemIndex As Long) As String
            Dim str As String = ""
            Dim num As Long = 0
            Try 
                Do While (Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)) <> "End of File")
                    If (Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)).StartsWith("*") AndAlso Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)).StartsWith("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229))) Then
                        Return Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)).Substring(Strings.Len("*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229))).Trim.Replace(" ", " ").Replace(ChrW(9), " ")
                    End If
                    num = (num + 1)
                Loop
                str = ""
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetItemCode" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function GetItemIndex(ByVal ItemFileName As String) As Long
            Dim num As Long
            Dim num2 As Long = 0
            Try 
                Do While Not ((Konstanten.ItemFiles(CInt(num2)) = "") Or (Konstanten.ItemFiles(CInt(num2)) = Nothing))
                    If (Konstanten.ItemFiles(CInt(num2)) = ItemFileName) Then
                        Return num2
                    End If
                    num2 = (num2 + 1)
                Loop
                num = -1
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetItemIndex" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function GetMapIndex(ByVal MapName As String) As Long
            Dim num2 As Long
            Do While (Konstanten.MapFiles(CInt(num2)) <> "")
                If (Konstanten.MapFiles(CInt(num2)) = MapName) Then
                    Return num2
                End If
                num2 = (num2 + 1)
            Loop
            Return -1
        End Function

        Public Shared Function GetMonsterExp(ByVal Index As Long) As Long
            Dim num As Long
            Dim num2 As Long = 0
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).StartsWith("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161))) Then
                        num = Conversions.ToLong(Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).Substring(Strings.Len("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161))).Trim.ToString)
                    End If
                    num2 = (num2 + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterExp" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function GetMonsterGold(ByVal MonsterIndex As Long) As String
            Dim str As String
            Dim num2 As Long = 0
            Dim num As Long = 0
            Try 
                str = ""
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)) <> "End of File")
                    If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Contains(ChrW(181) & ChrW(183))) Then
                        Do While (Conversions.ToString(Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Chars(CInt(num))) <> ChrW(181))
                            num = (num + 1)
                        Loop
                        Return Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num2)).Remove(0, CInt((num + 2))).Trim(New Char() { ChrW(9) })
                    End If
                    num2 = (num2 + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterGold" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function GetMonsterIndex(ByVal MonsterFile As String) As Long
            Dim num As Long
            Dim num2 As Long = 0
            Try 
                Do While (Konstanten.MonsterFiles(CInt(num2)) <> "")
                    If (Konstanten.MonsterFiles(CInt(num2)) = MonsterFile) Then
                        Return num2
                    End If
                    num2 = (num2 + 1)
                Loop
                num = -1
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterIndex" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function GetMonsterInGameName(ByVal MonNamePath As String) As String
            Dim str As String
            Try 
                str = ""
                If MonNamePath.Contains(":") Then
                    If File.Exists(Konstanten.MoNamePath.Trim(New Char() { """"c })) Then
                        Return Funktionen.GetMonsterName(MonNamePath)
                    End If
                    If MySettingsProperty.Settings.WarnMoZhoon Then
                        Interaction.MsgBox(("No .zhoon file found! " & ChrW(13) & ChrW(10) & MonNamePath.Trim(New Char() { """"c })), MsgBoxStyle.OkOnly, Nothing)
                    End If
                    Funktionen.WriteErrorLog((("In GetMonsterInGameName:" & ChrW(13) & ChrW(10) & "Cant find path:" & Konstanten.sPath & "GameServer\Monster\" & MonNamePath.Trim(New Char() { """"c }))))
                    Return "Name not found!"
                End If
                If File.Exists((Konstanten.sPath & "GameServer\Monster\" & MonNamePath.Trim(New Char() { """"c }))) Then
                    Konstanten.MoNamePath = (Konstanten.sPath & "GameServer\Monster\" & MonNamePath.Trim(New Char() { """"c }))
                    Return Funktionen.GetMonsterName(Konstanten.MoNamePath)
                End If
                If MySettingsProperty.Settings.WarnMoZhoon Then
                    Interaction.MsgBox(("No .zhoon file found! " & ChrW(13) & ChrW(10) & Konstanten.MoNamePath.Trim(New Char() { """"c })), MsgBoxStyle.OkOnly, Nothing)
                End If
                Funktionen.WriteErrorLog((("In GetMonsterInGameName:" & ChrW(13) & ChrW(10) & "Cant find path:" & Konstanten.sPath & "GameServer\Monster\" & Konstanten.MoNamePath.Trim(New Char() { """"c }))))
                str = "Name not found!"
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetInGameName" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function GetMonsterItemInfo(ByVal MonsterIndex As Long, ByVal ItemCode As String) As String
            Dim str As String
            Dim num As Long = 0
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)) <> "End of File")
                    If ((Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).StartsWith("*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219))) AndAlso Konstanten.MonsterDatenListe(CInt(MonsterIndex), CInt(num)).ToUpper.Contains(ItemCode.Trim(New Char() { """"c }).ToUpper)) Then
                        Return Konstanten.MonsterFiles(CInt(MonsterIndex))
                    End If
                    num = (num + 1)
                Loop
                str = ""
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterItemInfo" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function GetMonsterLVL(ByVal Index As Long) As Long
            Dim num As Long
            Dim num2 As Long = 0
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).StartsWith("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167))) Then
                        num = Conversions.ToLong(Konstanten.MonsterDatenListe(CInt(Index), CInt(num2)).Substring(Strings.Len("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167))).Trim.ToString)
                    End If
                    num2 = (num2 + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterLVL" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function GetMonsterName(ByVal Path As String) As String
            Dim str As String
            Try 
                str = ""
                Dim reader As New StreamReader(Path.Trim(New Char() { """"c }), Konstanten.enc)
                Do While (reader.Peek <> -1)
                    Dim str2 As String = reader.ReadLine
                    If str2.Contains("*J_") Then
                        str = str2.Substring(7).ToString.Trim
                        reader.Close
                        Return str
                    End If
                    str = ""
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "GetMonsterName" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                str = ""
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Function GetNPCShopItems(ByVal File As String, ByVal ShopCode As String) As ArrayList
            Dim list2 As New ArrayList
            If File.Exists(File) Then
                Dim num As Integer
                Dim reader As New StreamReader(File, Konstanten.enc)
                Dim str2 As String = ""
                Dim str As String = ""
                Do While (reader.Peek <> -1)
                    str2 = reader.ReadLine
                    If str2.StartsWith(ShopCode) Then
                        Exit Do
                    End If
                Loop
                If ((reader.Peek = -1) And Not str2.StartsWith(ShopCode)) Then
                    reader.Close
                    Return list2
                End If
                str2 = (str2.Replace(ShopCode, "").Trim.Replace(ChrW(9), " ") & ChrW(20))
                Dim num3 As Integer = (str2.Length - 1)
                Dim i As Integer = 0
                Do While (i <= num3)
                    If ((num + i) < (str2.Length - 1)) Then
                        goto Label_00D6
                    End If
                    Exit Do
                Label_00B9:
                    str = (str & Conversions.ToString(str2.Chars((i + num))))
                    num += 1
                Label_00D6:
                    If Not (((Conversions.ToString(str2.Chars((i + num))) = " ") Or (Conversions.ToString(str2.Chars((i + num))) = "")) Or ((num + i) >= (str2.Length - 1))) Then
                        goto Label_00B9
                    End If
                    i = (i + num)
                    num = 0
                    If (str <> "") Then
                        list2.Add(str)
                    End If
                    str = ""
                    i += 1
                Loop
                num = 0
                reader.Close
            End If
            Return list2
        End Function

        Public Shared Function GetNPCZhoonFile(ByRef NPCSetupFile As String) As String
            Dim str As String
            Try 
                Dim reader As New StreamReader(NPCSetupFile, Konstanten.enc)
                Dim str2 As String = ""
                Do While Not (str2.StartsWith("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Or (reader.Peek = -1))
                    str2 = reader.ReadLine
                Loop
                If ((reader.Peek = -1) And Not str2.StartsWith("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207))) Then
                    reader.Close
                    Return "No Zhoon found"
                End If
                reader.Close
                str = str2.Replace("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207), "").Trim.Replace(ChrW(9), "").Replace("""", "").Trim
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                str = "Not found"
                ProjectData.ClearProjectError
            End Try
            Return str
        End Function

        Public Shared Sub LoadBackupItem(ByVal BackupFileName As String, ByVal ItemIndex As Long)
            Dim num As Long = 0
            Try 
                Dim reader As New StreamReader(String.Concat(New String() { Konstanten.sPath, "GameServer\OpenItem\\", Konstanten.ItemBackupPath, "\", BackupFileName }), Konstanten.enc)
                Do While (reader.Peek <> -1)
                    Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)) = reader.ReadLine
                    num = (num + 1)
                    If (Konstanten.Index = &H1F3) Then
                        reader.ReadToEnd
                        Interaction.MsgBox(("Error in loading Monster File:" & Konstanten.ItemFiles(CInt(ItemIndex)) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Monsterfile to big: " & Konstanten.ItemFiles(CInt(ItemIndex)) & " Line index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.ItemDatenListe(CInt(ItemIndex), CInt(num)) = "End of File"
                reader.Close
                num = 0
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Shared Sub loadBackupMonster(ByVal BackupFileName As String, ByVal Monsterindex As Long)
            Dim num As Long = 0
            Try 
                Dim reader As New StreamReader(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\\", Konstanten.MoBackupPath, "\", BackupFileName }), Konstanten.enc)
                Do While (reader.Peek <> -1)
                    Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)) = reader.ReadLine
                    If Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)).Contains("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                        Konstanten.MoNamePath = Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)).Substring(Strings.Len("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207))).ToString.Trim
                        Konstanten.MonsterName(CInt(Monsterindex)) = Funktionen.GetMonsterInGameName(Konstanten.MoNamePath)
                    End If
                    num = (num + 1)
                    If (Konstanten.Index = &H1F3) Then
                        reader.ReadToEnd
                        Interaction.MsgBox(("Error in loading Monster File:" & Konstanten.MonsterFiles(CInt(Monsterindex)) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                        Funktionen.WriteErrorLog((("Monsterfile to big: " & Konstanten.MonsterFiles(CInt(Monsterindex)) & " Line index=" & Conversions.ToString(Konstanten.Index))))
                    End If
                Loop
                Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)) = "End of File"
                reader.Close
                num = 0
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Shared Function MonsterSaver(ByVal MonsterIndex As Long, ByVal MakeBackupFile As Boolean) As Long
            Dim num As Long
            Konstanten.Index = 0
            Dim str As String = Strings.Format(DateAndTime.Now.ToLocalTime, "yyyy_MM_dd_HH_mm_ss")
            Try 
                If (MakeBackupFile AndAlso File.Exists((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MonsterFiles(CInt(MonsterIndex))))) Then
                    If Not Directory.Exists((Konstanten.sPath & "GameServer\Monster\\" & Konstanten.MoBackupPath)) Then
                        Directory.CreateDirectory((Konstanten.sPath & "GameServer\Monster\\" & Konstanten.MoBackupPath))
                    End If
                    File.Copy((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MonsterFiles(CInt(MonsterIndex))), String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }))
                    If File.Exists(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) })) Then
                        File.Delete(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }))
                        File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }))
                    ElseIf Not File.Exists(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\Default_", Konstanten.MonsterFiles(CInt(MonsterIndex)) })) Then
                        File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\Default_", Konstanten.MonsterFiles(CInt(MonsterIndex)) }))
                    Else
                        File.Move(String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }), String.Concat(New String() { Konstanten.sPath, "GameServer\Monster\", Konstanten.MoBackupPath, "\", str, Konstanten.MoBackupNameAdd, Konstanten.MonsterFiles(CInt(MonsterIndex)) }))
                    End If
                End If
                Dim writer As New StreamWriter((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MonsterFiles(CInt(MonsterIndex))), False, Konstanten.enc)
                Konstanten.Index = 0
                Do While (Konstanten.MonsterDatenListe(CInt(MonsterIndex), Konstanten.Index) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(MonsterIndex), Konstanten.Index) <> "End of File") Then
                        writer.WriteLine(Konstanten.MonsterDatenListe(CInt(MonsterIndex), Konstanten.Index))
                    End If
                    Konstanten.Index += 1
                Loop
                Konstanten.Index = 0
                writer.Close
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function MonsterTextFinder(ByVal Monsterindex As Long, ByVal TextToFind As String) As Boolean
            Dim i As Long = 0
            Do While (Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)) <> "End of File")
                If Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)).Contains(TextToFind) Then
                    Return True
                End If
                i = (i + 1)
            Loop
            Return False
        End Function

        Public Shared Sub ReloadMonster(ByVal Monsterindex As Long)
            Dim num As Long = 0
            Dim reader As New StreamReader((Konstanten.sPath & "GameServer\Monster\" & Konstanten.MonsterFiles(CInt(Monsterindex))), Konstanten.enc)
            Do While (reader.Peek <> -1)
                Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)) = reader.ReadLine
                If Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)).Contains("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)) Then
                    Konstanten.MoNamePath = Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)).Substring(Strings.Len("*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207))).ToString.Trim
                    Konstanten.MonsterName(CInt(Monsterindex)) = Funktionen.GetMonsterInGameName(Konstanten.MoNamePath)
                End If
                num = (num + 1)
                If (Konstanten.Index = &H1F3) Then
                    reader.ReadToEnd
                    Interaction.MsgBox(("Error in loading Monster File:" & Konstanten.MonsterFiles(CInt(Monsterindex)) & ChrW(13) & ChrW(10) & "File to long!"), MsgBoxStyle.OkOnly, Nothing)
                    Funktionen.WriteErrorLog((("Monsterfile to big: " & Konstanten.MonsterFiles(CInt(Monsterindex)) & " Line index=" & Conversions.ToString(Konstanten.Index))))
                End If
            Loop
            Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(num)) = "End of File"
            reader.Close
            num = 0
        End Sub

        Public Shared Sub SetMonsterCommandValue(ByVal Monsterindex As Long, ByVal MoCommand As String, ByVal CommandValue As String)
            Dim i As Long = 0
            Do While (Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)) <> "End of File")
                If (Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)).StartsWith(MoCommand)) Then
                    Konstanten.MonsterDatenListe(CInt(Monsterindex), CInt(i)) = (MoCommand & ChrW(9) & CommandValue)
                    Return
                End If
                i = (i + 1)
            Loop
        End Sub

        Public Shared Sub SetMonsterExp(ByVal Index As Long, ByVal Exp As Long)
            Dim num As Long = 0
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(Index), CInt(num)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(Index), CInt(num)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(Index), CInt(num)).StartsWith("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161))) Then
                        Konstanten.MonsterDatenListe(CInt(Index), CInt(num)) = ("*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161) & ChrW(9) & Exp.ToString)
                    End If
                    num = (num + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "SetMonsterExp" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Shared Sub SetMonsterLVL(ByVal Index As Long, ByVal Level As Long)
            Dim num As Long = 0
            Try 
                Do While (Konstanten.MonsterDatenListe(CInt(Index), CInt(num)) <> "End of File")
                    If (Konstanten.MonsterDatenListe(CInt(Index), CInt(num)).StartsWith("*") AndAlso Konstanten.MonsterDatenListe(CInt(Index), CInt(num)).StartsWith("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167))) Then
                        Konstanten.MonsterDatenListe(CInt(Index), CInt(num)) = ("*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167) & ChrW(9) & Level.ToString)
                    End If
                    num = (num + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { "SetMonsterLVL" & ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

        Public Shared Function textausrechnung(ByVal expression As String) As Double
            Dim num As Double
            Try 
                Dim table As New DataTable
                num = Conversions.ToInteger(table.Compute(expression, Nothing))
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = String.Concat(New String() { ChrW(13) & ChrW(10), exception.TargetSite.Name, ChrW(13) & ChrW(10), exception.Message, ChrW(13) & ChrW(10), exception.Source, ChrW(13) & ChrW(10), exception.StackTrace })
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                num = 0
                ProjectData.ClearProjectError
            End Try
            Return num
        End Function

        Public Shared Function Textausschnitt(ByVal Zeichen As String, ByVal [Text] As String) As String
            Dim str As String = ""
            Dim str2 As String = ""
            Dim num As Long = 0
            Dim str3 As String = ""
            Try 
                Do While (str <> Zeichen)
                    str = Conversions.ToString([Text].Chars(CInt(num)))
                    num = (num + 1)
                Loop
                str = [Text].Substring(CInt(num))
                num = 0
                Do While (str2 <> Zeichen)
                    str2 = Conversions.ToString(str.Chars(CInt(num)))
                    str3 = (str3 & Conversions.ToString(str.Chars(CInt(num))))
                    num = (num + 1)
                Loop
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                str3 = str3.Trim(New Char() { Conversions.ToChar(Zeichen) })
                ProjectData.ClearProjectError
                Return str3
            End Try
            Return str3.Trim(New Char() { Conversions.ToChar(Zeichen) })
        End Function

        Public Shared Sub WriteErrorLog(ByRef ErrorText As String)
            Dim writer As StreamWriter
            If Not File.Exists((MyProject.Application.Info.DirectoryPath & "\PriTaTor_Errors.log")) Then
                Interaction.MsgBox((MyProject.Application.Info.DirectoryPath & "\PriTaTor_Errors.log"), MsgBoxStyle.OkOnly, Nothing)
                writer = File.CreateText((MyProject.Application.Info.DirectoryPath & "\PriTaTor_Errors.log"))
                writer.WriteLine("PriTaTor error log! Please post this file into forum on errors!")
                writer.WriteLine("----------------------------------------------------------------------")
                writer.WriteLine((DateTime.Now.ToLongDateString & " - " & DateTime.Now.ToLongTimeString))
                writer.WriteLine("PriTaTor Version:1.8.857")
                writer.WriteLine(CStr(ErrorText))
                writer.Flush
                writer.Close
            End If
            writer = File.AppendText((MyProject.Application.Info.DirectoryPath & "\PriTaTor_Errors.log"))
            writer.WriteLine(ChrW(13) & ChrW(10) & "----------------------------------------------------------------------" & ChrW(13) & ChrW(10))
            writer.WriteLine((DateTime.Now.ToLongDateString & " - " & DateTime.Now.ToLongTimeString))
            writer.WriteLine("PriTaTor Version:1.8.857")
            writer.WriteLine(("Textencoding: " & Encoding.Default.EncodingName & ChrW(13) & ChrW(10)))
            writer.WriteLine("Computer and System information: ")
            writer.WriteLine(("OS: " & MyProject.Computer.Info.OSFullName))
            writer.WriteLine(("OSPlattform: " & MyProject.Computer.Info.OSPlatform))
            writer.WriteLine(("Culture name: " & MyProject.Computer.Info.InstalledUICulture.TextInfo.CultureName))
            writer.WriteLine(("Culture name: " & MyProject.Computer.Info.InstalledUICulture.NativeName))
            writer.WriteLine(("OEM Codepage: " & Conversions.ToString(MyProject.Computer.Info.InstalledUICulture.TextInfo.OEMCodePage)))
            writer.WriteLine(("ANSI Codepage: " & Conversions.ToString(MyProject.Computer.Info.InstalledUICulture.TextInfo.ANSICodePage)))
            writer.WriteLine(("Letter Code: " & MyProject.Computer.Info.InstalledUICulture.ThreeLetterISOLanguageName))
            writer.WriteLine(("Network available: " & MyProject.Computer.Network.IsAvailable.ToString & ChrW(13) & ChrW(10)))
            writer.WriteLine("Error text:")
            writer.WriteLine(CStr(ErrorText))
            writer.Flush
            writer.Close
        End Sub

        Public Shared Function YesNo(ByVal Title As String, ByVal [Text] As String, ByVal Zeichen As Long) As Boolean
            Dim style As MsgBoxStyle
            If (Zeichen = 1) Then
                style = (MsgBoxStyle.DefaultButton2 Or (MsgBoxStyle.Question Or MsgBoxStyle.YesNo))
            End If
            If (Zeichen = 2) Then
                style = (MsgBoxStyle.DefaultButton2 Or (MsgBoxStyle.Exclamation Or MsgBoxStyle.YesNo))
            End If
            If (Zeichen = 3) Then
                style = (MsgBoxStyle.DefaultButton2 Or (MsgBoxStyle.Critical Or MsgBoxStyle.YesNo))
            End If
            If ((Zeichen <= 0) Or (Zeichen > 3)) Then
                style = (MsgBoxStyle.DefaultButton2 Or (MsgBoxStyle.Information Or MsgBoxStyle.YesNo))
            End If
            Return (Interaction.MsgBox([Text], style, Title) = MsgBoxResult.Yes)
        End Function


        ' Nested Types
        Public Class SentaiFile
            ' Methods
            Public Shared Function GetFileName(ByVal Path As String) As String
                Dim dialog As New OpenFileDialog
                Dim fileName As String = Nothing
                dialog.InitialDirectory = Path
                dialog.Multiselect = False
                dialog.Title = "Select a NPC file for dublicate"
                Try 
                    Dim dialog2 As OpenFileDialog = dialog
                    If (dialog2.ShowDialog = DialogResult.Cancel) Then
                        Return Nothing
                    End If
                    fileName = dialog.FileName
                    dialog2 = Nothing
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    Interaction.MsgBox(exception.Message, MsgBoxStyle.OkOnly, Nothing)
                    fileName = Nothing
                    ProjectData.ClearProjectError
                End Try
                Return fileName
            End Function

            Public Shared Function GetNPCIndex(ByVal File As String) As Integer
                Dim num2 As Integer
                Do While (Konstanten.NPCFiles(num2).ToUpper <> File.ToUpper)
                    num2 += 1
                    If (Konstanten.NPCFiles(num2) = Nothing) Then
                        Exit Do
                    End If
                Loop
                If (Konstanten.NPCFiles(num2) = Nothing) Then
                    num2 = -1
                End If
                Return num2
            End Function

            Public Shared Function ReadByteInFile(ByVal Path As String, ByVal offset As Long) As Byte
                Dim num As Byte
                Dim num2 As Byte
                Try 
                    Dim stream As New FileStream(Path, FileMode.Open) { _
                        .Position = (offset - 1) _
                    }
                    num = CByte(stream.ReadByte)
                    stream.Close
                    num2 = num
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    num2 = num
                    ProjectData.ClearProjectError
                End Try
                Return num2
            End Function

            Public Shared Function ReadBytesInFile(ByVal Path As String, ByVal offset As Long, ByVal count As Long) As Byte()
                Dim num As Integer
                Dim str As String = Path.GetFileName(Path).ToUpper
                Do While (str <> Konstanten.SPCFiles(num).ToUpper)
                    num += 1
                Loop
                Dim buffer As Byte() = New Byte((CInt((count - 1)) + 1)  - 1) {}
                Dim num3 As Long = (count - 1)
                Dim i As Long = 0
                Do While (i <= num3)
                    buffer(CInt(i)) = Konstanten.SPCDaten(num, CInt((offset + i)))
                    i = (i + 1)
                Loop
                Return buffer
            End Function

            Public Shared Function ReadBytesInFilee(ByVal Path As String, ByVal offset As Long, ByVal count As Long) As Byte()
                Dim buffer2 As Byte()
                Dim array As Byte() = New Byte((CInt((count - 1)) + 1)  - 1) {}
                Try 
                    Dim stream As New FileStream(Path, FileMode.Open) { _
                        .Position = offset _
                    }
                    stream.Read(array, 0, CInt(count))
                    stream.Close
                    buffer2 = array
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    buffer2 = array
                    ProjectData.ClearProjectError
                End Try
                Return buffer2
            End Function

            Public Shared Function ReadBytesInFileToEnd(ByVal Path As String, ByVal offset As Long) As Byte()
                Dim buffer As Byte()
                Try 
                    Dim stream As New FileStream(Path, FileMode.Open)
                    Dim array As Byte() = New Byte((CInt(stream.Length) + 1)  - 1) {}
                    Dim destinationArray As Byte() = New Byte((CInt((stream.Length - 2)) + 1)  - 1) {}
                    stream.Position = offset
                    stream.Read(array, 0, CInt(stream.Length))
                    Array.Copy(array, CLng(2), destinationArray, CLng(0), CLng((stream.Length - 2)))
                    stream.Close
                    buffer = destinationArray
                Catch exception1 As Exception
                    ProjectData.SetProjectError(exception1)
                    Dim exception As Exception = exception1
                    buffer = Nothing
                    ProjectData.ClearProjectError
                End Try
                Return buffer
            End Function

            Public Shared Sub WriteBytesInFile(ByRef Path As String, ByVal Offset As Integer, ByVal Count As Integer, ByVal Inhalt As Byte())
                Dim stream As New FileStream(Path, FileMode.Open, FileAccess.ReadWrite) { _
                    .Position = CLng(Offset) _
                }
                stream.Write(Inhalt, 0, Count)
                stream.Close
            End Sub

        End Class

        Public Class SUmwandlung
            ' Methods
            Public Shared Function ByteArrayToTextString(ByRef Barr As Byte(), ByVal Optional Codepage As Integer = &H4E4) As String
                Return Encoding.GetEncoding(Codepage).GetString(Barr)
            End Function

            Public Shared Function TextStringToByteArray(ByRef str As String, ByVal Optional Codepage As Integer = &H4E4) As Byte()
                Return Encoding.GetEncoding(Codepage).GetBytes(str)
            End Function

        End Class
    End Class
End Namespace

