#include "..\inc/DlgMainWindow.h"
#include "..\inc\Core.h"

HMENU hCtxMenu = NULL;
HWND hCbx = NULL;
HWND hTxtWindow = NULL;
HWND hSelectedWindow = NULL;

typedef enum tagMenuIds
{
	ID_REFRESH = 0x1001,
	ID_ABOUT
} MenuIds;

static BOOL InitFields(HWND hDlg)
{
	hCbx = GetDlgItem(hDlg, IDC_CBX_WINDOW);
	hTxtWindow = GetDlgItem(hDlg, IDC_TXT_WINDOW);
	return TRUE;
}

static BOOL CreateContextMenu(void)
{
	hCtxMenu = CreatePopupMenu();
	AppendMenu(hCtxMenu, MF_STRING, ID_REFRESH, TEXT("Refresh\tF5"));
	AppendMenu(hCtxMenu, MF_STRING, ID_ABOUT, TEXT("About\tF1"));
	AppendMenu(hCtxMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hCtxMenu, MF_STRING, IDCLOSE, TEXT("Close\tAlt+F4"));
	return TRUE;
}

static BOOL GetAllWindows(void)
{
	if (hCbx == NULL) return FALSE;

	hSelectedWindow = NULL;
	SetWindowText(hTxtWindow, TEXT("No window selected."));

	SendMessage(hCbx, CB_RESETCONTENT, 0, 0);
	return CoEnumWindows(hCbx);
}

static BOOL ToggleActiveWindow()
{
	if (hSelectedWindow == NULL) return FALSE;

	HWND hParent = GetParent(hTxtWindow);

	BOOL isAot = CoIsWindowAOT(hSelectedWindow);
	if (CoToggleAOT(hSelectedWindow, !isAot) == TRUE)
	{
		MessageBeep(MB_ICONINFORMATION);
		return TRUE;
	}

	else
	{
		MessageBeep(MB_ICONERROR);
		return FALSE;
	}
}

BOOL CALLBACK DlgMainWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			HMENU hMenu = GetSystemMenu(hDlg, FALSE);
			AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(hMenu, MF_STRING, ID_ABOUT, TEXT("About\tF1"));

			InitFields(hDlg);
			CreateContextMenu();
			GetAllWindows();
			return TRUE;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, IDCLOSE);
			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			switch(wParam)
			{
				case SC_CLOSE:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;

				case ID_ABOUT:
				{
					return CoDlgAbout(hDlg);
				}
			}
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCLOSE:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case ID_REFRESH:
				case IDC_BTN_REFRESH:
				{
					GetAllWindows();
					return TRUE;
				}

				case ID_ABOUT:
				{
					return CoDlgAbout(hDlg);
				}

				case IDC_BTN_OK:
				{
					// toggle selected window's priority
					if (ToggleActiveWindow())
					{
						GetAllWindows();
					}
				}

				case IDC_CBX_WINDOW: {
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						WCHAR text[MAX_PATH];
						int idx = (int)SendMessage(hCbx, CB_GETCURSEL, 0, 0);

						if (idx != CB_ERR)
						{
							if (SendMessage(hCbx, CB_GETLBTEXT, (WPARAM)idx, (LPARAM)text) != CB_ERR)
							{
								hSelectedWindow = SendMessage(hCbx, CB_GETITEMDATA, (WPARAM)idx, 0);
								WCHAR* isAot;

								if (CoIsWindowAOT(hSelectedWindow))
								{
									isAot = TEXT("IS");
								}

								else
								{
									isAot = TEXT("IS NOT");
								}

								WCHAR newText[2 * MAX_PATH];
								wsprintf(newText, TEXT("Window \'%s\' is selected and %s AoT."), text, isAot);
								SetWindowText(hTxtWindow, newText);
							}
						}
					}
					return TRUE;
				}

				default:
					return FALSE;
			}
		}

		case WM_CONTEXTMENU:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (x < 0 || y < 0)
			{
				POINT pt;
				GetCursorPos(&pt);
				x = pt.x;
				y = pt.y;
			}

			return TrackPopupMenu(hCtxMenu, TPM_LEFTALIGN, x, y, 0, hDlg, NULL);
		}

		default:
			return FALSE;
	}
}