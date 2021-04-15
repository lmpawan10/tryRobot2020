#include "pid.h"
#include "math.h"
#define SampleTime 10
float max, min;
float lastError = 0;
float iError = 0;

void PID::setKp(float kp) { Kp = kp; }
void PID::setKi(float ki) { Ki = ki; }
void PID::setKd(float kd) { Kd = kd; }
void PID::setPID(float kp, float ki, float kd)
{
    setKp(kp);
    setKi(ki);
    setKd(kd);
}
void PID::setlimits(float upp_out, float low_out)
{
    max = upp_out;
    min = low_out;
}

float PID::computePID(float setpoint, float obtain)
{
    float error = setpoint - obtain;
    iError = iError + (error * float(SampleTime)) / 1000.0;
    float output = Kp * error + Ki * iError;
    lastError = error;
    if (output > max)
    {
        output = max;
    }
    else if (output < min)
    {
        output = min;
    }
    // printf("SetPoint = %f, Output = %f\n", setpoint, output);
    return output;
}
