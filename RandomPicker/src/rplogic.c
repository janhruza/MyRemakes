#include "..\inc\rplogic.h"

#include <stdlib.h>
#include <time.h>

BOOL RpAddPickerOption(HWND hEdit, HWND hLbx, LPWSTR lpszOption)
{
	if (hEdit == NULL) return FALSE;
	if (hLbx == NULL) return FALSE;
	if (lpszOption== NULL || wcslen(lpszOption) == 0) return FALSE;

	LRESULT result = SendMessage(hLbx, LB_ADDSTRING, 0, (LPARAM)lpszOption);
	if (result == LB_ERR || result == LB_ERRSPACE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL RpPickOption(HWND hLbx)
{
	if (hLbx == NULL) return FALSE;
	int nCount = SendMessage(hLbx, LB_GETCOUNT, 0, 0);

	if (nCount <= 0)
	{
		MessageBox(hLbx, TEXT("No pickable items available. Please add options to the pool first."), TEXT("Error"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// get the random index
	int idx = rand() % nCount;
	int textLen = (int)SendMessage(hLbx, LB_GETTEXTLEN, idx, 0);
	if (textLen == LB_ERR) return FALSE;

	// get the text
	WCHAR buf[MAX_PATH];
	LRESULT result = SendMessage(hLbx, LB_GETTEXT, idx, (LPARAM)buf);
	if (result == LB_ERR) return FALSE;

	// print the picked option
	WCHAR text[MAX_PATH];
	wsprintf(text, TEXT("Selected option: %s"), buf);
	MessageBox(hLbx, text, TEXT("Result"), MB_OK | MB_ICONINFORMATION);

	return TRUE;
}