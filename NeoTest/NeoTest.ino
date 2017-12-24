/*
* A simple scrip to run some l337_l4mp patterns in sequance to test your neopixl ring.
*/
#include <Adafruit_NeoPixel.h>

#define PIN  5 //Data pin of your NeoPixel
#define NUMPIXELS  12 //Number of Pixels in your ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void loadBlueX4() {
  for(int i = 0; i < 4; i++){
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(106, 90, 205)); //On Light purple
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(80);
    }
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //Off.
      pixels.show();
      delay(80);
    }
  }
}

void ledLoaded(){
  for(int i=0; i < 3; i++){
    pixels.setPixelColor(0, pixels.Color(106, 90, 205));
    pixels.setPixelColor(2, pixels.Color(106, 90, 205));
    pixels.setPixelColor(4, pixels.Color(106, 90, 205));
    pixels.setPixelColor(6, pixels.Color(106, 90, 205));
    pixels.setPixelColor(8, pixels.Color(106, 90, 205));
    pixels.setPixelColor(10, pixels.Color(106, 90, 205));
    pixels.show();
    delay(80);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(8, pixels.Color(0, 0, 0));
    pixels.setPixelColor(10, pixels.Color(0, 0, 0));
    pixels.show();
    delay(80);
  }
}


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  loadBlueX4();
  ledLoaded();
}
