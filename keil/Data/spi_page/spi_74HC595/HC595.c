/**
 * @file HC595.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "reg51.h"
#include "HC595.h"

int count = 8;

void hc_595_init(){
    HC595_OE = 1;
    HC595_SH_CP = 0;
    HC595_ST_CP = 0;
    HC595_DS = 0;
    HC595_OE = 0;
}

void hc_595_drive(unsigned char dat){
    unsigned char i;
    HC595_SH_CP = 0;
    HC595_ST_CP = 0;
    // dat = 1111 1100
    for (i = 0; i < count; i++)
    {
        // 准备数据 房子啊 IO 口上
        if (dat >= 0x80)
        {
            HC595_DS = 1;
        } else
        {
            HC595_DS = 0;
        }
        //上升沿 数据一位一位的移入到 移位寄存器 
        HC595_SH_CP = 0;
        HC595_SH_CP = 1;
        dat <<= 1;
    }
    //上升沿 移位寄存器的数据到存储器
    HC595_ST_CP = 0;
    HC595_ST_CP = 1;
    // 拉低提高点评抗干扰
    HC595_SH_CP = 0;
    HC595_ST_CP = 0;
    HC595_DS= 0;
}

void led_hc_595_drive(unsigned char datH, unsigned char datL){
    unsigned char i;
    unsigned char TEMP;
    TEMP = datH;
    for (i = 0; i < count; i++)
    {
        // 准备数据 房子啊 IO 口上
        if (TEMP >= 0x80)
        {
            HC595_DS = 1;
        } else
        {
            HC595_DS = 0;
        }
        //上升沿 数据一位一位的移入到 移位寄存器 
        HC595_SH_CP = 0;
        HC595_SH_CP = 1;
        TEMP <<= 1;
    }
    TEMP = datL;
    for (i = 0; i < count; i++)
    {
        // 准备数据 房子啊 IO 口上
        if (TEMP >= 0x80)
        {
            HC595_DS = 1;
        } else
        {
            HC595_DS = 0;
        }
        //上升沿 数据一位一位的移入到 移位寄存器 
        HC595_SH_CP = 0;
        HC595_SH_CP = 1;
        TEMP <<= 1;
    }
    //上升沿 移位寄存器的数据到存储器
    HC595_ST_CP = 0;
    HC595_ST_CP = 1;

}


