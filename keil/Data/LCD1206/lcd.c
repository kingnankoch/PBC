#include "reg51.h"

sbit RS = P3^0;
sbit RW = P3^1;
sbit E = P3^2;
unsigned char str[] = {"hello world"};
unsigned int j = 0;

// 延时函数
void delay (unsigned int n)
{
	unsigned int i=0,j=0;
	for (i = 0; i < n; i++)
	{
		for(j=0;j<120;j++);
	}
}

// 写命令
void wireCommand(unsigned char com) {
    RS = 0; // 低电平开始写命令   高电平写数据
    RW = 0; // 低电平为 写， 高电平为读 
    E = 0;  // 使能 端 下降沿有效；  根据时序图  初始低电平，然后拉高电平 前 放入 数据
    P2 = com; // 通过 P2存入数据
    delay(5);
    E = 1; // 拉高电平 开始写入数据， 然后  数据传输完成 拉低
    E = 0; // 拉低电平 数据写入完成，
}

// 写数据
void wireData(unsigned char dat){
    RS = 1; // 低电平开始写命令   高电平写数据
    RW = 0; // 低电平为 写， 高电平为读 
    E = 0;  // 使能 端 下降沿有效；  根据时序图  初始低电平，然后拉高电平 前 放入 数据
    P2 = dat;// 通过 P2存入数据
    delay(5);
    E = 1; // 拉高电平 开始写入数据， 然后  数据传输完成 拉低
    E = 0; // 拉低电平 数据写入完成，
}

void initLcd(){
    // 写入命令 
    // 00111000  设置16 * 2显示， 5*7点阵， 8位数据接口
    wireCommand(0x38);
    // 0x0C  00001100 设置开显示， 不显示光标
    wireCommand(0x0C);
    // 写一个字符后地址指针 加一
    wireCommand(0x06);
    // 显示清零 数据指针清零
    wireCommand(0x01);

}


void display(){
    wireCommand(0x80);
    delay(5);
    wireData('K');
    delay(5);
    wireData('i');
    delay(5);
    // 通过 ask 码 显示数据
    wireData(0x31);
    delay(5);
    // wireData(0111000); 错误的方式
    // wireCommand(0x80 + 2);
    wireCommand(0x80 + 2 + 0x40);
    // "\0" 表示结束符
    while (str[j]!='\0')
    {
        /* code */
        wireData(str[j]);
        delay(5);
        j++; 
    }
    
}

int main()
{
    // 初始化LCD
    initLcd();
    /* code */
    while (1)
    {
        /* 显示数值 */
        display();
    }
    
}
