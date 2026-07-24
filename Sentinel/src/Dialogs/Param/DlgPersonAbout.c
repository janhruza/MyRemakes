#include "..\..\..\inc\Dialogs\Param\DlgAboutPerson.h"
#include "..\..\..\inc\Engine\Person.h"
#include "..\..\..\inc\Globals.h"
#include "..\..\..\res\resource.h"

#include <Windows.h>
#include <strsafe.h>

#define DATE_SIZE 16

static BOOL DateToString(SYSTEMTIME date, LPWSTR buf, size_t bufsize)
{
	return SUCCEEDED(StringCchPrintf(buf, bufsize, TEXT("%02d\\%02d\\%04d"), date.wMonth, date.wDay, date.wYear));
}

static BOOL DisplayPersonInfoText(HWND hStatic, PersonPtr person)
{
	if (hStatic == NULL) return FALSE;
	if (person == NULL) return FALSE;

	WCHAR* label = TEXT("ID:\t\t%d\nName:\t\t%s\nLevel:\t\t%d\nLast seen:\t%s\nRegistered\t%s\nNationality:\t%s");
	WCHAR text[1024] = { 0 };

	WCHAR sSeen[DATE_SIZE];
	WCHAR sReg[DATE_SIZE];

	DateToString(person->LastSeen, sSeen, DATE_SIZE);
	DateToString(person->CreationDate, sReg, DATE_SIZE);

	HRESULT hr = StringCchPrintf(text, 1024, label, person->Id, person->Name, person->Level, sSeen, sReg, gCountries[person->Nationality]);
	if (SUCCEEDED(hr))
	{
		return SetWindowText(hStatic, text);
	}

	return FALSE;
}

BOOL CALLBACK DlgAboutPersonProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			if (lParam == NULL)
			{
				// no person data passed
				MessageBox(hDlg, TEXT("No person data passed."), TEXT("No data"), MB_OK | MB_ICONERROR);
				return FALSE;
			}

			// get and display the person info
			PersonPtr person = (PersonPtr)lParam;
			HWND hStatic = GetDlgItem(hDlg, IDC_DATA);
			DisplayPersonInfoText(hStatic, person);
			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, IDCLOSE);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				case IDCANCEL:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				default: break;
			}
		}

		default: return FALSE;
	}
}