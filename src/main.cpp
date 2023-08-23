#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Greenhouse/Greenhouse.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UTC_OFFSET_IN_SECONDS 3600         // offset from greenwich time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

bool TimeDifferenceIs24(const String& date1, const String& date2);

const char* ssid = "InnoWarsaw";
const char* password = "Wise299!";

int hour;
int mins;
int sec;
String lastTimeWatered = "";

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);

int waterPin = 32;
int lightsPin = 12;
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

}

void loop() {

  timeClient.update();

  hour = timeClient.getHours();
  mins = timeClient.getMinutes();
  sec = timeClient.getSeconds();
  Serial.print(hour);

  if (hour == 00) {

    if (TimeDifferenceIs24(lastTimeWatered, String(hour) + ":" + String(mins) + ":" + String(sec))) {
        Serial.print("More than 24 hours has gone, time to water plants. ");
        water.waterPlants();
        lastTimeWatered = String(hour) + ":" + String(mins) + ":" + String(sec);
        Serial.print('Last time watered' + " " + lastTimeWatered);
    }

  }
  
  if (hour > 23 && hour < 12) {

    lights.switchLightsOff();
    fans.swichFansOff();

  }
  else {

    lights.switchLightsOn();
    fans.swichFansOn();

  }

  delay(10000);
  
}

bool TimeDifferenceIs24(const String &startTime, const String &endTime) {

  int startSec = (startTime.substring(0, 2).toInt() * 3600) +
                 (startTime.substring(3, 5).toInt() * 60) +
                 startTime.substring(6, 8).toInt();

  int endSec = (endTime.substring(0, 2).toInt() * 3600) +
               (endTime.substring(3, 5).toInt() * 60) +
               endTime.substring(6, 8).toInt();

  int timeDiff = endSec - startSec;

  return timeDiff >= 86400;
}

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info){

  Serial.println("Connected To The WiFi Network");

}

void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {

  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  
}