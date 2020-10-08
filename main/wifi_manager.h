#pragma once
#include "Arduino.h"

class WifiManager
{
public:
    WifiManager(const String &ssid, const String &password);
    void connect();
    void printWiFiStatus();

private:
    const String &ssid_;
    const String &password_;
    int status_;
};