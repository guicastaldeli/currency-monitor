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
        
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        HWND getHwnd() const {};
    private:
        HWND mHwnd = nullptr;
        Display* display = nullptr;

        int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int); 
};