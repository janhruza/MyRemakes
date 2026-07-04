#pragma once
#ifndef CRIME_H
#define CRIME_H

#include <wtypes.h>

#define MAX_CRIME_NAME	33		// 32 characters + null terminator
#define MAX_CRIME_DESC	256		// 255 characters + null terminator

typedef enum tagCrimeType
{
	CT_FELONY,
	CT_MISDEMEANOR,
	CT_INFRACTION,
	CT_VIOLATION,
	CT_LAST

} CrimeType;

typedef struct tagCrime
{
	UINT Id;
	WCHAR Name[MAX_CRIME_NAME];
	WCHAR Description[MAX_CRIME_DESC];
	USHORT Type; /* Use the CrimeType enum values */

} Crime, *PCrime;

#endif