#include "..\..\inc\Controls\CtlLanding.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Globals.h"
#include "..\..\inc\Engine\Database.h"

#include <strsafe.h>

#define MY_TIMER_ID		0x1000
#define	TIMER_FREQ		500

static BOOL UpdateTime(HWND hCtl)
{
	HWND hTxt = GetDlgItem(hCtl, IDC_LBL_TIME);

	SYSTEMTIME time;
	GetLocalTime(&time);

	WCHAR text[32];
	StringCchPrintf(text, 32, TEXT("%02d:%02d:%02d\n"), time.wHour, time.wMinute, time.wSecond);
	SetWindowText(hTxt, text);
	// update counts
	DatabasePtr db = GlobGetDbPtr();
	int persons = 0, vehicles = 0, weapons = 0, crimes = 0;
	if (db)
	{
		for (int i = 0; i < MAX_PERSONS; i++) if (db->Persons[i].Id != 0) persons++;
		for (int i = 0; i < MAX_VEHICLES; i++) if (db->Vehicles[i].Id != 0) vehicles++;
		for (int i = 0; i < MAX_WEAPONS; i++) if (db->Weapons[i].Id != 0) weapons++;
		for (int i = 0; i < MAX_CRIMES; i++) if (db->Crimes[i].Id != 0) crimes++;
	}

	WCHAR stats[256] = { 0 };
	StringCchPrintf(stats, 256, TEXT("People: %d  Vehicles: %d  Weapons: %d  Crimes: %d"), persons, vehicles, weapons, crimes);
	HWND hStats = GetDlgItem(hCtl, IDC_LBL_STATS);
	if (hStats) SetWindowText(hStats, stats);
	return TRUE;
}

static void Timerproc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	// 500ms timer
	UpdateTime(hWnd);
}

BOOL CALLBACK CtlLandingProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// setup timer
			SetTimer(hCtl, MY_TIMER_ID, TIMER_FREQ, Timerproc);

			// display current time
			UpdateTime(hCtl);
			return TRUE;
		}

		default: break;
	}

	return FALSE;
}