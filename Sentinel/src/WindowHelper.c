#include "..\inc\WindowHelper.h"
#include <wtypes.h>

BOOL WhFitContent(HWND hParent, HWND hControl)
{
	RECT rc;
	GetWindowRect(hControl, &rc);

	int childWidth = rc.right - rc.left;
	int childHeight = rc.bottom - rc.top;
	RECT rcClient = { 0, 0, childWidth, childHeight };
	DWORD dwStyle = (DWORD)GetWindowLongPtr(hParent, GWL_STYLE);
	DWORD dwExStyle = (DWORD)GetWindowLongPtr(hParent, GWL_EXSTYLE);
	BOOL bHasMenu = (GetMenu(hParent) != NULL);
	AdjustWindowRectEx(&rcClient, dwStyle, bHasMenu, dwExStyle);

	int finalWindowWidth = rcClient.right - rcClient.left;
	int finalWindowHeight = rcClient.bottom - rcClient.top;

	SetWindowPos(hParent, NULL, 0, 0, finalWindowWidth, finalWindowHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	MoveWindow(hControl, 0, 0, childWidth, childHeight, TRUE);

	return TRUE;
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