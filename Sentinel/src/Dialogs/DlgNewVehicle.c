/*
*	DlgNewVehicle.c
*	Representing the new vehicle dialog.
*	This dialog is used only to register new vehicles to the database.
*	This dialog is not meant to be used as a register vehicle dialog, but rather as a way to add new vehicles to the database.
*/

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