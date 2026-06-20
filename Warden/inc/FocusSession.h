#pragma once
#ifndef FOCUSSESSION_H
#define FOCUSSESSION_H

#include <wtypes.h>

#define FS_MAX_ITEMS	64

typedef struct tagFocusSession
{
	int nCount;
	WCHAR blacklist[FS_MAX_ITEMS][MAX_PATH];
} FocusSession, *PFocusSession;

PFocusSession FSCreate(void);
BOOL FSDestroy(PFocusSession pSesh);
BOOL FSInitialize(PFocusSession pSesh);

#endif