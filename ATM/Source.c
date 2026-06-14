#include <Windows.h>

#include "res/resource.h"
#include "inc/Dialogs/DlgMainWindow.h"
#include "inc/Core.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_WINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}