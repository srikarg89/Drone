#include "DShot.h"

/*

redefine DSHOT_PORT if you want to change the default PORT

Defaults
UNO: PORTD, available pins 0-7 (D0-D7)
Leonardo: PORTB, available pins 4-7 (D8-D11)

e.g.
#define DSHOT_PORT PORTD
*/

const int NUM_ESCS = 4;
const int MAX_DIFF = 25;

const int MICRO_DELAY = 20;

uint16_t throttles[NUM_ESCS];
uint16_t targets[NUM_ESCS];
uint16_t pins[NUM_ESCS] = {2, 3, 6, 7};
//uint16_t pins[NUM_ESCS] = {7};
DShot escs[NUM_ESCS];

void setup() {
  Serial.begin(115200);

  for(int i = 0; i < NUM_ESCS; i++){
    // Notice, all pins must be connected to same PORT
    escs[i].attach(pins[i]);
    throttles[i] = 0;
    targets[i] = 0;
    escs[i].setThrottle(throttles[i]);
    reset(i);
  }
  /*
  unsigned long start = millis();
  while(millis() - start < 1000){
    Serial.println("Doing stuff");
    escs[0].setThrottle(0);    
    escs[1].setThrottle(0);    
    escs[2].setThrottle(0);    
    escs[3].setThrottle(0);
    delay(10);
  }
  */
}

void reset(int idx){
  escs[idx].setThrottle(0);
  delayMicroseconds(MICRO_DELAY * 20);
}

int myabs(int num){
  if(num > 0){
    return num;
  }
  return -num;
}

int mymin(int a, int b){
  if(a < b){
    return a;
  }
  return b;
}

void actuate(int idx){
  int throttle = throttles[idx];
  int target = targets[idx];
  DShot esc = escs[idx];
  
  if(throttle != target){
    int diff = myabs(target - throttle);
    diff = mymin(diff, MAX_DIFF);
    int dir = 1;
    if(target < throttle){
      dir = -1;
    }
    diff *= dir;
    throttle += diff;
  }
  if (throttle < 48){
    throttle = 48;
    target = 48;
  }
  
  esc.setThrottle(throttle);
  
  throttles[idx] = throttle;
  targets[idx] = target;
}


void loop() {
  Serial.print("Throttle: ");
  Serial.println(throttles[0]);
  Serial.print("Target: ");
  Serial.println(targets[0]);
  if (Serial.available() > 0){
    int parsed = Serial.parseInt();
    int target = parsed;
    if (target > 2047)
      target = 2047;
    Serial.print(target, HEX);
    Serial.print("\t");
    Serial.println();
    Serial.print("Target: ");
    Serial.println(target);
    for(int i = 0; i < NUM_ESCS; i++){
      targets[i] = target;
    }
  }
  for(int i = 0; i < NUM_ESCS; i++){
    Serial.println("Actuating");
    actuate(i);
    delay(10);
  }
}
