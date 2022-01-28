#include"reg51.h"
// #include "stdio.h"
// 为了可以 简写 定义 uint 函数
// #include uint unsigned int;

sbit IN1 = P2^0;
sbit IN2= P2^1;
sbit E = P2^2;

unsigned int value[] = {2000, 8000};


void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}


// 根据 L293D功能表 ，配置电机正转,转速最高192，占空比100%；
void motor(){
    IN1 = 1;
    IN2 = 0;
    E = 1;
}


void motor50(){
    IN1 = 1;
    IN2 = 0;
    delay(50);
    IN1 = 1;
    delay(50);
    E = 1;
}

void motorTime(){
    // IN1 = 1;
    IN2 = 0;
    E = 1;
}

void initTime(){
    TMOD = 0x01; //选择 16位模式
    TH0 = (65536 - 8000) / 256;
    TL0 = (65536 - 8000) % 256;
    ET0 = 1; //定时器中断
    EA = 1; //开启中断
    TR0 = 1; //开启定时器

    // ---- 直流电机 ---
    // 给 IN0 赋 初值
    IN1 = 0;


}

// 直流电机 的转速主要参数 是占空比
int main()
{
    
    // printf("hellow ye yun");


    //  -----    占空比位 100% 的 ------
    // motor(); 

    // ------- 占空比位 50% 的 ---------
    // motor50(); 

    // ----- 定时器 实现占空比------
    initTime();
    while (1)
    {
        /* code */
        motorTime(); 
    }
    

}


// 中断服务程序    定时计数器 : 1
void timer_isr() interrupt 1 {
    TH0 = (65536 - value[IN1]) / 256;
    TL0 = (65536 - value[IN1]) % 256;

    // ---- 直流电机 方波 ---
    // 给 IN0 取反
    IN1 = ~IN1;


}


