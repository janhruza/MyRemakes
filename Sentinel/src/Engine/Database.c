#include "..\..\inc\Engine\Database.h"
#include "..\..\inc\Globals.h"

#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>

PDatabase DbCreate(void)
{
	PDatabase ptr = malloc(sizeof(Database));
	return ptr;
}

BOOL DbFree(PDatabase ptr)
{
	if (ptr == NULL) return FALSE;
	free(ptr);
	return TRUE;
}

BOOL DbInit(PDatabase ptr)
{
	if (ptr == NULL) return FALSE;
	memset(ptr, 0, sizeof(Database));

	// set weapons
	for (int i = 0; i < W_COUNT; i++)
	{
		ptr->Weapons[i] = gWeapons[i];
	}

	return TRUE;
}

BOOL DbLoad(PDatabase ptr, WCHAR* filepath)
{
	FILE* file = _wfopen(filepath, L"rb");
	if (file == NULL)
	{
		return FALSE;
	}

	size_t count = fread(ptr, sizeof(Database), 1, file);
	fclose(file);
	return count > 0 ? TRUE : FALSE;
}

BOOL DbSave(PDatabase ptr, WCHAR* filename)
{
	FILE* file = _wfopen(filename, L"wb");
	if (file == NULL) return FALSE;

	size_t count = fwrite(ptr, sizeof(Database), 1, file);
	fclose(file);
	return count > 0 ? TRUE : FALSE;
}

BOOL DbAddPerson(DatabasePtr db, Person person)
{
	if (db == NULL)
	{
		return FALSE;
	}

	if (person.Id == 0)
	{
		return FALSE;
	}

	// find a free spot
	for (int i = 0; i < MAX_PERSONS; i++)
	{
		if (db->Persons[i].Id == 0)
		{
			// free position found
			db->Persons[i] = person;

			// save the DB
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DbRemovePerson(DatabasePtr db, UINT personId)
{
	if (db == NULL) return FALSE;
	if (personId == 0) return FALSE;

	for (int i = 0; i < MAX_PERSONS; i++)
	{
		if (db->Persons[i].Id == personId)
		{
			memset(&db->Persons[i], 0, sizeof(Person));
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DbAddVehicle(PDatabase db, Vehicle vehicle)
{
	if (db == NULL) return FALSE;
	if (vehicle.Id == 0) return FALSE;

	for (int i = 0; i < MAX_VEHICLES; i++)
	{
		if (db->Vehicles[i].Id == 0)
		{
			db->Vehicles[i] = vehicle;

			// save the DB
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DbRemoveVehicle(PDatabase db, UINT vehicleId)
{
	if (db == NULL) return FALSE;
	if (vehicleId == 0) return FALSE;

	for (int i = 0; i < MAX_VEHICLES; i++)
	{
		if (db->Vehicles[i].Id == vehicleId)
		{
			memset(&db->Vehicles[i], 0, sizeof(Vehicle));
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DbAddWeapon(PDatabase db, Weapon weapon)
{
	if (db == NULL) return FALSE;
	if (weapon.Id == 0) return FALSE;

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (db->Weapons[i].Id == 0)
		{
			db->Weapons[i] = weapon;
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DbRemoveWeapon(PDatabase db, UINT weaponId)
{
	if (db == NULL) return FALSE;
	if (weaponId == 0) return FALSE;

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (db->Weapons[i].Id == weaponId)
		{
			memset(&db->Weapons[i], 0, sizeof(Weapon));
			DbSaveGlobal(db);
			return TRUE;
		}
	}

	return FALSE;
}