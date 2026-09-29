package main

/*
#include <stdlib.h>

// Callback signature: C++ provides
// a function pointer with this signature
typedef void (*message_callback_t)(const char* json_data);

// Helper to invoke a C function pointer.
static void invoke_callback(message_callback_t cb, const char* data) {
	if(cb != NULL && data != NULL) {
		cb(data);
	}
}
*/
import "C"
import (
	"encoding/json"
	"net/http"
	"sync"
	"time"
	"unsafe"
)

var (
	messageCb  C.message_callback_t
	mu         sync.Mutex
	stopCh     chan struct{}
	running    bool
	httpClient = &http.Client{Timeout: 10 * time.Second}
)

const API_URL = "http://api.frankfurter.dev/v1"

//export RegisterCallback
func RegisterCallback(cb C.message_callback_t) {
	messageCb = cb
}

// Emit
func Emit(payload map[string]interface{}) {
	if messageCb == nil {
		return
	}

	b, _ := json.Marshal(payload)
	cStr := C.CString(string(b))
	C.invoke_callback(messageCb, cStr)
	C.free(unsafe.Pointer(cStr))
}

// Emit Error
func EmitError(msg string) {
	Emit(map[string]interface{}{
		"type":    "error",
		"message": msg,
	})
}

/// -------------------------------------
/// External exports...
/// -------------------------------------

//export SetIntervalSeconds
func SetIntervalSeconds(sec C.int) {
	setIntervalSeconds(int(sec))
}

//export RequestCurrencies
func RequestCurrencies() {
	requestCurrencies()
}

//export StartMonitor
func StartMonitor() {
	startMonitor()
}

//export StopMonitor
func StopMonitor() {
	stopMonitor()
}

//export AddPair
func AddPair(from *C.char, to *C.char) {
	addPair(C.GoString(from), C.GoString(to))
}

//export ClearPairs
func ClearPairs() {
	clearPairs()
}

/// -------------------------------------
/// -------------------------------------

// Main
func main() {}
