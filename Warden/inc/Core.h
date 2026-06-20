#pragma once
#ifndef CORE_H
#define CORE_H

#include <wtypes.h>
#include "FocusSession.h"

#define TITLE_LEN	512
#define FREQUENCY	1000

enum tagExitCodes
{
	ID_QUIT = IDCANCEL,
	ID_RUN_LOOP
} EXIT_CODES;

typedef struct tagBlacklist
{
	WCHAR* words[512];
	int wordsLen;

} blacklist;

DWORD WINAPI CoMainLoop(LPVOID lParam);
BOOL CoDlgAbout(HWND hParent);
BOOL CoDlgHelp(HWND hParent);

#endif