#include <display.h>

// Set
void Display::set(HWND hwnd, LPARAM lParam) {
    instances.tray->setMenu(hwnd, lParam);
}

// Display
int Display::display(HWND hwnd, WPARAM wParam) {
    instances.tray->displayMenu(hwnd, wParam);
}

// Remove
void Display::remove() {
    instances.tray->removeMenu();
}

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

// Set Menu
int Display::Tray::setMenu(HWND hwnd, LPARAM lParam) {
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, ID_TRAY_SHOW, L"Show Chart");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, ID_TRAY_EXIT, L"Exit");

    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd);
    TrackPopupMenu(menu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, nullptr);

    DestroyMenu(menu);
    return 0;
}

// Display Menu
int Display::Tray::displayMenu(HWND hwnd, WPARAM wParam) {
    switch(LOWORD(wParam)) {
        case ID_TRAY_EXIT:
            DestroyWindow(hwnd);
            return 0;
        case ID_TRAY_SHOW:
            instances.chart->showChart();
            return 0;
    }

    return 0;
}

// Remove Menu
int Display::Tray::removeMenu() {
    instances.tray->remove();
}

/**
 * 
 * Chart
 * 
 */
// Show Chart
void Display::Chart::showChart() {
    StormTrack::Show();
}

// Create Chart
void Display::Chart::createChart() {
    if(chartId >= 0) return;
    
    for(const auto& [_, v] : colors) {
        StormTrack::AddTrace(CHART_TITLE, RGB(v, v, v), step, offset);
    }
}