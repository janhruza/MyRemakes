#include "..\inc\WindowHelper.h"

BOOL WhFitContent(HWND hWnd, HWND hCtl)
{
	RECT rc;
	GetWindowRect(hCtl, &rc);

	int childWidth = rc.right - rc.left;
	int childHeight = rc.bottom - rc.top;
	RECT rcClient = { 0, 0, childWidth, childHeight };
	DWORD dwStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwExStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_EXSTYLE);
	BOOL bHasMenu = (GetMenu(hWnd) != NULL);
	AdjustWindowRectEx(&rcClient, dwStyle, bHasMenu, dwExStyle);

	int finalWindowWidth = rcClient.right - rcClient.left;
	int finalWindowHeight = rcClient.bottom - rcClient.top;

	SetWindowPos(hWnd, NULL, 0, 0, finalWindowWidth, finalWindowHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	MoveWindow(hCtl, 0, 0, childWidth, childHeight, TRUE);
}

BOOL WhCenterWindow(HWND hWnd)
{
	if (hWnd == NULL)
	{
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	RECT rc;
	GetWindowRect(hWnd, &rc);

	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

	return MoveWindow(hWnd, x, y, w, h, TRUE);
}