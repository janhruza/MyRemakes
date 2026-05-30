#include <Windows.h>
#include "res/resource.h"
#include "inc/rplogic.h"

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

LRESULT CALLBACK EditBoxProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
		case WM_GETDLGCODE:
			return DLGC_WANTALLKEYS;

		case WM_KEYDOWN:
		{
			if (wParam == VK_RETURN)
			{
				// add new item to the picking pool
				WCHAR text[MAX_PATH];
				if (GetWindowText(hwnd, text, MAX_PATH) <= 0)
				{
					MessageBeep(MB_ICONERROR);
					return FALSE;
				}

				if (RpAddPickerOption(hwnd, GetDlgItem(GetParent(hwnd), IDC_LBX_OPTIONS), text) == FALSE)
				{
					MessageBox(hwnd, TEXT("Unable to add this item."), TEXT("ERROR"), MB_OK | MB_ICONERROR);
					return FALSE;
				}

				HWND hParent = GetParent(hwnd);
				BOOL isEnabled = SendMessage(GetDlgItem(hParent, IDC_LBX_OPTIONS), LB_GETCOUNT, 0, 0) > 0;
				EnableWindow(GetDlgItem(hParent, IDC_BTN_REMOVE), isEnabled);

				return TRUE;
			}

			else if (wParam == VK_F1)
			{
				MessageBox(hwnd, TEXT("Press ENTER to add your item into the options pool."), TEXT("Help"), MB_OK | MB_ICONINFORMATION);
				return TRUE;
			}

			break;
		}

		case WM_NCDESTROY:
		{
			RemoveWindowSubclass(hwnd, EditBoxProc, uIdSubclass);
			break;
		}
	}

	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			HWND hEdit = GetDlgItem(hDlg, IDC_TXT_NEW);
			SetWindowSubclass(hEdit, EditBoxProc, 1, 0);
			return TRUE;
		}

		case WM_CLOSE:
			EndDialog(hDlg, IDCLOSE);
			return TRUE;

		case WM_SYSCOMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case SC_CLOSE:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;
			}

			return FALSE;
		}

		case WM_VKEYTOITEM: {
			int nKey = LOWORD(wParam);
			int nIdx = HIWORD(wParam);
			HWND hLbx = (HWND)lParam;
			if (GetDlgCtrlID(hLbx) == IDC_LBX_OPTIONS)
			{
				if (nKey == VK_DELETE)
				{
					if (nIdx != LB_ERR)
					{
						SendMessage(hLbx, LB_DELETESTRING, nIdx, 0);
					}

					SetWindowLongPtr(hDlg, DWLP_MSGRESULT, -2);
					return TRUE;
				}
			}

			SetWindowLongPtr(hDlg, DWLP_MSGRESULT, -1);
			return TRUE;
		}

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				// the 'Cancel' button
				case IDCANCEL:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return TRUE;

				// the 'Pick' button
				case IDOK:
					return RpPickOption(GetDlgItem(hDlg, IDC_LBX_OPTIONS));

				// the 'remove selected' button
				case IDC_BTN_REMOVE:
					return TRUE;

				default:
					return FALSE;
			}
		}

		default: return FALSE;
	}
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DialogProc);
	return 0;
}