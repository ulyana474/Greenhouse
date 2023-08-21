#include "Switcher.h"
#include <Arduino.h>

Switcher::Switcher(int pin)
                          : On(false)
{  
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Switcher::swichOn() {
  if (On) {
    return;
  }
  Serial.print("Is on");
  digitalWrite(pin, HIGH);
  On = true;
}

void Switcher::swichOff() {
  if (!On) {
    return;
  }
  Serial.print("Is off");
  digitalWrite(pin, LOW);
  On = false;
}
