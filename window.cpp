#include <window.h>

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_APP_RATE_UPDATE:
            char* data = reinterpret_cast<char*>(lParam);
            if(data) {
                Message::handleDataMessage(data);
                std::free(data);
            }
            
        return 0;     
    }
}