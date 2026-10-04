#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "hello.h"
#include "data/.out/data.h"

static Hello gHello;

Hello::Hello() :
    window(),
    display(this, &window),
    message(this, &window, &display),
    stormTrack(window.WINDOW_TITLE)
{}
Hello::~Hello() {}

/**
 * 
 * Set
 * 
 */
void Hello::set(HINSTANCE hInstance) {
    window.setDisplay(&display);
    window.setMessage(&message);

    Message::install(&message);

    window.run(hInstance);
    display.run(hInstance);
    message.run();
}

/**
 * 
 * Run
 * 
 */
// Run
int Hello::Run(HINSTANCE hInstance) {
    gHello.set(hInstance);
    
    int val = gHello.message.set();
    return val;
}

// wWinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    int val = Hello::Run(hInstance);
    return val;
}