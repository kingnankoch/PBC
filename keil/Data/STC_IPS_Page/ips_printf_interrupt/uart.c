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

// int main(int argc, char const *argv[])
// {
    
//     return 0;
// }



void uartInit(void){
    // PCON &= 0x7F; // 0111 1111
    // 工作在方式 2  8位波特率 固定
    SCON = 0x50; // M0 M1 M2 GEN    TB8  RB8 TI RI = 0101 0000
    // T1 作为 波特率 发生器 ；工作在 方式 1 作为 8位 可重载

    //  4800 = (1/32) * (foc/ 12 )* [1/(256 - X)]
    // x = 6 TH1 = 0xFA; TL1 = 0xFA; 
    //  9600 = (1/32) * (foc/ 12 )* [1/(256 - X)]
    // x = 3
    TMOD = 0x20;// GATE_1 C/T M1_1 M0_1    GATE_0 C/T M1_0 M0_0  
    // TH1 = 0xFD; // 9600 的波特率 
    // TL1 = 0xFD;
    TH1 = 0xFA; 
    TL1 = 0xFA;
    ET1 = 0;//禁止 定时计数器 T1 中断
    TR1 = 1;//启动定时器1 
    EA = 1;//开启总中断
    ES = 1;//串口中断
} 


// void sendSBUF(){

// }


// void uart_ISR() interrput 4 using 0{
//     SBUF = ""
// }


// void uart_ISR() interrupt 4 {
//     // SBUF = ""   
//     if(TI){
//         TI = 0;
//     }
// }

// 串口 中断
// 将 SBUF 装填数据并发送后 会进入到中断的程序 中 ，
// 将 TI  清零 后，允许下一次中断 
// 新的数据 发送给 SBUF ，发送后 再次 进入中断

void uart_ISR() interrupt 4 {
    // SBUF = ""   
    if(TI){
        // DelayXms(2000); // 延时 1s
        
        DelayXms(2000);
        TI = 0;
        send(0x88);
    }
    
}

// 中断进入后 再次 进入 send

void send(unsigned char dat){

    SBUF = dat;
}


