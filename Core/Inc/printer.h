//
// Created by 周蜀杰 on 2020/12/22.
//

#ifndef __PRINTER_H
#define __PRINTER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "usart.h"
#include "string.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

struct Printer {
    UART_HandleTypeDef*handle;
};

struct Printer createPrinter(UART_HandleTypeDef*);

void PRINTER_print(struct Printer,char*);

void PRINTER_println(struct Printer,char*);

void PRINTER_printInt(struct Printer,int);

void PRINTER_printIntln(struct Printer,int);

void PRINTER_printFloat(struct Printer,float);

void PRINTER_printFloatln(struct Printer,float);

void PRINTER_printChar(struct Printer,char);

void PRINTER_printCharln(struct Printer,char);

void PRINTER_printf(struct Printer,const char*,...);

void PRINTER_printLimited(struct Printer,char*,uint32_t);

void PRINTER_printLimitedln(struct Printer,char*,uint32_t);

#ifdef __cplusplus
}
#endif

#endif //BLUETOOCH_PRINTER_H
