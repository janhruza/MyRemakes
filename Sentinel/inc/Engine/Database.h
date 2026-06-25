#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <wtypes.h>

#include "Person.h"
#include "Vehicle.h"

typedef struct tagDatabase
{
	PPerson Persons;
	int nPersons;

	PVehicle Vehicles;
	int nVehicles;

} Database, *PDatabase, *DatabasePtr;

#endif