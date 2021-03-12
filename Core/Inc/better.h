//
// Created by 周蜀杰 on 2021/1/4.
//

#ifndef POSETURE_BETTER_H
#define POSETURE_BETTER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "usart.h"
#include "stream.h"
#include "usart_handler.h"
void initBetter(UART_HandleTypeDef*);
void receive();
float getPitch();
float getRoll();
float getYaw();
#ifdef __cplusplus
}
#endif
#endif //POSETURE_BETTER_H
