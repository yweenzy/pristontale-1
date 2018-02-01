//----------------------------------------------------------------------------------
//  FIleName : HoEffectController.h
//
//	Class Name:	,
//
//  Desc: EffectModel 의 Controller 들이다.
//
//----------------------------------------------------------------------------------
#ifndef _HO_EFFECT_CONTROLLER_H_
#define _HO_EFFECT_CONTROLLER_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"
#include "math\\matrix4.h"
#include "HoEffectModel.h"
#include "HoEffectUtil.h"
#include "HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
	#include "smlib3d\\smd3d.h"
#endif
#ifdef  _HO_NEW_WIN32_
	#include "smlib3d\\smd3d.h"
#endif

#include <vector>
#include <string>
#include <algorithm>
#include <list>

enum
{
    CLASS_EVENT_NONE,
    CLASS_EVENT_ANGLE,
    CLASS_EVENT_TRANSLATION,
    CLASS_EVENT_SIZE,
    CLASS_EVENT_COLOR,
    CLASS_EVENT_TIMER
};

class HoEffectEventInterface
{
protected:
    int     ClassID;                            //현재의 Class정보를 가지고 있다.
    bool    Fade;                               //지금 실행할려는 Event의 전 Event와 보간을 할건지를 결정
    HoEffectEventInterface *NextFadeEvent;
    float                   StartTime;          //실제로 시작하는 Event시간 TimeRange 사이 값이다..

public:
    HoEffectEventInterface(): Fade(false), NextFadeEvent(0), ClassID(0) {}
    virtual ~HoEffectEventInterface() {}

    int     GetClassID() {return ClassID;}
    bool    IsFade(void) const { return(Fade); }
	void    SetFade(const bool data = true) { Fade = data; }
    void    SetStartTime(HoEffectMinMax<float> in)
    {
        StartTime = in.GetRandom();
    }

    float   GetStartTime(void) const
    {
        return(StartTime);
    }

	void    SetStartlTime(const float data)
    {
        StartTime = data;
    }

    void SetFadeNextEvent(HoEffectEventInterface *effectEvent)
    {
        if(effectEvent == NULL)
            return;
        NextFadeEvent = effectEvent;
    }

    virtual void VisitEffectModel(HoEffectModelInterface &effectModel) = 0;
};


//----------------------------------------------------------
// color 이벤트
//----------------------------------------------------------
class HoEffectEventColor : public HoEffectEventInterface
{
private:
    HoEffectMinMax<color4> m_Color;

public:
    HoEffectEventColor() {ClassID = CLASS_EVENT_COLOR;}
    ~HoEffectEventColor() {};

    void Set(HoEffectMinMax<color4> in) { m_Color = in;}
    HoEffectMinMax<color4> Get() {return m_Color;}
    void VisitEffectModel(HoEffectModelInterface &effectModel);
};

class HoEffectEventSize : public HoEffectEventInterface
{
private:
    HoEffectMinMax<point3> m_Size;

public:
    HoEffectEventSize() {ClassID = CLASS_EVENT_SIZE;}
    ~HoEffectEventSize() {};

    void Set(HoEffectMinMax<point3> in) { m_Size = in;}
    HoEffectMinMax<point3> Get() {return m_Size;}
    void VisitEffectModel(HoEffectModelInterface &effectModel);
};

class HoEffectEvent_CompareFunc : public std::binary_function<HoEffectEventInterface *,HoEffectEventInterface *, bool>
{
public:
	bool operator() (const HoEffectEventInterface* lhs, const HoEffectEventInterface* rhs) const
	{
		return lhs->GetStartTime() < rhs->GetStartTime();
	}
};
class HoEffectEventController
{
public:
    HoEffectEventController();
    ~HoEffectEventController();

private:
    std::vector<HoEffectEventInterface *>m_EffectEvents;
protected:

public:
    void Clear();
    void Init(HoEffectModelInterface *model);
    bool AddEvent(HoEffectEventInterface *event);
    bool RunEvent(HoEffectModelInterface *model);
    void CreateFadeList();

};


