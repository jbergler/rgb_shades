// LED Setup
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#define LED_PIN     PIN_LED_OUTPUT
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    68
#define BRIGHTNESS  50
#define DITHER      0
#define FRAMES_PER_SECOND 120

const uint8_t WIDTH  = 16;
const uint8_t HEIGHT = 5;

CRGB leds[NUM_LEDS+1];

#include "xy.h"

void setup_leds() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, (NUM_LEDS+1));
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither( DITHER );
  FastLED.show();
}

void loop_leds() {
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
}