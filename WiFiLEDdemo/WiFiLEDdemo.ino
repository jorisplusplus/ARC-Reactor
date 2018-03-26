#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#define PIN_BUTTON   0
#define PIN_LED     13
#define NUM_LEDS    25

// Neopixel object
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

uint32_t pixels;  // pixel buffer. this buffer allows you to set arbitrary
                            // brightness without destroying the original color values
byte brightness[NUM_LEDS] = {60, 120, 170, 120, 60, 60, 120, 170, 120, 60, 60, 120, 200, 120, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0};

ESP8266WebServer server(80);  // create web server at HTTP port 80

// Forward declare functions
void on_status();
void on_change_color();
void on_homepage();
void show_leds();

bool fire;
byte over;

void show_leds() {
  uint32_t r, g, b;
  uint32_t c;
  for(byte i=0;i<NUM_LEDS;i++) {
    r = (pixels>>16)&0xFF;
    g = (pixels>>8)&0xFF;
    b = (pixels)&0xFF;
    r = r*max(over, brightness[i])/255;
    g = g*max(over, brightness[i])/255;
    b = b*max(over, brightness[i])/255;
    c = (r<<16) + (g<<8) + b;
    leds.setPixelColor(i, c);
  }
  leds.show();

  
}

void setup() {
  Serial.begin(115200);
  
  // Set pin mode
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED,    OUTPUT);

  // Initialize LEDs
  leds.begin();
  leds.show();

  // Set WiFi SSID
  WiFi.mode(WIFI_AP);
  boolean result = WiFi.softAP("Arcie", "jornarc", 3);
  if(result) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed");
  }
  
  // Set server callback functions
  server.on("/",   on_homepage);    
  server.on("/js", on_status);
  server.on("/cc", on_change_color);
  server.begin();
  
  Serial.println("Starting");
  delay(1000);
    pixels = 0xFF307fff;

    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  fire = false;
  Serial.println("Starting loop");
}

void loop() {
    ArduinoOTA.handle();
    server.handleClient();
    delay(30);
    byte temp = brightness[0];
    for(int i = 0; i<15; i++) {
      brightness[i] = brightness[i+1];
    }
    brightness[15] = temp;
    for(int i = 0; i<15; i=i+2) {
      brightness[16+i/2] = brightness[i];
    }
    brightness[24] = 120;
    if(fire) over++;
    if(over == 0) fire = false;
    show_leds();
}

#include "html.h"
void on_homepage() {
  String html = FPSTR(index_html);
  server.send(200, "text/html", html);
}

// this returns device variables in JSON, e.g.
// {"pixels":xxxx,"blink":1}
void on_status() {
  
}

void on_change_color() {
  fire = true;
  over = 90;
  server.send(200, "text/html", "hey");
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}


