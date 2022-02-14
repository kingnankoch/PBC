#ifndef __I2C_H // 先测试是否被宏定义过
#define __I2C_H // 如果 __I2C_H 没有被宏定义过，定义 __I2C_H


#include "reg51.h"

#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int



sbit OLED_SCL=P1^0;//SCL
sbit OLED_SDA=P1^1;//SDA
// sbit OLED_RES =P1^2;//RES

#define OLED_SCL_Clr() OLED_SCL = 0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

// #define OLED_RES_Clr() OLED_RES=0
// #define OLED_RES_Set() OLED_RES=1

// 声明函数 但是为什么要声明,因为要在OLED.c中调用，所以要声明
void IIC_delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(unsigned char dat);

#endif