#include <Windows.h>
#include "inc/DlgMainWindow.h"
#include "inc/Core.h"

#include "inc/FocusSession.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	INT_PTR result = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DlgMainWindowProc);
	return result;
}