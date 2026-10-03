#pragma once

#include <windows.h>
#include <cstdio>
#include "display.h"

#define WM_APP_RATE_UPDATE (WM_APP + 1)

class Message {
    public:
        Message();
        ~Message();
        
        static HWND hwnd;

        static void handleRateMessage(const char* data);
        static void handleDataMessage(const char* data);

    private:
        const HWND g_sink = nullptr;
};

extern "C" {
    void __stdcall onDataMessage(const char* data);
    void __stdcall setDataSink(HWND hwnd);
    void __stdcall dataMessageSink(const char* data);
}