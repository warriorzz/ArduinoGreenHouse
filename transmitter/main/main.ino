#include <RCSwitch.h>
RCSwitch rcSwitch = RCSwitch(); 

void setup() {
   setupTransmitter();  
}

void loop() {
  loopTransmitter();
}
