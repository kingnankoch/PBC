#include "reg51.h"

unsigned char receveData, flag;

void initscon() {
    SCON = 0x50; // 0101 0000  设置方式1  8位异步通信方式  串口寄存器 波特率可变 
    TMOD = 0x20; // 0010 0000 使用定时器1 
    TH1 = (256 - 3);
    TL1 = (256 - 3);
    ES = 1; // 串口中断
    EA = 1; // 开启总中断
    TR1 = 1; //开启定时器1
}

sendData() {
	// 发送的数据是接受的  数据
	SBUF = receveData;
	while(!TI); //  循环检测是否发送完成 如果发送完成 TI 会被置为1， 需要再次发送 需要手动置为 0；
	// 发送完成之后 设置 TI = 0 这样第二次就可以发送
	TI = 0;
}

void main() {
	initscon();
	while(1){
		if (flag == 1){
			sendData();
			// 发送完之后 flag 清零
			flag = 0;
		}
	}

}

// 外部中断0: 0 ; 定时器中断1: 1; 外部中断1: 2; 定时器中1:3; 串口中断: 4;
void sconIser() interrupt 4{
	// SBUF 是接收器 发送器  共同使用的   存放器  
	receveData = SBUF; 
	RI = 0; // 数据接收完成 把 RI 手动置为 0 ；要不然第二次不会自动接收的
	flag = 1; // 标志位 表示数据接受结束
}


