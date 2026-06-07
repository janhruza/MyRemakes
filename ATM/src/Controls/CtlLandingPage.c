#include "..\..\inc\Controls\CtlLandingPage.h"

INT_PTR CALLBACK CtlLandingPageProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{

			return TRUE;
		}

		default: return FALSE;
	}
}