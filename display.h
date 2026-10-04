#pragma once

#include <window.h>
#include <string>
#include <map>
#include "StormTrack.hpp"

class Hello;
class Window;
class Display {
    public:
        /**
         * 
         * Chart
         * 
         */
        struct Chart {
            public:
                explicit Chart(Display* d) : display(d) {}
                
                Display* display;
                
                int chartId = -1;

                std::wstring CHART_TITLE = L"chart"; 
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
                
                explicit Tray(Display* d) : display(d) {}
            
                Display* display;

                bool install(HINSTANCE hInst, const wchar_t* tooltip);
                void remove();
                
                int setMenu(LPARAM lParam);
                int displayMenu(WPARAM);
                void removeMenu();

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
            Chart chart;
            Tray tray;

            explicit Instances(Display* d) : 
                chart(d),
                tray(d) {}
        };
        
        Display(Hello* hello, Window* window);
        ~Display();
        
        Instances instances;

        void set(LPARAM lParam);
        int display(WPARAM wParam);

        void run(HINSTANCE hInstance);
        void remove();
    
    private:
        Hello* hello = nullptr;
        Window* window = nullptr;
};