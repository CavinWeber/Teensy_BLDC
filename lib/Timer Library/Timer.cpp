#include "Arduino.h"
#include "Timer.h"

/*
For asynchronous checking of time state.
*/
bool Timer::isTriggered() {
  if (micros() - this->_startTime >= this->_duration) {
    _isTriggered = true;
    return true;
  }
  else {
    return false;
  }
}

/*
Resets and immediately begins timer again.
*/
void Timer::reset() {
  _startTime = micros();
  _isTriggered = false;
}

/*
Changes the duration of an existing timer, resets its current value, and immediately starts it again.
*/
void Timer::setDuration(unsigned long t) {
  _duration = t;
  reset();
}

