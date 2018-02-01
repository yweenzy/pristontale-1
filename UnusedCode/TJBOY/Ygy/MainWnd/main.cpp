#include "GlobalHeader.h"
#include "MainWindow.h"


	

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{	
	if(!g_MainWindow.Create(hInstance)) return 0;

	return g_MainWindow.Run();
}


