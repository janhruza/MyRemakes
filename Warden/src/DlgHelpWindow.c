#include "..\inc\DlgHelpWindow.h"
#include "..\res\resource.h"

#include <shellapi.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

BOOL CALLBACK DlgHelpWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			MessageBeep(MB_ICONINFORMATION);
			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, IDCLOSE);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				default: return FALSE;
			}
		}

		case WM_NOTIFY:
		{
			LPNMHDR pNmHdr = (LPNMHDR)lParam;
			if (pNmHdr->idFrom == IDC_LINK)
			{
				if (pNmHdr->code == NM_CLICK || pNmHdr->code == NM_RETURN)
				{
					PNMLINK pNml = (PNMLINK)lParam;
					ShellExecute(hDlg, TEXT("open"), pNml->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
					return TRUE;
				}
			}
			return FALSE;
		}

		default: return FALSE;
	}
}