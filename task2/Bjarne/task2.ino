#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include<RTClib.h>
#include<Seeed_BME280.h>

void setup(){
  setupSDCard();
  setupRTC();
  setupBME();
}

void loop(){
   loopRTC();

   delay(1000);
}
