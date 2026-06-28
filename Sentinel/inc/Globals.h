#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Core.h"
#include "Config.h"

extern CrimeInfo gCrimes[MAX_CRIMES];

BOOL GlobSetDbPtr(PDatabase ptr);
DatabasePtr GlobGetDbPtr(void);

BOOL GlobSetConfigPtr(PConfig ptr);
PConfig GlobGetConfigPtr(void);

#endif