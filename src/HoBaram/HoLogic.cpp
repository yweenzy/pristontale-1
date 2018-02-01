#include "..\\HoBaram\\HoLinkHeader.h"
#include "sinbaram\\sinLinkHeader.h"
#include "..\\PlayMain.h"

/*
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"
*/

HoEffectPatDest::HoEffectPatDest()
{
	BlurCurrentFrame = FALSE;
	SumCount = 0;

	BlurStartFlag = FALSE;
	AniDataIndex = -1;
}

HoEffectPatDest::~HoEffectPatDest()
{

}

int HoEffectPatDest::Main()
{
	int x,y,z;

	if(!StartFlag)
		return FALSE;
	
	if(CurrentFrame > AnimationEnd*160-1)
	{
		PrimitiveBillBoard.SetState(FALSE);
		Init();
		//EventEnd();
		if(SkillType == MONSTER_WEB_SHOT1)
			StartEffectMonster(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), MONSTER_WEB_HIT1);
	}
	
	if(CurrentFrame > (AnimationEnd*160-1)-5*FrameStep)
	{
		BlendStep -= 2;
		CurrentFrame += FrameStep/10;
	}
	else
		CurrentFrame += FrameStep;
	
	if(WorkState == PAT_PROCESS)
	{
		if( CurrentFrame >= (AnimationEnd*160-1)-5*FrameStep)
			CurrentFrame = 159;

	}
	
	if( CurrentFrame < (AnimationEnd*160-1)-5*FrameStep)
	{
		GetMoveLocation( 0, 0, Step, DestAngleX, DestAngleY, 0);
		if(SkillType == SKILL_PERFECT_AIM || SkillType == SKILL_WIND_ARROW || SkillType == MONSTER_WEB_SHOT1
			|| SkillType == SKILL_ARROW_OF_RAGE || SkillType == SKILL_AVALANCHE || SkillType == SKILL_GROUND_PIKE)
		{
			LocalX += GeoResult_X;
			LocalY += GeoResult_Y;
			LocalZ += GeoResult_Z;
			
			//이동할 위치에 대한 벡터의 정규화를 위해서.....
			D3DVECTOR	attractLocation;
			attractLocation.x = DestX - (WorldX+LocalX);
			attractLocation.y = DestY - (WorldY+LocalY);
			attractLocation.z = DestZ - (WorldZ+LocalZ);
			
			D3DVECTOR attractDir = attractLocation;
			//벡터의 길이를 구한다.
			float length;
			length = (float)sqrt(attractDir.x*attractDir.x+attractDir.y*attractDir.y+attractDir.z*attractDir.z);
			
			if(SkillType == SKILL_WIND_ARROW)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd*160-1)-FrameStep);
					PrimitiveBillBoard.SetState(FALSE);
					WorkState = PAT_END;
					EventEnd();
					return TRUE;	
				}
				StartEffect( int(WorldX+LocalX+GeoResult_X), int(WorldY+LocalY+GeoResult_Y), int(WorldZ+LocalZ+GeoResult_Z),100,100,100,150, EFFECT_PARTICLE_BOW2 );
			}
			else if(SkillType == SKILL_PERFECT_AIM)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd*160-1)-FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					EventEnd();
					return TRUE;	
				}
			}
			else if(SkillType == SKILL_ARROW_OF_RAGE)
			{
				//마지막에 좌표 보정..
				if(length < 35000 && WorkState == PAT_PROCESS)
				{
					GetRadian3D( int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), DestX, DestY-40000, DestZ);
					
					Angle.x = GeoResult_X;
					Angle.y = GeoResult_Y;
					Angle.z = 0;
					
					Angle.y = (-Angle.y+ANGLE_180)&ANGCLIP;
				}

				if(length < 30000 && WorkState == PAT_PROCESS)
				{

					CurrentFrame = ((AnimationEnd*160-1)-FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					
					StartEffect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), ARROW_OF_RAGE_POWER1);

					//StartSkillDest(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), DestX, DestY-40000, DestZ, SKILL_ARROW_OF_RAGE_END, Level);

					x = int(WorldX+LocalX);
					z = int(WorldZ+LocalZ);
					x = (DestX-x)>>FLOATNS;
					z = (DestZ-z)>>FLOATNS;
					z = (int)sqrt( (double)(x*x+z*z) );
					z /= 2;

					y = GetRadian2D( int(WorldX+LocalX) , int(WorldZ+LocalZ) , DestX , DestZ );
			
					GetMoveLocation( 0,0,z*fONE , 0,y,0 );

					x = int(WorldX+LocalX)+GeoResult_X;
					z = int(WorldZ+LocalZ)+GeoResult_Z;
					StartSkillDest(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), x, DestY-40000, z, SKILL_ARROW_OF_RAGE_END, Level);
					return TRUE;
				}
			}
			else if(SkillType == SKILL_AVALANCHE)
			{
				//static particleCount = 0;
				//particleCount++;

				//if(particleCount > 2)
				//{
					//particleCount = 0;
					StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), DestAngleX, DestAngleY, DestAngleZ, SKILL_AVALANCHE_PARTICLE);
				//}

				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd*160-1)-FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);

					//StartEffect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), EFFECT_NORMAL_HIT1);
					StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), 0, 0, 0, SKILL_TRIPLE_IMPACT);
					return TRUE;
				}
			}
			else if(SkillType == MONSTER_WEB_SHOT1)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					//AnimationEnd = CurrentFrame/250;
					CurrentFrame = ((AnimationEnd*160-1)-40);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					EventEnd();
					return TRUE;	
				}
			}
			else if(SkillType == SKILL_GROUND_PIKE)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					//StartEffect(WorldX+LocalX, WorldY+LocalY, WorldZ+LocalZ, EFFECT_GROUND_PIKE_PARTICLE);
					//AnimationEnd = CurrentFrame/250;
					//BlendStep -= 6;
					//if(BlendStep < -250)
					//{
						CurrentFrame = ((AnimationEnd*160-1)-200);
						WorkState = PAT_END;
						PrimitiveBillBoard.SetState(FALSE);
						EventEnd();

					//	StartFlag = FALSE;
					//}
					return TRUE;	
				}
			}
		}
		else if(SkillType == SKILL_MECHANIC_BOMB)
		{
			//이동할 위치에 대한 벡터의 정규화를 위해서.....
			D3DVECTOR	attractLocation;
			attractLocation.x = DestX - (WorldX+LocalX);
			attractLocation.y = DestY - (WorldY+LocalY);
			attractLocation.z = DestZ - (WorldZ+LocalZ);
			
			D3DVECTOR attractDir = attractLocation;
			//벡터의 길이를 구한다.
			float length;
			length = (float)sqrt(attractDir.x*attractDir.x+attractDir.y*attractDir.y+attractDir.z*attractDir.z);
			
			if(length < 20000)
			{

				//맵 체크 부분...
				int mapY1 = int(WorldY+LocalY);
				int mapY2 = int(WorldY+LocalY);

				if(smGameStage[0])
				{
					mapY1 = smGameStage[0]->GetHeight(int(WorldX+LocalX), int(WorldZ+LocalZ));
				}
				if(smGameStage[1])
				{
					mapY2 = smGameStage[1]->GetHeight(int(WorldX+LocalX), int(WorldZ+LocalZ));
					if (mapY1 < mapY2) mapY1 = mapY2;
				}
				
				//종료 조건(땅에 떨어지거나) //목적 위치에 근접했을때는 멈춰야 함...
				if(mapY1 > (WorldY+LocalY-4000) || length < 3000)
				{
					CurrentFrame = ((AnimationEnd*160-1)-5*FrameStep);
					PrimitiveBillBoard.SetState(FALSE);
					WorkState = PAT_END;
					Init();
					EventEnd();
					return TRUE;
				}
			}

			if(length > 10000)
				VelocityY += int(attractDir.y/length * 120.0f);
			else
				VelocityY += int(attractDir.y/length * 60.0f);

			if(VelocityY >= 5000)
			{
				VelocityY *= 0.75f;
			}

			LocalX += GeoResult_X;
			//벡터 정규화...
			LocalY += VelocityY;
			LocalZ += GeoResult_Z;

			StartEffect(int(WorldX+LocalX)+rand()%2000-1000+GeoResult_X, int(WorldY+LocalY)+rand()%1000-1000, int(WorldZ+LocalZ)+rand()%2000-1000+GeoResult_Z, EFFECT_MECHANICBOMB_DUST1);

			Angle.x += ANGLE_45/4;
			Angle.x = Angle.x&ANGCLIP;
		}
		else
		{
			LocalX += GeoResult_X;
			LocalY += GeoResult_Y;
			LocalZ += GeoResult_Z;
			//맵 체크 부분...
			int mapY1 = int(WorldY+LocalY);
			int mapY2 = int(WorldY+LocalY);

			if(smGameStage[0])
			{
				mapY1 = smGameStage[0]->GetHeight(int(WorldX+LocalX), int(WorldZ+LocalZ));
			}
			if(smGameStage[1])
			{
				mapY2 = smGameStage[1]->GetHeight(int(WorldX+LocalX), int(WorldZ+LocalZ));
				if (mapY1 < mapY2) mapY1 = mapY2;
			}
			
			//종료 조건(땅에 떨어지거나) //목적 위치에 근접했을때는 멈춰야 함...
			if(WorkState == PAT_PROCESS && mapY1 > (WorldY+LocalY-4000))
			{
				CurrentFrame = ((AnimationEnd*160-1)-5*FrameStep);
				PrimitiveBillBoard.SetState(FALSE);
				WorkState = PAT_END;

				if(SkillType == SKILL_ARROW_OF_RAGE_END)
				{
					BlurBlendValue = 0;
					StartEffect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), EFFECT_ARROW_OF_RAGE_HIT1);
				}
			}
		}
		
		POINT3D velocity;
		velocity.x = GeoResult_X;
		velocity.y = GeoResult_Y;
		velocity.z = GeoResult_Z;
		
		PrimitiveBillBoard.TranslateWorld(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ));
		PrimitiveBillBoard.SetDirectionVelocity(velocity);
		PrimitiveBillBoard.Main();

		MainBlur();
	}
	return TRUE;
}


