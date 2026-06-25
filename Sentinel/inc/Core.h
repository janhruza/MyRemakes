#pragma once
#ifndef SENTINEL_CORE_H
#define SENTINEL_CORE_H

#include <wtypes.h>

#define LINK_GITHUB		TEXT("https://www.github.com/janhruza/MyRemakes")
#define CoShowDialog(hParent, dlgId, lpDlgProc) (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(dlgId), hParent, lpDlgProc))

BOOL CoDlgAbout(HWND hOwner);
BOOL CoNotImplemented(HWND hParent);

// random generator
BOOL CoInitRandomness(void);

// dialogs
BOOL CoDlgPlateGen(HWND hParent);

#endif