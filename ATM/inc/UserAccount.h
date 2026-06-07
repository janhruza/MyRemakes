#pragma once
#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <wtypes.h>

#define MAX_NAME_LENGTH 256

#define APP_DATA_FILE_NAME	TEXT(".\\data\\clients.ini")
#define KEY_ACCOUNT_NAME	TEXT("Name")
#define KEY_ACCOUNT_PIN		TEXT("PIN")
#define KEY_ACCOUNT_BALANCE	TEXT("Balance")
#define CLIENT_SECTION		TEXT("Accounts")

typedef struct tagUserAccount
{
	USHORT PIN;
	DOUBLE balance;
	WCHAR name[MAX_NAME_LENGTH];
} UserAccount, *PUserAccount;

BOOL UACreateAccount(PUserAccount account);
BOOL UADeleteAccount(PUserAccount account);
BOOL UAUpdateAccount(PUserAccount account);
BOOL UARetrieveAccount(PUserAccount account, LPWSTR username);
BOOL UALoginByPin(PUserAccount account, int enteredPin);

#endif // USERACCOUNT_H