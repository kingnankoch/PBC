#ifndef __HC595_H // 先测试是否被宏定义过
#define __HC595_H // 如果 __I2C_H 没有被宏定义过，定义 __I2C_H


sbit HC595_SH_CP = P1^2;
sbit HC595_DS    = P1^3;

sbit HC595_ST_CP = P1^4;
sbit HC595_OE    = P1^5;

void hc_595_init();
void hc_595_drive(unsigned char dat);
void led_hc_595_drive(unsigned char datH, unsigned char datL);


#endif