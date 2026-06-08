#include "..\..\inc\Controls\CtlLandingPage.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\WindowHelper.h"

static HMENU hMenu;

static void InitializeMenu(void)
{
	hMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, IDHELP, TEXT("About\tF1"));
	AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hMenu, MF_STRING, IDCANCEL, TEXT("Logout\tESC"));
	return;
}

static void UILogout(HWND hDlg)
{
	if (hDlg == NULL) return;

	CoHideAllControls();
	CoShowControl(hCtlLogin);
	WhFitContent(GetParent(hDlg), hCtlLogin);
	return;
}

INT_PTR CALLBACK CtlLandingPageProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			InitializeMenu();
			return TRUE;
		}

		case WM_GETDLGCODE:
		{
			return DLGC_WANTALLKEYS;
		}

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDCANCEL:
					UILogout(hDlg);
					return TRUE;

				case IDHELP:
				{
					ShellAbout(hDlg, APP_NAME, TEXT("\x00A9 2026 Jan Hruza"), NULL);
					return TRUE;
				}

				default: return FALSE;
			}
		}

		case WM_CONTEXTMENU:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (x == -1 || y == -1)
			{
				RECT rc;
				GetClientRect(hDlg, &rc);
				POINT pt = { rc.left + (rc.right / 2), rc.top + (rc.bottom / 2) };
				ClientToScreen(hDlg, &pt);
				x = pt.x;
				y = pt.y;
			}

			TrackPopupMenu(hMenu, TPM_LEFTALIGN, x, y, NULL, hDlg, NULL);
			return TRUE;
		}

		default: return FALSE;
	}
}