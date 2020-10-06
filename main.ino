/*
  This example creates a client object that connects and transfers
  data using always SSL.

  It is compatible with the methods normally related to plain
  connections, like client.connect(host, port).

  Written by Arturo Guadalupi
  last revision November 2015

*/

#include <SPI.h>
#include <WiFiNINA.h>
#include "context.h"

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.google.com"; // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiSSLClient client;

void setup()
{
  const auto context = Context::getContext();
  if (!context)
  {
    Serial.print("Failed to create Context, abort!");
    return;
  }
  context->setup();
  Serial.print("Setup Completes!");

  // Serial.println("\nStarting connection to server...");
  // // if you get a connection, report back via serial:
  // if (client.connect(server, 443))
  // {
  //   Serial.println("connected to server");
  //   // Make a HTTP request:
  //   client.println("GET /search?q=arduino HTTP/1.1");
  //   client.println("Host: www.google.com");
  //   client.println("Connection: close");
  //   client.println();
  // }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected())
  {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true)
      ;
  }
}

void printWiFiStatus()
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
