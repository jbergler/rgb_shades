#define PIN_AUDIO_INPUT A9
#define PIN_LED_OUTPUT A1

#define PIN_BRIGHT A18
#define PIN_SCALE  A19
#define PIN_RATE  A20

#define PIN_ONBOARD_LED 13
#define USE_FFT256

#include "led.h"
#include "input.h"
#include "audio.h"
#include "effect_spectrum.h"

// Stuff for blinking onboard LED
u_int led_blink_state = HIGH;
unsigned long led_blink_previous = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(25);
  Serial.println("I'm alive!!!");
  
  setup_audio();
  setup_leds();
  setup_input(); 

  e_spectrum_setup();  
  
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  digitalWrite(PIN_ONBOARD_LED, led_blink_state);
}

void loop() {
  loop_input();
  loop_leds();
  e_spectrum_loop();
  
  unsigned long led_blink_current = millis();  
  u_int led_blink_interval = (led_blink_state == HIGH) ? 20 : 5000;
  if ((led_blink_current - led_blink_previous) > led_blink_interval) {
    led_blink_previous = led_blink_current;
    led_blink_state = !led_blink_state;
    digitalWrite(PIN_ONBOARD_LED, led_blink_state);
  }
}
