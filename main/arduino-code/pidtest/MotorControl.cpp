// #include "MotorControl.h"

// MotorControl::MotorControl(int inpPins[]){
//     for(int i = 0; i < NUM_MOTORS; i++){
//         pins[i] = inpPins[i];
//     }
// }

// void MotorControl::begin(){
//     for(int i = 0; i < NUM_MOTORS; i++){
//         escs[i].attach(pins[i]);
//         throttles[i] = 0;
//         targets[i] = 0;
//         diffs[i] = 0;
//         lastActuated[i] = 0;
//     }
//     reset();
//     Serial.println("Just reset, now delaying");
//     delay(10000);
//     Serial.println("Done delaying");
//     average = MIN_THROTTLE + 30;
//     update();
// }

// void MotorControl::reset(){
//     Serial.println("Resetting!");
//     for(int idx = 0; idx < NUM_MOTORS; idx++){
//         escs[idx].setThrottle(0);
//     }
// }

// int myabs(int num){
//   if(num > 0){ return num; }
//   return -num;
// }

// int mymin(int a, int b){
//   if(a < b){ return a; }
//   return b;
// }

// int mymax(int a, int b){
//   if(a > b){ return a; }
//   return b;
// }

// void MotorControl::actuate(int idx){
//     int throttle = throttles[idx];
//     int target = targets[idx];

//     if(throttle != target){
//     int diff = myabs(target - throttle);
//     diff = mymin(diff, MAX_DIFF);
//     int dir = 1;
//     if(target < throttle){
//         dir = -1;
//     }
//         diff *= dir;
//         throttle += diff;
//     }
//     if (throttle < 48){
//         throttle = 48;
//         target = 48;
//     }

//     if(throttle != lastActuated[idx]){
//         Serial.println(throttle);
//         escs[idx].setThrottle(throttle);
//         lastActuated[idx] = throttle;
//     }

//     throttles[idx] = throttle;
//     targets[idx] = target;
// }

// void MotorControl::control(){
//     Serial.println("Actuating");
//     for(int i = 0; i < NUM_MOTORS; i++){
//         actuate(i);
//     }
// }

// void MotorControl::update(){
//     if(average == 0){
//         for(int i = 0; i < NUM_MOTORS; i++){
//             escs[i].setThrottle(MIN_THROTTLE);
//         }
//         return;
//     }
//     for(int i = 0; i < NUM_MOTORS; i++){
//         int target = average + diffs[i];
//         target = mymin(target, MAX_THROTTLE);
//         target = mymax(target, MIN_THROTTLE);
//         targets[i] = target;
//     }
// }

// void MotorControl::setAverage(int throttleAnalog){
//     average = map(throttleAnalog, 1000, 2000, 48, 400);
//     update();
// }

// void MotorControl::setDiffs(int newDiffs[]){
//     for(int i = 0; i < NUM_MOTORS; i++){
//         diffs[i] = newDiffs[i];
//     }
//     update();
// }
