#include <Adafruit_NeoPixel.h>

#define LED_PIN 6       // WS2812B data pin
#define NUM_LEDS 13     // Number of LEDs in the strip
#define POT_PIN A0      // Potentiometer pin

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();  // Initialize all LEDs off
}

void loop() {
  // 1. Read potentiometer
  int potValue = analogRead(POT_PIN);         
  int volume = map(potValue, 0, 1023, 0, 100); // 0–100 %

  // 2. Send to PC
  Serial.println(volume);

  // 3. Update LED strip
  int ledsOn = map(volume, 0, 100, 0, NUM_LEDS);  // How many LEDs to light
  showVolumeBar(ledsOn);

  delay(100);
}

// Function to display bar on LEDs
void showVolumeBar(int ledsOn) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsOn) {
      strip.setPixelColor(i, strip.Color(255, 0, 0)); // Green LEDs for volume ,Red → strip.Color(255, 0, 0) ,Green → strip.Color(0, 255, 0) ,Blue → strip.Color(0, 0, 255)
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));   // Off
    }
  }
  strip.show();
}