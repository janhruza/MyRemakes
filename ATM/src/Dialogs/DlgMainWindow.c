#include "..\..\inc\Dialogs\DlgMainWindow.h"
#include "..\..\res\resource.h"

// custom headers
#include "..\..\inc\Controls\CtlLoginScr.h"
#include "..\..\inc\WindowHelper.h"

INT_PTR CALLBACK DlgMainWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}

		case WM_INITDIALOG:
		{
			HINSTANCE hInst = GetModuleHandle(NULL);
			HWND hCtl = CreateDialog(hInst, MAKEINTRESOURCE(IDC_SCR_LOGIN), hDlg, CtlLoginScrProc);
			ShowWindow(hCtl, SW_SHOW);

			// adjust window size
			WhFitContent(hDlg, hCtl);
			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case SC_CLOSE:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;

				// invalid option
				default: return FALSE;
			}
		}

		// other messages
		default:
			return FALSE;
	}
}