int HoEffectPatDest::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag)
	{
		HoEffectPat::Draw(x, y, z, ax, ay, az);
		PrimitiveBillBoard.Draw(x, y, z, ax, ay, az);
		DrawBlur(x, y, z, ax, ay, az);
	}
	return TRUE;
}


int HoEffectPatDest::StartDest(POINT3D currentPos, POINT3D destPos, smPAT3D *pat, int skillType, int level)
{
	if(pat == NULL || StartFlag)
		return FALSE;
	
	Angle.y = 0;
	Angle.x = 0;
	Level = level;
	HoEffectPat::Init();
	PatObj = pat;
	WorldX = (float)currentPos.x, WorldY = (float)currentPos.y, WorldZ = (float)currentPos.z;
	LocalX = 0, LocalY = 0, LocalZ = 0;

	StartFlag = TRUE;
	CurrentFrame = 159;
	PatObj->Frame = CurrentFrame;
	BlendStep = 0;

	DestX = destPos.x;
	DestY = destPos.y;
	DestZ = destPos.z;

	SkillType = skillType;
	WorkState = PAT_PROCESS;
	Step = 12*fONE;
	FrameStep = 40;

	if(SkillType == SKILL_ARROW_OF_RAGE)
	{
		Step = fONE*8;
		DestY += 60000;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE_END)
	{
		Step = fONE*5;
	}
	
	GetRadian3D( int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), DestX, DestY, DestZ);
	
	DestAngleX = GeoResult_X;
	DestAngleY = GeoResult_Y;
	DestAngleZ = 0;

	Angle.x = GeoResult_X;
	Angle.y = GeoResult_Y;
	Angle.z = 0;
	
	Angle.y = (-Angle.y+ANGLE_180)&ANGCLIP;
	
	
	if(SkillType == SKILL_MECHANIC_BOMB)
	{
		Step = 4*fONE;
		//이동할 위치에 대한 벡터의 정규화를 위해서.....
		//WorldY = WorldY+1000;
		
		D3DVECTOR	attractLocation;
		attractLocation.x = DestX - (WorldX+LocalX);
		attractLocation.y = DestY - (WorldY+LocalY);
		attractLocation.z = DestZ - (WorldZ+LocalZ);
		
		D3DVECTOR attractDir = attractLocation;
		//벡터의 길이를 구한다.
		float length;
		length = (float)sqrt(attractDir.x*attractDir.x+attractDir.y*attractDir.y+attractDir.z*attractDir.z);
		
		if(length >= 30000)
			VelocityY = 800;
		else
			VelocityY = 400;
	}
	else if(SkillType == SKILL_PERFECT_AIM)
	{
		Step = 9*fONE;
		POINT	size;
		size.x = 10;
		size.y = 400;

		GetMoveLocation( 0, 0, Step, DestAngleX, DestAngleY, 0);
		PrimitiveBillBoard.StartBillRect(int(WorldX+LocalX)+GeoResult_X, 
			int(WorldY+LocalY)+GeoResult_Y+200, int(WorldZ+LocalZ)+GeoResult_Z, "SkillPerfectAim1.ini", ANI_LOOP, PRIMITIVE_PATH_RECT_LINE);
		PrimitiveBillBoard.SetSize(size);	
	}
	else if(SkillType == SKILL_WIND_ARROW)
	{
		Step = 9*fONE;
	}
	else if(SkillType == MONSTER_WEB_SHOT1)
	{
		Step = 4*fONE;
		GetMoveLocation( 0, 0, Step*7, DestAngleX, DestAngleY, 0);
		DestX += GeoResult_X;
		DestZ += GeoResult_Z;
		FrameStep = 20;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE)
	{
		POINT	size;
		size.x = 17; 
		size.y = 600;

		/*
		PrimitiveBillBoard.StartBillRect(int(WorldX+LocalX), 
			int(WorldY+LocalY)+300, int(WorldZ+LocalZ), "Blur1.ini", ANI_LOOP, PRIMITIVE_PATH_RECT_LINE);
		PrimitiveBillBoard.SetSize(size);	
		*/

		StartBlur("Blur1.ini");
		Level = level;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE_END)
	{
		Step = 18*fONE;
		StartBlur("Blur1.ini");
	}
	else if(SkillType == SKILL_AVALANCHE)
	{
		Step = 12*fONE;
	}
	else if(SkillType == SKILL_GROUND_PIKE)
	{
		Step = 8*fONE;
		SetBlendStep(-110);
	}
	return TRUE;
}

int HoEffectPatDest::CreatePathFace()
{
	
	//Vertex 값 초기화..
	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;
	
	POINT3D firstPos;
	POINT3D secondPos;
	
	for(int index = 0; index < PosListCount-1; index++)
	{
		if( (VertexCount-4) >= MAX_BLUR_VERTEX)
			break;

		firstPos.x = int(PosList[index].x);
		firstPos.y = int(PosList[index].y);
		firstPos.z = int(PosList[index].z); 
		
		secondPos.x = int(PosList[index+1].x);
		secondPos.y = int(PosList[index+1].y);
		secondPos.z = int(PosList[index+1].z);
		
		int blendStep = BlurBlendValue/((PosListCount-1));
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x+PosList[index+1].x);
		inVector.y = float(PosList[index].y+PosList[index+1].y);
		inVector.z = float(PosList[index].z+PosList[index+1].z);
	
		double length = sqrt(inVector.x*inVector.x+inVector.y*inVector.y+inVector.z*inVector.z);
		inVector.x = float(inVector.x/length);
		inVector.y = float(inVector.y/length);
		inVector.z = float(inVector.z/length);
		
		
		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;
		
		if(index == 0)
		{
			//앞쪽...
			Vertex[VertexCount].x   = int(firstPos.x+outVector.x*SizeWidth*20);
			Vertex[VertexCount].y   = int(firstPos.y+outVector.y*SizeWidth*20);
			Vertex[VertexCount].z   = int(firstPos.z+outVector.z*SizeWidth*20);
			Vertex[VertexCount].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[3] = (int)BlurBlendValue;
			
			Vertex[VertexCount+1].x = int(firstPos.x+inVector.x*SizeWidth*20);
			Vertex[VertexCount+1].y = int(firstPos.y+inVector.y*SizeWidth*20);
			Vertex[VertexCount+1].z = int(firstPos.z+inVector.z*SizeWidth*20);
			Vertex[VertexCount+1].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[3] = (int)BlurBlendValue;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeWidth*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeWidth*20);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeWidth*20);
			Vertex[VertexCount+2].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[3] = (int)BlurBlendValue;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeWidth*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeWidth*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeWidth*20);

			Vertex[VertexCount+3].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[3] = (int)BlurBlendValue;
		}
		else
		{
			//앞쪽...
			Vertex[VertexCount].x   = Vertex[VertexCount-2].x;
			Vertex[VertexCount].y   = Vertex[VertexCount-2].y;
			Vertex[VertexCount].z   = Vertex[VertexCount-2].z;
			Vertex[VertexCount].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[3] = (int)BlurBlendValue;
			
			Vertex[VertexCount+1].x = Vertex[VertexCount-1].x;
			Vertex[VertexCount+1].y = Vertex[VertexCount-1].y;
			Vertex[VertexCount+1].z = Vertex[VertexCount-1].z;
			Vertex[VertexCount+1].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+1].sDef_Color[3] = (int)BlurBlendValue;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeWidth*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeWidth*20);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeWidth*20);
			Vertex[VertexCount+2].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+2].sDef_Color[3] = (int)BlurBlendValue;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeWidth*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeWidth*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeWidth*20);

			Vertex[VertexCount+3].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount+3].sDef_Color[3] = (int)BlurBlendValue;
		}

		
		
		//Texture 좌표 관련 초기화...
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		TexLink[TexLinkCount+1].u[0] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[0] = 0.0f;
		TexLink[TexLinkCount+1].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount+1].v[1] = 1.0f;
		TexLink[TexLinkCount+1].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[2] = 1.0f;
		
		
		//삼각형 컬링 때문에....
		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount+1;
		Face[FaceCount].Vertex[2] = VertexCount+2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;
	
		Face[FaceCount+1].Vertex[0] = VertexCount+2;
		Face[FaceCount+1].Vertex[1] = VertexCount+1;
		Face[FaceCount+1].Vertex[2] = VertexCount+3;
		Face[FaceCount+1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount+1].lpTexLink = &TexLink[TexLinkCount+1];
		Face[FaceCount+1].sum = 0;
		

		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}

	return TRUE;
}


int HoEffectPatDest::StartBlur(char *iniName)
{
	
	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;
	
	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;
	
	BlurBlendValue = 120;
	BlurTimeCount = 0;
	BlurCurrentFrame = 0;
	SizeWidth = 15;
	
	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_SHADOW;
	
	BlurStartFlag = TRUE;
	return TRUE;
}

