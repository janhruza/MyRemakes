#pragma once

#ifndef DLGMAINWINDOW_H
#define DLGMAINWINDOW_H
#include <Windows.h>

#define MI_ABOUT	0x1001

BOOL InitSysMenu(HWND hDlg);

INT_PTR CALLBACK DlgMainWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif