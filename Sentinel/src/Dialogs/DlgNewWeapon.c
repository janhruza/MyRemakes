/*
* DlgNewWeapon.c
* Representing the new weapon dialog.
* This dialog is meant only to register new weapons to the database.
* This dialog is not meant to add new weapons to a player.
*/

#include "..\..\inc\Dialogs\DlgNewWeapon.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"

#include <Windows.h>

static UINT weaponId = 0;

BOOL CALLBACK DlgNewWeaponProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SHOWWINDOW:
		{
			if ((BOOL)wParam == TRUE)
			{
				WhCenterChildWindow(WhGetOwner(hDlg), hDlg);
				MessageBeep(MB_ICONINFORMATION);
			}

			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, (INT_PTR)weaponId);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					CoNotImplemented(hDlg);
					return TRUE;
				}

				case IDCANCEL:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				default: break;
			}
		}

		default: break;
	}

	return FALSE;
}