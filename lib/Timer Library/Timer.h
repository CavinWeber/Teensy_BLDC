#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

// Creates a timer object that returns true if the allotted duration has passed.
class Timer
{
  private:
    volatile long unsigned int _startTime;
    long unsigned int _duration;
    volatile bool _isTriggered;
  public:
    bool isTriggered();
    void reset();
    void setDuration(unsigned long t);
    Timer(unsigned long duration) {
      this->_duration = duration;
      this->_isTriggered = false;
      this->_startTime = micros();
    }
};

#endif