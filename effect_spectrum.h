float e_spectrum_scale = 80.0;
u_int e_spectrum_color = 0;
bool  e_spectrum_color_cycle = true;

void e_spectrum_setup() {

}

void e_spectrum_loop() {
  if (e_spectrum_color_cycle) {
    e_spectrum_color = (u_int) millis()/10;
  }

  float level8[8];
  float level16[16];
  int shown[16];
  
  if (audio_fft.available()) {
    get_fft_data8(audio_fft, level8);
    get_fft_data16(audio_fft, level16);
    int x, y;
    for (x = 0; x < 8; x++) {
      shown[x] = 10 * log10(1 + (fabs(level8[x]) * fabs(level8[x]))) * e_spectrum_scale;
      //shown[x] = level8[x] * scale;

      for (y = 1; y < 6; y++) {
        if (shown[x] < y) {
          leds[XY(x,5-y)] = CRGB(CHSV((8 + x) * 16, 48, 48));
          leds[XY(15-x,5-y)] = CRGB(CHSV((8 + x) * 16, 48, 48));
        } else {
          leds[XY(x,5-y)] = CRGB(CHSV((e_spectrum_color + x) * 16, 255, 255));
          leds[XY(15-x,5-y)] = CRGB(CHSV((e_spectrum_color + x) * 16, 255, 255));
        }
      }
    }
  }
}

void e_spectrum_destroy() {

}