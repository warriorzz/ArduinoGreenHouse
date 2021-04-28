String nameAtm;
File atmFile;

bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String fileName) {
  nameAtm = fileName;
  atmFile = SD.open(fileName, FILE_READ);
  Serial.println(atmFile);
}

void printPart(String line) {
  atmFile.print(line);
}

void printPart(int line) {
  atmFile.print(line);
}

void printPart(float line) {
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

void readFile() {
  Serial.println(atmFile.read());
}
