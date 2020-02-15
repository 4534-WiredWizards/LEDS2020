#include "FastLED.h"

#define DATA_PIN 13
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 40
#define BRIGHTNESS 60

CRGB leds[NUM_LEDS];
char mode = '0';
int ledposcase3 = 1;
int ledstackcase3 = 0;
int ledamountcase7 = 20;
int ledposrecordcase7[20];
int pointercase7 = 0;
void setup() {
  delay(1000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER> (leds, NUM_LEDS)
  .setCorrection(TypicalLEDStrip)
  .setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop() {
  if (Serial.available() > 1){
     int prevMode = mode;
     mode = Serial.read();
     if (mode != prevMode) {
        for (int i = 0; i < NUM_LEDS; i++) {
           leds[i] = CHSV(0, 0, 0);
        }
        FastLED.show();
     }
  }
  switch (mode) {
    case '0':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i * 7 + millis() / 10, 187, 255);
      }
      break;
    case '1':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(millis() / 10, 187, 255);
      }
      break;
    case '2':
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 20 < 2) {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(180, 0, 255);
        }
        else if (i % 20 < 10) {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(180, (i % 20) * 20 + 30, 230);
        }
        else {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(180, 255, 200);
        }
      }
      break;
    case '3':
      delay(30);
      if (ledposcase3 - 1 > -1) {
        leds[ledposcase3 - 1] = CHSV(0, 0, 0);
      }
      leds[ledposcase3] = CHSV((double)ledstackcase3 / NUM_LEDS * 255, 255, 255);
      for (int i = NUM_LEDS - 1; i > NUM_LEDS - ledstackcase3 - 1; i--) {
        leds[i] = CHSV((double)(NUM_LEDS - i - 1) / NUM_LEDS * 255, 255, 255);
      }
      if (ledposcase3 < NUM_LEDS - ledstackcase3 - 1) {
        ledposcase3++;
      }
      else {
        ledstackcase3++;
        ledposcase3 = 0;
      }
      if (ledstackcase3 >= NUM_LEDS) {
        ledstackcase3 = 0;
      }
      break;
    case '4':
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 20 < 2) {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(100, 0, 255);
        }
        else if (i % 20 < 10) {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(100, (i % 20) * 20 + 30, 230);
        }
        else {
          leds[(i - millis() / 50) % NUM_LEDS] = CHSV(100, 255, 200);
        }
      }
      break;
    case '5':
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 20 < 5) {
          switch (i % 20) {
            case 0:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(100, 150, 255);
              break;
            case 1:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(100, 70, 255);
              break;
            case 2:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(150, 0, 255);
              break;
            case 3:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(180, 70, 255);
              break;
            case 4:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(180, 150, 255);
              break;
          }
        }
        else if (i % 20 < 10) {
          leds[(i + millis() / 50) % NUM_LEDS] = CHSV(180, 255, 255);
        }
        else if (i % 20 < 15) {
          switch (i % 20 - 10) {
            case 4:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(100, 150, 255);
              break;
            case 3:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(100, 70, 255);
              break;
            case 2:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(150, 0, 255);
              break;
            case 1:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(180, 70, 255);
              break;
            case 0:
              leds[(i + millis() / 50) % NUM_LEDS] = CHSV(180, 150, 255);
              break;
          }
        }
        else {
          leds[(i + millis() / 50) % NUM_LEDS] = CHSV(100, 255, 255);
        }
      }
      break;
    case '6':
      for (int i = 0; i < NUM_LEDS; i++) {
      CHSV spectrumcolor;
      spectrumcolor.hue = i * 7 + millis() / 10;
      spectrumcolor.saturation = 187;
      spectrumcolor.value = 255;
      hsv2rgb_spectrum(spectrumcolor, leds[i]);
      }
      break;
    case '7':
      delay(100);
      ledposrecordcase7[pointercase7] = random(0, NUM_LEDS);
      pointercase7++;
      if(pointercase7 > ledamountcase7 - 1) pointercase7 = 0;
      for (int i = 0; i < ledamountcase7; i++) {
        if(pointercase7 > i) leds[ledposrecordcase7[i]] = CHSV(100, 0, 225 - ((pointercase7 - i) * (225/ (ledamountcase7 - 1))));
        else leds[ledposrecordcase7[i]] = CHSV(100, 0, 225 - ((pointercase7 + ledamountcase7 - 1 - i) * (225/ (ledamountcase7 - 1))));
      }
      break;
  }
  FastLED.show();
}
