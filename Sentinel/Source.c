#include <Windows.h>
#include "inc/Core.h"
#include "res/resource.h"

#include "inc/Engine/Database.h"
#include "inc/Dialogs/DlgMainWindow.h"
#include "inc/Windows/WndMainWindow.h"

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
	//DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGMAINWINDOW), NULL, DlgMainWindowProc);

	if (!CreateMainWindow(hInstance, WndMainWindowProc))
	{
		return EXIT_FAILURE;
	}

	HWND hWnd = CreateWindowEx(
		0,
		SENTINEL_CLASS_NAME,
		SENTINEL_TITLE,
		WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL)
	{
		return EXIT_FAILURE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// post exit cleanup
	BOOL ecode = CoAppCleanup();
	return ecode == TRUE ? EXIT_SUCCESS : EXIT_FAILURE;
}