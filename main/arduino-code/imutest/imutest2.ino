// /*
//    Connections
//    ===========
//    Connect SCL to analog 5
//    Connect SDA to analog 4
//    Connect VDD to 3.3V DC
//    Connect GROUND to common ground
// */

// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>
// #include <utility/imumaths.h>

// int id = -1;
// int addr = 0x28;
// Adafruit_BNO055 bno;

// /*
// double offsetX = 159.13;
// double offsetY = 2.00;
// double offsetZ = 166.13;
// */
// double offsetX = 0;
// double offsetY = 0;
// double offsetZ = 0;

// void setup()
// {
//     Serial.begin(9600);
//     Serial.println("Setting up!");
//     bno = Adafruit_BNO055(id, addr);
//     if(!bno.begin())
//     {
//         /* There was a problem detecting the BNO055 ... check your connections */
//         Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//         while(1);
//     }
// }

// void printTemp(){
//     int8_t temp = bno.getTemp();
//     Serial.println(String("TEMP: ") + temp);
// }

// void printEuler(){
//     imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//     double x = euler.x() - offsetX;
//     double y = euler.y() - offsetY;
//     double z = euler.z() - offsetZ;
//     Serial.println(String("EULER: x=") + x + String(", y=") + y + String(", z=") + z);
// }

// void printCalibration(){
//     uint8_t system, gyro, accel, mag = 0;
//     bno.getCalibration(&system, &gyro, &accel, &mag);
//     Serial.print("CALIBRATION: Sys=");
//     Serial.print(system, DEC);
//     Serial.print(" Gyro=");
//     Serial.print(gyro, DEC);
//     Serial.print(" Accel=");
//     Serial.print(accel, DEC);
//     Serial.print(" Mag=");
//     Serial.println(mag, DEC);
// }

// void loop()
// {
// //    printCalibration();
// //    printTemp();
//     printEuler();
//     delay(1000);
// }