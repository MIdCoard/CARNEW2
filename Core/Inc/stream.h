//
// Created by 周蜀杰 on 2020/11/27.
//

#ifndef __STREAM_H
#define __STREAM_H

#ifdef __cplusplus
extern "C" {
#endif
#include "usart.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "printer.h"
#include "usart_handler.h"

void print(char*);

void printInt(int);

void println(char*);

void printIntln(int);

void printChar(char);

void printCharln(char);

void printLimited(char*,uint32_t);

void printLimitedln(char*,uint32_t);

void printFloat(float f);

void printFloatln(float f);

char* get();

void initStream(UART_HandleTypeDef*);


#ifdef __cplusplus
}
#endif


#endif //MYFIRST_STREAM_H
