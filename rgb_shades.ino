#define PIN_AUDIO_INPUT A9
#define PIN_LED_OUTPUT A8
#define PIN_ONBOARD_LED 13
#define USE_FFT256

// Libraries for Arudino IDE to figure itself out
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <Adafruit_BLE_UART.h>

// Stuff for this project.
#include "audio.h"
#include "led.h"
#include "effect_spectrum.h"
#include "commands.h"
#include "ble.h"
#include "serial.h"

// Stuff for blinking onboard LED
int led_blink_state = HIGH;
int led_blink_interval = 500;
unsigned long led_blink_previous = 0;

void setup() {
  delay(333);

  setup_audio();

  setup_leds();
  setup_serial();
  setup_ble();

  e_spectrum_setup();
  
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  digitalWrite(PIN_ONBOARD_LED, led_blink_state);
}

void loop() {
  loop_leds();
  loop_serial();
  loop_ble();

  e_spectrum_loop();
  
  unsigned long led_blink_current = millis();  
  if(led_blink_current - led_blink_previous > led_blink_interval) {
    led_blink_previous = led_blink_current;
    led_blink_state = !led_blink_state;
    digitalWrite(PIN_ONBOARD_LED, led_blink_state);
  }
}