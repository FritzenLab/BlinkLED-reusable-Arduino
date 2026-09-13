#include "BlinkLED.h"

#define MAX_BLINK_PINS 10 // bump this if you need to blink more LEDs at once

struct BlinkState {
  uint8_t pin;
  unsigned long timer;
  bool state;
  bool active;
};

// Array instead of std::map/std::vector: AVR-based boards (Uno/Nano) don't
// ship the STL containers, so a fixed-size array keeps this portable.
static BlinkState blinkStates[MAX_BLINK_PINS];

void blinkLED(uint8_t ledPin, unsigned long ledInterval) {
  BlinkState* s = nullptr;

  // Look for an existing entry for this pin, remembering the first
  // free slot in case we need to create one.
  for (uint8_t i = 0; i < MAX_BLINK_PINS; i++) {
    if (blinkStates[i].active && blinkStates[i].pin == ledPin) {
      s = &blinkStates[i];
      break;
    }
    if (!blinkStates[i].active && s == nullptr) {
      s = &blinkStates[i];
    }
  }

  if (s == nullptr) return; // all MAX_BLINK_PINS slots taken

  if (!s->active) {
    // First call for this pin: initialize its state
    s->pin = ledPin;
    s->timer = millis();
    s->state = false;
    s->active = true;
    // https://docs.arduino.cc/language-reference/en/functions/digital-io/pinMode/
    pinMode(ledPin, OUTPUT);
  }

  // https://docs.arduino.cc/language-reference/en/functions/time/millis/
  if (millis() - s->timer > ledInterval) {
    s->timer += ledInterval;
    s->state = !s->state;
    // https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalWrite/
    digitalWrite(s->pin, s->state);
  }
}