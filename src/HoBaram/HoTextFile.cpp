#include "..\\HoBaram\\HoTextFile.h"

#include "Language\\language.h"

#ifdef	_LANGUAGE_KOREAN

char *HoTextLoginMessage[20] =  {"      서버에 접속중....    ",
								 "      서버 접속 불가       ",
								 "   계정을 다시 입력하세요  ",
								 "비밀 번호를 다시 입력하세요",
								 "해당 아이디는 현재 사용권한이 없으니 고객센터로 문의 바랍니다.",
								 "   아이디가 접속중입니다   ",
								 "  Version이 맞지 않습니다  ",
								 "   서버에 인원이 많습니다  ",
								 "서버와의 연결이 끊어 졌습니다",
								 "  사용기간이 종료되었습니다 ",
								 "  사용시간이 종료되었습니다 ",
								 " 서버계정 삭제 요청중입니다 ",
								 "서버폭주!!! 잠시후 이용 바랍니다.",
								 " 잠시후 이용해 주십시요... ",
								 "비밀번호 3회 이상 오류입니다. 홈페이지 참조 바랍니다.",
								 "비밀번호에 한글 또는 사용할수 없는 문자가 있습니다.",
								 "  12세 미만 이용자는             프리스톤테일을 이용하실 수     없습니다. ",
								 " 프리스톤테일 이용약관에        동의를 하셔야만 게임 진행이    가능합니다.",
								 "JPT_일본용 일정기간 로그인정지",
								 "JPT_일본용 로그인정지"
								};
 
char *HoTextSelectMessage[12] = {"캐릭터를 삭제 하시겠습니까?",
								  "게임을 시작합니다",
								  "캐릭터를 더이상 생성 못합니다.",
								  "캐릭터 생성을 마쳤습니다 위 설정이 맞습니까?", //3
								  "캐릭터의 이름을 입력하세요", //4
								  "캐릭터 이름이 존재합니다", //5
								  "  캐릭터를 선택하세요  ", //6
								  " 종족마크를 선택하세요 ", //7
								  "  캐릭터를 선택하세요  ", //8
								  "캐릭터 얼굴을 선택하세요", //9
								  "클랜에 가입되어 있는 캐릭터는 삭제할수 없습니다", //10
								  "클랜 정보를 확인할수 없습니다" //11
								};

char *HoTextTempscronInfo[5] = {"템스크론은 기술을 바탕으로 발전해온 종족으로 무기를 통한 여러가지 기술을 가지고 있으며 모든 종족중 유일하게 기계류를 사용할 수 있는 강인한 육체를 가지고 있다.",

                                "기계를 다루는 능력이 뛰어난  캐릭터이며 공격형 기계류를 다룰수 있는 유일한 캐릭터이다.",
								"파이터들은 근접전에 있어서 매우 강한 위력을 발휘하며 근접전용 무기를 주로 사용한다.",
								"창을 매우 능숙하게 다루어 적에게 치명타를 입히는 기술을 구사할 수 있는 캐릭터이며 시야가 넓고 내구력이 높은 스케일 메일을 착용할 수 있다.",
								"원거리와 대공능력을 고루 갖춘 캐릭터이며 주무기는 활과 석궁류이다."};


//ktj : 추가된 모라이온용 설명글 새로넣음.
char *HoTextMoryon = "모라이온";
char *HoTextMoryonInfo[5] = {
	"프리스톤 대륙 북부지방을 중심으로 살고있는 모라이온들은 소박하면서 온유하며 그안에 화려한 문화를 담고있는 종족으로 육체적인 수양과 정신적인 수양을 병행하며, 그들만의 독특한 문화인 신앙과 마법을 발전시켜 정신적인 힘을 자유로이 사용할수 있는 종족이다.",

    "나이트는 경건한 정신과 육체를 가지고 있는 전사들을 통칭하는 모라이온들의 전사들로 신성한 힘을 물리적인 공격에 사용하는 신성한 전사로 모라이온의 강인한 힘을 나타내는 대표적인 클래스이다.",
	"스피어나 제블린류를 주로 다루는 아탈란타들은 자신이 사용하는 무기에 마법의 특성을 담아 강한 공격을 구사하는 전사형 캐릭터이다. 그들의 진정한 힘은 스피어와 제블린을 사용할때 나타나며 긴 사거리를 이용한 공격을 바탕으로 마법과 물리 공격력의 조합은 어느 누구도 흉내낼수 없는 아탈란타 힘의 원천이라 전해진다.",
	"성스러운 마법을 토대로 성직자의 길을 걷고있는 프리스티스들은 신성한 힘만을 사용하는 마법사들로 오랜 수행을 통해 성스러운 힘을 부여받은 이들은 다른 이들을 치료하거나 더 나아가 신성한 힘을 통해 공격까지 구사할수 있다고 전해진다. 하지만 정신적으로 강인하지만 육체적으로 약한면도 가지고 있다. ",
	"마법의 힘을 공격력으로 승화시켜 공격을 지향한 마법을 구사하는 매지션들은 각종 원소에 대한 속성을 이해하여 그힘을 원천으로 공격능력으로 바꾸는 마법을 연구하는 클래스이며 능력에 따라 땅과 별을 움직이는 힘을 얻을수 있다고 전해진다.",
};



char *HoText_PartyMessage = "님이 동료 신청";

char *HoTextTempskron = "템스크론";


char *HoTextFriendNear = "[최근목록]";
char *HoTextFriendList = "[친구목록] %d/%d";
char *HoTextFriendRefuse = "[거부자목록] %d/%d";

#endif

#ifdef	_LANGUAGE_CHINESE
#include "Language\\Chinese\\C_HoTextFile.h"
#endif

#ifdef	_LANGUAGE_JAPANESE
#include "Language\\Japanese\\J_HoTextFile.h"
#endif

#ifdef	_LANGUAGE_TAIWAN
#include "Language\\Taiwan\\T_HoTextFile.h"
#endif

#ifdef	_LANGUAGE_ENGLISH
#include "Language\\English\\E_HoTextFile.h"
#endif

#ifdef	_LANGUAGE_THAI
#include "Language\\THAI\\TH_HoTextFile.h"
#endif

#ifdef _LANGUAGE_VEITNAM
#include "Language\\VEITNAM\\V_HoTextFile.h"
#endif

#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_HoTextFile.h"
#endif

#ifdef _LANGUAGE_ARGENTINA
#include "Language\\ARGENTINA\\A_HoTextFile.h"
#endif