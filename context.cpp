#include "context.h"
#include "arduino_secrets.h"
#include <SPI.h>

ContextSettings *contextSettings = nullptr;
Context *context = nullptr;

// static
ContextSettings *ContextSettings::getDefault()
{
    if (contextSettings)
    {
        return contextSettings;
    }
    return new ContextSettings(SSID, PASSWORD);
}

//  static
Context *Context::getContext()
{
    if (context)
    {
        return context;
    }
    const auto settings = ContextSettings::getDefault();
    return new Context(*settings);
}

Context::Context(const ContextSettings &settings) : wifiManager_(settings.ssid, settings.password)
{
}

void Context::setup()
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    Serial.println("[setup]: Hello Board!");
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    wifiManager_.connect();
    wifiManager_.printWiFiStatus();
}

void Context::executeLoop()
{
    Serial.println("[executeLoop] Starts");
}