int HoEffectPatDest::MainBlur()
{
	if(BlurStartFlag == FALSE || AniDataIndex == -1)
		return FALSE;
	
	//if(CurrentFrame > (AnimationEnd*160-1)-5*FrameStep)
	//{
		//CurrentBlendValue--;
	//}

	GetMoveLocation( 0, 0, Step, DestAngleX, DestAngleY, 0);
	if(PosListCount < MAX_BLUR_LIST)
	{
		POINT3D tempPosList[MAX_BLUR_LIST-1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = int(WorldX+LocalX+GeoResult_X);
		PosList[0].y = int(WorldY+LocalY+GeoResult_Y);
		PosList[0].z = int(WorldZ+LocalZ+GeoResult_Z);
		
		PosListCount++;
	}
	else
	{
		POINT3D tempPosList[MAX_BLUR_LIST-1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = int(WorldX+LocalX+GeoResult_X);
		PosList[0].y = int(WorldY+LocalY+GeoResult_Y);
		PosList[0].z = int(WorldZ+LocalZ+GeoResult_Z);
	}

	if(StartFlag == FALSE )
		return FALSE;
	
	//Animation 한번...
	if(BlurCurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(BlurTimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[BlurCurrentFrame].Delay)
		{
			BlurTimeCount = 0;
			BlurCurrentFrame++;
			if(BlurCurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount-1)
				BlurCurrentFrame = 1;
		}
		//BlurBlendValue = 90;
		BlurTimeCount++;
	}
	
	return TRUE;
}

int HoEffectPatDest::DrawBlur(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || BlurStartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	
	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;
	//현재 찍을 Frame을 세팅한다..
	smMaterialGroup->SetMaterialAnimFrame( &smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()], 
	AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[BlurCurrentFrame].ImageNum);
	
	//Camera각도 입력.
	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	
	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);
	
	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	//lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		smRender.RenderD3D();
	//lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	SumCount++;

	return TRUE;
}

int HoEffectPatDest::StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, 
							  int destX, int destY, int destZ,
							  smPAT3D *pat, char *addEffectName)
{
	if(pat == NULL || StartFlag)
		return FALSE;
	
	Angle.y = ((ANGLE_270-angleY)&ANGCLIP);
	Angle.x = ANGLE_270;
	
	HoEffectPat::Init();
	PatObj = pat;
	WorldX = (float)x, WorldY = (float)y, WorldZ = (float)z;
	LocalX = 0, LocalY = 0, LocalZ = 0;

	StartFlag = TRUE;
	CurrentFrame = 159;
	PatObj->Frame = CurrentFrame;
	BlendStep = 0;
	
	DestX = destX;
	DestY = destY;
	DestZ = destZ;
	GetRadian3D( int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), DestX, DestY, DestZ);
	
	DestAngleX = GeoResult_X;
	DestAngleY = GeoResult_Y;
	DestAngleZ = 0;

	Angle.x = GeoResult_X;
	Angle.y = GeoResult_Y;
	Angle.z = 0;
	
	Angle.y = (-Angle.y+ANGLE_180)&ANGCLIP;
	if(addEffectName != NULL)
	{
		POINT	size;
		size.x = 16;
		size.y = 100;
		PrimitiveBillBoard.StartBillRect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), addEffectName, ANI_LOOP, PRIMITIVE_PATH_RECT_LINE);
		PrimitiveBillBoard.SetSize(size);
	}
	
	WorkState = PAT_PROCESS;
	FrameStep = 40;

	return TRUE;
}

int HoEffectPatDest::EventEnd()
{
	
	switch(SkillType)
	{
		case SKILL_MECHANIC_BOMB:
		{
			SkillPlaySound( SKILL_SOUND_MECHANIC_BOMB2, int(WorldX+LocalX),int(WorldY+LocalY+1000),int(WorldZ+LocalZ) );
			StartEffect(int(WorldX+LocalX), int(WorldY+LocalY+1000), int(WorldZ+LocalZ), EFFECT_FIRE_HIT1, Level);			
		}

		case SKILL_PERFECT_AIM:
		{
			
			SkillPlaySound( SKILL_SOUND_ARROW_HIT1, int(WorldX+LocalX),int(WorldY+LocalY),int(WorldZ+LocalZ) );
			StartEffect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), EFFECT_CRITICAL_HIT1);			
		}

		case SKILL_WIND_ARROW:
		{
			SkillPlaySound( SKILL_SOUND_ARROW_HIT2, int(WorldX+LocalX),int(WorldY+LocalY),int(WorldZ+LocalZ) );
			StartEffect(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), EFFECT_CRITICAL_HIT1);			
		}

		case MONSTER_WEB_SHOT1:
		{
			/*
			GetMoveLocation( 0, 0, Step*3, DestAngleX, DestAngleY, 0);
			LocalX += GeoResult_X;
			LocalY += GeoResult_Y;
			LocalZ += GeoResult_Z;
			*/

			//StartEffectMonster(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), MONSTER_WEB_HIT1);
		}
	}
	return TRUE;
}




//int HoEffectMove::Draw(int 
HoEffectShield::HoEffectShield()
{
	AniDataIndex = -1;
	StartFlag = FALSE;
	CurrentFrame = 0;

	SumCount = 0;

	memset(Vertex, 0, sizeof(Vertex));
	VertexCount = 0;
	memset(Face, 0, sizeof(Face));
	FaceCount = 0;
	memset(TexLink, 0, sizeof(TexLink));
	TexLinkCount = 0;

	Character = NULL;

	
}

HoEffectShield::~HoEffectShield()
{

}

