//
// Created by 周蜀杰 on 2020/12/6.
//


#ifndef __CAR_H
#define __CAR_H
#ifdef __cplusplus
extern "C" {
#endif
#define MAXS 35
#define DEFAULT_SPEED 0

#define LF 0
#define RF 1
#define LB 2
#define RB 3

#define FORWARD 0
#define BACK 1
#include "main.h"
#include "tim.h"
#include "tim_handler.h"
#include "gpio.h"

struct Car {
    float speed;
    uint8_t direction;
};

void enable(uint8_t);

void disable(uint8_t);
void moveBack();
void moveForward();
void initCar();
void setSpeed(uint8_t,float );
float getSpeed(uint8_t);
float getActualSpeed(uint8_t);
void setActualSpeed(uint8_t,float);
void setSpeedAll(float);
void disableAll();
void enableAll();

void changeDirection(uint8_t,uint8_t);

#ifdef __cplusplus
}
#endif

#endif //CARN_CAR_H
