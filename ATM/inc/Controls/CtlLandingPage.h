#pragma once
#ifndef CTLLANDINGPAGE_H
#define CTLLANDINGPAGE_H

#include <Windows.h>

INT_PTR CALLBACK CtlLandingPageProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

static void InitializeMenu(void);

#endif // CTLLANDINGPAGE_H