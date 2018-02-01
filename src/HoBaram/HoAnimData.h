/*----------------------------------------------------------------------------*
*	파일명 :  HoAnimData.h
*	하는일 :  에니메이션 데이타 관리  
*	작성일 :  최종업데이트 2000.1 
*	적성자 :  홍호동.
*-----------------------------------------------------------------------------*/	

#ifndef _HO_ANIM_DATA_
#define _HO_ANIM_DATA_

//AnimFrame Data Flag
#define INFO_NONE				0x00000000
#define	INFO_IMAGE				0x00000001
#define	INFO_DELAY				0x00000002
#define INFO_ALPHA				0x00000004

//확장1 (사이즈가 변함)
#define	INFO_SIZEWIDTH			0x00000008

//확장2 (사이즈가 가로, 세로 변하고, 회전이 되고 RGB값도 변함)
#define INFO_ANGLE				0x00000010
#define	INFO_SIZEHEIGHT			0x00000020
#define INFO_RGB				0x00000040

#define INFO_DEFAULT			(INFO_IMAGE | INFO_DELAY | INFO_ALPHA)
#define INFO_ONESIZE			(INFO_IMAGE | INFO_DELAY | INFO_ALPHA | INFO_SIZEWIDTH)
#define INFO_ONESIZEANGLE		(INFO_IMAGE | INFO_DELAY | INFO_ALPHA | INFO_SIZEWIDTH | INFO_ANGLE)

struct hoAnimFrame
{
	//디폴트..
	unsigned short ImageNum;		//Frame당 이미지의 번호....
	unsigned short Delay;			//Frame당 Delay
	BYTE AlphaValue;				//Frame당 알파값 변화율..
	
	//확장1...
	unsigned short SizeWidth;		//기본 디퐅트 값으로 Width값을 쓴다..(가로, 세로 길이가 같음)
	
	//확장2...
	unsigned short SizeHeight;
	float Angle;					//Frame당 앵글 변화율.. (-360~360)까지..
	BYTE ColorRValue;				//Frame당 컬러값..					
	BYTE ColorGValue;
	BYTE ColorBValue;
};

class HoAnimDataMgr;
//에니메이션 시퀀스 데이타 파일...
class HoAnimSequenceData
{
public:
	HoAnimSequenceData();
	~HoAnimSequenceData();

	hoAnimFrame *AnimFrame;
	int			AnimFrameCount;
	int			StartBlendValue;
	int			BlendType;

public:
	int  DataFileIndex;				//이미지 데이타 파일 리스트이 인덱스 번호..
	char IniName[64];

private:
	BYTE		InfoFlag;					//정보 Flag


public:
	int Load(char *iniName, HoAnimDataMgr *animationData = NULL);
	int Init();

	BYTE GetAnimInfo()
	{
		if(InfoFlag == INFO_DEFAULT)
		{
			return INFO_DEFAULT;
		}
		else if(InfoFlag == INFO_ONESIZE)
		{
			return INFO_ONESIZE;
		}
		else if(InfoFlag == INFO_ONESIZEANGLE)
		{
			return INFO_ONESIZEANGLE;
		}
		
		return INFO_NONE;
	}
};

//에니메이션 이미지 데이타 파일...
class HoAnimImageData
{
private:
	int  MaterialNum;			//Material 번호..(smMaterialGroup의)
	int	 AnimationCount;		//Animation의 갯수..

public:
	char IniName[64];			//ini Name...

	HoAnimImageData();
	~HoAnimImageData();

	char *GetIniName() { return IniName;}
	int Load(char *iniName);
	int GetAnimationCount(){ return AnimationCount; }
	int GetMaterialNum(){ return MaterialNum; }
	int Init();

private:
	int Load(char *textureName, int count);

};


#define MAX_IMAGEDATA_BUFFER	100
#define MAX_SEQUENCEDATA_BUFFER	100
class HoAnimDataMgr
{
public:
	HoAnimDataMgr();
	~HoAnimDataMgr();
	
	int SequenceLoad(char *iniName);
	int	ImageLoad(char *iniName);
	
public:
	HoAnimSequenceData SequenceDataBuffer[MAX_SEQUENCEDATA_BUFFER];
	int				   SequenceDataBufferCount;

	HoAnimImageData    ImageDataBuffer[MAX_IMAGEDATA_BUFFER];
	int				   ImageDataBufferCount;
	
	
	int	GetSearchSequenceData(char *iniName);
	int	GetSearchAnimImageData(char *iniName);
		
	int	Init();

	//aniDataIndex 번호로 실제로 쓰는 Material을 찾는다.
	int GetMaterialNum(int aniDataIndex)
	{
		if(aniDataIndex >= 0 && aniDataIndex < SequenceDataBufferCount)
			return ImageDataBuffer[SequenceDataBuffer[aniDataIndex].DataFileIndex].GetMaterialNum();
			
		return -1;
	}
};
extern HoAnimDataMgr AnimDataMgr;

#endif