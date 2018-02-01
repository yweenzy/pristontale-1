#ifndef __NPCWAV_H__
#define __NPCWAV_H__

#define NPCWAVE_CALL	0

class CNpcWav
{
public:
	CNpcWav();
	~CNpcWav();
public:
	void Main();
	void SetNpcWavNum(int num);
public:
	inline int  GetNpcWavNum(){return g_nNpcWav;}
private:
	int m_nNpcWav;
};
#endif

#ifdef NPCWAV_CPP
class CNpcWav g_cNpcWav;
#else
extern class CNpcWav g_cNpcWav;
#endif