#pragma once

#include <window.h>
#include <string>
#include <map>
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

                std::string CHART_TITLE = "chart"; 
                int CHART_WIDTH = 200;
                int CHART_HEIGHT = 200;

                float step = 1.0;
                float offset = 0.0;

                inline static const std::map<std::string, int> colors = {
                    { "r", 0 },
                    { "g", 200 },
                    { "b", 100 }
                };

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

        /**
         * 
         * Instances
         * 
         */
        struct Instances {
            Chart* chart;
            Tray* tray;
        };
        
        void set(HWND hwnd, LPARAM lParam);
        int display(HWND hwnd, WPARAM wParam);
        void remove();
    
    private:
        static Instances& instances;
};