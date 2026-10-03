#include <window.h>

Window::Window() {}
Window::~Window() {}

// Set Hwnd
void Window::setHwnd(HWND hwnd) {
    mHwnd = hwnd;
}

// Get Hwnd
HWND Window::getHwnd() const {
    HWND val = mHwnd;
    return val;
}

// Set Display
void Window::setDisplay(Display* display) {
    mDisplay = display;
}

// Get Display
Display* Window::getDisplay() const {
    Display* val = mDisplay;
    return val;
}

// Set Message
void Window::setMessage(Message* message) {
    mMessage = message;
}

// Get Messsage
Message* Window::getMessage() const {
    Message* val = mMessage;
    return val;
}

/**
 * 
 * Create Window
 * 
 */
void Window::createWindow(HINSTANCE hInstance) {
    HWND hwnd = CreateWindowExW(
        0, WINDOW_CLASS, WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        nullptr, nullptr,
        hInstance, this
    );
    if(hwnd == nullptr) {
        printf("CreateWindow failed!.");
    }

    setHwnd(hwnd);
}

/**
 * 
 * WndProc
 * 
 */
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Window* w = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    switch(msg) {
        case WM_NCCREATE: {
            auto* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
            return DefWindowProcW(hwnd, msg, wParam, lParam);
        }

        case WM_APP_RATE_UPDATE: {
            char* data = reinterpret_cast<char*>(lParam);
            if(data) {
                w->getMessage()->handleDataMessage(data);
                std::free(data);
            }
            
            return 0;
        }        
        case WM_TRAYICON: {
            if(LOWORD(lParam) == WM_RBUTTONUP && w && w->getDisplay()) {
                w->getDisplay()->set(lParam);
            }
        }
        case WM_COMMAND: {
            if(w && w->getDisplay()) {
                int val = w->getDisplay()->display(wParam);
                return val;
            }
        }
        case WM_DESTROY: {
            if(w && w->getDisplay()) w->getDisplay()->remove();
            StopMonitor();
            PostQuitMessage(0);
            return 0;
        }

        LRESULT CALLBACK val = DefWindowProcW(hwnd, msg, wParam, lParam);
        return val;
    }
}

/**
 * 
 * wWinMain
 * 
 */
int WINAPI Window::wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    WNDCLASSEX w = {};
    w.cbSize = sizeof(w);
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.lpszClassName = WINDOW_CLASS;
    w.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    RegisterClassExW(&w);

    // Window
    createWindow(hInstance);

    // Tray + chart
    getDisplay()->instances.tray.install(hInstance, WINDOW_TITLE);
    getDisplay()->instances.chart.createChart();
    
    RegisterCallback(&onDataMessage);

    RequestCurrencies();
    AddPair(const_cast<char*>("USD"), const_cast<char*>("BRL"));
    SetIntervalSeconds(10);
    StartMonitor();

    MSG msg;
    while(GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}