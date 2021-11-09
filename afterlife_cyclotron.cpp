/*
 * Class to animate a WS2812B LED ring as seen in Ghostbusters: Afterlife
 * Written By: Cole Funseth
 */
 
#include "Arduino.h"
#include "afterlife_cyclotron.h"
#include <Adafruit_NeoPixel.h>
#include <Ramp.h>

Cyclotron::Cyclotron(unsigned int pin, unsigned int qty, unsigned char group, unsigned char speed){
  _pin = pin;
  _qty = qty;
  _group = group;
  _speed = speed;

  _curPos = 0;
  _fadeInterval = 255 / _group;
}

void Cyclotron::start(void){
  _pixels.setPin(_pin);
  _pixels.updateLength(_qty);
  _pixels.updateType(NEO_GRB + NEO_KHZ800);
  
  _pixels.begin();
  _pixels.setBrightness(0);

  _delaySpeed = _speed;

  _motionRamp.go(_speed);
  _lightRamp.go(_brightness);
  //_lightRamp.go(255, _bootSpeed, CUBIC_INOUT, ONCEFORWARD);
}

void Cyclotron::update(){
  unsigned long _period = millis() - _lastMillis;
  
  if(_period >= _delaySpeed){
    _lastMillis = millis();

    //Clear everything and only set the pixels that should be set
    _pixels.clear();

    //This is written for running the pixel ring backwards (counter-clockwise)
    if(_curPos <= (_qty - _group)) {
      for(int _i=1; _i<=_group; _i++) {
        _pixels.setPixelColor(_qty - (_curPos + _i), _pixels.Color(_fadeInterval * _i, 0, 0));
      }
    }

    //Nearing the end of the loop...
    else if(_curPos > (_qty - _group) && _curPos < _qty){
      //Calculate how many pixels we need to turn on at beginning of loop
      unsigned int _remainder = _group - (_qty - _curPos);

      //Turn on pixels at end of loop
      for(int _i=1; _i<=(_group - _remainder); _i++) {
        _pixels.setPixelColor(_qty - (_curPos + _i), _pixels.Color(_fadeInterval * (_i + _remainder), 0, 0));
      }

      //Turn on pixels at the beginning of loop
      for(int _i=1; _i<=_remainder; _i++){
        _pixels.setPixelColor(_qty - _i, _pixels.Color(_fadeInterval * (_group - (_remainder - _i)), 0, 0));
      }       
    }

    //Back to the beginning...
    else{
      _curPos = 0;
      for(int _i=1; _i<=_group; _i++) {
        _pixels.setPixelColor(_qty - (_curPos + _i), _pixels.Color(_fadeInterval * _i, 0, 0));
      }
    }
    
    _pixels.show();

    _delaySpeed = _motionRamp.update();
    _pixels.setBrightness(_lightRamp.update());
    //_pixels.setBrightness(255);

    _curPos++;
  }
}

void Cyclotron::setSpeed(unsigned char value, unsigned int delay){
  if(value != _speed){
    _motionRamp.go(value, delay, CUBIC_OUT, ONCEFORWARD);
  }
  else {
    //Same speed as before, do nothing
  }

  _speed = value;
}

void Cyclotron::setBrightness(unsigned char value, unsigned int delay){  
  if(value != _brightness){
    _lightRamp.go(value, delay, CUBIC_INOUT, ONCEFORWARD);
  }
  else {
    //Same brightness as before, do nothing
  }

  _brightness = value;
}
