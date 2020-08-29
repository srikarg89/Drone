// #ifndef MotorControl_h
// #define MotorControl_h

// #include "Arduino.h"
// #include "DShot2.h"

// class MotorControl{
// private:
//     const int MAX_DIFF = 25;
//     const int NUM_MOTORS = 4;
//     const int MIN_THROTTLE = 48;
//     const int MAX_THROTTLE = 800;
//     uint16_t diffs[4];
//     uint16_t pins[4];
//     DShot2 escs[4];
//     uint16_t throttles[4];
//     uint16_t targets[4];
//     uint16_t lastActuated[4];
//     uint16_t average;
// public:
//     MotorControl(int pins[]);
//     void begin();
//     void reset();
//     void setAverage(int throttleAnalog);
//     void setDiffs(int newDiffs[]);
//     void actuate(int idx);
//     void update();
//     void control();
// };

// #endif
