#ifndef PWMMotorControl_h
#define PWMMotorControl_h

#include "Arduino.h"
#include <Servo.h>

class PWMMotorControl{
private:
    const int NUM_MOTORS = 4;
    const int MIN_THROTTLE = 1000;
    const int MAX_THROTTLE = 1300;
    uint16_t diffs[4];
    uint16_t pins[4];
    Servo escs[4];
    uint16_t targets[4];
    uint16_t average;
public:
    PWMMotorControl(int pins[]);
    void begin();
    void arm();
    void setAverage(int throttleAnalog);
    void setDiffs(int newDiffs[]);
    void updateThrottles();
    void control();
};

#endif
