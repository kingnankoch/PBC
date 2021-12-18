#include "reg51.h"
//  0-9 数据是二进制转十六进制 
char segArr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//int segArr[] = {0011100, 0001110, 0011100, 0001110, 0001110, 0001110, 0001110, 0001110, 0001110, 0011100};

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
        P2 = segArr[i];
        delay(100);
    }
}

int main(){
    // printf("kingnan \n");
    while (1)
    {
        seg();
    }
    return 0;
}
