/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "reg51.h"
#include "delay.h"
#include "HC595.h"

int main()
{
    hc_595_init();
    while (1)
    {
        // hc_595_drive(0xfe);
        // hc_595_drive(01001111);
        led_hc_595_drive(0x55, 0xAA);
        DelayXms(1000);
        led_hc_595_drive(0xAA, 0x55);
        DelayXms(1000);
        // DelayXms(10000);
        // led_hc_595_drive(0x55, 0xAA);
        // DelayXms(10000);
        // led_hc_595_drive(0xAA, 0x55);

        // led_hc_595_drive(01010101, 01010101); //
    }
    
    return 0;
}

