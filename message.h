#pragma once

#include <windows.h>
#include <cstdio>
#include "display.h"

#define WM_APP_RATE_UPDATE (WM_APP + 1)

class Hello;
class Window;
class Display;
extern Message* gMessage;
class Message {
    public:
        Message(Hello* hello, Window* window, Display* display);
        ~Message();
        static Message* instance();

        static void install(Message* instance);

        Window* getWindow() const;

        void handleRateMessage(const char* data);
        void handleDataMessage(const char* data);

        int set();
        void run();

    private:
        Hello* hello = nullptr;
        Window* window = nullptr;
        Display* display = nullptr;

        static Message* sInstance;

        void start();
};

extern "C" {
    Message* message = Message::instance();

    void __stdcall onDataMessage(const char* data);
    //void __stdcall setDataSink(HWND hwnd);
    //void __stdcall dataMessageSink(const char* data);
}