class HoEffectModelControllerInterface
{
public:
    HoEffectModelControllerInterface() : m_iLoop(0),
                                         m_iLoopCount(0),
                                         m_Translate(0.f, 0.f, 0.f),
                                         m_CalcTranslate(0.f, 0.f, 0.f),
										 m_Angle(0.f, 0.f, 0.f),
										 m_CalcAngle(0.f, 0.f, 0.f),
	                                     m_bLiveFlag(true) {};
    virtual ~HoEffectModelControllerInterface() {};

protected:
    HoEffectEventController     m_EffectEventController;
    int                         m_iLoop;
    float                       m_iLoopCount;

    point3                      m_Translate;
	point3						m_Angle;
    point3                      m_CalcTranslate;
	point3						m_CalcAngle;
	bool						m_bLiveFlag;
public:
    //Event 관련
    bool    InitEvent(HoEffectModelInterface *model);
    bool    AddEvent(HoEffectEventInterface  *event);
    bool    RunEvent(HoEffectModelInterface  *model);
    void    CreateFadeList();

	void    SetTranslate(const point3 &trans) { m_Translate = trans; }
	const   point3& GetTranslate() { return m_Translate; }

    void    SetCalcTranlsate(const point3 &trans) 
	{ 
		m_CalcTranslate = trans; 
		m_CalcTranslate += m_Translate; 
	}

	void	SetCalcAngle(const point3 &angle) { m_CalcAngle = angle; m_CalcAngle += m_Angle; } 
	const   point3& GetCalcTranslate() { return m_CalcTranslate; }

	bool	IsLive() { return m_bLiveFlag; }
public:
    virtual bool Main(float elapsedTime) = 0;
    virtual bool UpdateView(int x, int y, int z, int ax, int ay, int az) = 0;
};


class HoEffectTextureController : public HoEffectModelControllerInterface
{
public:
    HoEffectTextureController() {};
    ~HoEffectTextureController() {};

private:
    HoEffectTextureModel m_TextureModel;
public:
    void    Init(int type);
    void    Init(const std::string &textureName);
    void    Init(const std::string &textureName, int textureCount, float aniDelayTime);
    void    SetLive(bool flag);
    void    InitPos(float x, float y, float z);
    void    InitEndTime(float endTime);
    void    InitLoop(int loop);
    void    InitColor(float r, float g, float b, float a);
    void    InitStartDelayTime(float delayTime);
    void    InitSize(float x, float y);
    void    InitBlendType(int blendType);

    bool    Main(float elapsedTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
};

class HoEffectBillboardAxialController : public HoEffectModelControllerInterface
{
public:
    HoEffectBillboardAxialController() {};
    ~HoEffectBillboardAxialController() {};

private:
    HoEffectBillboardAxialModel m_BillboardAxialModel;
public:
    void    Init(const std::string &textureName);
    void    Init(const std::string &textureName, int textureCount, float aniDelayTime);

    void    InitPos(float x, float y, float z);
    void    InitPos(float x1, float y1, float z1, float x2, float y2, float z2);
    void    InitEndTime(float endTime);
    void    InitLoop(int loop);
    void    InitColor(float r, float g, float b, float a);
    void    InitStartDelayTime(float delayTime);
    void    InitSize(float x, float y);
    void    InitBlendType(int type);

    bool Main(float elapsedTime);
    bool UpdateView(int x, int y, int z, int ax, int ay, int az);
};

class HoEffectMeshController : public HoEffectModelControllerInterface
{
public:
    HoEffectMeshController() {};
    ~HoEffectMeshController() {};

private:
    HoEffectMeshModel   m_MeshModel;
public:
    void    Init(const std::string &meshName);
    void    Init(const std::string &meshName, const std::string &boneName);
    void    InitPos(float x, float y, float z);
    void    InitMaxFrame(float frame);
    void    InitLoop(int loop);
    void    InitColor(float r, float g, float b, float a);
    void    InitStartDelayTime(float delayTime);
    void    InitBlendType(int type);
    bool    Main(float elapsedTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
};

class HoEffectBoundingInterface
{
public:
    virtual ~HoEffectBoundingInterface() {};
    virtual point3 GetPos() = 0;
};

class HoEffectBoundingBox : public HoEffectBoundingInterface
{
private:
    HoEffectMinMax<float> m_AxisX;
    HoEffectMinMax<float> m_AxisY;
    HoEffectMinMax<float> m_AxisZ;

public:
    HoEffectBoundingBox()
    {
        m_AxisX.Min = -10.f;
        m_AxisX.Max =  10.f;
        m_AxisX.Min = -10.f;
        m_AxisX.Max =  10.f;
        m_AxisX.Min = -10.f;
        m_AxisX.Max =  10.f;
    }

