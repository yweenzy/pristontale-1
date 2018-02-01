
//#include "smLib3d\\smd3d.h"
#include "HoLinkHeader.h"
#include "HoNewParticleLinkHeader.h"

/*
#include "HoMinMax.h"
#include "HoNewParticle.h"
#include "HoNewParticleMgr.h"
*/

//HoNewParticleEmitter g_NewParticleEmitter;

void HoNewParticleEvent::ProcessPropEqualsValue(HoMinMax<float> &prop,
    std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
    std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // next token should be =
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  if (TokenIter->Type != Equals)
  {
	  OutputDebugString("Expecting = after property.");
      return;
  }

  // next token should be a number
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  HoNewParticleEmitterTokenizer::ProcessNumber(prop, TokenIter, EndIter);
}

void HoNewParticleEvent::ProcessPropEqualsValue(HoMinMax<D3DVECTOR> &prop,
    std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
    std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // next token should be =
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  if (TokenIter->Type != Equals)
  {
	  OutputDebugString("Expecting = after property.");
      return;
  }

  // next token should be a number
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  HoNewParticleEmitterTokenizer::ProcessVector(prop, TokenIter, EndIter);
}

void HoNewParticleEvent::ProcessPropEqualsValue(HoMinMax<D3DCOLORVALUE> &prop,
    std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
    std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // next token should be =
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  if (TokenIter->Type != Equals)
  {
	  OutputDebugString("Expecting = after property.");
	  return;
  }

  // next token should be a number
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  HoNewParticleEmitterTokenizer::ProcessColor(prop, TokenIter, EndIter);
}


bool HoNewParticleEvent_Size::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
    if (TokenIter->StrValue.compare("SIZE") == std::string::npos)
    {
        OutputDebugString("Expecting size!");
        return false;
    }
    ProcessPropEqualsValue(Size, TokenIter, EndIter);
    return(true);
}

bool HoNewParticleEvent_SizeExt::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
    if (TokenIter->StrValue.compare("SIZEEXT") == std::string::npos)
    {
        OutputDebugString("Expecting sizeext!");
        return false;
    }
    ProcessPropEqualsValue(SizeExt, TokenIter, EndIter);
    return(true);
}



bool HoNewParticleEvent_Color::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("COLOR") == std::string::npos)
  {
	  OutputDebugString("Expecting Color!");
	  return false;
  }
  
  ProcessPropEqualsValue(Color, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_RedColor::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("REDCOLOR") == std::string::npos)
  {
	  OutputDebugString("Expecting RedColor!");
      return false;
  }

  ProcessPropEqualsValue(RedColor, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_GreenColor::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("GREENCOLOR") == std::string::npos)
  {
	  OutputDebugString("Expecting GreenColor!");
      return false;
  }

  ProcessPropEqualsValue(GreenColor, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_BlueColor::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("BLUECOLOR") == std::string::npos)
  {
	  OutputDebugString("Expecting BlueColor!");
      return false;
  }
  ProcessPropEqualsValue(BlueColor, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_Alpha::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("ALPHA") == std::string::npos)
  {
	  OutputDebugString("Expecting Alpha!");
      return false;
  }
  ProcessPropEqualsValue(Alpha, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_Velocity::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
    if (TokenIter->StrValue.compare("VELOCITY") == std::string::npos)
    {
	    OutputDebugString("Expecting Velocity!");
        return false;
    }
    Flag = 0;
    TokenIter++;
    if (TokenIter->Type == Equals)
    {
        TokenIter++;
        if (TokenIter->Type == KeywordOutLength)
        {
            Flag = 1;
            TokenIter->Type = KeywordXYZ;
        }
        else if(TokenIter->Type == KeywordInLength)
        {
            Flag = 2;
            TokenIter->Type = KeywordXYZ;
        }
        TokenIter--;
        TokenIter--;
    }
    ProcessPropEqualsValue(Velocity, TokenIter, EndIter);
    if(Flag != 0)
    {
        if(TokenIter->Type == CloseParen)
        {
            if(TokenIter != EndIter)
                TokenIter++;
        }
    }

  return(true);
}

bool HoNewParticleEvent_VelocityX::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("VELOCITYX") == std::string::npos)
  {
	  OutputDebugString("Expecting VelocityX!");
      return false;
  }

  ProcessPropEqualsValue(VelocityX, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_VelocityY::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("VELOCITYY") == std::string::npos)
  {
	  OutputDebugString("Expecting VelocityY!");
      return false;
  }

  ProcessPropEqualsValue(VelocityY, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_VelocityZ::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("VELOCITYZ") == std::string::npos)
  {
	  OutputDebugString("Expecting VelocityZ!");
      return false;
  }

  ProcessPropEqualsValue(VelocityZ, TokenIter, EndIter);
  return(true);
}

bool HoNewParticleEvent_PartAngle::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("PARTANGLE") == std::string::npos)
  {
	  OutputDebugString("Expecting PartAngle!");
      return false;
  }

  ProcessPropEqualsValue(PartAngle, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  PartAngle.Min.x = (float)ANGLE_360/360.f*PartAngle.Min.x;
  PartAngle.Min.y = (float)ANGLE_360/360.f*PartAngle.Min.y;
  PartAngle.Min.z = (float)ANGLE_360/360.f*PartAngle.Min.z;

  PartAngle.Max.x = (float)ANGLE_360/360.f*PartAngle.Max.x;
  PartAngle.Max.y = (float)ANGLE_360/360.f*PartAngle.Max.y;
  PartAngle.Max.z = (float)ANGLE_360/360.f*PartAngle.Max.z;

  return(true);
}

bool HoNewParticleEvent_PartAngleX::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("PARTANGLEX") == std::string::npos)
  {
        OutputDebugString("Expecting PartAngleX!");
        return false;
  }
  ProcessPropEqualsValue(PartAngleX, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  PartAngleX.Min = (float)ANGLE_360/360.f*PartAngleX.Min;
  PartAngleX.Max = (float)ANGLE_360/360.f*PartAngleX.Max;

  return(true);
}

bool HoNewParticleEvent_PartAngleY::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("PARTANGLEY") == std::string::npos)
  {
	  OutputDebugString("Expecting PartAngleY!");
      return false;
  }

  ProcessPropEqualsValue(PartAngleY, TokenIter, EndIter);
  //360도 단위를 4096단위로 변환 한다.
  PartAngleY.Min = (float)ANGLE_360/360.f*PartAngleY.Min;
  PartAngleY.Max = (float)ANGLE_360/360.f*PartAngleY.Max;

  return(true);
}

bool HoNewParticleEvent_PartAngleZ::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("PARTANGLEZ") == std::string::npos)
  {
	  OutputDebugString("Expecting PartAngleZ!");
      return false;
  }
  ProcessPropEqualsValue(PartAngleZ, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  PartAngleZ.Min = (float)ANGLE_360/360.f*PartAngleZ.Min;
  PartAngleZ.Max = (float)ANGLE_360/360.f*PartAngleZ.Max;

  return(true);
}

bool HoNewParticleEvent_LocalAngle::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("LOCALANGLE") == std::string::npos)
  {
	  OutputDebugString("Expecting LocalAngle!");
      return false;
  }

  ProcessPropEqualsValue(LocalAngle, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  LocalAngle.Min.x = (float)ANGLE_360/360.f*LocalAngle.Min.x;
  LocalAngle.Min.y = (float)ANGLE_360/360.f*LocalAngle.Min.y;
  LocalAngle.Min.z = (float)ANGLE_360/360.f*LocalAngle.Min.z;

  LocalAngle.Max.x = (float)ANGLE_360/360.f*LocalAngle.Max.x;
  LocalAngle.Max.y = (float)ANGLE_360/360.f*LocalAngle.Max.y;
  LocalAngle.Max.z = (float)ANGLE_360/360.f*LocalAngle.Max.z;

  return(true);
}

bool HoNewParticleEvent_LocalAngleX::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("LOCALANGLEX") == std::string::npos)
  {
        OutputDebugString("Expecting LocalAngleX!");
        return false;
  }
  ProcessPropEqualsValue(LocalAngleX, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  LocalAngleX.Min = (float)ANGLE_360/360.f*LocalAngleX.Min;
  LocalAngleX.Max = (float)ANGLE_360/360.f*LocalAngleX.Max;

  return(true);
}

bool HoNewParticleEvent_LocalAngleY::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("LOCALANGLEY") == std::string::npos)
  {
	  OutputDebugString("Expecting LocalAngleY!");
      return false;
  }

  ProcessPropEqualsValue(LocalAngleY, TokenIter, EndIter);
  //360도 단위를 4096단위로 변환 한다.
  LocalAngleY.Min = (float)ANGLE_360/360.f*LocalAngleY.Min;
  LocalAngleY.Max = (float)ANGLE_360/360.f*LocalAngleY.Max;

  return(true);
}

bool HoNewParticleEvent_LocalAngleZ::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("LOCALANGLEZ") == std::string::npos)
  {
	  OutputDebugString("Expecting LocalAngleZ!");
      return false;
  }
  ProcessPropEqualsValue(LocalAngleZ, TokenIter, EndIter);

  //360도 단위를 4096단위로 변환 한다.
  LocalAngleZ.Min = (float)ANGLE_360/360.f*LocalAngleZ.Min;
  LocalAngleZ.Max = (float)ANGLE_360/360.f*LocalAngleZ.Max;

  return(true);
}

bool HoNewParticleEvent_EventTimer::ProcessTokenStream(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                             std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->StrValue.compare("EVENTTIMER") == std::string::npos)
  {
	  OutputDebugString("Expecting EventTimer!");
      return false;
  }

  ProcessPropEqualsValue(EventTimer, TokenIter, EndIter);
  return(true);
}

void HoNewParticleEvent_PartAngle::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.PartAngle = PartAngle.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    D3DVECTOR newAngle = static_cast<HoNewParticleEvent_PartAngle *>(NextFadeEvent)->GetPartAngle().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors

    part.PartAngleStep.x = (newAngle.x - part.PartAngle.x) / timedelta;
    part.PartAngleStep.y = (newAngle.y - part.PartAngle.y) / timedelta;
    part.PartAngleStep.z = (newAngle.z - part.PartAngle.z) / timedelta;
  }
}

void HoNewParticleEvent_PartAngleX::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.PartAngle.x = PartAngleX.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleX = static_cast<HoNewParticleEvent_PartAngleX *>(NextFadeEvent)->GetPartAngleX().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.PartAngleStep.x  = (newAngleX - part.PartAngle.x) / timedelta;
  }
}

void HoNewParticleEvent_PartAngleY::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.PartAngle.y = PartAngleY.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleY = static_cast<HoNewParticleEvent_PartAngleY *>(NextFadeEvent)->GetPartAngleY().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.PartAngleStep.y = (newAngleY - part.PartAngle.y) / timedelta;
  }
}

void HoNewParticleEvent_PartAngleZ::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.PartAngle.z = PartAngleZ.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleZ = static_cast<HoNewParticleEvent_PartAngleZ *>(NextFadeEvent)->GetPartAngleZ().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.PartAngleStep.z = (newAngleZ - part.PartAngle.z) / timedelta;
  }
}


void HoNewParticleEvent_LocalAngle::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.LocalAngle = LocalAngle.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    D3DVECTOR newAngle = static_cast<HoNewParticleEvent_LocalAngle *>(NextFadeEvent)->GetLocalAngle().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors

    part.LocalAngleStep.x = (newAngle.x - part.LocalAngle.x) / timedelta;
    part.LocalAngleStep.y = (newAngle.y - part.LocalAngle.y) / timedelta;
    part.LocalAngleStep.z = (newAngle.z - part.LocalAngle.z) / timedelta;
  }
}

void HoNewParticleEvent_LocalAngleX::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.PartAngle.x = LocalAngleX.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleX = static_cast<HoNewParticleEvent_LocalAngleX *>(NextFadeEvent)->GetLocalAngleX().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.LocalAngleStep.x  = (newAngleX - part.LocalAngle.x) / timedelta;
  }
}

void HoNewParticleEvent_LocalAngleY::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.LocalAngle.y = LocalAngleY.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleY = static_cast<HoNewParticleEvent_LocalAngleY *>(NextFadeEvent)->GetLocalAngleY().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.LocalAngleStep.y = (newAngleY - part.LocalAngle.y) / timedelta;
  }
}

void HoNewParticleEvent_LocalAngleZ::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.LocalAngle.z = LocalAngleZ.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newAngleZ = static_cast<HoNewParticleEvent_LocalAngleZ *>(NextFadeEvent)->GetLocalAngleZ().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.LocalAngleStep.z = (newAngleZ - part.LocalAngle.z) / timedelta;
  }
}


