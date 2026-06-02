#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

#include "res/resource.h"
#include "inc/Dialogs/DlgMainWindow.h"
#include "inc/Core.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES | ICC_LINK_CLASS;

	if (!InitCommonControlsEx(&icex))
	{
		return 0;
	}

	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_WINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}