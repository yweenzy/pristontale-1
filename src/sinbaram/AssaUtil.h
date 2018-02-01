/*----------------------------------------------------------------------------*
*	파일명 :  AssaUtil
*	하는일 :  이것저것 잡다한거 
*	작성일 :  최종업데이트 2002년 12월
*	적성자 :  박상열 & 호동동
*-----------------------------------------------------------------------------*/	
#ifndef _ASSAUTIL_HEADER_

#define _ASSAUTIL_HEADER_

char *FindFile(char *fileName); //찾고자하는 파일의 경로를 리턴받는다 


void InitAssaRes();				//리소스를 맨처음 한번 초기화 하는 함수..
void CloseAssaRes();			//리소스를 해제하는 함수.
void LoadAssaRes();				//리소스를 읽는 함수.

void *AssaSearchRes(char *resName, int blendType); //리소스를 찾는 함수..(주로 쓰는 함수는 이거)


#include <list>
using namespace std;

//3D경로를 저장하는 클래스..
class cASSATrace
{
public:
	list<POINT3D> TraceList;
private:
	unsigned int Length;		//리스트의 크기.

public:
	cASSATrace()
	{
		Length = 50;	
	}

	~cASSATrace()
	{
			
	}
	
	//리스트의 크기를 정해주는 함수.
	void SetLength(int length)
	{
		Length = length;	
	}

	//리스트에 데이타를 추가..
	void AddData(POINT3D *pos)
	{
		//Length = 50;
		POINT3D curPos;
		curPos.x = pos->x;
		curPos.y = pos->y;
		curPos.z = pos->z;
		
		int t = TraceList.size();
		if(TraceList.size() < Length)
			TraceList.push_front(curPos);
		else
        {
			if(!TraceList.empty())
            {
				std::list<POINT3D>::iterator i;
				i = TraceList.end();
                --i;
                TraceList.erase(i);
				TraceList.push_front(curPos);
			}
		}
	}

};

bool	AssaAddFace2D ( smFACE2D *face , int ZPosiFlag = FALSE, int angle = 0);
bool	AssaAddFace2DLine(smFACE2D *face, POINT3D *localDestPos,BOOL centerFlag = FALSE);//destPos 위치까지 늘려서 그리는 빌보드..
bool	AssaAddFaceWorld(smFACE2D *face, POINT3D *inAngle = NULL);
bool	AssaAddFaceTrace(smFACE2D *face, cASSATrace *assaTrace);

bool    AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos);
bool	AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos, int length);
bool    AssaSearchWeaponPos(smCHAR *character, POINT3D *outWeaponPos, float u = 0.0f);

int AssaTestEffectImage();      //테스트를 위해 INI파일을 읽어 셋팅한다
#endif