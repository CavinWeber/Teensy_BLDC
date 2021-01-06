#pragma once

#include <Arduino.h>

class BLDC_Motor{
    struct states
    {
        // 0 = LOW
        // 1 = HIGH
        // 2 = FLOATING
        int a;
        int b;
        int c;
    };

    struct pinPair
    {
        int en_pin;
        int in_pin;
    };

    struct MotorPins
    {
        pinPair a;
        pinPair b;
        pinPair c;
    };

    bool stopped; // Determines whether to stop all motor functionality

    private:
        int _en_a;
        int _en_b;
        int _en_c;
        int _in_a;
        int _in_b;
        int _in_c;
        bool direction; // 0 for counter-clockwise, 1 for clockwise
        int currState; // Current state in the 6 states of a BLDC (0-5)


        void moveToStep(MotorPins m, int s);

    public:


    int power;
    pinPair coilA;
    pinPair coilB;
    pinPair coilC;

    MotorPins motorPins;

    states state1;
    states state2;
    states state3;
    states state4;
    states state5;
    states state6;

    states motorStates[6];

    BLDC_Motor(int en_a, int en_b, int en_c, int in_a, int in_b, int in_c);
    void turnClockwise();
    void turnCounterclockwise();
    void incrementCurrState();
    void decrementCurrState();
    void stopMotor();
};