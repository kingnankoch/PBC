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

        // while ( (recv_cnt >= 5 ) && (recv_move_index <= recv_cnt) )
        // {
        //     if( (buf[recv_move_index + 0] == 0x55) && (buf[recv_move_index + 1] == 0xAA) && (buf[recv_move_index + 2] == 0x55) ){
        //         if((buf[recv_move_index + 3] == 0x01)  && (buf[recv_move_index + 4] == 0x02) ){
        //             printf("type of one\r\n");
        //         } else {
        //             printf("type two\r\n");
        //         }
        //         break;
        //     }
        //     recv_move_index++;
        // }
        
        // recv_cnt = 0;
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

