#include "..\inc\TrayIcon.h"

#include <strsafe.h>
#include <shellapi.h>

void Tray_AddIcon(HWND hDlg)
{
    NOTIFYICONDATAW nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hDlg;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    StringCchCopy(nid.szTip, 128, TEXT("Warden - Session Active"));

    Shell_NotifyIconW(NIM_ADD, &nid);
}

void Tray_RemoveIcon(HWND hDlg)
{
    NOTIFYICONDATAW nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hDlg;
    nid.uID = 1;
    Shell_NotifyIconW(NIM_DELETE, &nid);
}