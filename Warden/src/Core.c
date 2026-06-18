#include "..\inc\Core.h"
#include "..\res\Resource.h"
#include "..\inc\DlgHelpWindow.h"

#include <Windows.h>
#include <stdio.h>
#include <string.h>

BOOL CoMainLoop(WCHAR* blacklist[], int blacklistCount)
{
	while (TRUE)
	{
		// check the active window only
		HWND hActiveWnd = GetForegroundWindow();

		if (hActiveWnd != NULL)
		{
			WCHAR windowTitle[TITLE_LEN] = { 0 };
			if (GetWindowText(hActiveWnd, windowTitle, TITLE_LEN) > 0)
			{
				for (int i = 0; i < blacklistCount; i++)
				{
					// search for procrastination
					if (wcsstr(windowTitle, blacklist[i]) != NULL)
					{
						// procrastination detected, minimize window
						ShowWindow(hActiveWnd, SW_MINIMIZE);
						MessageBeep(MB_ICONWARNING);
						break;
					}
				}
			}
		}

		// limit CPU usage by iterating only once a second
		Sleep(FREQUENCY);
	}

	return TRUE;
}

BOOL CoDlgAbout(HWND hParent)
{
	return ShellAbout(hParent, TEXT("Warden"), TEXT("\x00A9 2026 Jan Hruza"), NULL);
}

BOOL CoDlgHelp(HWND hParent)
{
	return DialogBox(NULL, MAKEINTRESOURCE(IDD_DLGHELP), hParent, DlgHelpWindowProc);
}