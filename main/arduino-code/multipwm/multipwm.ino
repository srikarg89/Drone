#include <Servo.h>
Servo motor;


void setup()
{
    Serial.begin(9600);
    Serial.println("Stuff");
    motor.attach(9);
    actuate(0);
    delay(5000);
    // delay(10000000);
    // actuate(1000);
    // Serial.println("Actuated 1000");
    // delay(1000);

    // actuate(2500);
    // Serial.println("Actuated 2500");
    // delay(2000);
    // actuate(1000);
    // delay(1000);
    // actuate(1500);
    // Serial.println("Actuated 1500");
    // delay(100000);
}

void actuate(int sped){
    motor.writeMicroseconds(sped);
}

// 1. 1000, 2. 1000, 3. 1000, 4. 1000
// 1. 2230 2. 2230, 3. 2230, 4. 2230

void loop()
{
    for(int i = 1000; i < 1400; i += 10){ // Starting
    // for(int i = 2400; i > 1400; i -= 100){ // Ending
        Serial.println(i);
        // actuate(1000);
        // delay(1000);
        actuate(i);
        // delay(500);
        delay(500);
    }
}
