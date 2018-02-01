/*----------------------------------------------------------------------------*
*	파일명 :  sinLinkHeader.h	
*	하는일 :  Header를 관리한다 
*	작성일 :  최종업데이트 12월 
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#ifndef _SINLINK_HEADER_ //_SINLINK_HEADER_ 가 정의되어있지않으면
#define _SINLINK_HEADER_ //_SINLINK_HEADER_ 를 정의하며 파일 인쿠루드 

//#ifdef !_SINLINK_HEADER_ //_SINLINK_HEADER_ 가 정의되어있지않으면
//#define _SINLINK_HEADER_ //_SINLINK_HEADER_ 를 정의하며 파일 인쿠루드 
//#pragma once //한번만오픈 



#include <windows.h>
#include <math.h>
#include <stdio.h>


#include "smlib3d\\smd3d.h"
#include "..\\drawsub.h"
#include "..\\smwsock.h"
#include "..\\smpacket.h"
#include "..\\HoBaram\\HoLinkHeader.h" //호바람 
#include "..\\effectsnd.h"
#include "..\\playsub.h"
#include "Language\\language.h"

#include "sinUtil.h"
#include "sinMonster.h"
#include "sinMain.h"
#include "sinTrade.h"
#include "sinSubMain.h"
#include "sinItem.h"
#include "sinInvenTory.h"
#include "sinCharStatus.h"
#include "sinInterFace.h"
#include "sinShop.h"
#include "sinSkill.h"
#include "sinMessageBox.h"
#include "sin3D.h"
#include "sinEffect.h"
#include "sinEffect2.h"

#include "sinParticle.h"	
#include "sinMsg.h"
#include "sinHelp.h"
#include "sinQuest.h"
#include "sinSkillEffect.h"
#include "sinEvent.h"
#include "sinPublicEffect.h"
#include "AssaUtil.h"
#include "AssaEffect.h"
#include "sinAssaParticle.h"
#include "AssaTestParticle.h"
#include "sinAssaSkillEffect.h"

#include "YameEffect.h"
#include "sinWarpGate.h"
#include "sinHelpPet.h"
#include "sinSOD2.h"
//#include "sinMedia.h"
#include "HaQuest.h"
#include "haPremiumItem.h"
#include "sinParkPcBangPet.h"   //피시방

////////// 스킬 함수 파일 
#include "SkillFunction\\Tempskron.h"
#include "SkillFunction\\Morayion.h"


#endif