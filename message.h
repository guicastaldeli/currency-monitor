#pragma once

#include <windows.h>
#include <cstdio>
#include "display.h"

#define WM_APP_RATE_UPDATE (WM_APP + 1)

class Message {
    public:
        Message(Hello* hello, Window* window, Display* display);
        ~Message();

        void handleRateMessage(const char* data);
        void handleDataMessage(const char* data);
        
        Hello* hello = nullptr;
        Window* window = nullptr;
        Display* display = nullptr;
};

extern "C" {
    static Message* message;

    void __stdcall onDataMessage(const char* data);
    void __stdcall setDataSink(HWND hwnd);
    void __stdcall dataMessageSink(const char* data);
}