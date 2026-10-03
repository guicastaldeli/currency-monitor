#pragma once

#include <windows.h>
#include <cstdio>
#include "display.h"

#define WM_APP_RATE_UPDATE (WM_APP + 1)

extern Message* gMessage;
class Message {
    public:
        Message(Hello* hello, Window* window, Display* display);
        ~Message();
        static Message* instance();

        Hello* hello = nullptr;
        Window* window = nullptr;
        Display* display = nullptr;

        static void install(Message* instance);

        Window* getWindow() const;

        void handleRateMessage(const char* data);
        void handleDataMessage(const char* data);

    private:
        static Message* sInstance;
};

extern "C" {
    Message* message = Message::instance();

    void __stdcall onDataMessage(const char* data);
    //void __stdcall setDataSink(HWND hwnd);
    //void __stdcall dataMessageSink(const char* data);
}