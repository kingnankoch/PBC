#ifndef __CRC16_H // 先测试是否被宏定义过
#define __CRC16_H // 如果 __UART_H 没有被宏定义过，定义 __UART_H






unsigned int GetCRC16(unsigned char *ptr,  unsigned char len);

#endif