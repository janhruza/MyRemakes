#include "..\..\inc\Controls\CtlVehicles.h"
#include "..\..\inc\Dialogs\DlgNewVehicle.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"

#include <Windows.h>
#include <windowsx.h>
#include <strsafe.h>

static HMENU hVehicleMenu = NULL;
static HMENU hBlankMenu = NULL;

static HWND hLbx = NULL;

static BOOL InitializeMenus(void)
{
	hVehicleMenu = CreatePopupMenu();
	hBlankMenu = CreatePopupMenu();

	// selected vehicle menu
	AppendMenu(hVehicleMenu, MF_STRING, MENU_ABOUT_VEHICLE, TEXT("About"));
	AppendMenu(hVehicleMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hVehicleMenu, MF_STRING, MENU_REMOVE_VEHICLE, TEXT("Remove"));
	AppendMenu(hVehicleMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hVehicleMenu, MF_STRING, MENU_REFRESH, TEXT("Refresh"));

	// the 'blank' menu
	AppendMenu(hBlankMenu, MF_STRING, MENU_ADD_VEHICLE, TEXT("Add new Vehicle"));
	AppendMenu(hBlankMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hBlankMenu, MF_STRING, MENU_REFRESH, TEXT("Refresh"));

	return TRUE;
}

static BOOL RefreshVehicles(HWND hCtl)
{
	if (!hCtl) return FALSE;
	ListBox_ResetContent(hLbx);

	int count = 0;
	DatabasePtr db = GlobGetDbPtr();

	for (int i = 0; i < MAX_VEHICLES; i++)
	{
		Vehicle vehicle = db->Vehicles[i];
		if (vehicle.Id != 0)
		{
			// gets the brand + model name
			WCHAR name[VC_MAXLEN] = { 0 };
			StringCchPrintf(name, VC_MAXLEN, TEXT("%s %s"), gVehicleBrands[vehicle.Manufacturer], vehicle.Model);
			int idx = ListBox_AddString(hLbx, name);
			ListBox_SetItemData(hLbx, idx, vehicle.Id);
			count++;
		}
	}

	// display the info text
	HWND hTxt = GetDlgItem(hCtl, IDC_LBL_VEHICLE_COUNT);
	WCHAR text[MAX_PATH] = { 0 };

	StringCchPrintf(text, MAX_PATH, TEXT("Showing a total of %d vehicles"), count);
	SetWindowText(hTxt, text);
	return TRUE;
}

static BOOL RemoveVehicle(HWND hCtl)
{
	if (hLbx == NULL) return FALSE;

	// get the item selected
	int idx = ListBox_GetCurSel(hLbx);
	if (idx == LB_ERR) return FALSE;

	WCHAR text[VC_MODEL_LEN] = { 0 };
	ListBox_GetText(hLbx, idx, text);

	WCHAR buf[1024] = { 0 };
	StringCchPrintf(buf, 1024, TEXT("Do you want to remove '%s'? This action is irreversible."), text);

	if (MessageBox(hCtl, buf, TEXT("Remove vehicle"), MB_YESNO | MB_ICONWARNING) == IDYES)
	{
		UINT uId = ListBox_GetItemData(hLbx, idx);
		DatabasePtr db = GlobGetDbPtr();
		return DbRemoveVehicle(db, uId);
	}

	else
	{
		return FALSE;
	}
}

BOOL CALLBACK CtlVehiclesProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// initialize controls
			hLbx = GetDlgItem(hCtl, IDC_VEHICLES);
			
			// initialize app control-specific menus
			InitializeMenus();

			// refresh the UI
			RefreshVehicles(hCtl);

			// create context menus
			return TRUE;
		}

		case WM_CONTEXTMENU:
		{
			if ((HWND)wParam == hLbx)
			{
				int x = -1;
				int y = -1;

				x = LOWORD(lParam);
				y = HIWORD(lParam);

				if (x < 0 || y < 0)
				{
					POINT pt = { 0 };
					GetCursorPos(&pt);
					x = pt.x;
					y = pt.y;
				}

				int idx = ListBox_GetCurSel(hLbx);
				HWND hMenu = NULL;

				if (idx != LB_ERR)
				{
					// update the menu item text
					WCHAR text[VC_MAXLEN] = { 0 };
					ListBox_GetText(hLbx, idx, text);
					WCHAR buf[VC_MAXLEN + 10] = { 0 };
					StringCchPrintf(buf, 512, TEXT("About %s"), text);
					ModifyMenu(hVehicleMenu, MENU_ABOUT_VEHICLE, MF_BYCOMMAND, MENU_ABOUT_VEHICLE, buf);

					hMenu = hVehicleMenu;
				}

				else
				{
					hMenu = hBlankMenu;
				}

				return TrackPopupMenu(hMenu, TPM_LEFTALIGN, x, y, 0, hCtl, NULL);
			}

			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case MENU_ADD_VEHICLE:
				case IDOK:
				{
					INT_PTR result = CoShowDialog(hCtl, IDD_DLGNEWVEHICLE, DlgNewVehicleProc);
					if (result > 0)
					{
						RefreshVehicles(hCtl);
					}

					return TRUE;
				}

				case MENU_REFRESH:
				case IDRETRY:
				{
					RefreshVehicles(hCtl);
					return TRUE;
				}

				case MENU_ABOUT_VEHICLE:
				{
					CoNotImplemented(hCtl);
					return TRUE;
				}

				case MENU_REMOVE_VEHICLE:
				{
					if (RemoveVehicle(hCtl) == TRUE)
					{
						RefreshVehicles(hCtl);
					}
					
					return TRUE;
				}

				default: break;
			}

			return FALSE;
		}

		default: break;
	}

	return FALSE;
}