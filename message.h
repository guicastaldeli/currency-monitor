#pragma once

#define WM_APP_RATE_UPDATE (WM_APP + 1)

class Message {
    public:
        static void handleRateMessage(const char* data);
        static void handleDataMessage(const char* data);
};