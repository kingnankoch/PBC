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


// int main(int argc, char const *argv[])
// {
    
//     return 0;
// }



void uartInit(void){
    // PCON &= 0x7F // 0111 1111
    // 工作在方式 2  8位波特率 固定
    SCON = 0x50;// M0 M1 M2 GEN    TB8  RB8 TI RI = 0101 0000
    ES = 1;//串口中断

    // T1 作为 波特率 发生器 ；工作在 方式 1 作为 8位 可重载

    //  4800 = (1/32) * (foc/ 12 )* [1/(256 - X)]
    // x = 6 TH1 = 0xFA; TL1 = 0xFA;
    //  9600 = (1/32) * (foc/ 12 )* [1/(256 - X)]
    // x = 3
    TMOD = 0x20;// GATE_1 C/T M1_1 M0_1    GATE_0 C/T M1_0 M0_0  
    TH1 = 0xFD; // 4800 的波特率 
    TL1 = 0xFD;
    ET1 = 0;//禁止 定时计数器 T1 中断
    TR1 = 1;//启动定时器1 
    EA = 1;//开启总中断
} 


// void sendSBUF(){

// }


void uart_ISR() interrput 4 using 0{
    SBUF = ""
}




