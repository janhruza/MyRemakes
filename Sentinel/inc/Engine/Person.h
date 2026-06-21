#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <wtypes.h>

typedef struct tagPerson
{
	UINT Id;
	UINT Level;
	DATE LastSeen;
	DATE CreationDate;
	WCHAR Name[32];
	
} Person, *PPerson;

#endif