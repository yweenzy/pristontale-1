#define	FACE_MODEL_MAX		7	//All full-time [0], the first full-time (1), the second full-time [2], the third full-time [3], two eolkeun version [4], [5] // bakjaewon - Add 2010 World events (soccer ball portion [6]) seven kinds
#define	HEAREPOTION_MAX		13	//Hair Potion maximum tint <Tint Hair Potion 060 809 seonggeun Modify>

////////////////////////// Model Image /////////////////////////////
char *szModel_FighterFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {				//Fighter
	{
		// 전업전[0]
		"char\\tmABCD\\tmh-b01.inf",				
		"char\\tmABCD\\tmh-b02.inf",
		"char\\tmABCD\\tmh-b03.inf",
		"char\\tmABCD\\tmh-b04.inf",
		"char\\tmABCD\\tmh-b05.inf",
		"char\\tmABCD\\tmh-b06.inf",
		"char\\tmABCD\\tmh-b07.inf",
		"char\\tmABCD\\tmh-b08.inf",	

		"char\\tmABCD\\tmh-b09.inf",
		"char\\tmABCD\\tmh-b10.inf",
		"char\\tmABCD\\tmh-b11.inf",
		"char\\tmABCD\\tmh-b12.inf",
		"char\\tmABCD\\tmh-b13.inf"	

	},
	{
		// 1차 전업
		"char\\tmABCD\\tmh-b01a.inf",
		"char\\tmABCD\\tmh-b02a.inf",
		"char\\tmABCD\\tmh-b03a.inf",
		"char\\tmABCD\\tmh-b04a.inf",
		"char\\tmABCD\\tmh-b05a.inf",
		"char\\tmABCD\\tmh-b06a.inf",
		"char\\tmABCD\\tmh-b07a.inf",
		"char\\tmABCD\\tmh-b08a.inf",

		"char\\tmABCD\\tmh-b09a.inf",
		"char\\tmABCD\\tmh-b10a.inf",
		"char\\tmABCD\\tmh-b11a.inf",
		"char\\tmABCD\\tmh-b12a.inf",
		"char\\tmABCD\\tmh-b13a.inf"
	
	},
	{
		// 2차 전업
		"char\\tmABCD\\tmh_b01b.inf",
		"char\\tmABCD\\tmh_b02b.inf",
		"char\\tmABCD\\tmh_b03b.inf",
		"char\\tmABCD\\tmh_b04b.inf",
		"char\\tmABCD\\tmh_b05b.inf",
		"char\\tmABCD\\tmh_b06b.inf",
		"char\\tmABCD\\tmh_b07b.inf",
		"char\\tmABCD\\tmh_b08b.inf",
		
		"char\\tmABCD\\tmh_b09b.inf",
		"char\\tmABCD\\tmh_b10b.inf",
		"char\\tmABCD\\tmh_b11b.inf",
		"char\\tmABCD\\tmh_b12b.inf",
		"char\\tmABCD\\tmh_b13b.inf"
	
	},
	{
		// 3차 전업
		"char\\tmABCD\\tmh-b01c.inf",
		"char\\tmABCD\\tmh-b02c.inf",
		"char\\tmABCD\\tmh-b03c.inf",
		"char\\tmABCD\\tmh-b04c.inf",
		"char\\tmABCD\\tmh-b05c.inf",
		"char\\tmABCD\\tmh-b06c.inf",
		"char\\tmABCD\\tmh-b07c.inf",
		"char\\tmABCD\\tmh-b08c.inf",

		"char\\tmABCD\\tmh-b09c.inf",
		"char\\tmABCD\\tmh-b10c.inf",
		"char\\tmABCD\\tmh-b11c.inf",
		"char\\tmABCD\\tmh-b12c.inf",
		"char\\tmABCD\\tmh-b13c.inf"
	
	},

	//////////// 얼큰 버전 - 1 //////////
	{
		"char\\tmABCD\\tmh-b01b.inf",
		"char\\tmABCD\\tmh-b02b.inf",
		"char\\tmABCD\\tmh-b03b.inf",
		
		"char\\tmABCD\\tmh-b01b.inf",
		"char\\tmABCD\\tmh-b02b.inf",
		"char\\tmABCD\\tmh-b03b.inf",
		"char\\tmABCD\\tmh-b01b.inf",
		"char\\tmABCD\\tmh-b02b.inf",
		
		"char\\tmABCD\\tmh-b03b.inf",
		"char\\tmABCD\\tmh-b01b.inf",
		"char\\tmABCD\\tmh-b02b.inf",
		"char\\tmABCD\\tmh-b03b.inf",
		"char\\tmABCD\\tmh-b01b.inf"	

	},

	//////////// 얼큰 버전 - 2 //////////
	{
		"char\\tmABCD\\tmh-b01t.inf",
		"char\\tmABCD\\tmh-b02t.inf",
		"char\\tmABCD\\tmh-b03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-b01t.inf",
		"char\\tmABCD\\tmh-b02t.inf",
		"char\\tmABCD\\tmh-b03t.inf",
		"char\\tmABCD\\tmh-b01t.inf",
		"char\\tmABCD\\tmh-b02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-b01t.inf",
		"char\\tmABCD\\tmh-b02t.inf",
		"char\\tmABCD\\tmh-b03t.inf",
		"char\\tmABCD\\tmh-b01t.inf",
		"char\\tmABCD\\tmh-b02t.inf"	
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",

		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",

		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf",
		"char\\tmABCD\\TmhB-18t.inf"	
	}
};

