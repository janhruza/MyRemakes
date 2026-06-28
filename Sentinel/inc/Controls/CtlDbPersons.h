#pragma once
#ifndef CTLDBPERSONS_H
#define CTLDBPERSONS_H

#include <wtypes.h>

enum
{
	PERSON_DETAILS = 0x1001,
	PERSON_ADD_RECORD,
	PERSON_NEW_PERSON,
	PERSON_REMOVE
};

BOOL CtlDbPersonsProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif