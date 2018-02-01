#ifndef _HO_MIN_MAX_H
#define _HO_MIN_MAX_H
#include <vector>
#include <string>

#ifndef D3D_OVERLOADS
#define D3D_OVERLOADS
#endif

using namespace std;
inline void MakeUpperCase(std::string &str)
{
	for (std::string::iterator i = str.begin(); i != str.end(); i++)
	{
		*i = toupper(*i);
	}
}

inline std::string RemoveQuotes(std::string &str)
{
	for (std::string::iterator i = str.begin(); i != str.end(); i++)
	{
		if (*i == '\"')
		{
			i = str.erase(i); if (i == str.end()) 
				break;
		}
	}
	return(str);
}


int RandomNumber(int iMin, int iMax);
float RandomNumber(float fMin, float fMax);
D3DVECTOR RandomNumber(D3DVECTOR vMin, D3DVECTOR vMax);
D3DCOLORVALUE RandomNumber(D3DCOLORVALUE Min, D3DCOLORVALUE Max);


/*
float RandomNumber(float fMin, float fMax)
{
  if (fMin == fMax) return(fMin);
  float fRandom = (float)rand() / (float)RAND_MAX;
  return((fRandom * (float)fabs(fMax-fMin))+fMin);
}


int RandomNumber(int iMin, int iMax)
{
  if (iMin == iMax) return(iMin);
  return((rand() % (abs(iMax-iMin)+1))+iMin);
}

D3DVECTOR RandomNumber(D3DVECTOR vMin, D3DVECTOR vMax)
{
  float x = RandomNumber(vMin.x, vMax.x);
  float y = RandomNumber(vMin.y, vMax.y);
  float z = RandomNumber(vMin.z, vMax.z);

  D3DVECTOR temp;
  temp.x = x;
  temp.y = y;
  temp.z = z;

  return(temp);
}


D3DCOLORVALUE RandomNumber(D3DCOLORVALUE Min, D3DCOLORVALUE Max)
{
  float r = RandomNumber(Min.r, Max.r);
  float g = RandomNumber(Min.g, Max.g);
  float b = RandomNumber(Min.b, Max.b);
  float a = RandomNumber(Min.a, Max.a);

  D3DCOLORVALUE temp;
  temp.r = r;
  temp.g = g;
  temp.b = b;
  temp.a = a;
  return (temp);
}
*/

//최대값 최소값을 구하는 클래스
template <class T> class HoMinMax
{
	public:
		HoMinMax()
		{ 
			Min = T(); Max = T();
		}
		
		HoMinMax(T tMin, T tMax) 
		{ 
			Min = tMin; Max = tMax;
		}

		~HoMinMax() 
		{ 
		}

		T Min;
		T Max;

		T GetRandomNumInRange(void)
		{ 
			return(RandomNumber(Min, Max));
		}
		
		T GetRange(void) 
		{ 
			return(abs(Max-Min));
		}
};

#endif