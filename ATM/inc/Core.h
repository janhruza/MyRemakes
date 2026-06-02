#pragma once
#ifndef CORE_H
#define CORE_H

#include <Windows.h>

extern HWND hAppWindow;
extern HWND hCtlLogin;
extern HWND hCtlNewAccount;

BOOL CoInitWindows(HWND hDlg);
BOOL CoHideAllControls(void);
BOOL CoShowControl(HWND hCtl);
BOOL CoNotImplemented(HWND hParent);

#endif