void HoNewParticleEvent_Size::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.Size = Size.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newvalue = static_cast<HoNewParticleEvent_Size *>(NextFadeEvent)->GetSize().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.SizeStep = (newvalue - part.Size) / timedelta;
  }
}

void HoNewParticleEvent_SizeExt::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.SizeExt = SizeExt.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newvalue = static_cast<HoNewParticleEvent_SizeExt *>(NextFadeEvent)->GetSize().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.SizeExtStep = (newvalue - part.SizeExt) / timedelta;
  }
}


void HoNewParticleEvent_Color::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Color = Color.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    D3DCOLORVALUE newcolor = static_cast<HoNewParticleEvent_Color *>(NextFadeEvent)->GetColor().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    // calculate color deltas to get us to the next fade event.
    part.ColorStep.r = (newcolor.r - part.Color.r) / timedelta;
    part.ColorStep.g = (newcolor.g - part.Color.g) / timedelta;
    part.ColorStep.b = (newcolor.b - part.Color.b) / timedelta;
    part.ColorStep.a = (newcolor.a - part.Color.a) / timedelta;
  }
}

void HoNewParticleEvent_RedColor::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Color.r = RedColor.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_RedColor *>(NextFadeEvent)->GetRedColor().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.ColorStep.r = (newvalue - part.Color.r) / timedelta;
  }

}

void HoNewParticleEvent_GreenColor::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Color.g = GreenColor.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_GreenColor *>(NextFadeEvent)->GetGreenColor().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.ColorStep.g = (newvalue - part.Color.g) / timedelta;
  }
}

void HoNewParticleEvent_BlueColor::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Color.b = BlueColor.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_BlueColor *>(NextFadeEvent)->GetBlueColor().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.ColorStep.b = (newvalue - part.Color.b) / timedelta;
  }
}

void HoNewParticleEvent_Alpha::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Color.a = Alpha.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_Alpha *>(NextFadeEvent)->GetAlpha().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
    part.ColorStep.a = (newvalue - part.Color.a) / timedelta;
  }
}

void HoNewParticleEvent_Velocity::DoItToIt(HoNewParticle &part)
{
    if (!IsFade())
    {
        if(Flag == 0)
	        part.Dir = Velocity.GetRandomNumInRange();
        else if(Flag == 1)
        {
            //D3DVECTOR newvalue = static_cast<HoNewParticleEvent_Velocity *>(NextFadeEvent)->GetVelocity().GetRandomNumInRange();
            D3DVECTOR newvalue = Velocity.GetRandomNumInRange();

            double length = sqrt(part.LocalPos.x*part.LocalPos.x+part.LocalPos.y*part.LocalPos.y+
                             part.LocalPos.z*part.LocalPos.z);
            part.Dir.x = (part.LocalPos.x/(float)length)*newvalue.x;
            part.Dir.y = (part.LocalPos.y/(float)length)*newvalue.x;
            part.Dir.z = (part.LocalPos.z/(float)length)*newvalue.x;
        }
        else if(Flag = 2)
        {
             //D3DVECTOR newvalue = static_cast<HoNewParticleEvent_Velocity *>(NextFadeEvent)->GetVelocity().GetRandomNumInRange();
            D3DVECTOR newvalue = Velocity.GetRandomNumInRange();

            double length = sqrt(part.LocalPos.x*part.LocalPos.x+part.LocalPos.y*part.LocalPos.y+
                             part.LocalPos.z*part.LocalPos.z);
            part.Dir.x = -((part.LocalPos.x/(float)length)*newvalue.x);
            part.Dir.y = -((part.LocalPos.y/(float)length)*newvalue.x);
            part.Dir.z = -((part.LocalPos.z/(float)length)*newvalue.x);
        }
    }

    if (NextFadeEvent)
    {
        D3DVECTOR newvalue = static_cast<HoNewParticleEvent_Velocity *>(NextFadeEvent)->GetVelocity().GetRandomNumInRange();

        float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
        if (timedelta == 0) timedelta = 1; // prevent divide by zero errors
        part.DirStep.x = (newvalue.x - part.Dir.x) / timedelta;
        part.DirStep.y = (newvalue.y - part.Dir.y) / timedelta;
        part.DirStep.z = (newvalue.z - part.Dir.z) / timedelta;
    }
}

void HoNewParticleEvent_VelocityX::DoItToIt(HoNewParticle &part)
{
  if (!IsFade())
	  part.Dir.x = VelocityX.GetRandomNumInRange();
  if (NextFadeEvent)
  {
    float newvalue = static_cast<HoNewParticleEvent_VelocityX *>(NextFadeEvent)->GetValue().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) 
		timedelta = 1; // prevent divide by zero errors
    part.DirStep.x = (newvalue - part.Dir.x) / timedelta;
  }
}

void HoNewParticleEvent_VelocityY::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Dir.y = VelocityY.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_VelocityY *>(NextFadeEvent)->GetValue().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) 
		timedelta = 1; // prevent divide by zero errors
    part.DirStep.y = (newvalue - part.Dir.y) / timedelta;
  }
}

void HoNewParticleEvent_VelocityZ::DoItToIt(HoNewParticle &part)
{
  if (!IsFade()) 
	  part.Dir.z = VelocityZ.GetRandomNumInRange();
  if (NextFadeEvent) 
  {
    float newvalue = static_cast<HoNewParticleEvent_VelocityZ *>(NextFadeEvent)->GetValue().GetRandomNumInRange();
    float timedelta = NextFadeEvent->GetActualTime() - GetActualTime();
    if (timedelta == 0) 
		timedelta = 1; // prevent divide by zero errors
    part.DirStep.z = (newvalue - part.Dir.z) / timedelta;
  }
}


void HoNewParticleEvent_EventTimer::DoItToIt(HoNewParticle &part)
{
  part.EventTimer = EventTimer.GetRandomNumInRange();
}


const int HoNewParticleEmitterTokenizer::NUMBLENDINGMODES = 6;
const BLENDINGMODE HoNewParticleEmitterTokenizer::BlendingModes[6] =
{
  { "BLEND_ALPHA"   , BLEND_ALPHA },
  { "BLEND_COLOR"   , BLEND_COLOR },
  { "BLEND_ADDCOLOR", BLEND_ADDCOLOR },
  { "BLEND_SHADOW"  , BLEND_SHADOW },
  { "BLEND_LAMP"    , BLEND_LAMP },
  { "BLEND_INVSHADOW", BLEND_INVSHADOW }
};

/*
const int HoNewParticleEmitterTokenizer::NUMBLENDINGMODES = 11;
const BLENDINGMODE HoNewParticleEmitterTokenizer::BlendingModes[11] =
{
  { "D3DBLEND_ZERO", D3DBLEND_ZERO },
  { "D3DBLEND_ONE", D3DBLEND_ONE },
  { "D3DBLEND_SRCCOLOR", D3DBLEND_SRCCOLOR },
  { "D3DBLEND_INVSRCCOLOR", D3DBLEND_INVSRCCOLOR },
  { "D3DBLEND_SRCALPHA", D3DBLEND_SRCALPHA },
  { "D3DBLEND_INVSRCALPHA", D3DBLEND_INVSRCALPHA },
  { "D3DBLEND_DESTALPHA", D3DBLEND_DESTALPHA },
  { "D3DBLEND_INVDESTALPHA", D3DBLEND_INVDESTALPHA },
  { "D3DBLEND_DESTCOLOR", D3DBLEND_DESTCOLOR },
  { "D3DBLEND_INVDESTCOLOR", D3DBLEND_INVDESTCOLOR },
  { "D3DBLEND_SRCALPHASAT", D3DBLEND_SRCALPHASAT }
};
*/

const int HoNewParticleEmitterTokenizer::NUMPARTICLETYPES = 4;
const PARTICLETYPE HoNewParticleEmitterTokenizer::ParticleTypes[4] =
{
    { "TYPE_ONE", TYPE_ONE},
    { "TYPE_TWO", TYPE_TWO},
    { "TYPE_THREE", TYPE_THREE},
    { "TYPE_FOUR", TYPE_FOUR}
};

bool HoNewParticleEmitterTokenizer::ProcessNumber(HoMinMax<float> &number, std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                     std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // the first token is either the random keyword, or it's an actual number.
  switch(TokenIter->Type) 
  {
    case KeywordRandom:
    {
      // parse random number into minmax
      NextToken(TokenIter, EndIter);
      if (TokenIter->Type != OpenParen)
      {
        OutputDebugString("Expecting opening paren after Random keyword.");
        return false;
      }
      NextToken(TokenIter, EndIter);
      if (TokenIter->Type != RealNumber)
      {
		  OutputDebugString("Expecting first number within Random(...).");
          return false;
      }
      
	  number.Min = (float)atof(TokenIter->StrValue.c_str());
      NextToken(TokenIter, EndIter);
      
      if (TokenIter->Type != Comma)
      {
		  OutputDebugString("Expecting comma within Random(...).");
          return false;
      }

      NextToken(TokenIter, EndIter);

      if (TokenIter->Type != RealNumber)
      {
		  OutputDebugString("Expecting second number within Random(...).");
          return false;
      }

      number.Max = (float)atof(TokenIter->StrValue.c_str());
      NextToken(TokenIter, EndIter);
      if (TokenIter->Type != CloseParen)
      {
		  OutputDebugString("Missing close paren on Random(...).");
          return false;
      }
      NextToken(TokenIter, EndIter);
	}

    break;

    case RealNumber:
      // min and max both equal realnumber
      if (TokenIter->Type != RealNumber)
	  {
		  OutputDebugString("Expecting number.");
		  return false;
	  }
      number.Max = number.Min = (float)atof(TokenIter->StrValue.c_str());
      NextToken(TokenIter, EndIter);
    break;

    default:
    {
        OutputDebugString("Expecting either Random(...) or a number value.");
        return false;
    }
  }
  return(true);
}

bool HoNewParticleEmitterTokenizer::ProcessVector(HoMinMax<D3DVECTOR> &v,
                                     std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                     std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // this token needs to be a XYZ keyword.
  if (TokenIter->Type != KeywordXYZ)
  {
	  OutputDebugString("Expecting XYZ(...)!");
	  return false;
  }
	  //throw("Expecting XYZ(...)!");
  NextToken(TokenIter, EndIter);
  
  if (TokenIter->Type != OpenParen) 
  {
	  OutputDebugString(" after XYZ!");
	  return false;
  }
	  //throw("Expecting ( after XYZ!");
  
  HoMinMax<float> x;
  HoMinMax<float> y;
  HoMinMax<float> z;

  NextToken(TokenIter, EndIter); 
  ProcessNumber(x, TokenIter, EndIter);
  v.Min.x = x.Min;
  v.Max.x = x.Max;
  
  if (TokenIter->Type != Comma)
  {
	  OutputDebugString("Vector components must be seperated by comma.");
	  return false;
  }
	  //throw("Vector components must be seperated by a comma.");
  NextToken(TokenIter, EndIter); 
  ProcessNumber(y, TokenIter, EndIter);
  if (TokenIter->Type != Comma) 
  {
	  OutputDebugString("Vector components must be seperated by a comma.");
	  return false;
  }
	  //throw("Vector components must be seperated by a comma.");
  NextToken(TokenIter, EndIter); 
  ProcessNumber(z, TokenIter, EndIter);
  if (TokenIter->Type != CloseParen) 
  {
	  OutputDebugString("Expecting ) to close vector.");
	  return false;
  }
	 //throw("Expecting ) to close vector.");
  NextToken(TokenIter, EndIter);
  

  //v.Min = D3DVECTOR(x.Min, y.Min, z.Min);
  //v.Max = D3DVECTOR(x.Max, y.Max, z.Max);
  v.Min.x = x.Min;
  v.Min.y = y.Min;
  v.Min.z = z.Min;

  v.Max.x = x.Max;
  v.Max.y = y.Max;
  v.Max.z = z.Max;

  return(true);
}

