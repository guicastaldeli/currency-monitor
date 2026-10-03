#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "hello.h"
#include "data.h"

Hello::Hello() :
    window(),
    display(this, &window),
    message(this, &window, &display),
    stormTrack(window.WINDOW_TITLE)
{}