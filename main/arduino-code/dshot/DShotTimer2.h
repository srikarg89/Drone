/**********************
  @file     DShotTimer2.h
  @brief    DShot implementation for Arduino using bit-banging method
  @author   Andy Tsui
 
  Original version using Timer 1 - https://github.com/gueei/DShot-Arduino
 
  Modified to use Timer 2 and Port B on the Arduino UNO
  Pins D8 - D13

  Modifications:    David Such
  Version:          1.0
  Date:             26/05/20
**********************/

#include "Arduino.h"

#ifndef DShotTimer2_h
#define DShotTimer2_h

#if defined(__AVR_ATmega328P__)
// For UNO, PortB 8-13: i.e. D8-D13
#define DSHOT_PORT PORTD
#endif

#if defined(__AVR_ATmega32U4__)
// For Leonardo, PortB 4-7: i.e. D8-D11
#define DSHOT_PORT PORTB
#endif

class DShot{
  public:
    DShot();
    void attach(uint8_t pin);
    void setTimerActive(bool active);
    uint16_t setThrottle(uint16_t throttle);
  private:
    uint16_t _packet = 0;
    uint16_t _throttle = 0;
    uint8_t _pinMask = 0;
};

#endif
