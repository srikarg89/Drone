void setup()
{
    Serial.begin(115200);
    pinMode(A0, INPUT);
}

void loop()
{
    unsigned long start_time = millis();
    int throttleAnalog = pulseIn(A0, HIGH); // Gives number between 1000 to 2000
    Serial.println(throttleAnalog);
    Serial.println(millis() - start_time);
}