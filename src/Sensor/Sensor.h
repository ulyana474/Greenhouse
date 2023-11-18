#ifndef SENSOR_H
#define SENSOR_H
#include "Adafruit_HTU21DF.h"
// #include <Wire.h>

class Sensor
{
public:
    Adafruit_HTU21DF sensor;
    double temp;
    double humid;

    Sensor();

    float outTemperature();
    float outHumidity();
    
    void begin(){
        sensor.begin(&Wire);
    }
};
#endif