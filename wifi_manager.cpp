#include "wifi_manager.h"
#include <SPI.h>
#include <WiFiNINA.h>

WifiManager::WifiManager(const String &ssid, const String &password) : ssid_(ssid), password_(password_)
{
    status_ = WL_IDLE_STATUS;
}

void WifiManager::connect()
{
    // attempt to connect to WiFi network:
    while (status_ != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid_.c_str());
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status_ = WiFi.begin(ssid_.c_str(), password_.c_str());

        // wait 10 seconds for connection:
        delay(10 * 1000);
    }
    Serial.print("Wifi is connected");
}

void WifiManager::printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
