#include "wifi_manager.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include "logger.h"

WifiManager::WifiManager(const String &ssid, const String &password) : ssid_(ssid), password_(password)
{
    status_ = WL_IDLE_STATUS;
}

void WifiManager::connect()
{
    if (WiFi.status() == WL_NO_MODULE)
    {

        Logger::info("Communication with WiFi module failed!");

        // don't continue

        while (true)
            ;
    }

    String fv = WiFi.firmwareVersion();

    if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    {

        Logger::info("Please upgrade the firmware");
    }
    // attempt to connect to WiFi network:
    while (status_ != WL_CONNECTED)
    {
        Logger::info("Attempting to connect to SSID: %s", ssid_.c_str());
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status_ = WiFi.begin(ssid_.c_str(), password_.c_str());
        Logger::info("status = %d", status_);
        Logger::info("[WifiManager::connect] wait 5 sec");
        delay(5 * 1000);
    }
    Logger::info("Wifi is connected");
}

void WifiManager::printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Logger::info("SSID: %s", WiFi.SSID());

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Logger::info("signal strength (RSSI): %ld dBm", rssi);
}