bool HoNewParticleEmitterTokenizer::ProcessColor(HoMinMax<D3DCOLORVALUE> &c, 
                                     std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                     std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  // this token needs to be a RGBA keyword.
  if (TokenIter->Type != KeywordColor)
  {
	  OutputDebugString("Expecting RGBA(...)!");
	  return false;
  }
		
  NextToken(TokenIter, EndIter);
  
  if (TokenIter->Type != OpenParen) 
  {
	  OutputDebugString(" after RGBA!");
	  return false;
  }
	 
  
  HoMinMax<float> r;
  HoMinMax<float> g;
  HoMinMax<float> b;
  HoMinMax<float> a;

  NextToken(TokenIter, EndIter); 
  ProcessNumber(r, TokenIter, EndIter);
  if (TokenIter->Type != Comma) 
  {
	  OutputDebugString("Color components must be seperated by a comma.");
	  return false;
  }
  NextToken(TokenIter, EndIter); 
  ProcessNumber(g, TokenIter, EndIter);
  if (TokenIter->Type != Comma) 
  {
	  OutputDebugString("Color components must be seperated by a comma.");
	  return false;
  }

  NextToken(TokenIter, EndIter); 
  ProcessNumber(b, TokenIter, EndIter);
  if (TokenIter->Type != Comma) 
  {
	  OutputDebugString("Color components must be seperated by a comma.");
	  return false;
  }

  NextToken(TokenIter, EndIter); 
  ProcessNumber(a, TokenIter, EndIter);
  if (TokenIter->Type != CloseParen)
  {
	  OutputDebugString("Expecting ) to close vector.");
	  return false;
  }

  NextToken(TokenIter, EndIter);
  
  //c.Min = D3DCOLORVALUE(r.Min, g.Min, b.Min, a.Min);
  //c.Max = D3DCOLORVALUE(r.Max, g.Max, b.Max, a.Max);
  
  c.Min.r = r.Min;
  c.Min.g = g.Min;
  c.Min.b = b.Min;
  c.Min.a = a.Min;

  c.Max.r = r.Max;
  c.Max.g = g.Max;
  c.Max.b = b.Max;
  c.Max.a = a.Max;

  return(true);
}

bool HoNewParticleEmitterTokenizer::ProcessAlphaBlendMode(int &alphablendmode,
                                     std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                     std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  if (TokenIter->Type != AlphaBlendMode)
  {
	  OutputDebugString("Expecting alpha blend mode (D3DBLEND_ZERO, D3DBLEND_ONE, etc.).");
      return false;
  }

  for (int q=0; q < NUMBLENDINGMODES; q++)
  {
		//블렌드 모드를 찾는다..
		if (TokenIter->StrValue.find(BlendingModes[q].name) != std::string::npos &&
		TokenIter->StrValue.size() == strlen(BlendingModes[q].name))
		{
		    alphablendmode = BlendingModes[q].mode;
		    NextToken(TokenIter, EndIter);
		    return(true);
		}
  }
  OutputDebugString("Invalid alpha blending mode!");
  return(false);
}


