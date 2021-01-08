#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// Variables for automatic irrigation:
int soilMoisture;
const int moistureNorm = 0;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 12;
const int motorPin = 13;

//Variables for LCD display
LiquidCrystal_I2C lcd(0x27,16,2);

//Variables for SD Card
File file;

void setup() {
  pinMode( moistureSensorPin, INPUT);
  pinMode( motorPin, OUTPUT);
  setupLCD();
  if(setupSDCard()) {
    //TODO
  }
}

void loop() {
  checkMoisture();
  delay(1000);
}
