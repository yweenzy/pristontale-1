#pragma once

#ifndef __CE_SUBCHIP_H__
#define __CE_SUBCHIP_H__
#include "clan_Enti.h"
class CLANEntity_SubChip: public CLANEntity
{
public:
	CLANEntity_SubChip();
	~CLANEntity_SubChip();
public:
	int Init(int Life);
	int Clear();
	void Main();	
	void Draw();
	void menuInit(int num);
protected:
private:

};
#endif

#ifdef CE_SUBCHIP_CPP
class CLANEntity_SubChip g_SubChip;
#else
extern class CLANEntity_SubChip g_SubChip;
#endif