#pragma once
#ifndef SENTINEL_DLGABOUT_H
#define SENTINEL_DLGABOUT_H

#include <wtypes.h>

#define BLOCK_LEN	5 * MAX_PATH

BOOL CALLBACK DlgAboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif