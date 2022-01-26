#include "reg51.h"
// #include "stdio.h"

// 经过多天的寻找bug 最核心的问题是 if(DQ) 这段在程序中不起到任何的作用，但是我误以为是个判断


// ------ lcd  start-----
sbit RS=P3^0;
sbit RW=P3^1;
sbit E=P3^2;
// sbit DQ=P3^3;
unsigned int readtemp = 0;
unsigned char str[]={"0123456789"};
unsigned char s[]={"Temperature:"};


// ------ lcd  end-----

// 温度传感器的
sbit DQ = P3^3;



// 延时函数 因为 DS18B20函数的 时序 中的 在读的0的模式需要 15ms 在读1 的情况下需要 5ms左右
void delay_18B20(unsigned int i){
    for (; i > 0; i--);
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
    delay_18B20(8); //拉低电平前 先保持高电平一段时间
    DQ = 0;
    delay_18B20(80);//拉低电平保持 480us-960us 后然后释放（
    DQ = 1; //拉高，等待 DS18B20反应
    delay_18B20(14); // 等待12-60us 后查看数据线的状态
    x = DQ; //如果 是初始化成功，那么会产生一个低电平 若X= 0表示成功
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
        dat >>= 1; //每次读取1位后，数据向右移位 ；移位处理的时间需要1us以上，所以不需要再延时
        DQ = 1; //拉高总线
        if(DQ)//如果DQ是1 这段程序在 不起到任何的作用
        dat |= 0x80; //把数据第一位变成高位
        delay_18B20(4); //等待60us
        
    }
	return(dat);
}

// 写时序
// 写时序包含写0和1，
// 写0的过程中要把总线的时间拉低60us 保证  DS18B20能在 15us-45us之间正确采样I/O总线上的 0电平
// 在写 1的时候要在15us以内拉高电平，
void WriteOneChar(unsigned char dat){
    unsigned char i=0;
    for (i = 8; i > 0; i--) {
        DQ = 0;
        DQ = dat & 0x01;
        if(DQ) {
            delay_18B20(1);
            DQ = 1;
        } else {
            delay_18B20(5);
            DQ = 1;
        }
        // 例如5>>=1,首先将5转换为2进制，结果是0101，右移一位就成了0010，转换回十进制就成了2了，就这样
        dat >>= 1;
    }
}

// 读取 温度信息
unsigned char ReadTemperature(){
    unsigned char a = 0,b = 0;
    unsigned int temp = 0;
    // 初始化
    init_DS18B20();
    // 写入数据 
    WriteOneChar(0xCC); // 跳过读序列号操作
    WriteOneChar(0x44); // 启动温度转换
    delay_18B20(100); //等待一段时间后再进行初始化 ？？
    init_DS18B20();  // 初始化
    WriteOneChar(0xCC); //再一次跳过读序列号
    WriteOneChar(0xBE); // 读取温度寄存器
    delay_18B20(100); // 再次 等待一段时间
    a = ReadOneChar(); //读取温度的 低位
    b = ReadOneChar(); //读取温度的 高位
    //因为读取到的数据是二进制的 
    // 采集的温度除16得到实际温度, 因为只采集到12位数据，高四位是没有数据的
    temp = ((b * 256 + a) >> 4); 
    return(temp);
}

// ------ lcd ------------

void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}


void writedat(unsigned char dat)
{
	RS=1;
	RW=0;
	E=0;
	P1=dat;
	delay(5);
	E=1;
	E=0;
}

void writecom(unsigned char com)
{
	RS=0;
	RW=0;
	E=0;
	P1=com;
	delay(5);
	E=1;
	E=0;
}

void initlcd()
{
	writecom(0x38);
	writecom(0x0c);
	writecom(0x06);
	writecom(0x01);
}

void display()
{
	unsigned char temp0=0,temp1=0,temp2=0,i=0;
	temp0=readtemp/100;
	temp1=(readtemp%100)/10;
	temp2=readtemp%10;
	
	writecom(0x80);
	delay(5);
	while(s[i]!='\0')
	{
		writedat(s[i]);
		delay(5);
		i++;
	}
	writecom(0x80+0x40+6);
	writedat(str[temp0]);
	delay(5);
	writedat(str[temp1]);
	delay(5);
	writedat(str[temp2]);
	delay(5);
	writedat('C');
	delay(5);
}


// ------ lcd  end-----



int main()
{
    // printf("hellow world");
    initlcd();
    while (1)
    {
        /* code */
        // readt
        readtemp=ReadTemperature();
        display();


    }
    
    /* code */
    // return 0;
}

