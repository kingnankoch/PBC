/**
* 功能：根据ModBus规则计算CRC16
* 参数：
*       _pBuf:待计算数据缓冲区,计算得到的结果存入_pBuf的最后两字节
*       _usLen:待计算数据长度(字节数)
* 返回值：16位校验值
*/
static unsigned short int getModbusCRC16(unsigned char *_pBuf, unsigned short int _usLen)
{
    unsigned short int CRCValue = 0xFFFF;           //初始化CRC变量各位为1
    unsigned char i,j;

    for(i=0;i<_usLen;++i)
    {
        CRCValue  ^= *(_pBuf+i);                    //当前数据异或CRC低字节
        for(j=0;j<8;++j)                            //一个字节重复右移8次
        {
            if((CRCValue & 0x01) == 0x01)           //判断右移前最低位是否为1
            {
                 CRCValue = (CRCValue >> 1)^0xA001; //如果为1则右移并异或表达式
            }else 
            {
                CRCValue >>= 1;                     //否则直接右移一位
            }           
        }
    } 
    return CRCValue;            
} 
