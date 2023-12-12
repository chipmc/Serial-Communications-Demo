#include "Serial1_Listener.h"

char buffer[256];   // Where we will hold the serial data

Serial1_Listener *Serial1_Listener::_instance;

// [static]
Serial1_Listener &Serial1_Listener::instance() {
    if (!_instance) {
        _instance = new Serial1_Listener();
    }
    return *_instance;
}

Serial1_Listener::Serial1_Listener() {
}

Serial1_Listener::~Serial1_Listener() {
}

void Serial1_Listener::setup() {
    Serial1.begin(115200);

    Log.info("Starting up the Serial1_Listener");

}

void Serial1_Listener::loop() {
    // Put your code to run during the application thread loop here
    while(Serial1.available()) {
        int numBytes = Serial1.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
        if (numBytes > 0) {
            buffer[numBytes] = 0;
            Log.info("Received %d bytes: %s", numBytes, buffer);
        }
    }
}

