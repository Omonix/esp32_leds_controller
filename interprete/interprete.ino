#include "BluetoothSerial.h"
#include <FastLED.h>
#include <math.h>
#include <iterator>
#include <list>
#define NUM_LEDS 300
#define DATA_PIN 4

CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;
const int ledPin = 2;
int to_do = 0;
bool actived = false;
int brightness = 5;
int color1 = 0;
int color2 = 0;
int under_space = 0;

void lb_reset(int color) {
  int the_color[3] = {lb_get_rgb(color, 16), lb_get_rgb(color, 8), lb_get_rgb(color, 0)};
  to_do = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(the_color[0], the_color[1], the_color[2]);
  }
  FastLED.show();
}
void lb_all_leds(int color) {
  int the_color[3] = {lb_get_rgb(color, 16), lb_get_rgb(color, 8), lb_get_rgb(color, 0)};
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(the_color[0], the_color[1], the_color[2]);
    delay(10);
    FastLED.show();
  }
  to_do = 1;
}
void lb_two_colors(int color1, int color2, int space) {
  lb_all_leds(color1);
  delay(space);
  lb_all_leds(color2);
  delay(space);
  to_do = 2;
}
void lb_peer(int color1, int color2) {
  int the_color1[3] = {lb_get_rgb(color1, 16), lb_get_rgb(color1, 8), lb_get_rgb(color1, 0)};
  int the_color2[3] = {lb_get_rgb(color2, 16), lb_get_rgb(color2, 8), lb_get_rgb(color2, 0)};
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB(the_color1[0], the_color1[1], the_color1[2]);
    } else {
      leds[i] = CRGB(the_color2[0], the_color2[1], the_color2[2]);
    }
    FastLED.show();
    delay(10);
  }
  to_do = 3;
}
void lb_color_fade(int color1, int color2, int space) {
  int the_color1[3] = {lb_get_rgb(color1, 16), lb_get_rgb(color1, 8), lb_get_rgb(color1, 0)};
  int the_color2[3] = {lb_get_rgb(color2, 16), lb_get_rgb(color2, 8), lb_get_rgb(color2, 0)};
  FastLED.setBrightness(0);
  lb_reset(color1);
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(80);
  }
  delay(space);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(80);
  }
  lb_reset(color2);
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(80);
  }
  delay(space);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(80);
  }
  to_do = 4;
}
void lb_snake(int color, int space) {
  int the_color[3] = {lb_get_rgb(color, 16), lb_get_rgb(color, 8), lb_get_rgb(color, 0)};
  for (int i = NUM_LEDS; i > 0; i--) {
    if (i % 10 == 0) {
      for (int x = 0; x < i; x++) {
        if (x != 0) {
          leds[x - 10] = CRGB(0, 0, 0);
          leds[x - 9] = CRGB(0, 0, 0);
          leds[x - 8] = CRGB(0, 0, 0);
          leds[x - 7] = CRGB(0, 0, 0);
          leds[x - 6] = CRGB(0, 0, 0);
          leds[x - 5] = CRGB(0, 0, 0);
          leds[x - 4] = CRGB(0, 0, 0);
          leds[x - 3] = CRGB(0, 0, 0);
          leds[x - 2] = CRGB(0, 0, 0);
          leds[x - 1] = CRGB(0, 0, 0);
        }
        leds[x] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 1] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 2] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 3] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 4] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 5] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 6] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 7] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 8] = CRGB(the_color[0], the_color[1], the_color[2]);
        leds[x + 9] = CRGB(the_color[0], the_color[1], the_color[2]);
        FastLED.show();
      }
    }
    delay(1000 / i * 2);
  }
  delay(space);
  lb_all_leds(0);
  to_do = 5;
}
void lb_unicorn() {
  std::vector<int> vec_color;
  vec_color.reserve(6);
  std::vector<int>::iterator it_color;
  vec_color.emplace_back(255<<16 | 0<<8 | 0);
  vec_color.emplace_back(255<<16 | 42<<8 | 0);
  vec_color.emplace_back(255<<16 | 174<<8 | 0);
  vec_color.emplace_back(42<<16 | 255<<8 | 0);
  vec_color.emplace_back(21<<16 | 0<<8 | 255);
  vec_color.emplace_back(160<<16 | 0<<8 | 192);
  for (int x = 0; x < vec_color.size(); x++) {
    it_color = vec_color.begin() - 1;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(lb_get_rgb(*it_color, 16), lb_get_rgb(*it_color, 8), lb_get_rgb(*it_color, 0));
      FastLED.show();
      if (i % 50 == 0) {
        if (it_color != vec_color.end()) {
          it_color++;
        } else {
          it_color = vec_color.begin() - 1;
        }
      }
      delay(10);
    }
    vec_color.emplace(vec_color.begin(), *(vec_color.begin() + 5));
    vec_color.pop_back();
  }
}
int lb_get_rgb(int color, int rank) {
  return (color>>rank) & 0xFF;
}

void setup() {
  SerialBT.begin("LEDs Lydka");
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}
void loop() {
  std::list<int> data;
  std::list<int>::iterator it;
  if (SerialBT.available()) {
    while (SerialBT.available()) {
      data.push_back(SerialBT.read());
    }
    it = data.begin();
    int i = 0;
    int color1r = 0;
    int color1g = 0;
    int color1b = 0;
    int color2r = 0;
    int color2g = 0;
    int color2b = 0;
    while (it != data.end()) {
      if (i == 0) {
        actived = (bool)*it;
        if (!actived) break;
      } else if (i == 1) to_do = *it;
      else if (i == 2) {
        brightness = floor(*it * 255 / 100);
        if (brightness == 0) brightness++;
        FastLED.setBrightness(brightness);
      } else if (i == 3) color1r = *it;
      else if (i == 4) color1g = *it;
      else if (i == 5) color1b = *it;
      else if (i == 6) color2r = *it;
      else if (i == 7) color2g = *it;
      else if (i == 8) color2b = *it;
      else if (i == 9) under_space = *it * 1000;
      it++;
      i++;
    }
    color1 = color1r<<16 | color1g<<8 | color1b;
    color2 = color2r<<16 | color2g<<8 | color2b;
  }
  if (actived) {
    if (to_do == 1) {
      lb_all_leds(color1);
    } else if (to_do == 2) {
      lb_two_colors(color1, color2, under_space);
    } else if (to_do == 3) {
      lb_peer(color1, color2);
      to_do = 0;
    } else if (to_do == 4) {
      lb_color_fade(color1, color2, under_space);
    } else if (to_do == 5) {
      lb_snake(color1, under_space);
    } else if (to_do == 6) {
      lb_unicorn();
    }
  } else {
    lb_reset(0);
  }
}
