#include <Adafruit_BNO055.h>

unsigned long start_time;
int num_loops;

Adafruit_BNO055 bno;

void setup()
{
    Serial.begin(115200);
    bno = Adafruit_BNO055(-1, 0x28);
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }

    bno.setExtCrystalUse(true);

    while(true){
        uint8_t cals[4];
        getCalibration(bno, &cals[0]);
        if(cals[1] != 0){
            break;
        }
        Serial.println("Waiting for gyro calibration");
        delay(100);
    }
    num_loops = 0;
}

void loop()
{
    num_loops += 1;
    if(num_loops == 1){
        start_time = millis();
    }
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    Serial.print(euler.x());
    Serial.print("Y: ");
    Serial.print(euler.y());
    Serial.print("Z: ");
    Serial.print(euler.z());
    Serial.println();
    double diff = (double)(millis() - start_time);
    Serial.print("Time (ms) per loop: ");
    Serial.println(diff / (double)num_loops);
    Serial.println(diff);
}

void getCalibration(Adafruit_BNO055 bno, uint8_t *cals){
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
