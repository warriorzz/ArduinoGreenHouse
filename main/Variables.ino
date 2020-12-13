#include <LiquidCrystal.h>

// Variables for automatic irrigation:
int soilMoisture;
const int moistureNorm = 0;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 12;