char *szModel_MechFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {			//Mechanican
	{
		"char\\tmABCD\\tmh-a01.inf",
		"char\\tmABCD\\tmh-a02.inf",
		"char\\tmABCD\\tmh-a03.inf",
		"char\\tmABCD\\tmh-a04.inf",
		"char\\tmABCD\\tmh-a05.inf",
		"char\\tmABCD\\tmh-a06.inf",
		"char\\tmABCD\\tmh-a07.inf",
		"char\\tmABCD\\tmh-a08.inf",
		"char\\tmABCD\\tmh-a09.inf",
		"char\\tmABCD\\tmh-a10.inf",
		"char\\tmABCD\\tmh-a11.inf",
		"char\\tmABCD\\tmh-a12.inf",
		"char\\tmABCD\\tmh-a13.inf"
	},
	{
		"char\\tmABCD\\tmh-a01a.inf",
		"char\\tmABCD\\tmh-a02a.inf",
		"char\\tmABCD\\tmh-a03a.inf",
		"char\\tmABCD\\tmh-a04a.inf",
		"char\\tmABCD\\tmh-a05a.inf",
		"char\\tmABCD\\tmh-a06a.inf",
		"char\\tmABCD\\tmh-a07a.inf",
		"char\\tmABCD\\tmh-a08a.inf",
		"char\\tmABCD\\tmh-a09a.inf",
		"char\\tmABCD\\tmh-a10a.inf",
		"char\\tmABCD\\tmh-a11a.inf",
		"char\\tmABCD\\tmh-a12a.inf",
		"char\\tmABCD\\tmh-a13a.inf"
	},
	{
		"char\\tmABCD\\tmh_a01b.inf",
		"char\\tmABCD\\tmh_a02b.inf",
		"char\\tmABCD\\tmh_a03b.inf",
		"char\\tmABCD\\tmh_a04b.inf",
		"char\\tmABCD\\tmh_a05b.inf",
		"char\\tmABCD\\tmh_a06b.inf",
		"char\\tmABCD\\tmh_a07b.inf",
		"char\\tmABCD\\tmh_a08b.inf",
		"char\\tmABCD\\tmh_a09b.inf",
		"char\\tmABCD\\tmh_a10b.inf",
		"char\\tmABCD\\tmh_a11b.inf",
		"char\\tmABCD\\tmh_a12b.inf",
		"char\\tmABCD\\tmh_a13b.inf"
	},
	{
		"char\\tmABCD\\tmh-a01c.inf",
		"char\\tmABCD\\tmh-a02c.inf",
		"char\\tmABCD\\tmh-a03c.inf",
		"char\\tmABCD\\tmh-a04c.inf",
		"char\\tmABCD\\tmh-a05c.inf",
		"char\\tmABCD\\tmh-a06c.inf",
		"char\\tmABCD\\tmh-a07c.inf",
		"char\\tmABCD\\tmh-a08c.inf",
		"char\\tmABCD\\tmh-a09c.inf",
		"char\\tmABCD\\tmh-a10c.inf",
		"char\\tmABCD\\tmh-a11c.inf",
		"char\\tmABCD\\tmh-a12c.inf",
		"char\\tmABCD\\tmh-a13c.inf"
	},
	//////////// 얼큰 버전 //////////
	{
		"char\\tmABCD\\tmh-a01b.inf",
		"char\\tmABCD\\tmh-a02b.inf",
		"char\\tmABCD\\tmh-a03b.inf",
		
		"char\\tmABCD\\tmh-a01b.inf",
		"char\\tmABCD\\tmh-a02b.inf",
		"char\\tmABCD\\tmh-a03b.inf",
		"char\\tmABCD\\tmh-a01b.inf",
		"char\\tmABCD\\tmh-a02b.inf",
		
		"char\\tmABCD\\tmh-a03b.inf",
		"char\\tmABCD\\tmh-a01b.inf",
		"char\\tmABCD\\tmh-a02b.inf",
		"char\\tmABCD\\tmh-a03b.inf",
		"char\\tmABCD\\tmh-a01b.inf"
		
	},
	{
		"char\\tmABCD\\tmh-a01t.inf",
		"char\\tmABCD\\tmh-a02t.inf",
		"char\\tmABCD\\tmh-a03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-a01t.inf",
		"char\\tmABCD\\tmh-a02t.inf",
		"char\\tmABCD\\tmh-a03t.inf",
		"char\\tmABCD\\tmh-a01t.inf",
		"char\\tmABCD\\tmh-a02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-a01t.inf",
		"char\\tmABCD\\tmh-a02t.inf",
		"char\\tmABCD\\tmh-a03t.inf",
		"char\\tmABCD\\tmh-a01t.inf",
		"char\\tmABCD\\tmh-a02t.inf"
	},
	
	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",

		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",

		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf",
		"char\\tmABCD\\TmhA-18t.inf"	
	}
};

char *szModel_ArcherFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {		//Archer
	{	
		"char\\tmABCD\\tfh-D01.inf",
		"char\\tmABCD\\tfh-d02.inf",
		"char\\tmABCD\\tfh-d03.inf",
		"char\\tmABCD\\tfh-d04.inf",
		"char\\tmABCD\\tfh-d05.inf",
		"char\\tmABCD\\tfh-d06.inf",
		"char\\tmABCD\\tfh-d07.inf",
		"char\\tmABCD\\tfh-d08.inf",
		"char\\tmABCD\\tfh-d09.inf",
		"char\\tmABCD\\tfh-d10.inf",
		"char\\tmABCD\\tfh-d11.inf",
		"char\\tmABCD\\tfh-d12.inf",
		"char\\tmABCD\\tfh-d13.inf"
	},
	{
		"char\\tmABCD\\tfh-D01a.inf",
		"char\\tmABCD\\tfh-d02a.inf",
		"char\\tmABCD\\tfh-d03a.inf",
		"char\\tmABCD\\tfh-d04a.inf",
		"char\\tmABCD\\tfh-d05a.inf",
		"char\\tmABCD\\tfh-d06a.inf",
		"char\\tmABCD\\tfh-d07a.inf",
		"char\\tmABCD\\tfh-d08a.inf",
		"char\\tmABCD\\tfh-d09a.inf",
		"char\\tmABCD\\tfh-d10a.inf",
		"char\\tmABCD\\tfh-d11a.inf",
		"char\\tmABCD\\tfh-d12a.inf",
		"char\\tmABCD\\tfh-d13a.inf"
	},
	{
		"char\\tmABCD\\tfh_D01b.inf",
		"char\\tmABCD\\tfh_d02b.inf",
		"char\\tmABCD\\tfh_d03b.inf",
		"char\\tmABCD\\tfh_d04b.inf",
		"char\\tmABCD\\tfh_d05b.inf",
		"char\\tmABCD\\tfh_d06b.inf",
		"char\\tmABCD\\tfh_d07b.inf",
		"char\\tmABCD\\tfh_d08b.inf",
		"char\\tmABCD\\tfh_d09b.inf",
		"char\\tmABCD\\tfh_d10b.inf",
		"char\\tmABCD\\tfh_d11b.inf",
		"char\\tmABCD\\tfh_d12b.inf",
		"char\\tmABCD\\tfh_d13b.inf"
	},
	{
		"char\\tmABCD\\tfh-D01c.inf",
		"char\\tmABCD\\tfh-d02c.inf",
		"char\\tmABCD\\tfh-d03c.inf",
		"char\\tmABCD\\tfh-d04c.inf",
		"char\\tmABCD\\tfh-d05c.inf",
		"char\\tmABCD\\tfh-d06c.inf",
		"char\\tmABCD\\tfh-d07c.inf",
		"char\\tmABCD\\tfh-d08c.inf",
		"char\\tmABCD\\tfh-d09c.inf",
		"char\\tmABCD\\tfh-d10c.inf",
		"char\\tmABCD\\tfh-d11c.inf",
		"char\\tmABCD\\tfh-d12c.inf",
		"char\\tmABCD\\tfh-d13c.inf"
	},

	//////////// 얼큰 버전 //////////
	{
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf"

	},
	{
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf",
		"char\\tmABCD\\tfh-d03t.inf",
		"char\\tmABCD\\tfh-D01t.inf",
		"char\\tmABCD\\tfh-d02t.inf"
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",

		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",

		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf",
		"char\\tmABCD\\TfhD-18t.inf"	
	}
};

