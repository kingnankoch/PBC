#include "stdio.h"

unsigned char T_IO[] = {"10101000"};


void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<1200;j++);
	}	
		
}

int tenToTwo(num) {
    int i = 0, n, a[32];
    // printf("请输入一个十进制整数.\n");
    // scanf("%d", &n);
    n = num;
    while (n > 0) {
        a[i] = n % 2;
        i = i + 1;
        n = n / 2;
    }
    printf("十进制整数转换为二进制数是: %u  == ", num);
    for (i--; i >= 0; i--)
        printf("%d", a[i]);
    printf("\n");
    return 0;
}




void computer(){
    // printf("%c", T_IO[0]);
    unsigned char readData = 0;
    unsigned char i = 8;
    for (i = 8; i > 0; i--){
        readData = readData >> 1;
        delay(100);
        // if(T_IO){
        //     readData |= 0x80; //没明白什么意思， 最高位移动到最低位，相当于一次还原？？？？？

        // }
        // printf("i = %u \n", i);
        // printf("= %c \n", (T_IO[i]));
        if(T_IO[i]=='1') {
            // printf("T_IO == %c \n", T_IO[i]);
            readData |= 0x80;
        }
        printf("readData = %u \n", readData);
        
        // printf("%c", T_IO[i]);
        
        tenToTwo(readData);
    }
    


}

int main(){
    computer();
    return 0;

}






