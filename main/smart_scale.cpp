#include "smart_scale.h"
#include "logger.h"
#include <SPI.h>
#include <math.h>

SmartScale::SmartScale(WifiManager &wifiManager, const char *serverAddress, const int port) : wifiManager_(wifiManager), httpClient_(wifi_, serverAddress, port), lcd_(12, 11, 2, 3, 4, 5)
{
    accumulatedCount_ = 0;
    delta_ = 2.0;
}

void SmartScale::prepare()
{
    scale_.prepare();
    lcd_.begin(16, 2);
}

void SmartScale::loop()
{
    const auto weight = scale_.read();
    Logger::info("weight = %f g", weight);
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
        digitalWrite(LED_PIN, state);
        delay(500);
    }
}

bool SmartScale::shouldUpdate_(const double weight)
{
    if (weight <= 75)
    {

        lcd_.noDisplay();
        lcd_.clear();
        if (isEqual_(previousValue_, weight))
        {
            lcd_.noDisplay();
            digitalWrite(LED_BACKLIGHT_PIN, LOW);
        }

        accumulatedCount_ = 0;
        previousValue_ = weight;
        digitalWrite(LED_PIN, LOW);
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
    lcd_.clear();
    char weightStr[16];
    snprintf(weightStr, 16, "milk: %.2f ml", weight - 105);
    lcd_.print(weightStr);
    lcd_.display();
    digitalWrite(LED_BACKLIGHT_PIN, HIGH);
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
    const auto len = snprintf(postData, 100, "{\r\n    \"weight\" : \"%.2f\"\r\n}", weight);
    Logger::info("post data write length = %ld", len);
    postData[len] = '\0';

    String postDataStr = String(postData);

    httpClient_.post("/dev/measurement", contentType, postDataStr);

    const auto statusCode = httpClient_.responseStatusCode();
    const auto response = httpClient_.responseBody();

    Logger::info("Status code: %d", statusCode);
    Serial.println(response);
}