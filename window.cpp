#include <cstdio>
#include <cstdlib>
#include "window.h"
#include "display.h"
#include "message.h"
#include "data/.out/data.h"

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
 * Run
 * 
 */
void Window::run(HINSTANCE hInstance) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS;
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    RegisterClassExW(&wc);

    mHwnd = CreateWindowExW(
        0, WINDOW_CLASS, WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        nullptr, nullptr,
        hInstance, this
    );
    if(mHwnd == nullptr) {
        printf("CreateWindow failed!.");
    }

    setHwnd(mHwnd);
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

            return 0;
        }
        case WM_COMMAND: {
            if(w && w->getDisplay()) {
                int val = w->getDisplay()->display(wParam);
                return val;
            }

            return 0;
        }
        case WM_DESTROY: {
            if(w && w->getDisplay()) w->getDisplay()->remove();
            StopMonitor();
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}