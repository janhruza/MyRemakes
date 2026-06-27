#include "..\inc\Globals.h"

DatabasePtr gDatabase = NULL;
CrimeInfo gCrimes[MAX_CRIMES] = { 0 };

BOOL GlobSetDbPtr(PDatabase ptr)
{
	gDatabase = ptr;
	return TRUE;
}

DatabasePtr GlobGetDbPtr(void)
{
	return gDatabase;
}