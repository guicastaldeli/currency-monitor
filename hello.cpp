#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "hello.h"
#include "data/.out/data.h"

Hello::Hello() :
    window(),
    display(this, &window),
    message(this, &window, &display),
    stormTrack(window.WINDOW_TITLE)
{}