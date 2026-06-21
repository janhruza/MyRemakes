#include "..\inc\Core.h"
#include "..\inc\Dialogs\DlgAbout.h"
#include "..\inc\Dialogs\DlgPlateGenerator.h"
#include "..\res\resource.h"

BOOL CoDlgAbout(HWND hOwner)
{
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLGABOUT), hOwner, DlgAboutProc);
}

BOOL CoDlgPlateGen(HWND hParent)
{
	return CoShowDialog(hParent, IDD_DLGPLATEGEN, DlgPlateGeneratorProc);
}