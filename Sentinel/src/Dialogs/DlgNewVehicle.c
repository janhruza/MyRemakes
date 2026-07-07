/*
*	DlgNewVehicle.c
*	Representing the new vehicle dialog.
*	This dialog is used only to register new vehicles to the database.
*	This dialog is not meant to be used as a register vehicle dialog, but rather as a way to add new vehicles to the database.
*/

#include "..\..\inc\Dialogs\DlgNewVehicle.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Config.h"

#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

#include "..\..\res\resource.h"

static UINT vehicleId = 0;

static BOOL CreateVehicle(HWND hDlg)
{
	// get control handles
	HWND hCbxBrand = GetDlgItem(hDlg, IDC_VEHICLE_BRAND);
	HWND hCbxClass = GetDlgItem(hDlg, IDC_VEHICLE_CLASS);
	HWND hEdtPrice = GetDlgItem(hDlg, IDC_VEHICLE_PRICE);
	HWND hTxtModel = GetDlgItem(hDlg, IDC_VEHICLE_MODEL);

	// get selected brand and class
	int brandIndex = ComboBox_GetCurSel(hCbxBrand);
	int classIndex = ComboBox_GetCurSel(hCbxClass);
	if (brandIndex == CB_ERR || classIndex == CB_ERR)
	{
		MessageBox(hDlg, L"Please select a vehicle brand and class.", L"Error", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	// get the model
	WCHAR modelBuffer[VC_MODEL_LEN];
	GetWindowText(hTxtModel, modelBuffer, sizeof(modelBuffer) / sizeof(WCHAR));
	if (wcslen(modelBuffer) == 0)
	{
		MessageBox(hDlg, L"Please enter a vehicle model.", L"Error", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	// get the price
	WCHAR priceBuffer[32];
	GetWindowText(hEdtPrice, priceBuffer, sizeof(priceBuffer) / sizeof(WCHAR));
	int price = _wtoi(priceBuffer);
	if (price < 0) // 0 is a valid price, but negative values are not
	{
		MessageBox(hDlg, L"Please enter a valid vehicle price.", L"Error", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	// create the vehicle in the database (not implemented)
	PConfig config = GlobGetConfigPtr();
	Vehicle vehicle = { 0 };
	vehicle.Id = config->nVehicleId + 1; // increment the vehicle ID
	vehicle.Manufacturer = brandIndex;
	vehicle.Class = classIndex;
	vehicle.Price = price;

	// copy the model to the vehicle struct
	wcscpy_s(vehicle.Model, sizeof(vehicle.Model) / sizeof(WCHAR), modelBuffer);
	vehicleId = vehicle.Id; // set the static vehicleId to the new vehicle's ID

	DatabasePtr db = GlobGetDbPtr();
	db->Vehicles[config->nVehicleIdx++] = vehicle; // add the vehicle to the database
	DbSaveGlobal(db);

	return TRUE;
}

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
			if ((BOOL)wParam == TRUE)
			{
				WhCenterChildWindow(WhGetOwner(hDlg), hDlg);
				MessageBeep(MB_ICONINFORMATION);
			}

			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					// the 'register' button
					if (CreateVehicle(hDlg))
					{
						SendMessage(hDlg, WM_CLOSE, 0, 0);
					}

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