#include "..\..\inc\Controls\CtlNewAccount.h"
#include "..\..\inc\WindowHelper.h"

#include "..\..\inc\Core.h"

INT_PTR CALLBACK CtlNewAccountProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDCANCEL:
				{
					CoHideAllControls();
					CoShowControl(hCtlLogin);
					WhFitContent(hAppWindow, hCtlLogin);
					return TRUE;
				}

				case IDOK:
				{
					// the 'Create' button
					return TRUE;
				}

				default: return FALSE;
			}
		}

		default: break;
	}
	return FALSE;
}