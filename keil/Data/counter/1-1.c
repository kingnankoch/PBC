//#include "stdio.h"
#include "reg51.h"
//int TMOD, TH0, TL0, ET0, EA, TR0;
int count;
int num;
int segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void initCounter(){
    //printf("%d \n", 0x01);
    
    TMOD = 0x06; // 0000 0110   8位 自动重置定时计数器
    TH0 = (256 - 5); // 计数为 3  
    TL0 = (256 - 5);
    ET0 = 1; //定时器0 开启终中断
    EA = 1; // 开启总中断
    TR0 = 1; //启动定时器 0

}

void seg() {
    P2 = segArr[count];
		if(count == 10) {
			count =0;
		}
}


int main() {
    initCounter();
    while (1){
			seg();
		}
    return 0;
}

// 外部中断0: 0 ; 定时器中断1: 1; 外部中断1: 2; 定时器中1:3; 串口中断: 4;
void countIser() interrupt 1{
    count++;
}

