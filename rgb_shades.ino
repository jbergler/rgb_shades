#define PIN_AUDIO_INPUT A9
#define PIN_LED_OUTPUT A8
#define USE_FFT256


// Libraries for Arudino IDE to figure itself out
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>

// Stuff for this project.
#include "audio.h"
#include "led.h"
#include "effect_spectrum.h"
#include "commands.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Boo!");

  setup_commands();
  setup_leds();
  setup_audio();

  e_spectrum_setup();
}

void loop() {
  e_spectrum_loop();
  
  loop_leds();
  loop_commands();
}

// void serialEvent() {
//   inputString = ""
//   while (Serial.available()) {
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag
//     // so the main loop can do something about it:
//     if (inChar == '\n') {
//       stringComplete = true;
//     }
//   }
// }