/*----------------------------------------------------------------------------*
*	파일명 :  HoPhysics.h
*	하는일 :  이동 경로 관리..
*	작성일 :  최종업데이트 2000.1 
*	적성자 :  홍호동.
*-----------------------------------------------------------------------------*/	

#ifndef _HO_PHYSICS_H_
#define _HO_PHYSICS_H_

struct hoPOINT3D
{
	float x;
	float y;
	float z;
};

#define MOVE_LINE						0x00000010 //직선 이동
#define MOVE_PARTICLE					0x00000020 //파티클 이동.
#define MOVE_ANGLE						0X00000040 //회전을 함.

class HoPhysicsObject
{
public:
	HoPhysicsObject();
	~HoPhysicsObject();
	
protected:
	hoPOINT3D	Velocity;
	BOOL		StartFlag;

	int			WorkId;	//작업 종류

public:
	virtual void Init();
	virtual int Main();
	virtual hoPOINT3D GetVector() { return Velocity; }
	virtual BOOL GetState() { return StartFlag; }
	virtual void SetState(BOOL startFlag) { StartFlag = startFlag;}
	virtual hoPOINT3D GetAngle()
	{
		hoPOINT3D temp;
		memset(&temp, 0, sizeof(temp));
		return temp;
	}

	int		GetWorkId() { return WorkId; }
};

//한점에서 다른점으로 직선 이동 할때 
class HoPhysicsDest : public HoPhysicsObject 
{
public:
	HoPhysicsDest();
	~HoPhysicsDest();
private:
	POINT3D		DestPos;		//목적지..
	POINT3D		CurrentPos;     //현재의 위치..
	int			Speed;
			
public:
	void		Init();
	int			Main();
	int			Start(POINT3D &currentPos, POINT3D &destPos, int speed);
	hoPOINT3D	GetVector() { return Velocity; }
};

//가장 기초적인 파티클 중력 모델...
class HoPhysicsParticle : public HoPhysicsObject
{
public:
	HoPhysicsParticle();
	~HoPhysicsParticle();

private:
	float		Gravity;			//중력
	int			Live;               //생명력..
	
	//Local회전에 관한 변수들..
	hoPOINT3D			DestLocalAngle;
	hoPOINT3D			LocalAngleStep;

public:
	void	Init();
	int		Main();
	int		Start(POINT3D &velocity);
	void	SetGravity(float gravity) { Gravity = gravity;}
	void	SetLive(int live) { Live = live; }
	hoPOINT3D GetVector() { return Velocity; }

	int		SetDestAngle(POINT3D destAngle);
	hoPOINT3D GetAngle() {return LocalAngleStep;}
};

#define MAX_PHYSICS_OBJECT_MAX		100
//이동 경로를 관리하는 클래스
class HoPhysicsMgr
{
public:
	HoPhysicsMgr();
	~HoPhysicsMgr();

private:
	HoPhysicsObject *PhysicsObject[MAX_PHYSICS_OBJECT_MAX];
	int				 PhysicsObjectBufferCount;
	
	
public:
	int AddObject(HoPhysicsObject *object);
	
	hoPOINT3D	*GetVector(int index)
	{
		if(index < 0 && index >= MAX_PHYSICS_OBJECT_MAX)
			return NULL;

		if(PhysicsObject[index] == NULL)
			return NULL;

		if(PhysicsObject[index]->GetState() == FALSE)
			return NULL;

		return &PhysicsObject[index]->GetVector();
	}

	void Init();
	int Main();
};

#endif