bool HoNewParticleEmitterTokenizer::ProcessParticleTypeMode(int &particleTypeMode,
                                     std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
                                     std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{

  if (TokenIter->Type != ParticleTypeMode)
  {
	  OutputDebugString("Expecting Particle Type Mode");
      return false;
  }



  for (int q=0; q < NUMPARTICLETYPES; q++)
  {
    if (TokenIter->StrValue.find(ParticleTypes[q].name) != std::string::npos &&
		TokenIter->StrValue.size() == strlen(ParticleTypes[q].name))
		{
		    particleTypeMode = ParticleTypes[q].mode;
		    NextToken(TokenIter, EndIter);
		    return(true);
		}
  }
  OutputDebugString("Invalid alpha blending mode!");


  return(false);
}

bool HoNewParticleEmitterTokenizer::ProcessTime(HoMinMax<float> &TimeRange, bool &IsFade, const float InitialTime, const float FinalTime,
                                   std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
                                   std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{

  // determine if this time specification is a fade directive
  if (TokenIter->Type == KeywordFade) {
    // it is... the next token must be "so"
    NextToken(TokenIter, EndIter); if (TokenIter->Type != KeywordSo)
    {
        OutputDebugString("Expecting \"so\" after \"fade\".");
        return false;
    }

    // flip the fade flag on
    IsFade = true;

    // move to next token (so that we land on "at" for the code below)
    NextToken(TokenIter, EndIter);
  }
  else IsFade = false; // just to be safe

  switch(TokenIter->Type) {
    case KeywordAt:
    {
      // easy, just grab the time
      NextToken(TokenIter, EndIter);
      ProcessNumber(TimeRange, TokenIter, EndIter);
    }
    break;

    case KeywordInitial:
    {
      // use initial time that was passed in.
      if (IsFade)
      {
		  OutputDebugString("Cannot use \"fade so\" modifier on \"initial\" times.");
          return false;
      }
      TimeRange.Min = InitialTime;
      TimeRange.Max = InitialTime;
      HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
    }
    break;

    case KeywordFinal:
    {
      // use final time that was passed in.
      TimeRange.Min = FinalTime;
      TimeRange.Max = FinalTime;
      HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
    }
    break;

    default:
    {
        OutputDebugString("Expected time specifier: \"[fade so] at\", \"initial\", or \"[fade so] final\"");
        return false;
    }
  }

  return(true);
}

void HoNewParticleEmitterTokenizer::DetermineTokenType(HoNewParticleEmitterToken &token)
{
	token.Type = UnknownToken;
  
	// these things are easy to see...
	if (isdigit(token.StrValue[0]) || token.StrValue[0] == '-') { token.Type = RealNumber; return; }
	if (token.StrValue[0] == '=')   { token.Type = Equals; return; }
	if (token.StrValue[0] == ',')   { token.Type = Comma; return; }
	if (token.StrValue[0] == '(')   { token.Type = OpenParen; return; }
	if (token.StrValue[0] == ')')   { token.Type = CloseParen; return; }
	if (token.StrValue[0] == '{')   { token.Type = OpenBrace; return; }
	if (token.StrValue[0] == '}')   { token.Type = CloseBrace; return; }
	if (token.StrValue[0] == '\"')  { token.Type = Quote; return; }
	  
	// if we got here, it's not a quote... so convert it to uppercase.
	MakeUpperCase(token.StrValue);


	// keywords are easy to figure out, just look for the text...
	if (token.StrValue.find("PARTICLESYSTEM") != std::string::npos) { token.Type = KeywordParticleSystem; return; }
    if (token.StrValue.find("EVENTSEQUENCE") != std::string::npos) { token.Type = KeywordEventSequence; return; }
	if (token.StrValue.find("RANDOM") != std::string::npos) { token.Type = KeywordRandom; return; }
	if (token.StrValue.find("XYZ") != std::string::npos) { token.Type = KeywordXYZ; return; }
	if (token.StrValue.find("RGBA") != std::string::npos) { token.Type = KeywordColor; return; }
	if (token.StrValue.find("FADE") != std::string::npos) { token.Type = KeywordFade; return; }
    if (token.StrValue.find("OUTLENGTH") != std::string::npos)
    {
        token.Type = KeywordOutLength;
        return;
    }

    if (token.StrValue.find("INLENGTH") != std::string::npos)
    {
        token.Type = KeywordInLength;
        return;
    }


	  
	if (token.StrValue.find("INITIAL") != std::string::npos) { token.Type = KeywordInitial; return; }
	if (token.StrValue.find("FINAL") != std::string::npos) { token.Type = KeywordFinal; return; }
	if (token.StrValue.find("TEXTURE") != std::string::npos) { token.Type = KeywordTexture; return; }
	  
	// these two keywords are embedded in other words, so we've got to be careful.
	if (token.StrValue.find("SO") != std::string::npos && token.StrValue.size() == 2) { token.Type = KeywordSo; return; }
	if (token.StrValue.find("AT") != std::string::npos && token.StrValue.size() == 2) { token.Type = KeywordAt; return; }

    if (token.StrValue.find("PARTICLETYPE") != std::string::npos)
    {
        token.Type = SeqParticleProp;
        return;
    }

    if (token.StrValue.find("TYPE_") != std::string::npos)
    {
        token.Type = ParticleTypeMode;
        return;
    }

    // now it gets harder...
	if (token.StrValue.find("BLEND_") != std::string::npos)
	{ 
		token.Type = AlphaBlendMode;
        return;
	}
	if (token.StrValue.find("SOURCEBLENDMODE") != std::string::npos ||
		token.StrValue.find("DESTBLENDMODE") != std::string::npos) {

		token.Type = SeqAlphaBlendModeProp;
        return;
	}

	if (token.StrValue.find("LIFETIME") != std::string::npos ||
		token.StrValue.find("EMITRATE") != std::string::npos ||
		token.StrValue.find("NUMPARTICLES") != std::string::npos ||
		token.StrValue.find("LOOPS") != std::string::npos ||
//		token.StrValue.find("CELLSIZE") != std::string::npos) ||
        token.StrValue.find("DELAY") != std::string::npos)
    {
		token.Type = SeqNumericProp;
        return;
	}

	if (token.StrValue.find("SPAWNDIR") != std::string::npos ||
		token.StrValue.find("GRAVITY") != std::string::npos ||
		token.StrValue.find("EMITRADIUS") != std::string::npos)
    {
		token.Type = SeqVectorProp;
        return;
	}

	if (token.StrValue.find("POSITION") != std::string::npos)
    {
		token.Type = SysVectorProp;
        return;
	}


	if (token.StrValue.find("SIZE") != std::string::npos ||
		token.StrValue.find("EVENTTIMER") != std::string::npos ||
        token.StrValue.find("SIZEEXT") != std::string::npos)
    {
		token.Type = ParticleNumericProp;
        return;
	}

    if (token.StrValue.find("PARTANGLE") != std::string::npos ||
        token.StrValue.find("LOCALANGLE") != std::string::npos)
    {
        token.Type = ParticleAngleProp;
        return;
    }

	if (token.StrValue.find("VELOCITY") != std::string::npos)
    {
		token.Type = ParticleVectorProp;
        return;
	}

	if (token.StrValue.find("COLOR") != std::string::npos)
    {
		token.Type = ParticleColorProp;
        return;
	}
}

void HoNewParticleEmitterTokenizer::AddToken(HoNewParticleEmitterToken token)
{
  if (token.StrValue.size())
  {
	  //토큰의 종류를 판단한다.
	  DetermineTokenType(token);

	  //토큰을 정보와 토큰을 저장한다.
	  TokenVector.push_back(token);
  }
}

//토큰들을 분류한다.
void HoNewParticleEmitterTokenizer::Tokenize(const char *str)
{
	enum CurState
	{
		InWhiteSpace = 1,
		InText,
		InQuote,
		InComment
	};
  
	CurState cs = InWhiteSpace;
	const char *p = str;          //Text Buffer 포인터를 받는다.
	HoNewParticleEmitterToken token;
	  
	while ((*p) != 0)
	{
		switch(cs)
		{
			case InWhiteSpace:
			{
				// 스페이스(빈공간)가 없으면
				if (!isspace(*p))
				{
					// add it to the running buffer
					token.StrValue = (*p);
					//표시가 있으면 주석 상태로 바꾼다.)
					if ((*p) == '/' && *(p+1) == '/') 
						cs = InComment;
					else//인용부호(")가 열려 있는지 판단해서 인용문인지 텍스트 인지 구별한다. 
						cs = (*p == '\"') ? InQuote : InText;
				} // end if
			}
			break;

            case InText:
			{
				// if this letter is whitespace (빈 공간이 있으면)
				if (isspace(*p))
				{
					// 완성된 토큰을 벡터에 추가를 한다.
					AddToken(token);
					//OutputDebugString(token.StrValue.c_str());
					// switch to whitespace case
					cs = InWhiteSpace;
				} 
				else
				{ 
					// if this letter is a token terminator
					if ((*p) == '(' || (*p) == ')' || (*p) == ',' || (*p) == '\"' || (*p) == '{' || (*p) == '}' || (*p) == '/')
					{
						if ((*p) == '/' && *(p+1) == '/')
							cs = InComment;
						else 
						{
							// add the completed token to the vector
							DetermineTokenType(token);
							AddToken(token);
				            
							// if it was a quote, transition to InQuote state
							if ((*p) == '\"')
								cs = InQuote; 
							// otherwise, process this one char as a token 
							else
							{
								token.StrValue = (*p);
								AddToken(token);
								//OutputDebugString(token.StrValue.c_str());
								token.StrValue = "";
							}
						}
					} 
					else 
					{
						// add this letter to the work in progress token
						token.StrValue += (*p);
					} // end if
				
				} // end if
			}
			break;

			case InComment:
			{
				// C++ style comments - skip everything until end of line
				if (*p == '\n') 
				{ 
					token.StrValue = ""; 
					cs = InWhiteSpace; 
				}
			}
			break;

			case InQuote:
			{
				// unconditionally add this letter to the token until we hit a close quote
				token.StrValue += (*p);
				if (*p == '\"')
				{
					AddToken(token);
				    //OutputDebugString(token.StrValue.c_str());
					// go back to whitespace
					cs = InWhiteSpace;
				}
			}
			break;
		}
		p++;
	}
	AddToken(token);
	//OutputDebugString(token.StrValue.c_str());
}

void HoNewParticleEmitter::init()
{
	StrName = "";
	for (std::vector<HoNewParticleEventSequence *>::iterator i = Sequences.begin(); i != Sequences.end(); i++)
	{
		delete (*i);
	}
	Sequences.clear();
	
	D3DVECTOR temp0,temp1;
	temp0.x = 0.0f;
	temp0.y = 0.0f;
	temp0.z = 0.0f;

	temp1.x = 0.0f;
	temp1.y = 0.0f;
	temp1.z = 0.0f;

	SetPosRange(HoMinMax<D3DVECTOR>(temp0, temp1));
	Stop();
	FadeStopFlag  = false;
	AttachPosFlag = false;
	FastStopFlag  = false;
	FastStopStateFlag = false;
	StartDelay = 0.f;
	memset(&Angle, 0, sizeof(Angle));
	Rendering = true;
	
}


void HoNewParticleEmitter::InvalidateDeviceObjects()
{
	for (std::vector<HoNewParticleEventSequence *>::iterator i = Sequences.begin(); i != Sequences.end(); i++)
	{
		(*i)->InvalidateDeviceObjects();
	}
}

void HoNewParticleEmitter::RestoreDeviceObjects()
{
	// restore device objects for each event sequence
	for (std::vector<HoNewParticleEventSequence *>::iterator i = Sequences.begin(); i != Sequences.end(); i++)
	{
		(*i)->RestoreDeviceObjects();
	}
}

HoNewParticleEvent *HoNewParticleEmitter::EventFactory(std::string EventName)
{
  HoNewParticleEvent *event = NULL;

  if (EventName.find("SIZEEXT") != std::string::npos) event = new HoNewParticleEvent_SizeExt();
  else if (EventName.find("SIZE") != std::string::npos) event = new HoNewParticleEvent_Size();
  else if (EventName.find("EVENTTIMER") != std::string::npos) event = new HoNewParticleEvent_EventTimer();
  else if (EventName.find("REDCOLOR") != std::string::npos) event = new HoNewParticleEvent_RedColor();
  else if (EventName.find("GREENCOLOR") != std::string::npos) event = new HoNewParticleEvent_GreenColor();
  else if (EventName.find("BLUECOLOR") != std::string::npos) event = new HoNewParticleEvent_BlueColor();
  else if (EventName.find("ALPHA") != std::string::npos) event = new HoNewParticleEvent_Alpha();
  else if (EventName.find("COLOR") != std::string::npos) event = new HoNewParticleEvent_Color();
  else if (EventName.find("VELOCITYX") != std::string::npos) event = new HoNewParticleEvent_VelocityX();
  else if (EventName.find("VELOCITYY") != std::string::npos) event = new HoNewParticleEvent_VelocityY();
  else if (EventName.find("VELOCITYZ") != std::string::npos) event = new HoNewParticleEvent_VelocityZ();
  else if (EventName.find("VELOCITY") != std::string::npos) event = new HoNewParticleEvent_Velocity();
  else if (EventName.find("PARTANGLEX")   != std::string::npos) event = new HoNewParticleEvent_PartAngleX();
  else if (EventName.find("PARTANGLEY")   != std::string::npos) event = new HoNewParticleEvent_PartAngleY();
  else if (EventName.find("PARTANGLEZ")   != std::string::npos) event = new HoNewParticleEvent_PartAngleZ();
  else if (EventName.find("PARTANGLE")    != std::string::npos) event = new HoNewParticleEvent_PartAngle();
  else if (EventName.find("LOCALANGLEX")   != std::string::npos) event = new HoNewParticleEvent_LocalAngleY();
  else if (EventName.find("LOCALANGLEY")   != std::string::npos) event = new HoNewParticleEvent_LocalAngleY();
  else if (EventName.find("LOCALANGLEZ")   != std::string::npos) event = new HoNewParticleEvent_LocalAngleZ();
  else if (EventName.find("LOCALANGLE")    != std::string::npos) event = new HoNewParticleEvent_LocalAngle();


  return(event);
}

void HoNewParticleEmitter::Main(float elapsedTime, float timeDelta)
{
	if(IsRunning())
	{
		if(StartDelay <= 0)
		{
			int runningCount=0;
			for (std::vector<HoNewParticleEventSequence *>::iterator i = Sequences.begin(); i != Sequences.end(); i++) 
			{
				if( (*i)->IsRunning())
				{
					(*i)->Main(elapsedTime, timeDelta, Pos, FadeStopFlag, AttachPosFlag);
					
					if(Angle.x != 0.0f || Angle.y != 0.0f || Angle.z != 0.0f)
					(*i)->SetAngle(Angle);

					if(FastStopFlag && FastStopStateFlag == false)
						(*i)->FastStopFlag = true;
				}
				else
				{
					runningCount++;
				}
			}
			
			if(FastStopFlag == true && FastStopStateFlag == false)			
			{
				FastStopStateFlag = true;
				FastStopFlag = false;
			}


			int seqSize = Sequences.size();
			if(runningCount >= seqSize)
			{
				Running = false;
			}
		}
		else
		{
			StartDelay -= timeDelta;
		}
	}
}

//하나의 시퀀스를 처리하는 함수. (하나의 파티클 동작)
bool HoNewParticleEmitter::ProcessEventSequenceBlock(HoNewParticleEventSequence &seq,
                                                 std::vector<HoNewParticleEmitterToken>::iterator &TokenIter, 
                                                 std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
  bool StartedProcessingEvents = false;

  // move past the event sequence keyword...
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);

  // next token should be the name of the sequence...
  if (TokenIter->Type != Quote)
  {
	  OutputDebugString("Must name particle sequence block!");
	  return false;
  }
	  //throw("Must name particle sequence block!");
  seq.SetName(TokenIter->StrValue);
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);

  // next token should be opening brace...
  if (TokenIter->Type != OpenBrace)
  {
	  OutputDebugString("Expected opening brace for particel sequence block!");
	  return false;
  }
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  while (TokenIter->Type != CloseBrace)
  {

    HoNewParticleEmitterToken savedtoken;
    savedtoken = *TokenIter;

    // the first token here can be a SysNumberProperty, SysAlphaBlendModeProperty, SysVectorProperty,
    // or an EventSequence.
    switch (TokenIter->Type)
	{
      case SeqNumericProp:
      {
        if (StartedProcessingEvents)
		{
			OutputDebugString("Cannot specify any sequence properties after specifying events.");
			return false;
		}
        HoMinMax<float> number;
        // the next 2 tokens should be an equals, and a number.
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
		if (TokenIter->Type != Equals)
		{
			OutputDebugString("Expected equals sign!");
			return false;
		}
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
        HoNewParticleEmitterTokenizer::ProcessNumber(number, TokenIter, EndIter);

        if (savedtoken.IsEmitRate()) 
			{ seq.SetEmitRate(number); }
        else if(savedtoken.IsDelay())
            seq.SetDelay(number.Max);
        else if (savedtoken.IsLifeTime())
			{ seq.SetLifetime(number); }
        else if (savedtoken.IsNumParticles())
			{ seq.SetNumParticles((const int)number.Max); }
		else if (savedtoken.IsLoops())
			{ seq.SetLoops((const int)number.Max); }
		else
		{
			OutputDebugString("Unknown sequence numeric property!");
			return false;
        }
      }
      break;



      case SeqVectorProp:
      {
        if (StartedProcessingEvents)
			OutputDebugString("Cannot specify any sequence properties after specifying events.");
        HoMinMax<D3DVECTOR> v;
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
        if (TokenIter->Type != Equals)
		{
			OutputDebugString("Expected equals sign!");
			return false;
		}
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
		if(!HoNewParticleEmitterTokenizer::ProcessVector(v, TokenIter, EndIter))
		{
			OutputDebugString("벡터값 읽던중 에러");
			return false;
		}

        if (savedtoken.IsSpawnDir())        
			{ seq.SetSpawnDir(v); }
        else if (savedtoken.IsEmitRadius()) 
			{ seq.SetEmitRadius(v); }
        else if (savedtoken.IsGravity())    
			{ seq.SetGravity(v); }
        else 
		{
			OutputDebugString("Unknown sequence vector property!");
			return false;
        }
      }
      break;

      case SeqParticleProp:
      {
        if (StartedProcessingEvents)
		{
			OutputDebugString("Cannot specify any sequence properties after specifying events.");
			return false;
		}
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
        if (TokenIter->Type != Equals)
		{
			OutputDebugString("Expected equals sign!");
			return false;
		}

        int particleTypeMode;
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
        HoNewParticleEmitterTokenizer::ProcessParticleTypeMode(particleTypeMode, TokenIter, EndIter);

        if (savedtoken.IsParticleType())
			{ seq.SetParticleType(particleTypeMode);}
      }
      break;

      case SeqAlphaBlendModeProp:
      {
        if (StartedProcessingEvents)
		{
			OutputDebugString("Cannot specify any sequence properties after specifying events.");
			return false;
		}

        int alphablendmode;
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
        if (TokenIter->Type != Equals)
		{
			OutputDebugString("Expected equals sign!");
			return false;
		}

        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
        HoNewParticleEmitterTokenizer::ProcessAlphaBlendMode(alphablendmode, TokenIter, EndIter);

        /*
        if (savedtoken.IsSrcBlendMode())
			{ seq.SetSrcBlendMode(alphablendmode); }
        else if (savedtoken.IsDestBlendMode())
			{ seq.SetDestBlendMode(alphablendmode); }
        else
		{
          OutputDebugString("Unknown sequence alpha blending mode property!");
		  return false;
        }
        */

        if (savedtoken.IsBlendMode())
            seq.SetSrcBlendMode(alphablendmode);
      }
      break;

      case KeywordTexture:
      {
        // TODO
		//텍스쳐 부분 처리하는 부분..
        if (StartedProcessingEvents) 
		{
			OutputDebugString("Cannot specify any sequence properties after specifying events.");
			return false;
		}

        HoMinMax<D3DVECTOR> v;
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
        if (TokenIter->Type != Equals) 
		{
			OutputDebugString("Expected equals sign!");
			return false;
		}
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);

        if (TokenIter->Type != Quote) 
		{
			OutputDebugString("Expected filename after texture sequence property.");
			return false;
		}
		seq.SetTexture(RemoveQuotes(TokenIter->StrValue).c_str());
        HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
	  }
      break;

      case KeywordFade: case KeywordAt: case KeywordInitial: case KeywordFinal:
      {
        StartedProcessingEvents = true;

        bool IsFade = false;
        HoMinMax<float> TimeRange;

        // parse the time range section of the event line
        HoNewParticleEmitterTokenizer::ProcessTime(TimeRange, IsFade, 0, seq.GetLifetime().Max, TokenIter, EndIter);

        if (TokenIter->Type != ParticleNumericProp &&  TokenIter->Type != ParticleVectorProp &&
            TokenIter->Type != ParticleColorProp && TokenIter->Type != ParticleAngleProp)
		{
			OutputDebugString("Expecting particle property after time specifier!");
			return false;
		}

        HoNewParticleEvent * NewEvent = NULL;
        try 
		{
			// 새로운 이벤트를 생성한다.
			NewEvent = EventFactory(TokenIter->StrValue);

			if (!NewEvent)
			{
				OutputDebugString("Unknown event type, or there was an error creating this event.");
				return false;
			}

            // 페이드 이벤트 일때 이벤트가 페이드를 지원하는지 알아 본다.
			if (IsFade && !NewEvent->FadeAllowed())
			{
				OutputDebugString("Fading is not supported on this event.");
				return false;
			}
			NewEvent->ProcessTokenStream(TokenIter, EndIter);
			NewEvent->SetTimeRange(TimeRange);
			NewEvent->SetFade(IsFade);
			seq.Events.push_back(NewEvent);
		}
        catch(char *e) 
		{
          //SAFE_DELETE(NewEvent);

		  if(NewEvent)
		  {
			  delete NewEvent;
			  NewEvent = NULL;
		  }
		  OutputDebugString(e);
		  return false;
          //throw(e);
        }
        catch(...) {
          //SAFE_DELETE(NewEvent);
			if(NewEvent)
			{
				delete NewEvent;
				NewEvent = NULL;
			}
          OutputDebugString("Unhandled exception creating event!");
		  return false;
        }
      }
      break;

      default: 
      {
        char buf[256]; _snprintf(buf, sizeof(buf), "Unexpected \"%s\" in Sequence Block!", TokenIter->StrValue.c_str());
		OutputDebugString(&buf[0]);
		return false;
        //throw(&buf[0]);
      }
      break;
    }
  }
  seq.NailDownRandomTimes();
  seq.SortEvents();
  seq.CreateFadeLists();
  HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
  return(true);
}


