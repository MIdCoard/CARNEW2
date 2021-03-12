//
// Created by 周蜀杰 on 2020/12/9.
//

#ifndef __PID_H
#define __PID_H
#ifdef __cplusplus
extern "C" {
#endif

#define MAXOUTS 1000

#include "main.h"

struct PID {
    float kp,ki,kd;

    float err,lastErr,sumErr;

    float maxOut,minOut;

    float maxSumErr,minSumErr;

    float out;

};

struct PID *getPID(uint8_t);

void PID_CALC(struct PID*,float,float);

void PID_INIT(struct PID*,float,float ,float ,float ,float,float ,float );

float calcPID(uint8_t,float,float);

void initPID(float,float,float);
#ifdef __cplusplus
}
#endif
#endif //CARN_PID_H
