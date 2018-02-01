//######################################################################################
//작 성 일 : 2004-05-08 오후 1:21:51
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#include "smlib3d\\smd3d.h"
#include "TextMessage.h"		//문자 메세지 헤더
#include "FullZoomMap.h"
#include "FontImage.h"
#include "BellatraFontEffect.h"
#include "drawsub.h"


//
const float fANGLE_1 = float(ANGLE_360) / 360;
inline int smToDegree( float degree )
{
	return (int(degree * fANGLE_1) & ANGCLIP);
}


//
static char	*s_lpBL_DDS_ImageNameList[ DMAX_BELLATRA_DDS_IMAGELIST ] = 
{
	"BL_loding.bmp",			// 0
	"BL_loding_00.bmp",			// 1
	"BL_loding_01.bmp",			// 2
	"BL_loding_02.bmp",			// 3
	"BL_loding_03.bmp",			// 4
	"BL_loding_04.bmp",			// 5
	"F_change01.bmp",			// 6
	"F_change02.bmp",			// 7
	"F_change03.bmp",			// 8
};

static char	*s_lpBL_TEX_ImageNameList[ DMAX_BELLATRA_TEX_IMAGELIST ] = 
{
	"T_Round_316_65.tga",		// 0
	"T_1_37_64.tga",			// 1
	"T_2_54_64.tga",			// 2
	"T_3_53_64.tga",			// 3
	"T_4_56_64.tga",			// 4
	"T_5_55_64.tga",			// 5
	"T_6_55_64.tga",			// 6
	"T_7_51_64.tga",			// 7
	"T_Start_278_65.tga",		// 8
	"T_S-Stage_280_65.tga",		// 9
	"T_S-complete_440_65.tga",	// 10
	"T_S-fail_180_65.tga",		// 11
	"T_Con_754_65.tga",			// 12
	"T_8_56_64.tga",			// 13
	"effect_item01.tga",		// 14
	"effect_item02.tga",		// 15a
	"effect_item03.tga",		// 16
	"effect_item04.tga",		// 17
	"effect_item05.tga",		// 18
	"effect_item06.tga",		// 19
	"effect_item07.tga",		// 20
};


//
struct  SBL_EventScoreInfo
{
	POINT TextMarkPos;
	POINT TextNamePos;
	RECT  rcRect;
};

//
static SBL_EventScoreInfo		 s_EventScoreTextInfo[2] = 
{
	{
		{460, 164},
		{490, 170},
		{580, 170, 680, 200},
	},

	{
		{460, 194},
		{490, 200},
		{580, 200, 680, 230},
	},
};


//
extern float						g_fWinSizeRatio_X;
extern float						g_fWinSizeRatio_Y;

//
static int							s_IsBellatraFontEffect;
static HFONT						s_EventScore_Font;

static DIRECTDRAWSURFACE		    s_BL_lpDDSurfaceBuff[ DMAX_BELLATRA_DDS_IMAGELIST ];
static smMATERIAL_GROUP				s_BL_ImageMatGroup( DMAX_BELLATRA_TEX_IMAGELIST );

static SBL_MinFontEffectInfo		s_BL_MinFontEffectInfoBuff[ DMAX_BL_MIN_EFFECT_INFO ];
static SBL_FontEffectInfo			s_BL_FontEffectInfoBuff[ DMAX_BL_EFFECT_INFO ];
static SBL_SetFontEffect			s_IsSetFontEffectBuff[ DMAX_BL_EFFECT_INFO ];

static SBL_MinFontEffect			s_BL_MinFontEffectBuff_1[ DMAX_BL_MIN_EFFECT ];
static SBL_MinFontEffect			s_BL_MinFontEffectBuff_2[ DMAX_BL_MIN_EFFECT ];
static SBL_MinFontEffect			s_BL_MinFontEffectBuff_3[ DMAX_BL_MIN_EFFECT ];
static SBL_MinFontEffect		   *s_lpBL_MinFontEffectPtrBuff[ E_BL_PRIORITY_3+1 ] =
{
	s_BL_MinFontEffectBuff_1, s_BL_MinFontEffectBuff_2, s_BL_MinFontEffectBuff_3,
};

//
SBL_EventScore						g_EventScore;