//만들어진 토큰들을 분
bool HoNewParticleEmitter::ProcessParticleSystemBlock(std::vector<HoNewParticleEmitterToken>::iterator &TokenIter,
													  std::vector<HoNewParticleEmitterToken>::iterator &EndIter)
{
	
	bool StartedProcessingSequences = false;
    HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
  
	
	while (TokenIter->Type != CloseBrace)
	{
		HoNewParticleEmitterToken savedtoken;
		savedtoken = *TokenIter;
		

		switch (TokenIter->Type)
		{
			case SysVectorProp:
			{
				if (StartedProcessingSequences)
				{
					OutputDebugString("Cannot specify any particle system properties after specifying sequences.");
					return false;
				}
					//throw("Cannot specify any particle system properties after specifying sequences.");
				
				HoMinMax<D3DVECTOR> v;
				HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
				if (TokenIter->Type != Equals)
				{
					OutputDebugString("Expected equals sign!");
					return false;
				}
					//throw("Expected equals sign!");
				HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter); 
				HoNewParticleEmitterTokenizer::ProcessVector(v, TokenIter, EndIter);
				if (savedtoken.IsPosition())
				{
					PosRange = v;
				}
				else 
				{
					OutputDebugString("Unknown particle system property");
					return false;
				}
			}
			break;
			
			
			case KeywordEventSequence:
			{
				StartedProcessingSequences = true;
				
				HoNewParticleEventSequence *newseq = new HoNewParticleEventSequence;
				Sequences.push_back(newseq);
				
				HoNewParticleEventSequence *seq = *(Sequences.end()-1);
				seq->Reset();

				if (!ProcessEventSequenceBlock(*seq, TokenIter, EndIter))
				{
					delete seq;
					Sequences.pop_back();
				}
			}

			break;
			

			default: 
			{
				char buf[256]; 
				_snprintf(buf, sizeof(buf), "Unexpected \"%s\" in Particle System Block!", TokenIter->StrValue.c_str());
				OutputDebugString(buf);
				return false;
				//throw(&buf[0]);
			}
			break;
		}
	}
	
	HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
	
	return(true);
}


bool HoNewParticleEmitter::AddScript(HoNewParticleScriptRes *scrRes)
{
    StrLastError = "Script Starting";

    //HoNewParticleEmitterTokenizer tokenizer;
    InvalidateDeviceObjects();
    init();

    std::vector<HoNewParticleEmitterToken>::iterator TokenIter = scrRes->emitterTokenizer.TokenVector.begin();
    std::vector<HoNewParticleEmitterToken>::iterator EndIter = scrRes->emitterTokenizer.TokenVector.end();

    if (scrRes->emitterTokenizer.TokenVector.size() < 2)
        return false;
	
	if (TokenIter->Type != KeywordParticleSystem)
		return false;

	HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
    if (TokenIter->Type != Quote)
		return false;

	StrName = RemoveQuotes(TokenIter->StrValue);
    HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);

	if (TokenIter->Type != RealNumber)
		return false;

	HoNewParticleEmitterTokenizer::NextToken(TokenIter, EndIter);
    if (TokenIter->Type != OpenBrace)
		return false;

	if(!ProcessParticleSystemBlock(TokenIter, EndIter))
		return false;

	Pos = PosRange.GetRandomNumInRange();
    RestoreDeviceObjects();
    return true;
}

//텍스쳐를 로드하는곳
void HoNewParticleEventSequence::SetTexture(const char *strTexFileName)
{
    //char buffer[500];
    //memset(buffer, 0, sizeof(buffer));
    //GetCurrentDirectory(sizeof(buffer), buffer);
	char fileName[64];
	char fileExt[64];
	memset(fileName, 0, sizeof(fileName));
	memset(fileExt,  0, sizeof(fileExt));
	
	_splitpath(strTexFileName,NULL,NULL,fileName,fileExt);
	StrTexFileName = fileName;
	//StrTexFileName += '.';
	StrTexFileName += fileExt;

	//_splitpath(directory,drive,dir,NULL,NULL);
	//StrTexFileName = strTexFileName;
	MakeUpperCase(StrTexFileName);
}

void HoNewParticleEventSequence::RestoreDeviceObjects()
{
    Particles = new HoRecyclingArrayDyn<HoNewParticle>(NumParticles);
    //텍스쳐를 세팅하는 부분...
    SetTexture(StrTexFileName.c_str());
	//MakeUpperCase(StrTexFileName);
    MaterialNum = g_NewParticleResMgr.AddTexture(StrTexFileName.c_str());

    // restore device objects for each event in this sequence
    for (std::vector<HoNewParticleEvent *>::iterator i = Events.begin(); i != Events.end(); i++)
    {
        (*i)->RestoreDeviceObjects();
    }
}

void HoNewParticleEventSequence::Reset()
{
    ParticleType = TYPE_ONE;
    SumCount = 0;
    CellSize = 0;
    MaterialNum = -1;
    TotalParticleLives = 0;
    Loops = -1;

    NumParticles = 100;
    NumNewPartsExcess = 0.0f;

    DelayRunningTime = 0;
    TimeCount = 0;
    D3DVECTOR temp0,temp1;
    temp0.x = 0.0f;
    temp0.y = 0.0f;
    temp0.z = 0.0f;

    temp1.x = 0.0f;
    temp1.y = 0.0f;
    temp1.z = 0.0f;

    Gravity = HoMinMax<D3DVECTOR>(temp0,temp0);
    EmitRadius = HoMinMax<D3DVECTOR>(temp1,temp1);
    for (std::vector<HoNewParticleEvent *>::iterator i = Events.begin(); i != Events.end(); i++)
    {
			// can't use safe delete here, because it will set i = NULL.
        if (*i)
        delete (*i);
    }
    Events.clear();

    if(Particles)
    {
        delete Particles;
        Particles = NULL;
    }



}

smRENDFACE *HoNewParticleEventSequence::AddFace2dPlane(smFACE2D *face)
{
	int x,y,z;
    int width , height;

    smRENDVERTEX *v[4];
    smRENDFACE	 *rf;
    short		sColor[4];

    sColor[ SMC_A ] = face->Transparency;
    sColor[ SMC_R ] = face->r;
    sColor[ SMC_G ] = face->g;
    sColor[ SMC_B ] = face->b;

    x = face->x;
    y = face->y;
    z = face->z;

    POINT3D inVertex[4];
    POINT3D outVertex[4];

    width = face->width/2;
    height = face->height/2;

	inVertex[0].x   = x-width;
    inVertex[0].y   = y;
    inVertex[0].z   = z+height;

    inVertex[1].x   = x+width;
    inVertex[1].y   = y;
    inVertex[1].z   = z+height;

    inVertex[2].x   = x-width;
    inVertex[2].y   = y;
    inVertex[2].z   = z-height;

    inVertex[3].x   = x+width;
    inVertex[3].y   = y;
	inVertex[3].z   = z-height;

	int index;
	for(index = 0; index < 4; index++)
    {
        inVertex[index].x -= smRender.CameraPosiX;
        inVertex[index].y -= smRender.CameraPosiY;
        inVertex[index].z -= smRender.CameraPosiZ;
    }

	for(index = 0; index < 4; index++)
    {
        outVertex[index].x = inVertex[index].x*smRender.mCamera._11 +
                             inVertex[index].y*smRender.mCamera._21 +
                             inVertex[index].z*smRender.mCamera._31;

        outVertex[index].y = inVertex[index].x*smRender.mCamera._12 +
                             inVertex[index].y*smRender.mCamera._22 +
                             inVertex[index].z*smRender.mCamera._32;

        outVertex[index].z = inVertex[index].x*smRender.mCamera._13 +
                             inVertex[index].y*smRender.mCamera._23 +
                             inVertex[index].z*smRender.mCamera._33;

        outVertex[index].x = outVertex[index].x >> FLOATS_EM;
        outVertex[index].y = outVertex[index].y >> FLOATS_EM;
        outVertex[index].z = outVertex[index].z >> FLOATS_EM;
		
		if(outVertex[index].z < SMFLOAT_DIST_NEARZ)
            return NULL;
    }

	//렌더링 버텍스 추가 ( 좌표 직접 입력 )
    v[0] = smRender.AddRendVertex ( outVertex[0].x , outVertex[0].y , outVertex[0].z, sColor);
    v[1] = smRender.AddRendVertex ( outVertex[1].x,  outVertex[1].y , outVertex[1].z, sColor);
    v[2] = smRender.AddRendVertex ( outVertex[2].x , outVertex[2].y , outVertex[2].z, sColor);
    v[3] = smRender.AddRendVertex ( outVertex[3].x , outVertex[3].y , outVertex[3].z, sColor);

		//첫번째 폴리곤 ( 1 - 2 - 3 );
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = face->MatNum ;		//메트리얼 복사
		rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
		rf->lpTexLink  = 0;

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
    return &smRender.RendFace[ smRender.nRendFace-1 ];
}

//평면 폴리곤을 추가하는 루틴(렌더링이 된후에 찍히는 것들)
smRENDFACE *HoNewParticleEventSequence::AddFace2dPlane(smFACE2D *face, D3DVECTOR inAngle)
{
    int x,y,z;
    int width , height;

    smRENDVERTEX *v[4];
    smRENDFACE	 *rf;
    short		sColor[4];

    sColor[ SMC_A ] = face->Transparency;
    sColor[ SMC_R ] = face->r;
    sColor[ SMC_G ] = face->g;
    sColor[ SMC_B ] = face->b;

    x = face->x;
    y = face->y;
    z = face->z;

    POINT3D inVertex[4];
    POINT3D outVertex[4];

    width = face->width/2;
    height = face->height/2;

	inVertex[0].x   = x-width;
    inVertex[0].y   = y;
    inVertex[0].z   = z+height;

    inVertex[1].x   = x+width;
    inVertex[1].y   = y;
    inVertex[1].z   = z+height;

    inVertex[2].x   = x-width;
    inVertex[2].y   = y;
    inVertex[2].z   = z-height;

    inVertex[3].x   = x+width;
    inVertex[3].y   = y;
	inVertex[3].z   = z-height;
	
	int index = 0;
	//if(inAngle != NULL)
	//{
		inVertex[0].x   = -width;
		inVertex[0].y   = 0;
		inVertex[0].z   = height;

		inVertex[1].x   = width;
		inVertex[1].y   = 0;
		inVertex[1].z   = height;

		inVertex[2].x   = -width;
		inVertex[2].y   = 9;
		inVertex[2].z   = -height;

		inVertex[3].x   = width;
		inVertex[3].y   = 0;
		inVertex[3].z   = -height;

		POINT3D angle;
		angle.x = (int)inAngle.x;
		angle.y = (int)inAngle.y;
		angle.z = (int)inAngle.z;

		angle.x = angle.x & ANGCLIP;
		angle.y = angle.y & ANGCLIP;
		angle.z = angle.z & ANGCLIP;

		smMATRIX inRotXMatrix;
		smMATRIX inRotYMatrix;
		smMATRIX inRotZMatrix;

		smMATRIX outMatrix;
		smIdentityMatrix(outMatrix);
		smIdentityMatrix(inRotXMatrix);
		smIdentityMatrix(inRotYMatrix);
		smIdentityMatrix(inRotZMatrix);

		smRotateXMatrix(inRotXMatrix, angle.x);
		smRotateYMatrix(inRotYMatrix, angle.y);
		smRotateZMatrix(inRotZMatrix, angle.z);

		smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
		smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

		for(index = 0; index < 4; index++)
		{
			outVertex[index].x = inVertex[index].x * outMatrix._11 +
								 inVertex[index].y * outMatrix._21 +
								 inVertex[index].z * outMatrix._31 ;


			outVertex[index].y = inVertex[index].x * outMatrix._12 +
								 inVertex[index].y * outMatrix._22 +
								 inVertex[index].z * outMatrix._32 ;


			outVertex[index].z = inVertex[index].x * outMatrix._13 +
								 inVertex[index].y * outMatrix._23 +
								 inVertex[index].z * outMatrix._33 ;

			outVertex[index].x = outVertex[index].x/fONE+x;
			outVertex[index].y = outVertex[index].y/fONE+y;
			outVertex[index].z = outVertex[index].z/fONE+z;

		}

		memcpy(inVertex, outVertex, sizeof(inVertex));
	//}

	//int index;
	for(index = 0; index < 4; index++)
    {
        inVertex[index].x -= smRender.CameraPosiX;
        inVertex[index].y -= smRender.CameraPosiY;
        inVertex[index].z -= smRender.CameraPosiZ;
    }

	for(index = 0; index < 4; index++)
    {
        outVertex[index].x = inVertex[index].x*smRender.mCamera._11 +
                             inVertex[index].y*smRender.mCamera._21 +
                             inVertex[index].z*smRender.mCamera._31;

        outVertex[index].y = inVertex[index].x*smRender.mCamera._12 +
                             inVertex[index].y*smRender.mCamera._22 +
                             inVertex[index].z*smRender.mCamera._32;

        outVertex[index].z = inVertex[index].x*smRender.mCamera._13 +
                             inVertex[index].y*smRender.mCamera._23 +
                             inVertex[index].z*smRender.mCamera._33;

        outVertex[index].x = outVertex[index].x >> FLOATS_EM;
        outVertex[index].y = outVertex[index].y >> FLOATS_EM;
        outVertex[index].z = outVertex[index].z >> FLOATS_EM;

		if(outVertex[index].z < SMFLOAT_DIST_NEARZ)
            return NULL;
    }
	

	//렌더링 버텍스 추가 ( 좌표 직접 입력 )
    v[0] = smRender.AddRendVertex ( outVertex[0].x , outVertex[0].y , outVertex[0].z, sColor);
    v[1] = smRender.AddRendVertex ( outVertex[1].x,  outVertex[1].y , outVertex[1].z, sColor);
    v[2] = smRender.AddRendVertex ( outVertex[2].x , outVertex[2].y , outVertex[2].z, sColor);
    v[3] = smRender.AddRendVertex ( outVertex[3].x , outVertex[3].y , outVertex[3].z, sColor);

		//첫번째 폴리곤 ( 1 - 2 - 3 );
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = face->MatNum ;		//메트리얼 복사
		rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
		rf->lpTexLink  = 0;

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
    return &smRender.RendFace[ smRender.nRendFace-1 ];
}

