#include "..\..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"

static HBRUSH hBg;

BOOL CALLBACK DlgPlateGeneratorProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hBg = GetSysColorBrush(COLOR_WINDOW);
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
					CoNotImplemented(hDlg);
					return TRUE;
				}

				default: return FALSE;
			}
		}

		default:
			break;
	}

	return FALSE;
}