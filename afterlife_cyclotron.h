/*
 * Class to animate a WS2812B LED ring as seen in Ghostbusters: Afterlife
 * Written By: Cole Funseth
 */

#ifndef Cyclotron_h
#define Cyclotron_h

#include "Arduino.h"
#include "afterlife_cyclotron.h"
#include <Adafruit_NeoPixel.h>
#include <Ramp.h>

class Cyclotron {
  public:
    Cyclotron(unsigned int pin, unsigned int qty, unsigned int group, 
              unsigned int initSpeed, unsigned int finalSpeed, unsigned int bootSpeed);
    void start();
    void update();
    
  private:
    unsigned int _pin;
    unsigned int _qty;
    unsigned int _group;
    unsigned int _initSpeed;
    unsigned int _finalSpeed;
    unsigned int _bootSpeed;
    
    unsigned int _fadeInterval;
    unsigned int _delaySpeed;
    unsigned long _lastMillis;
    unsigned int _curPos;

    Adafruit_NeoPixel _pixels;
    ramp _motionRamp;
    ramp _lightRamp;
};

#endif
