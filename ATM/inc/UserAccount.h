#pragma once
#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <wtypes.h>

#define MAX_NAME_LENGTH 256

typedef struct tagUserAccount
{
	UINT PIN;
	DOUBLE balance;
	WCHAR name[MAX_NAME_LENGTH];
} UserAccount, *PUserAccount;

BOOL UACreateAccount(PUserAccount account);
BOOL UADeleteAccount(PUserAccount account);
BOOL UAUpdateAccount(PUserAccount account);

#endif // USERACCOUNT_H