#include "..\inc\Core.h"
#include "..\inc\Globals.h"
#include "..\inc\Dialogs\DlgAbout.h"
#include "..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\inc\Dialogs\DlgNewPerson.h"
#include "..\res\resource.h"

#include <stdlib.h>
#include <time.h>

BOOL CoInitCountries(void)
{
	if (gCountries == NULL)
	{
		return FALSE;
	}

	// list countries
	gCountries[COUNTRY_OTHER] = TEXT("Other");
	gCountries[USA] = TEXT("United States of America");
	gCountries[CAN] = TEXT("Canada");
	gCountries[GER] = TEXT("Germany");
	gCountries[CZE] = TEXT("Czechia");
	gCountries[GBR] = TEXT("Great Britain");
	gCountries[SPA] = TEXT("Spain");

	gCountries[FRA] = TEXT("France");
	gCountries[ITA] = TEXT("Italy");
	gCountries[SVK] = TEXT("Slovakia");
	gCountries[POL] = TEXT("Poland");
	gCountries[AUT] = TEXT("Austria");
	gCountries[CHN] = TEXT("China");
	gCountries[JPN] = TEXT("Japan");
	gCountries[IND] = TEXT("India");
	gCountries[BRA] = TEXT("Brazil");
	gCountries[MEX] = TEXT("Mexico");
	gCountries[AUS] = TEXT("Australia");
	gCountries[KOR] = TEXT("South Korea");
	gCountries[NED] = TEXT("Netherlands");
	gCountries[BEL] = TEXT("Belgium");
	gCountries[SUI] = TEXT("Switzerland");
	gCountries[SWE] = TEXT("Sweden");
	gCountries[NOR] = TEXT("Norway");
	gCountries[FIN] = TEXT("Finland");
	gCountries[DEN] = TEXT("Denmark");
	gCountries[POR] = TEXT("Portugal");
	gCountries[GRE] = TEXT("Greece");
	gCountries[TUR] = TEXT("Turkey");
	gCountries[UKR] = TEXT("Ukraine");
	gCountries[RSA] = TEXT("South Africa");
	gCountries[ARG] = TEXT("Argentina");
	gCountries[NZL] = TEXT("New Zealand");
	gCountries[ISR] = TEXT("Israel");
	gCountries[SGP] = TEXT("Singapore");
	gCountries[IRL] = TEXT("Ireland");

	return TRUE;
}

BOOL CoInitializeApp(void)
{
	DatabasePtr db = DbCreate();

	if (CoFileExists(GLOBAL_DB_PATH) == FALSE)
	{
		DbInit(db);
		DbSave(db, GLOBAL_DB_PATH);
	}

	else
	{
		DbLoad(db, GLOBAL_DB_PATH);
	}

	GlobSetDbPtr(db);

	PConfig cfg = CreateConfig();
	if (CoFileExists(CFG_FILENAME) == FALSE)
	{
		ResetConfig(cfg);
		SaveConfig(cfg);
	}

	else
	{
		LoadConfig(cfg);
	}

	GlobSetConfigPtr(cfg);

	CoInitRandomness();

	// initialize countries
	CoInitCountries();

	return TRUE;
}

BOOL CoAppCleanup(void)
{
	PConfig config = GlobGetConfigPtr();
	DatabasePtr db = GlobGetDbPtr();

	if (config == NULL || db == NULL)
	{
		return FALSE;
	}

	DbSave(db, GLOBAL_DB_PATH);
	SaveConfig(config);

	return TRUE;
}

BOOL CoFileExists(LPCWSTR szPath)
{
	DWORD dwAttrib = GetFileAttributesW(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL CoSetDatabasePtr(PDatabase ptr)
{
	return GlobSetDbPtr(ptr);
}

BOOL CoDlgAbout(HWND hOwner)
{
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLGABOUT), hOwner, DlgAboutProc);
}

BOOL CoNotImplemented(HWND hParent)
{
	MessageBox(hParent, TEXT("This feature is not implemented at this moment."), TEXT("Not implemented"), MB_OK | MB_ICONSTOP);
	return TRUE;
}

BOOL CoDlgPlateGen(HWND hParent)
{
	return CoShowDialog(hParent, IDD_DLGPLATEGEN, DlgPlateGeneratorProc);
}

BOOL CoInitRandomness(void)
{
	srand(time(NULL));
	return TRUE;
}

BOOL CoDlgNewPerson(HWND hParent)
{
	return CoShowDialog(hParent, IDD_DLGNEWPERSON, DlgNewPersonProc);
}

int CoDisplayError(HWND hParent, UINT uID)
{
	WCHAR text[MAX_PATH];
	if (LoadString(GetModuleHandle(NULL), uID, text, MAX_PATH) == 0)
	{
		// resource not found
		return FALSE;
	}

	return MessageBox(hParent, text, TEXT("Error"), MB_OK | MB_ICONERROR);
}

int CoDisplayMessage(HWND hParent, UINT uMessageId, UINT uMsgParams)
{
	WCHAR text[MAX_PATH];
	if (LoadString(GetModuleHandle(NULL), uMessageId, text, MAX_PATH) == 0)
	{
		// resource not found
		return FALSE;
	}

	return MessageBox(hParent, text, TEXT("Message"), uMsgParams);
}