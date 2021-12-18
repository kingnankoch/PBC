//#include "stdio.h"
#include "reg51.h"
//int TMOD, TH0, TL0, ET0, EA, TR0;
int count;
int num;
int segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void initTime(){
    //printf("%d \n", 0x01);
    
    TMOD = 0x01; // 0000 0001 定时器0 16位定时器
    TH0 = (65536 - 50000)/256; // 20ms = 50000us;  256 = 2 ^ 8;  初值>> 8  
    TL0 = (65536 - 50000)%256;
    // printf("TH0: %d TH0: %d \n", TH0, TL0);
    ET0 = 1; //定时器0 开启终中断
    EA = 1; // 开启总中断
    TR0 = 1; //启动定时器 0

}

void seg() {
    P2 = segArr[num];
    if(num==10) {
        num = 0;
    }
}


int main() {
    initTime();
    while (1){
			seg();
		};
    return 0;
}

// 外部中断0: 0 ; 定时器中断1: 1; 外部中断1: 2; 定时器中1:3; 串口中断: 4;
void timeIser() interrupt 1{
    TH0 = (65536 - 50000)/256;  
    TL0 = (65536 - 50000)%256;
    count++;
		if(count == 20) {
			num++;
			count =0;
		}
			
}

