#include "Greenhouse.h"
#include <Arduino.h>

Greenhouse::Greenhouse(int pin) {

    this->pin = pin;
    pinMode(pin, OUTPUT);

}

void Greenhouse::waterPlants() {

  if (watered)
  {
    return;
  }
  Serial.print("Started watering");
  digitalWrite(pin, HIGH);
  delay(10000); // 10 sec
  digitalWrite(pin, LOW);
  Serial.print("Finished watering");
  watered = true;

}

void Greenhouse::swichFansOn() {

  Serial.print("Fan is on ");
  digitalWrite(pin, HIGH);
  fanIsOn = true;

}

void Greenhouse::swichFansOff() {

  Serial.print("Fan is off ");
  digitalWrite(pin, LOW);
  fanIsOn = false;

}

void Greenhouse::switchLightsOn() {

  Serial.print("Light is on ");
  digitalWrite(pin, HIGH);
  lightIsOn = true;

}

void Greenhouse::switchLightsOff() {
  Serial.print("Light is off ");
  digitalWrite(pin, LOW);

}