int HoEffectShield::CreatePathFace()
{
	//Vertex 값 초기화..
	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;
	
	
	POINT3D firstPos;
	POINT3D secondPos;
	
	for(int index = 0; index < PosListCount-1; index++)
	{
		firstPos.x = int(PosList[index].x+WorldX);
		firstPos.y = int(PosList[index].y+WorldY);
		firstPos.z = int(PosList[index].z+WorldZ); 
		
		secondPos.x = int(PosList[index+1].x+WorldX);
		secondPos.y = int(PosList[index+1].y+WorldY);
		secondPos.z = int(PosList[index+1].z+WorldZ);
		
		int blendStep = CurrentBlendValue/((PosListCount-1)+10);
		


		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x+PosList[index+1].x);
		inVector.y = float(PosList[index].y+PosList[index+1].y);
		inVector.z = float(PosList[index].z+PosList[index+1].z);
	
		double length = sqrt(inVector.x*inVector.x+inVector.y*inVector.y+inVector.z*inVector.z);
		inVector.x = float(inVector.x/length);
		inVector.y = float(inVector.y/length);
		inVector.z = float(inVector.z/length);
		
		
		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;
		
		if(index == 0)
		{
			//앞쪽...
			Vertex[VertexCount].x   = int(firstPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount].y   = int(firstPos.y+outVector.y*SizeHeight*20);
			Vertex[VertexCount].z   = int(firstPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = int(firstPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+1].y = int(firstPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+1].z = int(firstPos.z+inVector.z*SizeHeight*20);
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}
		else
		{
			//앞쪽...
			Vertex[VertexCount].x   = Vertex[VertexCount-2].x;
			Vertex[VertexCount].y   = Vertex[VertexCount-2].y;
			Vertex[VertexCount].z   = Vertex[VertexCount-2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = Vertex[VertexCount-1].x;
			Vertex[VertexCount+1].y = Vertex[VertexCount-1].y;
			Vertex[VertexCount+1].z = Vertex[VertexCount-1].z;
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}

		/*
		//앞쪽...
		Vertex[VertexCount].x   = int(firstPos.x);
		Vertex[VertexCount].y   = int(firstPos.y+SizeHeight*18);
		Vertex[VertexCount].z   = int(firstPos.z);
		Vertex[VertexCount].sDef_Color[0] = 255;
		Vertex[VertexCount].sDef_Color[1] = 255;
		Vertex[VertexCount].sDef_Color[2] = 255;
		Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+1].x = int(firstPos.x);
		Vertex[VertexCount+1].y = int(firstPos.y-SizeHeight*18);
		Vertex[VertexCount+1].z = int(firstPos.z);
		Vertex[VertexCount+1].sDef_Color[0] = 255;
		Vertex[VertexCount+1].sDef_Color[1] = 255;
		Vertex[VertexCount+1].sDef_Color[2] = 255;
		Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		//꼬리 부분..
		Vertex[VertexCount+2].x = int(secondPos.x);
		Vertex[VertexCount+2].y = int(secondPos.y+SizeHeight*18);
		Vertex[VertexCount+2].z = int(secondPos.z);
		Vertex[VertexCount+2].sDef_Color[0] = 255;
		Vertex[VertexCount+2].sDef_Color[1] = 255;
		Vertex[VertexCount+2].sDef_Color[2] = 255;
		Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+3].x = int(secondPos.x);
		Vertex[VertexCount+3].y = int(secondPos.y-SizeHeight*18);
		Vertex[VertexCount+3].z = int(secondPos.z);
		Vertex[VertexCount+3].sDef_Color[0] = 255;
		Vertex[VertexCount+3].sDef_Color[1] = 255;
		Vertex[VertexCount+3].sDef_Color[2] = 255;
		Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		*/

		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount].v[2] = 0.0f;
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		TexLink[TexLinkCount+1].u[0] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[0] = 0.0f;
		TexLink[TexLinkCount+1].u[1] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[1] = 1.0f;
		TexLink[TexLinkCount+1].u[2] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[2] = 1.0f;

		//삼각형 컬링 때문에....
		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount+1;
		Face[FaceCount].Vertex[2] = VertexCount+2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;
	
		Face[FaceCount+1].Vertex[0] = VertexCount+2;
		Face[FaceCount+1].Vertex[1] = VertexCount+1;
		Face[FaceCount+1].Vertex[2] = VertexCount+3;
		Face[FaceCount+1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount+1].lpTexLink = &TexLink[TexLinkCount+1];
		Face[FaceCount+1].sum = 0;
		

		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
		
		/*
		firstPos.x = PosList[index].x;
		firstPos.y = PosList[index].y;
		firstPos.z = PosList[index].z; 
		
		secondPos.x = PosList[index+1].x;
		secondPos.y = PosList[index+1].y;
		secondPos.z = PosList[index+1].z;
		
		

		inVector.x = firstPos.x+secondPos.x;
		inVector.y = firstPos.y+secondPos.y;
		inVector.z = firstPos.z+secondPos.z;
		
		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;
		
		//앞쪽...
		Vertex[VertexCount].x   = outVector.x+firstPos.x;
		Vertex[VertexCount].y   = outVector.x+firstPos.y;
		Vertex[VertexCount].z   = outVector.x+firstPos.z;
		Vertex[VertexCount].sDef_Color[0] = 255;
		Vertex[VertexCount].sDef_Color[1] = 255;
		Vertex[VertexCount].sDef_Color[2] = 255;
		Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+1].x = inVector.x+firstPos.x;
		Vertex[VertexCount+1].y = inVector.y+firstPos.y;
		Vertex[VertexCount+1].z = inVector.z+firstPos.z;
		Vertex[VertexCount+1].sDef_Color[0] = 255;
		Vertex[VertexCount+1].sDef_Color[1] = 255;
		Vertex[VertexCount+1].sDef_Color[2] = 255;
		Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		//꼬리 부분..
		Vertex[VertexCount+2].x = outVector.x+secondPos.x;
		Vertex[VertexCount+2].y = outVector.y+secondPos.y;
		Vertex[VertexCount+2].z = outVector.z+secondPos.z;
		Vertex[VertexCount+2].sDef_Color[0] = 100;
		Vertex[VertexCount+2].sDef_Color[1] = 100;
		Vertex[VertexCount+2].sDef_Color[2] = 100;
		Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+3].x = inVector.x+secondPos.x;
		Vertex[VertexCount+3].y = inVector.y+secondPos.y;
		Vertex[VertexCount+3].z = inVector.z+secondPos.z;

		Vertex[VertexCount+3].sDef_Color[0] = 100;
		Vertex[VertexCount+3].sDef_Color[1] = 100;
		Vertex[VertexCount+3].sDef_Color[2] = 100;
		Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		*/


		/*
		//앞쪽...
		Vertex[VertexCount].x   = int(firstPos.x);
		Vertex[VertexCount].y   = int(firstPos.y);
		Vertex[VertexCount].z   = int(firstPos.z-SizeHeight*18);
		Vertex[VertexCount].sDef_Color[0] = 255;
		Vertex[VertexCount].sDef_Color[1] = 255;
		Vertex[VertexCount].sDef_Color[2] = 255;
		Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+1].x = int(firstPos.x);
		Vertex[VertexCount+1].y = int(firstPos.y);
		Vertex[VertexCount+1].z = int(firstPos.z+SizeHeight*18);
		Vertex[VertexCount+1].sDef_Color[0] = 255;
		Vertex[VertexCount+1].sDef_Color[1] = 255;
		Vertex[VertexCount+1].sDef_Color[2] = 255;
		Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		//꼬리 부분..
		Vertex[VertexCount+2].x = int(secondPos.x);
		Vertex[VertexCount+2].y = int(secondPos.y);
		Vertex[VertexCount+2].z = int(secondPos.z-SizeHeight*18);
		Vertex[VertexCount+2].sDef_Color[0] = 100;
		Vertex[VertexCount+2].sDef_Color[1] = 100;
		Vertex[VertexCount+2].sDef_Color[2] = 100;
		Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		
		Vertex[VertexCount+3].x = int(secondPos.x);
		Vertex[VertexCount+3].y = int(secondPos.y);
		Vertex[VertexCount+3].z = int(secondPos.z+SizeHeight*18);
		Vertex[VertexCount+3].sDef_Color[0] = 100;
		Vertex[VertexCount+3].sDef_Color[1] = 100;
		Vertex[VertexCount+3].sDef_Color[2] = 100;
		Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		*/
		
		/*
		//Texture 좌표 관련 초기화...
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount].v[2] = 0.0f;
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		TexLink[TexLinkCount+1].u[0] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[0] = 0.0f;
		TexLink[TexLinkCount+1].u[1] = (1.0f)*(float(index)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[1] = 1.0f;
		TexLink[TexLinkCount+1].u[2] = (1.0f)*(float(index+1)/float(PosListCount-1));
		TexLink[TexLinkCount+1].v[2] = 1.0f;


		//삼각형 컬링 때문에....
		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount+1;
		Face[FaceCount].Vertex[2] = VertexCount+2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;
	
		Face[FaceCount+1].Vertex[0] = VertexCount+2;
		Face[FaceCount+1].Vertex[1] = VertexCount+1;
		Face[FaceCount+1].Vertex[2] = VertexCount+3;
		Face[FaceCount+1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount+1].lpTexLink = &TexLink[TexLinkCount+1];
		Face[FaceCount+1].sum = 0;
		
		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
		*/
		
	}
	return TRUE;
}

void HoEffectShield::Init()
{
	StartFlag = FALSE;
}

int HoEffectShield::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	
	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;
	//현재 찍을 Frame을 세팅한다..
	smMaterialGroup->SetMaterialAnimFrame( &smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()], 
	AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);
	
	//Camera각도 입력.
	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	
	/*
	Face2d.x = int(WorldX+LocalX);
	Face2d.y = int(WorldY+LocalY);
	Face2d.z = int(WorldZ+LocalZ);

	Face2d.r = int(CurrentBlendValue);
	Face2d.g = int(CurrentBlendValue);
	Face2d.b = int(CurrentBlendValue);
	Face2d.Transparency = (int)CurrentBlendValue; //hoEffectAnimationData.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].BlendValue;
	*/
	//뒤에 가물 가물 그림..
	//if(AddFace2D(&Face2d))
	//{
	
	//Camera각도 입력.
	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);
	

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();
	SumCount++;
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	BackBillBoard.Draw(x, y, z, ax, ay, az);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	if(ShieldType == SKILL_SHIELD2)
	{
		if(UnderPat.GetState())
			UnderPat.Draw(x, y, z, ax, ay, az);
	}
	
	return TRUE;
}


int HoEffectShield::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;
	
	//Animation 한번...
 	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount-1)
				CurrentFrame = 1;
			
			//Blend 값 설정...
			BlendStep = (AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].AlphaValue-CurrentBlendValue)/
				AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}
	
	

	WorldX = float(Character->pX);
	WorldY = float(Character->pY+3000);
	WorldZ = float(Character->pZ);
	
	if(ShieldType == SKILL_SHIELD1)
	{
		DirectionAngle.y += (ANGLE_360/60)&ANGCLIP;
		DirectionAngle.y = DirectionAngle.y&ANGCLIP;
		
		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
		POINT3D tempGeoResult;
		tempGeoResult.x = GeoResult_X;
		tempGeoResult.y = GeoResult_Y;
		tempGeoResult.z = GeoResult_Z;

		GetMoveLocation(tempGeoResult.x, tempGeoResult.y, tempGeoResult.z, DirectionAngle.x, 0, 0);
	
	
		GeoResult_Y += 4500;
		BackBillBoard.TranslateWorld(int(GeoResult_X+WorldX), int(GeoResult_Y+WorldY), int(GeoResult_Z+WorldZ));
		BackBillBoard.Main();
		
		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;


			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
			
			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));

			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
			
		}
		
		static int particleCount= 0;
		if(particleCount >= 25)
		{
			StartEffect(int(GeoResult_X+WorldX), int(GeoResult_Y+WorldY), int(GeoResult_Z+WorldZ), EFFECT_SHIELD1_PARTICLE);
			particleCount = 0;
			
		}
		particleCount++;

		EndCount++;

		//ktj : 원본
		//if(EndCount >= 75*70 || ((Character != NULL) && !(Character->dwDispAppSkill & SKILL_APPMASK_PHYSICAL_ABSORB)) )
		//if(EndCount >= 75*70 || (Character != NULL) )//&& !(Character->dwDispAppSkill & SKILL_APPMASK_PHYSICAL_ABSORB)) )

		//ktj : 나중에 원본으로 복원해야함에 주의할것.
		//if(EndCount >= 75*70)

		if(EndCount >= 150*70 || ((Character != NULL) && !(Character->dwDispAppSkill & SKILL_APPMASK_PHYSICAL_ABSORB)) )
		{
			if(Character != NULL)
					Character->HoSkillCode = 0;

			Init();
			for(int index = 0; index < CHR_IN_EFFECT_OBJECT_MAX; index++)
			{
				if(ChrInEffectObject[index].object == (HoEffectObject *)this)
				{
					ChrInEffectObject[index].object = NULL;
					break;
				}
			}
		}
	}	
	
	if(ShieldType == SKILL_SHIELD2)
	{
		static int shieldTwoCount = 0;
		if(UnderPat.GetState())
		{
			
			UnderPat.TranslateWorld(int(WorldX), int(WorldY-1000), int(WorldZ));
			UnderPat.Main();
		}

		if(shieldTwoCount >= 20)
		{
			StartChildEffect(int(WorldX), int(WorldY+3000), int(WorldZ), EFFECT_SHIELD2_PARTICLE, this);
			StartChildEffect(int(WorldX), int(WorldY-2000), int(WorldZ), EFFECT_SHIELD2_PARTICLE);
			shieldTwoCount = 0;
		}
		shieldTwoCount++;
		
		EndCount++;
		if(EndCount >= 150*70 || ((Character != NULL) && !(Character->dwDispAppSkill & SKILL_APPMASK_AUTOMATION)) )
		{
			if(Character != NULL)
					Character->HoSkillCode = 0;

			Init();
		}
	}
	
	return TRUE;
}

