#pragma once

#include <window.h>

class Display {
    public:
        /**
         * 
         * Tray
         * 
         */
        struct Tray {
            public:
                int WM_TRAYICON = (WM_APP + 100);
                int ID_TRAY_SHOW = 9001;
                int ID_TRAY_EXIT = 9002;
                
                bool install(HWND hwnd, HINSTANCE hInst, const wchar_t* tooltip);
                void remove();
            private:
                NOTIFYICONDATAW mNid = {};
                bool mInstalled = false;

                int uid = 1;
        };
};