smRENDFACE *HoNewParticleEventSequence::AddFace2DBillBoard( smFACE2D *face)
{
    int x,y,z;
	int rx , ry, rz;
	int width , height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[ SMC_A ] = face->Transparency;
	sColor[ SMC_R ] = face->r;
	sColor[ SMC_G ] = face->g;
	sColor[ SMC_B ] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;

	//중심 좌표를 카메라 좌표를 변환
	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		 y * smRender.mCamera._21 +
		 z * smRender.mCamera._31 ;

	ry = x * smRender.mCamera._12 +
		 y * smRender.mCamera._22 +
		 z * smRender.mCamera._32 ;

	rz = x * smRender.mCamera._13 +
		 y * smRender.mCamera._23 +
		 z * smRender.mCamera._33 ;

	x = rx>>FLOATS_EM;
	y = ry>>FLOATS_EM;
	z = rz>>FLOATS_EM;

    if ( z<SMFLOAT_DIST_NEARZ ) return NULL;

    width  = face->width >> 1;
	height = face->height >> 1;

    POINT3D outVertex[4];
    memset(outVertex, 0, sizeof(outVertex));
    outVertex[0].x = -width;
    outVertex[0].y = -height;
    outVertex[0].z = 0;

    outVertex[1].x =  width;
    outVertex[1].y = -height;
    outVertex[1].z = 0;

    outVertex[2].x = -width;
    outVertex[2].y = height;
    outVertex[2].z = 0;

    outVertex[3].x = width;
    outVertex[3].y = height;
    outVertex[3].z = 0;

    //렌더링 버텍스 추가 ( 좌표 직접 입력 )
	v[0] = smRender.AddRendVertex ( x+outVertex[0].x , y+outVertex[0].y , z+outVertex[0].z, sColor );
	v[1] = smRender.AddRendVertex ( x+outVertex[1].x , y+outVertex[1].y , z+outVertex[1].z, sColor );
	v[2] = smRender.AddRendVertex ( x+outVertex[2].x , y+outVertex[2].y , z+outVertex[2].z, sColor );
	v[3] = smRender.AddRendVertex ( x+outVertex[3].x , y+outVertex[3].y , z+outVertex[3].z, sColor );

	//첫번째 폴리곤 ( 1 - 2 - 3 );
	rf = &smRender.RendFace[ smRender.nRendFace++ ];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial    = face->MatNum ;		//메트리얼 복사
	rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
	rf->lpTexLink  = 0;

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


	return &smRender.RendFace[ smRender.nRendFace-1 ];
}


BOOL HoNewParticleEventSequence::GetCameraCoord(POINT3D &world)
{
	int rx, ry, rz;

    //중심 좌표를 카메라 좌표로 변환
	world.x -= smRender.CameraPosiX;
	world.y -= smRender.CameraPosiY;
	world.z -= smRender.CameraPosiZ;
	
	rx = world.x * smRender.mCamera._11 +
		 world.y * smRender.mCamera._21 +
		 world.z * smRender.mCamera._31 ;
	
	ry = world.x * smRender.mCamera._12 +
		 world.y * smRender.mCamera._22 +
		 world.z * smRender.mCamera._32 ;
	
	rz = world.x * smRender.mCamera._13 +
		 world.y * smRender.mCamera._23 +
		 world.z * smRender.mCamera._33 ;

	world.x = rx>>FLOATS_EM;
	world.y = ry>>FLOATS_EM;
	world.z = rz>>FLOATS_EM;

    if ( world.z<SMFLOAT_DIST_NEARZ )
		return FALSE;
	return TRUE;
}

bool HoNewParticleEventSequence::AddFaceThree(smFACE2D *face, D3DVECTOR inAngle)
{
    int x,y,z;
    int width , height;

    smRENDVERTEX *v[4];
    smRENDFACE	 *rf;
    short		sColor[4];

    sColor[ SMC_A ] = face->Transparency;
    sColor[ SMC_R ] = face->r;
    sColor[ SMC_G ] = face->g;
    sColor[ SMC_B ] = face->b;

    x = face->x;
    y = face->y;
    z = face->z;

    POINT3D currentPos;
    POINT3D destPos;

    width = face->width/2;
    height = face->height/2;

    /*
	currentPos.x   = x;
    currentPos.y   = y+height;
    currentPos.z   = z;

    destPos.x   = x;
    destPos.y   = y-height;
    destPos.z   = z;
    */

    currentPos.x   = 0;
    currentPos.y   = height;
    currentPos.z   = 0;

    destPos.x   = 0;
    destPos.y   = -height;
    destPos.z   = 0;

    POINT3D angle;
    angle.x = (int)inAngle.x;
    angle.y = (int)inAngle.y;
    angle.z = (int)inAngle.z;

    angle.x = angle.x & ANGCLIP;
    angle.y = angle.y & ANGCLIP;
    angle.z = angle.z & ANGCLIP;

    POINT3D outVertex[2];
    POINT3D inVertex[2];
    inVertex[0].x = currentPos.x;
    inVertex[0].y = currentPos.y;
    inVertex[0].z = currentPos.z;

    inVertex[1].x = destPos.x;
    inVertex[1].y = destPos.y;
    inVertex[1].z = destPos.z;

    smMATRIX inRotXMatrix;
    smMATRIX inRotYMatrix;
    smMATRIX inRotZMatrix;

    smMATRIX outMatrix;
    smIdentityMatrix(outMatrix);
    smIdentityMatrix(inRotXMatrix);
    smIdentityMatrix(inRotYMatrix);
    smIdentityMatrix(inRotZMatrix);

    smRotateXMatrix(inRotXMatrix, angle.x);
    smRotateYMatrix(inRotYMatrix, angle.y);
    smRotateZMatrix(inRotZMatrix, angle.z);

    smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
    smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

    int index=0;
    for(index = 0; index < 2; index++)
    {
        outVertex[index].x = inVertex[index].x * outMatrix._11 +
		                     inVertex[index].y * outMatrix._21 +
		                     inVertex[index].z * outMatrix._31 ;
        outVertex[index].x = outVertex[index].x >> FLOATNS;

	    outVertex[index].y = inVertex[index].x * outMatrix._12 +
		                     inVertex[index].y * outMatrix._22 +
		                     inVertex[index].z * outMatrix._32 ;
        outVertex[index].y = outVertex[index].y >> FLOATNS;

	    outVertex[index].z = inVertex[index].x * outMatrix._13 +
		                     inVertex[index].y * outMatrix._23 +
		                     inVertex[index].z * outMatrix._33 ;
        outVertex[index].z = outVertex[index].z >> FLOATNS;
    }

    memcpy(&currentPos, &outVertex[0], sizeof(currentPos));
    memcpy(&destPos, &outVertex[1], sizeof(destPos));

    currentPos.x   += x;
    currentPos.y   += y;
    currentPos.z   += z;

    destPos.x   += x;
    destPos.y   += y;
    destPos.z   += z;

    if(GetCameraCoord(currentPos) == FALSE)
			return FALSE;

    if(GetCameraCoord(destPos) == FALSE)
			return FALSE;


    sColor[ SMC_A ] = face->Transparency;
	sColor[ SMC_R ] = face->r;
	sColor[ SMC_G ] = face->g;
	sColor[ SMC_B ] = face->b;

    smTEXRECT texRect;
    texRect.left = 0;
    texRect.top  = 0;
    texRect.right = 1;
    texRect.bottom = 1;

    float dx     = float(destPos.x - currentPos.x); //대상 까지의 x축의 기울기를 구한다.
    float dy     = float(destPos.y - currentPos.y); //대상 까지의 y축의 기울기를 구한다.
    float length = (float)sqrt(dx*dx+dy*dy);        //대상 까지의 거리를 구한다.

    dx = dx/length*width; //날아가는 파티클의 넓이..
    dy = dy/length*width;

    D3DVECTOR persp;
    persp.x = -dy;
    persp.y = +dx;
    persp.z = 0;

    if (abs((int)dx) > 1.0f) currentPos.x -= (int)dx;
    if (abs((int)dy) > 1.0f) currentPos.y -= (int)dy;
    v[0] = smRender.AddRendVertex ( int(destPos.x-persp.x), int(destPos.y-persp.y), int(destPos.z), sColor );
    v[1] = smRender.AddRendVertex ( int(destPos.x+persp.x), int(destPos.y+persp.y), int(destPos.z), sColor );
    v[2] = smRender.AddRendVertex ( int(currentPos.x-persp.x), int(currentPos.y-persp.y), int(currentPos.z), sColor );
    v[3] = smRender.AddRendVertex ( int(currentPos.x+persp.x), int(currentPos.y+persp.y), int(currentPos.z), sColor );

    //첫번째 폴리곤 ( 1 - 2 - 3 );
    rf = &smRender.RendFace[ smRender.nRendFace++ ];
    rf->lpRendVertex[0] = v[0];
    rf->lpRendVertex[1] = v[1];
    rf->lpRendVertex[2] = v[2];
    rf->Matrial    = MaterialNum;		//메트리얼 복사
    rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
    rf->lpTexLink  = 0;

    //텍스쳐 연결
    smRender.AddRendTempTexLink( rf , 0,	texRect.left , texRect.bottom,
                                texRect.right , texRect.bottom,
                                texRect.left , texRect.top );


    //두번째 폴리곤 ( 2 - 4 - 3 );
    rf = &smRender.RendFace[ smRender.nRendFace++ ];
    rf->lpRendVertex[0] = v[1];
    rf->lpRendVertex[1] = v[3];
    rf->lpRendVertex[2] = v[2];
    rf->Matrial    = MaterialNum;		//메트리얼 복사
    rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
    rf->lpTexLink  = 0;

    //텍스쳐 연결
    smRender.AddRendTempTexLink( rf , 0,	texRect.right , texRect.bottom,
                                            texRect.right , texRect.top,
                                            texRect.left  , texRect.top );

    return true;
}

