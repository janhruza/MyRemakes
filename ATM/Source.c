#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

#include "res/resource.h"
#include "inc/Dialogs/DlgMainWindow.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	InitCommonControls();
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_WINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}