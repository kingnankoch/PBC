/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "reg51.h"
#include "uart.h"
#include "stdio.h"



unsigned char receive_data;



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
    // if(TI){
    //     // DelayXms(2000);
    //     DelayXms(50);
    //     TI = 0;
    //     // sendByte(0x87);
        
    // }
    if (RI)
    {
        RI = 0;
        // 接收数据 
        receive_data = SBUF;
        // receive_data = receive_data +1;
        // SBUF = receive_data;
        // printf("%bd", receive_data);
    }
    if(TI){
        TI = 0;
    }
    
}


void sendByte(unsigned char dat){
    SBUF = dat;
    while (!TI); 
    // DelayXms(200);
    // TI = 0;
    
}

void sendString(unsigned char * dat){
    while (* dat != '\0' )
    {
        sendByte(* (dat++));
    }
}

// 重定向 printf 函数
char putchar(char c){
    sendByte(c);
    return c;
}

