/**
 * @file BLDC_Motor.h
 *
 * @brief Constructs a BLDC (Brushless DC Motor) object, used for driving 3-phase Brushless DC Motors.
 *
 * @author Cavin Weber
 *
 */

#pragma once

#include <Arduino.h>


class BLDC_Motor{
    struct states // Describes the values of each output used during each of the six states of a BLDC
    {
        // 0 = LOW
        // 1 = HIGH
        // 2 = FLOATING (Disconnected / Open circuit)
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

    struct RPMLog
    {
        float timeElapsed;
        float numTicks;
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
        int numRotorPositions; // The number of positions the rotor must cycle through in order to make 1 revolution. Should be a multiple of 3 for a 3-phase motor.

        float RPMCounter;
        unsigned long lastRPMCall;

        void moveToStep(MotorPins m, int s);
        void incrementCurrState();
        void decrementCurrState();

        RPMLog _RPMLog[5];

    public:

    int power; // Value at which to set the PWM duty cycle
    pinPair coilA;
    pinPair coilB;
    pinPair coilC;

    MotorPins motorPins; // Holds the state space for the motor

    states state1;
    states state2;
    states state3;
    states state4;
    states state5;
    states state6;

    states motorStates[6]; 

    

    BLDC_Motor(int en_a, int en_b, int en_c, int in_a, int in_b, int in_c);

    /** Advance the BLDC forward one "state".
     * 
     * Note: BLDC directions are technically arbitrary.
     * ie. "Clockwise" and "Counterclockwise" are relative terms
     * defined by the way the wires are connected to the motor drivers.
     * 
     */
    void turnClockwise();
    
    /** Advance the BLDC backward one "state".
     * 
     * Note: BLDC directions are technically arbitrary.
     * ie. "Clockwise" and "Counterclockwise" are relative terms
     * defined by the way the wires are connected to the motor drivers.
     * 
     */
    void turnCounterclockwise();

    /** Ground all phases and disable input pins.
     */

    void stopMotor();

    // UNUSED
    int getState();

    /** Set the duty cycle (not frequency) of the motor control pins.
    */
    void setPower(float s);

    /** Set the PWM frequency (not duty cycle) of the motor control pins.
     * 
     * Default value is 20,000Hz.
     * Values at or above 20,000Hz are recommended in order to reduce audible vibrations.
     * Setting this value too high will induce switching losses in the MOSFETs.
     * IE. power will be wasted during the transition time between full saturation
     * and MOSFETs will begin to produce additional heat.
     * 
     */
    void setAnalogWriteFrequency(unsigned int f);

    /** Return RPM value of the BLDC.
     * 
     * Must be called more than once in order to get a valid reading.
     * May be less accurate with microcontrollers that do not give
     * exact micros() readings.
     * 
     */
    unsigned int getRPM();
};