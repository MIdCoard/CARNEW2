#include "tim_handler.h"

struct Handler {
    TIM_HandleTypeDef tim;
    void (*handler[10])();
    int handlerSize;
};

static int handlerPos = 0;

struct Handler handlers[16];

static int captureHandlerPos = 0;

struct Handler captureHandlers[16];

void addHandler(TIM_HandleTypeDef tim,void (*handler)() ) {
    int flag = 0;
    for (int i = 0;i<handlerPos;i++)
        if (handlers[i].tim.Instance == tim.Instance) {
            if (handlers[i].handlerSize < 10)
                handlers[i].handler[handlers[i].handlerSize++] = handler;
            else println("Error Handle!!!");
            flag = 1;
        }
    if (!flag) {
        struct Handler h;
        h.tim = tim;
        h.handlerSize = 0;
        h.handler[h.handlerSize++] = handler;
        handlers[handlerPos++] = h;
    }
}

void addCaptureHandler(TIM_HandleTypeDef tim,void (*handler)() ) {
    int flag = 0;
    for (int i = 0;i<captureHandlerPos;i++)
        if (captureHandlers[i].tim.Instance == tim.Instance) {
            if (captureHandlers[i].handlerSize < 10)
                captureHandlers[i].handler[captureHandlers[i].handlerSize++] = handler;
            else println("Error Capture Handle!!!");
            flag = 1;
        }
    if (!flag) {
        struct Handler h;
        h.tim = tim;
        h.handlerSize = 0;
        h.handler[h.handlerSize++] = handler;
        captureHandlers[captureHandlerPos++] = h;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    for (int i = 0;i<handlerPos;i++)
        if (htim->Instance == handlers[i].tim.Instance)
            for (int j = 0;j<handlers[i].handlerSize;j++)
                handlers[i].handler[j]();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef * htim) {
    for (int i = 0;i<captureHandlerPos;i++)
        if (htim->Instance == captureHandlers[i].tim.Instance)
            for (int j = 0;j<captureHandlers[i].handlerSize;j++)
                captureHandlers[i].handler[j]();
}


