#include "..\..\inc\Controls\CtlDbPersons.h"
#include "..\..\res\resource.h"
#include "..\..\inc\Core.h"

#include <Windows.h>

static HBRUSH hBr;

BOOL CtlDbPersonsProc(HWND hCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_GETDLGCODE:
		{
			return DLGC_WANTALLKEYS;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDRETRY:
				{
					// the 'Refresh' button
					return CoNotImplemented(hCtl);
				}

				default: return FALSE;
			}
		}

		default:
			break;
	}

	return FALSE;
}