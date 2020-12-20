#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string>

// Variables for automatic irrigation:
int soilMoisture;
const int moistureNorm = 0;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 12;
LiquidCrystal_I2C lcd(0x27,16,2);