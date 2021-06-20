#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h>
#include <RTClib.h>

// Variables for automatic irrigation:
int soilMoisture;
int nextMeasurement = 0;
const int moistureNorm = 700;  // The moisture we want to keep
const int moistureSensorPin = A0;
const int pumpPin = 10;

//Variables for LCD display
LiquidCrystal_I2C lcd(0x27,16,2);
boolean working = true;
boolean successfullyInitialized = true;

//Variables for SD Card
File atmFile;
String nameAtm = "DATA.CSV";

//Variables for RTC
RTC_DS3231 rtc;

// Variables for BME
BME280 bme;

void setup() {
  Serial.begin(9600);
  // initialize moisture sensor
  pinMode(moistureSensorPin, INPUT);
  // initialize pump
  pinMode(pumpPin, OUTPUT);
  // initialize BME
  bme.init();
  
  setupLCD();
  String randomString = ""; //getTimeFormatted()
  randomString.concat("DATA.CSV");
  nameAtm = randomString;
  if (!setupSDCard()) {
    Serial.println("Error! Could not initialize SD card");
    successfullyInitialized = false;
  }
  setupRTC();

  if (isFileEmpty(nameAtm)) {
    openFile(nameAtm);
    writeLine("Time;Pressure (Bar);Pressure (Pascal);Humidity;Temperature");
    closeFile();
  }
  displayFirstLine("                ");
  displaySecondLine("                ");
  if (successfullyInitialized) {
    displayFirstLine(String("Successfully initialized"));
  } else {
    displayFirstLine(String("Cannot initialized!"));
  }
}

void loop() {
  openFile(nameAtm);
  writeLine(getTimeFormatted() + ";" + getPressureBar() + ";" + getPressurePascal() + ";" + getHumidityString() + ";" + getTemperatureString());
  closeFile();
  displayFirstLine("                ");
  displaySecondLine("                ");
  if (working) {
    displaySecondLine(String("Working, however"));
  } else {
    displaySecondLine(String("PROBLEM!"));
  }
  working = true;
  if ( nextMeasurement % 60 == 0 ) checkMoisture();
  delay(1000);
  nextMeasurement++;
  if ( (nextMeasurement+1) % 60 == 0) stopPump(); 
  // The pump should be only activated for a short time (1s)
}

//Automatic irrigation
void startPump(){
  digitalWrite(pumpPin, HIGH);
}

void stopPump(){
  digitalWrite(pumpPin, LOW);
}

void checkMoisture(){
  soilMoisture = analogRead(moistureSensorPin);
  Serial.println(soilMoisture);
  if ( soilMoisture > moistureNorm ) startPump();
  /*if ( soilMoisture < moistureNorm ) stopPump();
  Serial.println(String(map(soilMoisture,253,1019,100,0))+","+String(soilMoisture));
  Serial.println("Grenzwert: "+String(map(moistureNorm,253,1019,100,0)));*/
}

//LCD
void setupLCD() {
    setupLCD(true);
}

void displaySecondLine(String line) {
    lcd.setCursor(1,0);
    lcd.print(line);
}

void displayFirstLine(String line) {
  lcd.setCursor(0,0);
  lcd.print(line);
}

void setupLCD(bool backlight) {
    lcd.begin();
    setBacklight(backlight);
}

void setBacklight(bool backlight) {
    if (backlight) {
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }
}

// SD-Card
bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String name) {
  atmFile = SD.open(name, FILE_WRITE);
  if (!atmFile) {
      working = false;
      Serial.println("Failed to open File " + nameAtm + "!");
  }
}

void writeLine(String line) {
  atmFile.println(line);
}

void writePart(String line) {
  atmFile.print(line);
}

void closeFile() {
  atmFile.close();
}

bool isFileEmpty(String name) {
  atmFile = SD.open(name, FILE_READ);
  if (!atmFile) {
      Serial.println("Failed to open File " + nameAtm + "!");
      return true;
  }
  bool response = atmFile.read() == -1;
  working = working && response;
  closeFile();
  return response;
}

// RTC
void setupRTC() {
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),  F(__TIME__)));
}

String getTimeFormatted() {
  return String(rtc.now().hour()) + String(":") + String(rtc.now().minute()) + String(":") + String(rtc.now().second());
}

String getTimeForName() {
  return String(rtc.now().year()) + String("-") + String(rtc.now().day()) + String("-") + String(rtc.now().hour()) + String("-") + String(rtc.now().minute()) + String("-") + String(rtc.now().second()) + String("-");
}

// BME
String getPressurePascal() {
  return String(bme.getPressure());
}

String getPressureBar() {
  return String((float) bme.getPressure() / (float) 100000);
}

String getHumidityString() {
  return String(bme.getHumidity());
}

String getTemperatureString() {
  return String(bme.getTemperature());
}

// General 
String randomString(){
    String pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    String randomString = String("");
    for (int i = 0; i < 10; i++) {
        int randomInt = random(pool.length() - 2);
        randomString.concat(pool.substring(randomInt, randomInt + 1));
    }
    return randomString;
}
