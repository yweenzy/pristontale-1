Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports System

Namespace PriTaTor
    <StandardModule> _
    Friend NotInheritable Class Programmstarts
        ' Methods
        Public Shared Sub Execute(ByVal Prog As String, ByVal FileAndPath As String)
            Try 
                Interaction.Shell((Prog & " " & FileAndPath), AppWinStyle.NormalFocus, False, -1)
            Catch exception1 As Exception
                ProjectData.SetProjectError(exception1)
                Dim exception As Exception = exception1
                Interaction.MsgBox(("Error: Please check errorlog!" & ChrW(13) & ChrW(10) & Konstanten.sPath & "PriTaTor_Errors.log"), MsgBoxStyle.Critical, Nothing)
                Konstanten.ErrorText = ("Programmstart" & ChrW(13) & ChrW(10) & exception.Message & ChrW(13) & ChrW(10) & exception.StackTrace)
                FileSystem.WriteLine(Conversions.ToInteger(("Programm:" & Prog & ChrW(13) & ChrW(10) & "Pfad:" & FileAndPath)), New Object(0  - 1) {})
                Funktionen.WriteErrorLog((Konstanten.ErrorText))
                ProjectData.ClearProjectError
            End Try
        End Sub

    End Class
End Namespace

