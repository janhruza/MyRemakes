#include <Windows.h>
#include "res/resource.h"
#include "inc/Dialogs/DlgAbout.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGABOUT), NULL, DlgAboutProc);
}