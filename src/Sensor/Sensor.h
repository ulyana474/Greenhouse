#ifndef SENSOR_H
#define SENSOR_H
#include <Adafruit_Si7021.h>
// #include <Wire.h>

class Sensor
{
public:
    Adafruit_Si7021 sensor;
    double temp;
    double humid;

    Sensor();

    float outTemperature();
    float outHumidity();
};
#endif