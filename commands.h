#include <SerialCommand.h>

SerialCommand sCmd;

void c_set_brightness() {
  int brightness;
  char *arg;

  arg = sCmd.next();
  if (arg == NULL) {
  	Serial.println("c_set_brightness requires an argument");
  	return;
  }

  if (strcmp(arg, "RESET") == 0) {
  	brightness = BRIGHTNESS;
  } else {
    brightness = atoi(arg);
  }
  
  if (brightness < 0 || brightness > 255) {
    Serial.print("Brightness out of range: ");
    Serial.println(brightness);
    return;
  }

  Serial.print("Setting Brightness to: ");
  Serial.println(brightness);
  FastLED.setBrightness(brightness);
}

void c_set_scale() {
  float scale;
  char *arg;

  arg = sCmd.next();
  if (arg == NULL) {
    Serial.println("c_set_scale requires an argument");
    return;
  }

  if (strcmp(arg, "RESET") == 0) {
    scale = 80.0;
  } else {
    scale = atof(arg);
  }

  Serial.print("Setting scale to: ");
  Serial.println(scale);
  e_spectrum_scale = scale;
}

void c_unrecognized(const char *command) {
  Serial.print("Unrecognized Command: ");
  Serial.println(command);
}

void setup_commands() {
  sCmd.addCommand("BRIGHTNESS", c_set_brightness);
  sCmd.addCommand("SCALE", c_set_scale);
  sCmd.setDefaultHandler(c_unrecognized);
}

void loop_commands() {
  sCmd.readSerial();
}