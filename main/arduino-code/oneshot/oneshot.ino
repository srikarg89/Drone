const int PIN = 6;

const int MIN_ONESHOT_WIDTH = 125;
const int MAX_ONESHOT_WIDTH = 250;

int period = 1000;

int pulseWidth = 0;

void setup(){
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);

  TCCR1A = 0;                              //  Clear TCCR A & B bits
  TCCR1B = 0;
  TCCR1A = (1 << COM1A1);                  //  Non-inverting output
  TCCR1B = (1 << WGM13)  | (1 << CS11);    //  Phase & Freq correct PWM, prescaler N = 8
  ICR1 = 20000;                            //  Default Freq = 50 Hz
  OCR0A = 0;

  delay(1000);
  on();
  delay(250);
}

void on(){
  pulseWidth = MIN_ONESHOT_WIDTH;
  ICR1 = period;
  OCR0A = MIN_ONESHOT_WIDTH;
}

void off(){
  pulseWidth = 0;
  OCR0A = 0;                              //  PWM OFF, pulse width = 0  
}

void printPulse(){
  Serial.print("Width: ");
  Serial.println(OCR0A);
}

void loop(){
  if(Serial.available()){
    int val = Serial.parseInt();
    if(val == 0){
      off();
    }
    else{
      val = constrain(val, MIN_ONESHOT_WIDTH, MAX_ONESHOT_WIDTH);
      pulseWidth = val;
      OCR0A = val;
      printPulse();
    }
  }
}
