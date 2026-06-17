#pragma once
#include <Windows.h>

#define APP_NAME	TEXT("AoT Maker")

BOOL CoEnumWindows(HWND hCbx);
BOOL CoDlgAbout(HWND hDlg);
BOOL CoIsWindowAOT(HWND hWnd);
BOOL CoToggleAOT(HWND hWnd, BOOL value);