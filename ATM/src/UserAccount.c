#include "..\inc\UserAccount.h"

BOOL UACreateAccount(PUserAccount account)
{
	if (account == NULL)
	{
		return FALSE;
	}

	CreateDirectory(TEXT(".\\data"), NULL);

	if (lstrlen(account->name) == 0)
	{
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	// FIXME temp solution
	return WritePrivateProfileStruct(
		CLIENT_SECTION,
		account->name,
		account,
		sizeof(UserAccount),
		APP_DATA_FILE_NAME
	);
}

BOOL UADeleteAccount(PUserAccount account)
{
	if (account == NULL)
	{
		return FALSE;
	}

	return WritePrivateProfileString(CLIENT_SECTION, account->name, NULL, APP_DATA_FILE_NAME);
}

BOOL UAUpdateAccount(PUserAccount account)
{
	if (account == NULL)
	{
		return FALSE;
	}

	return WritePrivateProfileStruct(CLIENT_SECTION, account->name, account, sizeof(UserAccount), APP_DATA_FILE_NAME);
}

BOOL UARetrieveAccount(PUserAccount account, LPWSTR username)
{
	if (account == NULL || username == NULL)
	{
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	if (lstrlen(username) == 0)
	{
		SetLastError(E_FAIL);
		return FALSE;
	}

	return GetPrivateProfileStruct(
		CLIENT_SECTION,
		username,
		account,
		sizeof(UserAccount),
		APP_DATA_FILE_NAME
	);
}

BOOL UALoginByPin(PUserAccount account, int enteredPin)
{
	if (account == NULL)
	{
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	WCHAR buffer[4096] = { 0 };
	GetPrivateProfileString(
		CLIENT_SECTION,
		NULL,
		TEXT(""),
		buffer,
		4096,
		APP_DATA_FILE_NAME
	);

	WCHAR* currentUsername = buffer;
	while (*currentUsername != L'\0')
	{
		UserAccount tempAcc = { 0 };
		if (GetPrivateProfileStruct(
			CLIENT_SECTION,
			currentUsername,
			&tempAcc,
			sizeof(UserAccount),
			APP_DATA_FILE_NAME))
		{
			if (tempAcc.PIN == enteredPin)
			{
				memcpy(account, &tempAcc, sizeof(UserAccount));
				return TRUE;
			}
		}

		currentUsername += lstrlen(currentUsername) + 1;
	}

	SetLastError(E_FAIL);
	return FALSE;
}