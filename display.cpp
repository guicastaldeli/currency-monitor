#include <display.h>

Display::Display(Hello* hello, Window* window) : 
    hello(hello),
    window(window),
    instances(this) {}

Display::~Display() {}

// Set
void Display::set(LPARAM lParam) {
    instances.tray.setMenu(lParam);
}

// Display
int Display::display(WPARAM wParam) {
    instances.tray.displayMenu(wParam);
}

// Remove
void Display::remove() {
    instances.tray.removeMenu();
}

/**
 * 
 * Tray
 * 
 */
// Install
bool Display::Tray::install(HINSTANCE hInst, const wchar_t* tooltip) {
    if(mInstalled) return true;
    
    const wchar_t* appIcon = L"IDI_APPICON";
    HICON icon = LoadIconW(hInst, appIcon);
    if(icon == nullptr) icon = LoadIconW(nullptr, IDI_APPLICATION);

    mNid.cbSize = sizeof(mNid);
    mNid.hWnd = display->window->getHwnd();
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
int Display::Tray::setMenu(LPARAM lParam) {
    HWND hwnd = display->window->getHwnd();

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
int Display::Tray::displayMenu(WPARAM wParam) {
    HWND hwnd = display->window->getHwnd();

    switch(LOWORD(wParam)) {
        case ID_TRAY_EXIT:
            DestroyWindow(hwnd);
            return 0;
        case ID_TRAY_SHOW:
            display->instances.chart.showChart();
            return 0;
    }

    return 0;
}

// Remove Menu
void Display::Tray::removeMenu() {
    display->instances.tray.remove();
}

/**
 * 
 * Chart
 * 
 */
// Show Chart
void Display::Chart::showChart() {
    display->hello->stormTrack.Show();
}

// Create Chart
void Display::Chart::createChart() {
    if(chartId >= 0) return;
    
    for(const auto& [_, v] : colors) {
        display->hello->stormTrack.AddTrace(CHART_TITLE, RGB(v, v, v), step, offset);
    }
}