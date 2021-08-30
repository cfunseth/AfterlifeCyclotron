/*
 * Example sketch for afterlife_cyclotron class
 * Written By: Cole Funseth
 */

#include "afterlife_cyclotron.h"

#define PIN 3           // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 40    // How many NeoPixels are attached to the Arduino?
#define GROUP 5         // How big of a group of Neopixels do you want to rotate?
#define INIT_SPD  100   // How slow do you want the animation to rotate at the beginning of the boot? (higher = slower, 255 max)
#define FINAL_SPD 5     // How fast do you want the animation to rotate at the end of the boot? (lower = faster, 0 min)
#define BOOT_SPD  5000  // How long do you want the boot animation to last?

// Create a new cyclotron object
Cyclotron cyclotron(PIN, NUMPIXELS, GROUP, INIT_SPD, FINAL_SPD, BOOT_SPD);

void setup() {
  //Initialize the cyclotron object
  cyclotron.start();
}

void loop() {
  //Update the cyclotron object (should be called as frequently as possible)
  cyclotron.update();
}
