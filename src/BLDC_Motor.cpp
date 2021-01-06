#include <BLDC_Motor.h>

BLDC_Motor::BLDC_Motor(int en_a, int en_b, int en_c, int in_a, int in_b, int in_c){
    _en_a = en_a;
    _en_b = en_b;
    _en_c = en_c;
    _in_a = in_a;
    _in_b = in_b;
    _in_c = in_c;

    currState = 0; 
    direction = false;
    stopped = false;
    power = 128;

    coilA.en_pin = _en_a;
    coilA.in_pin = _in_a;
    coilB.en_pin = _en_b;
    coilB.in_pin = _in_b;
    coilC.en_pin = _en_c;
    coilC.in_pin = _in_c;

    motorPins = {coilA, coilB, coilC};

    state1.a = 1;
    state1.b = 0;
    state1.c = 2;

    state2.a = 1;
    state2.b = 2;
    state2.c = 0;

    state3.a = 2;
    state3.b = 1;
    state3.c = 0;

    state4.a = 0;
    state4.b = 1;
    state4.c = 2;

    state5.a = 0;
    state5.b = 2;
    state5.c = 1;

    state6.a = 2;
    state6.b = 0;
    state6.c = 1;

    analogWriteResolution(8);
    analogWriteFrequency(in_a,50000);
    analogWriteFrequency(in_b,50000);
    analogWriteFrequency(in_c,50000);
    pinMode(en_a, OUTPUT);
    pinMode(en_b, OUTPUT);
    pinMode(en_c, OUTPUT);
    pinMode(in_a, OUTPUT);
    pinMode(in_b, OUTPUT);
    pinMode(in_c, OUTPUT);

    // Create new temp array and transfer its contents to the
    // global variable (I don't know of a better way to do this)
    states newStates[6] = {state1, state2, state3, state4, state5, state6};

    for (int i = 0; i < 6; i++)
    {
        motorStates[i] = newStates[i];
    }
}

void BLDC_Motor::moveToStep(MotorPins m, int s){
    if (!stopped){
    digitalWrite(m.a.en_pin, motorStates[s].a < 2);
    digitalWrite(m.b.en_pin, motorStates[s].b < 2);
    digitalWrite(m.c.en_pin, motorStates[s].c < 2);

    analogWrite(m.a.in_pin, (motorStates[s].a == 1) * power);
    analogWrite(m.b.in_pin, (motorStates[s].b == 1) * power);
    analogWrite(m.c.in_pin, (motorStates[s].c == 1) * power);
    }
    else
    {
    digitalWrite(m.a.en_pin, motorStates[s].a < 2);
    digitalWrite(m.b.en_pin, 0);
    digitalWrite(m.c.en_pin, 0);

    analogWrite(m.a.in_pin, 0);
    analogWrite(m.b.in_pin, 0);
    analogWrite(m.c.in_pin, 0);
    }
    
}

void BLDC_Motor::turnCounterclockwise(){
    incrementCurrState();
    moveToStep(motorPins, currState);
}

void BLDC_Motor::turnClockwise(){
    decrementCurrState();
    moveToStep(motorPins, currState);
}

void BLDC_Motor::incrementCurrState(){
    currState++;
    currState = currState % 6;
}

void BLDC_Motor::decrementCurrState(){
    currState--;
    if (currState < 0)
    {
        currState = 5;
    }
}

void BLDC_Motor::stopMotor(){
    stopped = true;
}