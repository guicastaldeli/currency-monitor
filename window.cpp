#include <window.h>

Window::Window() :
    stormTrack(WINDOW_TITLE) {}

 Window::~Window() {}

// Get Hwnd
HWND Window::getHwnd() const {
    HWND val = mHwnd;
    return val;
}

// Wnd Proc
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_APP_RATE_UPDATE: {
            char* data = reinterpret_cast<char*>(lParam);
            if(data) {
                Message::handleDataMessage(data);
                std::free(data);
            }
            
            return 0;
        }        
        case WM_TRAYICON: {
            switch(LOWORD(lParam)) {
                case WM_RBUTTONUP:
                    display.set(hwnd, lParam);
                    return 0;
            }

            return 0;
        }
        case WM_COMMAND: {
            int val = display.display(hwnd, wParam);
            return val;
        }
        case WM_DESTROY: {
            display.remove();
            StopMonitor();
            PostQuitMessage(0);
            return 0;
        }

        LRESULT CALLBACK val = DefWindowProcW(hwnd, msg, wParam, lParam);
        return val;
    }
}