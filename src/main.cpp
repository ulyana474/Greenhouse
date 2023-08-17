#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define UTC_OFFSET_IN_SECONDS 3600         // offset from greenwich time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

const char* ssid = "InnoWarsaw";
const char* password = "Wise299!";

int hour;

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);

const int ledPin = 23;

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(10800);
  Serial.println("\nConnecting to WiFi Network ..");

  pinMode(ledPin, OUTPUT);
}

void loop() {
  timeClient.update();

  hour = timeClient.getHours();
  Serial.print(hour);

  delay(1000);
  
}

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Connected To The WiFi Network");

}

void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
