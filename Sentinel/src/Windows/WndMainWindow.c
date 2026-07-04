#include "..\..\inc\Windows\WndMainWindow.h"
#include "..\..\res\resource.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"
#include <windows.h>

#include "..\..\inc\Controls\CtlDbPersons.h"

BOOL CreateMainWindow(HINSTANCE hInst, WNDPROC lpfnWndProc)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInst;
	wc.lpfnWndProc = lpfnWndProc;
	wc.lpszClassName = SENTINEL_CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Failed to register window class."), TEXT("Error"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndMainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			// test
			HWND hCtl = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CTLPERSONS), hWnd, CtlDbPersonsProc);
			WhFitContent(hWnd, hCtl);
			ShowWindow(hCtl, SW_SHOW);
			return 0;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SHOWWINDOW:
		{
			if ((BOOL)wParam == TRUE)
			{
				WhCenterWindow(hWnd);
				return 0;
			}

			break;
		}

		case WM_HELP:
		{
			CoDlgAbout(hWnd);
			return 0;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDHELP:
				{
					SendMessage(hWnd, WM_HELP, 0, 0);
					return TRUE;
				}

				case IDCLOSE:
				{
					SendMessage(hWnd, WM_CLOSE, 0, 0);
					return TRUE;
				}

				case ID_HELP_WEBSITE:
				{
					ShellExecute(hWnd, TEXT("open"), LINK_GITHUB, NULL, NULL, SW_SHOWDEFAULT);
					return TRUE;
				}

				case ID_VEHICLES_LICENCEPLATEGENERATOR:
				{
					return CoDlgPlateGen(hWnd);
				}

				case ID_PLAYERS_NEWPLAYER:
				{
					return CoDlgNewPerson(hWnd);
				}

				case ID_WEAPONS_ADDNEWWEAPON:
				{
					return CoDlgNewWeapon(hWnd);
				}

				case ID_VEHICLES_NEWVEHICLE:
				{
					return CoDlgNewVehicle(hWnd);
				}

				case ID_CRIMES_ADDCRIME:
				{
					return CoNotImplemented(hWnd);
				}

				default: return FALSE;
			}
		}

		default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}