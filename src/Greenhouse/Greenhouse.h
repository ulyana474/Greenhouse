
#ifndef GREENHOUSE_H
#define GREENHOUSE_H

class Greenhouse
{
private:
    int pin;

public:
    bool watered;
    bool lightIsOn;
    bool fanIsOn;

    Greenhouse(int pin);

    void waterPlants();
    void swichFansOn();
    void swichFansOff();
    void switchLightsOn();
    void switchLightsOff();
};

#endif