#include "Greenhouse.h"
#include <Arduino.h>

Greenhouse::Greenhouse(int pin)
                      : watered(false)
                      , lightIsOn(false)
                      , fanIsOn(false) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Greenhouse::waterPlants() {
  if (watered)
  {
    return;
  }
  
  digitalWrite(pin, HIGH);
  delay(9000); 
  digitalWrite(pin, LOW);
  watered = true;
}

void Greenhouse::swichFansOn() {
  if (fanIsOn) {
    return;
  }
  Serial.print("Fan is on");
  digitalWrite(pin, HIGH);
  fanIsOn = true;
}

void Greenhouse::swichFansOff() {
  if (!fanIsOn) {
    return;
  }
  Serial.print("Fan is off");
  digitalWrite(pin, LOW);
  fanIsOn = false;
}

void Greenhouse::switchLightsOn() {
  digitalWrite(pin, HIGH);
  lightIsOn = true;
}

void Greenhouse::switchLightsOff() {
  digitalWrite(pin, HIGH);
}
