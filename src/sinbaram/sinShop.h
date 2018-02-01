/*----------------------------------------------------------------------------*
*	파일명 :  sinShop.h	
*	하는일 :  상점을 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#define     MAX_SHOP_CLASS_ITEM	30  //각 클래스당 30씩

#define     SHOP_ROW			9  //임시 상점 아이템 영역 
#define     SHOP_COL			9
	
#define 	SINALLREPAIR		1 
#define 	SINREPAIR			2    
#define 	SINSELL				3      
#define 	SINBUY				4       
#define 	SINRIGHTARROW		5
#define 	SINLEFTARROW		6  
#define     SINSHOPEXIT			7

#define 	SIN_WEAPON			1 
#define 	SIN_DEFENSE			2 
#define 	SIN_ETC				3 


struct	sMYSHOP_ITEM{
	sITEMINFO	sItem;
	int			Price;
	short       Posi[2];
	DWORD		dwTemp[3];
};

struct sMYSHOP{
	DWORD			CHAR_CODE;
	DWORD			dwTemp[6];
	sMYSHOP_ITEM	sMyShopItem[30]; //보내고 받는 아이템
};

struct sMYSHOP_ITEM_SERVER{ //개인상점으로 구매할 아이템 
	DWORD CODE;
	DWORD CkSum;
	DWORD Head;
	DWORD sTime;
	DWORD Price;
	DWORD SendFlag;
	DWORD Buyer;

	DWORD Temp[4];

};

class cSHOP{


public:

	int OpenFlag;	//현재 인벤토리가 열려있나 아닌가에 대한 플랙 
	int UseItemFlag; // 박재원 - 이동 상점 아이템

	int PosX;
	int PosY;

	int MatShop[10];

	int SelectShop; // 1무기 ,2 방어구 ,3 그외 것들 

	int ShopIconPosi;

	
	sITEM ShowShopItem[30];	//한번에 보여질 아이템 최대 30
	sITEM ShopItem[60]; //저장될 아이템 
	

	int RevWeaponCnt;
	int RevDefenseCnt;
	int RevEtcCnt;
	int MatMyShop_Button;
	
	DIRECTDRAWSURFACE lpGoldEdit;

	DIRECTDRAWSURFACE lpAllRepair;
	DIRECTDRAWSURFACE lpRepair;

	DIRECTDRAWSURFACE lpSell;
	DIRECTDRAWSURFACE lpBuy;

	DIRECTDRAWSURFACE lpAllRepair_D;
	DIRECTDRAWSURFACE lpRepair_D;

	DIRECTDRAWSURFACE lpSell_D;
	DIRECTDRAWSURFACE lpBuy_D;

	DIRECTDRAWSURFACE lpRightArrow;
	DIRECTDRAWSURFACE lpLeftArrow;

	
	DIRECTDRAWSURFACE lpTabAttack;
	DIRECTDRAWSURFACE lpTabDefense;
	DIRECTDRAWSURFACE lpTabEtc;

	DIRECTDRAWSURFACE lpTabAttack_D;
	DIRECTDRAWSURFACE lpTabDefense_D;
	DIRECTDRAWSURFACE lpTabEtc_D;

	DIRECTDRAWSURFACE lpExit;
	DIRECTDRAWSURFACE lpGrid;

	DIRECTDRAWSURFACE lpRepairAllInfo;	
	DIRECTDRAWSURFACE lpRepairInfo;
	DIRECTDRAWSURFACE lpDefaultRepairAll;	
	DIRECTDRAWSURFACE lpDefaultRepair;

	DIRECTDRAWSURFACE lpSellInfo;
	DIRECTDRAWSURFACE lpBuyInfo;


	DIRECTDRAWSURFACE lpTitle_Attack;
	DIRECTDRAWSURFACE lpTitle_Etc;
	DIRECTDRAWSURFACE lpTitle_Trade;
	DIRECTDRAWSURFACE lpTitle_WareHouse;

	DIRECTDRAWSURFACE lpWeightEdit;

	DIRECTDRAWSURFACE lpNoUseBox;

	DIRECTDRAWSURFACE lpCraftItemMain;
	DIRECTDRAWSURFACE lpCraftItemButton;
	DIRECTDRAWSURFACE lpCraftItemButtonInfo;
	DIRECTDRAWSURFACE lpTitle_CraftItem;

	// pluto 제련
	DIRECTDRAWSURFACE lpSmeltingItemMain;
	DIRECTDRAWSURFACE lpTitle_SmeltingItem;
	DIRECTDRAWSURFACE lpSmeltingItemButtonInfo;

	// pluto 제작
	DIRECTDRAWSURFACE lpManufactureItemMain;
	DIRECTDRAWSURFACE lpTitle_ManufactureItem;
	DIRECTDRAWSURFACE lpManufactureItemButtonInfo;

	// 석지용 - 믹스쳐 리셋용 이미지 로딩 추가
	DIRECTDRAWSURFACE lpMResetTitle;
	DIRECTDRAWSURFACE lpMResetMain;
	DIRECTDRAWSURFACE lpMResetButton;
	DIRECTDRAWSURFACE lpMResetButtonInfo;
	
	DIRECTDRAWSURFACE lpTitle_Aging;
	DIRECTDRAWSURFACE lpAging_Info;
	

	DIRECTDRAWSURFACE	lpShopMain;
	DIRECTDRAWSURFACE	lpShopMain2;


	//개인 상점
	DIRECTDRAWSURFACE	lpMyShopExp;
	DIRECTDRAWSURFACE	lpMyShopExp_;
	DIRECTDRAWSURFACE	lpMyShopExp_T;
	DIRECTDRAWSURFACE	lpMyShopNoSale;
	DIRECTDRAWSURFACE	lpMyShopNoSale_;
	DIRECTDRAWSURFACE	lpMyShopNoSale_T;
	DIRECTDRAWSURFACE	lpMyShopSale;
	DIRECTDRAWSURFACE	lpMyShopSale_;
	DIRECTDRAWSURFACE	lpMyShopSale_T;
	DIRECTDRAWSURFACE    lpTitle_MyShop;
	DIRECTDRAWSURFACE    lpImage_MyShop;
	DIRECTDRAWSURFACE    lpMyShop_T;
	

	
public:
	cSHOP();
	~cSHOP();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void CheckShopNpcState();  //NPC와 헤어짐을 체크한다 

	//void CopyShopItemToShow(int Index);//서버에서 받아온 아이템을 보여줄 아이템으로 복사한다 
	void CopyShopItemToShow(int Index,int Kind=0);

	int GetShopItemXY(sITEM *pItem); //아이템의 좌표를 구한다 

	void DrawShopText(); //상점 텍스트를 표시한다 

	////////////////////아아템 사고 팔기 
	int RecvBuyItemToServer(sITEM *pItem ,int ItemCount=1); //아이템을 산다 
	int SellItemToShop(sITEM *pItem,int ItemCount=1); //아아템을 판다 

	int SendBuyItemToServer(sITEM *pItem , int ItemCount=1 ); //서버에서아이템을 사온다 

	void DeleteShopItem(); //상점을 닫을때 상점아이템을 초기화한다

	int CheckHighRankItem(sITEM *pItem); //좋은아이템 체크

	//현재 아이템을 살수있는 지 체크한다.
	int haBuyMoneyCheck(int BuyMoney);
	//상점 아이템 세율적용된 가격을 표시해준다.
	int haShopItemPrice(int Money);
};

/*----------------------------------------------------------------------------*
*								개인상점 등록 클래스 
*-----------------------------------------------------------------------------*/
class cMYSHOP{
public:
	int OpenFlag;	
	sITEM MyShopItem[30];

