#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include<RTClib.h>
#include<Seeed_BME280.h>

const int RX1 = 8;
const int TX1 = 9;

void setup(){
  Serial.begin(9600);
  Serial.println("Initializing...");
  if (setupSDCard()) {
    Serial.println("good to go");
  }
  setupRTC();
  setupBME();
  Serial.println("Initialized");
}

void loop(){
   loopRTC();
   Serial.println("Loop");
   delay(1000);
}