void HoEffectShield::SetUnderPat(smPAT3D *pat, int aniEnd)
{
	UnderPat.StartAni( (int)WorldX, (int)WorldY, (int)WorldZ, 0, 0, 0, pat, ANI_LOOP);
	UnderPat.AnimationEnd = aniEnd;
}

int HoEffectShield::Start(int x, int y, int z, int shieldType, int angle, int circleRadius, smCHAR *character)
{
	if(StartFlag || character == NULL)
		return FALSE;



	char iniName[256];
	
	ShieldType = shieldType;
	if(shieldType == SKILL_SHIELD1)
	{
		memset(iniName, 0,sizeof(iniName));
		strcpy(iniName, "Shield1.ini");

		//따라 다니는 콩알 탄..
		BackBillBoard.StartBillRect(x, y, z, "ShieldParticle1.ini", ANI_LOOP);
	}
	else if(shieldType == SKILL_SHIELD2)
	{
		memset(iniName, 0,sizeof(iniName));
		strcpy(iniName, "Shield2.ini");
	}
	
	EndCount = 0;
	Character = character;
	Character->HoSkillCode = SKILL_SHIELD1;
	
	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;
	DirectionAngle.x = angle;
	DirectionAngle.y = 0;
	DirectionAngle.z = angle;

	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == FALSE)
		return FALSE;
	Face2d.MatNum = AnimDataMgr.GetMaterialNum(AniDataIndex);
	if(Face2d.MatNum == -1)
		return FALSE;
	
	WorldX = (float)x;
	WorldY = (float)(Character->pY+3000);
	WorldZ = (float)z;
	
	LocalX = 0;
	LocalY = 0;
	LocalZ = (float)circleRadius;
	
	StartFlag = TRUE;
	SizeWidth  = 20;
	SizeHeight = 20;

	Face2d.x = (int)(WorldX+LocalX);
	Face2d.y = (int)(WorldX+LocalY);
	Face2d.z = (int)(WorldX+LocalZ);
	Face2d.TexRect.left = 0;
	Face2d.TexRect.top = 0;
	Face2d.TexRect.right = 1;
	Face2d.TexRect.bottom = 1;
	Face2d.width  = (int)SizeWidth<<FLOATNS;
	Face2d.height = (int)SizeHeight<<FLOATNS;
	
	Face2d.Transparency = 255;
	Face2d.r = 255;
	Face2d.g = 255;
	Face2d.b = 255;
	
	CurrentBlendValue = (int)AnimDataMgr.SequenceDataBuffer[AniDataIndex].StartBlendValue;
	
	if(AnimDataMgr.SequenceDataBufferCount > 1)
	{
		
		CurrentBlendValue = AnimDataMgr.SequenceDataBuffer[AniDataIndex].StartBlendValue;
		BlendStep = (AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].AlphaValue-CurrentBlendValue)/
								AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay;
	}
	else
	{
		BlendStep = 0;
	}
	
	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_SHADOW;
	
	Face2d.width  = (int)(SizeWidth)<<FLOATNS;
	Face2d.height = (int)(SizeHeight)<<FLOATNS;
	
	

	return TRUE;
}

/*
BOOL HoEffectShield::AddFace2D(smFACE2D *face)
{
	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[ SMC_A ] = face->Transparency;
	sColor[ SMC_R ] = face->r;
	sColor[ SMC_G ] = face->g;
	sColor[ SMC_B ] = face->b;
	

	for(int index = 0; index < PosListCount-1; index++)
	{
		POINT3D destPos;
		destPos.x = PosList[index].x+WorldX;
		destPos.y = PosList[index].y+WorldY;
		destPos.z = PosList[index].z+WorldZ; 
		
		POINT3D currentPos;
		currentPos.x = PosList[index+1].x+WorldX;
		currentPos.y = PosList[index+1].y+WorldY;
		currentPos.z = PosList[index+1].z+WorldZ;
		
		if(GetCameraCoord(currentPos) == FALSE)
			return FALSE;

		if(GetCameraCoord(destPos) == FALSE)
			return FALSE;
		
		float dx    = float(destPos.x - currentPos.x);
		float dy    = float(destPos.y - currentPos.y);
		float oolen = (float)sqrt(dx*dx+dy*dy);

		dx = dx/oolen*(SizeHeight*10); //넓이.
		dy = dy/oolen*(SizeHeight*10);

		D3DVECTOR persp;
		persp.x = -dy;
		persp.y = +dx;
		persp.z = 0;
		
		//if (abs((int)dx) > 1.0f) currentPos.x -= (int)dx;
		//if (abs((int)dy) > 1.0f) currentPos.y -= (int)dy;

		v[0] = smRender.AddRendVertex ( int(destPos.x-persp.x), int(destPos.y-persp.y), int(destPos.z), sColor );
		v[1] = smRender.AddRendVertex ( int(destPos.x+persp.x), int(destPos.y+persp.y), int(destPos.z), sColor );
		v[3] = smRender.AddRendVertex ( int(currentPos.x+persp.x), int(currentPos.y+persp.y), int(currentPos.z), sColor );
		v[2] = smRender.AddRendVertex ( int(currentPos.x-persp.x), int(currentPos.y-persp.y), int(currentPos.z), sColor );
		
		
		//첫번째 폴리곤 ( 1 - 2 - 3 );
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = face->MatNum ;		//메트리얼 복사
		rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
		rf->lpTexLink  = 0;

		face->TexRect.left   = float(index/PosListCount*index);
		face->TexRect.top    = 0;
		face->TexRect.right  = float(index/PosListCount*index+index/PosListCount);
		face->TexRect.bottom = 1;

	//	Face2d.TexRect.left = 0;
//		Face2d.TexRect.top = 0;
//		Face2d.TexRect.right = 1;
//		Face2d.TexRect.bottom = 1;

		//텍스쳐 연결
		smRender.AddRendTempTexLink( rf , 0,	face->TexRect.left , face->TexRect.bottom,
									face->TexRect.right , face->TexRect.bottom,
									face->TexRect.left , face->TexRect.top );


		//두번째 폴리곤 ( 2 - 4 - 3 );
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[1];
		rf->lpRendVertex[1] = v[3];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = face->MatNum ;		//메트리얼 복사
		rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
		rf->lpTexLink  = 0;

		//텍스쳐 연결
		smRender.AddRendTempTexLink( rf , 0,	face->TexRect.right , face->TexRect.bottom,
												face->TexRect.right , face->TexRect.top,
												face->TexRect.left , face->TexRect.top );
	}
	return TRUE;
}
*/

HoEffectPower::HoEffectPower()
{
	StartFlag = FALSE;
}

HoEffectPower::~HoEffectPower()
{

}

											//ktj : sw는 삽입함
int HoEffectPower::Start(int x, int y, int z,  int sw,  int aniType, smCHAR *character)
{
	//ktj : 원본
	//char *iniName = "Power1.ini";


	//ktj : 새로 삽입함 ================= start
	char iniName[32] = {0,};
	if(sw==1) {
		strcpy(iniName, "Power1.ini");		//MONSTER_PIGON_POWER1	: 새로만든것
	}
	else {
		strcpy(iniName, "Power2.ini");		//MONSTER_PIGON_POWER2	: 원래있던것
	}
	Skill_n = sw;
	//==================================  end




	//if(StartFlag || character == NULL)
		//return FALSE;
	Character = character;

	//if(Character != NULL)
		//BackBillBoard.StartBillRect(x, y, z, iniName, aniType);
	//else
	BackBillBoard.StartBillRect(x, y, z, iniName, aniType);
	
	StartFlag = TRUE;
	WorldX = (float)x;
	WorldY = (float)y;
	WorldZ = (float)z;

	LocalX = 0.f;
	LocalY = 0.f;
	LocalZ = 0.f;

	return TRUE;
}


int HoEffectPower::Main()
{
	if(StartFlag)
	{
		BackBillBoard.Main();
		
		/*
		if(Character != NULL)
		{
			WorldX = float(Character->pX);
			WorldY = float(Character->pY+10000);
			WorldZ = float(Character->pZ);
			
			BackBillBoard.Move( int(WorldX), int(WorldY), int(WorldZ));
		}
		*/

		BackBillBoard.TranslateWorld( int(WorldX), int(WorldY), int(WorldZ));
		static int count;
		if(count > 5)
		{
			count = 0;

			
			//ktj : 원본임.
			/*
			StartEffectMonster(int(WorldX), int(WorldY), int(WorldZ), MONSTER_PIGON_PARTICLE1);

			//StartEffect(int(WorldX), int(WorldY), int(WorldZ), EFFECT_FIRE1_PARTICLE);
			*/

			
			
			//ktj : 새로 만들어넣음.
			if(Skill_n == 1) {
				StartEffectMonster(int(WorldX), int(WorldY), int(WorldZ), MONSTER_PIGON_PARTICLE1);
			}
			else {
				StartEffectMonster(int(WorldX), int(WorldY), int(WorldZ), MONSTER_PIGON_PARTICLE2);
			}
			

		}
		count++;

		if(BackBillBoard.GetState() == FALSE)
			StartFlag = FALSE;
	}

	return TRUE;
}


