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
				case IDC_CREATE_ACCOUNT:
					MessageBeep(MB_ICONINFORMATION);
					return TRUE;
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