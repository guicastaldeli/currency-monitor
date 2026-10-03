#pragma once

#include <StormTrack.hpp>
#include "window.h"
#include "message.h"
#include "display.h"

class Hello {
    public:
        Hello();
        ~Hello();

        Window window;
        Message message;
        Display display;

        StormTrack stormTrack;
};