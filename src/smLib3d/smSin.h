#ifndef _SIN_H
#define _SIN_H

#ifndef PI
#define PI 3.14159265358979323846f
#endif

//3.14592654
extern	int *GetSin;
extern	int *GetCos;

extern	int *sdGetSin;
extern	int *sdGetCos;

extern double *dbGetSin;
extern double *dbGetCos;


/*
#define ANGLE_180		4096
#define ANGLE_90		2048
#define ANGLE_360		8192
*/

#define ANGLE_360		4096
//#define ANGLE_360		16384

#define ANGLE_1			(ANGLE_360/360)
#define ANGLE_45		(ANGLE_360/8)
#define ANGLE_90		(ANGLE_360/4)
#define ANGLE_180		(ANGLE_360/2)
#define ANGLE_270		(ANGLE_180+ANGLE_90)
#define ANGLE_MASK		(ANGLE_360-1)

#define smMULT_PIE		((ANGLE_180/PI)+0.5)


int zDSin(int deg);

int zRSin(double rad);

int zDCos(int deg);

int zRCos(double rad);

void initSinCos();


#endif


