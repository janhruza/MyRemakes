#include "..\inc\Globals.h"

DatabasePtr gDatabase = NULL;
PConfig gConfig = NULL;

CrimeInfo gCrimes[MAX_CRIMES] = { 0 };
WCHAR* gCountries[MAX_COUNTRIES] = { 0 };

BOOL GlobSetDbPtr(PDatabase ptr)
{
	gDatabase = ptr;
	return TRUE;
}

DatabasePtr GlobGetDbPtr(void)
{
	return gDatabase;
}

BOOL GlobSetConfigPtr(PConfig ptr)
{
	gConfig = ptr;
	return TRUE;
}

PConfig GlobGetConfigPtr(void)
{
	return gConfig;
}