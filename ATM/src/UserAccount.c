#include "..\inc\UserAccount.h"

BOOL UACreateAccount(PUserAccount account)
{
	if (account == NULL)
	{
		return FALSE;
	}

	CreateDirectory(TEXT(".\\data"), NULL);

	// FIXME temp solution
	return WritePrivateProfileStruct(
		TEXT("Accounts"),
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

	return WritePrivateProfileString(TEXT("Accounts"), account->name, NULL, APP_DATA_FILE_NAME);
}

BOOL UAUpdateAccount(PUserAccount account)
{
	if (account == NULL)
	{
		return FALSE;
	}

	return WritePrivateProfileStruct(TEXT("Accounts"), account->name, account, sizeof(UserAccount), APP_DATA_FILE_NAME);
}