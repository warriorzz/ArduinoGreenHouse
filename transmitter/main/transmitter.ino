void setupTransmitter() {
  rcSwitch.enableTransmit(10);
}
void loopTransmitter() {
  rcSwitch.send(9876,24);
  delay(1000);
}
