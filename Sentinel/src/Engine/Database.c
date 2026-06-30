#include "..\..\inc\Engine\Database.h"

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
	memset(ptr, 0, sizeof(Database));
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

	// find a free spot
	for (int i = 0; i < MAX_PERSONS; i++)
	{
		if (db->Persons[i].Id == 0)
		{
			// free position found
			db->Persons[i] = person;

			// save the DB
			DbSave(db, GLOBAL_DB_PATH);
			break;
		}
	}

	return TRUE;
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
			return TRUE;
		}
	}

	return FALSE;
}