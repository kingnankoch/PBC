#include "reg51.h"
#include  <intrins.h> //因为要调用nop函数，所以添加了这个库
// #include "stdio.h";
// #define uchar unsigned  char 

sbit RS = P3^0;
sbit RW = P3^1;
sbit E = P3^2;


sbit T_RST = P3^3;
sbit T_CLK =P3^4;
sbit T_IO =P3^5;


unsigned char dateChar[] = {"DATE:"};
unsigned char  timeChar[]={"TIME:"};
unsigned char dateBuffer[10] = {0x32, 0x30, 0, 0, 0x2d, 0, 0, 0x2d, 0, 0}; //ascii码 0x32  = 2 , 0x30 = 0, 0x2d = -
unsigned char timeBuffer[10] = {0, 0, 0x3a, 0, 0, 0x3a, 0, 0}; // 0x3a = :
unsigned char weekBuffer = {0x30};

// 延时函数
void delay (unsigned int n)
{
	unsigned int i=0,j=0;
	for (i = 0; i < n; i++)
	{
		for(j=0;j<120;j++);
	}
}


void Write(unsigned char dat){
    unsigned char i;
    for(i = 8; i > 0;i--){
        T_IO = dat & 0x01;
        T_CLK = 1;
        T_CLK = 0;
        dat = dat >> 1;
    }
}

unsigned char Read(void) {
    unsigned char i, readData = 0;
    for (i = 8; i> 0; i++){
        readData = readData >> 1;
        // T_IO 是每次for循环都会有变化吗？
        if(T_IO){
            readData |= 0x80; //没明白什么意思， 最高位移动到最低位，相当于一次还原？？？？？ 为什么与10000000 或

        }
        T_CLK = 1;
        T_CLK = 0;
    }
    return(readData);
}


void W1302(unsigned char address, unsigned char dat){
    T_RST = 0;
    T_CLK = 0;
    _nop_();
    _nop_();
    T_RST = 1;
    _nop_();
    _nop_();
    Write(address);
    Write(dat);
    T_CLK = 1;
    T_RST  =0;

}

unsigned char R1302(unsigned char address){
    unsigned char dataInfo = 0;
    T_RST = 0;
    T_CLK = 0;
    T_RST = 1;
    Write(address);
    // 不清楚这步获取到的数据是什么形式
    dataInfo = Read();
    T_CLK = 1;
    T_RST = 0;
    return(dataInfo);



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


void display(){
    // wireCommand(0x80);
    // delay(5);
    // wireData('K');
    // delay(5);
    int i = 0,temp = 0;
    temp = R1302(0x8d); //读年

    dateBuffer[2] = 0x30 + temp/16;
    dateBuffer[3] = 0x30 + temp%16;

    temp = R1302(0x8B); //读星期
    weekBuffer = 0x30 + temp;

    temp = R1302(0x89); //读月
    dateBuffer[5] = 0x30 + temp/16;
    dateBuffer[6] = 0x30 + temp%16;


	temp=R1302(0x87);	//读日
	timeBuffer[8]=0x30+temp/16;
	timeBuffer[9]=0x30+temp%16;


    temp=R1302(0x85); 	//读小时
	temp=temp&0x7f;
	timeBuffer[0]=0x30+temp/16;
	timeBuffer[1]=0x30+temp%16;
	
	temp=R1302(0x83); 	//读分
	timeBuffer[3]=0x30+temp/16;
	timeBuffer[4]=0x30+temp%16;
	
	temp=R1302(0x81); 	//读秒
	temp = temp & 0x7f;
	timeBuffer[6]=0x30+temp/16;
	timeBuffer[7]=0x30+temp%16;



    wireCommand(0x80);
    for (i = 0; i < 5; i++)
    {
        /* code */
        wireData(dateChar[i]);
    }
    
	wireCommand(0xc0);           
	for (i=0;i<5;i++) 
	{
		wireData(timeChar[i]);    
	}

	wireCommand(0x86);    //显示日历       	
	for (i=0;i<10;i++) 
	{
		wireData(dateBuffer[i]);       
	}	


	wireCommand(0xc6);    //显示时间       		
	for (i=0;i<8;i++) 
	{
		wireData(timeBuffer[i]);
	}

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


int main()
{
 
    /* code */
    // int i;
    // printf("%d\n", argc); 
    // while(argc){
    //     printf("%s\n", argv[--argc]);
    // }



    // while (1)
    // {
    //     display();
    // }
    // int i;
    // int readdat = 00001110;
    // int  T_IO;
    // for(i=0;i< 8; i++) {
    //     T_IO = readdat & 0x01;
    //     readdat = readdat >> 1;
    //     printf(" %d \n", readdat);
    //     printf("T_IO == %d \n", T_IO);
    // }

   initLcd();
   W1302(0x8e, 0);      // 打开写保护 
   W1302(0x8c, 0x20);   // 写入年 
   W1302(0x8A, 0x01);   // 写入星期
   W1302(0x88, 0x12);   //写入月
   W1302(0x86, 0x27);   //写入日
   W1302(0x84, 0x22);   //写入小时
   W1302(0x82, 0x35);   //写入分
   W1302(0x80, 0x44);   //写入秒
   W1302(0x8e, 0x80);   //关闭写保护
   while (1)
   {
       /* code */
       display();
   }
   



    return 0;
}

