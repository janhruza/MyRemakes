#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Core.h"

// TODO add array of crimes and misdemeanors
extern CrimeInfo gCrimes[MAX_CRIMES];

BOOL GlobSetDbPtr(PDatabase ptr);
DatabasePtr GlobGetDbPtr(void);

#endif