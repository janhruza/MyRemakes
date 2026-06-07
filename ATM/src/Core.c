#include "..\inc\Core.h"
#include "..\inc\WindowHelper.h"
#include "..\res\resource.h"

// individual windows
#include "..\inc\Controls\CtlLoginScr.h"
#include "..\inc\Controls\CtlNewAccount.h"
#include "..\inc\Controls\CtlLandingPage.h"

HWND hAppWindow;
HWND hCtlLogin;
HWND hCtlNewAccount;
HWND hCtlLanding;

BOOL CoInitWindows(HWND hDlg)
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	
	hCtlLogin = CreateDialog(hInst, MAKEINTRESOURCE(IDC_SCR_LOGIN), hDlg, CtlLoginScrProc);
	hCtlNewAccount = CreateDialog(hInst, MAKEINTRESOURCE(IDC_NEW_ACCOUNT), hDlg, CtlNewAccountProc);
	hCtlLanding = CreateDialog(hInst, MAKEINTRESOURCE(IDC_DLG_LANDING_PAGE), hDlg, CtlLandingPageProc);
	return TRUE;
}

BOOL CoHideAllControls(void)
{
	// dynamically hide all controls by using the global control handles
	ShowWindow(hCtlLogin, SW_HIDE);
	ShowWindow(hCtlNewAccount, SW_HIDE);
	ShowWindow(hCtlLanding, SW_HIDE);
	return TRUE;
}

BOOL CoShowControl(HWND hCtl)
{
	return ShowWindow(hCtl, SW_SHOW);
}

BOOL CoNotImplemented(HWND hParent)
{
	MessageBox(hParent, TEXT("Feature not implemented."), TEXT("Not implemented"), MB_OK | MB_ICONERROR);
	return TRUE;
}