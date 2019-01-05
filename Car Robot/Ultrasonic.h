// Ultrasonic.h - Library for HR-SC04 Ultrasonic Ranging Module.
  
#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

#define CM 1
#define INC 0

class Ultrasonic
{
    private:
      int Trig_pin;
      int Echo_pin;
      long  duration,distacne_cm,distance_inc;

    public:
      Ultrasonic(int TP, int EP);
      long Timing();
      long Ranging(int sys);
    
};

#endif
