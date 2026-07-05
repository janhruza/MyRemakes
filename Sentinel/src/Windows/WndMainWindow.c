#include "..\..\inc\Windows\WndMainWindow.h"
#include "..\..\res\resource.h"
#include "..\..\inc\WindowHelper.h"
#include "..\..\inc\Core.h"
#include <windows.h>

#include "..\..\inc\Controls\CtlLanding.h"

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
	HBITMAP imgAdd = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IMG_ADD), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);
	HBITMAP imgHelp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_IMG_HELP), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);

	WhSetItemImage(hMenu, ID_PLAYERS_NEWPLAYER, imgAdd);
	WhSetItemImage(hMenu, ID_VEHICLES_NEWVEHICLE, imgAdd);
	WhSetItemImage(hMenu, ID_WEAPONS_ADDNEWWEAPON, imgAdd);
	WhSetItemImage(hMenu, ID_CRIMES_ADDCRIME, imgAdd);
	WhSetItemImage(hMenu, IDHELP, imgHelp);
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

			// load menu item images
			LoadMenuImages(hWnd);

			// test
			HWND hCtl = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CTLLANDING), hWnd, CtlLandingProc);
			WhFitContent(hWnd, hCtl);
			ShowWindow(hCtl, SW_SHOW);
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

				default: return FALSE;
			}
		}

		default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}