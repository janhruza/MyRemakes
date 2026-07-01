#include "..\..\inc\Dialogs\DlgNewVehicle.h"

#include <Windows.h>

static UINT vehicleId = 0;

BOOL CALLBACK DlgNewVehicleProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			EndDialog(hDlg, (INT_PTR)vehicleId);
			return TRUE;
		}

		default: break;
	}

	return FALSE;
}