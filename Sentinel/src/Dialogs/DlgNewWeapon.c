#include "..\..\inc\Dialogs\DlgNewWeapon.h"

#include <Windows.h>

static UINT weaponId = 0;

BOOL CALLBACK DlgNewWeaponProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		EndDialog(hDlg, (INT_PTR)weaponId);
		return TRUE;
	}

	default: break;
	}

	return FALSE;
}