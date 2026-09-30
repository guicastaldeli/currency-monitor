#include <display.h>

/**
 * 
 * Tray
 * 
 */
// Install
bool Display::Tray::install(HWND hwnd, HINSTANCE hInst, const wchar_t* tooltip) {
    if(mInstalled) return true;
    
    HICON icon = LoadIconW(hInst, L"IDI_APPICON");
    if(icon == nullptr) icon = LoadIconW(nullptr, IDI_APPLICATION);

    mNid.cbSize = sizeof(mNid);
    mNid.hWnd = hwnd;
    mNid.uID = uid;
    mNid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    mNid.uCallbackMessage = WM_TRAYICON;
    mNid.hIcon = icon;
    wcsncpy_s(mNid.szTip, tooltip, _TRUNCATE);

    if(!Shell_NotifyIconW(NIM_ADD, &mNid)) return false;
    mInstalled = true;
    return true;
}

// Remove
void Display::Tray::remove() {
    if(!mInstalled) return;
    Shell_NotifyIconW(NIM_DELETE, &mNid);
    mInstalled = false;
}