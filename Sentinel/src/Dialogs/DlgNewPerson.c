#include "..\..\inc\Dialogs\DlgNewPerson.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"
#include "..\..\inc\Engine\Database.h"
#include "..\..\res\resource.h"

#include <CommCtrl.h>
#include <windowsx.h>
#include <strsafe.h>

PersonPtr pPerson = NULL;

static HWND hDp = NULL;
static HWND hName = NULL;
static HWND hCountry = NULL;

BOOL RegisterPerson(HWND hParent)
{
	WCHAR name[TEXT_LEN] = { 0 };
	SYSTEMTIME st = { 0 };
	Country country = 0;

	// get the basics: name, registration date and country of origin
	if (GetWindowText(hName, name, TEXT_LEN) == 0)
	{
		// no name
		CoDisplayError(hParent, IDS_MSG_ERR_NAME);
		return FALSE;
	}

	if (DateTime_GetSystemtime(hDp, &st) != GDT_VALID)
	{
		// error getting date
		CoDisplayError(hParent, IDS_MSG_ERR_DTP);
		return FALSE;
	}

	int idx = ComboBox_GetCurSel(hCountry);
	if (idx == CB_ERR)
	{
		// no country selected
		CoDisplayError(hParent, IDS_MSG_ERR_COUNTRY);
		return FALSE;
	}

	country = ComboBox_GetItemData(hCountry, idx);

	// create a new person
	Person p;
	PConfig config = GlobGetConfigPtr();
	if (config == NULL)
	{
		return FALSE;
	}

	p.Id = config->nPersonId++;
	p.CreationDate = st;
	p.LastSeen = st;
	p.Level = 0;
	p.Nationality = country;

	// copy the name
	wcscpy_s(p.Name, _countof(p.Name), name);

	// add person to the database
	DatabasePtr db = GlobGetDbPtr();
	if (DbAddPerson(db, p) == FALSE)
	{
		// unable to save person
		return FALSE;
	}

	// assign the pointer
	pPerson = &p;
	return TRUE;
}

BOOL CALLBACK DlgNewPersonProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hName = GetDlgItem(hDlg, IDC_TXT_USERNAME);
			hDp = GetDlgItem(hDlg, IDC_DTP_REGDATE);
			hCountry = GetDlgItem(hDlg, IDC_CBX_COUNTRY);

			// load countries
			for (int i = COUNTRY_OTHER; i < COUNTRY_LAST; i++)
			{
				int idx = ComboBox_AddString(hCountry, gCountries[i]);
				ComboBox_SetItemData(hCountry, idx, (Country)i);
			}

			ComboBox_SetMinVisible(hCountry, 8);

			Person p;
			pPerson = &p;
			memset(pPerson, 0, sizeof(Person));

			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			MessageBeep(MB_ICONINFORMATION);
			return TRUE;
		}

		case WM_CLOSE:
		{
			// return the id of the created person
			EndDialog(hDlg, (INT_PTR)pPerson->Id);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCANCEL:
				{
					// operation cancelled
					pPerson->Id = -1;
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case IDOK:
				{
					if (RegisterPerson(hDlg) == FALSE)
					{
						// error
						return FALSE;
					}

					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				default: break;
			}

			return FALSE;
		}

		default: return FALSE;
	}
}