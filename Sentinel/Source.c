#include <Windows.h>
#include "inc/Core.h"
#include "res/resource.h"

#include "inc/Dialogs/DlgMainWindow.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGMAINWINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}