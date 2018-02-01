//---------------------------------------------------------------------------------- 
//  FIleName : LowLevelPet.h
//                     
//	Class Name:	LowLevelPet
//
//  Desc:   초보 도우미 팻 동작
//		
//----------------------------------------------------------------------------------


#ifndef _PC_BANG_Pet_H_
#define _PC_BANG_Pet_H_

#include "smlib3d\\smd3d.h"
#include "..\\smwsock.h"
#include "..\\character.h"

#define PCBANG_PET_BURSTP	0
#define PCBANG_PET_BURSTS	1
#define PCBANG_PET_BURSTL	2
#define PCBANG_PET_BURSTD	3

//------------------------------------------------------------------------
// Name : PcBangPet
// Desc : PcBangPet 기본 속성을 가지고 있는 객체
// Date : 2004.4.19		Author : HongHoDong소스 수정 박철호		Version : 1.0
//------------------------------------------------------------------------
class HoPCBangPet
{
public:
	enum Type
	{
		BurstP,
		BurstS,
		BurstL,
		BurstD,
		IllusionP,
		IllusionS,
		IllusionL,
		IllusionD,
	};

	enum PCBang_FsmState
	{
		Spawn,						//Pet 생성
		Idle,						//Pet 유저 평화모드
		SkillPre,                   //Pet Skill 쓰기전 스킬시전 위치로 가는 모드
		Skill,                      //Pet Skill 쓰는 모드
		Vanish,                     //Pet 사라지는 모드
		None						//Pet 아무것두 안하는 모드	
	};

	enum PCBang_FsmStateEvent
	{
		EVENT_INIT,
		EVENT_UPDATE,
		EVENT_EXIT
	};

	HoPCBangPet();
	~HoPCBangPet();
	
	void	FsmEventProcess(PCBang_FsmStateEvent eStateEvent);
	void	OnEvent(PCBang_FsmStateEvent eEvent, PCBang_FsmState eFsmState);
	
	void		SetFsmState(HoPCBangPet::PCBang_FsmState eFsmState);
	void		SetFsmAttackState(smCHAR *pAttackChar);
	void        SetFsmHealState(smCHAR *pHealChar);

	PCBang_FsmState    GetFsmState();
	smCHAR     *GetAttachChar();
	BOOL	PetNearMonster( smCHAR *lpNearMonster );

	void    SetSpawn(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes);
	void    SetIdle(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, smCHAR *pAttackChar);

	bool	Main();
	bool	Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
	
	HoPCBangPet::Type	GetType();

private:
	Type		m_Type;
	smPAT3D		*m_PetMeshRes;
	smPAT3D     *m_PetBoneRes;
	smCHAR		*m_TargetChar;
    smCHAR      *m_AttackChar;
	int			m_iCurrentFrame;

	smCHAR      *m_AttackCharTarget;

	PCBang_FsmState            m_eCurrentFsmState;
	PCBang_FsmState			m_eNextFsmState;
	bool				m_bFsmChangeFlag;
	bool				m_bMyCharacterFlag;

	//각상태들마다 임시적으로 쓰는 변수들
	POINT3D				m_CurrentPos;
	POINT3D				m_TargetPos;
	POINT3D				m_AttackPos;
	bool				m_bSkillFlag;
	int					m_iParticleID;
	smOBJ3D				*ObjBip;
	bool				m_bAttackTiming;
	//int					m_iHealCount;
	bool				m_bPetAttacking;
};



//------------------------------------------------------------------------
// Name : HoLowLevelPetManager
// Desc : Pet을 관리하는 클래스
// Date : 2004.4.19		Author : HongHoDong		Version : 1.0
//------------------------------------------------------------------------
const int MAX_PCBANG_PET = 100;
class HoPCBangPetManager
{
public:
	HoPCBangPetManager();
	~HoPCBangPetManager();
	
private:
	HoPCBangPet	PcBangPetList[MAX_PCBANG_PET];
	smPAT3D			*m_BoneBurstP;
	smPAT3D			*m_BoneBurstS;
	smPAT3D			*m_BoneBurstL;
	smPAT3D			*m_BoneBurstD;
	
	smPAT3D			*m_MeshBurstP;
	smPAT3D			*m_MeshBurstS;
	smPAT3D			*m_MeshBurstL;
	smPAT3D			*m_MeshBurstD;
/*
	enum Type
	{
		BurstP,
		BurstS,
		BurstL,
		BurstD,
		IllusionP,
		IllusionS,
		IllusionL,
		IllusionD,
	}*/

private:
	HoPCBangPet *GetEmptyPet(smCHAR *pAttachChar);
	HoPCBangPet *GetEmptyIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);
public:
	bool	Create();
	bool    Destroy();

	bool    AddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType);
	bool	AddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);

	void    DeletePet(smCHAR *pAttachChar);

	bool	Main();
	bool    Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
};


//------------------------------------------------------------------------
// Name : 외부에서 PetManager를 쓰기위한 C Interface 함수들
// Desc : 외부에서 PetManager에 접근하기 위한 기본 함수를 제공한다.
// Date : 2004.4.19		Author : HongHoDong		Version : 1.0
//------------------------------------------------------------------------
extern bool g_PCBang_CreatePetSystem();
extern bool g_PCBang_MainPetSystem();
extern bool g_PCBang_DrawPetSystem(int x, int y, int z, int ax, int ay, int az);
extern bool g_PCBang_DestroyPetSystem();
extern bool g_HoPCBangAddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType);
extern bool g_HoPCBangAddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar = NULL);

extern void g_HoPCBangDeletePet(smCHAR *pAttachChar);

extern POINT3D HoHoPCBangPetRenderPoint;
extern DWORD  g_HoPCBangPetAttackSerial;

#endif