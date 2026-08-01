#include "..\..\inc\Controls\CtlWeapons.h"
#include "..\..\inc\Dialogs\DlgNewWeapon.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"

#include <Windows.h>
#include <windowsx.h>
#include <strsafe.h>

static HMENU hWeaponMenu = NULL;
static HMENU hBlankMenu = NULL;

static HWND hLbx = NULL;

static BOOL InitializeMenus(void)
{
	hWeaponMenu = CreatePopupMenu();
	hBlankMenu = CreatePopupMenu();

	AppendMenu(hWeaponMenu, MF_STRING, MENU_ABOUT_WEAPON, TEXT("About"));
	AppendMenu(hWeaponMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hWeaponMenu, MF_STRING, MENU_REMOVE_WEAPON, TEXT("Remove"));
	AppendMenu(hWeaponMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hWeaponMenu, MF_STRING, MENU_REFRESH_WEAPONS, TEXT("Refresh"));

	AppendMenu(hBlankMenu, MF_STRING, MENU_ADD_WEAPON, TEXT("Add new Weapon"));
	AppendMenu(hBlankMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hBlankMenu, MF_STRING, MENU_REFRESH_WEAPONS, TEXT("Refresh"));

	return TRUE;
}

static BOOL RefreshWeapons(HWND hCtl)
{
	if (!hCtl) return FALSE;
	ListBox_ResetContent(hLbx);

	int count = 0;
	DatabasePtr db = GlobGetDbPtr();

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		Weapon weapon = db->Weapons[i];
		if (weapon.Id != 0)
		{
			const WCHAR* display = NULL;
			if (weapon.Id < W_COUNT && gWeaponNames[weapon.Id] != NULL)
			{
				display = gWeaponNames[weapon.Id];
			}
			else
			{
				static WCHAR buf[64];
				StringCchPrintf(buf, 64, TEXT("Custom weapon #%u"), weapon.Id);
				display = buf;
			}

			int idx = ListBox_AddString(hLbx, display);
			ListBox_SetItemData(hLbx, idx, weapon.Id);
			count++;
		}
	}

	HWND hTxt = GetDlgItem(hCtl, IDC_LBL_WEAPON_COUNT);
	WCHAR text[MAX_PATH] = { 0 };
	StringCchPrintf(text, MAX_PATH, TEXT("Showing a total of %d weapons"), count);
	SetWindowText(hTxt, text);
	return TRUE;
}

static BOOL RemoveWeapon(HWND hCtl)
{
	if (hLbx == NULL) return FALSE;

	int idx = ListBox_GetCurSel(hLbx);
	if (idx == LB_ERR) return FALSE;

	WCHAR text[128] = { 0 };
	ListBox_GetText(hLbx, idx, text);

	WCHAR buf[1024] = { 0 };
	StringCchPrintf(buf, 1024, TEXT("Do you want to remove '%s'? This action is irreversible."), text);

	if (MessageBox(hCtl, buf, TEXT("Remove weapon"), MB_YESNO | MB_ICONWARNING) == IDYES)
	{
		UINT uId = ListBox_GetItemData(hLbx, idx);
		DatabasePtr db = GlobGetDbPtr();
		return DbRemoveWeapon(db, uId);
	}

	return FALSE;
}

BOOL CALLBACK CtlWeaponsProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hLbx = GetDlgItem(hCtl, IDC_WEAPONS);
			InitializeMenus();
			RefreshWeapons(hCtl);
			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			if ((BOOL)wParam == TRUE)
			{
				RefreshWeapons(hCtl);
			}

			return TRUE;
		}

		case WM_CONTEXTMENU:
		{
			if ((HWND)wParam == hLbx)
			{
				int x = -1; int y = -1;
				x = LOWORD(lParam); y = HIWORD(lParam);
				if (x < 0 || y < 0)
				{
					POINT pt = { 0 };
					GetCursorPos(&pt);
					x = pt.x; y = pt.y;
				}

				int idx = ListBox_GetCurSel(hLbx);
				HMENU hMenu = NULL;

				if (idx != LB_ERR)
				{
					WCHAR buf[128] = { 0 };
					ListBox_GetText(hLbx, idx, buf);
					WCHAR title[256] = { 0 };
					StringCchPrintf(title, 256, TEXT("About %s"), buf);
					ModifyMenu(hWeaponMenu, MENU_ABOUT_WEAPON, MF_BYCOMMAND, MENU_ABOUT_WEAPON, title);
					hMenu = hWeaponMenu;
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
				case MENU_ADD_WEAPON:
				case IDOK:
				{
					INT_PTR result = CoShowDialog(hCtl, IDD_DLGNEWWEAPON, DlgNewWeaponProc);
					if (result > 0)
					{
						RefreshWeapons(hCtl);
					}
					return TRUE;
				}

				case MENU_REFRESH_WEAPONS:
				case IDRETRY:
				{
					RefreshWeapons(hCtl);
					return TRUE;
				}

				case MENU_ABOUT_WEAPON:
				{
					CoNotImplemented(hCtl);
					return TRUE;
				}

				case MENU_REMOVE_WEAPON:
				{
					if (RemoveWeapon(hCtl) == TRUE)
					{
						RefreshWeapons(hCtl);
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

