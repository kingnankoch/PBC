/**
 * @file ips_receive_string_header_communication_protocol_immediately.c
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




void uart_service(void){
    //unsigned char recv_move_index;
    if(recv_flag == 1){
        recv_flag = 0;

        // 关闭 自定义的 软件定时计数器
        // start_time = 0;
        
        sendString(recv_buf);

        switch (recv_buf[0]) {
            case 1:
                // 对数据进行即时解析 并且 在 进行反馈
                printf("led_data = 0x01");
                // sendByte(0x01);
                break;
            case 2:
                // 对数据进行即时解析 并且  进行反馈
                printf("led_data = 0x02");
                // sendByte(0x02);
                break;
            default:
                break;
        }
        

        // 发送完成后  recv_buf 清除
        clear_recv_buffer(recv_buf);
        


    }
}

int main()
{
    // 初始化 定时计数器 T1
    // timer0_init();
    uartInit();
    while (1)
    {
        uart_service();
    }
    //return 0;
}

