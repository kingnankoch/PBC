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

#include "CRC16.h"

#define LOCAL_ADDRESS 0x01

unsigned char crc;
unsigned char crch;
unsigned char crcl;

unsigned char i;


// 发送的 数据为  01 01 20 24 C3 00  但是觉得不太对

void uart_service(void){
    //unsigned char recv_move_index;
    if(recv_flag == 1){
        recv_flag = 0;

        // 关闭 自定义的 软件定时计数器
        start_time = 0;
        
        // sendString(recv_buf);

        // switch (recv_buf[0]) {
        //     case 1:
        //         // 对数据进行即时解析 并且 在 进行反馈
        //         printf("led_data = 0x01");
        //         // sendByte(0x01);
        //         break;
        //     case 2:
        //         // 对数据进行即时解析 并且  进行反馈
        //         printf("led_data = 0x02");
        //         // sendByte(0x02);
        //         break;
        //     default:
        //         break;
        // }

        // for (i = 0; i < recv_cnt; i++)
        // {
        //     sendByte(recv_buf[i]);
        // }

        if(recv_buf[0] != LOCAL_ADDRESS){
            return;
        }
        // 开始CRC 校验
        crc = GetCRC16(recv_buf, 4);
        // 取出 高位 和 低位
        crch = crc >> 8;
        crcl = crc & 0xFF;
        // printf("crc = %d \r\n", crc);
        // printf("crch = %d \r\n", crch);
        // printf("crcl = %d \r\n", crcl);
        // sendByte(crc);
        // sendByte(crch);
        // sendByte(crcl);
        // 如果 
        if( (recv_buf[recv_cnt - 1] != crch) || (recv_buf[recv_cnt - 2] != crcl) ){
            // recv_buf[1] = recv_buf[1] | 0x80;
            crc = GetCRC16(recv_buf, 4);
            recv_buf[4] = crc & 0xFF;
            recv_buf[5] = crc >> 8;
            
            for (i = 0; i < recv_cnt; i++)
            {
                sendByte(recv_buf[i]);
            }
            // // sendByte(0x06);
            recv_cnt = 0;
            return;
        }
        
        switch (recv_buf[1]) {
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
        recv_cnt = 0;
        


        
        // 发送完成后  recv_buf 清除
        clear_recv_buffer(recv_buf);
        


    }
}

int main()
{
    // 初始化 定时计数器 T1
    timer0_init();
    uartInit();
    while (1)
    {
        uart_service();
    }
    //return 0;
}

