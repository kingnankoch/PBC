/**
 * @file timer.h
 * @author your name (you@domain.com)
 * @brief 定时计数器 中断
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "reg51.h"
#include "timer.h"
#include "uart.h"
#include "stdio.h"



// 开启定时器 T0 中断, 因为定时器 T1 已经用做波特率发生器了
void timer0_init(void){
    // 8 位 重载 ;工作在方式 3;  时间 2ms  256 - 2
    //TMOD = 0x02;// 0000 0020  GATE  C/T M1_1 M0_1 GATE C/T M0_1 M01_0
    
    // 16 位定时计数器 工作在方式 1
    // 时间 2ms 
    TMOD = 0x012;
    TH0 = 0xFC;//(65536 - 1000)/256
    TL0 = 0x66;//(65536 - 1000)%256
    ET0 = 1;//允许定时器 T0 中断
    // EA = 1;//总中断 因为  串口中断中也有开启总中断 所以 合并为一个
    TR0 = 1;//开启定时器 T0 中断

}

// 定时器中断0   所以 interrupt 1
void timer0_ISR() interrupt 1{
    TR0 = 0;
    if(start_time == 1){
        recv_timer_cnt++; //累计 定时器计数  1ms 计数器 +1
        // 判断 定时时间 是否超过 约定的最大时间
        if (recv_timer_cnt > MAX_REV_TIME)
        {
            
            // 数据接收完成
            recv_timer_cnt = 0;//清除定时计数器 处理数据 ，清除 rev_buf
            recv_cnt = 0;
            recv_flag = 1;
        }
        
    }
    // printf("recv_timer_cnt = %d", recv_timer_cnt);
    // printf("recv_timer_cnt == %d", recv_timer_cnt );
    TH0 = 0xFC;//(65536 - 1000)/256
    TL0 = 0x66;//(65536 - 1000)%256
    TR0 = 1;//开启定时器 T0 中断
}
