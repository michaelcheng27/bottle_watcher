#include "smart_scale.h"
#include "logger.h"
#include <SPI.h>
#include <math.h>

SmartScale::SmartScale(WifiManager &wifiManager, const char *serverAddress, const int port) : wifiManager_(wifiManager), httpClient_(wifi_, serverAddress, port)
{
    accumulatedCount_ = 0;
    delta_ = 2.0;
}

void SmartScale::prepare()
{
    scale_.prepare();
}

void SmartScale::loop()
{
    const auto weight = scale_.read();
    Logger::info("weight = %f", weight);
    if (shouldUpdate_(weight))
    {
        blink_();
        postUpdate_(weight);
    }
}

bool SmartScale::isEqual_(const double lhs, const double rhs)
{
    return abs(lhs - rhs) <= delta_;
}

void SmartScale::blink_()
{
    int state = LOW;
    for (int i = 0; i < 5; i++)
    {
        state = state == LOW ? HIGH : LOW;
        digitalWrite(10, state);
        delay(500);
    }
}

bool SmartScale::shouldUpdate_(const double weight)
{
    if (isEqual_(weight, 0))
    {
        accumulatedCount_ = 0;
        digitalWrite(10, LOW);
        return false;
    }
    if (isEqual_(weight, previousValue_))
    {
        ++accumulatedCount_;
    }
    else
    {
        previousValue_ = weight;
        accumulatedCount_ = 1;
    }
    if (accumulatedCount_ == 3)
    {
        return true;
    }
    return false;
}

void SmartScale::postUpdate_(const double weight)
{
    wifiManager_.connect();
    wifiManager_.printWiFiStatus();

    String contentType = "application/x-www-form-urlencoded";
    char postData[100];
    const auto len = snprintf(postData, 100, "{\r\n    \"weight\" : \"%f\"\r\n}", weight);
    Logger::info("post data write length = %ld", len);
    postData[len] = '\0';

    String postDataStr = String(postData);

    httpClient_.post("/dev/measurement", contentType, postDataStr);

    const auto statusCode = httpClient_.responseStatusCode();
    const auto response = httpClient_.responseBody();

    Logger::info("Status code: %d", statusCode);
    Serial.println(response);
}