#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Greenhouse/Greenhouse.h"

#define UTC_OFFSET_IN_SECONDS 3600         // offset from greenwich time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

// const char* ssid = "InnoWarsaw";
// const char* password = "Wise299!";


// const char* ssid = "Ulyana's iPhone";
// const char* password = "eHsC-nN26-mvc2-w12v";

const char* ssid = "FoxFi79";
const char* password = "b255p24c32$$$";

int hour;

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);

int waterPin = 12;
int lightsPin = 13;
int fansPin = 14;

Greenhouse water(waterPin);
Greenhouse fans(fansPin);
Greenhouse lights(lightsPin);

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(10800);
  Serial.println("\nConnecting to WiFi Network ..");

  lights.switchLightsOn();
  fans.swichFansOn();
}

void loop() {
  timeClient.update();

  hour = timeClient.getHours();
  Serial.print(hour);

  if (hour == 00) {
      Serial.print("Water plants start");
      water.waterPlants();
      Serial.print("Water plants end");
  }
  
  if (hour > 23 && hour < 12) {
    Serial.print("Light off, fans off");
    lights.switchLightsOff();
    fans.swichFansOff();
  }

  delay(10000);
  
}

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Connected To The WiFi Network");

}

void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}