bool HoNewParticleEventSequence::AddFaceTrace(HoNewParticle *part)
{
    if(part == NULL)
        return false;

    if(part->SizeExt == 0) //SizeExt가 0이면 원점에서 날아가는 곳까지 그린다.
    {
        POINT3D destPos;
        POINT3D currentPos;


        std::list<D3DVECTOR>::iterator i;
        i = part->TraceList.begin();

        destPos.x = int(part->WorldPos.x*fONE+i->x*fONE);
        destPos.y = int(part->WorldPos.y*fONE+i->y*fONE);
        destPos.z = int(part->WorldPos.z*fONE+i->z*fONE);

        if(part->TraceList.size() == 2)
            ++i;
        currentPos.x = int(part->WorldPos.x*fONE+i->x*fONE);
        currentPos.y = int(part->WorldPos.y*fONE+i->y*fONE);
        currentPos.z = int(part->WorldPos.z*fONE+i->z*fONE);

        /*
        destPos.x = int(part->WorldPos.x*fONE+part->LocalPos.x*fONE);
        destPos.y = int(part->WorldPos.y*fONE+part->LocalPos.y*fONE);
        destPos.z = int(part->WorldPos.z*fONE+part->LocalPos.z*fONE);

        currentPos.x = int(part->WorldPos.x*fONE);
        currentPos.y = int(part->WorldPos.y*fONE);
        currentPos.z = int(part->WorldPos.z*fONE);
        */
        
        if(GetCameraCoord(currentPos) == FALSE)
			return FALSE;

		if(GetCameraCoord(destPos) == FALSE)
			return FALSE;

        smRENDVERTEX *v[4];
	    smRENDFACE	 *rf;

	    short		sColor[4];

        sColor[ SMC_R ] = int(part->Color.r);
	    sColor[ SMC_G ] = int(part->Color.g);
	    sColor[ SMC_B ] = int(part->Color.b);
        sColor[ SMC_A ] = int(part->Color.a);

        smTEXRECT texRect;
        texRect.left = 0;
        texRect.top  = 0;
        texRect.right = 1;
        texRect.bottom = 1;

        
        int size;
        size = (int)part->Size;
        size = size << FLOATNS;
        size = size >> 1;


        float dx     = float(destPos.x - currentPos.x); //대상 까지의 x축의 기울기를 구한다.
		float dy     = float(destPos.y - currentPos.y); //대상 까지의 y축의 기울기를 구한다.
		float length = (float)sqrt(dx*dx+dy*dy);        //대상 까지의 거리를 구한다.

        dx = dx/length*size; //날아가는 파티클의 넓이..
		dy = dy/length*size;

        D3DVECTOR persp;
		persp.x = -dy;
		persp.y = +dx;
		persp.z = 0;

		if (abs((int)dx) > 1.0f) currentPos.x -= (int)dx;
		if (abs((int)dy) > 1.0f) currentPos.y -= (int)dy;
        v[0] = smRender.AddRendVertex ( int(destPos.x-persp.x), int(destPos.y-persp.y), int(destPos.z), sColor );
		v[1] = smRender.AddRendVertex ( int(destPos.x+persp.x), int(destPos.y+persp.y), int(destPos.z), sColor );
        v[2] = smRender.AddRendVertex ( int(currentPos.x-persp.x), int(currentPos.y-persp.y), int(currentPos.z), sColor );
		v[3] = smRender.AddRendVertex ( int(currentPos.x+persp.x), int(currentPos.y+persp.y), int(currentPos.z), sColor );

        //첫번째 폴리곤 ( 1 - 2 - 3 );
        rf = &smRender.RendFace[ smRender.nRendFace++ ];
        rf->lpRendVertex[0] = v[0];
        rf->lpRendVertex[1] = v[1];
        rf->lpRendVertex[2] = v[2];
        rf->Matrial    = MaterialNum;		//메트리얼 복사
        rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
        rf->lpTexLink  = 0;

        //텍스쳐 연결
        smRender.AddRendTempTexLink( rf , 0,	texRect.left , texRect.top,
                                texRect.right , texRect.top,
                                texRect.left , texRect.bottom );


        //두번째 폴리곤 ( 2 - 4 - 3 );
        rf = &smRender.RendFace[ smRender.nRendFace++ ];
        rf->lpRendVertex[0] = v[1];
        rf->lpRendVertex[1] = v[3];
        rf->lpRendVertex[2] = v[2];
        rf->Matrial    = MaterialNum;		//메트리얼 복사
        rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
        rf->lpTexLink  = 0;

        //텍스쳐 연결
        smRender.AddRendTempTexLink( rf , 0,	texRect.right , texRect.top,
                                            texRect.right , texRect.bottom,
                                            texRect.left  , texRect.bottom );
    }
    else //SizeExt가 0이 아니면 SizeExt의 갯수 만큼 폴리곤을 그린다.
    {
		if(part->TraceList.size() < 2)
            return FALSE;

        POINT3D destPos;
        POINT3D currentPos;

        std::list<D3DVECTOR>::iterator i;
        i = part->TraceList.begin();
        destPos.x = int(part->WorldPos.x*fONE+i->x*fONE);
        destPos.y = int(part->WorldPos.y*fONE+i->y*fONE);
        destPos.z = int(part->WorldPos.z*fONE+i->z*fONE);

        int texSizeCount = 0;
        int test = part->TraceList.size();
        float cellSize = 1.f/(part->TraceList.size()-1);
        
        ++i;

        POINT3D OldVertex[2];
        memset(OldVertex, 0, sizeof(OldVertex));

        for (; i != part->TraceList.end();i++)
        {
            currentPos.x = int(part->WorldPos.x*fONE+i->x*fONE);
            currentPos.y = int(part->WorldPos.y*fONE+i->y*fONE);
            currentPos.z = int(part->WorldPos.z*fONE+i->z*fONE);

            if(GetCameraCoord(currentPos) == FALSE)
			    return FALSE;

            if(GetCameraCoord(destPos) == FALSE)
			    return FALSE;

            smRENDVERTEX *v[4];
	        smRENDFACE	 *rf;

	        short		sColor[4];

            sColor[ SMC_R ] = (int)part->Color.r;
	        sColor[ SMC_G ] = (int)part->Color.g;
	        sColor[ SMC_B ] = (int)part->Color.b;
            sColor[ SMC_A ] = (int)part->Color.a;

            smTEXRECT texRect;
            texRect.left   = 0;
            texRect.top    = (float)texSizeCount*cellSize;
            texRect.right  = 1;
            texRect.bottom = (float)(texSizeCount+1)*cellSize;


            int size;
            size = (int)part->Size;
            size = size << FLOATNS;
            size = size >> 1;

            //날아가는 방향의 벡터..
            float firstX, firstY, lastX, lastY;
            firstX = (float)0;
            firstY = (float)size;

            lastX = (float)0;
            lastY = (float)size;

            float dx = (float)destPos.x-(float)currentPos.x;
            if(dx == 0)
                dx = 1;
            float m = (float)destPos.y-(float)currentPos.y/dx;

            /*
            if(m > 1.0f)
            {
                firstX = (float)size;
                lastX  = (float)size;
            }

            if(m < -1.0f)
            {
                firstX = -(float)size;
                lastX = -(float)size;
            }
            */

            //firstX = 0.f;
            //firstY = (float)size;

            //lastX = 0.f;
            //lastY = (float)size;


            v[0] = smRender.AddRendVertex ( int(destPos.x+firstX), int(destPos.y+firstY), int(destPos.z), sColor );
            v[1] = smRender.AddRendVertex ( int(destPos.x-firstX), int(destPos.y-firstY), int(destPos.z), sColor );

            destPos.x = int(part->WorldPos.x*fONE+i->x*fONE);
            destPos.y = int(part->WorldPos.y*fONE+i->y*fONE);
            destPos.z = int(part->WorldPos.z*fONE+i->z*fONE);

            v[2] = smRender.AddRendVertex ( int(currentPos.x+lastX), int(currentPos.y+lastY), int(currentPos.z), sColor );
            v[3] = smRender.AddRendVertex ( int(currentPos.x-lastX), int(currentPos.y-lastY), int(currentPos.z), sColor );

            //첫번째 폴리곤 ( 1 - 2 - 3 );
            rf = &smRender.RendFace[ smRender.nRendFace++ ];
            rf->lpRendVertex[0] = v[0];
            rf->lpRendVertex[1] = v[1];
            rf->lpRendVertex[2] = v[2];
            rf->Matrial    = MaterialNum;		//메트리얼 복사
            rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
            rf->lpTexLink  = 0;

            //텍스쳐 연결
            smRender.AddRendTempTexLink( rf , 0,	texRect.left , texRect.top,
                                texRect.right , texRect.top,
                                texRect.left , texRect.bottom );


            //두번째 폴리곤 ( 2 - 4 - 3 );
            rf = &smRender.RendFace[ smRender.nRendFace++ ];
            rf->lpRendVertex[0] = v[1];
            rf->lpRendVertex[1] = v[3];
            rf->lpRendVertex[2] = v[2];
            rf->Matrial    = MaterialNum;		//메트리얼 복사
            rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
            rf->lpTexLink  = 0;

            //텍스쳐 연결
            smRender.AddRendTempTexLink( rf , 0, texRect.right , texRect.top,
                                                 texRect.right , texRect.bottom,
                                                 texRect.left  , texRect.bottom );

            texSizeCount++;
        }
	}
    return true;
}

smRENDFACE *HoNewParticleEventSequence::AddFace2DBillBoard( smFACE2D *face , D3DVECTOR inAngle)
{
	int x,y,z;
	int rx , ry, rz;
	int width , height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[ SMC_A ] = face->Transparency;
	sColor[ SMC_R ] = face->r;
	sColor[ SMC_G ] = face->g;
	sColor[ SMC_B ] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;

	//중심 좌표를 카메라 좌표를 변환
	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		 y * smRender.mCamera._21 +
		 z * smRender.mCamera._31 ;

	ry = x * smRender.mCamera._12 +
		 y * smRender.mCamera._22 +
		 z * smRender.mCamera._32 ;

	rz = x * smRender.mCamera._13 +
		 y * smRender.mCamera._23 +
		 z * smRender.mCamera._33 ;

	x = rx>>FLOATS_EM;
	y = ry>>FLOATS_EM;
	z = rz>>FLOATS_EM;

//	z -= 12*fONE;
	//z -= 24*fONE;


	if ( z<SMFLOAT_DIST_NEARZ ) return NULL;

	width  = face->width >> 1;
	height = face->height >> 1;


	//회전 적용
	//int		ex[4],ey[4];
	//int		mx,my;
	//int		sin,cos;

    POINT3D angle;
    angle.x = (int)inAngle.x;
    angle.y = (int)inAngle.y;
    angle.z = (int)inAngle.z;

    angle.x = angle.x & ANGCLIP;
    angle.y = angle.y & ANGCLIP;
    angle.z = angle.z & ANGCLIP;

    POINT3D outVertex[4];
    POINT3D inVertex[4];
    memset(outVertex, 0, sizeof(outVertex));
    inVertex[0].x = -width;
    inVertex[0].y = -height;
    inVertex[0].z = 0;

    inVertex[1].x =  width;
    inVertex[1].y = -height;
    inVertex[1].z = 0;

    inVertex[2].x = -width;
    inVertex[2].y = height;
    inVertex[2].z = 0;

    inVertex[3].x = width;
    inVertex[3].y = height;
    inVertex[3].z = 0;

    smMATRIX inRotXMatrix;
    smMATRIX inRotYMatrix;
    smMATRIX inRotZMatrix;

    smMATRIX outMatrix;
    smIdentityMatrix(outMatrix);
    smIdentityMatrix(inRotXMatrix);
    smIdentityMatrix(inRotYMatrix);
    smIdentityMatrix(inRotZMatrix);

    smRotateXMatrix(inRotXMatrix, angle.x);
    smRotateYMatrix(inRotYMatrix, angle.y);
    smRotateZMatrix(inRotZMatrix, angle.z);

    smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
    smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

    int index=0;
    for(index = 0; index < 4; index++)
    {
        outVertex[index].x = inVertex[index].x * outMatrix._11 +
		                     inVertex[index].y * outMatrix._21 +
		                     inVertex[index].z * outMatrix._31 ;
        outVertex[index].x = outVertex[index].x >> FLOATNS;

	    outVertex[index].y = inVertex[index].x * outMatrix._12 +
		                     inVertex[index].y * outMatrix._22 +
		                     inVertex[index].z * outMatrix._32 ;
        outVertex[index].y = outVertex[index].y >> FLOATNS;

	    outVertex[index].z = inVertex[index].x * outMatrix._13 +
		                     inVertex[index].y * outMatrix._23 +
		                     inVertex[index].z * outMatrix._33 ;
        outVertex[index].z = outVertex[index].z >> FLOATNS;
    }

    //렌더링 버텍스 추가 ( 좌표 직접 입력 )
	v[0] = smRender.AddRendVertex ( x+outVertex[0].x , y+outVertex[0].y , z+outVertex[0].z, sColor );
	v[1] = smRender.AddRendVertex ( x+outVertex[1].x , y+outVertex[1].y , z+outVertex[1].z, sColor );
	v[2] = smRender.AddRendVertex ( x+outVertex[2].x , y+outVertex[2].y , z+outVertex[2].z, sColor );
	v[3] = smRender.AddRendVertex ( x+outVertex[3].x , y+outVertex[3].y , z+outVertex[3].z, sColor );

	//첫번째 폴리곤 ( 1 - 2 - 3 );
	rf = &smRender.RendFace[ smRender.nRendFace++ ];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial    = face->MatNum ;		//메트리얼 복사
	rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
	rf->lpTexLink  = 0;

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


	return &smRender.RendFace[ smRender.nRendFace-1 ];
}

