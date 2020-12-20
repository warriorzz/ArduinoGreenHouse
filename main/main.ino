void setup() {
  pinMode( moistureSensorPin, INPUT);
  pinMode( motorPin, OUTPUT);
  setupLCD();
}

void loop() {
  checkMoisture()
}
