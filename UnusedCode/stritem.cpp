
struct	sITEM_CREATE {
	DWORD	Head;			//헤더
	DWORD	dwVersion;		//생성 버전
	DWORD	dwTime;			//생성시간
	DWORD	dwChkSum;		//아이템 체크섬
};

struct sITEM_SPECIAL {

	//그냥 추가되는 값
	int		Add_Absorb;				//흡수력 
  	int     Add_Defence;			//방어력 
	float   Add_fSpeed;				//이동 속도 
	float   Add_fBlock_Rating;		//(방패)블럭율 
	int     Add_Attack_Speed;		//공격속도
	int     Add_Critical_Hit;		//1.5배 데미지확율
	int     Add_Shooting_Range;		//사정거리 
	float   Add_fMagic_Mastery;     //마법숙련도 
	short	Add_Resistance[8];		//원소에대한 저항력 

	////////////////////////////////////////////////

	short	Lev_Attack_Resistance[8];	//원소에대한 공격력
	int		Lev_Mana;				//마나회복(최소)(최대)
	int		Lev_Life;				//라이프회복(최소)(최대) 
	int     Lev_Attack_Rating;		//명중력 
	short	Lev_Damage[2];			//공격력

	int		Per_Mana_Regen;			//마나 재생 
	int		Per_Life_Regen;			//라이프 재생 
	int		Per_Stamina_Regen;		//스테미나 재생

	//////////////////////////////////////////////////

	DWORD	dwTemp[32];
};


struct sITEMINFO{

	DWORD	dwSize;						//아이템 구조 크기
	
	sITEM_CREATE	ItemHeader;			//아이템 생성 정보

	short	Durability[2];				//내구력

	//////// 실제 아이템 데이타정보가 들어갑니다 /////////

	/*-------------------------*
	*		 아이템 정보	
	*--------------------------*/
	DWORD	CODE;				//아이템 코드 	
	char	ItemName[32];		//아이템 이름 	

	/*-------------------------*
	*		공통 사항 	
	*--------------------------*/
	int     Weight;				//무게 		
	int     Price;				//가격

	/////////////////////////////////////////
	int		Index;				//인덱스
	int		Counter;			//카운터
	////////////////////////////////////////

	/**원소**/
	short	Resistance[8];		//원소에대한 저항력 
	/********/

	int		Sight;				//시야

	DWORD	Temp0;

	/*-------------------------*
	*		 공격성능 
	*--------------------------*/
	short	Damage[2];			//공격력 
	int     Shooting_Range;		//사정거리 
	int     Attack_Speed;		//공격속도 
	int     Attack_Rating;		//명중력 
	int     Critical_Hit;		//1.5배 데미지확율  

	/*-------------------------*
	*		 방어성능 
	*--------------------------*/

	int		Absorb;				//흡수력 
  	int     Defence;			//방어력 
	float   fBlock_Rating;		//(방패)블럭율 

	/*-------------------------*
	*		 이동성능 
	*--------------------------*/
	float     fSpeed;				//이동 속도 

	/*-------------------------*
	*		 팔찌 성능 
	*--------------------------*/

	int		Potion_Space;		//소켓 공간 할당 
	
	/**특수능력**/
	float   fMagic_Mastery;     //마법숙련도 
	float   fMana_Regen;		//마나 재생 
	float   fLife_Regen;		//라이프 재생 
	float   fStamina_Regen;	    //스테미나 재생 
	float   fIncrease_Life;     //라이프 최대치상승 
	float   fIncrease_Mana;     //마나 최대치상승
	float   fIncrease_Stamina;  //스테미나 최대치상승

	/************/

	/*-------------------------*
	*		요구특성 
	*--------------------------*/
	int     Level;				//레벨 
	int     Strength;			//힘 	
	int     Spirit;				//정신력 
	int     Talent;				//재능 
	int     Dexterity;			//민첩성 
	int     Health;				//건강 

	/*-------------------------*
	*		 회복약 
	*--------------------------*/
	short   Mana[2];            //마나회복(최소)(최대)
	short   Life[2];            //라이프회복(최소)(최대) 
	short   Stamina[2];         //스테미너회복(최소)(최대)
	

	/*-------------------------*
	*		 .....
	*--------------------------*/
	int		Money;				//보유한 돈


	DWORD	dwTemp1[8];			//예비

	DWORD	DispEffect;			//아이템 표시 이펙트 (예정)

	/*-------------------------*
	*		캐릭터 특화아이템    (현재 미설정)
	*--------------------------*/

	DWORD			JobCodeMask;		//특화 직업	(직업별 비트 마스크)
	sITEM_SPECIAL	JobItem;			//특화 아이템 성능

	DWORD	dwTemp[16];			//예비
};


