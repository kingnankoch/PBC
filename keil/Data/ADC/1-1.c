#include "reg51.h"

// ADC控制接口
sbit start = P3^0;
sbit eoc = P3^1;
sbit oe= P3^2;


// 1602控制接口 
sbit RS = P3^3;
sbit RW = P3^4;
sbit E = P3^5;


// // 1602控制接口 
// sbit rs= P3^3;
// sbit rw= P3^4;
// sbit e= P3^5;

// 定一个变量存储从 P2 中读取的电压值
unsigned int vol = 0;
unsigned char numberArr[] = {"0123456789"};
unsigned char str[] = {"VOLTAGE:"};

// 这里没整明白
unsigned char temp0 = 0, temp1 = 0, temp2 = 0;

// 延时函数
void delay (unsigned int n)
{
	unsigned int i=0,j=0;
	for (i = 0; i < n; i++)
	{
		for(j=0;j<120;j++);
	}
}



//  LCD star

// 对 电压值的显示 1206的显示屏 



// 写命令
void wireCommand(unsigned char com) {
    RS = 0; // 低电平开始写命令   高电平写数据
    RW = 0; // 低电平为 写， 高电平为读 
    E = 0;  // 使能 端 下降沿有效；  根据时序图  初始低电平，然后拉高电平 前 放入 数据
    P1 = com; // 通过 P2存入数据
    delay(5);
    E = 1; // 拉高电平 开始写入数据， 然后  数据传输完成 拉低
    E = 0; // 拉低电平 数据写入完成，
}

// 写数据
void wireData(unsigned char dat){
    RS = 1; // 低电平开始写命令   高电平写数据
    RW = 0; // 低电平为 写， 高电平为读 
    E = 0;  // 使能 端 下降沿有效；  根据时序图  初始低电平，然后拉高电平 前 放入 数据
    P1 = dat;// 通过 P2存入数据
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

int k = 0;
void display(){
    // wireCommand(0x80);
    // delay(5);
    vol = (vol * 100) / 51;
    // vol = 210;
    temp0 = vol / 100;
    temp1 = (vol % 100) / 10;
    temp2 = vol % 10;

    wireCommand(0x80);
    
    for (k = 0;k <8; k++) {
        wireData(str[k]);
        delay(5);
    }
    wireCommand(0x80 + 0x40 + 2);
    delay(5);
    wireData('K');
    wireData(numberArr[temp0]);
    delay(5);
    // wireData(number[temp1]);
    // delay(5);
    // wireData(numberArr[vol]);
    delay(5);
    wireData('.');
    delay(5);
    wireData(numberArr[temp1]);
    delay(5);
    wireData(numberArr[temp0]);
    delay(5);
}

// LCD end


void adc() {
    // 根据时序图 首先 start的状态是 关闭 低电平 
    start = 0;
    // start (ADC 的转换 的控制器) 设置为高电平 ，上升沿使其 逐步逼近寄存器 复位   
    // 同时被开启的还有 ALE(地址锁存器) ,ALE 的时序与 start 是完全同步的所以 ALE 与start 连接同一个接口
    //  输入3位地址， 并使ALE = 1 ，将地址存入地址锁存器中，经过 地址译码器译码 8路通道中选通一路模拟量送到比较器
    start = 1;
    // 经过一段时间延时
    delay(5);
    // 将start = 0， 下降沿启动 ADC的转换，并且是EOC的信号为低电平
    start = 0;
    // 转换结束的时候，转换的结果送到三态输出 锁存器 并使EOC信号会带高电平， 通知CPU 已经转换结束
    // 使用 循环检测 eoc 为 1 的情况， 当eoc ==1的情况下，转换完成 
    // while 会在 eoc==1的时候跳出循环
    while (eoc != 1);
    // 当CPU执行一读数据指令， 使 oe为高电平，则输出端 D0 -D7 输出数据
    // 打开 oe
    oe = 1;
    // vol 从 P2 中读取数据
    vol = P2;
    // 读取完成 后 关掉OE
    oe = 0;
}

void main(){
    // lcd 初始化
    initLcd();
    while (1)
    {
        // adc
        adc();
        display();
    }
    
}
