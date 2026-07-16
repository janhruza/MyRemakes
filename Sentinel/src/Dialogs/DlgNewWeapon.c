/*
* DlgNewWeapon.c
* Representing the new weapon dialog.
* This dialog is meant only to register new weapons to the database.
* This dialog is not meant to add new weapons to a player.
*/

#include "..\..\inc\Dialogs\DlgNewWeapon.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"
#include "..\..\inc\Engine\Database.h"
#include "..\..\res\resource.h"
#include <CommCtrl.h>
#include <windowsx.h>
#include <Windows.h>

static UINT weaponId = 0;
static HWND hName = NULL;
static HWND hType = NULL;
static HWND hCap = NULL;
static HWND hMax = NULL;

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

		case WM_INITDIALOG:
		{
			hName = GetDlgItem(hDlg, IDC_TXT_NAME);
			hType = GetDlgItem(hDlg, IDC_CBX_WEAPON_TYPE);
			hCap = GetDlgItem(hDlg, IDC_TXT_WEAPON_CAPACITY);
			hMax = GetDlgItem(hDlg, IDC_TXT_WEAPON_MAXAMMO);

			// populate weapon types
			const WCHAR* types[] = { L"Unknown", L"Melee", L"Handgun", L"SMG", L"Shotgun", L"Rifle", L"MG", L"Sniper", L"Heavy", L"Thrown" };
			for (int i = WPT_FIRST; i < WPT_LAST; i++)
			{
				int idx = ComboBox_AddString(hType, types[i]);
				ComboBox_SetItemData(hType, idx, (LPARAM)i);
			}
			ComboBox_SetCurSel(hType, WPT_FIRST + 1); // default to first real type

			return TRUE;
		}
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
					// register new weapon
					{
						WCHAR name[128] = { 0 };
						if (GetWindowText(hName, name, _countof(name)) == 0)
						{
							CoDisplayError(hDlg, IDS_MSG_ERR_NAME);
							return TRUE;
						}

						int idx = ComboBox_GetCurSel(hType);
						if (idx == CB_ERR)
						{
							CoNotImplemented(hDlg);
							return TRUE;
						}

						Weapon w = { 0 };
						PConfig cfg = GlobGetConfigPtr();
						if (cfg == NULL) return TRUE;
						w.Id = cfg->nWeaponId++;
						w.Type = (WeaponType)ComboBox_GetItemData(hType, idx);

						WCHAR buf[32] = { 0 };
						GetWindowText(hCap, buf, _countof(buf));
						w.Capacity = _wtoi(buf);
						GetWindowText(hMax, buf, _countof(buf));
						w.MaxAmmo = _wtoi(buf);

						DatabasePtr db = GlobGetDbPtr();
						if (DbAddWeapon(db, w) == TRUE)
						{
							weaponId = w.Id;
						}
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