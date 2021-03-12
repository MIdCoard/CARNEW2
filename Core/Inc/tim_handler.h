//
// Created by 周蜀杰 on 2020/11/27.
//

#ifndef __TIM_HANDLER_H
#define __TIM_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "tim.h"
#include "stream.h"


void addHandler(TIM_HandleTypeDef,void (*)());
void addCaptureHandler(TIM_HandleTypeDef,void (*)());


#ifdef __cplusplus
}
#endif


#endif //MYFIRST_TIM_HANDLER_H
