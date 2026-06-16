#pragma once
#include <Windows.h>

#define APP_NAME	TEXT("AoT Maker")

BOOL CoEnumWindows(HWND hCbx);
BOOL CoDlgAbout(HWND hDlg);
BOOL CoToggleAOT(HWND hWnd, BOOL value);