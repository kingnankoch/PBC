/**
 * @file I2C.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief I2C 的时序与逻辑 
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "I2C.h"


//延时
void IIC_delay(void)
{
	u8 t=1;
	while(t--);
}

// ------- 起始信号 --------
// 89C51 没有I2C， 所以使用模拟时序操作 I2C
// SCL 在高电平过程中， SDA 有下降沿，这时 开启了I2C
// void I2C_star() {
//     SDA = 1;
//     SCL = 1;
//     delay(5); // 延时5us, 时间要大于 4.7us， 
//     SDA = 0; // 将SDA处于低电平，开始 I2C
//     delay(5); // 时间要大于额 4us
//     SCL = 0;
// }
void I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Clr();
	IIC_delay();
	OLED_SCL_Clr();
}


// -------  结束信号 ---------
// void I2C_stop() {
//     SCL = 0;
//     SDA = 0;
//     delay(5);
//     SCL = 1;
//     delay(5);
//     SDA = 1; // 当 SCL 为高电平的情况下， SDA为高电平；
//     delay(5);
//     SDA = 0;
// }
void I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Set();
}


// ---- 等待信号响应 -----
// // 发送非应答位
// void unAsk() {
//     SDA = 1; // 当SCL为高电平的时候，SDA为1，所以 非应答为 1
//     delay(5); // 持续时间 大于 4us
//     SCL = 1;
//     delay(5); // 持续时间 大于 4us
//     SCL = 0;
//     delay(5); // 持续时间 大于 4us
//     SDA = 0;
// }
void I2C_WaitAck(void) //测数据信号的电平
{
	OLED_SDA_Set();
	IIC_delay();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SCL_Clr();
	IIC_delay();
}




//写入一个字节
// void sendByte(unsigned char dat){
//     unsigned char i;
//     SCL = 0;
//     for (i = 0; i < 8; i++)
//     {
        
//         SDA = dat & 0x80;
//         SCL = 1;
//         delay(5);
//         SCL = 0;
//         dat <<= 1;
//     }
    
// }

void Send_Byte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		OLED_SCL_Clr();//将时钟信号设置为低电平
		if(dat&0x80){//将dat的8位从最高位依次写入
			OLED_SDA_Set();
        }
		else {
			OLED_SDA_Clr();
        }
		IIC_delay();
		OLED_SCL_Set();
		IIC_delay();
		OLED_SCL_Clr();
		dat<<=1;
  }
}







