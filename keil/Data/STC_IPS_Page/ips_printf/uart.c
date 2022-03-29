/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
#include "reg51.h"
#include "uart.h"

#include "delay.h"


void uartInit(void){
    PCON &= 0x7F; // & 0111 1111
    // 串口 中断  8位 无教验位  波特率 
    SCON = 0x50;//  M0 M1 M2  GEN  TB8 RB8 TI RI  = 0101 0000
    ES = 1;// 串行口中断
    // 定时器 T1  工作在方式 3 8位可重载
    TMOD = 0x20;// GATE C/T M1 M0  GATE C/T M1 M0  = 0010 0000
    // 波特率 4800
    TH1 = 0xFA;
    TH1 = 0xFA;
    ET1 = 0;// 禁止定时器 中断 
    EA = 1;//开启总中断
    TR1 = 1;// 启动定时器 
}


// 方式 4 串口中断
void uart_ISR() interrupt 4 {
    if(TI){
        DelayXms(2000);
        TI = 0;
        sendSBUF(0x87);
    }
}


void sendSBUF(unsigned char dat){
    SBUF = dat;
}

