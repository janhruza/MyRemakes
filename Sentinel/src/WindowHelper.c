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

BOOL WhCenterChildWindow(HWND hParent, HWND hChild) {
    if (hParent == NULL || hChild == NULL) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // Get the bounding rectangle of the parent window in screen coordinates
    RECT rcParent;
    if (!GetWindowRect(hParent, &rcParent)) return FALSE;

    // Get the bounding rectangle of the child window in screen coordinates
    RECT rcChild;
    if (!GetWindowRect(hChild, &rcChild)) return FALSE;

    // Calculate dimensions of both windows
    int parentWidth = rcParent.right - rcParent.left;
    int parentHeight = rcParent.bottom - rcParent.top;

    int childWidth = rcChild.right - rcChild.left;
    int childHeight = rcChild.bottom - rcChild.top;

    // Calculate the relative center position
    int relX = (parentWidth - childWidth) / 2;
    int relY = (parentHeight - childHeight) / 2;

    // Convert to absolute screen coordinates by adding the parent's top-left corner
    int x = rcParent.left + relX;
    int y = rcParent.top + relY;

    // Prevent the dialog from being positioned outside the screen boundaries
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + childWidth > screenWidth)   x = screenWidth - childWidth;
    if (y + childHeight > screenHeight) y = screenHeight - childHeight;

    // Move the child window to the new position
    return MoveWindow(hChild, x, y, childWidth, childHeight, TRUE);
}

HWND WhGetOwner(HWND hWnd)
{
    return GetWindow(hWnd, GW_OWNER);
}

BOOL WhSetItemImage(HMENU hMenu, UINT uId, HBITMAP hImage)
{
    if (hMenu == NULL || hImage == NULL)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

    MENUITEMINFO info = { 0 };
    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_BITMAP;
    info.hbmpItem = hImage;

    return SetMenuItemInfo(hMenu, uId, FALSE, &info);
}

BOOL WhSetItemImageResource(HMENU hMenu, UINT uId, UINT resourceId)
{
    if (hMenu == NULL)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

    HINSTANCE hInst = GetModuleHandle(NULL);
    HBITMAP hImg = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(resourceId), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);

    if (hImg == NULL)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

    return WhSetItemImage(hMenu, uId, hImg);
}