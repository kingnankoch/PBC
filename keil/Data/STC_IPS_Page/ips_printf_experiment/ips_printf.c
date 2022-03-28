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


// 中断的方式实现 发送一串数据

int main()
{

    // 串口初始化
    SCON = 0x50; // 串口控制器 方式1  SM2 = 0, REN =1, 
    // SMOD = 0; //波特率不加倍
    TMOD = 0x20;//
    // 串口总中断
    // EA = 1;
    // ES= 1;
    TH1 = (65535 - 3);
    TL1 = (65535 - 3);
    TE1 = 0;//禁止定时器1 中断
    TR1 = 1;//开启定时器1
    return 0;
}

void UartInit(void){
     // 串口初始化
    SCON = 0x50; // 串口控制器 方式1  SM2 = 0, REN =1, 
    // SMOD = 0; //波特率不加倍
    TMOD = 0x20;//
    // 串口总中断
    // EA = 1;
    // ES= 1;
    TH1 = (65535 - 3);
    TL1 = (65535 - 3);
    TE1 = 0;//禁止定时器1 中断
    TR1 = 1;//开启定时器1
}

void Uart_intupper(void) interrupt 1{



}
