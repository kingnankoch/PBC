/**
 * @file ips_printf.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief 串口发送一串数据及printf重定向
 * @version 0.1
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "reg51.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

unsigned char num = 88;
unsigned int longNum = 15888;
float floatNum = 1.888;

int main(void)
{
    uartInit();
    DelayXms(1000);
    // sendByte(0x88);
    sendString("hellow world1\r\n");

    printf("hellow world printf\r\n");
    printf("num16 = %d\r\n", num);
    printf("num = %bd\r\n", num);
    
    printf("longNum = %u\r\n", longNum);

    printf("floatNum = %f\r\n", floatNum);
    printf("floatNum = %g\r\n", floatNum);
    return 0;
}


