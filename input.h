#include <FastLED.h>
#include <ADC.h>

extern float e_spectrum_scale;
extern int e_spectrum_rate;

int bright = 0;
int rate = 0;

#define HIST_SIZE 4
int hist_idx = 0;
int rate_hist[HIST_SIZE];
int bright_hist[HIST_SIZE];

ADC *adc = new ADC();

void setup_input() {
  adc->setReference(ADC_REF_3V3, ADC_1);
  adc->setResolution(8, ADC_1);
  pinMode(PIN_BRIGHT, INPUT);
  pinMode(PIN_SCALE, INPUT);
  pinMode(PIN_RATE, INPUT);
}

bool check_hist(int * hist) {
  bool result = true;
  int idx = 1;
  while (idx < HIST_SIZE && result) {
    result &= (hist[idx - 1] == hist[idx]);
    idx++;
  }
  return result;
}

void loop_input() {
  hist_idx++;
  hist_idx %= HIST_SIZE;
  
  bright_hist[hist_idx] = adc->analogRead(PIN_BRIGHT, ADC_1);

  if (bright != bright_hist[hist_idx] && check_hist(bright_hist)) {
    bright = bright_hist[hist_idx];
    Serial.print("bright: "); 
    Serial.println(bright);
    FastLED.setBrightness(bright);
  }

  rate_hist[hist_idx] = adc->analogRead(PIN_RATE, ADC_1);

  if (rate != rate_hist[hist_idx] && check_hist(rate_hist)) {
    rate = rate_hist[hist_idx];
    Serial.print("rate: "); 
    Serial.println(rate);
    e_spectrum_rate = rate;
  }

  e_spectrum_scale = (float) exp((double)adc->analogRead(PIN_SCALE, ADC_1) / 25);
//  Serial.print("scale: ");
//  Serial.println(e_spectrum_scale);
}



