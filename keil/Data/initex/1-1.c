
#include "reg51.h"
sbit ex = P3^2;
// int IT0, EX0, EA;
int segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int num;
// 外部中断
void initex() {
    IT0 = 1;  // 外部中断的出发方式1 边沿出发 , 因位init0 和int1 的是低电平有效，所以出发方式1 代表的意思就是 下降沿触发
    EX0 = 1;  // 外部中断 INT0 的中断 EX1 为INT0的中断
    EA = 1;   // 总控中断
		ex  1;
}

void seg() {
    P2 = segArr[num];
    if(num==10) {
        num = 0;
    }
}

int main()
{
    initex();
    while(1){
			seg();
    }
    return 0;
}
 
// 定时器 0 的中断
void exIsr() interrupt 0 {
    // 每次进入中断让  num++
    num++;
}
