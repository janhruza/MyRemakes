#include "..\..\inc\Controls\CtlLoginScr.h"
#include "..\..\res\resource.h"
#include <CommCtrl.h>

INT_PTR CALLBACK CtlLoginScrProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDRETRY:
				{
					// clear button clicked
					HWND hPin = GetDlgItem(hDlg, IDC_PIN);
					SetWindowText(hPin, TEXT(""));
					return TRUE;
				}

				case IDC_BTN_LOGIN:
				{
					// login button clicked
					return TRUE;
				}

				default: break;
			}

			return FALSE;
		}

		case WM_NOTIFY:
		{
			if (!lParam) return FALSE;

			LPNMHDR pnmh = (LPNMHDR)lParam;
			if (pnmh->idFrom == IDC_CREATE_ACCOUNT)
			{
				if (pnmh->code == NM_CLICK || pnmh->code == NM_RETURN)
				{
					// create account link clicked
					return TRUE;
				}
			}
			return FALSE;
		}

		// other messages
		default: return FALSE;
	}
	return FALSE;
}