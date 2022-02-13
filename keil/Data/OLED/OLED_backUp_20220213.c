/**
 * @file OLED.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief 此项目 主要学习 OELD 的使用
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include"reg51.h"
#include"intrins.h"
// #include "stdio.h"
#include<stdio.h> 
#include <stdlib.h> 


// ----- I2C 的接口 ------
sbit SDA = P3^0;
sbit SCL = P3^1;

// 延时函数
void delay(num) {
    int i = 0;
    for (i = 0; i < num; i++)
    {
        _nop_(); // _nop_(); 代表运行一个机器周期. 如果这个单片机的晶振是12M的，那么这调代码会运行1US
        // printf("%d",num);
    }
}

// 89C51 没有I2C， 所以使用模拟时序操作 I2C
// SCL 在高电平过程中， SDA 有下降沿，这时 开启了I2C
void I2C_star() {
    SDA = 1;
    SCL = 1;
    delay(5); // 延时5us, 时间要大于 4.7us， 
    SDA = 0; // 将SDA处于低电平，开始 I2C
    delay(5); // 时间要大于额 4us
    SCL = 0;

}

// 停止 202020209 修复 停止的逻辑后，可以自由储存信息了
void I2C_stop() {
    SCL = 0;
    SDA = 0;
    delay(5);
    SCL = 1;
    delay(5);
    SDA = 1; // 当 SCL 为高电平的情况下， SDA为高电平；
    delay(5);
    SDA = 0;
}

// 发送应答位 
void sendAck(void) {
    SDA = 0; // 当SCL为高电平的时候，SDA为0，所以应答为 0
    delay(5); // 持续时间 大于 4us
    SCL = 1;
    delay(5); // 持续时间 大于 4us
    SCL = 0;
    delay(5); // 持续时间 大于 4us
    // delay(1);
    SDA = 1;
    delay(5); // 持续时间 大于 4us
}


// 发送非应答位
void unAsk() {
    SDA = 1; // 当SCL为高电平的时候，SDA为1，所以 非应答为 1
    delay(5); // 持续时间 大于 4us
    SCL = 1;
    delay(5); // 持续时间 大于 4us
    SCL = 0;
    delay(5); // 持续时间 大于 4us
    SDA = 0;
}


// 接受应答信号
bit recvAck() {
    bit flat;
    SCL = 1;
    delay(5);
    //等待被选中的器件返回确认应答 ：如果有应答 那么 器件会通过 SDA 这条线传回数据，这时单片机的SDA： P1^0 会有电平的 变化
    flat = SDA; // 当 SCL为 高电平的时候 检测 SDA 线上的数据
    SCL = 0; // 数据接受完成后， 将时钟电平拉低
    delay(5);
    return(flat); // 为 0 时 是应答 为1 时 是非应答
}



void oledWritedCmd(cmdWrite){
    I2C_star();
    oledWriteByte(0x78); // 发送从机地址 设备地址  0111100 r/w 1=Read 0= wirte ；最终 01111000 = 0x78
    recvAck();
    //  --- 开始控制字节 --
    oledWriteByte(0x00);// Co+D/C+0000000  co 0:后面跟随字节，一个字节一个字节发送    ;  D/C  0:命令 1:数据 ; 写命令： 0000 0000
    recvAck();

    // --- 发送的 命令信息 ---
    oledWriteByte(cmdWrite);
    recvAck();

    I2C_stop();
}


void oledWritedData(dataWrite){
    I2C_star();
    oledWriteByte(0x78); // 发送从机地址 设备地址  0111100 r/w 1=Read 0= wirte ；最终 01111000 = 0x78
    recvAck();
    //  --- 开始控制字节 --
    oledWriteByte(0x40);// Co+D/C+0000000  co 0:后面跟随字节，一个字节一个字节发送    ;  D/C  0:命令 1:数据 ; 写数据： 0100 0000
    recvAck();

    // --- 发送的 数据信息 ---
    oledWriteByte(dataWrite);
    recvAck();

    I2C_stop();
}



// 显示内容

void show() {

    oledWritedCmd(0x20); // 确定寻址模式 这个是双字节命令，先要发送 0x20 再发送 0x02  以REST模式
    oledWritedCmd(0x02);
    // 第几行
    oledWritedCmd(0xb0 + i);// 10110+ X2 + X1 + X0 ，X2 X1 X0 代表其中的8个page页面， 000-111 ；也就是说 在128*64的屏幕上，每一列有64个像素点，以8个字节为单位，可以分出 8块，0~7

    //确定第几列
    oledWritedCmd(0x00); //设置显示 位置 一列低地址 ？？
    oledWritedCmd(0x10); //设置显示 位置 一列高地址 ？？

    oledWritedData(0x00); // 8个led全部熄灭
    oledWritedData(0xff); //8个led全部点亮


}



int main()
{
    
    return 0;
}






