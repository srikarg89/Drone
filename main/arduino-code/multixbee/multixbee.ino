#include <DShot.h>
#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

/*

redefine DSHOT_PORT if you want to change the default PORT

Defaults
UNO: PORTD, available pins 0-7 (D0-D7)
Leonardo: PORTB, available pins 4-7 (D8-D11)

e.g.
#define DSHOT_PORT PORTD
*/

SoftwareSerial xbee =  SoftwareSerial(rxPin, txPin);

const int NUM_ESCS = 4;
const int MAX_DIFF = 25;

uint16_t throttles[NUM_ESCS];
uint16_t targets[NUM_ESCS];
uint16_t pins[NUM_ESCS] = {2, 3, 6, 7};
DShot escs[NUM_ESCS];

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);

  for(int i = 0; i < NUM_ESCS; i++){
    // Notice, all pins must be connected to same PORT
    escs[i].attach(pins[i]);
    throttles[i] = 0;
    targets[i] = 0;
    escs[i].setThrottle(throttles[i]);
  }
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

long mymap(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void actuate(int idx){
  int throttle = throttles[idx];
  int target = targets[idx];
  DShot esc = escs[idx];
  if (throttle < 48){
    throttle = 48;
  }
  if (target <= 48){
    esc.setThrottle(target);
  }
  else if(throttle != target){
    int diff = myabs(target - throttle);
    diff = mymin(diff, MAX_DIFF);
    int dir = 1;
    if(target < throttle){
      dir = -1;
    }
    diff *= dir;
    throttle += diff;
    esc.setThrottle(throttle);
  }
  throttles[idx] = throttle;
  targets[idx] = target;
}


void loop() {
  Serial.print("Throttle: ");
  Serial.println(throttles[0]);
  Serial.print("Target: ");
  Serial.println(targets[0]);
  if (xbee.available()){
    int incoming = xbee.read();
    int target = mymap(incoming, 0, 255, 45, 2047);
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
    actuate(i);
    delay(10);
  }
}