int HoEffectPower::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag)
	{
		BackBillBoard.Draw(x, y, z, ax, ay, az);
	}
	return TRUE;
}

HoEffectHitLine::HoEffectHitLine()
{
	AniDataIndex = -1;
	StartFlag = FALSE;
	CurrentFrame = 0;


	delayCount = 0;
}

HoEffectHitLine::~HoEffectHitLine()
{

}


//#define KTJ_D2

#ifndef KTJ_D2

//ktj : 원본임.
int HoEffectHitLine::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;
	
	//Animation 한번...
	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount-1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}
	
	//ktj : 클라스변수로이동
	//static int delayCount = 0;
	if(DirectionAngle.y >= ANGLE_360)
	{
		delayCount++;

		CurrentBlendValue-= 30;
		if(delayCount > 5)
		{

			//ktj : 토네이도돌고난후 터지는부분.

			//ktj : 새로넣음.
			if(Skill_n == SKILL_TORNADO) {
				StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), 0, 0, 0, SKILL_GREAT_SMASH);
			}
			else {
				StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), 0, 0, 0, SKILL_GREAT_SMASH2);
			}

			StartFlag = FALSE;
			delayCount = 0;
		}
	}
	else
	{
		DirectionAngle.y += (ANGLE_360/30);
		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
			
			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
		}
	}
	return TRUE;
}

#else

int HoEffectHitLine::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;


	//ktj 새로넣음.
	cntM++;		

	
	//Animation 한번...
	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount-1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}
	
	//static int delayCount = 0;
	//if(DirectionAngle.y >= ANGLE_360)
	if(cntM> 5)
	{
		cntM = 0;

		delayCount++;

		CurrentBlendValue-= 30;
		if(delayCount > 5)
		{

			
			//ktj : 토네이도돌고난후 터지는부분.

			//ktj : 새로넣음.
			if(Skill_n == SKILL_TORNADO) {
				StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), 0, 0, 0, SKILL_GREAT_SMASH);
			}
			else {
				StartSkill(int(WorldX+LocalX), int(WorldY+LocalY), int(WorldZ+LocalZ), 0, 0, 0, SKILL_GREAT_SMASH2);
			}
			


			StartFlag = FALSE;
			delayCount = 0;
		}
	}
	else
	{
		//ktj : 고침.
		//if(cnt0==0)
			//DirectionAngle.y += (ANGLE_360/30);
		//else 
			//DirectionAngle.y -= (ANGLE_360/30);


		if(cnt0==0)DirectionAngle.y += (ANGLE_360/30);
		
		//cnt0 &= 1;



		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);

		//GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, DirectionAngle.y, 0, 0);
		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			/*
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
			*/
			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;

			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX-1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;


			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;
		}


		if(cnt0==0) {
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
		}
		else {

			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;
		}



		cnt0++;
	}

	WorldX += (int)Vx;
	WorldY += (int)Vy;
	WorldZ += (int)Vz;

	return TRUE;
}
#endif




/*

int HoEffectTracker::Main()
{
	if(StartFlag == FALSE)
		return FALSE;

	POINT3D currentPos;
	currentPos.x = int(WorldX+LocalX);
	currentPos.y = int(WorldY+LocalY);
	currentPos.z = int(WorldZ+LocalZ);

	//추적 하는 방향의 백터를 구한다.
	float vx = float(DestPos.x-currentPos.x);
	float vy = float(DestPos.y-currentPos.y);
	float vz = float(DestPos.z-currentPos.z);
	
	float length = vx*vx+vy*vy+vz+vz;
	if( (SkillCode == MONSTER_PIGON_SHOT1) ||
		(SkillCode == MONSTER_WEB_SHOT1) ||
		(SkillCode == MONSTER_IMP_SHOT1) || 
		(SkillCode == MONSTER_MEPHIT_SHOT1) ||
		//ktj : 추가
		(SkillCode == MONSTER_MEPHIT_SHOT2) ||
		//ktj : 추가함.
		(SkillCode == MONSTER_IMP_SHOT2) || (SkillCode == MONSTER_IMP_SHOT3)   )

	{
		
		if(EffectObj)
		{
			//ktj : 클라스변수로교체함.
			//static int	liveCount = 0;
			//static BOOL	liveFlag = FALSE; 

			if(length < 2000*2000)
				liveFlag = TRUE;
				
			if(liveFlag)
				liveCount++;

			if(length < 1000*1000)
			{
				if(SkillCode == MONSTER_WEB_SHOT1)
				{
					EffectObj->SetState(FALSE);
					StartFlag = FALSE;
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_WEB_HIT1);
				}
			}

			if(length < 800*800 || liveCount > 4)
			{
				//ktj : 임시
				if(SkillCode == MONSTER_PIGON_SHOT1)
				{
					EffectObj->SetState(FALSE);
					StartFlag = FALSE;
					StartEffect( currentPos.x, currentPos.y, currentPos.z, EFFECT_FIRE_HIT2 );
					esPlaySound( esSOUND_FIGON_IMPACT , GetDistVolume(currentPos.x, currentPos.y, currentPos.z) );
				}

				
				liveCount = 0;
				liveFlag = FALSE;
				StartFlag = FALSE;
				EffectObj->SetState(FALSE);
				
				
				
				if(SkillCode == MONSTER_IMP_SHOT1) 
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_IMP_HIT1);
				//ktj : 추가
				if(SkillCode == MONSTER_IMP_SHOT2)
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_IMP_HIT2);

				//ktj : 추가
				if(SkillCode == MONSTER_IMP_SHOT3)
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_IMP_HIT3);
				


				if(SkillCode == MONSTER_MEPHIT_SHOT1)
				{
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_MEPHIT_HIT1);
				}

				if(SkillCode == MONSTER_MEPHIT_SHOT2)
				{
					StartEffectMonster( currentPos.x, currentPos.y, currentPos.z, MONSTER_MEPHIT_HIT2);
				}
			}					



			


		}
	}
	
	//ktj : 클라스변수로교체함.
	//static int sparkCount = 0;
	if( (SkillCode == SKILL_SPARK))
	{
		if(length < 1000*1000)
		{
			StartFlag = FALSE;
			StartEffect(currentPos.x, currentPos.y, currentPos.z, EFFECT_SPARK2, Level);

			//전기 소리
			SkillPlaySound( SKILL_SOUND_SKILL_SPARK3 , currentPos.x, currentPos.y, currentPos.z );

			
		}

		if(sparkCount >= 3)
		{
			sparkCount = 0;
			StartChildEffect(currentPos.x, currentPos.y , currentPos.z, EFFECT_SPARK1, this);
		}

		sparkCount++;
	}
	

	//ktj : 추가==============================================================================start
	//ktj : 꼬리에 불붙어 날아가는것을 표현하기위해 넣은것으로 불덩이를 따라서 연기가피어오름
	//ktj : 클라스변수로교체함.
	//static int IMP_SHOT2_liveCount = 0;
	if( SkillCode == MONSTER_IMP_SHOT2 )
	{
		IMP_SHOT2_liveCount++;
		IMP_SHOT2_liveCount &= 0x03;

		if(IMP_SHOT2_liveCount ==0)
			StartEffectMonster(currentPos.x, currentPos.y, currentPos.z, MONSTER_PIGON_PARTICLE1);
	}

	//ktj : 클라스변수로교체함.
	//static int IMP_SHOT3_liveCount = 0;
	if( SkillCode == MONSTER_IMP_SHOT3 )
	{
		IMP_SHOT3_liveCount++;
		IMP_SHOT3_liveCount &= 0x03;

		if(IMP_SHOT3_liveCount ==0)
			StartEffectMonster(currentPos.x, currentPos.y, currentPos.z, MONSTER_PIGON_PARTICLE1_BLH);
	}
	//ktj : 추가==============================================================================end




	if(EffectObj)
		EffectObj->TranslateWorld(currentPos.x, currentPos.y, currentPos.z);

	if(SkillCode == SKILL_METEO)
	{
		int mapY1, mapY2;
		if(smGameStage[0])
		{
			mapY1 = smGameStage[0]->GetHeight(currentPos.x, currentPos.z);
		}
		if(smGameStage[1])
		{
			mapY2 = smGameStage[1]->GetHeight(currentPos.x, currentPos.z);
		}

		if(smGameStage[0] && smGameStage[1])
			if (mapY1 < mapY2) mapY1 = mapY2;
		if(smGameStage[0] == NULL && smGameStage[1])
			mapY1 = mapY2;
		
		//맵과 총돌을 했는지 검사한다.
		if(mapY1 > currentPos.y+Vy)
		{
			StartFlag = FALSE;
			currentPos.y = mapY1;
			EffectObj->SetState(FALSE);
			StartEffect( currentPos.x, currentPos.y, currentPos.z, EFFECT_FIRE_HIT2);
		}
	}
	WorldX += (int)Vx;
	WorldY += (int)Vy;
	WorldZ += (int)Vz;
	
	return TRUE;
}

int HoEffectTracker::Start(POINT3D currentPos, POINT3D destPos, int skillCode, HoEffectObject *effectObj, int level)
{
	StartFlag = TRUE;
	WorldX = (float)currentPos.x;
	WorldY = (float)currentPos.y;
	WorldZ = (float)currentPos.z;
	
	DestPos.x = destPos.x;
	DestPos.y = destPos.y;
	DestPos.z = destPos.z;

	LocalX = 0.f;
	LocalY = 0.f;
	LocalZ = 0.f;
	
	SkillCode = skillCode;

	Level = 1;
	if(SkillCode == SKILL_METEO)
	{
		Vx = 0.f;
		Vy = 0.f;
		Vz = 0.f;
		
		EffectObj = effectObj;

		POINT3D currentPos;
		currentPos.x = int(WorldX+LocalX);
		currentPos.y = int(WorldY+LocalY);
		currentPos.z = int(WorldZ+LocalZ);
		
		//추적 하는 방향의 백터를 구한다.
		float vx = float(DestPos.x-currentPos.x);
		float vy = float(DestPos.y-currentPos.y);
		float vz = float(DestPos.z-currentPos.z);
		
		float length = (float)sqrt(vx*vx+vz*vz+vy*vy);
		Vx += vx/length*2000;
		Vy += vy/length*2000;
		Vz += vz/length*2000;

	}
	
	//ktj : 추가됨
	//if( (SkillCode == MONSTER_PIGON_SHOT1) || (SkillCode == MONSTER_WEB_SHOT1)
	//	|| (SkillCode == MONSTER_IMP_SHOT1) || (SkillCode == MONSTER_MEPHIT_SHOT1) )
	if( (SkillCode == MONSTER_PIGON_SHOT1) || (SkillCode == MONSTER_WEB_SHOT1)
		|| (SkillCode == MONSTER_IMP_SHOT1) || (SkillCode == MONSTER_MEPHIT_SHOT1) 
		|| (SkillCode == MONSTER_MEPHIT_SHOT2)	//ktj : 추가
		|| (SkillCode == MONSTER_IMP_SHOT2)		//ktj : 추가
		|| (SkillCode == MONSTER_IMP_SHOT3)		//ktj : 추가
		)
	{
		Vx = 0.f;
		Vy = 0.f;
		Vz = 0.f;
		
		EffectObj = effectObj;

		POINT3D currentPos;
		currentPos.x = int(WorldX+LocalX);
		currentPos.y = int(WorldY+LocalY);
		currentPos.z = int(WorldZ+LocalZ);
		
		//추적 하는 방향의 백터를 구한다.
		float vx = float(DestPos.x-currentPos.x);
		float vy = float(DestPos.y-currentPos.y);
		float vz = float(DestPos.z-currentPos.z);
		
		float length = (float)sqrt(vx*vx+vz*vz+vy*vy);
		
		if(SkillCode == MONSTER_PIGON_SHOT1)
		{
			Vx += vx/length*1500;
			Vy += vy/length*1500;
			Vz += vz/length*1500;
		}
		//ktj : 추가함.
		//else if(SkillCode == MONSTER_IMP_SHOT1 || SkillCode == MONSTER_MEPHIT_SHOT1)
		else if(SkillCode == MONSTER_IMP_SHOT1 || SkillCode == MONSTER_MEPHIT_SHOT1

			|| SkillCode == MONSTER_MEPHIT_SHOT2	//ktj : 추가

			|| (SkillCode == MONSTER_IMP_SHOT2)
			)//ktj : 추가

		{
			Vx += vx/length*1300;
			Vy += vy/length*1300;
			Vz += vz/length*1300;
		}
		//ktj : 추가
		else if(SkillCode == MONSTER_IMP_SHOT3)
		{
			
			Vx += vx/length*1000;
			Vy += vy/length*1000;
			Vz += vz/length*1000;
			
		}
		else
		{
			Vx += vx/length*800;
			Vy += vy/length*800;
			Vz += vz/length*800;
		}

	}
	
	if( SkillCode == SKILL_SPARK)
	{
		Vx = 0.f;
		Vy = 0.f;
		Vz = 0.f;
		
		POINT3D currentPos;
		currentPos.x = int(WorldX+LocalX);
		currentPos.y = int(WorldY+LocalY);
		currentPos.z = int(WorldZ+LocalZ);
		
		//추적 하는 방향의 백터를 구한다.
		float vx = float(DestPos.x-currentPos.x);
		float vy = float(DestPos.y-currentPos.y);
		float vz = float(DestPos.z-currentPos.z);
		
		float length = (float)sqrt(vx*vx+vz*vz+vy*vy);	
		Vx += vx/length*1600;
		Vy += vy/length*1600;
		Vz += vz/length*1600;

		Level = level;
	}

	return TRUE;
}
*/


