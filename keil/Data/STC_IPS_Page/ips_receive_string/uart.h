#ifndef __UART_H // 先测试是否被宏定义过
#define __UART_H // 如果 __UART_H 没有被宏定义过，定义 __UART_H


#define MAX_REV_NUM 10
extern unsigned char receive_data;
extern unsigned char recv_buf[];
extern unsigned char recv_flag;

extern unsigned char recv_buf_length;

void uartInit(void);
void sendString(unsigned char * dat);
void sendByte(unsigned char dat);

#endif

