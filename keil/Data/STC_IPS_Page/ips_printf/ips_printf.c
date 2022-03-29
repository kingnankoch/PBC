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

int main()
{
    uartInit();
    DelayXms(1000);
    sendSBUF(0x88);
    return 0;
}
