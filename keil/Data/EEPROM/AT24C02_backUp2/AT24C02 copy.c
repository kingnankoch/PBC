/**
 * @file AT24C02.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief 可以电擦除的 内部储存器， 断电不消失;使用 I2C的方式进行数据存储
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include"reg51.h"
#include"intrins.h"
#include "stdio.h"

// ----- I2C 的接口 ------
sbit SDA = P3^0;
sbit SCL = P3^1;

//  ----- 按钮 ---
sbit button1 = P1^0;



// ---- 测试写入的数据 --
unsigned char testData[] = {2, 6, 8, 7};
unsigned char bufferData[]= {7, 3, 1, 8};



// --- star -- 此处学习一下 _at_0x55  的写法 ；暂时不清楚具体代表的意思 ----



// unsigned char mem[4] _at_0x55; //书上说 : 发送缓冲区的首地址(我的理解为，将mem[4] 的存储的地址指针指向 0x55)

// unsigned char men[4] = {0x41, 0x42, 0x43,0x44}; // 向0x55的地址 存入 四个数据（问题是如果存不下怎么办？？？）
//  -----------  end --------




// 初始化 AT24C02 
// void initAT24C02() {
//     _nop_();
// }


// 使用数字灯 展示读取出的文字
char segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};



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

// 停止
void I2C_stop() {
    SCL = 1;
    SDA = 0;
    delay(5);
    SDA = 1; // 当 SCL 为高电平的情况下， SDA为高电平；
    delay(5);
    SCL = 0;
}

// 发送应答位 
void sendAck(void) {
    SDA = 0; // 当SCL为高电平的时候，SDA为0，所以应答为 0
    SCL = 1;
    delay(5); // 持续时间 大于 4us
    SCL = 0;
    // delay(1);
    SDA = 1;
}

// void sendAck(bit ask) {
//     SDA = ask; // 当SCL为高电平的时候，SDA为0，所以应答为 0
//     SCL = 1;
//     delay(5); // 持续时间 大于 4us
//     SCL = 0;
//     delay(5);
//     
// }

// 发送非应答位
void unAsk() {
    SDA = 1; // 当SCL为高电平的时候，SDA为1，所以 非应答为 1
    SCL = 1;
    delay(5); // 持续时间 大于 4us
    SCL = 0;
    SDA = 1;
}


// 接受应答信号
bit recvAck() {
    unsigned char flat;
    SCL = 1;
    delay(5);
    //等待被选中的器件返回确认应答 ：如果有应答 那么 器件会通过 SDA 这条线传回数据，这时单片机的SDA： P1^0 会有电平的 变化
    flat = SDA; // 当 SCL为 高电平的时候 检测 SDA 线上的数据
    SCL = 0; // 数据接受完成后， 将时钟电平拉低
    delay(5);
    return flat; // 为 0 时 是应答 为1 时 是非应答
}




// 单片机向 器件发送信号
void sendByte(unsigned char dat){
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        
        SDA = dat & 0x80;
        SCL = 1;
        delay(5);
        SCL = 0;
        dat <<= 1;
    }
    
}

bit readByte(){
    unsigned char i;
    unsigned char bufferData;
    for (i = 0; i < 8; i++)
    {
        bufferData <<= 1;
        SCL = 1;
        delay(5);
        bufferData |= SDA; // 若SDA = 1， bufferData = 0000 0000 ； bufferData |= SDA , bufferData = 0000 0001 ; bufferData <<=1, bufferData = 0000 0010 ; 
        SCL = 0;
        delay(5);
        
    }
    return bufferData;
    
}


/**
 * @brief 写操作步骤
 * 1、单片机发出起始信号 :  I2C_star
 * 2、器件寻址操作 1010 A0 A1 A2 W/R  (寻址写: 1010 0000)  
 * 3、等待被选中的器件返回确认应答
 * 4、单片机完成片内地址操作  (首地址： 00H)
 * 5、器件返回确认应答（或非应答）
 * 
 * 单片机发送数据字节
 * 器件产生应答
 * 单片机发出停止信号 P :  I2C_stop
 * 
 * 
 */

// 单片机 写
void AT24C02_write(){
    unsigned char i;
    bit flat;
    I2C_star(); //起始信号
    sendByte(0xa0);// 发送设备地址 + 写信号 (1010 0000)
    // sendByte(0xa2);// 发送设备地址 + 写信号 (1010 0000)
    flat = recvAck(); //应答
    sendByte(0x30); // 发送储存单地址
    flat = recvAck(); //应答

    // 开始写入数据
    for (i = 0; i < 4; i++)
    {
        sendByte(testData[i]);
        flat = recvAck(); //应答
        if(flat) break;
    }
    I2C_stop(); // 停止
}






/**
 * @brief 当前地址读操作
 * 1、单片机发出起始信号 :  I2C_star
 * 2、器件寻址读操作 1010 A0 A1 A2 W/R  (寻址读: 1010 0001)  
 * 3、等待被选中的器件返回确认应答（或非应答）
 * 4、器件发送数据字节
 * 5、单片机回复复应答
 * 6、单片机发出停止信号 P :   I2C_stop
 * 
 * @return int 
 */



/**
 * @brief 随机读 : 读多个字节
 * 单片机发出起始信号 :  I2C_star
 * 单片机完成 器件寻址写操作 （伪写）
 * 等待被选中的器件返回确认应答（或非应答）
 * 单片机完成 数据地址写操作 （伪写）
 * 等待被选中的器件返回确认应答（或非应答）
 * 
 * 单片机发出起始信号 :  I2C_star
 * 单片机完成 器件寻址 读操作
 * 等待被选中的器件返回确认应答（或非应答）
 * 
 * 器件发送数据字节
 * 单片机产生应答
 * 
 * 单片机发出非应答及停止信号 P :   I2C_stop
 * 
 * 
 * @return int 
 */



// 随机读
void AT24C02_read() {
    unsigned char i;
    bit flat;
    I2C_star();
    sendByte(0xa0);// 发送设备地址 + 写信号 (1010 0000)
    flat = recvAck(); //应答
    sendByte(0x30); // 发送储存单地址
    flat = recvAck(); //应答

    I2C_star();
    sendByte(0xa1); // 发送设备地址 + 写信号 (1010 0001)
    for ( i = 0; i < 4; i++)
    {
        /* code */
        bufferData[i] = readByte();
        // men[i] = readByte();
        if(i == 3){
            unAsk();
        } else {
            recvAck();
        }
        // i == 3 ? unAsk() : recvAck();
    }

    I2C_stop();
}


void seg() {
    int i;
    for(i=0;i< 4; i++) {
        P2 = segArr[bufferData[i]];
        delay(10000);
    }
    // P2 = segArr[2];
}


int main()
{
    // delay(5);
    // printf("hello word \r\n");
    AT24C02_write();
    // return 0;
}

