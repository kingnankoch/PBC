/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */





#include "reg51.h"
#include "uart.h"
#include "stdio.h"



unsigned char start_time = 0;
unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt = 0;
unsigned char recv_timer_cnt;

unsigned char recv_flag;
unsigned char machine_step = 0;

unsigned char led_data;


unsigned char sum_check = 0;
unsigned char xor_check = 0;
unsigned char recv_data;


void uartInit(void) {
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

    
    if (RI)
    {
        RI = 0;
        // 接收一帧数据的时候  , 打开 软件 定时计数器(自定义的计数器)
        start_time = 1;
        if (recv_cnt < MAX_REV_NUM)
        {
            recv_buf[recv_cnt] = SBUF;//接收数据缓冲区
            recv_cnt++;
        } else {
           recv_cnt = MAX_REV_NUM;
        }
        // 每接收一帧数据 后 都清零, 把定时计数 清零
        // 但当 不再进入到串口中断的时候，没有新的数据发送 过来, 在定时器中 会不断累加， 超过 一定值的时候，判断接收的此数据包 结束
        recv_timer_cnt = 0;
        // recv_data = SBUF;





    }
    if(TI){
        // DelayXms(200);
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

// 清除 recv_buffer 
void clear_recv_buffer(unsigned char * buf ){
    unsigned char i;
    for (i = 0; i < MAX_REV_NUM; i++)
    {
        buf[i]  = 0;
    }
    

}
