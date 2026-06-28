#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <wtypes.h>

#define TEXT_LEN	65

// TODO add values
typedef enum tagCountryFlag
{
	OTHER = 0, USA, CAN, GER, CZE, GBR
} Country;

typedef struct tagPerson
{
	UINT Id;
	UINT Level;
	SYSTEMTIME LastSeen;
	SYSTEMTIME CreationDate;
	Country Nationality;
	WCHAR Name[TEXT_LEN];
	
} Person, *PPerson, *PersonPtr;

#endif