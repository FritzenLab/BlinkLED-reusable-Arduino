#include <BlinkLED.h>
#define LED 14

int ledInterval = 500; // that means 500 miliseconds

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  blinkLED(LED, ledInterval);
}
