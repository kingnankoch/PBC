/**
 * @file ips_receive_timeInterrupt.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "reg51.h"
#include "uart.h"
#include "timer.h"
#include "stdio.h"
// #include <string.h>


int main()
{

    // 初始化 定时计数器 T1
    timer0_init();
    uartInit();
    while (1)
    {
        if(recv_flag == 1){
            recv_flag = 0;

            // 关闭 自定义的 软件定时计数器
            start_time = 0;
            sendString(recv_buf);
            // 发送完成后  recv_buf 清除
            clear_recv_buffer(recv_buf);


        }
    }
    //return 0;
}
