#pragma once
#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H
#include <Windows.h>

// dialogs
extern HWND hCtlLogin;;
extern HWND hCtlNewAccount;

BOOL WhFitContent(HWND hWnd, HWND hCtl);
#endif