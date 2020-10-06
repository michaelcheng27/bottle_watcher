#pragma once
#include "wifi_manager.h"

struct ContextSettings
{
    const String ssid;
    const String password;
    ContextSettings(const String &ssid, const String &password) : ssid(ssid), password(password){};
    static ContextSettings *getDefault();
};

struct Context
{
    static Context *getContext();
    Context(const ContextSettings &settings);
    void setup();
    void executeLoop();

    //  data member:
    WifiManager wifiManager_;
};