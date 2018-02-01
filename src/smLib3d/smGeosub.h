
extern int	GeoResult_X;
extern int	GeoResult_Y;
extern int	GeoResult_Z;


//점이 삼각형 안에 들어 있는지(삼각형 라인에 걸치는 점은 들어가지 않는걸루 처리) ->호바람 제작
//bool    PointInTri(int a1, int b1, int a2, int b2, int a3, int b3, int pointX, int pointY);
//점이 삼각형 안에 들어 있는지(삼각형 라인에 걸치는 점은 들어가지 않는걸루 처리) ->호바람 제작
bool PointInTri(float a1, float a2, float a3, float b1, float b2, float b3, float mouseX, float mouseY);

// 이동된 지역 좌표값을 구하는 것이구나! 놀랍다.
void GetMoveLocation(int x, int y, int z, int AngX, int AngY, int AngZ );
//  상대의 위치를 파악하여 이동해야 할 각도를 알려준다.
void GetTraceAngle( POINT3D *posi , POINT3D *angle , int tx , int ty , int tz );
int CheckLocateBox( int sx, int sz , int tx, int tz , int size );
int GetSubAngle( int a1, int a2 );
void GetRadian3D(int x1 , int y, int y1, int x2, int y_, int y2 );
int GetRadian2D(int x1 ,int y1, int x2, int y2 );
int GetDistance(int x1 , int y, int y1, int x2, int y_, int y2 );

// 카메라 추적 메트릭스 만들기 ( sx,sy,sz -카메라  tx,ty,tz - 추적점 )
int MakeTraceMatrix ( eCAMERA_TRACE *lpeTrace , int sx, int sy, int sz, int tx, int ty, int tz );
