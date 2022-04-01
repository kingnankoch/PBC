/**
 * @file ips_receive.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "reg51.h"
#include "stdio.h"
#include "uart.h"

int main()
{
    uartInit();
    printf("hellow world printf\r\n");
    while (1)
    {
        // 接收到的没数据
        if(receive_data == 3){
            break;
        }
    }
    printf("rev data\r\n");
    
    return 0;
}

