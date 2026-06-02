#include "..\..\inc\Dialogs\DlgMainWindow.h"
#include "..\..\res\resource.h"
#include <CommCtrl.h>

// custom headers
#include "..\..\inc\Controls\CtlLoginScr.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"

// dialog handles

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
			// iniotialize the main window and show the login screen
			hAppWindow = hDlg;
			CoInitWindows(hDlg);
			CoHideAllControls();
			CoShowControl(hCtlLogin);
			WhFitContent(hDlg, hCtlLogin);
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