char *szModel_PikeFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {		//Pikeman
	{
		"char\\tmABCD\\tmh-c01.inf",		
		"char\\tmABCD\\tmh-c02.inf",		
		"char\\tmABCD\\tmh-c03.inf",		
		"char\\tmABCD\\tmh-c04.inf",		
		"char\\tmABCD\\tmh-c05.inf",		
		"char\\tmABCD\\tmh-c06.inf",		
		"char\\tmABCD\\tmh-c07.inf",		
		"char\\tmABCD\\tmh-c08.inf",
		"char\\tmABCD\\tmh-c09.inf",		
		"char\\tmABCD\\tmh-c10.inf",		
		"char\\tmABCD\\tmh-c11.inf",		
		"char\\tmABCD\\tmh-c12.inf",		
		"char\\tmABCD\\tmh-c13.inf"			

	},
	{
		"char\\tmABCD\\tmh-c01a.inf",
		"char\\tmABCD\\tmh-c02a.inf",
		"char\\tmABCD\\tmh-c03a.inf",
		"char\\tmABCD\\tmh-c04a.inf",
		"char\\tmABCD\\tmh-c05a.inf",
		"char\\tmABCD\\tmh-c06a.inf",
		"char\\tmABCD\\tmh-c07a.inf",
		"char\\tmABCD\\tmh-c08a.inf",
		"char\\tmABCD\\tmh-c09a.inf",
		"char\\tmABCD\\tmh-c10a.inf",
		"char\\tmABCD\\tmh-c11a.inf",
		"char\\tmABCD\\tmh-c12a.inf",
		"char\\tmABCD\\tmh-c13a.inf"

	},
	{
		"char\\tmABCD\\tmh_c01b.inf",
		"char\\tmABCD\\tmh_c02b.inf",
		"char\\tmABCD\\tmh_c03b.inf",
		"char\\tmABCD\\tmh_c04b.inf",
		"char\\tmABCD\\tmh_c05b.inf",
		"char\\tmABCD\\tmh_c06b.inf",
		"char\\tmABCD\\tmh_c07b.inf",
		"char\\tmABCD\\tmh_c08b.inf",
		"char\\tmABCD\\tmh_c09b.inf",
		"char\\tmABCD\\tmh_c10b.inf",
		"char\\tmABCD\\tmh_c11b.inf",
		"char\\tmABCD\\tmh_c12b.inf",
		"char\\tmABCD\\tmh_c13b.inf"
	},
/*
	{
		"char\\tmABCD\\tmh-c01c.inf",
		"char\\tmABCD\\tmh-c02c.inf",
		"char\\tmABCD\\tmh-c03c.inf"
	},
*/
	{
		"char\\tmABCD\\tmhC-01c.inf",
		"char\\tmABCD\\tmhC-02c.inf",
		"char\\tmABCD\\tmhC-03c.inf",
		"char\\tmABCD\\tmhC-04c.inf",
		"char\\tmABCD\\tmhC-05c.inf",
		"char\\tmABCD\\tmhC-06c.inf",
		"char\\tmABCD\\tmhC-07c.inf",
		"char\\tmABCD\\tmhC-08c.inf",
		"char\\tmABCD\\tmhC-09c.inf",
		"char\\tmABCD\\tmhC-10c.inf",
		"char\\tmABCD\\tmhC-11c.inf",
		"char\\tmABCD\\tmhC-12c.inf",
		"char\\tmABCD\\tmhC-13c.inf"

	},
	//////////// 얼큰 버전 //////////					
	{
		"char\\tmABCD\\tmh-c01b.inf",
		"char\\tmABCD\\tmh-c02b.inf",
		"char\\tmABCD\\tmh-c03b.inf",
		
		"char\\tmABCD\\tmh-c01b.inf",
		"char\\tmABCD\\tmh-c02b.inf",
		"char\\tmABCD\\tmh-c03b.inf",
		"char\\tmABCD\\tmh-c01b.inf",
		"char\\tmABCD\\tmh-c02b.inf",
		
		"char\\tmABCD\\tmh-c03b.inf",
		"char\\tmABCD\\tmh-c01b.inf",
		"char\\tmABCD\\tmh-c02b.inf",
		"char\\tmABCD\\tmh-c03b.inf",
		"char\\tmABCD\\tmh-c01b.inf"
	},
	{
		"char\\tmABCD\\tmh-c01t.inf",
		"char\\tmABCD\\tmh-c02t.inf",
		"char\\tmABCD\\tmh-c03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-c01t.inf",
		"char\\tmABCD\\tmh-c02t.inf",
		"char\\tmABCD\\tmh-c03t.inf",
		"char\\tmABCD\\tmh-c01t.inf",
		"char\\tmABCD\\tmh-c02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\tmh-c01t.inf",
		"char\\tmABCD\\tmh-c02t.inf",
		"char\\tmABCD\\tmh-c03t.inf",
		"char\\tmABCD\\tmh-c01t.inf",
		"char\\tmABCD\\tmh-c02t.inf"
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",

		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",

		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf",
		"char\\tmABCD\\TmhC-18t.inf"	
	}
};