    void Init(float x1, float x2, float y1, float y2, float z1, float z2)
    {
        m_AxisX.Min = x1;
        m_AxisX.Max = x2;
        m_AxisY.Min = y1;
        m_AxisY.Max = y2;
        m_AxisZ.Min = z1;
        m_AxisZ.Max = z2;
    }
    point3 GetPos()
    {
        point3 pos;
        pos.x = m_AxisX.GetRandom();
        pos.y = m_AxisY.GetRandom();
        pos.z = m_AxisZ.GetRandom();
        return pos;
    }
};

class HoEffectBoundingSphere : public HoEffectBoundingInterface
{
private:
    HoEffectMinMax<float>  m_Radius;
    HoEffectMinMax<point3> m_Angle;
public:
    HoEffectBoundingSphere()
    {
        m_Radius.Min = 5.f;
        m_Radius.Max = 10.f;

        m_Angle.Min.x = 0.f;
        m_Angle.Max.x = 4.f;
        m_Angle.Min.y = 0.f;
        m_Angle.Max.y = 4.f;
        m_Angle.Min.z = 0.f;
        m_Angle.Max.z = 4.f;
    }

    void Init(float x1, float x2)
    {
        m_Radius.Min = x1;
        m_Radius.Max = x2;
    }

    point3 GetPos()
    {
        point3  pos;
        pos.x = 0.f;
        pos.y = 0.f;
        pos.z = m_Radius.GetRandom();
        matrix4 temp1;
        matrix4 temp2;
        temp1.MakeIdent();
        temp2.MakeIdent();


        point3  Angle;
        Angle = m_Angle.GetRandom();
        temp1.Translate(pos);
        temp2.Rotate(Angle.x, Angle.y, Angle.z);
        temp1 = temp1 * temp2;
        return temp1.GetLoc();
    }
};

class HoEffectBoundingDoughnut : public HoEffectBoundingInterface
{
private:
    HoEffectMinMax<point3> m_Pos;
    HoEffectMinMax<float>  m_Radius;
    HoEffectMinMax<point3> m_Angle;
public:
    HoEffectBoundingDoughnut()
    {
        m_Pos.Min.x = -10;
        m_Pos.Max.x =  10;
        m_Pos.Min.y = -10;
        m_Pos.Max.y =  10;
        m_Pos.Min.z = -10;
        m_Pos.Max.z =  10;

        m_Radius.Min = 50;
        m_Radius.Max = 50;

        m_Angle.Min.x = 0.f;
        m_Angle.Max.x = 8.f;
        m_Angle.Min.y = 0.f;
        m_Angle.Max.y = 8.f;
        m_Angle.Min.z = 0.f;
        m_Angle.Max.z = 8.f;
    }

