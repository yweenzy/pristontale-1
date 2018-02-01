//----------------------------------------------------------------------------------
//  FIleName : HoEffectEvent.h
//
//	Class Name:	,
//
//  Desc:
//
//----------------------------------------------------------------------------------
#ifndef _HO_EFFECT_EVENT_H_
#define _HO_EFFECT_EVENT_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"
#include "HoEffectModel.h"
#include "HoEffectUtil.h"
#include <vector>
#include <string>


enum
{
    CLASS_EVENT_ANGLE = 1,
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


    int GetClassID() {return ClassID;}

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
    HoEffectMinMax<color4> Color;

public:
    HoEffectEventColor()
    {
        ClassID = CLASS_EVENT_COLOR;
    }
    ~HoEffectEventColor() {}

    void Set(HoEffectMinMax<color4> in)
    {
        Color = in;
    }

    HoEffectMinMax<color4> Get()
    {
        return Color;
    }

    void VisitEffectModel(HoEffectModelInterface &effectModel);
};

#endif 