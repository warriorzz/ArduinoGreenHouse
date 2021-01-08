bool setupSDCard() {
  return SD.begin(5);
}

void openFile(String fileName) {
  nameAtm = fileName;
  atmFile = SD.open(fileName, FILE_WRITE);
}

void writeLine(String line) {
  atmFile.println(line);
}

void closeFile() {
  atmFile.close();
}
