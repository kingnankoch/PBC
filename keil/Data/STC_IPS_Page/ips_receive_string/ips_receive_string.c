/**
 * @file ips_receive_string.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "reg51.h"
#include "uart.h"
#include "stdio.h"
#include <string.h>


 unsigned char i;

int main()
{
    uartInit();
    printf("receive string of message\r\n");
    
    while (1)
    {
        if(recv_flag == 1){
            recv_flag = 0;
            // 发送会给上位机
            // sendString(recv_buf);



            // for (i = 0; i < recv_buf_length; i++)
            // {
            //     sendByte(recv_buf[i]);
            // }
            // printf("sizeof == %d", strlen(recv_buf) );
            for (i = 0; i < strlen(recv_buf); i++)
            {
                sendByte(recv_buf[i]);
            }


        }
    }
    // return 0;
}

