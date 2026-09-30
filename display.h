#pragma once

#include <window.h>
#include <string>
#include "StormTrack.hpp"

class Display {
    public:
        /**
         * 
         * Chart
         * 
         */
        struct Chart {
            public:
                int chartId = -1;

                const wchar_t* CHART_TITLE = L"chart"; 
                int CHART_WIDTH = 200;
                int CHART_HEIGHT = 200;

                float minX = 0.0;
                float maxX = 60.0f;

                void showChart();
                void createChart();
        };

        /**
         * 
         * Tray
         * 
         */
        struct Tray {
            public:
                #define WM_TRAYICON (WM_APP + 100)
                #define ID_TRAY_SHOW 9001
                #define ID_TRAY_EXIT 9002

                static Tray tray;
                
                bool install(HWND hwnd, HINSTANCE hInst, const wchar_t* tooltip);
                void remove();
                
                int setMenu(HWND hwnd, LPARAM lParam);
                int displayMenu(HWND hwnd, WPARAM);
                int removeMenu();
            private:
                Chart* chart = nullptr;

                NOTIFYICONDATAW mNid = {};
                bool mInstalled = false;

                int uid = 1;
        };
};