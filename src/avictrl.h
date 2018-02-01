#include "common.h"
#include "smLib3d\\smd3d.h"

#pragma comment( lib, "vfw32.lib" )

int OpenVideoFile (char *AVIFile );
void CloseAVIData();
void AVIDrawSurface(DIRECTDRAWSURFACE *lpDDSSource, int frame );
