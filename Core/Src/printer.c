//
// Created by 周蜀杰 on 2020/12/22.
//

#include "printer.h"

struct Printer createPrinter(UART_HandleTypeDef*handle) {
    struct Printer printer;
    printer.handle = handle;
    return printer;
}

void PRINTER_print(struct Printer printer,char* str) {
    HAL_UART_Transmit(printer.handle,str,strlen(str),10000);
}

void PRINTER_println(struct Printer printer,char* str) {
    PRINTER_print(printer,str);
    PRINTER_print(printer,"\n");
}

char PRINTER_string[100];

void PRINTER_printInt(struct Printer printer,int v) {
    memset(PRINTER_string,0,sizeof(PRINTER_string));
    itoa(v,PRINTER_string,10);
    PRINTER_print(printer,PRINTER_string);
}

void PRINTER_printIntln(struct Printer printer,int v) {
    PRINTER_printInt(printer,v);
    PRINTER_print(printer,"\n");
}

char PRINTER_char[2] = {0,0};

void PRINTER_printChar(struct Printer printer,char c) {
    PRINTER_char[0] = c;
    PRINTER_print(printer,PRINTER_char);
}

void PRINTER_printCharln(struct Printer printer,char c) {
    PRINTER_printChar(printer,c);
    PRINTER_print(printer,"\n");
}

void PRINTER_printFloat(struct Printer printer,float f) {
    memset(PRINTER_string,0,sizeof(PRINTER_string));
    sprintf(PRINTER_string,"%f",f);
    PRINTER_print(printer,PRINTER_string);
}

void PRINTER_printFloatln(struct Printer printer,float f) {
    PRINTER_printFloat(printer,f);
    PRINTER_print(printer,"\n");
}

void PRINTER_printf(struct Printer printer,const char* str,...) {
    memset(PRINTER_string,0,sizeof(PRINTER_string));
    va_list p;
    va_start(p,str);
    vsprintf(PRINTER_string,str,p);
    PRINTER_print(printer,PRINTER_string);
    va_end(p);
}

void PRINTER_printLimited(struct Printer printer,char* str,uint32_t limited) {
    HAL_UART_Transmit(printer.handle,str,limited,10000);
}

void PRINTER_printLimitedln(struct Printer printer,char* str,uint32_t  limited) {
    PRINTER_printLimited(printer,str,limited);
    PRINTER_print(printer,"\n");
}