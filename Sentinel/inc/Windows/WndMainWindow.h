#pragma once
#ifndef WNDMAINWINDOW_H
#define WNDMAINWINDOW_H

#include <wtypes.h>

#define SENTINEL_TITLE				TEXT("Sentinel")
#define SENTINEL_CLASS_NAME		TEXT("SentinelMainWindow")

BOOL CreateMainWindow(HINSTANCE hInst, WNDPROC lpfnWndProc);
LRESULT CALLBACK WndMainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif