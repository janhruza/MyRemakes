#pragma once
#ifndef TRAYICON_H
#define TRAYICON_H

#include <wtypes.h>

#define WM_TRAYICON		(WM_USER + 1)

void Tray_AddIcon(HWND hDlg);
void Tray_RemoveIcon(HWND hDlg);

#endif