	char szDoc[128];     //홍보문구
	char szSendDoc[128]; //서버로 보낼 홍보문구

public:
	
	//아이템이 셋팅될공간을 찾는다
	int SetMyShopItem(sITEM *pItem);

	//셋팅한다
	int LastSetMyShopItem(sITEM *pItem);

	//인벤아이템을 등록한다
	int SetShopItemToInven(sITEM *pItem);

	//상점에 등록한 아이템을 찾는다
	int SearchShopItemToInven(sITEM *pItem);

	//아이템을 서버로 보낸다 
	int SendMyShopItem(); 

	//서버에서 구매요청이 들어온 아이템을 받는다
	int RecvMyShopItem( DWORD dwCharCode , sMYSHOP_ITEM_SERVER *lpShopItem );

	//자신이 가질수 있는 금액을 리턴한다
	int GetLimitMoney(int Money);

	//물건이 다팔리면 상점을 닫는다
	int AutoCloseShop();

	//개인상점의 돈을 구해온다
	int GetTotalMyShopItemMoney();

};
/*----------------------------------------------------------------------------*
*								개인상점 클래스 
*-----------------------------------------------------------------------------*/
class cCHARSHOP{
public:
	int OpenFlag;	

public:
	sITEM CharShopItem[30];
	
	//아이템을 받는다
	int RecvShopItem(sMYSHOP *sMyShop);

	//받은 아이템을 찾는다
	int SearchMyShopItem(DWORD CODE ,DWORD Head , DWORD CheckSum);

	//개인상점에서산 아이템을 인벤토리로 셋팅한다
	int SetCharShopItemToInven(sITEMINFO *pItem_Info);

	//개인상점에서 아이템을 산다
	int BuyItem(int Index);

};

extern cSHOP cShop;

extern int sinShopKind;  //현재 상점의 종류  1  무기 2 방어 3 물약 (defalt 는 상점)

extern int TalkNpcState; //현재 상점 NPC와 함께 있을경우 

extern int ShopGoldEdit[2][4];

extern int ShopArrowPosi; //상점 화살표 방향 

extern int BuyItemServerFlag; //서버에서 물건을 살때 메세지를 받지않으면 살수없다 

extern cMYSHOP cMyShop;
extern cCHARSHOP cCharShop;

extern sMYSHOP     sMyShop;       //보내는 MyShop 구조체
extern sMYSHOP     sRecvMyShop;   //받는 MyShop 구조체
extern int MyShopSendButton;

extern int MyShopExpBox;
extern int MyShopItemSellMoney2;
extern sMYSHOP_ITEM_SERVER sMyShop_Server;
extern sITEMINFO MyShopPotion;
extern int MyShopItemCancelIndex[2];
