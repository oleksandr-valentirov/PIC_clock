/*
 * File:   main.c
 * Author: aleks
 *
 * Created on November 22, 2020, 10:50 PM
 */


#include <xc.h>
#include "system.h"
#include "timer_0.h"
#include "rs3231_i2c.h"
#include "I2C.h"
#include "internal_interrupt.h"
#include "lcd.h"

void main(void) {
    System_Initialize();
    interrupt_enable();
    peripheral_int_enable();
    TMR0IF = 0;
    t0_int_enable();
    t0_enable();
    INTF = 0;
    INT_enable();

    // RTC configuration
    set_minutes(59);
    set_hours(0, 21);
    set_seconds(56);
    set_date(23);
    set_month(10);
    set_year(20, 21);
    
    while (1) {

    }

    return;
}

void __interrupt() ISR(void) {
    if (TMR0IF & TMR0IE)
        t0_ISR();
    if (SSP1IF & SSP1IE)
        i2c_ISR();
    if (INTF & INTE)
        int_ISR();
    return;
}