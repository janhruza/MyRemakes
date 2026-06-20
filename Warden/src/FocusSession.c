#include "..\inc\FocusSession.h"

#include <stdlib.h>

PFocusSession FSCreate(void)
{
	void* ptr = malloc(sizeof(FocusSession));
	return (PFocusSession)ptr;
}

BOOL FSDestroy(PFocusSession pSesh)
{
	if (pSesh == NULL) return FALSE;
	free(pSesh);
	return TRUE;
}

BOOL FSInitialize(PFocusSession pSesh)
{
	if (pSesh == NULL) return FALSE;
	memset(pSesh, 0, sizeof(FocusSession));
	return TRUE;
}