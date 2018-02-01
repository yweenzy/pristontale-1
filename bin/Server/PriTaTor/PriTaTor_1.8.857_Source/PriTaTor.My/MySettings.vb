Imports Microsoft.VisualBasic.CompilerServices
Imports System
Imports System.CodeDom.Compiler
Imports System.ComponentModel
Imports System.Configuration
Imports System.Diagnostics
Imports System.Runtime.CompilerServices

Namespace PriTaTor.My
    <CompilerGenerated, EditorBrowsable(EditorBrowsableState.Advanced), GeneratedCode("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "9.0.0.0")> _
    Friend NotInheritable Class MySettings
        Inherits ApplicationSettingsBase
        ' Methods
        <EditorBrowsable(EditorBrowsableState.Advanced), DebuggerNonUserCode> _
        Private Shared Sub AutoSaveSettings(ByVal sender As Object, ByVal e As EventArgs)
            If MyProject.Application.SaveMySettingsOnExit Then
                MySettingsProperty.Settings.Save
            End If
        End Sub


        ' Properties
        <UserScopedSetting, DefaultSettingValue("False"), DebuggerNonUserCode> _
        Public Property chItemInfo As Boolean
            Get
                Return Conversions.ToBoolean(Me.Item("chItemInfo"))
            End Get
            Set(ByVal Value As Boolean)
                Me.Item("chItemInfo") = Value
            End Set
        End Property

        <UserScopedSetting, DefaultSettingValue("False"), DebuggerNonUserCode> _
        Public Property chMap As Boolean
            Get
                Return Conversions.ToBoolean(Me.Item("chMap"))
            End Get
            Set(ByVal Value As Boolean)
                Me.Item("chMap") = Value
            End Set
        End Property

        <UserScopedSetting, DefaultSettingValue("ItemSelector:" & ChrW(13) & ChrW(10) & "Everything=" & ChrW(13) & ChrW(10) & "--Defence--=da,db,dg1,oa2,om,ds" & ChrW(13) & ChrW(10) & "Armor=da1" & ChrW(13) & ChrW(10) & "Robe=da2" & ChrW(13) & ChrW(10) & "Boots=db" & ChrW(13) & ChrW(10) & "Gauntletss=dg1" & ChrW(13) & ChrW(10) & "Armlets=oa2" & ChrW(13) & ChrW(10) & "Orb=om" & ChrW(13) & ChrW(10) & "Shield=ds" & ChrW(13) & ChrW(10) & "--Weapons--=wp,ws1,ws3,wa,wm,wt,wh,wc,ws2,ws4" & ChrW(13) & ChrW(10) & "Pike=wp" & ChrW(13) & ChrW(10) & "Bow=ws1,ws3" & ChrW(13) & ChrW(10) & "Axe=wa" & ChrW(13) & ChrW(10) & "Staff/Wand=wm" & ChrW(13) & ChrW(10) & "Javelin=wt" & ChrW(13) & ChrW(10) & "Mace=wh" & ChrW(13) & ChrW(10) & "Claw=wc" & ChrW(13) & ChrW(10) & "Sword=ws2,ws4" & ChrW(13) & ChrW(10) & "--Spick and span--=or,oa1,os" & ChrW(13) & ChrW(10) & "Ring=or" & ChrW(13) & ChrW(10) & "Amulet=oa1" & ChrW(13) & ChrW(10) & "Sheltom=os" & ChrW(13) & ChrW(10) & "--Others--" & ChrW(13) & ChrW(10) & "Potions=pm,ps,pl" & ChrW(13) & ChrW(10) & "Crystals=gp" & ChrW(13) & ChrW(10) & "Force Orb=fo" & ChrW(13) & ChrW(10) & "Donation Items=b" & ChrW(13) & ChrW(10) & "Quest Items=_u,2_,ma,qt,sp,uw" & ChrW(13) & ChrW(10) & "Event Items=ch,pz,sd,se,sp" & ChrW(13) & ChrW(10) & "Other=ec" & ChrW(13) & ChrW(10) & "<End>" & ChrW(13) & ChrW(10) & ChrW(13) & ChrW(10) & "MonsterSelector:" & ChrW(13) & ChrW(10) & "Name=" & ChrW(13) & ChrW(10) & "Level=0-10" & ChrW(13) & ChrW(10) & "Level=11-20" & ChrW(13) & ChrW(10) & "Level=21-30" & ChrW(13) & ChrW(10) & "Level=31-40" & ChrW(13) & ChrW(10) & "Level=41-50" & ChrW(13) & ChrW(10) & "Level=51-60" & ChrW(13) & ChrW(10) & "Level=61-70" & ChrW(13) & ChrW(10) & "Level=71-80" & ChrW(13) & ChrW(10) & "Level=81-90" & ChrW(13) & ChrW(10) & "Level=91-100" & ChrW(13) & ChrW(10) & "Level=100-200" & ChrW(13) & ChrW(10) & "Name=Hopy" & ChrW(13) & ChrW(10) & "<End>"), DebuggerNonUserCode> _
        Public Property Config As String
            Get
                Return Conversions.ToString(Me.Item("Config"))
            End Get
            Set(ByVal Value As String)
                Me.Item("Config") = Value
            End Set
        End Property

        Public Shared ReadOnly Property [Default] As MySettings
            Get
                If Not MySettings.addedHandler Then
                    Dim addedHandlerLockObject As Object = MySettings.addedHandlerLockObject
                    ObjectFlowControl.CheckForSyncLockOnValueType(addedHandlerLockObject)
                    SyncLock addedHandlerLockObject
                        If Not MySettings.addedHandler Then
                            AddHandler MyProject.Application.Shutdown, New ShutdownEventHandler(AddressOf MySettings.AutoSaveSettings)
                            MySettings.addedHandler = True
                        End If
                    End SyncLock
                End If
                Return MySettings.defaultInstance
            End Get
        End Property

        <UserScopedSetting, DefaultSettingValue(""), DebuggerNonUserCode> _
        Public Property Editor As String
            Get
                Return Conversions.ToString(Me.Item("Editor"))
            End Get
            Set(ByVal Value As String)
                Me.Item("Editor") = Value
            End Set
        End Property

        <DebuggerNonUserCode, DefaultSettingValue("EXP*2"), UserScopedSetting> _
        Public Property EXPFormel As String
            Get
                Return Conversions.ToString(Me.Item("EXPFormel"))
            End Get
            Set(ByVal Value As String)
                Me.Item("EXPFormel") = Value
            End Set
        End Property

        <UserScopedSetting, DefaultSettingValue("False"), DebuggerNonUserCode> _
        Public Property FindMonsters As Boolean
            Get
                Return Conversions.ToBoolean(Me.Item("FindMonsters"))
            End Get
            Set(ByVal Value As Boolean)
                Me.Item("FindMonsters") = Value
            End Set
        End Property

        <DebuggerNonUserCode, UserScopedSetting, DefaultSettingValue("Gold*2")> _
        Public Property GoldFormel As String
            Get
                Return Conversions.ToString(Me.Item("GoldFormel"))
            End Get
            Set(ByVal Value As String)
                Me.Item("GoldFormel") = Value
            End Set
        End Property

        <DebuggerNonUserCode, UserScopedSetting, DefaultSettingValue("DA120,DA220")> _
        Public Property ItemWarn As String
            Get
                Return Conversions.ToString(Me.Item("ItemWarn"))
            End Get
            Set(ByVal Value As String)
                Me.Item("ItemWarn") = Value
            End Set
        End Property

        <UserScopedSetting, DefaultSettingValue("1000000"), DebuggerNonUserCode> _
        Public Property MaxExp As String
            Get
                Return Conversions.ToString(Me.Item("MaxExp"))
            End Get
            Set(ByVal Value As String)
                Me.Item("MaxExp") = Value
            End Set
        End Property

        <DebuggerNonUserCode, DefaultSettingValue("1000000"), UserScopedSetting> _
        Public Property MaxGold As String
            Get
                Return Conversions.ToString(Me.Item("MaxGold"))
            End Get
            Set(ByVal Value As String)
                Me.Item("MaxGold") = Value
            End Set
        End Property

        <UserScopedSetting, DebuggerNonUserCode, DefaultSettingValue("c:")> _
        Public Property sspath As String
            Get
                Return Conversions.ToString(Me.Item("sspath"))
            End Get
            Set(ByVal Value As String)
                Me.Item("sspath") = Value
            End Set
        End Property

        <DebuggerNonUserCode, UserScopedSetting, DefaultSettingValue("True")> _
        Public Property WarnMoZhoon As Boolean
            Get
                Return Conversions.ToBoolean(Me.Item("WarnMoZhoon"))
            End Get
            Set(ByVal Value As Boolean)
                Me.Item("WarnMoZhoon") = Value
            End Set
        End Property


        ' Fields
        Private Shared addedHandler As Boolean
        Private Shared addedHandlerLockObject As Object = RuntimeHelpers.GetObjectValue(New Object)
        Private Shared defaultInstance As MySettings = DirectCast(SettingsBase.Synchronized(New MySettings), MySettings)
    End Class
End Namespace

