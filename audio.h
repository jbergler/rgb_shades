#include <math.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>

#ifdef USE_FFT256
#define FFT_SIZE     256
#define FFT_WINDOW   AudioWindowHanning256
#define FFT_ANALYSER AudioAnalyzeFFT256
#else
#define FFT_SIZE     1024
#define FFT_WINDOW   AudioWindowHanning1024 //AudioWindowBlackmanNuttall1024
#define FFT_ANALYSER AudioAnalyzeFFT1024
#endif

AudioInputAnalog     audio_in(PIN_AUDIO_INPUT);
FFT_ANALYSER         audio_fft;
AudioConnection      patchCord1(audio_in, 0, audio_fft, 0);

void setup_audio() {
  AudioMemory(10);
  audio_fft.windowFunction(FFT_WINDOW);
  //audio_fft.averageTogether(10);
}

#ifdef USE_FFT256
void get_fft_data8(FFT_ANALYSER fft, float* levels) {
  levels[0] = fft.read(2, 3);
  levels[1] = fft.read(4, 6);
  levels[2] = fft.read(7, 10);
  levels[3] = fft.read(11, 19);
  levels[4] = fft.read(20, 32);
  levels[5] = fft.read(33, 52);
  levels[6] = fft.read(53, 82);
  levels[7] = fft.read(83, 127);
}

void get_fft_data16(FFT_ANALYSER fft, float* levels) {
  levels[0] = fft.read(2);
  levels[1] = fft.read(3);
  levels[2] = fft.read(4);
  levels[3] = fft.read(5, 6);
  levels[4] = fft.read(7, 8);
  levels[5] = fft.read(9, 10);
  levels[6] = fft.read(11, 14);
  levels[7] = fft.read(15, 19);
  levels[8] = fft.read(20, 25);
  levels[9] = fft.read(26, 32);
  levels[10] = fft.read(33, 41);
  levels[11] = fft.read(42, 52);
  levels[12] = fft.read(53, 65);
  levels[13] = fft.read(66, 82);
  levels[14] = fft.read(83, 103);
  levels[15] = fft.read(104, 127);
}

#else

void get_fft_data8(FFT_ANALYSER fft, float* levels) {
  levels[0] = fft.read(2, 3);
  levels[1] = fft.read(4, 10);
  levels[2] = fft.read(11, 22);
  levels[3] = fft.read(23, 46);
  levels[4] = fft.read(47, 93);
  levels[5] = fft.read(94, 131);
  levels[6] = fft.read(132, 257);
  levels[7] = fft.read(258, 511);
} 

void get_fft_data16(FFT_ANALYSER fft, float* levels) {
  levels[0] = fft.read(0);
  levels[1] = fft.read(1);
  levels[2] = fft.read(2, 3);
  levels[3] = fft.read(4, 6);
  levels[4] = fft.read(7, 10);
  levels[5] = fft.read(11, 15);
  levels[6] = fft.read(16, 22);
  levels[7] = fft.read(23, 32);
  levels[8] = fft.read(33, 46);
  levels[9] = fft.read(47, 66);
  levels[10] = fft.read(67, 93);
  levels[11] = fft.read(94, 131);
  levels[12] = fft.read(132, 184);
  levels[13] = fft.read(185, 257);
  levels[14] = fft.read(258, 359);
  levels[15] = fft.read(360, 511);
}
#endif

