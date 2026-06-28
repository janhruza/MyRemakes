#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <wtypes.h>

#define CFG_FILENAME	TEXT("config.bin")

typedef struct tagConfig
{
	int nPersonIdx;
	int nVehicleIdx;
	int nWeaponIdx;
	int nPersonId;
	int nVehicleId;
	int nWeaponId;

} Config, * PConfig;

PConfig CreateConfig(void);
BOOL LoadConfig(PConfig ptr);
BOOL SaveConfig(PConfig ptr);
BOOL ResetConfig(PConfig ptr);
BOOL FreeConfig(PConfig ptr);

#endif