#include "..\..\inc\Dialogs\DlgMainWindow.h"
#include "..\..\res\resource.h"
#include <CommCtrl.h>

// custom headers
#include "..\..\inc\Controls\CtlLoginScr.h"
#include "..\..\inc\WindowHelper.h"

// dialog handles
HWND hDlgLoginScr;

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
			hDlgLoginScr = CreateDialog(hInst, MAKEINTRESOURCE(IDC_SCR_LOGIN), hDlg, CtlLoginScrProc);
			SetParent(hDlgLoginScr, hDlg);
			ShowWindow(hDlgLoginScr, SW_SHOW);

			// adjust window size
			WhFitContent(hDlg, hDlgLoginScr);
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