    void Init(float x1, float x2, float y1, float y2)
    {
        m_Pos.Min.x = y1;
        m_Pos.Max.x = y2;
        m_Pos.Min.y = y1;
        m_Pos.Max.y = y2;
        m_Pos.Min.z = y1;
        m_Pos.Max.z = y2;

        m_Radius.Min = x1;
        m_Radius.Max = x2;
    }
    point3 GetPos()
    {
        point3  pos;
        pos    = m_Pos.GetRandom();
        pos.z += m_Radius.GetRandom();
        matrix4 temp1;
        matrix4 temp2;
        temp1.MakeIdent();
        temp2.MakeIdent();
        point3  Angle;
        Angle = m_Angle.GetRandom();
        temp1.Translate(pos);
        temp2.Rotate(0.f, Angle.y, 0.f);
        temp1 = temp1 * temp2;
        return temp1.GetLoc();
    }
};

enum
{
    SPAWN_VELOCITY_RANDOM,
    SPAWN_VELOCITY_CURPOS,
};

enum
{
    PARTICLE_BILLBOARD_DEFAULT,
    PARTICLE_BILLBOARD_AXIAL,
};

#define MAX_PARTICLE_LIST 100
class HoEffectParticleController : public HoEffectModelControllerInterface
{
public:
    HoEffectParticleController();
    ~HoEffectParticleController();

private:
    HoEffectTextureModel        m_ParticleList[MAX_PARTICLE_LIST];
    HoEffectBoundingInterface   *m_EmitRange;           //방사할 영역(AABB, Sphere, 도넛)

    HoEffectMinMax<color4>      m_Color;                //처음 시작 칼라.
    HoEffectMinMax<point3>      m_Velocity;             //Velocity속도.(Random, 축에서 바깥 방향, 축쪽으로)
    int                         m_VelocityType;         //VelocityType(Random, Out, Int)
    int                         m_ParticleType;         //ParticleType(Billboard, AxialBillboard)
    int                         m_iBlendType;           //BlendType;

    HoEffectMinMax<point3>      m_Size;                 //처음 파티클 사이즈 (Billboard, 하고 Axial 두가지만 지원하도록 한다.)

    float                       m_fEmitRate;            //초당 파티클을 방사할 양
    float                       m_fEmitRateSum;         //초당 방사 내부 계산용 변수
    HoEffectMinMax<float>       m_fEndTime;             //파티클들이 살아 있을 시간
    float                       m_fParticleNum;         //방사할 파티클 총개수(이개수 만큼 뿌리고 없어진다)
    float                       m_fParticleTotalNum;    //실제로 방사한 파티클의 총수(내부 계산용)
    float                       m_fParticleLiveNum;     //현재 살아 있는 파티클의 수(내부 계산용)

    int                         m_iLoop;                // Loop( 0이면 무한, 0이 아니면 갯수 만큼)
    float                       m_fTimer;               // Loop 용 Time
    std::string                 m_TextureName;          // TextureName

    //bool                        m_bLiveFlag;
    HoEffectEventController     m_EffectEventController;

    void    CreateNewParticle(HoEffectTextureModel &part);

public:
    void    Init(const std::string &fileName);
    bool    Main(float elapsedTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);

    //외부 인터페이스들..
    void    InitPos(float x, float y, float z);
    void    InitLoop(int loop);
    void    InitColor(float r, float g, float b, float a);
    void    InitBlendType(int type);
    void    InitEndTime(float x1, float x2);
    void    InitSize(float x, float y);
    void    InitSize(float x1, float x2, float y1, float y2);

    void    InitSpawnBoundingBox(float x1, float x2, float y1, float y2, float z1, float z2);
    void    InitSpawnBoundingSphere(float x1, float x2);
    void    InitSpawnBoundingDoughnut(float x1, float x2, float y1, float y2);

    void    InitParticleNum(float particleNum);
    void    InitEmitRate(float emitRate);
    void    InitVelocity(float x1, float x2, float y1, float y2, float z1, float z2);

    void    InitVelocityType(int type);
    void    InitParticleType(int type);


};

class HoEffectGroup
{
public:
	HoEffectGroup();
    ~HoEffectGroup();
private:
    std::vector<HoEffectModelControllerInterface *> m_ControllerList;
    point3  m_Translate;
	point3  m_Angle;
	bool	m_bLiveFlag;
	
public:
    void    Clear();
    void    CreateFadeList();
    
    bool    Main(float elapsedTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
    bool    AddModelController(HoEffectModelControllerInterface *modelController);
	bool	IsLive()	{ return m_bLiveFlag; }
	const   point3 &GetTranslate() { return m_Translate; }
	void	SetCalcTranslate(const point3 *trans, const point3 *ang);
	HoEffectModelControllerInterface *CreateFactory(int effectType);
};
#endif

