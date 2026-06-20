#include "..\inc\Core.h"
#include "..\res\Resource.h"
#include "..\inc\DlgHelpWindow.h"
#include "..\inc\ThreadParams.h"

#include <Windows.h>
#include <stdio.h>
#include <string.h>

DWORD WINAPI CoMainLoop(LPVOID lpParam)
{
	PThreadParams pParams = (PThreadParams)lpParam;
	if (pParams == NULL) return 0;

	while (!IsWindowVisible(pParams->hDlg))
	{
		HWND hActiveWnd = GetForegroundWindow();

		if (hActiveWnd != NULL && hActiveWnd != pParams->hDlg)
		{
			WCHAR windowTitle[TITLE_LEN] = { 0 };
			if (GetWindowTextW(hActiveWnd, windowTitle, TITLE_LEN) > 0)
			{
				for (int i = 0; i < pParams->pSession->nCount; i++)
				{
					if (wcsstr(windowTitle, pParams->pSession->blacklist[i]) != NULL)
					{
						ShowWindow(hActiveWnd, SW_MINIMIZE);
						MessageBeep(MB_ICONWARNING);
						break;
					}
				}
			}
		}

		Sleep(FREQUENCY);
	}

	free(pParams);
	return 0;
}

BOOL CoDlgAbout(HWND hParent)
{
	return ShellAbout(hParent, TEXT("Warden"), TEXT("\x00A9 2026 Jan Hruza"), NULL);
}

BOOL CoDlgHelp(HWND hParent)
{
	return DialogBox(NULL, MAKEINTRESOURCE(IDD_DLGHELP), hParent, DlgHelpWindowProc);
}