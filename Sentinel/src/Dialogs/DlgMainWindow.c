#include "..\..\inc\Dialogs\DlgMainWindow.h"
#include "..\..\inc\Core.h"
#include "..\..\res\resource.h"

#include <Windows.h>

HBRUSH hBg;

BOOL CALLBACK DlgMainWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// enhance the system menu
			HMENU hMenu = GetSystemMenu(hDlg, FALSE);
			AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(hMenu, MF_STRING, IDHELP, TEXT("About\tF1"));

			// set the default bg color
			hBg = GetSysColorBrush(COLOR_WINDOW);
			return TRUE;
		}

		case WM_CTLCOLORBTN:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORDLG:
		{
			return (HBRUSH)hBg;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, IDCLOSE);
			return TRUE;
		}

		case WM_HELP:
		{
			return CoDlgAbout(hDlg);
		}

		case WM_SYSCOMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDHELP:
				{
					SendMessage(hDlg, WM_HELP, 0, 0);
					return TRUE;
				}

				default: return FALSE;
			}
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDHELP:
				{
					SendMessage(hDlg, WM_HELP, 0, 0);
					return TRUE;
				}

				case IDCLOSE:
				{
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case ID_HELP_WEBSITE:
				{
					ShellExecute(hDlg, TEXT("open"), LINK_GITHUB, NULL, NULL, SW_SHOWDEFAULT);
					return TRUE;
				}

				case ID_VEHICLES_LICENCEPLATEGENERATOR:
				{
					return CoDlgPlateGen(hDlg);
				}

				default: return FALSE;
			}
		}

		default: return FALSE;
	}
}