/**
 * @file testPrintf.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief  本项目主要学习一下 printf 的用法 ，同时 会学习一下  goto 的用法， 以及之前没有完全搞清楚的 _at_
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include"reg51.h"
#include"intrins.h"
#include "stdio.h"
//#include<stdio.h> 
//#include <stdlib.h> //随机数

unsigned char i = 20;

unsigned int C = 20;
// --- star -- 此处学习一下 _at_0x55  的写法 ；暂时不清楚具体代表的意思 ----



// unsigned char mem[4] _at_0x55; //书上说 : 发送缓冲区的首地址(我的理解为，将mem[4] 的存储的地址指针指向 0x55)

// unsigned char men[4] = {0x41, 0x42, 0x43,0x44}; // 向0x55的地址 存入 四个数据（问题是如果存不下怎么办？？？）

// 现在这样写就可以了，保证代码不报错，但是是否存入了
//unsigned char men[4] _at_ 0x55;
//unsigned char men[4] = {0x41, 0x42, 0x43,0x44};


//  -----------  end --------


// testGoTo(){

// }



// 这段用于学习 goto
// unsigned char I2C_SendByte(unsigned char dat, unsigned char ack)
// {
 
 
 
// 	unsigned char a = 0,b = 0;//最大255，一个机器周期为1us，最大延时255us。
// Replay:
//     b = 0 ;			
// 	for(a=0; a<8; a++)//要发送8位，从最高位开始
// 	{
// 		SDA = dat >> 7;	 //起始信号之后I2C_SCL=0，所以可以直接改变I2C_SDA信号
// 		dat = dat << 1;
// 		Delay10us();
// 		SCL = 1;
// 		Delay10us();//建立时间>4.7us
// 		SCL = 0;
// 		Delay10us();//时间大于4us		
// 	}
 
// 	SDA = 1;
// 	Delay10us();
// 	SCL = 1;
// 	while(SDA && (ack == 1))//等待应答，也就是等待从设备把I2C_SDA拉低
// 	{
// 		b++;
// 		if(b > 200)	 //如果超过200us没有应答发送失败，或者为非应答，表示接收结束
// 		{
// 			SCL = 0;
// 			Delay10us();
// 		//	return 0;
// 			goto Replay ;   //如果超过200us没有应答则发送失败，或者为非应答，这时候系统启动重发机制
// 							//使用goto语句返回到上面接着发
// 		}
// 	}
 
// 	SCL = 0;
// 	Delay10us();
//  	return 1;		
// }
// ————————————————
// 版权声明：本文为CSDN博主「勿舛」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/zbl12345678910/article/details/106029054


// 延时函数
void delay(num) {
    int i = 0;
    for (i = 0; i < num; i++)
    {
        _nop_(); // _nop_(); 代表运行一个机器周期. 如果这个单片机的晶振是12M的，那么这调代码会运行1US
    }
}

// 串口初始化
void urtInit(){
    TMOD |= 0x20;  // 0010 0000 使用定时器1 
    TH1 = 0xFD; // 设置 波特率 9600 // 时钟频率11.0592M
    TL1 = 0xFD;
    SCON = 0x50; // 0101 0000  设置方式1  8位异步通信方式  串口寄存器 波特率可变 
    PCON = 0; //SMOD=1 波特率加倍 这里不加倍

    ES = 1; // 串口中断
    EA = 1; // 开启总中断
    TR1 = 1; //开启定时器1


}


// 单片机 的主函数不能传递参数
int main()
{
    urtInit();
    TI = 1; // 如果想使用 printF 函数 必须TI = 1
	// while(!TI); //  循环检测是否发送完成 如果发送完成 TI 会被置为1， 需要再次发送 需要手动置为 0；
	// 发送完成之后 设置 TI = 0 这样第二次就可以发送
    
    while (C)
    {
        printf ("Hello World\n");
        printf ("%d \n", C); //C是 int 所以打印出来的会是数字
        printf ("%d \n", i); // 两种数据 char 类型的打印出的会是 二进制
        
        delay(50000000000);
        C--;
    }
	return 0;
}

