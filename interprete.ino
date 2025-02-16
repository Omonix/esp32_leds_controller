#include "BluetoothSerial.h";
//#include <FastLED.h>;
//#define NUM_LEDS 1;
//#define DATA_PIN 3;

//CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;
const int ledPin = 2;
void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32-Bluetooth");
  pinMode(ledPin, OUTPUT);
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  //leds[0] = CRGB(255, 0, 0);
  //FastLED.show();
  //delay(500);
  //leds[0] = CRGB(0, 0, 0);
  //FastLED.show();
  //delay(500);
  if (SerialBT.available()) {
    char c = SerialBT.read();
    if (c == '1') {
      digitalWrite(ledPin, HIGH);
    } else if (c == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}
