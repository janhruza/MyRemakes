#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <wtypes.h>

#include "Person.h"
#include "Vehicle.h"
#include "Weapon.h"

#define MAX_PERSONS		4096
#define MAX_VEHICLES	1024
#define MAX_WEAPONS		128

#define GLOBAL_DB_PATH	TEXT("Database.bin")

typedef struct tagDatabase
{
	Person Persons[MAX_PERSONS];
	Vehicle Vehicles[MAX_VEHICLES];
	Weapon Weapons[MAX_WEAPONS];

} Database, *PDatabase, *DatabasePtr;

PDatabase DbCreate(void);
BOOL DbFree(PDatabase ptr);
BOOL DbInit(PDatabase ptr);
BOOL DbLoad(PDatabase ptr, WCHAR* filepath);
BOOL DbSave(PDatabase ptr, WCHAR* filename);

#endif