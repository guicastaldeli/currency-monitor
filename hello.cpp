#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "hello.h"
#include "data.h"

Hello::Hello() :
    window(),
    message(),
    display(this, &window),
    stormTrack(window.WINDOW_TITLE)
{}