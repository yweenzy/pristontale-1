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
	void SetFileName(char* FileName);
public:
	inline int  GetNpcWavNum(){return m_nNpcWav;}
private:
	int m_nNpcWav;
	int m_nNpcWav2;
	char m_chFileName[64];
};
#endif

#ifdef NPCWAV_CPP
class CNpcWav g_cNpcWav;
#else
extern class CNpcWav g_cNpcWav;
#endif