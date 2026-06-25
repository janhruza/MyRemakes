#include "..\..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"

static HBRUSH hBg = NULL;
static HWND hLbxHistory = NULL;

BOOL GeneratePlate(HWND hLbx, BOOL bCustomFormat)
{
	if (hLbx == NULL) return FALSE;

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
			hBg = GetSysColorBrush(COLOR_WINDOW);
			hLbxHistory = GetDlgItem(hDlg, IDC_HISTORY);

			CheckDlgButton(hDlg, IDC_RBKEEPFORMAT, TRUE);
			return TRUE;
		}

		case WM_CTLCOLORDLG:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSTATIC:
		{
			return (HBRUSH)hBg;
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