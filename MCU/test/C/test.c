#include "stdio.h"

unsigned char T_IO[] = {"10101001"};




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
    // i = 8;
    printf("十进制整数转换为二进制数是: %u  == ", num);
    for (i--; i >= 0; i--)
        printf("%d", a[i]);
    printf("\n");
    return 0;

    // int i = 0, n, a[32];
    // n = num;
    // for (; n > 0; n /= 2) a[i++] = n % 2;
    // printf("十进制整数转换为二进制数是:\n");
    // for (i--; i >= 0; i--){
    //     printf("%d", a[i]);
    // } 

}




void computer(){
    // printf("%c", T_IO[0]);
    unsigned char readData = 0;
    unsigned char i = 9;
    // for (i = 8; i > 0; i--){
    //     readData = readData >> 1;
    //     // printf("i = %u \n", i);
    //     // printf("T_IO == %c \n", T_IO[i]);
    //     // printf("T_IO == %c \n", T_IO);
    //     if(T_IO[i-1]=='1') {
    //         // printf("T_IO == %c \n", T_IO[i]);
    //         readData |= 0x80; //没明白什么意思， 最高位移动到最低位，相当于一次还原？？？？？
    //     }
    //     printf("readData = %u \n", readData);
        
    //     // printf("%c", T_IO[i]);
    //     tenToTwo(readData);
        
    // }
    
    for (i = 0; i < 8; i++){
        readData = readData >> 1;

        if(T_IO[i]=='1') {
            readData |= 0x80; //没明白什么意思， 最高位移动到最低位，相当于一次还原？？？？？
        }
        printf("readData = %u \n", readData);
        
        tenToTwo(readData);
        
    }




}

int main(){
    computer();
    return 0;

}






