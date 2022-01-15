// #include "reg51.h"
#include "stdio.h"


sbit DQ = P3^3;

// 延时函数 因为 DS18B20函数的 时序 中的 在读的0的模式需要 15ms 在读1 的情况下需要 5ms左右
void delay_18B20(unsigned int i){
    for (; i > 0; i--)
}
// 初始化 DS18B20

// 精度分为 9、10、11、12 位，默认 12位
// 在配置过程中 一般跳过ROM 指令码 OCCH
// 启动温度转换 指令 44H
// 读暂存器 0BEH 
// 首先将 数据线下拉持续 时间 480us-960us 后然后释放（拉高电平）DS18B20收到信号后等待15-60us左右 初始化成功，会在 12-60us后产生一个低电平，信号会持续 60-240us
void init_DS18B20(void){
    unsigned char x = 0;
    DQ = 1; 
    delay_18B20(8);//拉低电平前 先保持高电平一段时间
    DQ = 0;
    delay_18B20(80);//拉低电平保持 480us-960us 后然后释放（
    DQ = 1; //拉高，等待 DS18B20反应
    delay_18B20(14); // 等待12-60us 后查看数据线的状态
    X = DQ;//如果 是初始化成功，那么会产生一个低电平 若X= 0表示成功
    delay_18B20(20); //60-240us

}


// 读时序
// 读时序分为读1和读0，读1两个过程，当要读区DS18B20的数据时，先将总线拉低，并保持 1us 然后总线拉高，此时应尽快读取，从拉低到读区引脚状态时间不能超过15us
//读1的情况下，只能将电平拉低1us，读0的情况下可以将电平拉低到15us左右，但不能超过 15us
unsigned char ReadOneChar(void){
    unsigned char i = 0;
    unsigned char dat = 0;
    for(i = 8;i > 0; i--){
        DQ = 0; //先拉低总线
        // delay_18B20(8);
        dat>>1; //每次读取1位后，数据向右移位 ；移位处理的时间需要1us以上，所以不需要再延时
        DQ = 1; //拉高总线
        if(DQ){ //如果DQ是1
            dat |= 0x80; //把数据第一位变成高位
            delay_18B20(4); //等待60us
        }
        return (dat)
    }
}

int main()
{
    // printf("hellow world");
    while (1)
    {
        /* code */
        // readt
    }
    
    /* code */
    return 0;
}

