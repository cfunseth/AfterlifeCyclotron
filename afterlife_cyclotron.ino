/*
 * Example sketch for afterlife_cyclotron class
 * Written By: Cole Funseth
 */

#include "afterlife_cyclotron.h"

#define PIN 3           // Which pin on the Arduino is connected to the NeoPixels?
#define HEAT_PIN  9     // Which pin on the Arduino is connected to the "overheat" signal?
#define NUMPIXELS 40    // How many NeoPixels are attached to the Arduino?
#define GROUP 2         // How big of a group of pixels do you want to rotate?
#define INIT_SPD  255   // How slow do you want the animation to rotate at the beginning of the boot? (higher = slower, 255 max)
#define IDLE_SPD  10    // How fast do you want the animation to rotate during "normal" operation (lower = faster, 0 min)
#define HEAT_SPD 5      // How fast do you want the animation to rotate at overheat? (lower = faster, 0 min)
#define BOOT_DLY  5000  // How long do you want the boot animation to last?
#define HEAT_DLY  5000  // How long should the "overheat" ramp up last?

// Create a new cyclotron object
Cyclotron cyclotron(PIN, NUMPIXELS, GROUP, INIT_SPD);

void setup() {
  //Setup and start the cyclotron
  cyclotron.setBrightness(0, 0);
  cyclotron.start();
  cyclotron.setSpeed(IDLE_SPD, BOOT_DLY);
  cyclotron.setBrightness(255, BOOT_DLY);

  //Set "overheat" signal pin as an input
  pinMode(HEAT_PIN, INPUT_PULLUP);
}

void loop() {
  //Update the cyclotron (should be called as frequently as possible)
  cyclotron.update();

  //Check if overheat input is low (normal) or high (overheating)
  if(!digitalRead(9)) cyclotron.setSpeed(IDLE_SPD, BOOT_DLY);
  else cyclotron.setSpeed(HEAT_SPD, HEAT_DLY);
}
