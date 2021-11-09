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
    Cyclotron(unsigned int pin, unsigned int qty, unsigned char group, unsigned char speed);
    void start();
    void update();
    
    void setSpeed(unsigned char value, unsigned int delay);
    void setBrightness(unsigned char value, unsigned int delay);
    
  private:
    unsigned int _pin;
    unsigned int _qty;
    unsigned char _group;
    unsigned char _speed;
    unsigned char _brightness;
    
    unsigned int _fadeInterval;
    unsigned int _delaySpeed;
    unsigned long _lastMillis;
    unsigned int _curPos;

    Adafruit_NeoPixel _pixels;
    ramp _motionRamp;
    ramp _lightRamp;
};

#endif
