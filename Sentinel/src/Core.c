#include "..\inc\Core.h"
#include "..\inc\Dialogs\DlgAbout.h"
#include "..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\inc\Dialogs\DlgNewPerson.h"
#include "..\res\resource.h"

#include <stdlib.h>
#include <time.h>

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