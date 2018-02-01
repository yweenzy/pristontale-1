Imports Microsoft.VisualBasic.CompilerServices
Imports System
Imports System.Collections
Imports System.Drawing
Imports System.Text

Namespace PriTaTor
    <StandardModule> _
    Friend NotInheritable Class Konstanten
        ' Fields
        Public Shared Accounts As ArrayList = New ArrayList
        Public Shared AktuellPath As String
        Public Shared Anzahl As Integer
        Public Shared Ars As String = "Archer"
        Public Shared ata As String = "Atalanta"
        Public Shared CheckMap As Boolean
        Public Shared correctsplit As String
        Public Shared DefaultNPCSPC As String = "f8 01 00 00 70 00 47 48 c0 e2 c8 ad c1 a1 20 ba f1 be c8 c6 ae 00 c6 00 d5 c6 ae 00 00 00 00 00 00 00 00 00 00 00 00 00 63 68 61 72 5c 6e 70 63 5c 54 4e 2d 30 30 35 5c 54 4e 2d 30 30 35 2e 69 6e 69 00 6e 57 6f 6c 76 65 72 69 6e 2d 30 33 2e 69 6e 69 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 61 6d 65 53 65 72 76 65 72 5c 6e 70 63 5c 6e 61 76 69 73 6b 6f 2d 73 74 6f 72 65 2e 6e 70 63 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ed 20 00 50 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 08 00 00 00 64 00 00 00 29 00 00 00 e0 00 00 00 57 00 00 00 0f 00 00 00 7a 00 00 00 00 00 00 00 f4 01 00 00 40 00 00 00 59 00 00 00 08 00 00 00 b4 00 00 00 00 00 00 00 a6 01 00 00 00 00 00 00 17 00 00 00 03 00 00 00 b4 00 00 00 a7 01 f9 01 0f 00 00 00 06 00 0b 00 0b 00 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 64 00 64 00 64 00 af 03 bc 02 bc 02 b8 1e 85 3f 47 e1 ca 40 00 00 00 00 7c e4 a0 01 ef fe fc 6f 9c e7 00 00 00 00 00 00 00 00 00 00 69 00 00 00 00 07 00 00 01 00 03 00 16 00 00 00 03 00 00 00 01 00 00 00 03 00 00 00 02 00 02 00 22 b2 ff ff 01 00 00 00 00 00 04 00 00 00 00 00 00 00 00 00 14 a4 b5 6e 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 b2 5d 04 30 95 55 56 00 11 10 03 00 c0 18 f6 ff 00 00 00 00 5f 0e 00 00 00 00 00 00 00 00 00 00"
        Public Shared DropDaten As String() = New String(&HC9  - 1) {}
        Public Shared DropIndex As Integer
        Public Shared DropReader As Integer
        Public Shared EditorExe As String = "Explorer.exe"
        Public Shared enc As Encoding = Encoding.GetEncoding(&H4E4)
        Public Shared EncDef As Encoding = Encoding.Default
        Public Shared EncUTF7 As Encoding = Encoding.UTF7
        Public Shared Endung As String
        Public Const ErrorLogFile As String = "PriTaTor_Errors.log"
        Public Shared ErrorText As String = "If you see this! Its realy critical!"
        Public Shared Explorer As String = "Explorer.exe"
        Public Shared ExpSender As Object
        Public Shared FoundFiles As String() = New String(&H2711  - 1) {}
        Public Shared fs As String = "Fighter"
        Public Shared GefundenText As String() = New String(&H2711  - 1) {}
        Public Shared GefundenZahl As String() = New String(&H2711  - 1) {}
        Public Shared Image As Bitmap
        Public Shared imagefile As String = ""
        Public Shared Index As Integer
        Public Const ItemAbs As String = "*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)
        Public Const ItemAgility As String = "*" & ChrW(185) & ChrW(206) & ChrW(195) & ChrW(184) & ChrW(188) & ChrW(186)
        Public Const ItemAPT As String = "*" & ChrW(184) & ChrW(182) & ChrW(185) & ChrW(253) & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(188) & ChrW(247) & ChrW(183) & ChrW(195) & ChrW(181) & ChrW(181)
        Public Const ItemAtkCrit As String = "*" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)
        Public Const ItemAtkPower As String = "*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)
        Public Const ItemAtkRange As String = "*" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)
        Public Const ItemAtkRating As String = "*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)
        Public Const ItemAtkSpeed As String = "*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Shared ItemBackupNameAdd As String = "_Backup_"
        Public Shared ItemBackupPath As String = "Backup"
        Public Const ItemBlock As String = "*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)
        Public Const ItemCode As String = "*" & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)
        Public Shared ItemCodes As String() = New String(&H7D1  - 1) {}
        Public Const ItemColor As String = "*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169) & ChrW(187) & ChrW(246) & ChrW(187) & ChrW(243)
        Public Shared ItemComplete As String
        Public Shared ItemDatenListe As String(0 To .,0 To .) = New String(&H7D1  - 1, &H1F5  - 1) {}
        Public Const ItemDef As String = "*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)
        Public Const ItemEndung As String = "*.txt"
        Public Const ItemEngName As String = "*Name"
        Public Shared ItemFiles As String() = New String(&H7D1  - 1) {}
        Public Const ItemFire As String = "*" & ChrW(186) & ChrW(210)
        Public Const ItemFrost As String = "*" & ChrW(179) & ChrW(195) & ChrW(177) & ChrW(226)
        Public Const ItemHPAdd As String = "*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)
        Public Const ItemHPREC As String = "*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)
        Public Const ItemHPRegen As String = "*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)
        Public Const ItemHPReq As String = "*" & ChrW(176) & ChrW(199) & ChrW(176) & ChrW(173)
        Public Const ItemIntegrity As String = "*" & ChrW(179) & ChrW(187) & ChrW(177) & ChrW(184) & ChrW(183) & ChrW(194)
        Public Const ItemJPName As String = "*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)
        Public Const ItemLevel As String = "*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)
        Public Shared ItemLevels As String() = New String(&H7D1  - 1) {}
        Public Const ItemLighting As String = "*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)
        Public Const ItemMPAdd As String = "*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)
        Public Const ItemMPREC As String = "*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)
        Public Const ItemMPRegen As String = "*" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)
        Public Shared ItemName As String() = New String(&H1389  - 1) {}
        Public Shared ItemNamePath As String
        Public Const ItemOrganic As String = "*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)
        Public Const ItemPath As String = "GameServer\OpenItem\"
        Public Const ItemPosion As String = "*" & ChrW(181) & ChrW(182)
        Public Const ItemPotStore As String = "*" & ChrW(186) & ChrW(184) & ChrW(192) & ChrW(175) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(163)
        Public Const ItemPrise As String = "*" & ChrW(176) & ChrW(161) & ChrW(176) & ChrW(221)
        Public Const ItemPriSpec As String = "**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173)
        Public Const ItemQuest As String = "*" & ChrW(192) & ChrW(175) & ChrW(180) & ChrW(207) & ChrW(197) & ChrW(169)
        Public Const ItemRealName As String = "*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)
        Public Const ItemRunSpeed As String = "**" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Const ItemSecSpec As String = "**" & ChrW(198) & ChrW(175) & ChrW(200) & ChrW(173) & ChrW(183) & ChrW(163) & ChrW(180) & ChrW(253)
        Public Shared ItemsFound As String() = New String(&H7D1  - 1) {}
        Public Const ItemSpAbs As String = "**" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(183) & ChrW(194)
        Public Const ItemSpAtkCrit As String = "**" & ChrW(197) & ChrW(169) & ChrW(184) & ChrW(174) & ChrW(198) & ChrW(188) & ChrW(196) & ChrW(195)
        Public Const ItemSpAtkSPeed As String = "**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Const ItemSpBlock As String = "**" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)
        Public Const ItemSpDef As String = "**" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)
        Public Const ItemSpHPRegen As String = "**" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)
        Public Const ItemSpirit As String = "*" & ChrW(193) & ChrW(164) & ChrW(189) & ChrW(197) & ChrW(183) & ChrW(194)
        Public Shared ItemSplit As String()
        Public Const ItemSpMPRegen As String = "**" & ChrW(177) & ChrW(226) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)
        Public Const ItemSpPowerLV As String = "**" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)
        Public Const ItemSPRange As String = "**" & ChrW(187) & ChrW(231) & ChrW(193) & ChrW(164) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)
        Public Const ItemSpRatingLv As String = "**" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)
        Public Const ItemSPSpeed As String = "*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Const ItemSTMAdd As String = "*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161)
        Public Const ItemSTMREC As String = "*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(187) & ChrW(243) & ChrW(189) & ChrW(194)
        Public Const ItemSTMRegen As String = "*" & ChrW(177) & ChrW(217) & ChrW(183) & ChrW(194) & ChrW(192) & ChrW(231) & ChrW(187) & ChrW(253)
        Public Const ItemStr As String = "*" & ChrW(200) & ChrW(251)
        Public Const ItemTalent As String = "*" & ChrW(192) & ChrW(231) & ChrW(180) & ChrW(201)
        Public Const ItemWeight As String = "*" & ChrW(185) & ChrW(171) & ChrW(176) & ChrW(212)
        Public Shared ItemWeights As String() = New String(&H7D1  - 1) {}
        Public Shared ItemZhoonFile As String() = New String(&H7D1  - 1) {}
        Public Shared ks As String = "Knight"
        Public Shared lwSelector As Long
        Public Const MapBoss As String = "*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218) & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)
        Public Shared MapDatenListe As String(0 To .,0 To .) = New String(&H7D1  - 1, &H1F5  - 1) {}
        Public Const MapEndung As String = "*.spm"
        Public Shared MapFiles As String() = New String(&H7D1  - 1) {}
        Public Const MapMonsters As String = "*" & ChrW(195) & ChrW(226) & ChrW(191) & ChrW(172) & ChrW(192) & ChrW(218)
        Public Const MapPath As String = "GameServer\Field\"
        Public Const MapValue1 As String = "*" & ChrW(195) & ChrW(214) & ChrW(180) & ChrW(235) & ChrW(181) & ChrW(191) & ChrW(189) & ChrW(195) & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246)
        Public Const MapValue2 As String = "*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(176) & ChrW(163) & ChrW(176) & ChrW(221)
        Public Const MapValue3 As String = "*" & ChrW(195) & ChrW(226) & ChrW(199) & ChrW(246) & ChrW(188) & ChrW(246)
        Public Shared Mech As String = "Mechanician"
        Public Shared mgs As String = "Magician"
        Public Const MoABS As String = "*" & ChrW(200) & ChrW(237) & ChrW(188) & ChrW(246) & ChrW(192) & ChrW(178)
        Public Const MoApp As String = "*" & ChrW(193) & ChrW(182) & ChrW(193) & ChrW(247)
        Public Const MoAtkCrit As String = "*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(176) & ChrW(197) & ChrW(184) & ChrW(174)
        Public Const MoATKPow As String = "*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)
        Public Const MoAtkRange As String = "*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(185) & ChrW(252) & ChrW(192) & ChrW(167)
        Public Const MoAtkRtg As String = "*" & ChrW(184) & ChrW(237) & ChrW(193) & ChrW(223) & ChrW(183) & ChrW(194)
        Public Const MoAtkSpd As String = "*" & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Shared MoBackupNameAdd As String = "_Backup_"
        Public Shared MoBackupPath As String = "Backup"
        Public Const MoBLK As String = "*" & ChrW(186) & ChrW(237) & ChrW(183) & ChrW(176) & ChrW(192) & ChrW(178)
        Public Const MoBoss As String = "*" & ChrW(181) & ChrW(206) & ChrW(184) & ChrW(241)
        Public Const MoChar As String = "*" & ChrW(199) & ChrW(176) & ChrW(188) & ChrW(186)
        Public Const MoDef As String = "*" & ChrW(185) & ChrW(230) & ChrW(190) & ChrW(238) & ChrW(183) & ChrW(194)
        Public Const MoDrop As String = "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)
        Public Const MoEmptyDrop As String = ChrW(190) & ChrW(248) & ChrW(192) & ChrW(189)
        Public Const MoEndung As String = "*.inf"
        Public Const MoExp As String = "*" & ChrW(176) & ChrW(230) & ChrW(199) & ChrW(232) & ChrW(196) & ChrW(161)
        Public Const MoExtraDrop As String = "*" & ChrW(195) & ChrW(223) & ChrW(176) & ChrW(161) & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219)
        Public Const MoFire As String = "*" & ChrW(186) & ChrW(210)
        Public Const MoGold As String = ChrW(181) & ChrW(183)
        Public Const MoHP As String = "*" & ChrW(187) & ChrW(253) & ChrW(184) & ChrW(237) & ChrW(183) & ChrW(194)
        Public Const MoIce As String = "*" & ChrW(190) & ChrW(243) & ChrW(192) & ChrW(189)
        Public Const MoInt As String = "*" & ChrW(193) & ChrW(246) & ChrW(180) & ChrW(201)
        Public Const MoLevel As String = "*" & ChrW(183) & ChrW(185) & ChrW(186) & ChrW(167)
        Public Const MoLgt As String = "*" & ChrW(185) & ChrW(248) & ChrW(176) & ChrW(179)
        Public Const MoMage As String = "*" & ChrW(184) & ChrW(197) & ChrW(193) & ChrW(247)
        Public Const MoMapName As String = "*" & ChrW(192) & ChrW(204) & ChrW(184) & ChrW(167)
        Public Const MoMSpd As String = "*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(188) & ChrW(211) & ChrW(181) & ChrW(181)
        Public Const MoMTyp As String = "*" & ChrW(192) & ChrW(204) & ChrW(181) & ChrW(191) & ChrW(197) & ChrW(184) & ChrW(192) & ChrW(212)
        Public Shared MoNamePath As String
        Public Const MoNoDrop As String = "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(196) & ChrW(171) & ChrW(191) & ChrW(238) & ChrW(197) & ChrW(205)
        Public Shared MonsterAnzahl As Single
        Public Shared MonsterDaten As String() = New String(&H7D1  - 1) {}
        Public Shared MonsterDatenListe As String(0 To .,0 To .) = New String(&H7D1  - 1, &H1F5  - 1) {}
        Public Shared MonsterFiles As String() = New String(&H7D1  - 1) {}
        Public Shared MonsterLevels As String() = New String(&H7D1  - 1) {}
        Public Shared MonsterMapName As String() = New String(&H7D1  - 1) {}
        Public Shared MonsterName As String() = New String(&H1389  - 1) {}
        Public Shared MonsterZhoonFile As String() = New String(&H7D1  - 1) {}
        Public Const MoOrg As String = "*" & ChrW(187) & ChrW(253) & ChrW(195) & ChrW(188)
        Public Const MoPath As String = "GameServer\Monster\"
        Public Const MoPAtkRtg As String = "*" & ChrW(198) & ChrW(175) & ChrW(188) & ChrW(246) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(252)
        Public Const MoPoision As String = "*" & ChrW(181) & ChrW(182)
        Public Const MoQuestDrop As String = "*" & ChrW(190) & ChrW(198) & ChrW(192) & ChrW(204) & ChrW(197) & ChrW(219) & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(206)
        Public Const MoRealName As String = "*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)
        Public Const MoSize As String = "*" & ChrW(184) & ChrW(240) & ChrW(181) & ChrW(168) & ChrW(197) & ChrW(169) & ChrW(177) & ChrW(226)
        Public Const MoSKATK As String = "*" & ChrW(177) & ChrW(226) & ChrW(188) & ChrW(250) & ChrW(176) & ChrW(248) & ChrW(176) & ChrW(221) & ChrW(183) & ChrW(194)
        Public Const MoSnd As String = "*" & ChrW(200) & ChrW(191) & ChrW(176) & ChrW(250) & ChrW(192) & ChrW(189)
        Public Const MoSpCode As String = "*" & ChrW(177) & ChrW(184) & ChrW(186) & ChrW(176) & ChrW(196) & ChrW(218) & ChrW(181) & ChrW(229)
        Public Const MoTyp As String = "*" & ChrW(184) & ChrW(243) & ChrW(189) & ChrW(186) & ChrW(197) & ChrW(205) & ChrW(193) & ChrW(190) & ChrW(193) & ChrW(183)
        Public Shared mouseposx As Integer
        Public Shared mouseposy As Integer
        Public Const MoVision As String = "*" & ChrW(189) & ChrW(195) & ChrW(190) & ChrW(223)
        Public Shared NotFOund As Boolean
        Public Shared NPCData As String(0 To .,0 To .) = New String(&H7D1  - 1, &H1F5  - 1) {}
        Public Shared NPCEnde As Integer
        Public Shared NPCEndung As String = "*.NPC"
        Public Shared NPCFiles As String() = New String(&H7D1  - 1) {}
        Public Shared npcName As String = "*" & ChrW(191) & ChrW(172) & ChrW(176) & ChrW(225) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)
        Public Shared NPCNames As String() = New String(&H7D1  - 1) {}
        Public Shared NPCPath As String = "GameServer\NPC\"
        Public Shared NPCPosEndung As String = "*.spc"
        Public Shared NPCSetupIni As String() = New String(&H3E9  - 1) {}
        Public Shared NPCSetupInIErkennung As String = "*" & ChrW(184) & ChrW(240) & ChrW(190) & ChrW(231) & ChrW(198) & ChrW(196) & ChrW(192) & ChrW(207)
        Public Shared Posx As Double
        Public Shared Posy As Double
        Public Const Programmversion As String = "1.8.857"
        Public Shared prs As String = "Priestess"
        Public Shared Ps As String = "Pikeman"
        Public Shared SelectionspeicherlbMonster As Long
        Public Shared SetMoTyp As Boolean
        Public Shared sFile As String
        Public Shared slIndex As Long = -1
        Public Shared SP As Boolean
        Public Shared sPath As String
        Public Shared SpawnPosiEndung As String = "*.spp"
        Public Shared SPCDaten As Byte(0 To .,0 To .) = New Byte(&H7D1  - 1, &HC4E1  - 1) {}
        Public Shared SPCFiles As String() = New String(&H7D1  - 1) {}
        Public Shared SPPDaten As Byte(0 To .,0 To .) = New Byte(&H7D1  - 1, &H961  - 1) {}
        Public Shared SPPFiles As String() = New String(&H7D1  - 1) {}
        Public Shared TX As Double
        Public Shared TY As Double
    End Class
End Namespace

