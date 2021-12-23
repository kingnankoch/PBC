#include "stdio.h"

// #include "reg51.h"

void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<1200;j++);
	}	
		
}

void led() {
    int i;
    for(i=0;i< 8; i++) {
        // P2 = 
        delay(10);
        printf(" %d \n", (00000001)<< i);
    };
};

int main(){
    // printf("kingnan \n");
    led();
    return 0;
}