char *szModel_KnightFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {	//Knight
	{
		"char\\tmABCD\\Mmh-A01.inf",
		"char\\tmABCD\\Mmh-A02.inf",
		"char\\tmABCD\\Mmh-A03.inf",
		"char\\tmABCD\\Mmh-A04.inf",
		"char\\tmABCD\\Mmh-A05.inf",
		"char\\tmABCD\\Mmh-A06.inf",
		"char\\tmABCD\\Mmh-A07.inf",
		"char\\tmABCD\\Mmh-A08.inf",
		"char\\tmABCD\\Mmh-A09.inf",
		"char\\tmABCD\\Mmh-A10.inf",
		"char\\tmABCD\\Mmh-A11.inf",
		"char\\tmABCD\\Mmh-A12.inf",
		"char\\tmABCD\\Mmh-A13.inf"
	},
	{
		"char\\tmABCD\\Mmh-A01a.inf",
		"char\\tmABCD\\Mmh-A02a.inf",
		"char\\tmABCD\\Mmh-A03a.inf",
		"char\\tmABCD\\Mmh-A04a.inf",
		"char\\tmABCD\\Mmh-A05a.inf",
		"char\\tmABCD\\Mmh-A06a.inf",
		"char\\tmABCD\\Mmh-A07a.inf",
		"char\\tmABCD\\Mmh-A08a.inf",
		"char\\tmABCD\\Mmh-A09a.inf",
		"char\\tmABCD\\Mmh-A10a.inf",
		"char\\tmABCD\\Mmh-A11a.inf",
		"char\\tmABCD\\Mmh-A12a.inf",
		"char\\tmABCD\\Mmh-A13a.inf"
	},
	{
		"char\\tmABCD\\Mmh_A01b.inf",
		"char\\tmABCD\\Mmh_A02b.inf",
		"char\\tmABCD\\Mmh_A03b.inf",
		"char\\tmABCD\\Mmh_A04b.inf",
		"char\\tmABCD\\Mmh_A05b.inf",
		"char\\tmABCD\\Mmh_A06b.inf",
		"char\\tmABCD\\Mmh_A07b.inf",
		"char\\tmABCD\\Mmh_A08b.inf",
		"char\\tmABCD\\Mmh_A09b.inf",
		"char\\tmABCD\\Mmh_A10b.inf",
		"char\\tmABCD\\Mmh_A11b.inf",
		"char\\tmABCD\\Mmh_A12b.inf",
		"char\\tmABCD\\Mmh_A13b.inf"
	},
	{
		"char\\tmABCD\\Mmh-A01c.inf",
		"char\\tmABCD\\Mmh-A02c.inf",
		"char\\tmABCD\\Mmh-A03c.inf",
		"char\\tmABCD\\Mmh-A04c.inf",
		"char\\tmABCD\\Mmh-A05c.inf",
		"char\\tmABCD\\Mmh-A06c.inf",
		"char\\tmABCD\\Mmh-A07c.inf",
		"char\\tmABCD\\Mmh-A08c.inf",

		"char\\tmABCD\\Mmh-A09c.inf",
		"char\\tmABCD\\Mmh-A10c.inf",
		"char\\tmABCD\\Mmh-A11c.inf",
		"char\\tmABCD\\Mmh-A12c.inf",
		"char\\tmABCD\\Mmh-A13c.inf"
	},
	//////////// 얼큰 버전 //////////
	{
		"char\\tmABCD\\Mmh-A01b.inf",
		"char\\tmABCD\\Mmh-A02b.inf",
		"char\\tmABCD\\Mmh-A03b.inf",
		
		"char\\tmABCD\\Mmh-A01b.inf",
		"char\\tmABCD\\Mmh-A02b.inf",
		"char\\tmABCD\\Mmh-A03b.inf",
		"char\\tmABCD\\Mmh-A01b.inf",
		"char\\tmABCD\\Mmh-A02b.inf",
		
		"char\\tmABCD\\Mmh-A03b.inf",
		"char\\tmABCD\\Mmh-A01b.inf",
		"char\\tmABCD\\Mmh-A02b.inf",
		"char\\tmABCD\\Mmh-A03b.inf",
		"char\\tmABCD\\Mmh-A01b.inf"

	},
	{
		"char\\tmABCD\\Mmh-A01t.inf",
		"char\\tmABCD\\Mmh-A02t.inf",
		"char\\tmABCD\\Mmh-A03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mmh-A01t.inf",
		"char\\tmABCD\\Mmh-A02t.inf",
		"char\\tmABCD\\Mmh-A03t.inf",
		"char\\tmABCD\\Mmh-A01t.inf",
		"char\\tmABCD\\Mmh-A02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mmh-A01t.inf",
		"char\\tmABCD\\Mmh-A02t.inf",
		"char\\tmABCD\\Mmh-A03t.inf",
		"char\\tmABCD\\Mmh-A01t.inf",
		"char\\tmABCD\\Mmh-A02t.inf"		
	},
	
	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",

		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",

		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf",
		"char\\tmABCD\\MmhA-18t.inf"	
	}
};

char *szModel_AtalantaFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {			//Atalanta
	{
		"char\\tmABCD\\Mfh-B01.inf",
		"char\\tmABCD\\Mfh-B02.inf",
		"char\\tmABCD\\Mfh-B03.inf",
		"char\\tmABCD\\Mfh-B04.inf",
		"char\\tmABCD\\Mfh-B05.inf",
		"char\\tmABCD\\Mfh-B06.inf",
		"char\\tmABCD\\Mfh-B07.inf",
		"char\\tmABCD\\Mfh-B08.inf",

		"char\\tmABCD\\Mfh-B09.inf",
		"char\\tmABCD\\Mfh-B10.inf",
		"char\\tmABCD\\Mfh-B11.inf",
		"char\\tmABCD\\Mfh-B12.inf",
		"char\\tmABCD\\Mfh-B13.inf"
	},
	{
		"char\\tmABCD\\Mfh-B01a.inf",
		"char\\tmABCD\\Mfh-B02a.inf",
		"char\\tmABCD\\Mfh-B03a.inf",
		"char\\tmABCD\\Mfh-B04a.inf",
		"char\\tmABCD\\Mfh-B05a.inf",
		"char\\tmABCD\\Mfh-B06a.inf",
		"char\\tmABCD\\Mfh-B07a.inf",
		"char\\tmABCD\\Mfh-B08a.inf",

		"char\\tmABCD\\Mfh-B09a.inf",
		"char\\tmABCD\\Mfh-B10a.inf",
		"char\\tmABCD\\Mfh-B11a.inf",
		"char\\tmABCD\\Mfh-B12a.inf",
		"char\\tmABCD\\Mfh-B13a.inf"
	},
	{
		"char\\tmABCD\\Mfh_B01b.inf",
		"char\\tmABCD\\Mfh_B02b.inf",
		"char\\tmABCD\\Mfh_B03b.inf",
		"char\\tmABCD\\Mfh_B04b.inf",
		"char\\tmABCD\\Mfh_B05b.inf",
		"char\\tmABCD\\Mfh_B06b.inf",
		"char\\tmABCD\\Mfh_B07b.inf",
		"char\\tmABCD\\Mfh_B08b.inf",

		"char\\tmABCD\\Mfh_B09b.inf",
		"char\\tmABCD\\Mfh_B10b.inf",
		"char\\tmABCD\\Mfh_B11b.inf",
		"char\\tmABCD\\Mfh_B12b.inf",
		"char\\tmABCD\\Mfh_B13b.inf"
	},
	{
		"char\\tmABCD\\Mfh-B01c.inf",
		"char\\tmABCD\\Mfh-B02c.inf",
		"char\\tmABCD\\Mfh-B03c.inf",
		"char\\tmABCD\\Mfh-B04c.inf",
		"char\\tmABCD\\Mfh-B05c.inf",
		"char\\tmABCD\\Mfh-B06c.inf",
		"char\\tmABCD\\Mfh-B07c.inf",
		"char\\tmABCD\\Mfh-B08c.inf",

		"char\\tmABCD\\Mfh-B09c.inf",
		"char\\tmABCD\\Mfh-B10c.inf",
		"char\\tmABCD\\Mfh-B11c.inf",
		"char\\tmABCD\\Mfh-B12c.inf",
		"char\\tmABCD\\Mfh-B13c.inf"
	
	},
	//////////// 얼큰 버전 //////////
	{
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf"
	},
	{
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",		
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",
		"char\\tmABCD\\Mfh-B03t.inf",
		"char\\tmABCD\\Mfh-B01t.inf",
		"char\\tmABCD\\Mfh-B02t.inf",	
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",

		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",

		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf",
		"char\\tmABCD\\MfhB-18t.inf"	
	}
};

