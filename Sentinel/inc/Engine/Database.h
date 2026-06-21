#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <wtypes.h>

#include "Person.h"

typedef struct tagDatabase
{
	PPerson Persons;
	int nPersons;

} Database, *PDatabase;

#endif