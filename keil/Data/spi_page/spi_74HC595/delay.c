/**
 * @file delay.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-13
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
