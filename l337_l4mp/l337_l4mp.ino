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
#define DBG_OUTPUT_PORT Serial //Remove and make all DBG_OUTPUT_PORT Serial !!! 

ESP8266WebServer server(80);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "*********";
const char* password = "*********";
const char* host = "l337_l4mp";

static bool hasSD = false;

void returnOK() {
  server.send(200, "text/plain", "");
}

void returnFail(String msg) {
  server.send(500, "text/plain", msg + "\r\n");
}

bool loadFromSdCard(String path){
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.htm";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".htm")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";

  File dataFile = SD.open(path.c_str());
  if(dataFile.isDirectory()){
    path += "/index.htm";
    dataType = "text/html";
    dataFile = SD.open(path.c_str());
  }

  if (!dataFile)
    return false;

  if (server.hasArg("download")) dataType = "application/octet-stream";

  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
    Serial.println("Sent less data than expected!");
  }

  dataFile.close();
  return true;
}

void handleNotFound(){
  if(hasSD && loadFromSdCard(server.uri())) return;
  String message = "SDCARD Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.print(message);
}

// ------------------------------ LIGHT PATTERNS ---------------------------------


//Loading light pattern
void loadBlue() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(106, 90, 205)); //On Light purple
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //Off.
    pixels.show();
    delay(500);
  }
}

//Standard  blink 3 times loaded pattern
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
    pixels.show();
    delay(80);
  }
}

//Call of the CYLON
void cylon(){
  
}


//------------------------------- SETUP --------------------------------------
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.print("\n");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wait for connection
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) {//wait 10 seconds
    delay(500);
  }
  if(i == 21){
    Serial.print("Could not connect to");
    Serial.println(ssid);
    while(1) delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(host)) {
    MDNS.addService("http", "tcp", 80);
    Serial.println("MDNS responder started");
    Serial.print("You can now connect to http://");
    Serial.print(host);
    Serial.println(".local");
  }

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  if (SD.begin(SS)){
     Serial.println("SD Card initialized.");
     hasSD = true;
  }
}


// ------------------------------- LOOP ---------------------------------
void loop() {
  loadBlue();
  server.handleClient();
}
