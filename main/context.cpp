#include "context.h"
#include "arduino_secrets.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include "logger.h"
#include <ArduinoHttpClient.h>

ContextSettings *contextSettings = nullptr;
Context *context = nullptr;
char serverAddress[] = "uq48mkovcb.execute-api.us-west-2.amazonaws.com";
// IPAddress server(192, 168, 86, 35);

// static
ContextSettings *ContextSettings::getDefault()
{
    if (!contextSettings)
    {
        contextSettings = new ContextSettings(SSID, PASSWORD);
    }
    return contextSettings;
}

//  static
Context *Context::getContext()
{
    if (!context)
    {
        const auto settings = ContextSettings::getDefault();
        context = new Context(*settings);
    }
    return context;
}

Context::Context(const ContextSettings &settings) : wifiManager_(settings.ssid, settings.password)
{
    Logger::info("[Context::Context]:CreatedContext!");
}

void Context::setup()
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    Logger::info("[Context::setup]: Hello Board!");
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    scale_.prepare();
}

void Context::executeLoop()
{

    Logger::info("[executeLoop] Starts");
    const auto weight = scale_.read();
    Logger::info("weight = %f", weight);
    delay(2 * 1000);

    // wifiManager_.connect();
    // wifiManager_.printWiFiStatus();
    // const int port = 443;
    // WiFiSSLClient wifi;
    // HttpClient client = HttpClient(wifi, serverAddress, port);

    // String contentType = "application/x-www-form-urlencoded";
    // char postData[100];
    // const auto len = snprintf(postData, 100, "{\r\n    \"weight\" : \"%f\"\r\n}", weight);
    // Logger::info("post data write length = %ld", len);
    // postData[len] = '\0';

    // String postDataStr = String(postData);

    // client.post("/dev/measurement", contentType, postDataStr);

    // const auto statusCode = client.responseStatusCode();
    // const auto response = client.responseBody();

    // Logger::info("Status code: %d", statusCode);
    // Serial.print("Response: ");
    // Serial.println(response);
}
