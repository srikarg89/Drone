#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

SoftwareSerial xbee =  SoftwareSerial(rxPin, txPin);
void setup() {
  // put your setup code here, to run once:
  xbee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(xbee.available()){
    Serial.println(xbee.read());
  }
}
