#include "..\..\inc\Controls\CtlLoginScr.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"
#include <CommCtrl.h>

#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\UserAccount.h"

static BOOL UIAttemptLogin(HWND hDlg)
{
	if (hDlg == NULL) return FALSE;
	return TRUE;
}

INT_PTR CALLBACK CtlLoginScrProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDRETRY:
				{
					// clear button clicked
					HWND hPin = GetDlgItem(hDlg, IDC_TXT_PIN);
					SetWindowText(hPin, TEXT(""));
					return TRUE;
				}

				case IDC_BTN_LOGIN:
				{
					// login button clicked
					UserAccount acc;
					if (UALoginByPin(&acc, GetDlgItemInt(hDlg, IDC_TXT_PIN, NULL, FALSE)) == TRUE)
					{
						// login successful
						// clear the PIN box
						SendMessage(hDlg, WM_COMMAND, IDRETRY, 0);

						// show the landing page
						HWND hParent = GetParent(hDlg);
						CoHideAllControls();
						CoShowControl(hCtlLanding);
						WhFitContent(hParent, hCtlLanding);
						return TRUE;
					}

					else
					{
						MessageBox(hDlg, TEXT("Invalid PIN. Please try again."), TEXT("Error"), MB_OK | MB_ICONERROR);
						return FALSE;
					}
				}

				default: break;
			}

			return FALSE;
		}

		case WM_NOTIFY:
		{
			if (!lParam) return FALSE;

			LPNMHDR pnmh = (LPNMHDR)lParam;
			if (pnmh->idFrom == IDC_CREATE_ACCOUNT)
			{
				if (pnmh->code == NM_CLICK || pnmh->code == NM_RETURN)
				{
					// create account link clicked
					HWND hParent = GetParent(hDlg);
					ShowWindow(hDlg, SW_HIDE);
					ShowWindow(hCtlNewAccount, SW_SHOW);
					WhFitContent(hParent, hCtlNewAccount);

					return TRUE;
				}
			}
			return FALSE;
		}

		// other messages
		default: return FALSE;
	}
	return FALSE;
}