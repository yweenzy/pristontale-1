#if defined(TIMER_CPP)

#else

#endif

//게임에 들어가기 전에 1 frame의 시간을 설정한다.
void InitFrameTime(DWORD ft);

//Time을 현재시각으로 재설정해 클리어한다.
void TimeClear(void);

//TimeClear()함수를 부른후 부터 경과한 시간 에 따라 스킵할 프레임수 리턴
DWORD GetSkipFrame(void);

