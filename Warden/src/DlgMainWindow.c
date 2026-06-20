#include <Windows.h>
#include <strsafe.h>

#include "..\inc\DlgMainWindow.h"
#include "..\inc\Core.h"
#include "..\inc\FocusSession.h"
#include "..\inc\ThreadParams.h"
#include "..\inc\TrayIcon.h"


// window handles
static HWND hBtnAdd = NULL;
static HWND hTxtWord = NULL;
static HWND hLbxList = NULL;
static HWND hBtnStart = NULL;

// context menus
enum
{
	MENU_REMOVE = 0x1001
};

HMENU hLbxMenu = NULL;

BOOL UIUpdateState(HWND hDlg)
{
	int count = SendMessage(hLbxList, LB_GETCOUNT, 0, 0);
	BOOL visible = count > 0;
	return EnableWindow(hBtnStart, visible);
}

BOOL InitializeControls(HWND hDlg)
{
	// init controls
	hTxtWord = GetDlgItem(hDlg, IDC_TXT_WORD);
	hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD);
	hLbxList = GetDlgItem(hDlg, IDC_LBX_BLACKLIST);
	hBtnStart = GetDlgItem(hDlg, IDC_BTN_OK);

	// customize app menu
	HMENU hMenu = GetSystemMenu(hDlg, FALSE);
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, IDHELP, TEXT("About\tF1"));

	// create the listbox menu
	hLbxMenu = CreatePopupMenu();
	AppendMenu(hLbxMenu, MF_STRING, MENU_REMOVE, TEXT("Remove\tDEL"));
	return TRUE;
}

BOOL BeginSession(HWND hDlg)
{
	int count = SendMessage(hLbxList, LB_GETCOUNT, 0, 0);
	if (count <= 0) return TRUE;

	PFocusSession pSesh = FSCreate();
	pSesh->nCount = count;
	for (int i = 0; i < count; i++) {
		SendMessage(hLbxList, LB_GETTEXT, i, (LPARAM)pSesh->blacklist[i]);
	}

	PThreadParams pParams = malloc(sizeof(ThreadParams));
	pParams->hDlg = hDlg;
	pParams->pSession = pSesh;
	ShowWindow(hDlg, SW_HIDE);
	HANDLE hThread = CreateThread(NULL, 0, CoMainLoop, pParams, 0, NULL);
	if (hThread) CloseHandle(hThread);

	// create the tray icon
	Tray_AddIcon(hDlg);

	return TRUE;
}

BOOL CALLBACK DlgMainWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_GETDLGCODE:
			return DLGC_WANTALLKEYS;

		case WM_INITDIALOG:
		{
			return InitializeControls(hDlg);
		}

		case WM_CLOSE:
		{
			Tray_RemoveIcon(hDlg);
			EndDialog(hDlg, wParam);
			return TRUE;
		}

		case WM_TRAYICON:
		{
			if (lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
			{
				Tray_RemoveIcon(hDlg);
				ShowWindow(hDlg, SW_SHOW);
			}

			return (INT_PTR)TRUE;
		}

		case WM_SYSCOMMAND:
		{
			switch (LOWORD(wParam))
			{
			case SC_CLOSE:
			{
				SendMessage(hDlg, WM_CLOSE, IDCLOSE, 0);
				return TRUE;
			}

			case IDHELP:
			{
				//CoDlgAbout(hDlg);
				CoDlgHelp(hDlg);
				return TRUE;
			}

			default: return FALSE;
			}
		}

		/*case WM_HOTKEY:
		{
			if (hDlg == GetForegroundWindow())
			{
				switch (wParam)
				{
					case IDHELP:
						CoDlgAbout(hDlg);
						return TRUE;

					default: return FALSE;
				}
			}

			return FALSE;
		}*/

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCANCEL:
				case IDCLOSE:
				{
					SendMessage(hDlg, WM_CLOSE, IDCLOSE, 0);
					return TRUE;
				}

				case IDC_TXT_WORD:
				{
					switch (HIWORD(wParam))
					{
					case EN_CHANGE:
					{
						WCHAR text[MAX_PATH];
						GetWindowText(hTxtWord, text, MAX_PATH);

						BOOL value = lstrlen(text) > 0;
						EnableWindow(hBtnAdd, value);
						return TRUE;
					}

					default: return FALSE;
					}
				}

				case IDC_BTN_ADD:
				{
					WCHAR text[MAX_PATH];
					GetWindowText(hTxtWord, text, MAX_PATH);

					if (lstrlen(text) <= 0) return FALSE;

					int idx = SendMessage(hLbxList, LB_ADDSTRING, NULL, (LPARAM)text);
					if (idx == LB_ERR) return FALSE;

					SendMessage(hLbxList, LB_SETITEMDATA, idx, text);
					SetWindowText(hTxtWord, NULL);

					// show the 'Start' button if any item is available
					UIUpdateState(hDlg);

					return TRUE;
				}

				case IDHELP:
				{
					//CoDlgAbout(hDlg);
					CoDlgHelp(hDlg);
					return TRUE;
				}

				case MENU_REMOVE:
				{
					// remove selected item from the blacklist
					int idx = SendMessage(hLbxList, LB_GETCURSEL, 0, 0);
					if (idx == LB_ERR) return FALSE;

					SendMessage(hLbxList, LB_DELETESTRING, idx, 0);
					return UIUpdateState(hDlg);
				}

				case IDC_BTN_OK:
				{
					return BeginSession(hDlg);
				}

				default: return FALSE;
			}
		}

		case WM_HELP:
			//CoDlgAbout(hDlg);
			CoDlgHelp(hDlg);
			return TRUE;

		case WM_CONTEXTMENU:
		{
			if (wParam == hLbxList)
			{
				int result = SendMessage(hLbxList, LB_GETCURSEL, 0, 0);
				if (result == LB_ERR) return FALSE;

				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				if (x < 0 || y < 0)
				{
					POINT pt;
					GetCursorPos(&pt);
					x = pt.x;
					y = pt.y;
				}

				return TrackPopupMenu(hLbxMenu, TPM_LEFTALIGN, x, y, NULL, hDlg, NULL);
			}

			return FALSE;
		}

		default:
			return FALSE;
	}
}