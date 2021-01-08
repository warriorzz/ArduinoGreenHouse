bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String fileName) {
  nameAtm = fileName;
  atmFile = SD.open(fileName, FILE_WRITE);
}

void printPart(String line) {
  atmFile.print(line);
}

void printPart(uint8_t line) {
  atmFile.print(line);
}

void printLn() {
    atmFile.println();
}

void closeFile() {
  atmFile.close();
}

void writePlaceholder() {
  atmFile.print(" - ");
}
