# BlinkLED

A tiny non-blocking library to blink one or more LEDs on Arduino-compatible
boards without using `delay()`.

## Why

The classic blink-without-delay pattern needs a timer and a state variable
per LED. This library manages those internally (up to `MAX_BLINK_PINS`
LEDs at once), so you can call one function per loop and forget about it.

## Usage

```cpp
#include <BlinkLED.h>

void setup() {}

void loop() {
  blinkLED(13, 500);  // blink pin 13 every 500 ms
  blinkLED(12, 200);  // independently blink pin 12 every 200 ms
}
```

## API

```cpp
void blinkLED(uint8_t ledPin, unsigned long ledInterval);
```
- `ledPin` — pin number (or board-specific macro, e.g. `D10`, `LED_BUILTIN`)
- `ledInterval` — half-period in milliseconds (time the LED stays on/off)

## Notes

- Supports up to 10 simultaneous LEDs by default. Change `MAX_BLINK_PINS`
  in `BlinkLED.cpp` if you need more.
- `pinMode(OUTPUT)` is set automatically on first use of a pin.

## License

MIT — see [LICENSE](LICENSE).