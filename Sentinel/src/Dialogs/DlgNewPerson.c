#include "..\..\inc\Dialogs\DlgNewPerson.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Engine\Database.h"

PersonPtr pPerson = NULL;

BOOL CALLBACK DlgNewPersonProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			Person p;
			pPerson = &p;
			memset(pPerson, 0, sizeof(Person));

			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			MessageBeep(MB_ICONINFORMATION);
			return TRUE;
		}

		case WM_CLOSE:
		{
			// return the id of the created person
			EndDialog(hDlg, (INT_PTR)pPerson->Id);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCANCEL:
				{
					// operation cancelled
					pPerson->Id = -1;
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