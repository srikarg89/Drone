/*
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
*/
#include "Arduino.h"
#include "IMU.h"

//#define BNO055_SAMPLERATE_DELAY_MS(100);

IMU::IMU(){}

void IMU::begin(int id, int addr){
    _id = id;
    _addr = addr;
    Serial.println(String("Creating IMU object with ID=") + id + String(" and addr=") + addr);
    bno = Adafruit_BNO055(id, addr);
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    x = 0; y = 0; z = 0;
    temp = 0;
}

void IMU::getTemp(){
    temp = bno.getTemp();
}

double round180(double num){
    if(num > 180){
        num -= 360;
    }
    if(num < -180){
        num += 360;
    }
    if(num > 90){
        num -= 180;
    }
    if(num < -90){
        num += 180;
    }
    return num;
}

void IMU::getEuler(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//    Serial.println(String("Offsets: ") + xOff + String(" ") + yOff + String(" ") + zOff);
    x = round180(euler.x() - xOff);
    y = round180(euler.y() - yOff);
    z = round180(euler.z() - zOff);
}

void IMU::printCalibration(){
    uint8_t cals[4];
    getCalibration(&cals[0]);
    Serial.print("CALIBRATION: Sys=");
    Serial.print(cals[0], DEC);
    Serial.print(" Gyro=");
    Serial.print(cals[1], DEC);
    Serial.print(" Accel=");
    Serial.print(cals[2], DEC);
    Serial.print(" Mag=");
    Serial.println(cals[3], DEC);
}

void IMU::getCalibration(uint8_t *cals){
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    cals[0] = system;
    cals[1] = gyro;
    cals[2] = accel;
    cals[3] = mag;
    Serial.print(system);
    Serial.print(gyro);
    Serial.print(accel);
    Serial.print(mag);
    Serial.println();
}

void IMU::calibrateOffsets(){
    while(true){
        uint8_t cals[4];
        getCalibration(&cals[0]);
        if(cals[1] != 0){
            break;
        }
        Serial.println("Waiting for gyro calibration");
        delay(100);
    }
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    xOff = euler.x();
    yOff = euler.y();
    zOff = euler.z();
}
