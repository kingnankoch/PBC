#ifndef __UART_H // 先测试是否被宏定义过
#define __UART_H // 如果 __UART_H 没有被宏定义过，定义 __UART_H

void uartInit(void);
void sendByte(unsigned char dat);
void sendString(unsigned char * dat);

#endif