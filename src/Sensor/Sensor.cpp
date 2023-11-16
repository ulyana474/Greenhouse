#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor()
{
    Serial.print("Sensor is initialized!");
};

float Sensor::outTemperature()
{
    temp = sensor.readTemperature();

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    return temp;
};

float Sensor::outHumidity()
{
    humid = sensor.readHumidity();

    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.println("%");

    return humid;
};

