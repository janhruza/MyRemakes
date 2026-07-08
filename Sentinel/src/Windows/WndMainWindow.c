#include "..\..\inc\Windows\WndMainWindow.h"
#include "..\..\res\resource.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"
#include "..\..\inc\Globals.h"
#include <windows.h>

typedef struct tagNavigation
{
	HWND hCtl;

} Navigation;

static Navigation nav = { 0 };

BOOL CreateMainWindow(HINSTANCE hInst, WNDPROC lpfnWndProc)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInst;
	wc.lpfnWndProc = lpfnWndProc;
	wc.lpszClassName = SENTINEL_CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APP_ICON));
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APP_ICON));*/
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Failed to register window class."), TEXT("Error"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

static void LoadMenuImages(HWND hWnd)
{
	HMENU hMenu = GetMenu(hWnd);
	/*HBITMAP imgAdd = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IMG_ADD), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);
	HBITMAP imgHelp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IMG_HELP), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);

	WhSetItemImage(hMenu, ID_PLAYERS_NEWPLAYER, imgAdd);
	WhSetItemImage(hMenu, ID_VEHICLES_NEWVEHICLE, imgAdd);
	WhSetItemImage(hMenu, ID_WEAPONS_ADDNEWWEAPON, imgAdd);
	WhSetItemImage(hMenu, ID_CRIMES_ADDCRIME, imgAdd);
	WhSetItemImage(hMenu, IDHELP, imgHelp);*/

	WhSetItemImageResource(hMenu, ID_PLAYERS_NEWPLAYER, IDB_IMG_ADD);
	WhSetItemImageResource(hMenu, ID_VEHICLES_NEWVEHICLE, IDB_IMG_ADD);
	WhSetItemImageResource(hMenu, ID_WEAPONS_ADDNEWWEAPON, IDB_IMG_ADD);
	WhSetItemImageResource(hMenu, ID_CRIMES_ADDCRIME, IDB_IMG_ADD);
	WhSetItemImageResource(hMenu, IDHELP, IDB_IMG_HELP);
	WhSetItemImageResource(hMenu, IDCLOSE, IDB_IMG_CLOSE);
	WhSetItemImageResource(hMenu, ID_DATABASE_INSIGHTS, IDB_IMG_INSIGHTS);
}

static UINT uMenuIds[] = { ID_PAGES_HOME, ID_PAGES_PERSONS, ID_PAGES_VEHICLES, ID_PAGES_WEAPONS, ID_PAGES_CRIMES };

inline static void UncheckAllNavItems(HWND hWnd)
{
	HMENU hMenu = GetMenu(hWnd);
	for (int i = 0; i < ARRAYSIZE(uMenuIds); i++)
	{
		CheckMenuItem(hMenu, uMenuIds[i], MF_BYCOMMAND | MF_UNCHECKED);
	}
}

static UINT GetCtlId(HWND hCtl)
{
	if (hCtl == gCtlLanding) return ID_PAGES_HOME;
	else if (hCtl == gCtlPersons) return ID_PAGES_PERSONS;
	else if (hCtl == gCtlVehicles) return ID_PAGES_VEHICLES;
	else if (hCtl == gCtlWeapons) return ID_PAGES_WEAPONS;
	else if (hCtl == gCtlCrimes) return ID_PAGES_CRIMES;
	else return -1;
}

static BOOL NavToCtl(HWND hWnd, HWND hCtl)
{
	if (hCtl == NULL) return FALSE;
	if (nav.hCtl != NULL)
	{
		ShowWindow(nav.hCtl, SW_HIDE);
	}

	WhFitContent(hWnd, hCtl);
	ShowWindow(hCtl, SW_SHOW);
	nav.hCtl = hCtl;

	// additionally update the check mark status
	UncheckAllNavItems(hWnd);
	UINT uId = GetCtlId(hCtl);
	if (uId != -1)
	{
		CheckMenuItem(GetMenu(hWnd), uId, MF_BYCOMMAND | MF_CHECKED);
	}

	return TRUE;
}

LRESULT CALLBACK WndMainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			// enhance the system menu
			HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
			AppendMenu(hSysMenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(hSysMenu, MF_STRING, IDHELP, TEXT("About\tF1"));

			// load all controls
			CoInitGlobControls(hWnd);

			// load menu item images
			LoadMenuImages(hWnd);

			// set the initial page
			NavToCtl(hWnd, gCtlLanding);

			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

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

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_F12:
				{
					// view db insights
					CoDlgInsights(hWnd);
					return 0;
				}

				default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}

		case WM_SYSCOMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDHELP:
				{
					SendMessage(hWnd, WM_HELP, 0, 0);
					return 0;
				}

				default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
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
					CoDlgNewVehicle(hWnd);
					return 0;
				}

				case ID_CRIMES_ADDCRIME:
				{
					CoNotImplemented(hWnd);
					return 0;
				}

				case ID_DATABASE_INSIGHTS:
				{
					CoDlgInsights(hWnd);
					return 0;
				}

				case ID_PAGES_HOME:
				{
					NavToCtl(hWnd, gCtlLanding);
					return 0;
				}

				case ID_PAGES_PERSONS:
				{
					NavToCtl(hWnd, gCtlPersons);
					return 0;
				}

				case ID_PAGES_VEHICLES:
				{
					NavToCtl(hWnd, gCtlVehicles);
					return 0;
				}

				case ID_PAGES_WEAPONS:
				{
					NavToCtl(hWnd, gCtlWeapons);
					return 0;
				}

				case ID_PAGES_CRIMES:
				{
					NavToCtl(hWnd, gCtlCrimes);
					return 0;
				}

				default: return FALSE;
			}
		}

		default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}