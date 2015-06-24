String c_set_brightness(String arg) {
  int brightness;
  String result;

  if (arg == "RESET") {
    brightness = BRIGHTNESS;
  } else {
    brightness = arg.toInt();
  }
  
  if (brightness < 0 || brightness > 255) {
    result = "BRIGHT out of range: ";
    result += brightness;
  } else {
    FastLED.setBrightness(brightness);
    result = "BRIGHT = ";
    result += brightness;
  }
  return result;
}

String c_set_scale(String arg) {
  int scale;
  String result;

  if (arg == "RESET") {
    scale = 80;
  } else {
    scale = arg.toInt();
  }

  e_spectrum_scale = (float) scale;
  result = "SCALE = ";
  result += scale;
  return result;
}

String c_set_color(String arg) {
  int color;
  String result;

  if (arg == "RESET") {
    color = 0;
  } else {
    color = arg.toInt();
  }

  e_spectrum_color = color;
  result = "COLOR = ";
  result += color;
  return result;
}

String c_set_color_cycle(String arg) {
  String result;
  e_spectrum_color_cycle = !e_spectrum_color_cycle;
  result = "CC Toggled";
  return result;
}

String process_command(String input) {
  String result = "";
  if (input.indexOf(' ') <= 0) {
    result = "error: ";
    result += input;
    return result;
  }

  String command = input.substring(0,input.indexOf(' '));
  String arg = input.substring(input.indexOf(' ')+1);

  command.toUpperCase();
  
  // BR - brightness
  if      (command == "BR" || command == "BRIGHT") result = c_set_brightness(arg);
  else if (command == "SC" || command == "SCALE")  result = c_set_scale(arg);
  else if (command == "CO" || command == "COLOR")  result = c_set_color(arg);
  else if (command == "CC" || command == "CYCLE")  result = c_set_color_cycle(arg);
  else    result = "unknown: " + command;

  return result;
}