int HoEffectHitLine::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	
	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;
	//현재 찍을 Frame을 세팅한다..
	smMaterialGroup->SetMaterialAnimFrame( &smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()], 
	AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);
	
	//Camera각도 입력.
	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	
	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);
	
	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	smRender.RenderD3D();
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	SumCount++;
	return TRUE;
}

int HoEffectHitLine::CreatePathFace()
{
	
	//Vertex 값 초기화..
	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;
	
	POINT3D firstPos;
	POINT3D secondPos;
	
	for(int index = 0; index < PosListCount-1; index++)
	{
		firstPos.x = int(PosList[index].x+WorldX);
		firstPos.y = int(PosList[index].y+WorldY);
		firstPos.z = int(PosList[index].z+WorldZ); 
		
		secondPos.x = int(PosList[index+1].x+WorldX);
		secondPos.y = int(PosList[index+1].y+WorldY);
		secondPos.z = int(PosList[index+1].z+WorldZ);
		
		int blendStep = CurrentBlendValue/((PosListCount-1)+10);
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x+PosList[index+1].x);
		inVector.y = float(PosList[index].y+PosList[index+1].y);
		inVector.z = float(PosList[index].z+PosList[index+1].z);
	
		double length = sqrt(inVector.x*inVector.x+inVector.y*inVector.y+inVector.z*inVector.z);
		inVector.x = float(inVector.x/length);
		inVector.y = float(inVector.y/length);
		inVector.z = float(inVector.z/length);
		
		
		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;
		
		if(index == 0)
		{
			//앞쪽...
			Vertex[VertexCount].x   = int(firstPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount].y   = int(firstPos.y+outVector.y*SizeHeight*20+5000);
			Vertex[VertexCount].z   = int(firstPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = int(firstPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+1].y = int(firstPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+1].z = int(firstPos.z+inVector.z*SizeHeight*20);
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20+5000);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}
		else
		{
			//앞쪽...
			Vertex[VertexCount].x   = Vertex[VertexCount-2].x;
			Vertex[VertexCount].y   = Vertex[VertexCount-2].y;
			Vertex[VertexCount].z   = Vertex[VertexCount-2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = Vertex[VertexCount-1].x;
			Vertex[VertexCount+1].y = Vertex[VertexCount-1].y;
			Vertex[VertexCount+1].z = Vertex[VertexCount-1].z;
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20+5000);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}

		
		
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		TexLink[TexLinkCount+1].u[0] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[0] = 0.0f;
		TexLink[TexLinkCount+1].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount+1].v[1] = 1.0f;
		TexLink[TexLinkCount+1].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[2] = 1.0f;
		
		/*
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		
		TexLink[TexLinkCount].u[0] = 0.0f;
		TexLink[TexLinkCount].v[0] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].u[1] = 1.0f;
		TexLink[TexLinkCount].v[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].u[2] = 0.0f;
		TexLink[TexLinkCount].v[2] = (1.0f)*(float(index+1)/float(PosListCount));
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		
		TexLink[TexLinkCount+1].u[0] = 0.0f;
		TexLink[TexLinkCount+1].v[0] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].u[1] = 1.0f;
		TexLink[TexLinkCount+1].v[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount+1].u[2] = 1.0f;
		TexLink[TexLinkCount+1].v[2] = (1.0f)*(float(index+1)/float(PosListCount));
		*/

		//삼각형 컬링 때문에....
		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount+1;
		Face[FaceCount].Vertex[2] = VertexCount+2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;
	
		Face[FaceCount+1].Vertex[0] = VertexCount+2;
		Face[FaceCount+1].Vertex[1] = VertexCount+1;
		Face[FaceCount+1].Vertex[2] = VertexCount+3;
		Face[FaceCount+1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount+1].lpTexLink = &TexLink[TexLinkCount+1];
		Face[FaceCount+1].sum = 0;
		

		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}
	
	return TRUE;
}


//ktj : sw를 넣어 "SkillTornado.ini", "SkillTornado2.ini"등을 선택하도록고침.
//x, y, z
int HoEffectHitLine::Start(int x, int y, int z, int destX, int destY, int destZ, int sw)
{
	//ktj : 원본
	//char *iniName = "SkillTornado.ini";

	//ktj : 새로 넣음.
	cntM=0;
	cnt0=0;


	char iniName[32]={0,};
	if(sw==0) {
		strcpy(iniName,"SkillTornado.ini");
	}
	if(sw==1) {
		strcpy(iniName,"SkillTornado2.ini");
	}

	
	if(sw==2) {
		strcpy(iniName,"SkillTornado3.ini");	//SKILL_TORNADO3
	}
	


	//char *iniName = "ContinueStun.ini";
	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;

	WorldX = float(x);
	WorldY = float(y);
	WorldZ = float(z);

	LocalX = float(destX-x);
	LocalY = float(destY-y);
	LocalZ = float(destZ-z);




	//ktj : 새로 넣음. ========================start

	if(sw==2) {
		DestPos.x = destX;
		DestPos.y = destY;
		DestPos.z = destZ;
		LocalX = 0.f;
		LocalY = 0.f;
		LocalZ = 0.f;

		Vx = 0.f;
		Vy = 0.f;
		Vz = 0.f;
		
		POINT3D currentPos;
		currentPos.x = int(WorldX+LocalX);
		currentPos.y = int(WorldY+LocalY);
		currentPos.z = int(WorldZ+LocalZ);
		
		//추적 하는 방향의 백터를 구한다.
		float vx = float(DestPos.x-currentPos.x);
		float vy = float(DestPos.y-currentPos.y);
		float vz = float(DestPos.z-currentPos.z);
		
		float length = (float)sqrt(vx*vx+vz*vz+vy*vy);
		
		Vx += vx/length*1500;
		Vy += vy/length*1500;
		Vz += vz/length*1500;
	}












	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;
	
	DirectionAngle.x = 0;
	DirectionAngle.y = 0;
	DirectionAngle.z = 0;
	
	CurrentBlendValue = 200;
	TimeCount = 0;
	CurrentFrame = 0;
	SizeHeight = 170;
	StartFlag = TRUE;

//	EndCount = 0;

	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_SHADOW;
	return TRUE;
}


