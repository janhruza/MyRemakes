#pragma once
#ifndef CORE_H
#define CORE_H

#include <Windows.h>

#define APP_NAME		TEXT("ATM")

extern HWND hAppWindow;
extern HWND hCtlLogin;
extern HWND hCtlNewAccount;
extern HWND hCtlLanding;

BOOL CoInitWindows(HWND hDlg);
BOOL CoHideAllControls(void);
BOOL CoShowControl(HWND hCtl);
BOOL CoNotImplemented(HWND hParent);

#endif