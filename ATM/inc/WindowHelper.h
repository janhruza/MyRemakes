#pragma once
#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H
#include <Windows.h>

// dialogs
extern HWND hCtlLogin;;
extern HWND hCtlNewAccount;

/// <summary>
/// Resizes the window with the given handle (hWnd) to the exact size of the child control (hCtl) with a small margin.
/// </summary>
/// <param name="hWnd">Handle to the main window.</param>
/// <param name="hCtl">Handle to the child control.</param>
/// <returns>Operation result.</returns>
BOOL WhFitContent(HWND hWnd, HWND hCtl);

/// <summary>
/// Centers the given window (hWnd).
/// </summary>
/// <param name="hWnd">Handle to the target window.</param>
/// <returns>Operation result.</returns>
BOOL WhCenterWindow(HWND hWnd);

#endif