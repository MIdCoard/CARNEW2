//
// Created by 周蜀杰 on 2020/12/20.
//

#ifndef __USART_HANDLER_H


#define __USART_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
#include "stream.h"
void addUsartHandler(UART_HandleTypeDef ,void (*handler)());

#ifdef __cplusplus
}
#endif

#endif
