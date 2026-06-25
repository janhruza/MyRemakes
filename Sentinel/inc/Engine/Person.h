#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <wtypes.h>

// TODO add values
typedef enum tagCountryFlag
{
	OTHER = 0, USA, CAN, GER, CZE, GBR
} Country;

typedef struct tagPerson
{
	UINT Id;
	UINT Level;
	DATE LastSeen;
	DATE CreationDate;
	Country Nationality;
	WCHAR Name[32];
	
} Person, *PPerson, *PersonPtr;

#endif