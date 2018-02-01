Imports Microsoft.VisualBasic
Imports Microsoft.VisualBasic.CompilerServices
Imports System
Imports System.ComponentModel.Design
Imports System.Diagnostics
Imports System.Runtime.CompilerServices

Namespace PriTaTor.My
    <CompilerGenerated, DebuggerNonUserCode, StandardModule, HideModuleName> _
    Friend NotInheritable Class MySettingsProperty
        ' Properties
        <HelpKeyword("My.Settings")> _
        Friend Shared ReadOnly Property Settings As MySettings
            Get
                Return MySettings.Default
            End Get
        End Property

    End Class
End Namespace

