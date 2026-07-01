#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Core.h"
#include "Config.h"

extern CrimeInfo gCrimes[MAX_CRIMES];

// country names
extern WCHAR* gCountries[MAX_COUNTRIES];

// weapon names
extern WCHAR* gWeaponNames[W_COUNT];

// global list of weapons
static const Weapon gWeapons[MAX_WEAPONS];

BOOL GlobSetDbPtr(PDatabase ptr);
DatabasePtr GlobGetDbPtr(void);

BOOL GlobSetConfigPtr(PConfig ptr);
PConfig GlobGetConfigPtr(void);

#endif