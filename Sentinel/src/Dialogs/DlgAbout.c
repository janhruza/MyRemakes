#include "..\..\inc\Dialogs\DlgAbout.h"

#include <Windows.h>
#include <strsafe.h>
#include <shlwapi.h>

#include "..\..\res\resource.h"

HBRUSH hBg = NULL;

BOOL CALLBACK DlgAboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CTLCOLORSTATIC:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		{
			return hBg;
		}

		case WM_INITDIALOG:
		{
			hBg = GetSysColorBrush(COLOR_WINDOW);

			HINSTANCE hInst = GetModuleHandle(NULL);
			HWND hEdit = GetDlgItem(hDlg, IDC_LICENSE);

			WCHAR header[MAX_PATH];
			WCHAR copyright[MAX_PATH];

			WCHAR text1[BLOCK_LEN];
			WCHAR text2[BLOCK_LEN];
			WCHAR text3[BLOCK_LEN];

			LoadString(hInst, IDS_LICENSE_HEADER, header, MAX_PATH);
			LoadString(hInst, IDS_LICENSE_COPYRIGHT, copyright, MAX_PATH);
			LoadString(hInst, IDS_LICENSE_TEXT1, text1, BLOCK_LEN);
			LoadString(hInst, IDS_LICENSE_TEXT2, text2, BLOCK_LEN);
			LoadString(hInst, IDS_LICENSE_TEXT3, text3, BLOCK_LEN);

			int maxlen = 5 * BLOCK_LEN;
			WCHAR* buf = malloc(maxlen * (sizeof(WCHAR) + 1));
			if (buf == NULL) return FALSE;

			memset(buf, 0, maxlen * sizeof(WCHAR));

			StringCbPrintf(buf, maxlen, TEXT("%s\r\n\r\n%s\r\n\r\n%s\r\n\r\n%s\r\n\r\n%s"), header, copyright, text1, text2, text3);
			SetWindowText(hEdit, buf);
			free(buf);

			// set bigger font
			/*HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit, WM_SETFONT, NULL, MAKELPARAM(TRUE, 0));*/

			return TRUE;
		}

		case WM_CLOSE:
			EndDialog(hDlg, IDCLOSE);
			return TRUE;

		case WM_DESTROY:
		{
			
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
			{
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