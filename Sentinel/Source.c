#include <Windows.h>
#include "inc/Core.h"
#include "res/resource.h"

#include "inc/Engine/Database.h"

#include "inc/Dialogs/DlgMainWindow.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
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

	

	CoInitRandomness();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGMAINWINDOW), NULL, DlgMainWindowProc);
	return EXIT_SUCCESS;
}