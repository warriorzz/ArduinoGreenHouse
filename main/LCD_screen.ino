void displaySecondLine(string line) {
    lcd.cursor(1,0);
    lcd.print(line)
}

void displayFirstLine(string line) {
  lcd.cursor(0,0);
  lcd.print(line)
}

void setupLCD() {
    lcd.begin();
    lcd.backlight();
}