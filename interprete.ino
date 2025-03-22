#include "BluetoothSerial.h";
#include <FastLED.h>;
#define NUM_LEDS 300
#define DATA_PIN 4
int to_do = 0;
int color1[3];
int color2[3];
int delayer = 10;
int brightness = 0;

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
void lb_all_leds(int red, int green, int blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(red, green, blue);
    delay(delayer);
    FastLED.show();
  }
}
void lb_two_colors(int space) {
  lb_all_leds(color1[0], color1[1], color1[2]);
  delay(space);
  lb_all_leds(color2[0], color2[1], color2[2]);
  delay(space);
}
void lb_peer() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB(color1[0], color1[1], color1[2]);
    } else {
      leds[i] = CRGB(color2[0], color2[1], color2[2]);
    }
    FastLED.show();
    delay(delayer);
  }
}
void lb_color_fade(int space) {
  FastLED.setBrightness(0);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(color1[0], color1[1], color1[2]);
  }
  FastLED.show();
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  delay(5000);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(color2[0], color2[1], color2[2]);
  }
  FastLED.show();
  for (int i = 0; i < brightness; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
  delay(5000);
  for (int i = brightness; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(40);
  }
}

void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("LEDs Lydka");
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if (SerialBT.available()) {
    FastLED.setBrightness(10);
    brightness = 10;
    char info = SerialBT.read();
    if (info == '1') {
      digitalWrite(ledPin, HIGH);
      to_do = 3;
      color1[0] = 0;
      color1[1] = 128;
      color1[2] = 128;
      color2[0] = 255;
      color2[1] = 50;
      color2[2] = 140;
    } else if (info == '0') {
      digitalWrite(ledPin, LOW);
      lb_reset();
    }
  }
  if (to_do == 1) {
    lb_two_colors(1000);
  } else if (to_do == 2) {
    lb_peer();
    to_do = 0;
  } else if (to_do == 3) {
    lb_color_fade(1000);
  }
}
