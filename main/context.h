#pragma once
#include "wifi_manager.h"
#include "scale.h"

struct ContextSettings
{
    const String ssid;
    const String password;
    ContextSettings(const String &id, const String &pw) : ssid(id), password(pw){};
    static ContextSettings *getDefault();
};

struct Context
{
    static Context *getContext();
    Context(const ContextSettings &settings);
    void setup();
    void executeLoop();
    void setupWeighter();

    //  data member:
    WifiManager wifiManager_;
    Scale scale_;
};
