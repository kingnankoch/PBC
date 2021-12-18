#include "reg51.h"

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
        //printf(" %d \n", (00000001)<< i);
				P2 = (00000001)<< i;
				delay(10);
    }
}

int main(){
    // printf("kingnan \n");
    led();
    return 0;
}