char *szModel_PristessFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {				//Priestess
	{
		"char\\tmABCD\\Mfh-C01.inf",
		"char\\tmABCD\\Mfh-C02.inf",
		"char\\tmABCD\\Mfh-C03.inf",
		"char\\tmABCD\\Mfh-C04.inf",
		"char\\tmABCD\\Mfh-C05.inf",
		"char\\tmABCD\\Mfh-C06.inf",
		"char\\tmABCD\\Mfh-C07.inf",
		"char\\tmABCD\\Mfh-C08.inf",

		"char\\tmABCD\\Mfh-C09.inf",
		"char\\tmABCD\\Mfh-C10.inf",
		"char\\tmABCD\\Mfh-C11.inf",
		"char\\tmABCD\\Mfh-C12.inf",
		"char\\tmABCD\\Mfh-C13.inf"
	},
	{
		"char\\tmABCD\\Mfh-C01a.inf",
		"char\\tmABCD\\Mfh-C02a.inf",
		"char\\tmABCD\\Mfh-C03a.inf",
		"char\\tmABCD\\Mfh-C04a.inf",
		"char\\tmABCD\\Mfh-C05a.inf",
		"char\\tmABCD\\Mfh-C06a.inf",
		"char\\tmABCD\\Mfh-C07a.inf",
		"char\\tmABCD\\Mfh-C08a.inf",

		"char\\tmABCD\\Mfh-C09a.inf",
		"char\\tmABCD\\Mfh-C10a.inf",
		"char\\tmABCD\\Mfh-C11a.inf",
		"char\\tmABCD\\Mfh-C12a.inf",
		"char\\tmABCD\\Mfh-C13a.inf"
	},
	{
		"char\\tmABCD\\Mfh_C01b.inf",
		"char\\tmABCD\\Mfh_C02b.inf",
		"char\\tmABCD\\Mfh_C03b.inf",
		"char\\tmABCD\\Mfh_C04b.inf",
		"char\\tmABCD\\Mfh_C05b.inf",
		"char\\tmABCD\\Mfh_C06b.inf",
		"char\\tmABCD\\Mfh_C07b.inf",
		"char\\tmABCD\\Mfh_C08b.inf",

		"char\\tmABCD\\Mfh_C09b.inf",
		"char\\tmABCD\\Mfh_C10b.inf",
		"char\\tmABCD\\Mfh_C11b.inf",
		"char\\tmABCD\\Mfh_C12b.inf",
		"char\\tmABCD\\Mfh_C13b.inf"
	},
	{
		"char\\tmABCD\\Mfh-C01c.inf",
		"char\\tmABCD\\Mfh-C02c.inf",
		"char\\tmABCD\\Mfh-C03c.inf",
		"char\\tmABCD\\Mfh-C04c.inf",
		"char\\tmABCD\\Mfh-C05c.inf",
		"char\\tmABCD\\Mfh-C06c.inf",
		"char\\tmABCD\\Mfh-C07c.inf",
		"char\\tmABCD\\Mfh-C08c.inf",

		"char\\tmABCD\\Mfh-C09c.inf",
		"char\\tmABCD\\Mfh-C10c.inf",
		"char\\tmABCD\\Mfh-C11c.inf",
		"char\\tmABCD\\Mfh-C12c.inf",
		"char\\tmABCD\\Mfh-C13c.inf"

	},
	//////////// 얼큰 버전 //////////
	{
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf"
		
	},
	{
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf",
		"char\\tmABCD\\Mfh-C03t.inf",
		"char\\tmABCD\\Mfh-C01t.inf",
		"char\\tmABCD\\Mfh-C02t.inf"
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",

		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",

		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf",
		"char\\tmABCD\\MfhC-18t.inf"	
	}	
};

char *szModel_MagicanFaceName[FACE_MODEL_MAX][HEAREPOTION_MAX] = {			//Magican
	{	
		"char\\tmABCD\\Mmh-D01.inf",
		"char\\tmABCD\\Mmh-D02.inf",
		"char\\tmABCD\\Mmh-D03.inf",
		"char\\tmABCD\\Mmh-D04.inf",
		"char\\tmABCD\\Mmh-D05.inf",
		"char\\tmABCD\\Mmh-D06.inf",
		"char\\tmABCD\\Mmh-D07.inf",
		"char\\tmABCD\\Mmh-D08.inf",

		"char\\tmABCD\\Mmh-D09.inf",
		"char\\tmABCD\\Mmh-D10.inf",
		"char\\tmABCD\\Mmh-D11.inf",
		"char\\tmABCD\\Mmh-D12.inf",
		"char\\tmABCD\\Mmh-D13.inf"
	},
	{
		"char\\tmABCD\\Mmh-D01a.inf",
		"char\\tmABCD\\Mmh-D02a.inf",
		"char\\tmABCD\\Mmh-D03a.inf",
		"char\\tmABCD\\Mmh-D04a.inf",
		"char\\tmABCD\\Mmh-D05a.inf",
		"char\\tmABCD\\Mmh-D06a.inf",
		"char\\tmABCD\\Mmh-D07a.inf",
		"char\\tmABCD\\Mmh-D08a.inf",

		"char\\tmABCD\\Mmh-D09a.inf",
		"char\\tmABCD\\Mmh-D10a.inf",
		"char\\tmABCD\\Mmh-D11a.inf",
		"char\\tmABCD\\Mmh-D12a.inf",
		"char\\tmABCD\\Mmh-D13a.inf"
	},
	{
		"char\\tmABCD\\Mmh_D01b.inf",
		"char\\tmABCD\\Mmh_D02b.inf",
		"char\\tmABCD\\Mmh_D03b.inf",
		"char\\tmABCD\\Mmh_D04b.inf",
		"char\\tmABCD\\Mmh_D05b.inf",
		"char\\tmABCD\\Mmh_D06b.inf",
		"char\\tmABCD\\Mmh_D07b.inf",
		"char\\tmABCD\\Mmh_D08b.inf",

		"char\\tmABCD\\Mmh_D09b.inf",
		"char\\tmABCD\\Mmh_D10b.inf",
		"char\\tmABCD\\Mmh_D11b.inf",
		"char\\tmABCD\\Mmh_D12b.inf",
		"char\\tmABCD\\Mmh_D13b.inf"
	},
	{
		"char\\tmABCD\\Mmh-D01c.inf",
		"char\\tmABCD\\Mmh-D02c.inf",
		"char\\tmABCD\\Mmh-D03c.inf",
		"char\\tmABCD\\Mmh-D04c.inf",
		"char\\tmABCD\\Mmh-D05c.inf",
		"char\\tmABCD\\Mmh-D06c.inf",
		"char\\tmABCD\\Mmh-D07c.inf",
		"char\\tmABCD\\Mmh-D08c.inf",

		"char\\tmABCD\\Mmh-D09c.inf",
		"char\\tmABCD\\Mmh-D10c.inf",
		"char\\tmABCD\\Mmh-D11c.inf",
		"char\\tmABCD\\Mmh-D12c.inf",
		"char\\tmABCD\\Mmh-D13c.inf"
	},
	//////////// 얼큰 버전 //////////
	{	
		"char\\tmABCD\\Mmh-D01b.inf",
		"char\\tmABCD\\Mmh-D02b.inf",
		"char\\tmABCD\\Mmh-D03b.inf",
		
		"char\\tmABCD\\Mmh-D01b.inf",
		"char\\tmABCD\\Mmh-D02b.inf",
		"char\\tmABCD\\Mmh-D03b.inf",
		"char\\tmABCD\\Mmh-D01b.inf",
		"char\\tmABCD\\Mmh-D02b.inf",
		
		"char\\tmABCD\\Mmh-D03b.inf",
		"char\\tmABCD\\Mmh-D01b.inf",
		"char\\tmABCD\\Mmh-D02b.inf",
		"char\\tmABCD\\Mmh-D03b.inf",
		"char\\tmABCD\\Mmh-D01b.inf"

	},
	{
		"char\\tmABCD\\Mmh-D01t.inf",
		"char\\tmABCD\\Mmh-D02t.inf",
		"char\\tmABCD\\Mmh-D03t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mmh-D01t.inf",
		"char\\tmABCD\\Mmh-D02t.inf",
		"char\\tmABCD\\Mmh-D03t.inf",
		"char\\tmABCD\\Mmh-D01t.inf",
		"char\\tmABCD\\Mmh-D02t.inf",
		//헤어틴트포션때문에 가데이터로 채워 넣는다.. 얼큰 버젼 사용시 바꿔줘야함.	
		"char\\tmABCD\\Mmh-D01t.inf",
		"char\\tmABCD\\Mmh-D02t.inf",
		"char\\tmABCD\\Mmh-D03t.inf",
		"char\\tmABCD\\Mmh-D01t.inf",
		"char\\tmABCD\\Mmh-D02t.inf"
	},

	// 박재원 - 2010 월드컵 이벤트 - 축구공 포션 추가(축구공 모델 이미지 추가 - 머리)
	{
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",

		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",

		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf",
		"char\\tmABCD\\MmhD-18t.inf"	
	}
};

