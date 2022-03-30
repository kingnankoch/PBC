/**
 * @file delay.c
 * @author kingnan (github.com/kingnan-Guo/PBC)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "delay.h"


void DelayXms(unsigned int xms){
    unsigned int i, j;
    for (i = xms; i > 0; i--)
    {
        for (j = 124; j > 0; j--);
    }
    
}