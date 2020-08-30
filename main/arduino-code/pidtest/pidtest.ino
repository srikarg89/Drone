#include "IMU.h"
#include "PID.h"
#include "PWMMotorControl.h"

#define THROTTLE_PIN A0
#define PID_PIN A1

IMU myImu;

// Gain constants: P, I, D
// Setting gain constants: P, I, D
double gains1[3] = {0.5, 0, 0};
double gains2[3] = {0.5, 0, 0};
// Pitch, Roll, Yaw
double bounds[3] = {150, 150, 0};

PID pid;

int pins[4] = {3, 6, 9, 10};
PWMMotorControl controller(pins);

void setup(){
    Serial.begin(9600);
    delay(1000);
    Serial.println("Setting up");
    pinMode(THROTTLE_PIN, INPUT);
    pinMode(PID_PIN, INPUT);
    setGains();
    myImu.begin(-1, 0x28);
    pid.begin(gains1, gains2, bounds);
    myImu.printCalibration();
    myImu.calibrateOffsets();
    controller.begin();
}

double mymap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double setGains(){
    int pidAnalog = pulseIn(PID_PIN, HIGH); // Gives number between 1000 to 2000
    double analogDouble = (double) pidAnalog;
    double pidVal = mymap(analogDouble, 1000.0, 2000.0, 0.0, 5.0);
    gains1[0] = pidVal;
    gains2[0] = pidVal;
}

void pidToMotors(double changes[2], int *diffs){
    diffs[0] = (int)(changes[0] + changes[1]);
    diffs[1] = (int)(changes[0] - changes[1]);
    diffs[2] = (int)(-changes[0] - changes[1]);
    diffs[3] = (int)(-changes[0] + changes[1]);
}

void updateAverage(){
    int throttleAnalog = pulseIn(THROTTLE_PIN, HIGH); // Gives number between 1000 to 2000
    if(throttleAnalog < 1050){
      throttleAnalog = 1050;
    }
    Serial.print("Setting average: ");
    Serial.println(throttleAnalog);
    controller.setAverage(throttleAnalog);
}


void loop(){
    updateAverage();
    // myImu.getTemp();
    myImu.getEuler();
    Serial.println(String("IMU Data:") + String("\tx=") + myImu.x + String("\ty=") + myImu.y + String("\tz=") + myImu.z);
    double changes[2];
    pid.update(myImu.x, myImu.y, myImu.z, &changes[0]);
    Serial.println(String("Changes:\t") + changes[0] + String("\t") + changes[1]);
    int diffs[4];
    pidToMotors(changes, &diffs[0]);
//    Serial.println(String("Diffs:\t") + diffs[0] + String("\t") + diffs[1] + String("\t") + diffs[2] + String("\t") + diffs[3]);
    controller.setDiffs(diffs);

    controller.control();
}