//
extern int psDrawTexImage2( smTEXTUREHANDLE *hTexHandle , float *x, float *y, float fx, float fy, float fw, float fh, int Transp , int specular);
extern int psSetDefaultRenderState();


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:41:57
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
static void DrawEventScore(void)
{
	if( g_EventScore.TeamNum <= 0 )
		return;

	int iTextPos = 0;
	switch( g_EventScore.TeamNum )
	{
	case 4:
	case 3:
		iTextPos = 0;
		break;

	case 2:
	case 1:
		iTextPos = 1;
		break;
	}

	//
	HDC hdc = NULL;
	renderDevice.lpDDSBack->GetDC( &hdc );
	if( hdc == NULL )
		return;

	SelectObject( hdc, s_EventScore_Font );
	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,246,196) );

	//
	char *lpName = NULL;
	int   yPos   = 0;
	RECT  rcRect;
	for( int i=0; i < g_EventScore.TeamNum; i++ )
	{
		//
		DrawSpecialFontImage( g_EventScore.TeamMarkBuff[i],
							  int( s_EventScoreTextInfo[ iTextPos ].TextMarkPos.x * g_fWinSizeRatio_X ),
							  int( (s_EventScoreTextInfo[ iTextPos ].TextMarkPos.y + yPos) * g_fWinSizeRatio_Y ),
							  RGBA_MAKE(255,255,255,255) ); //, g_fWinSizeRatio_X );

		//
		lpName = g_lpBellatraTeamNameText[ g_EventScore.TeamMarkBuff[i] ];
		dsTextLineOut( hdc,
			     int( s_EventScoreTextInfo[ iTextPos ].TextNamePos.x * g_fWinSizeRatio_X ),
                 int( (s_EventScoreTextInfo[ iTextPos ].TextNamePos.y + yPos) * g_fWinSizeRatio_Y ),
				 lpName, lstrlen(lpName) );

		//
		lpName = g_EventScore.szTeamPointBuff[i];
		::CopyMemory( &rcRect, &s_EventScoreTextInfo[ iTextPos ].rcRect, sizeof(rcRect) );
		rcRect.left   = int( rcRect.left  * g_fWinSizeRatio_X );
		rcRect.right  = int( rcRect.right * g_fWinSizeRatio_X );
		rcRect.top    = int( (rcRect.top + yPos)    * g_fWinSizeRatio_Y );
		rcRect.bottom = int( (rcRect.bottom + yPos) * g_fWinSizeRatio_Y );
        DrawText( hdc, lpName, lstrlen(lpName), &rcRect, DT_RIGHT );

		//
		yPos += 30;
	}

	//
	if( g_EventScore.EntryTeamNum > 0 )
	{
		char szBuff[64] = {0,};
		char *lpName_1, *lpName_2;
		if( g_EventScore.EntryTeamNum == 1 )
		{
			lpName_1 = g_lpBellatraTeamNameText[ g_EventScore.EntryTeamMarkBuff[0] ];
			::sprintf( szBuff, g_lpBellatraResult_Text1, lpName_1 );
		}
		else // if( g_EventScore.EntryTeamNum == 2 )
		{
			lpName_1 = g_lpBellatraTeamNameText[ g_EventScore.EntryTeamMarkBuff[0] ];
			lpName_2 = g_lpBellatraTeamNameText[ g_EventScore.EntryTeamMarkBuff[1] ];
			::sprintf( szBuff, g_lpBellatraResult_Text2, lpName_1, lpName_2 );
		}
		
		SetTextColor( hdc, RGB(255,216,0) );
		dsTextLineOut( hdc, int(490 * g_fWinSizeRatio_X), int(320 * g_fWinSizeRatio_Y), szBuff, lstrlen(szBuff) );
		dsTextLineOut( hdc, int(490 * g_fWinSizeRatio_X), int(350 * g_fWinSizeRatio_Y), g_lpBellatraResult_Text3, lstrlen(g_lpBellatraResult_Text3) );
		dsTextLineOut( hdc, int(490 * g_fWinSizeRatio_X), int(380 * g_fWinSizeRatio_Y), g_lpBellatraResult_Text4, lstrlen(g_lpBellatraResult_Text4) );
	}

	//
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:22:07
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
void CreateBellatraFontEffect(void)
{
	if( s_IsBellatraFontEffect > 0 )
		return;

	///////////////////////////////////////////////////////////////////////
	//
	FILE *fp = fopen( "image\\Bellatra\\Bellatra.dat", "rb" );
	if( fp )
	{
		fread( &s_BL_MinFontEffectInfoBuff, sizeof(s_BL_MinFontEffectInfoBuff), 1, fp );
		fread( &s_BL_FontEffectInfoBuff, sizeof(s_BL_FontEffectInfoBuff), 1, fp );
		fclose(fp);
	}
	else
		return;
	
	///////////////////////////////////////////////////////////////////////
	//
	char szFullName[128];
	char szDirectory[32];
	::lstrcpy( szDirectory, "image\\Bellatra\\" );

	int i;

	//
	for( i=0; i< DMAX_BELLATRA_DDS_IMAGELIST; i++ )
	{
		::CopyMemory( szFullName, szDirectory, 32 );
		::lstrcat( szFullName, s_lpBL_DDS_ImageNameList[ i ] );

		s_BL_lpDDSurfaceBuff[i] = LoadDibSurfaceOffscreen( szFullName );
	}

	//
	for( i=0; i< DMAX_BELLATRA_TEX_IMAGELIST; i++ )
	{
		::CopyMemory( szFullName, szDirectory, 32 );
		::lstrcat( szFullName, s_lpBL_TEX_ImageNameList[ i ] );

		s_BL_ImageMatGroup.CreateTextureMaterial( szFullName, NULL, 0, 0, 0, SMMAT_BLEND_ALPHA );
	}

	s_BL_ImageMatGroup.ReadTextures();

	///////////////////////////////////////////////////////////////////////
	//
#ifdef _LANGUAGE_KOREAN
	s_EventScore_Font = ::CreateFont( 12, 0, 0, 0, 1000, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "굴림체" );
#endif

	///////////////////////////////////////////////////////////////////////
#ifdef _LANGUAGE_ENGLISH
	s_EventScore_Font = ::CreateFont( 16,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,"Comic Sans MS" );	
#endif
#ifdef _LANGUAGE_TAIWAN
	s_EventScore_Font = ::CreateFont( 12,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,CHINESEBIG5_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,"MingLiu" );
#endif
#ifdef _LANGUAGE_JAPANESE
#include "Japanese\\j_font.h"
	s_EventScore_Font = ::CreateFont( 12,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH | FF_MODERN,j_font );
#endif
#ifdef _LANGUAGE_CHINESE
	s_EventScore_Font = ::CreateFont( 12,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,"SimSun" );
#endif
#ifdef _LANGUAGE_THAI
	s_EventScore_Font = ::CreateFont(13,0,0,0,FW_THIN,FALSE,FALSE,FALSE,THAI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
#endif
#ifdef _LANGUAGE_BRAZIL
	s_EventScore_Font = ::CreateFont(16,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET|FS_LATIN1,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Comic Sans MS");
#endif
#ifdef _LANGUAGE_ARGENTINA //임시로 브라질과 폰트 동일하게 설정
	s_EventScore_Font = ::CreateFont(16,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET|FS_LATIN1,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Comic Sans MS");
#endif
#ifdef _LANGUAGE_VEITNAM
	s_EventScore_Font = ::CreateFont( 14,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,VIETNAMESE_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,"Tahoma" );
#endif
	///////////////////////////////////////////////////////////////////////
	//
	s_IsBellatraFontEffect = 1;
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:22:12
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//#######################################################################################
void DestroyBellatraFontEffect(void)
{
	if( s_IsBellatraFontEffect == NULL )
		return;

	//
	for( int i=0; i< DMAX_BELLATRA_DDS_IMAGELIST; i++ )
	{
		if( s_BL_lpDDSurfaceBuff[i] )
		{
			s_BL_lpDDSurfaceBuff[i]->Release();
			s_BL_lpDDSurfaceBuff[i] = NULL;
		}
	}

	//
	s_BL_ImageMatGroup.Close();
	s_BL_ImageMatGroup.Init( DMAX_BELLATRA_TEX_IMAGELIST );

	//
	DeleteObject( s_EventScore_Font );
	s_EventScore_Font = NULL;

	//	
	s_IsBellatraFontEffect = 0;
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:22:16
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
int SetBellatraFontEffect( EBL_FontEffectType eBL_Type, SBL_SetFontEffect *lpCheckFontEffect, EBL_EVENT_TYPE eEventNum )
{
	//
	int iEventNum = 0;

	//
	if( s_IsBellatraFontEffect == NULL || eBL_Type == E_BL_ZERO )
	{
		if( lpCheckFontEffect )
            ::ZeroMemory( lpCheckFontEffect, sizeof(SBL_SetFontEffect) );
		return 0;
	}

	//
	SBL_SetFontEffect *lpSetFontEffect = &s_IsSetFontEffectBuff[ eBL_Type ];
	if( lpSetFontEffect->eBL_Type )
		return 0;

	//
	SBL_FontEffectInfo *lpSBL_FontEffectInfo = &s_BL_FontEffectInfoBuff[ eBL_Type ];

	::ZeroMemory( lpSetFontEffect, sizeof(SBL_SetFontEffect) );
	lpSetFontEffect->eBL_Type = eBL_Type;
	lpSetFontEffect->Max_MinEffect_Info = lpSBL_FontEffectInfo->Max_MinEffect_Info;

	//
	for( int i=0; i < lpSBL_FontEffectInfo->Max_MinEffect_Info; i++ )
	{
		SBL_MinFontEffect *lpMinFontEffectPtrBuff = s_lpBL_MinFontEffectPtrBuff[ lpSBL_FontEffectInfo->eMinEffect_PriorityBuff[ i ] ];

		SBL_MinFontEffect *lpMinFontEffectPtr = NULL;
		for( int loop=0; loop < DMAX_BL_MIN_EFFECT; loop++ )
		{
			if( lpMinFontEffectPtrBuff[ loop ].Life == 0 )
			{
				lpMinFontEffectPtr = &lpMinFontEffectPtrBuff[ loop ];
				break;
			}
		}

		if( lpMinFontEffectPtr == NULL )
		{
            ::ZeroMemory( lpSetFontEffect, sizeof(SBL_SetFontEffect) );
			return 0;
		}

		//
		lpSetFontEffect->eMinEffect_PriorityBuff[i] = lpSBL_FontEffectInfo->eMinEffect_PriorityBuff[ i ];
		lpSetFontEffect->lpMinFontEffectPtrBuff[i]  = lpMinFontEffectPtr;

		//
		::ZeroMemory( lpMinFontEffectPtr, sizeof(SBL_MinFontEffect) );
		lpMinFontEffectPtr->lpBL_MinEffectInfo = &s_BL_MinFontEffectInfoBuff[ lpSBL_FontEffectInfo->MinEffect_InfoBuff[ i ] ];

		lpMinFontEffectPtr->eBL_Type = eBL_Type;
		lpMinFontEffectPtr->Life = 1;

		lpMinFontEffectPtr->Pos.x = lpSBL_FontEffectInfo->Pos[ i ].x;
		lpMinFontEffectPtr->Pos.y = lpSBL_FontEffectInfo->Pos[ i ].y;

		lpMinFontEffectPtr->Size.cx = lpSBL_FontEffectInfo->Size[ i ].cx;
		lpMinFontEffectPtr->Size.cy = lpSBL_FontEffectInfo->Size[ i ].cy;

		lpMinFontEffectPtr->fBlend = lpMinFontEffectPtr->lpBL_MinEffectInfo->BlendNum[0];

		if( lpMinFontEffectPtr->lpBL_MinEffectInfo->DelayTime[ 0 ] > 0 )
		{
			float fDelayTime = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->DelayTime[ 0 ]);
			lpMinFontEffectPtr->fPosStep_x   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->PosMove[0].x) / fDelayTime;
			lpMinFontEffectPtr->fPosStep_y   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->PosMove[0].y) / fDelayTime;
			lpMinFontEffectPtr->fScaleStep_x = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->ScaleNum[0].cx) / fDelayTime;
			lpMinFontEffectPtr->fScaleStep_y = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->ScaleNum[0].cy) / fDelayTime;
			lpMinFontEffectPtr->fAngStep_x   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].x) / fDelayTime;
			lpMinFontEffectPtr->fAngStep_y   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].y) / fDelayTime;
			lpMinFontEffectPtr->fAngStep_z   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].z) / fDelayTime;
		}

		//
		if( eEventNum == E_BL_NO_EVENT )
			lpMinFontEffectPtr->eEventNum = E_BL_NO_EVENT;
		else if( iEventNum == 0 )
		{
			iEventNum = 1;
			lpMinFontEffectPtr->eEventNum = eEventNum;
		}
	}

	//
	if( lpCheckFontEffect )
        ::CopyMemory( lpCheckFontEffect, lpSetFontEffect, sizeof(SBL_SetFontEffect) );
	return 1;
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:39:06
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
void MainBellatraFontEffect(void)
{
	//
	int i, loop;
	if( s_IsBellatraFontEffect == NULL )
		return;

	//
	for( i=0; i <= E_BL_PRIORITY_3; i++ )
	{
		SBL_MinFontEffect *lpMinFontEffectPtrBuff = s_lpBL_MinFontEffectPtrBuff[ i ];
		for( loop=0; loop < DMAX_BL_MIN_EFFECT; loop++ )
		{
			if( lpMinFontEffectPtrBuff[ loop ].Life )
			{
				SBL_MinFontEffect	  *lpMinFontEffectPtr  = &lpMinFontEffectPtrBuff[ loop ];
				SBL_MinFontEffectInfo *lpMinFontEffectInfo = lpMinFontEffectPtr->lpBL_MinEffectInfo;

				lpMinFontEffectPtr->FrameTime++;
				if( lpMinFontEffectPtr->FrameTime > lpMinFontEffectInfo->DelayTime[ lpMinFontEffectPtr->FrameNum ] )
				{
					//
					if( lpMinFontEffectInfo->DelayTime[ lpMinFontEffectPtr->FrameNum ] == DELAY_STOP )
						lpMinFontEffectPtr->FrameTime--;
					else if( lpMinFontEffectInfo->DelayTime[ lpMinFontEffectPtr->FrameNum ] == DELAY_LOOP )
					{
						lpMinFontEffectPtr->FrameTime = 0;
						lpMinFontEffectPtr->FrameNum  = 0;

						//
						lpMinFontEffectPtr->fPos_x = lpMinFontEffectPtr->fPos_y = 0.f;
						lpMinFontEffectPtr->fScale_x = lpMinFontEffectPtr->fScale_y = 0.f;
						lpMinFontEffectPtr->fAng_x = lpMinFontEffectPtr->fAng_y = lpMinFontEffectPtr->fAng_z = 0.f;
						lpMinFontEffectPtr->fBlend = float(lpMinFontEffectInfo->BlendNum[0]);

						//
						if( lpMinFontEffectInfo->DelayTime[ 0 ] > 0 )
						{
							float fDelayTime = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->DelayTime[ 0 ]);
							lpMinFontEffectPtr->fPosStep_x   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->PosMove[0].x) / fDelayTime;
							lpMinFontEffectPtr->fPosStep_y   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->PosMove[0].y) / fDelayTime;
							lpMinFontEffectPtr->fScaleStep_x = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->ScaleNum[0].cx) / fDelayTime;
							lpMinFontEffectPtr->fScaleStep_y = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->ScaleNum[0].cy) / fDelayTime;
							lpMinFontEffectPtr->fAngStep_x   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].x) / fDelayTime;
							lpMinFontEffectPtr->fAngStep_y   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].y) / fDelayTime;
							lpMinFontEffectPtr->fAngStep_z   = float(lpMinFontEffectPtr->lpBL_MinEffectInfo->Rot3d[0].z) / fDelayTime;
						}
						else
						{
							lpMinFontEffectPtr->fPosStep_x = lpMinFontEffectPtr->fPosStep_y = 0.f;
							lpMinFontEffectPtr->fScaleStep_x = lpMinFontEffectPtr->fScaleStep_y = 0.f;
							lpMinFontEffectPtr->fAngStep_x = lpMinFontEffectPtr->fAngStep_y = lpMinFontEffectPtr->fAngStep_z = 0.f;
						}
					}
					else
					{
						lpMinFontEffectPtr->FrameNum++;

						//
						if( lpMinFontEffectPtr->FrameNum >= lpMinFontEffectInfo->MaxFrameNum )
							lpMinFontEffectPtr->Life = 0;
						else
						{
							lpMinFontEffectPtr->FrameTime = 0;

							int FrameNum = lpMinFontEffectPtr->FrameNum;

							//
							lpMinFontEffectPtr->fPos_x = float(lpMinFontEffectInfo->PosMove[FrameNum - 1].x);
							lpMinFontEffectPtr->fPos_y = float(lpMinFontEffectInfo->PosMove[FrameNum - 1].y);

							lpMinFontEffectPtr->fScale_x = float(lpMinFontEffectInfo->ScaleNum[FrameNum - 1].cx);
							lpMinFontEffectPtr->fScale_y = float(lpMinFontEffectInfo->ScaleNum[FrameNum - 1].cy);

							lpMinFontEffectPtr->fAng_x = float(lpMinFontEffectInfo->Rot3d[FrameNum - 1].x);
							lpMinFontEffectPtr->fAng_y = float(lpMinFontEffectInfo->Rot3d[FrameNum - 1].y);
							lpMinFontEffectPtr->fAng_z = float(lpMinFontEffectInfo->Rot3d[FrameNum - 1].z);

							lpMinFontEffectPtr->fBlend = float(lpMinFontEffectInfo->BlendNum[FrameNum - 1]);

							//
							float fDelayTime = float( lpMinFontEffectInfo->DelayTime[ FrameNum ] );

							lpMinFontEffectPtr->fPosStep_x = float(lpMinFontEffectInfo->PosMove[ FrameNum ].x - lpMinFontEffectPtr->fPos_x) / fDelayTime;
							lpMinFontEffectPtr->fPosStep_y = float(lpMinFontEffectInfo->PosMove[ FrameNum ].y - lpMinFontEffectPtr->fPos_y) / fDelayTime;

							lpMinFontEffectPtr->fScaleStep_x = float(lpMinFontEffectInfo->ScaleNum[ FrameNum ].cx - lpMinFontEffectPtr->fScale_x) / fDelayTime;
							lpMinFontEffectPtr->fScaleStep_y = float(lpMinFontEffectInfo->ScaleNum[ FrameNum ].cy - lpMinFontEffectPtr->fScale_y) / fDelayTime;

							lpMinFontEffectPtr->fAngStep_x = float(lpMinFontEffectInfo->Rot3d[ FrameNum ].x - lpMinFontEffectPtr->fAng_x) / fDelayTime;
							lpMinFontEffectPtr->fAngStep_y = float(lpMinFontEffectInfo->Rot3d[ FrameNum ].y - lpMinFontEffectPtr->fAng_y) / fDelayTime;
							lpMinFontEffectPtr->fAngStep_z = float(lpMinFontEffectInfo->Rot3d[ FrameNum ].z - lpMinFontEffectPtr->fAng_z) / fDelayTime;

							lpMinFontEffectPtr->fBlendStep = float(lpMinFontEffectInfo->BlendNum[ FrameNum ] - lpMinFontEffectPtr->fBlend) / fDelayTime;
						}
					}
				}
				else
				{
					lpMinFontEffectPtr->fPos_x += lpMinFontEffectPtr->fPosStep_x;
					lpMinFontEffectPtr->fPos_y += lpMinFontEffectPtr->fPosStep_y;

					lpMinFontEffectPtr->fScale_x += lpMinFontEffectPtr->fScaleStep_x;
					lpMinFontEffectPtr->fScale_y += lpMinFontEffectPtr->fScaleStep_y;

					lpMinFontEffectPtr->fAng_x += lpMinFontEffectPtr->fAngStep_x;
					lpMinFontEffectPtr->fAng_y += lpMinFontEffectPtr->fAngStep_y;
					lpMinFontEffectPtr->fAng_z += lpMinFontEffectPtr->fAngStep_z;

					lpMinFontEffectPtr->fBlend += lpMinFontEffectPtr->fBlendStep;
				}
			}
		}
	}

	//
	for( i=0; i < DMAX_BL_EFFECT_INFO; i++ )
	{
		SBL_SetFontEffect *lpSetFontEffect = &s_IsSetFontEffectBuff[ i ];
	
		if( CheckBellatraFontEffect(lpSetFontEffect) <= 0 )
			CheckBellatraFontEffect( lpSetFontEffect, 1 );
	}
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:39:15
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
void DrawBellatraFontEffect(void)
{
	if( s_IsBellatraFontEffect == NULL )
		return;

	for( int i=E_BL_PRIORITY_3; i >= 0; i-- )
	{
		SBL_MinFontEffect *lpMinFontEffectPtrBuff = s_lpBL_MinFontEffectPtrBuff[ i ];
		for( int loop=0; loop < DMAX_BL_MIN_EFFECT; loop++ )
		{
			if( lpMinFontEffectPtrBuff[ loop ].Life )
			{
				SBL_MinFontEffect	  *lpMinFontEffectPtr  = &lpMinFontEffectPtrBuff[ loop ];
				SBL_MinFontEffectInfo *lpMinFontEffectInfo = lpMinFontEffectPtr->lpBL_MinEffectInfo;

				//
				if( lpMinFontEffectInfo->DelayTime[ lpMinFontEffectPtr->FrameNum ] == DELAY_STOP )
				{
					switch( lpMinFontEffectPtr->eEventNum )
					{
					case E_BL_EVENT_SCORE:
						DrawEventScore();
						break;
					}
				}

				//
				int ImageNum = lpMinFontEffectInfo->FrameMatBuff[ lpMinFontEffectPtr->FrameNum ];
				int dest_x = int(lpMinFontEffectPtr->Pos.x + lpMinFontEffectPtr->fPos_x);
				int dest_y = int(lpMinFontEffectPtr->Pos.y + lpMinFontEffectPtr->fPos_y);
				int x, y, width, height;

				if( ImageNum >= 0 )
				{
					if( lpMinFontEffectInfo->eBL_ImageType == E_BL_SURFACE )
					{
						//
						if( dest_x + lpMinFontEffectPtr->Size.cx <= 0 || dest_y + lpMinFontEffectPtr->Size.cy <= 0 || 
							dest_x >= 800 || dest_y >= 600 )
						{
							continue;
						}

						//
						width = (dest_x + lpMinFontEffectPtr->Size.cx) - 800;
						if( width > 0 )
							width = lpMinFontEffectPtr->Size.cx - width;
						else
							width = lpMinFontEffectPtr->Size.cx;

						//
						height = (dest_y + lpMinFontEffectPtr->Size.cy) - 600;
						if( height > 0 )
							height = lpMinFontEffectPtr->Size.cy - height;
						else
							height = lpMinFontEffectPtr->Size.cy;

						//
						if( dest_x < 0 )
						{
							x = -dest_x;
							dest_x = 0;
						}
						else // if( dest_x >= 0 )
							x = 0;

						//
						if( dest_y < 0 )
						{
							y      = -dest_y;
							dest_y = 0;
						}
						else // if( dest_y >= 0 )
							y = 0;

						//
						DrawFzmBackToSurface( dest_x, dest_y, s_BL_lpDDSurfaceBuff[ ImageNum ],											  
											  x, y, width, height, DDBLT_WAIT | DDBLT_KEYSRC );
					}
					else // if( lpMinFontEffectInfo->eBL_ImageType == E_BL_MAT_GROUP )
					{
						//
						width  = int(lpMinFontEffectPtr->Size.cx + lpMinFontEffectPtr->fScale_x);
						height = int(lpMinFontEffectPtr->Size.cy + lpMinFontEffectPtr->fScale_y);

						//
						smFMATRIX  fMatrix_x, fMatrix_y, fMatrix_z, fMatrix;
						smFMATRIX *lpMatrix = NULL;

						if( lpMinFontEffectPtr->fAng_x || lpMinFontEffectPtr->fAng_y || lpMinFontEffectPtr->fAng_z )
						{
							smFIdentityMatrix( fMatrix_x );
							smFIdentityMatrix( fMatrix_y );
							smFIdentityMatrix( fMatrix_z );

							smFRotateXMatrix( fMatrix_x, smToDegree(lpMinFontEffectPtr->fAng_x) );
							smFRotateYMatrix( fMatrix_y, smToDegree(lpMinFontEffectPtr->fAng_y) );
							smFRotateZMatrix( fMatrix_z, smToDegree(lpMinFontEffectPtr->fAng_z) );

							smFMatrixMult( fMatrix, fMatrix_y, fMatrix_x );
							smFMatrixMult( fMatrix, fMatrix, fMatrix_z );

							lpMatrix = &fMatrix;
						}

						//
						DrawBellatraBackToTexture2D( s_BL_ImageMatGroup.smMaterial[ ImageNum ].smTexture[0], dest_x, dest_y,
													 lpMatrix, width, height, int(lpMinFontEffectPtr->fBlend) );
					}
				}
				else if( lpMinFontEffectInfo->eBL_ImageType == E_BL_FONT_MAT_GROUP )
				{
					psSetDefaultRenderState();

					switch( lpMinFontEffectPtr->eBL_Type )
					{
					case E_BL_FONT_QUAKE_SEAL:
						DrawFontImage( "Quake seal", int(265*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
									    RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_STUN_SEAL:
						DrawFontImage( "Stun seal", int(280*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_FREEZE_SEAL:
						DrawFontImage( "Freeze seal", int(260*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_RABBIE_SEAL:
						DrawFontImage( "Rabbie seal", int(260*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_STYGIAN_SEAL:
						DrawFontImage( "Stygian seal", int(235*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_GUARDIAN_SEAL:
						DrawFontImage( "Guardian Saint seal", int(150*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;

					case E_BL_FONT_POINT_SEAL:
						DrawFontImage( "5000 Point UP", int(210*g_fWinSizeRatio_X), int(350*g_fWinSizeRatio_Y),
										RGBA_MAKE(255,230,0,int(lpMinFontEffectPtr->fBlend)), 2.f*g_fWinSizeRatio_X );
						break;
					}
				}
			}
		}
	}
}


//######################################################################################
//작 성 일 : 2004-05-08 오후 1:40:39
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
void DrawBellatraBackToTexture2D( smTEXTUREHANDLE *hTexHandle, int X, int Y, smFMATRIX *lpMatrix, int HalfSize_x, int HalfSize_y, int Blend )
{
	int ix[4], iy[4];
	ix[0] = -HalfSize_x; iy[0] = -HalfSize_y;
	ix[1] = -HalfSize_x; iy[1] =  HalfSize_y;
	ix[2] =  HalfSize_x; iy[2] = -HalfSize_y;
	ix[3] =  HalfSize_x; iy[3] =  HalfSize_y;

	int cnt;
	float fx[4], fy[4];	

	if( lpMatrix )
	{
		for( cnt=0; cnt < 4; cnt++ )
		{
			fx[cnt] = float(ix[cnt]) * lpMatrix->_11 + float(iy[cnt]) * lpMatrix->_21;
			fy[cnt] = float(ix[cnt]) * lpMatrix->_12 + float(iy[cnt]) * lpMatrix->_22;

			fx[cnt] += (float)X;
			fy[cnt] += (float)Y;
		}
	}
	else
	{
		for( cnt=0; cnt < 4; cnt++ )
		{
			fx[cnt] = float(ix[cnt] + X);
			fy[cnt] = float(iy[cnt] + Y);
		}
	}

	//
	for( cnt=0; cnt < 4; cnt++ )
	{
		fx[cnt] *= g_fWinSizeRatio_X;
		fy[cnt] *= g_fWinSizeRatio_Y;
	}

	//
	psDrawTexImage2( hTexHandle, fx, fy, 0, 0, 1, 1, Blend, 0 );
}


// 리턴값이 
// 0 이면 죽은 상태. 혹은 인자값 이상.
// 1 이면 정지 상태
// 2 이면 활동중 ( 무한 LOOP 포함 )
int CheckBellatraFontEffect( SBL_SetFontEffect *lpCheckFontEffect, int isKill )
{
	if( lpCheckFontEffect == NULL || lpCheckFontEffect->Max_MinEffect_Info <= 0 )
		return 0;

	int Life, stopNum, i;

	if( isKill )
	{
		for( i=0; i < lpCheckFontEffect->Max_MinEffect_Info; i++ )
		{
            lpCheckFontEffect->lpMinFontEffectPtrBuff[i]->Life = FALSE;
			lpCheckFontEffect->lpMinFontEffectPtrBuff[i]->eEventNum = E_BL_NO_EVENT;
		}

		lpCheckFontEffect->eBL_Type			= E_BL_ZERO;
		lpCheckFontEffect->Max_MinEffect_Info = 0;
		return 0;
	}
	else
	{
		SBL_MinFontEffect     *lpMinFontEffect;
		SBL_MinFontEffectInfo *lpMinEffectInfo;

		Life = stopNum = 0;
		for( i=0; i < lpCheckFontEffect->Max_MinEffect_Info; i++ )
		{
			lpMinFontEffect = lpCheckFontEffect->lpMinFontEffectPtrBuff[i];
			lpMinEffectInfo = lpMinFontEffect->lpBL_MinEffectInfo;

			if( lpMinFontEffect->Life )
				Life++;

			if( lpMinEffectInfo->DelayTime[ lpMinFontEffect->FrameNum ] == DELAY_STOP )
				stopNum++;
		}

		if( Life <= 0 )
			return 0;

		if( stopNum && stopNum == lpCheckFontEffect->Max_MinEffect_Info )
			return 1;
	}

	return 2;
}



