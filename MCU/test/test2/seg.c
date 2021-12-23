
#include "stdio.h"
// #include "reg51.h"
// 数据是 二进制转16进制的 数据 0-9
// char segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int segArr[] = {0011100, 0001110, 0011100, 0001110, 0001110, 0001110, 0001110, 0001110, 0001110, 0011100};


void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<1200;j++);
	}	
}

void seg() {
    int i;
    for(i=0;i< 10; i++) {
        // P2 = segArr[i]
        printf("%ul \n", segArr[i]);
        delay(10);
        
    };
};

int main(){
    // printf("kingnan \n");
    // while (1)
    // {
       
    // }
    seg(); 
    return 0;
}
