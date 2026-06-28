#include "..\..\inc\Controls\CtlDbPersons.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"

#include <Windows.h>
#include <windowsx.h>
#include <strsafe.h>

static HWND hLbx = NULL;
static HWND hLabel = NULL;

static HMENU hPersonMenu = NULL;
static HMENU hBlankMenu = NULL;

static BOOL CreatePersonMenu(void)
{
	if (hPersonMenu != NULL)
	{
		DestroyMenu(hPersonMenu);
	}

	hPersonMenu = CreatePopupMenu();
	AppendMenu(hPersonMenu, MF_STRING, PERSON_DETAILS, TEXT("About"));
	AppendMenu(hPersonMenu, MF_STRING, PERSON_ADD_RECORD, TEXT("Add Criminal Record"));
	AppendMenu(hPersonMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hPersonMenu, MF_STRING, PERSON_REMOVE, TEXT("Delete Person"));

	return TRUE;
}

static BOOL CreateBlankMenu(void)
{
	if (hBlankMenu != NULL)
	{
		DestroyMenu(hBlankMenu);
	}

	hBlankMenu = CreatePopupMenu();
	AppendMenu(hBlankMenu, MF_STRING, PERSON_NEW_PERSON, TEXT("Add new Person"));

	return TRUE;
}

static BOOL RefreshDbView(void)
{
	if (hLbx == NULL || hLabel == NULL) return FALSE;

	DatabasePtr db = GlobGetDbPtr();
	int counter = 0;

	ListBox_ResetContent(hLbx);
	for (int i = 0; i < MAX_PERSONS; i++)
	{
		if (db->Persons[i].Id != 0)
		{
			// valid person, add to the view
			int idx = ListBox_AddString(hLbx, db->Persons[i].Name);
			if (idx != LB_ERR)
			{
				ListBox_SetItemData(hLbx, idx, db->Persons[i].Id);
				counter++;
			}
		}
	}

	WCHAR text[MAX_PATH] = { 0 };
	StringCbPrintf(text, MAX_PATH, TEXT("Showing a total of %d records"), counter);
	SetWindowText(hLabel, text);
}

BOOL CtlDbPersonsProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hLbx = GetDlgItem(hCtl, IDC_LBX_RESULTS);
			hLabel = GetDlgItem(hCtl, IDC_TXT_LABEL);
			CreatePersonMenu();
			CreateBlankMenu();
			RefreshDbView();
			return TRUE;
		}

		case WM_GETDLGCODE:
		{
			return DLGC_WANTALLKEYS;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDRETRY:
				{
					// the 'Refresh' button
					return RefreshDbView();
				}

				case IDC_BTN_ADD:
				case PERSON_NEW_PERSON:
				{
					if (CoDlgNewPerson(hCtl) != 0)
					{
						RefreshDbView();
					}

					return TRUE;
				}

				case PERSON_DETAILS:
				{
					CoNotImplemented(hCtl);
					return TRUE;
				}

				default: return FALSE;
			}

			return FALSE;
		}

		case WM_CONTEXTMENU:
		{
			if (wParam == hLbx)
			{
				// show the menu
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				if (x <= 0 || y <= 0)
				{
					POINT p;
					GetCursorPos(&p);
					x = p.x;
					y = p.y;
				}

				// check if an item is selected
				int idx = ListBox_GetCurSel(hLbx);
				if (idx == LB_ERR)
				{
					// no item selected, show general menu
					TrackPopupMenu(hBlankMenu, TPM_LEFTALIGN, x, y, 0, hCtl, NULL);
				}

				else
				{
					// any item selected, show item related menu
					TrackPopupMenu(hPersonMenu, TPM_LEFTALIGN, x, y, 0, hCtl, NULL);
				}

				return TRUE;
			}

			return FALSE;
		}

		default:
			break;
	}

	return FALSE;
}