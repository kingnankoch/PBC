#include"reg51.h"
// #include "stdio.h"
unsigned char str[] = {0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01};//1001 1000 1100 0100 0110 0010 0011 0001

unsigned int count = 0, num = 0;
// void delay(unsigned int n)
// {
// 	unsigned int i=0,j=0;
// 	for(i=0;i<n;i++)
// 	{
// 		for(j=0;j<120;j++);
// 	}
// }



void stepMotor(){
    // int i =  0;
    // for ( i = 0; i < 8; i++){
    //     P2 = str[i];
    //     delay(500);
    // }

    P2 = str[num];
    
}

void initTimer(){
    TMOD = 0x01; //选择 16位模式
    TH0 = (65536 - 50000) / 256;
    TL0 = (65536 - 50000) % 256;
    ET0 = 1; //定时器中断
    EA = 1; //开启中断
    TR0 = 1; //开启定时器

    //  ----- 步进电机 -----
    // count = 0;

}
 
int main()
{
    /* code */
    initTimer();
    while (1)
    {
        stepMotor();
    }
    // stepMotor();
    
    
    // return 0;
}

// 中断服务程序    定时计数器 : 1
void timer_isr() interrupt 1 {
    TH0 = (65536 - 50000) / 256;
    TL0 = (65536 - 50000) % 256;

    // ---- 步进电机  ---
    count ++;
    if(count  == 20) {
        num ++;
        num = num > 7 ? 0 : num;
        count = 0;
    }
    
}

 


