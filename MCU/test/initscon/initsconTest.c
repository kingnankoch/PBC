#include "stdio.h"
// #include "reg51.h"


int SCON, TMOD, TH1, TL1, ET0, EA, TR0;

initscon() {
    SCON = 0x50; // 0101 0000 启动
    TMOD = 0x20; // 0010 0000 定时器1 
    TH1 = (256 - 3);
    TL1 = (256 - 3);
    ES = 1; // 
    EA = 1; // 开启总中断
    TR1 = 1; //启动定时器1
}

void main() {

}
