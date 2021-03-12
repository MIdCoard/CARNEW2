#include "stream.h"

struct Printer printer;

int STREAM_hasData = 0;

char STREAM_tempData[1024];

char STREAM_data[10000];

int STREAM_dataPos = 0;

static void handleGet() {
    HAL_UART_Receive_IT(&huart1, STREAM_tempData, 1);
    while(!STREAM_hasData) {}
    STREAM_hasData = 0;
    if (STREAM_tempData[0] != '\n') {
        STREAM_data[STREAM_dataPos++] = STREAM_tempData[0];
        handleGet();
    }
    else {
        STREAM_data[STREAM_dataPos++] = '\n';
        STREAM_data[STREAM_dataPos] = '\0';
    }
}

char* get() {
    STREAM_hasData = 0;
    handleGet();
    STREAM_dataPos = 0;
    return STREAM_data;
}

void handleStream() {
    STREAM_hasData = 1;
}

void print(char* str) {
    PRINTER_print(printer,str);
}

void printInt(int v) {
    PRINTER_printInt(printer,v);
}

void println(char* str) {
    PRINTER_println(printer,str);
}

void printIntln(int v) {
    PRINTER_printIntln(printer,v);
}

void printChar(char c) {
    PRINTER_printChar(printer,c);
}

void printCharln(char c) {
    PRINTER_printCharln(printer,c);
}

void printLimited(char* str,uint32_t limited) {
    PRINTER_printLimited(printer,str,limited);
}

void printLimitedln(char* str,uint32_t limited) {
    PRINTER_printLimitedln(printer,str,limited);
}

void printFloat(float f) {
    PRINTER_printFloat(printer,f);
}

void printFloatln(float f) {
    PRINTER_printFloatln(printer,f);
}

void initStream(UART_HandleTypeDef * serialPrinter) {
    printer = createPrinter(serialPrinter);
    addUsartHandler(*serialPrinter,handleStream);
}
