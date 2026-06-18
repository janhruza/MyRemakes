#include <Windows.h>
#include "inc/DlgMainWindow.h"
#include "inc/Core.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	INT_PTR result = 0;
	BOOL keepRunning = TRUE;
	while (keepRunning)
	{
		result = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DlgMainWindowProc);
		switch (result)
		{
		case IDCLOSE:
		case ID_QUIT:
			keepRunning = FALSE;
			break;

		case ID_RUN_LOOP:
			break;
		}
	}

	return result;
}