#pragma once

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "message.h"

class Window {
    public:
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        
    private:
        int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int); 
};