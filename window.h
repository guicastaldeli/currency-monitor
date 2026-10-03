#pragma once

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "data.h"
#include "display.h"
#include "message.h"

class Window {
    public:
        Window();
        ~Window();
        
        const wchar_t* WINDOW_TITLE = L"Currency Monitor";
        const wchar_t* WINDOW_CLASS = L"Window";
        const int WINDOW_WIDTH = 200;
        const int WINDOW_HEIGHT = 400;

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        
        void setHwnd(HWND hwnd);
        HWND getHwnd() const;

        void setDisplay(Display* display);
        Display* getDisplay() const;

        void setMessage(Message* message);
        Message* getMessage() const;

    private:
        HWND mHwnd = nullptr;
        Display* mDisplay = nullptr;
        Message* mMessage = nullptr;

        void createWindow(HINSTANCE hInstance);

        int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int); 
};