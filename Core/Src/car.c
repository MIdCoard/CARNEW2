//
// Created by 周蜀杰 on 2020/12/6.
//

#include <stdlib.h>
#include "car.h"
GPIO_TypeDef * ports1[4];
uint16_t pins1[4];
GPIO_TypeDef * ports2[4];
uint16_t pins2[4];

struct Car cars[4];

uint8_t status = 0;

void changeDirection(uint8_t pos,uint8_t direction) {
    // notice: for fix
    cars[pos].direction = direction;
//    if (direction == FORWARD) {
//        HAL_GPIO_WritePin(ports1[pos],pins1[pos],GPIO_PIN_SET);
//        HAL_GPIO_WritePin(ports2[pos],pins2[pos],GPIO_PIN_RESET);
//    } else if (direction == BACK) {
//        HAL_GPIO_WritePin(ports1[pos],pins1[pos],GPIO_PIN_RESET);
//        HAL_GPIO_WritePin(ports2[pos],pins2[pos],GPIO_PIN_SET);
//    }

    if (direction == FORWARD) {
        HAL_GPIO_WritePin(ports1[pos],pins1[pos],GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ports2[pos],pins2[pos],GPIO_PIN_SET);
    } else if (direction == BACK) {
        HAL_GPIO_WritePin(ports1[pos],pins1[pos],GPIO_PIN_SET);
        HAL_GPIO_WritePin(ports2[pos],pins2[pos],GPIO_PIN_RESET);
    }
}

void moveForward() {
    changeDirection(LF,FORWARD);
    changeDirection(RF,FORWARD);
    changeDirection(LB,FORWARD);
    changeDirection(RB,FORWARD);
}

void moveBack() {
    changeDirection(LF,BACK);
    changeDirection(RF,BACK);
    changeDirection(LB,BACK);
    changeDirection(RB,BACK);
}

void enable(uint8_t pos) {
    changeDirection(pos,cars[pos].direction);
}

void enableAll() {
    enable(LF);
    enable(RF);
    enable(LB);
    enable(RB);
}

static void disableDirection(uint8_t pos) {
    HAL_GPIO_WritePin(ports1[pos],pins1[pos],GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ports2[pos],pins2[pos],GPIO_PIN_RESET);
}

void disable(uint8_t pos) {
    disableDirection(pos);
}

void disableAll() {
    disable(LF);
    disable(RF);
    disable(LB);
    disable(RB);
}

void setSpeed(uint8_t pos,float spd) {
    if (spd < 0 || spd > MAXS)
        return;
    cars[pos].speed = spd;
    if(pos == LF)
	    TIM1->CCR1 = spd;
    else if (pos == RF)
    	TIM1->CCR2 = spd;
    else if (pos == LB)
	    TIM1->CCR3 = spd;
    else
	    TIM1->CCR4 = spd;
}

uint8_t getDirection(uint8_t pos) {
    return cars[pos].direction;
}

void setSpeedAll(float spd) {
    setSpeed(LF,spd);
    setSpeed(RF,spd);
    setSpeed(LB,spd);
    setSpeed(RB,spd);
}

float getSpeed(uint8_t pos) {
    return cars[pos].speed;
}

float getActualSpeed(uint8_t pos) {
    if (getDirection(pos) == FORWARD)
        return getSpeed(pos);
    else return  -getSpeed(pos);
}

void setActualSpeed(uint8_t pos,float speed) {
    if (speed == 0) {
        setSpeed(pos,speed);
    }
    if (speed > 0)  {
        if (getDirection(pos) != FORWARD)
            changeDirection(pos,FORWARD);
    } else {
        if (getDirection(pos) != BACK)
            changeDirection(pos,BACK);
    }
    setSpeed(pos,speed > 0 ? speed:-speed);
}

void initCar() {

    cars[0].speed = DEFAULT_SPEED;
    cars[0].direction = FORWARD;
    cars[1].speed = DEFAULT_SPEED;
    cars[1].direction = FORWARD;
    cars[2].speed = DEFAULT_SPEED;
    cars[2].direction = FORWARD;
    cars[3].speed = DEFAULT_SPEED;
    cars[3].direction = FORWARD;

    ports1[0] = LFL1_GPIO_Port;
    ports1[1] = RFL1_GPIO_Port;
    ports1[2] = LBL1_GPIO_Port;
    ports1[3] = RBL1_GPIO_Port;
    ports2[0] = LFL2_GPIO_Port;
    ports2[1] = RFL2_GPIO_Port;
    ports2[2] = LBL2_GPIO_Port;
    ports2[3] = RBL2_GPIO_Port;
    pins1[0] = LFL1_Pin;
    pins1[1] = RFL1_Pin;
    pins1[2] = LBL1_Pin;
    pins1[3] = RBL1_Pin;
    pins2[0] = LFL2_Pin;
    pins2[1] = RFL2_Pin;
    pins2[2] = LBL2_Pin;
    pins2[3] = RBL2_Pin;

    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
}