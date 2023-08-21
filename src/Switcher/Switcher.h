
#ifndef GREENHOUSE_H
#define GREENHOUSE_H

class Switcher
{
private:
    int pin;

public:
    bool On;
    bool Off;

    Switcher(int pin);

    void swichOn();
    void swichOff();
};

#endif