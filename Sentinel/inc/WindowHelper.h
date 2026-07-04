#pragma once
#ifndef SENTINEL_WINDOWHELPER_H
#define SENTINEL_WINDOWHELPER_H

#include <wtypes.h>

BOOL WhFitContent(HWND hParent, HWND hControl);
BOOL WhCenterWindow(HWND hWnd);
BOOL WhCenterChildWindow(HWND hParent, HWND hChild);

HWND WhGetOwner(HWND hWnd);

#endif