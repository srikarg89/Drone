#include "PWMMotorControl.h"

PWMMotorControl::PWMMotorControl(int inpPins[]){  
    for(int i = 0; i < NUM_MOTORS; i++){
        pins[i] = inpPins[i];
    }
}

void PWMMotorControl::begin(){
    Serial.println("Beginning");
    for(int i = 0; i < NUM_MOTORS; i++){
        escs[i].attach(pins[i]);
        targets[i] = MIN_THROTTLE;
        diffs[i] = 0;
    }
    arm();
    average = MIN_THROTTLE;
    updateThrottles();
    delay(3000);
}

void PWMMotorControl::arm(){
    for(int i = 0; i < NUM_MOTORS; i++){
        escs[i].attach(pins[i]);
        targets[i] = MIN_THROTTLE;
        diffs[i] = 0;
        escs[i].writeMicroseconds(MIN_THROTTLE);
    }
    delay(2000);
}

int mymin(int a, int b){
  if(a < b){ return a; }
  return b;
}

int mymax(int a, int b){
  if(a > b){ return a; }
  return b;
}

void PWMMotorControl::control(){
    Serial.println("CONTROLLING");
    for(int idx = 0; idx < NUM_MOTORS; idx++){
        int target = targets[idx];
        if(average == 1000){
            target = 1000;
        }
        Servo esc = escs[idx];
        Serial.print("\tWriting: ");
        Serial.print(target);
        esc.writeMicroseconds(target);
    }
    Serial.println();
}

void PWMMotorControl::updateThrottles(){
    for(int i = 0; i < NUM_MOTORS; i++){
        int target = average + diffs[i];
        target = mymin(target, MAX_THROTTLE);
        target = mymax(target, MIN_THROTTLE);
        targets[i] = target;
    }
}

void PWMMotorControl::setAverage(int throttleAnalog){
    average = map(throttleAnalog, 1050, 2000, MIN_THROTTLE, MAX_THROTTLE);
    Serial.println(average);
    updateThrottles();
}

void PWMMotorControl::setDiffs(int newDiffs[]){
    for(int i = 0; i < NUM_MOTORS; i++){
        diffs[i] = newDiffs[i];
    }
    updateThrottles();
}
