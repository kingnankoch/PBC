#ifndef __UART_H // 先测试是否被宏定义过
#define __UART_H // 如果 __UART_H 没有被宏定义过，定义 __UART_H

#define MAX_REV_NUM 20
// 当前的波特率 为4800 相比9600 速度比较慢  所以 等待的时间相对较大
#define MAX_REV_TIME 10


extern unsigned char start_time;
extern unsigned char recv_buf[];
extern unsigned char recv_cnt;
extern unsigned char recv_timer_cnt;
extern unsigned char recv_flag;



void uartInit(void);
void sendString(unsigned char * dat);
void sendByte(unsigned char dat);

void clear_recv_buffer(unsigned char * buf );

#endif