#include <Windows.h>
#include "inc/DlgMainWindow.h"
#include "res/resource.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DlgMainWindowProc);
	return 0;
}