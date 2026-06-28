#include "..\inc\Config.h"

#include <stdio.h>

PConfig CreateConfig(void)
{
	PConfig ptr = (PConfig)malloc(sizeof(Config));
	return ptr;
}

BOOL LoadConfig(PConfig ptr)
{
	if (ptr == NULL)
	{
		return FALSE;
	}

	FILE* file = _wfopen(CFG_FILENAME, L"rb");
	if (file == NULL)
	{
		return FALSE;
	}

	fread(ptr, sizeof(Config), 1, file);
	fclose(file);
	return TRUE;
}

BOOL SaveConfig(PConfig ptr)
{
	if (ptr == NULL)
	{
		return FALSE;
	}

	FILE* file = _wfopen(CFG_FILENAME, L"wb");
	if (file == NULL)
	{
		return FALSE;
	}

	fwrite(ptr, sizeof(Config), 1, file);
	fclose(file);
	return TRUE;
}

BOOL ResetConfig(PConfig ptr)
{
	if (ptr == NULL)
	{
		return FALSE;
	}

	// reset all counters
	ptr->nPersonId = 1;
	ptr->nPersonIdx = 0;
	ptr->nVehicleId = 1;
	ptr->nVehicleIdx = 0;
	ptr->nWeaponId = 1;
	ptr->nWeaponIdx = 0;

	return TRUE;
}

BOOL FreeConfig(PConfig ptr)
{
	if (ptr == NULL) return FALSE;
	free(ptr);
	return TRUE;
}