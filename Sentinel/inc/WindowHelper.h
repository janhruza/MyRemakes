#pragma once
#ifndef SENTINEL_WINDOWHELPER_H
#define SENTINEL_WINDOWHELPER_H

#include <wtypes.h>

/// <summary>
/// Adjusts the target window's size to fit the requested control.
/// </summary>
/// <param name="hParent">Handle to a parent window.</param>
/// <param name="hControl">Handle to the target child window (control).</param>
/// <returns>Operation result.</returns>
BOOL WhFitContent(HWND hParent, HWND hControl);

/// <summary>
/// Centers the target window to the center of the primary screen.
/// </summary>
/// <param name="hWnd">Handle to a window.</param>
/// <returns>Operation result.</returns>
BOOL WhCenterWindow(HWND hWnd);

/// <summary>
/// Centers a child window to the center of it's owner.
/// </summary>
/// <param name="hParent">Handle to the parent (owner) window.</param>
/// <param name="hChild">Handle to a child window.</param>
/// <returns>Operation result.</returns>
BOOL WhCenterChildWindow(HWND hParent, HWND hChild);

/// <summary>
/// Gets the owner of the specified window.
/// </summary>
/// <param name="hWnd">Handle to a window.</param>
/// <returns>Handle to the owner window.</returns>
HWND WhGetOwner(HWND hWnd);

/// <summary>
/// Assigns a bitmap image to a specified menu item.
/// </summary>
/// <param name="hMenu">Handle to a menu.</param>
/// <param name="uId">ID of the target menu item.</param>
/// <param name="hImage">Handle to a bitmap image.</param>
/// <returns>Operation result.</returns>
BOOL WhSetItemImage(HMENU hMenu, UINT uId, HBITMAP hImage);

/// <summary>
/// Loads a bitmap image from a resource and then assigns it to a menu item.
/// After the image is loaded, the WhSetItemImage method is called.
/// </summary>
/// <param name="hMenu">Handle to a menu.</param>
/// <param name="uId">ID of the target menu item.</param>
/// <param name="resourceId">Bitmap image resource name.</param>
/// <returns>Operation result.</returns>
BOOL WhSetItemImageResource(HMENU hMenu, UINT uId, UINT resourceId);

#endif