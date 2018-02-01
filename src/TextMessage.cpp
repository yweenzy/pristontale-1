#include "TextMessage.h"

#include "Language\\language.h"

#ifdef	_LANGUAGE_KOREAN
//////////////////// 한국어 - 기본 ////////////////////////////
#include "Language\\Korean\\k_TextMessage.h"
#include "Language\\Korean\\k_QuestMsg.h"
#endif

#ifdef	_LANGUAGE_CHINESE
//중국어
#include "Language\\Chinese\\C_TextMessage.h"
#include "Language\\Chinese\\C_QuestMsg.h"
#endif

#ifdef	_LANGUAGE_JAPANESE
//일본어
#include "Language\\Japanese\\J_TextMessage.h"
#include "Language\\Japanese\\J_QuestMsg.h"
#endif

#ifdef	_LANGUAGE_TAIWAN
//자유중국
#include "Language\\Taiwan\\T_TextMessage.h"
#include "Language\\Taiwan\\T_QuestMsg.h"
#endif

#ifdef	_LANGUAGE_ENGLISH
//영국어
#include "Language\\English\\E_TextMessage.h"
#include "Language\\English\\E_QuestMsg.h"
#endif

#ifdef	_LANGUAGE_THAI
//태국어
#include "Language\\THAI\\Th_TextMessage.h"
#include "Language\\THAI\\Th_QuestMsg.h"
#endif

//베트남어
#ifdef _LANGUAGE_VEITNAM
#include "Language\\VEITNAM\\V_TextMessage.h"
#include "Language\\VEITNAM\\V_QuestMsg.h"
#endif

//브라질어
#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_TextMessage.h"
#include "Language\\BRAZIL\\B_QuestMsg.h"
#endif

//아르헨티나어
#ifdef _LANGUAGE_ARGENTINA
#include "Language\\ARGENTINA\\A_TextMessage.h"
#include "Language\\ARGENTINA\\A_QuestMsg.h"
#endif