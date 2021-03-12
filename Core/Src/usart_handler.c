//
// Created by 周蜀杰 on 2020/12/20.
//
#include "usart_handler.h"

struct UsartHandler {
    UART_HandleTypeDef usart;
    void (*handler[10])();
    int handlerSize;
};

uint8_t usartHandlerPos = 0;

struct UsartHandler usartHandlers[10];

void addUsartHandler(UART_HandleTypeDef usart,void (*handler)()) {
    if (usartHandlerPos < 10) {
        struct UsartHandler h;
        h.usart = usart;
        h.handlerSize = 0;
        h.handler[h.handlerSize++] = handler;
        usartHandlers[usartHandlerPos++] = h;
    }
    else println("Error Usart Handle!!!");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * handleTypeDef) {
    for (int i = 0;i<usartHandlerPos;i++)
        if (handleTypeDef->Instance == usartHandlers[i].usart.Instance)
            for (int j = 0;j<usartHandlers[i].handlerSize;j++)
                usartHandlers[i].handler[j]();
}