#include <Windows.h>
#include "res/resource.h"

INT_PTR CALLBACK DialogProc(HWND hDlg, int msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			EndDialog(hDlg, IDCLOSE);
			return TRUE;

		case WM_SYSCOMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case SC_CLOSE:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
			}

			return FALSE;
		}
		default: return FALSE;
	}
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DialogProc);
	return 0;
}