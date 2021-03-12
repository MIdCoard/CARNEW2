//
// Created by 周蜀杰 on 2020/12/9.
//
#include <car.h>
#include "pid.h"

static float med(float value,float mx,float mi) {
    if (value < mi)
        return mi;
    if (value > mx)
        return mx;
    return value;
}

float calcPID(uint8_t pos,float now,float target) {
    PID_CALC(getPID(pos),now,target);
    return getPID(pos)->out;
}

void PID_CALC(struct PID *pid, float now, float target){
    pid->err = target - now;
    float delta = pid->err - pid->lastErr;
    pid->sumErr = med(pid->sumErr + pid->err, pid->maxSumErr, pid->minSumErr);
    pid->lastErr = pid->err;

    float pout = pid->kp * pid->err;
    float iout = pid->ki * pid->sumErr;
    float dout = pid->kd * delta;

    pid->out = med(pout + iout + dout, pid->maxOut, pid->minOut);
}

struct PID pids[4];

struct PID* getPID(uint8_t pos) {
    return &pids[pos];
}

void PID_INIT(struct PID* pid,float kp,float ki,float kd,float maxOut,float minOut,float maxSum,float minSum) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->err = 0;
    pid->lastErr = 0;
    pid->sumErr = 0;
    pid->out = 0;
    pid->maxOut = maxOut;
    pid->minOut = minOut;
    pid->maxSumErr = maxSum;
    pid->minSumErr = minSum;
}

void initPID(float kp,float ki,float kd) {
    PID_INIT(&pids[LF],kp,ki,kd,MAXS,-MAXS,MAXOUTS,-MAXOUTS);
    PID_INIT(&pids[RF],kp,ki,kd,MAXS,-MAXS,MAXOUTS,-MAXOUTS);
    PID_INIT(&pids[LB],kp,ki,kd,MAXS,-MAXS,MAXOUTS,-MAXOUTS);
    PID_INIT(&pids[RB],kp,ki,kd,MAXS,-MAXS,MAXOUTS,-MAXOUTS);
}
