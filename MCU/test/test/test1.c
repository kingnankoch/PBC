#include "reg51.h"

sbit LED0=P2^0;
void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<1200;j++);
	}	
		
}

void main()
{
	while(1)
	{
		LED0=0;
		//sleep(3);
		delay(10);
		LED0=1;
		//sleep(3);
		delay(10);
	}
}