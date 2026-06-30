#include "..\..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"

static HWND hLbxHistory = NULL;

static WCHAR chars[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static WCHAR numbers[] = L"0123456789";
static WCHAR all_chars[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

WCHAR Rnd_NextChar(void)
{
	return chars[rand() % wcslen(chars)];
}

WCHAR Rnd_NextDigit(void)
{
	return numbers[rand() % wcslen(numbers)];
}

BOOL GeneratePlate(HWND hLbx, BOOL bCustomFormat)
{
	if (hLbx == NULL) return FALSE;

	WCHAR plate[PLATE_LEN + 1] = { 0 };

	switch (bCustomFormat)
	{
		default:
		{
			MessageBox(GetParent(hLbx), TEXT("Invalid generator option."), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			return FALSE;
		}

		case FALSE:
		{
			// standard plate: 00-AAA-000
			for (int i = 0; i < 2; i++)
			{
				plate[i] = Rnd_NextDigit();
			}

			for (int i = 2; i < 5; i++)
			{
				plate[i] = Rnd_NextChar();
			}

			for (int i = 5; i < PLATE_LEN; i++)
			{
				plate[i] = Rnd_NextDigit();
			}

			SendMessage(hLbx, LB_ADDSTRING, 0, plate);

			return TRUE;
		}

		case TRUE:
		{
			// custom format (random)
			for (int i = 0; i < PLATE_LEN; i++)
			{
				plate[i] = all_chars[rand() % wcslen(all_chars)];
			}

			SendMessage(hLbx, LB_ADDSTRING, 0, plate);
			return TRUE;
		}
	}

	return CoNotImplemented(GetParent(hLbx));
}

BOOL GeneratePlateWrapper(HWND hDlg)
{
	if (hDlg == NULL) return FALSE;

	BOOL bCustom = FALSE;

	if (IsDlgButtonChecked(hDlg, IDC_RBKEEPFORMAT) == TRUE)
	{
		bCustom = FALSE;
	}

	else if (IsDlgButtonChecked(hDlg, IDC_RBCUSTOM) == TRUE)
	{
		bCustom = TRUE;
	}

	else
	{
		// no option selected
		return FALSE;
	}

	return GeneratePlate(hLbxHistory, bCustom);
}

BOOL CALLBACK DlgPlateGeneratorProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hLbxHistory = GetDlgItem(hDlg, IDC_HISTORY);

			CheckDlgButton(hDlg, IDC_RBKEEPFORMAT, TRUE);
			return TRUE;
		}

		case WM_SHOWWINDOW:
		{
			MessageBeep(MB_ICONINFORMATION);
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
				case IDCLOSE:
				case IDCANCEL:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case IDOK:
				{
					// plate generation
					return GeneratePlateWrapper(hDlg);
				}

				default: return FALSE;
			}
		}

		default:
			break;
	}

	return FALSE;
}