#include "..\..\inc\Dialogs\DlgInsights.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Globals.h"

#include "..\..\res\resource.h"

#include <Windows.h>
#include <strsafe.h>

static inline BOOL ShowInsights(HWND hDlg)
{
	HWND hTxt = GetDlgItem(hDlg, IDC_LBL_INSIGHTS);

	int persons = 0;
	int vehicles = 0;
	int weapons = 0;
	int crimes = 0;

	DatabasePtr db = GlobGetDbPtr();
	PConfig cfg = GlobGetConfigPtr();

	for (int i = 0; i < MAX_PERSONS; i++)
	{
		if (db->Persons[i].Id != 0)
		{
			persons++;
		}
	}

	for (int i = 0; i < MAX_VEHICLES; i++)
	{
		if (db->Vehicles[i].Id != 0)
		{
			vehicles++;
		}
	}

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (db->Weapons[i].Id != 0)
		{
			weapons++;
		}
	}

	for (int i = 0; i < MAX_CRIMES; i++)
	{
		if (db->Crimes[i].Id != 0)
		{
			crimes++;
		}
	}

	int pID = cfg->nPersonId;
	int vID = cfg->nVehicleId;
	int wID = cfg->nWeaponId;
	int cID = cfg->nCrimeId;

	WCHAR text[1024] = { 0 };
	StringCchPrintf(text, 1024, TEXT("Registered objects and next IDs:\n\nPersons:\t\t%d\tPerson ID:\t%d\nVehicles:\t\t%d\tVehicle ID:\t%d\nWeapons:\t%d\tWeapon ID:\t%d\nCrimes:\t\t%d\tCrime ID:\t%d"), persons, pID, vehicles, vID, weapons, wID, crimes, cID);

	SetWindowText(hTxt, text);

	return TRUE;
}

BOOL CALLBACK DlgInsightsProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			HWND hParent = WhGetOwner(hDlg);
			WhCenterChildWindow(hParent, hDlg);

			ShowInsights(hDlg);

			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			if ((BOOL)wParam == TRUE)
			{
				MessageBeep(MB_ICONINFORMATION);
			}

			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
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

				default: break;
			}
		}

		default: break;
	}

	return FALSE;
}