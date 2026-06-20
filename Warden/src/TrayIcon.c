#include "..\inc\TrayIcon.h"

#include <strsafe.h>
#include <shellapi.h>

void Tray_AddIcon(HWND hDlg)
{
    NOTIFYICONDATAW nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hDlg;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    StringCchCopyW(nid.szTip, 128, L"Warden - Session Active");

    // notify icon
    StringCchCopyW(nid.szInfo, 256, L"Warden is active and monitoring your workspace. Click this icon to end your session.");
    StringCchCopyW(nid.szInfoTitle, 64, L"Session Started");
    nid.dwInfoFlags = NIIF_INFO;

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