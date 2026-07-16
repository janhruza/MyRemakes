#pragma once
#ifndef CTLWEAPONS_H
#define CTLWEAPONS_H

#include <wtypes.h>

enum
{
	MENU_ADD_WEAPON = 0x1000,
	MENU_ABOUT_WEAPON,
	MENU_REMOVE_WEAPON,
	MENU_REFRESH_WEAPONS
};

BOOL CALLBACK CtlWeaponsProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif