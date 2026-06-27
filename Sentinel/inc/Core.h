#pragma once
#ifndef SENTINEL_CORE_H
#define SENTINEL_CORE_H

#include <wtypes.h>

#include "Engine/Vehicle.h"
#include "Engine/Person.h"

#define LINK_GITHUB		TEXT("https://www.github.com/janhruza/MyRemakes")
#define CoShowDialog(hParent, dlgId, lpDlgProc) (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(dlgId), hParent, lpDlgProc))

#define MAX_CRIMES	MAX_PATH

#pragma region Structs

enum
{
	CRIME_MURDER = 0,
	CRIME_THEFT,
	CRIME_ROBBERY,
	CRIME_ASSAULT,
	CRIME_ASSASSINATION,
	CRIME_VANDALISM,
	CRIME_SPEEDING
};

typedef struct tagCrimeInfo
{
	UINT Id;
	UINT Penalty;
	WCHAR Name[MAX_PATH];

} CrimeInfo, *PCRIME;

#pragma endregion

BOOL CoDlgAbout(HWND hOwner);
BOOL CoNotImplemented(HWND hParent);

// random generator
BOOL CoInitRandomness(void);

// dialogs
BOOL CoDlgPlateGen(HWND hParent);

/// <summary>
/// Representing the new person dialog.
/// </summary>
/// <param name="hParent"></param>
/// <returns></returns>
BOOL CoDlgNewPerson(HWND hParent);

/// <summary>
/// Representing the new vehicle dialog.
/// </summary>
/// <param name="hParent"></param>
/// <returns></returns>
BOOL CoDlgNewVehicle(HWND hParent);

/// <summary>
/// Representing the new weapon dialog.
/// </summary>
/// <param name="hParent"></param>
/// <returns></returns>
BOOL CoDlgNewWeapon(HWND hParent);

BOOL CoDlgVehicleInfo(HWND hParent, VehiclePtr vehicle);

BOOL CoDlgPersonInfo(HWND hParent, PersonPtr person);

#endif