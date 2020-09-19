#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Kalman.h>

class IMU{
    public:
        IMU();
        void begin(int id, int addr);
        void getEuler();
        void printCalibration();
        void getCalibration(uint8_t *cals);
        void calibrateOffsets();
        double x, y, z;
        double xOff, yOff, zOff;
    private:
        int _id;
        int _addr;
        unsigned long last_measured_time;
        Adafruit_BNO055 bno;
        Kalman kalmanX, kalmanY, kalmanZ;
};

#endif