#define	ARMOR_FILE_MAX		54

//Plain clothes models list
char *szArmorNumFile[MAX_JOBNUM][ARMOR_FILE_MAX] = {
	{ "A001.ini" , "A001.ini",  "A002.ini",  "A003.ini",  "A004.ini",  "A005.ini",  "A006.ini",  "A007.ini", "A008.ini", "A009.ini", "A010.ini", 
	  "A011.ini" , "A012.ini",  "A013.ini",  "A014.ini",  "A015.ini",  "A016.ini",  "A017.ini",  "A018.ini", "A019.ini", "A020.ini", "A021.ini",  
	  "A001.ini" , "A022.ini",  "A023.ini",  "A024.ini",  "A001.ini",  "A001.ini",  "A001.ini",  "A001.ini",
	  "Ca001.ini", "Ca001.ini", "Ca001.ini", "Ca001.ini", "Ca002.ini", "Ca002.ini", "Ca002.ini", "Ca002.ini",
	  "Ca003.ini", "Ca003.ini", "Ca003.ini", "Ca003.ini", "Ca004.ini", "Ca004.ini", "Ca004.ini", "Ca004.ini",
	  "Ca005.ini", "Ca006.ini", "Ca007.ini", "Ca008.ini", "Ca009.ini", "Ca010.ini", "Ca011.ini", "Ca012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추
	},

	{ "B001.ini" , "B001.ini",  "B002.ini",  "B003.ini",  "B004.ini" , "B005.ini",  "B006.ini",  "B007.ini", "B008.ini", "B009.ini", "B010.ini" , 
	  "B011.ini" , "B012.ini",  "B013.ini",  "B014.ini",  "B015.ini" , "B016.ini",  "B017.ini",  "B018.ini", "B019.ini", "B020.ini", "B021.ini" ,
	  "B001.ini" , "B022.ini" , "B023.ini",  "B024.ini",  "B001.ini",  "B001.ini" , "B001.ini" , "B001.ini",
	  "Cb001.ini", "Cb001.ini", "Cb001.ini", "Cb001.ini", "Cb002.ini", "Cb002.ini", "Cb002.ini", "Cb002.ini",	
	  "Cb003.ini", "Cb003.ini", "Cb003.ini", "Cb003.ini", "Cb004.ini", "Cb004.ini", "Cb004.ini", "Cb004.ini",
	  "Cb005.ini", "Cb006.ini", "Cb007.ini", "Cb008.ini", "Cb009.ini", "Cb010.ini", "Cb011.ini", "Cb012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "C001.ini" , "C001.ini",  "C002.ini",  "C003.ini",  "C004.ini",  "C005.ini",  "C006.ini",  "C007.ini",  "C008.ini", "C009.ini", "C010.ini",
	  "C011.ini" , "C012.ini",  "C013.ini",  "C014.ini",  "C015.ini",  "C016.ini",  "C017.ini",  "C018.ini",  "C019.ini", "C020.ini", "C021.ini",
	  "C001.ini" , "C022.ini",  "C023.ini",  "C024.ini",  "C001.ini",  "C001.ini",  "C001.ini",  "C001.ini",
	  "Cc001.ini", "Cc001.ini", "Cc001.ini", "Cc001.ini", "Cc002.ini", "Cc002.ini", "Cc002.ini", "Cc002.ini",
	  "Cc003.ini", "Cc003.ini", "Cc003.ini", "Cc003.ini", "Cc004.ini", "Cc004.ini", "Cc004.ini", "Cc004.ini",
	  "Cc005.ini", "Cc006.ini", "Cc007.ini", "Cc008.ini", "Cc009.ini", "Cc010.ini", "Cc011.ini", "Cc012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "D001.ini" , "D001.ini",  "D002.ini",  "D003.ini",  "D004.ini",  "D005.ini",  "D006.ini",  "D007.ini", "D008.ini", "D009.ini", "D010.ini", 
	  "D011.ini" , "D012.ini",  "D013.ini",  "D014.ini",  "D015.ini",  "D016.ini",  "D017.ini",  "D018.ini", "D019.ini", "D020.ini", "D021.ini",
	  "D001.ini" , "D022.ini",  "D023.ini",  "D024.ini",  "D001.ini",  "D001.ini",  "D001.ini",  "D001.ini",
	  "Cd001.ini", "Cd001.ini", "Cd001.ini", "Cd001.ini", "Cd002.ini", "Cd002.ini", "Cd002.ini", "Cd002.ini",
	  "Cd003.ini", "Cd003.ini", "Cd003.ini", "Cd003.ini", "Cd004.ini", "Cd004.ini", "Cd004.ini", "Cd004.ini",
	  "Cd005.ini", "Cd006.ini", "Cd007.ini", "Cd008.ini", "Cd009.ini", "Cd010.ini", "Cd011.ini", "Cd012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mA001.ini",  "mA001.ini",  "mA002.ini",  "mA003.ini",   "mA004.ini",  "mA005.ini",  "mA006.ini",  "mA007.ini", "mA008.ini", "mA009.ini", "mA010.ini", 
	  "mA011.ini",  "mA012.ini",  "mA013.ini",  "mA014.ini",   "mA015.ini",  "mA016.ini",  "mA017.ini",  "mA018.ini", "mA019.ini", "mA020.ini", "mA021.ini",
	  "mA001.ini",  "mA022.ini",  "mA023.ini",  "mA024.ini",  "mA001.ini",   "mA001.ini",  "mA001.ini",  "mA001.ini",
	  "Cma001.ini", "Cma001.ini", "Cma001.ini", "Cma001.ini",  "Cma002.ini", "Cma002.ini", "Cma002.ini", "Cma002.ini",
	  "Cma003.ini", "Cma003.ini", "Cma003.ini", "Cma003.ini",  "Cma004.ini", "Cma004.ini", "Cma004.ini", "Cma004.ini",
	  "Cma005.ini", "Cma006.ini", "Cma007.ini", "Cma008.ini", "Cma009.ini", "Cma010.ini", "Cma011.ini", "Cma012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},
	
	{ "mB001.ini",  "mB001.ini",  "mB002.ini",  "mB003.ini",  "mB004.ini",  "mB005.ini",  "mB006.ini",  "mB007.ini", "mB008.ini", "mB009.ini", "mB010.ini", 
	  "mB011.ini",  "mB012.ini",  "mB013.ini",  "mB014.ini",  "mB015.ini",  "mB016.ini",  "mB017.ini",  "mB018.ini", "mB019.ini", "mB020.ini", "mB021.ini",
	  "mB001.ini",  "mB022.ini",  "mB023.ini",  "mB024.ini" , "mB001.ini",  "mB001.ini",  "mB001.ini" , "mB001.ini" ,
	  "Cmb001.ini", "Cmb001.ini", "Cmb001.ini", "Cmb001.ini", "Cmb002.ini", "Cmb002.ini", "Cmb002.ini", "Cmb002.ini",	
	  "Cmb003.ini", "Cmb003.ini", "Cmb003.ini", "Cmb003.ini", "Cmb004.ini", "Cmb004.ini", "Cmb004.ini", "Cmb004.ini",
	  "Cmb005.ini", "Cmb006.ini", "Cmb007.ini", "Cmb008.ini", "Cmb009.ini", "Cmb010.ini", "Cmb011.ini", "Cmb012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mC001.ini",  "mC001.ini",  "mC002.ini",  "mC003.ini",  "mC004.ini",  "mC005.ini",  "mC006.ini",  "mC007.ini", "mC008.ini", "mC009.ini", "mC010.ini", 
	  "mC011.ini",  "mC012.ini",  "mC013.ini",  "mC014.ini",  "mC015.ini",  "mC016.ini",  "mC017.ini",  "mC018.ini", "mC019.ini", "mC020.ini", "mC021.ini",
	  "mC001.ini",  "mC022.ini",  "mC023.ini",  "mC024.ini",  "mC001.ini",  "mC001.ini",  "mC001.ini",  "mC001.ini",
	  "Cmc001.ini", "Cmc001.ini", "Cmc001.ini", "Cmc001.ini", "Cmc002.ini", "Cmc002.ini", "Cmc002.ini", "Cmc002.ini",
	  "Cmc003.ini", "Cmc003.ini", "Cmc003.ini", "Cmc003.ini", "Cmc004.ini", "Cmc004.ini", "Cmc004.ini", "Cmc004.ini",
	  "Cmc005.ini", "Cmc006.ini", "Cmc007.ini", "Cmc008.ini", "Cmc009.ini", "Cmc010.ini", "Cmc011.ini", "Cmc012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mD001.ini",  "mD001.ini",  "mD002.ini",  "mD003.ini",  "mD004.ini",  "mD005.ini",  "mD006.ini",  "mD007.ini", "mD008.ini", "mD009.ini", "mD010.ini",
	  "mD011.ini",  "mD012.ini",  "mD013.ini",  "mD014.ini",  "mD015.ini",  "mD016.ini",  "mD017.ini",  "mD018.ini", "mD019.ini", "mD020.ini", "mD021.ini",
	  "mD001.ini",  "mD022.ini",  "mD023.ini",  "mD024.ini",  "mD001.ini",  "mD001.ini",  "mD001.ini",  "mD001.ini",
	  "Cmd001.ini", "Cmd001.ini", "Cmd001.ini", "Cmd001.ini", "Cmd002.ini", "Cmd002.ini", "Cmd002.ini", "Cmd002.ini",
	  "Cmd003.ini", "Cmd003.ini", "Cmd003.ini", "Cmd003.ini", "Cmd004.ini", "Cmd004.ini", "Cmd004.ini", "Cmd004.ini",
	  "Cmd005.ini", "Cmd006.ini", "Cmd007.ini", "Cmd008.ini", "Cmd009.ini", "Cmd010.ini", "Cmd011.ini", "Cmd012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},
};

//Comics clothes models list
char *szArmorNumFile_Comic[MAX_JOBNUM][ARMOR_FILE_MAX] = {
	{ "A001.ini" , "A001.ini",  "A002.ini",  "A003.ini",  "A004.ini",  "A005.ini",  "A006.ini",  "A007.ini", "A008.ini", "A009.ini", "A010.ini", 
	  "A011.ini" , "A012.ini",  "A013.ini",  "A014.ini",  "A015.ini",  "A016.ini",  "A017.ini",  "A018.ini", "A019.ini", "A020.ini", "A021.ini",  
	  "A001.ini" , "A022.ini",  "A023.ini",  "A024.ini",  "A001.ini",  "A001.ini",  "A001.ini",  "A001.ini",
	  "Ca001.ini", "Ca001.ini", "Ca001.ini", "Ca001.ini", "Ca002.ini", "Ca002.ini", "Ca002.ini", "Ca002.ini",
	  "Ca003.ini", "Ca003.ini", "Ca003.ini", "Ca003.ini", "Ca004.ini", "Ca004.ini", "Ca004.ini", "Ca004.ini",
	  "Ca005.ini", "Ca006.ini", "Ca007.ini", "Ca008.ini", "Ca009.ini", "Ca010.ini", "Ca011.ini", "Ca012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "B001.ini" , "B001.ini",  "B002.ini",  "B003.ini",  "B004.ini" , "B005.ini",  "B006.ini",  "B007.ini", "B008.ini", "B009.ini", "B010.ini" , 
	  "B011.ini" , "B012.ini",  "B013.ini",  "B014.ini",  "B015.ini" , "B016.ini",  "B017.ini",  "B018.ini", "B019.ini", "B020.ini", "B021.ini" ,
	  "B001.ini" , "B022.ini",  "B023.ini",  "B024.ini",  "B001.ini",  "B001.ini" , "B001.ini" , "B001.ini",
	  "Cb001.ini", "Cb001.ini", "Cb001.ini", "Cb001.ini", "Cb002.ini", "Cb002.ini", "Cb002.ini", "Cb002.ini",	
	  "Cb003.ini", "Cb003.ini", "Cb003.ini", "Cb003.ini", "Cb004.ini", "Cb004.ini", "Cb004.ini", "Cb004.ini",
	  "Cb005.ini", "Cb006.ini", "Cb007.ini", "Cb008.ini", "Cb009.ini", "Cb010.ini", "Cb011.ini", "Cb012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},
	
	{ "C001.ini" , "C001.ini",  "C002.ini",  "C003.ini",  "C004.ini",  "C005.ini",  "C006.ini",  "C007.ini",  "C008.ini", "C009.ini", "C010.ini",
	  "C011.ini" , "C012.ini",  "C013.ini",  "C014.ini",  "C015.ini",  "C016.ini",  "C017.ini",  "C018.ini",  "C019.ini", "C020.ini", "C021.ini",
	  "C001.ini" , "C022.ini",  "C023.ini",  "C024.ini",  "C001.ini",  "C001.ini",  "C001.ini",  "C001.ini",
	  "Cc001.ini", "Cc001.ini", "Cc001.ini", "Cc001.ini", "Cc002.ini", "Cc002.ini", "Cc002.ini", "Cc002.ini",
	  "Cc003.ini", "Cc003.ini", "Cc003.ini", "Cc003.ini", "Cc004.ini", "Cc004.ini", "Cc004.ini", "Cc004.ini",
	  "Cc005.ini", "Cc006.ini", "Cc007.ini", "Cc008.ini", "Cc009.ini", "Cc010.ini", "Cc011.ini", "Cc012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "D001.ini" , "D001.ini",  "D002.ini",  "D003.ini",  "D004.ini",  "D005.ini",  "D006.ini",  "D007.ini", "D008.ini", "D009.ini", "D010.ini", 
	  "D011.ini" , "D012.ini",  "D013.ini",  "D014.ini",  "D015.ini",  "D016.ini",  "D017.ini",  "D018.ini", "D019.ini", "D020.ini", "D021.ini",
	  "D001.ini" , "D022.ini",  "D023.ini",  "D024.ini",  "D001.ini",  "D001.ini",  "D001.ini",  "D001.ini",
	  "Cd001.ini", "Cd001.ini", "Cd001.ini", "Cd001.ini", "Cd002.ini", "Cd002.ini", "Cd002.ini", "Cd002.ini",
	  "Cd003.ini", "Cd003.ini", "Cd003.ini", "Cd003.ini", "Cd004.ini", "Cd004.ini", "Cd004.ini", "Cd004.ini",
	  "Cd005.ini", "Cd006.ini", "Cd007.ini", "Cd008.ini", "Cd009.ini", "Cd010.ini", "Cd011.ini", "Cd012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mA001.ini",  "mA001.ini",  "mA002.ini",  "mA003.ini",   "mA004.ini",  "mA005.ini",  "mA006.ini",  "mA007.ini", "mA008.ini", "mA009.ini", "mA010.ini", 
	  "mA011.ini",  "mA012.ini",  "mA013.ini",  "mA014.ini",   "mA015.ini",  "mA016.ini",  "mA017.ini",  "mA018.ini", "mA019.ini", "mA020.ini", "mA021.ini",
	  "mA001.ini",  "mA022.ini",  "mA023.ini",  "mA024.ini",  "mA001.ini",   "mA001.ini",  "mA001.ini",  "mA001.ini",
	  "Cma001.ini", "Cma001.ini", "Cma001.ini", "Cma001.ini",  "Cma002.ini", "Cma002.ini", "Cma002.ini", "Cma002.ini",
	  "Cma003.ini", "Cma003.ini", "Cma003.ini", "Cma003.ini",  "Cma004.ini", "Cma004.ini", "Cma004.ini", "Cma004.ini",
	  "Cma005.ini", "Cma006.ini", "Cma007.ini", "Cma008.ini",  "Cma009.ini",  "Cma010.ini", "Cma011.ini", "Cma012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},
	
	{ "mB001.ini",  "mB001.ini",  "mB002.ini",  "mB003.ini",  "mB004.ini",  "mB005.ini",  "mB006.ini",  "mB007.ini", "mB008.ini", "mB009.ini", "mB010.ini", 
	  "mB011.ini",  "mB012.ini",  "mB013.ini",  "mB014.ini",  "mB015.ini",  "mB016.ini",  "mB017.ini",  "mB018.ini", "mB019.ini", "mB020.ini", "mB021.ini",
	  "mB001.ini",  "mB022.ini",  "mB023.ini",  "mB024.ini" , "mB001.ini",  "mB001.ini",  "mB001.ini" , "mB001.ini" ,
	  "Cmb001.ini", "Cmb001.ini", "Cmb001.ini", "Cmb001.ini", "Cmb002.ini", "Cmb002.ini", "Cmb002.ini", "Cmb002.ini",	
	  "Cmb003.ini", "Cmb003.ini", "Cmb003.ini", "Cmb003.ini", "Cmb004.ini", "Cmb004.ini", "Cmb004.ini", "Cmb004.ini",
	  "Cmb005.ini", "Cmb006.ini", "Cmb007.ini", "Cmb008.ini", "Cmb009.ini", "Cmb010.ini", "Cmb011.ini", "Cmb012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mC001.ini",  "mC001.ini",  "mC002.ini",  "mC003.ini",  "mC004.ini",  "mC005.ini",  "mC006.ini",  "mC007.ini", "mC008.ini", "mC009.ini", "mC010.ini", 
	  "mC011.ini",  "mC012.ini",  "mC013.ini",  "mC014.ini",  "mC015.ini",  "mC016.ini",  "mC017.ini",  "mC018.ini", "mC019.ini", "mC020.ini", "mC021.ini",
	  "mC001.ini",  "mC022.ini",  "mC023.ini",  "mC024.ini",  "mC001.ini",  "mC001.ini",  "mC001.ini",  "mC001.ini",
	  "Cmc001.ini", "Cmc001.ini", "Cmc001.ini", "Cmc001.ini", "Cmc002.ini", "Cmc002.ini", "Cmc002.ini", "Cmc002.ini",
	  "Cmc003.ini", "Cmc003.ini", "Cmc003.ini", "Cmc003.ini", "Cmc004.ini", "Cmc004.ini", "Cmc004.ini", "Cmc004.ini",
	  "Cmc005.ini", "Cmc006.ini", "Cmc007.ini", "Cmc008.ini", "Cmc009.ini", "Cmc010.ini", "Cmc011.ini", "Cmc012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},

	{ "mD001.ini",  "mD001.ini",  "mD002.ini",  "mD003.ini",  "mD004.ini",  "mD005.ini",  "mD006.ini",  "mD007.ini", "mD008.ini", "mD009.ini", "mD010.ini",
	  "mD011.ini",  "mD012.ini",  "mD013.ini",  "mD014.ini",  "mD015.ini",  "mD016.ini",  "mD017.ini",  "mD018.ini", "mD019.ini", "mD020.ini", "mD021.ini",
	  "mD001.ini",  "mD022.ini",  "mD023.ini",  "mD024.ini",  "mD001.ini",  "mD001.ini",  "mD001.ini",  "mD001.ini",
	  "Cmd001.ini", "Cmd001.ini", "Cmd001.ini", "Cmd001.ini", "Cmd002.ini", "Cmd002.ini", "Cmd002.ini", "Cmd002.ini",
	  "Cmd003.ini", "Cmd003.ini", "Cmd003.ini", "Cmd003.ini", "Cmd004.ini", "Cmd004.ini", "Cmd004.ini", "Cmd004.ini",
	  "Cmd005.ini", "Cmd006.ini", "Cmd007.ini", "Cmd008.ini", "Cmd009.ini", "Cmd010.ini", "Cmd011.ini", "Cmd012.ini" // 박재원 - 2010 월드컵 이벤트(축구복 추가), 수영복 추가
	},
};



