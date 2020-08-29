#include "DShotTimer2.h"

DShot esc;
// 0x555 or 1365 Decimal (68% throttle)
//uint16_t throttle = 0b10101010101; 
uint16_t throttle = 125;

void setup() {
  esc.attach(2);  
  esc.setThrottle(0);
  delay(10000);
}

void loop() {
  esc.setThrottle(throttle);
  delay(100);
}