void HoNewParticleEventSequence::Draw(int x, int y, int z, int ax, int ay, int az)
{
    if(MaterialNum == -1)
        return;                         
        
	smRender.Init();
    smMaterialGroup->smMaterial[MaterialNum].TwoSide = TRUE;
	smMaterialGroup->smMaterial[MaterialNum].BlendType  = SrcBlendMode;
    smRender.SetMaterialGroup(smMaterialGroup);
	smRender.SetCameraPosi(x, y, z, ax, ay, az);

    //블렌드 모드가 Shadow일 경우 제대루 안나와서 SelfIllum을 먹인다.
	
	if(SrcBlendMode == SMMAT_BLEND_SHADOW)
	{
		smMaterialGroup->smMaterial[MaterialNum].SelfIllum = TRUE;
    }
	
	//각각의 파티클을 찍는다.
    for (int q=0; q < NumParticles; q++)
    {
        // Render each particle a bunch of times to get a blurring effect
        if (Particles->IsAlive(q))
        {
            HoNewParticle &part = Particles->GetAt(q);
            //로칼 회전...
            if(part.LocalAngle.x != 0 || part.LocalAngle.y != 0 || part.LocalAngle.z != 0)
            {
                smMATRIX inRotXMatrix;
                smMATRIX inRotYMatrix;
                smMATRIX inRotZMatrix;

                smMATRIX outMatrix;
                smIdentityMatrix(outMatrix);
                smIdentityMatrix(inRotXMatrix);
                smIdentityMatrix(inRotYMatrix);
                smIdentityMatrix(inRotZMatrix);

                smRotateXMatrix(inRotXMatrix, (int)part.LocalAngle.x&ANGCLIP);
                smRotateYMatrix(inRotYMatrix, (int)part.LocalAngle.y&ANGCLIP);
                smRotateZMatrix(inRotZMatrix, (int)part.LocalAngle.z&ANGCLIP);

                smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
				smMatrixMult(outMatrix, outMatrix, inRotZMatrix);
				
				POINT3D inlocalPos;
                inlocalPos.x = (int)(part.LocalPos.x*fONE);
                inlocalPos.y = (int)(part.LocalPos.y*fONE);
                inlocalPos.z = (int)(part.LocalPos.z*fONE);
			
				POINT3D outlocalPos;
                outlocalPos.x = inlocalPos.x * outMatrix._11+
                                inlocalPos.y * outMatrix._21+
                                inlocalPos.z * outMatrix._31;
                

                outlocalPos.y = inlocalPos.x * outMatrix._12+
                                inlocalPos.y * outMatrix._22+
                                 inlocalPos.z * outMatrix._32;
                

                outlocalPos.z = inlocalPos.x * outMatrix._13+
                                inlocalPos.y * outMatrix._23+
                                inlocalPos.z * outMatrix._33;
				
				//전체적으로 각도를 돌리고 싶을때 행렬값들..
				if(Angle.x != 0 || Angle.y != 0 || Angle.z != 0)
				{
					smIdentityMatrix(outMatrix);
					smIdentityMatrix(inRotXMatrix);
					smIdentityMatrix(inRotYMatrix);
					smIdentityMatrix(inRotZMatrix);

					smRotateXMatrix(inRotXMatrix, (int)Angle.x&ANGCLIP);
					smRotateYMatrix(inRotYMatrix, (int)Angle.y&ANGCLIP);
					smRotateZMatrix(inRotZMatrix, (int)Angle.z&ANGCLIP);

					smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
					smMatrixMult(outMatrix, outMatrix, inRotZMatrix);
					
					memcpy(&inlocalPos, &outlocalPos, sizeof(inlocalPos));
					inlocalPos.x = inlocalPos.x/fONE;
					inlocalPos.y = inlocalPos.y/fONE;
					inlocalPos.z = inlocalPos.z/fONE;

					outlocalPos.x = inlocalPos.x * outMatrix._11+
									inlocalPos.y * outMatrix._21+
									inlocalPos.z * outMatrix._31;
                

					outlocalPos.y = inlocalPos.x * outMatrix._12+
									inlocalPos.y * outMatrix._22+
									inlocalPos.z * outMatrix._32;
	                

					outlocalPos.z = inlocalPos.x * outMatrix._13+
									inlocalPos.y * outMatrix._23+
									inlocalPos.z * outMatrix._33;
				}
				
 				Face2d.x = outlocalPos.x/fONE+(int)(part.WorldPos.x*fONE);
				Face2d.y = outlocalPos.y/fONE+(int)(part.WorldPos.y*fONE);
				Face2d.z = outlocalPos.z/fONE+(int)(part.WorldPos.z*fONE);
			}
            else
            {
				POINT3D outlocalPos;
				memset(&outlocalPos, 0, sizeof(outlocalPos));
				//전체적으로 각도를 돌리고 싶을때 행렬값들..
				if(Angle.x != 0 || Angle.y != 0 || Angle.z != 0)
				{
					smMATRIX inRotXMatrix;
					smMATRIX inRotYMatrix;
					smMATRIX inRotZMatrix;

					smMATRIX outMatrix;
					POINT3D inlocalPos;
					

 					smIdentityMatrix(outMatrix);
					smIdentityMatrix(inRotXMatrix);
					smIdentityMatrix(inRotYMatrix);
					smIdentityMatrix(inRotZMatrix);

					smRotateXMatrix(inRotXMatrix, (int)Angle.x&ANGCLIP);
					smRotateYMatrix(inRotYMatrix, (int)Angle.y&ANGCLIP);
					smRotateZMatrix(inRotZMatrix, (int)Angle.z&ANGCLIP);

					smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
					smMatrixMult(outMatrix, outMatrix, inRotZMatrix);
					
					memcpy(&inlocalPos, &outlocalPos, sizeof(inlocalPos));
					inlocalPos.x = (int)(part.LocalPos.x*fONE);
					inlocalPos.y = (int)(part.LocalPos.y*fONE);
					inlocalPos.z = (int)(part.LocalPos.z*fONE);
					
					outlocalPos.x = inlocalPos.x * outMatrix._11+
									inlocalPos.y * outMatrix._21+
									inlocalPos.z * outMatrix._31;
                

					outlocalPos.y = inlocalPos.x * outMatrix._12+
									inlocalPos.y * outMatrix._22+
									inlocalPos.z * outMatrix._32;
	                

					outlocalPos.z = inlocalPos.x * outMatrix._13+
									inlocalPos.y * outMatrix._23+
									inlocalPos.z * outMatrix._33;
					//Camera각도 입력.
					Face2d.x = (int)(part.WorldPos.x*fONE)+outlocalPos.x/fONE;
					Face2d.y = (int)(part.WorldPos.y*fONE)+outlocalPos.y/fONE;
					Face2d.z = (int)(part.WorldPos.z*fONE)+outlocalPos.z/fONE;
				}
				else
				{
					//Camera각도 입력.
  					Face2d.x = (int)(part.WorldPos.x*fONE+part.LocalPos.x*fONE);
					Face2d.y = (int)(part.WorldPos.y*fONE+part.LocalPos.y*fONE);
					Face2d.z = (int)(part.WorldPos.z*fONE+part.LocalPos.z*fONE);
				}
            }

            Face2d.r = (int)part.Color.r;
            Face2d.g = (int)part.Color.g;
            Face2d.b = (int)part.Color.b;
            Face2d.Transparency = (int)part.Color.a;

            Face2d.TexRect.left = 0;
            Face2d.TexRect.top = 0;
            Face2d.TexRect.right = 1;
            Face2d.TexRect.bottom = 1;
            Face2d.MatNum = MaterialNum;



			int size = (int)(part.Size*fONE);
            //Face2d.width  = size<<FLOATNS;
            //Face2d.height = size<<FLOATNS;
            Face2d.width  = size;
            Face2d.height = size;
            int sizeExt = (int)(part.SizeExt*fONE);
            if(sizeExt != 0.0f)
                //Face2d.height = sizeExt<<FLOATNS;
                Face2d.height = sizeExt;

			/*
            int size = (int)part.Size;
            Face2d.width  = size<<FLOATNS;
            Face2d.height = size<<FLOATNS;

            int sizeExt = (int)part.SizeExt;
            if(sizeExt != 0.0f)
                Face2d.height = sizeExt<<FLOATNS;
			*/

            //빌보드용..
            if(ParticleType == TYPE_ONE)
            {
                if(part.PartAngle.x == 0 && part.PartAngle.y == 0 && part.PartAngle.z == 0)
                    //smRender.AddFace2D(&Face2d);
                    AddFace2DBillBoard(&Face2d);
                else
                    AddFace2DBillBoard(&Face2d, part.PartAngle);
            }//월드 모양으로 나타나는 폴리곤..
            else if(ParticleType == TYPE_TWO)
            {
				if(Angle.x == 0 && Angle.y == 0 && Angle.z == 0)
				{
					if(part.PartAngle.x == 0 && part.PartAngle.y == 0 && part.PartAngle.z == 0)
						AddFace2dPlane(&Face2d);
					else
					{
						//if(Angle.x != 0 || Angle.y != 0 || Angle.z != 0)
						//{
							//D3DVECTOR angle;
							//angle.x = (float)Angle.x;
							//angle.y = (float)Angle.y;
							//angle.z = (float)Angle.z;

							
							//AddFace2dPlane(&Face2d, angle);
						//}
						//else
							AddFace2dPlane(&Face2d, part.PartAngle);
					}
				}
				else
				{
					D3DVECTOR angle;
					angle.x = part.PartAngle.x + Angle.x;
					angle.y = part.PartAngle.y + Angle.y;
					angle.z = part.PartAngle.z + Angle.z;
					
					AddFace2dPlane(&Face2d, angle);
				}
            }
            else if(ParticleType == TYPE_THREE)
            {
				/*
				if(Angle.x != 0 || Angle.y != 0 || Angle.z != 0)
				{
					D3DVECTOR worldAddAngle;
 					memcpy(&worldAddAngle, &Angle, sizeof(Angle) );

					worldAddAngle.x = worldAddAngle.x + part.PartAngle.x;
					worldAddAngle.y = worldAddAngle.y + part.PartAngle.y;
					worldAddAngle.z = worldAddAngle.z + part.PartAngle.z;

					AddFaceThree(&Face2d, worldAddAngle);
				}
				else
				*/
				AddFaceThree(&Face2d, part.PartAngle);
            }
            //파티클의 자취를 따라 가는 폴리곤..
            else if(ParticleType == TYPE_FOUR)
            {
                AddFaceTrace(&part);
            }
        }
    }

	renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE);
	renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	//if(ParticleType == TYPE_THREEE)
	//{
		//int tempAngleX = ax;
		//smRender.SetCameraPosi(x, y, z, ax, ay, az);
	//}
    smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
    smRender.ClipRendFace();
    smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();

	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
}



/*
//평면 폴리곤을 추가하는 루틴..
bool AddFaceWorldPlane(smFACE2D *inface)
{
	int x,y,z;
	int width , height;
	
	x = inface->x;
	y = inface->y;
	z = inface->z;
	
	width  = inface->width >> 1; //반으로 나눈다.
	height = inface->height >> 1;
	
	Vertex[0].x   = x-width;
	Vertex[0].y   = y;
	Vertex[0].z   = z+height;
	
	Vertex[1].x   = x+width;
	Vertex[1].y   = y;
	Vertex[1].z   = z+height;
	
	Vertex[2].x   = x-width;
	Vertex[2].y   = y;
	Vertex[2].z   = z-height;
	
	Vertex[3].x   = x+width;
	Vertex[3].y   = y;
	Vertex[3].z   = z-height;

    int index = 0;
	for(index = 0; index < 4; index++)
	{
		Vertex[index].sDef_Color[0] = inface->r;
		Vertex[index].sDef_Color[1] = inface->g;
		Vertex[index].sDef_Color[2] = inface->b;
		Vertex[index].sDef_Color[3] = inface->Transparency;
	}
	
	//Texture 좌표 관련 초기화...
	TexLink[0].hTexture = 0;
	TexLink[0].NextTex = 0;
	
	TexLink[0].u[0] = 0.0f;
	TexLink[0].v[0] = 0.0f;
	TexLink[0].u[1] = 1.0f;
	TexLink[0].v[1] = 0.0f;
	TexLink[0].u[2] = 0.0f;
	TexLink[0].v[2] = 1.0f;
	
	TexLink[1].hTexture = 0;
	TexLink[1].NextTex = 0;
	TexLink[1].u[0] = 0.0f;
	TexLink[1].v[0] = 1.0f;
	TexLink[1].u[1] = 1.0f;
	TexLink[1].v[1] = 0.0f;
	TexLink[1].u[2] = 1.0f;
	TexLink[1].v[2] = 1.0f;

	
	//삼각형 컬링 때문에....
	FlatFace[0].Vertex[0] = 0;
	FlatFace[0].Vertex[1] = 1;
	FlatFace[0].Vertex[2] = 2;
	FlatFace[0].Vertex[3] = inface->MatNum;
	FlatFace[0].lpTexLink = &TexLink[0];
	FlatFace[0].sum = 0;

	FlatFace[1].Vertex[0] = 2;
	FlatFace[1].Vertex[1] = 1;
	FlatFace[1].Vertex[2] = 3;
	FlatFace[1].Vertex[3] = inface->MatNum;
	FlatFace[1].lpTexLink = &TexLink[1];
	FlatFace[1].sum = 0;
	

	smRender.InitStageMesh(Vertex, SumCount);

	for(index = 0; index < 2; index++)
		smRender.AddStageFace(&FlatFace[index]);
	SumCount++;
	
	return true;
}
*/