#pragma once
#ifndef CORE_H
#define CORE_H

#include <wtypes.h>

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

BOOL CoMainLoop(WCHAR *blacklist[], int blacklistCount);
BOOL CoDlgAbout(HWND hParent);

#endif