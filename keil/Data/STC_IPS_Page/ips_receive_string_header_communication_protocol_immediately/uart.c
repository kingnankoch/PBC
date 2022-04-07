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
        // start_time = 1;
        // if (recv_cnt < MAX_REV_NUM)
        // {
        //     recv_buf[recv_cnt] = SBUF;//接收数据缓冲区
        //     recv_cnt++;
        // } else {
        //    recv_cnt = MAX_REV_NUM;
        // }
        // // 每接收一帧数据 后 都清零, 把定时计数 清零
        // // 但当 不再进入到串口中断的时候，没有新的数据发送 过来, 在定时器中 会不断累加， 超过 一定值的时候，判断接收的此数据包 结束
        // recv_timer_cnt = 0;
        // recv_data = SBUF;


        switch (machine_step) {

            case 0:
                recv_buf[0] = SBUF;
                if(recv_buf[0] == 0xAA){
                    machine_step = 1;
                    // recv_cnt = 2;
                } else{
                    machine_step = 0;
                }
                break;

            case 1:
                recv_buf[1] = SBUF;
                if(recv_buf[1] == 0x55){
                    machine_step = 2;
                    recv_cnt = 2;
                } else{
                    machine_step = 0;
                }
                break;

            case 2:
                recv_buf[recv_cnt] = SBUF;
                // printf("recv_buf[recv_cnt] = %d", recv_buf[recv_cnt]);
                recv_cnt++;
                if(recv_cnt > 4){
                    machine_step = 3;
                } else {
                    machine_step = 2;
                }
                break;

            case 3:
                recv_buf[recv_cnt] = SBUF;
                // printf("recv_buf[recv_cnt] = %d", recv_buf[recv_cnt]);
                if(recv_buf[recv_cnt] == 0x0D) {
                    switch (recv_buf[2]) {
                        case 1:
                            led_data = recv_buf[3];
                            led_data = led_data << 8;
                            led_data = led_data + recv_buf[4];
                            // printf("led_data = %d", led_data);
                            // 对数据进行即时解析 并且 在第六位 进行反馈
                            recv_buf[6] = 0x01;
                            break;
                        case 2:
                            // 对数据进行即时解析 并且 在第六位 进行反馈
                            // printf("0x02");
                            recv_buf[6] = 0x02;
                            break;
                        default:
                            break;
                    }
                    
                    machine_step = 0;
                    recv_cnt = 0;
                    recv_flag = 1;
                }

                break;

            default:
                break;
        }

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
