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

	Crime crime = { 0 };
	for (int i = 0; i < MAX_CRIMES; i++)
	{
		if (db->Crimes[i].Id != 0)
		{
			crimes++;
			crime = db->Crimes[i];
		}
	}

	int pID = cfg->nPersonId;
	int vID = cfg->nVehicleId;
	int wID = cfg->nWeaponId;
	int cID = cfg->nCrimeId;

	WCHAR text[1024] = { 0 };
	StringCchPrintf(text, 1024, TEXT("Registered objects:\n\nPersons:\t%d\nVehicles:\t%d\nWeapons:\t%d\nCrimes:\t\t%d\n\nNext ID's:\n\nPerson ID:\t%d\nVehicle ID:\t%d\nWeapon ID:\t%d\nCrime ID:\t%d"), persons, vehicles, weapons, crimes, pID, vID, wID, cID);

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