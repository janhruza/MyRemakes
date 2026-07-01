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
	COUNTRY_OTHER = 0,
	USA,
	CAN,
	GER,
	CZE,
	GBR,
	SPA,
	FRA,
	ITA,
	SVK,
	POL,
	AUT,
	CHN,
	JPN,
	IND,
	BRA,
	MEX,
	AUS,
	KOR,
	NED,
	BEL,
	SUI,
	SWE,
	NOR,
	FIN,
	DEN,
	POR,
	GRE,
	TUR,
	UKR,
	RSA,
	ARG,
	NZL,
	ISR,
	SGP,
	IRL,
	COUNTRY_LAST
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