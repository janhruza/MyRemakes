#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <wtypes.h>

#define TEXT_LEN	65
#define MAX_COUNTRIES	MAX_PATH

// TODO add values and update the
// corresponding string array (gCountries)
typedef enum tagCountryFlag
{
	COUNTRY_OTHER = 0,	ARG,	AUS,	AUT,	BEL,
	BRA,	CAN,		CHN,	CZE,	DEN,	FIN,
	FRA,	GBR,		GER,	GRE,	IND,	IRL,
	ISR,	ITA,		JPN,	KOR,	MEX,	NED,
	NOR,	NZL,		POL,	POR,	RSA,	SGP,
	SPA,	SUI,		SVK,	SWE,	TUR,	UKR,
	USA,	COUNTRY_LAST
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