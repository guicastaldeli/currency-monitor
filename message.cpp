#include <message.h>

Message::Message() {
    hwnd = nullptr;
}

Message::~Message() {}

// Handle Rate Message
void Message::handleRateMessage(const char* data) {
    const char* key = "\"rate\":";
    const char* pos = strstr(data, key);
    if(!pos) return;
    pos += strlen(key);

    double rate = atof(pos);
    if(rate <= 0.0) return;

    Display::Chart* c = Display::Instances::chart;
    if(c != nullptr && c->chartId >= 0) {
        StormTrack::RealtimeView(rate, c->chartId);
    }

    printf("[rate] %.4%\n", rate);
    fflush(stdout);
}

// Handle Data Message
void Message::handleDataMessage(const char* data) {
    if(strstr(data, "\"type\":\"rate\"")) {
        handleRateMessage(data);
    } else if(strstr(data, "\"type\":\"currencies\"")) {
        printf("[currencies] %s\n", data);
        fflush(stdout);
        // TODO: parse and populate dropdowns once UI is added...
    } else if(strstr(data, "\"type\":\"error\"")) {
        printf("ERROR: %s\n", data);
        fflush(stdout);
    } else {
        printf("UNKNOWN: %s\n", data);
        fflush(stdout);
    }
}

// On Data Message
extern "C" void __stdcall onDataMessage(const char* data) {
    if(data == nullptr) return;

    size_t len = strlen(data);
    char* copy = static_cast<char*>(malloc(len + 1));
    if(!copy) return;
    memcpy(copy, data, len + 1);

    if(!PostMessage(Message::hwnd, WM_APP_RATE_UPDATE, 0, reinterpret_cast<LPARAM>(copy))) {
        free(copy);
    }
}

// Set Data Sink
extern "C" void __stdcall setDataSink(HWND hwnd) {
    Message::hwnd = hwnd;
}

//