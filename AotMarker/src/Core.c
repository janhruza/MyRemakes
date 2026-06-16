#include "..\inc\Core.h"

BOOL CALLBACK CoEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	// window enumeration
	HWND hCbx = (HWND)lParam;

	WCHAR text[MAX_PATH];
	GetWindowText(hWnd, text, MAX_PATH);

	if (IsWindowVisible(hWnd) && lstrlen(text) > 0)
	{
		int idx = SendMessage(hCbx, CB_ADDSTRING, 0, (LPCWSTR)text);
		SendMessage(hCbx, CB_SETITEMDATA, idx, hWnd);
	}
}

BOOL CoEnumWindows(HWND hCbx)
{
	return EnumWindows(CoEnumWindowsProc, hCbx);
}

BOOL CoDlgAbout(HWND hDlg)
{
	return ShellAbout(hDlg, APP_NAME, TEXT("\x00A9 2026 Jan Hruza"), NULL);
}