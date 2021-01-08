RTC_DS3231 rtc;
int count = 0;

void setupRTC() {
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),  F(__TIME__)));

  openFile("Messdaten.txt");
  printPart("Tag - Monat - Jahr - Stunden - Minuten - Temperatur - Druck(Pascal) - Druck(Bar) - Luftfeuchtigkeit");
  printLn();
  closeFile();
}

void loopRTC() {
      DateTime now = rtc.now();
      openFile("messdaten.txt");
      printPart(now.day());
      writePlaceholder();
      printPart(now.month());
      writePlaceholder();
      printPart(now.year());
      writePlaceholder();
      printPart(now.hour() + 1);
      writePlaceholder();
      printPart(now.minute());

      writePlaceholder();
      printTemperatureOnSDCard();
      writePlaceholder();
      printPascalOnSDCard();
      writePlaceholder();
      printBarOnSDCard();
      writePlaceholder();
      printHumidityOnSDCard();

      printLn();

      closeFile();
}