HoEffectStun::HoEffectStun()
{
	//StartFlag = FALSE;
	//Character = NULL;
	StartFlag = FALSE;
	Character = NULL;
	
}

HoEffectStun::~HoEffectStun()
{

}


int HoEffectStun::Start(int worldX, int worldY, int worldZ, smCHAR *character)
{

	/*
	StartFlag = TRUE;

	WorldX = worldX;
	WorldY = worldY;
	WorldZ = worldZ;

	LocalX = 5000;
	LocalY = 0;
	LocalZ = 0;
	
	Character = character;
	//따라 다니는 콩알 탄..
	BackBillBoard.StartBillRect(worldX, worldY, worldZ, "ContinueStun.ini", ANI_LOOP);
	
	RotateAngle.x = 0;
	RotateAngle.y = 0;
	RotateAngle.z = 0;

	*/
	
	char *iniName = "ContinueStun.ini";
	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;

	WorldX = float(worldX);
	WorldY = float(worldY);
	WorldZ = float(worldZ);

	LocalX = 3000;
	LocalY = 0;
	LocalZ = 0;

	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;
	
	DirectionAngle.x = 0;
	DirectionAngle.y = 0;
	DirectionAngle.z = 0;
	
	CurrentBlendValue = 200;
	TimeCount = 0;
	CurrentFrame = 0;
	SizeHeight = 10;
	StartFlag = TRUE;

//	EndCount = 0;

	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType  = SMMAT_BLEND_SHADOW;
	
	Character = character;
	return TRUE;
}

int HoEffectStun::Main()
{
	/*
	GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, RotateAngle.y, 0);
	
	BackBillBoard.TranslateWorld(int(WorldX+GeoResult_X), int(WorldY+GeoResult_Y), int(WorldZ+GeoResult_Z));
	BackBillBoard.Main();
	
	RotateAngle.y += ANGLE_360/36;
	RotateAngle.y &= ANGCLIP;
	*/
	
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;
	
	//Animation 한번...
	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount-1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}
	
	/*
	static int delayCount = 0;
	if(DirectionAngle.y >= ANGLE_360)
	{
		delayCount++;

		CurrentBlendValue-= 30;
		if(delayCount > 5)
		{
			//StartSkill((WorldX+LocalX), (WorldY+LocalY), (WorldZ+LocalZ), 0, 0, 0, SKILL_GREAT_SMASH);
			StartFlag = FALSE;
			delayCount = 0;
		}
	}
	else
	{
	*/

	WorldX = float(Character->pX);
	WorldY = float(Character->pY+10000);
	WorldZ = float(Character->pZ);

	DirectionAngle.y += (ANGLE_360/50);
	GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
	if(PosListCount < STUN_POS_LIST_MAX)
	{
		POINT3D tempPosList[STUN_POS_LIST_MAX-1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = GeoResult_X;
		PosList[0].y = GeoResult_Y;
		PosList[0].z = GeoResult_Z;
		
		PosListCount++;
	}
	else
	{
		POINT3D tempPosList[STUN_POS_LIST_MAX-1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = GeoResult_X;
		PosList[0].y = GeoResult_Y;
		PosList[0].z = GeoResult_Z;
	}
	return TRUE;
}


int HoEffectStun::Draw(int x, int y, int z, int ax, int ay, int az)
{

	//BackBillBoard.Draw(x, y, z, ax, ay, az);

	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	
	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;
	//현재 찍을 Frame을 세팅한다..
	smMaterialGroup->SetMaterialAnimFrame( &smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()], 
	AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);
	
	//Camera각도 입력.
	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	
	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);
	
	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	smRender.RenderD3D();
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	SumCount++;

	return TRUE;
}

int HoEffectStun::CreatePathFace()
{
	
	//Vertex 값 초기화..
	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;
	
	POINT3D firstPos;
	POINT3D secondPos;
	
	for(int index = 0; index < PosListCount-1; index++)
	{
		firstPos.x = int(PosList[index].x+WorldX);
		firstPos.y = int(PosList[index].y+WorldY);
		firstPos.z = int(PosList[index].z+WorldZ); 
		
		secondPos.x = int(PosList[index+1].x+WorldX);
		secondPos.y = int(PosList[index+1].y+WorldY);
		secondPos.z = int(PosList[index+1].z+WorldZ);
		
		int blendStep = CurrentBlendValue/((PosListCount-1)+10);
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x+PosList[index+1].x);
		inVector.y = float(PosList[index].y+PosList[index+1].y);
		inVector.z = float(PosList[index].z+PosList[index+1].z);
	
		double length = sqrt(inVector.x*inVector.x+inVector.y*inVector.y+inVector.z*inVector.z);
		inVector.x = float(inVector.x/length);
		inVector.y = float(inVector.y/length);
		inVector.z = float(inVector.z/length);
		
		
		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;
		
		if(index == 0)
		{
			//앞쪽...
			Vertex[VertexCount].x   = int(firstPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount].y   = int(firstPos.y+outVector.y*SizeHeight*20+1400);
			Vertex[VertexCount].z   = int(firstPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = int(firstPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+1].y = int(firstPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+1].z = int(firstPos.z+inVector.z*SizeHeight*20);
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20+1400);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}
		else
		{
			//앞쪽...
			Vertex[VertexCount].x   = Vertex[VertexCount-2].x;
			Vertex[VertexCount].y   = Vertex[VertexCount-2].y;
			Vertex[VertexCount].z   = Vertex[VertexCount-2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+1].x = Vertex[VertexCount-1].x;
			Vertex[VertexCount+1].y = Vertex[VertexCount-1].y;
			Vertex[VertexCount+1].z = Vertex[VertexCount-1].z;
			Vertex[VertexCount+1].sDef_Color[0] = 255;
			Vertex[VertexCount+1].sDef_Color[1] = 255;
			Vertex[VertexCount+1].sDef_Color[2] = 255;
			Vertex[VertexCount+1].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			//꼬리 부분..
			Vertex[VertexCount+2].x = int(secondPos.x+outVector.x*SizeHeight*20);
			Vertex[VertexCount+2].y = int(secondPos.y+outVector.y*SizeHeight*20+1400);
			Vertex[VertexCount+2].z = int(secondPos.z+outVector.z*SizeHeight*20);
			Vertex[VertexCount+2].sDef_Color[0] = 255;
			Vertex[VertexCount+2].sDef_Color[1] = 255;
			Vertex[VertexCount+2].sDef_Color[2] = 255;
			Vertex[VertexCount+2].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
			
			Vertex[VertexCount+3].x = int(secondPos.x+inVector.x*SizeHeight*20);
			Vertex[VertexCount+3].y = int(secondPos.y+inVector.y*SizeHeight*20);
			Vertex[VertexCount+3].z = int(secondPos.z+inVector.z*SizeHeight*20);

			Vertex[VertexCount+3].sDef_Color[0] = 255;
			Vertex[VertexCount+3].sDef_Color[1] = 255;
			Vertex[VertexCount+3].sDef_Color[2] = 255;
			Vertex[VertexCount+3].sDef_Color[3] = (int)CurrentBlendValue-index*blendStep;
		}

		
		
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		TexLink[TexLinkCount+1].u[0] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[0] = 0.0f;
		TexLink[TexLinkCount+1].u[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount+1].v[1] = 1.0f;
		TexLink[TexLinkCount+1].u[2] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].v[2] = 1.0f;
		
		/*
		//Texture 좌표 관련 초기화...
		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		
		TexLink[TexLinkCount].u[0] = 0.0f;
		TexLink[TexLinkCount].v[0] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].u[1] = 1.0f;
		TexLink[TexLinkCount].v[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount].u[2] = 0.0f;
		TexLink[TexLinkCount].v[2] = (1.0f)*(float(index+1)/float(PosListCount));
		
		TexLink[TexLinkCount+1].hTexture = 0;
		TexLink[TexLinkCount+1].NextTex = 0;
		
		TexLink[TexLinkCount+1].u[0] = 0.0f;
		TexLink[TexLinkCount+1].v[0] = (1.0f)*(float(index+1)/float(PosListCount));
		TexLink[TexLinkCount+1].u[1] = 1.0f;
		TexLink[TexLinkCount+1].v[1] = (1.0f)*(float(index)/float(PosListCount));
		TexLink[TexLinkCount+1].u[2] = 1.0f;
		TexLink[TexLinkCount+1].v[2] = (1.0f)*(float(index+1)/float(PosListCount));
		*/

		//삼각형 컬링 때문에....
		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount+1;
		Face[FaceCount].Vertex[2] = VertexCount+2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;
	
		Face[FaceCount+1].Vertex[0] = VertexCount+2;
		Face[FaceCount+1].Vertex[1] = VertexCount+1;
		Face[FaceCount+1].Vertex[2] = VertexCount+3;
		Face[FaceCount+1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount+1].lpTexLink = &TexLink[TexLinkCount+1];
		Face[FaceCount+1].sum = 0;
		

		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}
	
	return TRUE;
}

