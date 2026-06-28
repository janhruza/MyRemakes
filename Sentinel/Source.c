#include <Windows.h>
#include "inc/Core.h"
#include "res/resource.h"

#include "inc/Engine/Database.h"
#include "inc/Dialogs/DlgMainWindow.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	if (CoInitializeApp() == FALSE)
	{
		// unable to initialize
		WCHAR text[MAX_PATH];
		LoadString(hInstance, IDS_MSG_ERR_INIT, text, MAX_PATH);
		MessageBox(NULL, text, TEXT("Error"), MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// start the application
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGMAINWINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}