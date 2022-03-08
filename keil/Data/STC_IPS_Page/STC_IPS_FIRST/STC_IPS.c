/**
 * @file STC_IPS.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief STC-IPS 串口调试
 * @version 0.1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "reg51.h"
#include "delay.h"


void UartInit(void);


unsigned char dat = 5;


int main()
{
    /* code */
    UartInit();
    
    while (1)
    {
        /* code */
        //SBUF=0x88;// 10 位异步串口 通信  0 88H 1
        // SBUF = '1';
        SBUF = dat + '0';
        while (!TI);
        TI = 0;
        DelayXms(1000); // 延时 1s

    }
    
    // return 0;
}

void UartInit(void)		//4800bps@11.0592MHz
{
	//PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率  SM0 SM1 SM2 REN TB8 RB8 TI RI  =  0101 0000
	TMOD &= 0x0F;		//设置定时器1模式位
	TMOD |= 0x20;		//设置定时器模式 8 位自动重载 方式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
}





