#include "..\..\inc\Controls\CtlNewAccount.h"
#include "..\..\inc\WindowHelper.h"

#include "..\..\inc\Core.h"
#include "..\..\inc\UserAccount.h"
#include "..\..\res\resource.h"

static BOOL UICreateUserAccount(HWND hDlg)
{
	if (hDlg == NULL) return FALSE;

	WCHAR name[MAX_NAME_LENGTH] = { 0 };
	GetDlgItemText(hDlg, IDC_TXT_USERNAME, name, MAX_NAME_LENGTH);

	UserAccount acc = { 0 };
	acc.PIN = GetDlgItemInt(hDlg, IDC_TXT_PIN, NULL, FALSE);
	lstrcpy(acc.name, name);
	return UACreateAccount(&acc);
}

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
					if (UICreateUserAccount(hDlg) == TRUE)
					{
						MessageBox(hDlg, TEXT("Account created successfully!"), TEXT("Success"), MB_OK | MB_ICONINFORMATION);
						CoHideAllControls();
						CoShowControl(hCtlLogin);
						WhFitContent(hAppWindow, hCtlLogin);
						return TRUE;

					}
					else
					{
						DWORD err = GetLastError();

						WCHAR text[512] = { 0 };
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, LANG_USER_DEFAULT, text, 512, NULL);

						MessageBox(hDlg, text, TEXT("Error"), MB_OK | MB_ICONERROR);
						return TRUE;
					}
				}

				default: return FALSE;
			}
		}

		default: break;
	}
	return FALSE;
}