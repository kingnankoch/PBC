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





unsigned char dat = 5;
int main()
{

    uartInit();
    SBUF = dat + '0';
    // while (1)
    // {
    //     /* code */
    //     //SBUF=0x88;// 10 位异步串口 通信  0 88H 1
    //     // SBUF = '1';
    //     SBUF = dat + '0';
    //     // SBUF = 0x88;
    //     // while (!TI);
    //     // TI = 0;
    //     DelayXms(2000); // 延时 1s
    // }
    // return 0;
}

