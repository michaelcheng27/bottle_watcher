#pragma once
#include "scale.h"
#include "wifi_manager.h"
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

class SmartScale
{
public:
    SmartScale(WifiManager &wifiManager, const char *serverAddress, const int port);
    void loop();
    void prepare();

private:
    void postUpdate_(const double weight);
    bool shouldUpdate_(const double weight);
    bool isEqual_(const double lhs, const double rhs);

    void blink_();

    double previousValue_;
    int accumulatedCount_;
    double delta_;

    Scale scale_;
    WifiManager &wifiManager_;
    WiFiSSLClient wifi_;
    HttpClient httpClient_;
};