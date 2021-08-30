/*
 * Class to animate a WS2812B LED ring as seen in Ghostbusters: Afterlife
 * Written By: Cole Funseth
 */
 
#include "Arduino.h"
#include "afterlife_cyclotron.h"
#include <Adafruit_NeoPixel.h>
#include <Ramp.h>

Cyclotron::Cyclotron(unsigned int pin, unsigned int qty, unsigned int group, unsigned int initSpeed, unsigned int finalSpeed, unsigned int bootSpeed){
  _pin = pin;
  _qty = qty;
  _group = group;
  _initSpeed = initSpeed;
  _finalSpeed = finalSpeed;
  _bootSpeed = bootSpeed;

  _curPos = 0;
  _fadeInterval = 255 / _group;
}

void Cyclotron::start(void){
  _pixels.setPin(_pin);
  _pixels.updateLength(_qty);
  _pixels.updateType(NEO_GRB + NEO_KHZ800);
  
  _pixels.begin();
  _pixels.setBrightness(0);

  _delaySpeed = _initSpeed;

  _motionRamp.go(_initSpeed);
  _motionRamp.go(_finalSpeed, _bootSpeed, CUBIC_OUT, ONCEFORWARD);
  _lightRamp.go(255, _bootSpeed, CUBIC_INOUT, ONCEFORWARD);
}

void Cyclotron::update(){
  unsigned long _period = millis() - _lastMillis;
  
  if(_period >= _delaySpeed){
    _lastMillis = millis();

    if(_curPos >= _qty) _curPos = 0;
          
    _pixels.clear();

    for(int _i=1; _i<=_group; _i++){
      _pixels.setPixelColor(_qty - (_curPos + _i), _pixels.Color(_fadeInterval * _i, 0, 0));
    }

    if(_curPos > (_qty - _group)){
      //Calculate how many Neopixels we need to turn on back at the beginning of the loop
      unsigned int _remainder = _group - (_qty - _curPos);

      //Turn on the necessary Neopixels at the beginning of the ring to keep the pattern moving
      for(int _j=0; _j<_remainder; _j++){
        _pixels.setPixelColor(_qty - _j, _pixels.Color(255 - (_fadeInterval * _j), 0, 0));
      }       
    }
    
    _pixels.show();

    _delaySpeed = _motionRamp.update();
    _pixels.setBrightness(_lightRamp.update());

    _curPos++;
  }
}
