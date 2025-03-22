using namespace std;
#include "BluetoothSerial.h";
#include <FastLED.h>;
#include <string>;
#define NUM_LEDS 300
#define DATA_PIN 4
int to_do = 0;
bool actived = false;
int brightness = 0;
int color1 = 0<<16 | 128<<8 | 128;
int color2 = 255<<16 | 50<<8 | 140;

CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;
const int ledPin = 2;

void lb_reset() {
  to_do = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(the_color1[0], the_color1[1], the_color1[2]);
  }
  FastLED.show();
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  delay(space);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(the_color2[0], the_color2[1], the_color2[2]);
  }
  FastLED.show();
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  delay(space);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  to_do = 4;
}
void lb_snake(int color) {
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
  delay(10000);
  lb_all_leds(0);
}
int lb_get_rgb(int color, int rank) {
  return (color>>rank) & 0xFF;
}

void setup() {
  SerialBT.begin("LEDs Lydka");
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if (SerialBT.available()) {
    FastLED.setBrightness(1);
    brightness = 1;
    char info = SerialBT.read();
    //std::string info = "1";
    if (info == '1') {
      digitalWrite(ledPin, HIGH);
      to_do = 5;
      actived = true;
    } else if (info == '0') {
      digitalWrite(ledPin, LOW);
      lb_reset();
      actived = false;
    }
  }
  if (actived == true) {
    if (to_do == 1) {
      lb_all_leds(color1);
    } else if (to_do == 2) {
      lb_two_colors(color1, color2, 10000);
    } else if (to_do == 3) {
      lb_peer(color1, color2);
      to_do = 0;
    } else if (to_do == 4) {
      lb_color_fade(color1, color2, 5000);
    } else if (to_do == 5) {
      lb_snake(color1);
    }
  }
}
