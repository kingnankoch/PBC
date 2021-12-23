#include <stdio.h>

// #include "reg51.h"

int IT0, EX0, EA;

int num;
// 外部中断的
void initex() {
    IT0 = 1;  // 外部中断的触发方式 1 边沿触发， 因为 int0 和 int1的是低电平有效，所以触发方式1代表的意思就是 下降沿触发
    EX0 = 1;  // 外部中断 INT0的中断   EX1为INT0的中断
    EA = 1;  //总控位 中断
}

int main()
{
    initex();
    while(1){
        /* code */
    }
    
    return 0;
}
 
//  定时器 0 的中断
void exIsr() interrupt 0 {
    // 每次进入中断 让 num++
    num++
}

