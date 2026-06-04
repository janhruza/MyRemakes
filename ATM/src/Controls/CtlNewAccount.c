#include "..\..\inc\Controls\CtlNewAccount.h"
#include "..\..\inc\WindowHelper.h"

#include "..\..\inc\Core.h"
#include "..\..\inc\UserAccount.h"

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
					// the 'Cancel' button
					CoHideAllControls();
					CoShowControl(hCtlLogin);
					WhFitContent(hAppWindow, hCtlLogin);
					return TRUE;
				}

				case IDOK:
				{
					// the 'Create' button
					CoNotImplemented(hDlg);
					return TRUE;
				}

				default: return FALSE;
			}
		}

		default: break;
	}
	return FALSE;
}