#pragma once
#ifndef CTLVEHICLES_H
#define CTLVEHICLES_H

#include <wtypes.h>

enum
{
	MENU_ADD_VEHICLE = 0x1000,
	MENU_ABOUT_VEHICLE,
	MENU_REMOVE_VEHICLE,
	MENU_REFRESH
};

BOOL CALLBACK CtlVehiclesProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif