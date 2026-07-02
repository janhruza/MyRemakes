/*
*	DlgNewVehicle.c
*	Representing the new vehicle dialog.
*	This dialog is used only to register new vehicles to the database.
*	This dialog is not meant to be used as a register vehicle dialog, but rather as a way to add new vehicles to the database.
*/

#include "..\..\inc\Dialogs\DlgNewVehicle.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"

#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

#include "..\..\res\resource.h"

static UINT vehicleId = 0;

BOOL CALLBACK DlgNewVehicleProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// get control handles
			HWND hCbxBrand = GetDlgItem(hDlg, IDC_VEHICLE_BRAND);
			HWND hCbxClass = GetDlgItem(hDlg, IDC_VEHICLE_CLASS);

			// create a spin control for the vehicle price
			HWND hSpin = CreateWindowEx(0, UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_ARROWKEYS, 0, 0, 0, 0, hDlg, NULL, GetModuleHandle(NULL), NULL);
			SendMessage(hSpin, UDM_SETBUDDY, (WPARAM)GetDlgItem(hDlg, IDC_VEHICLE_PRICE), 0);
			SendMessage(hSpin, UDM_SETRANGE32, 0, 100000000);

			// load vehicle manufacturers
			for (int i = 0; i < VB_LAST; i++)
			{
				int idx = ComboBox_AddString(hCbxBrand, gVehicleBrands[i]);
				if (idx != CB_ERR && idx != CB_ERRSPACE)
				{
					ComboBox_SetItemData(hCbxBrand, idx, i);
				}
			}

			// load vehicle classes
			for (int i = 0; i < VC_LAST; i++)
			{
				int idx = ComboBox_AddString(hCbxClass, gVehicleClasses[i]);
				if (idx != CB_ERR && idx != CB_ERRSPACE)
				{
					ComboBox_SetItemData(hCbxClass, idx, i);
				}
			}

			// set visible height to 10 items
			ComboBox_SetMinVisible(hCbxBrand, 10);
			ComboBox_SetMinVisible(hCbxClass, 10);
			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, (INT_PTR)vehicleId);
			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			MessageBeep(MB_ICONINFORMATION);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					// the 'register' button
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