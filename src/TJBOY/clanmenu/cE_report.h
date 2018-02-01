#pragma once

#ifndef __CE_REPORT_HPP__
#define __CE_REPORT_HPP__

#include "clan_Enti.h"

#define REPORT_MAX 512
class CLANEntity_report: public CLANEntity
{
public:
	CLANEntity_report();
	~CLANEntity_report();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();
	void Draw();
	void InitMsg(char *msg);


	void menuInit(int num,LONG x, LONG y);
public:	
	
	//int nScl_Bar;           //스크롤바
	//RECT scrIconPos;		//스크롤바의 움직이는아이콘위치설정
	char szReport[REPORT_MAX];
	
};


#endif 





#ifdef CE_REPORT_CPP

	class CLANEntity_report cClanReport;
//	cClanReport.Init(char *msg);
//	cClanReport.menuInit(int num);

#else

	extern class CLANEntity_report cClanReport;
	//extern cClanReport.Init(char *msg);
	//extern cClanReport.menuInit(int num);

#endif
