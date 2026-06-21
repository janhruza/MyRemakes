#include "..\inc\Core.h"
#include "..\inc\Dialogs\DlgAbout.h"
#include "..\res\resource.h"

BOOL CoDlgAbout(HWND hOwner)
{
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLGABOUT), hOwner, DlgAboutProc);
}