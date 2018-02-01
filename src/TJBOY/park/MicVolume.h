#pragma once
#ifndef __MICVOL_H__
#define __MICVOL_H__

#include <Mmsystem.h>

typedef struct MixerControlStruct {
	short nIndex;
	short nDeviceNum;
	unsigned int nLineID;
	int nMax;
	char DeviceName[64];
	MIXERCONTROL m_ctlMixerSpeaker;
	MIXERCONTROL m_ctlMixerMute;
} MCS;

class CMicVolume
{
public:
	HMIXER h_mix;						//장치 핸들
	MCS m_WavOut, m_WavIn, m_MicIn, m_MicOut;
	float nVolStep;
public:
	CMicVolume(void);
	~CMicVolume(void);

	BOOL Init();	//초기화및 설정
	HMIXER MixDevice(HMIXER current_mix, unsigned int mix_id);	// MixDevice를 ID값에 맞게 읽어드린다
	void GetMicDevice();	// 마이크 볼륨 조정 디바이스 드라이버를 읽어드린다.
	BOOL GetDevice();		// 등록된 장치의 정보를 읽을 수 없습니다
	float VolDevice(MCS *pData);	// 장치의 볼륨을 얻어 온다
	void GetDeviceCtrl(MCS *pData);	
	void SetDeviceCtrl(MCS *pData, float vol);	//장치의 볼륨을 조절한다, max 볼륨은 각 사운드 카드마다 틀리다
};

#endif


#ifdef MICVOL_CPP

	class CMicVolume cmicvol;

#else

	extern class CMicVolume cmicvol;

#endif
