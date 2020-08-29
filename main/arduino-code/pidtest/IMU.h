#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class IMU{
    public:
        IMU();
        void begin(int id, int addr);
        void getTemp();
        void getEuler();
        void printCalibration();
        void getCalibration(uint8_t *cals);
        void calibrateOffsets();
        double x, y, z;
        double xOff, yOff, zOff;
        int8_t temp;
    private:
        int _id;
        int _addr;
        Adafruit_BNO055 bno;
};

#endif
