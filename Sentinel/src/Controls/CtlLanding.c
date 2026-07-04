#include "..\..\inc\Controls\CtlLanding.h"
#include "..\..\res\resource.h"

#include <strsafe.h>

#define MY_TIMER_ID		0x1000
#define	TIMER_FREQ		500

static BOOL UpdateTime(HWND hCtl)
{
	HWND hTxt = GetDlgItem(hCtl, IDC_LBL_TIME);

	SYSTEMTIME time;
	GetLocalTime(&time);

	WCHAR text[32];
	StringCchPrintf(text, 32, TEXT("%02d:%02d:%02d\n"), time.wHour, time.wMinute, time.wSecond);
	SetWindowText(hTxt, text);
	return TRUE;
}

static void Timerproc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	// 500ms timer
	UpdateTime(hWnd);
}

BOOL CALLBACK CtlLandingProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// setup timer
			SetTimer(hCtl, MY_TIMER_ID, TIMER_FREQ, Timerproc);

			// display current time
			UpdateTime(hCtl);
			return TRUE;
		}

		default: break;
	}

	return FALSE;
}