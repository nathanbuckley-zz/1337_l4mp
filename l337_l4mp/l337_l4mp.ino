/*
*
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>

#define PIN  5
#define NUMPIXELS  12
#define DBG_OUTPUT_PORT Serial //Here for note. to be removed after initial write to just serial for easier reading and understanding

ESP8266WebServer server(1337);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "*********";
const char* password = "*********";
const char* host = "l337_l4mp";

//Function for standard LOADING... pattern
void ledPatternLoadBlue() {
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

// Function for standard LOADED Light pattern
void ledPatternLoaded(){
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

//Function for cylon pattern
void ledPatternCylon(){

}


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  loadBlue()
}
