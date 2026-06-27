#include "..\..\inc\Dialogs\DlgNewPerson.h"
#include "..\..\inc\Core.h"

BOOL CALLBACK DlgNewPersonProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			EndDialog(hDlg, TRUE);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCANCEL:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case IDOK:
				{
					return CoNotImplemented(hDlg);
				}
			}

			return FALSE;
		}

		default: return FALSE;
	}
}