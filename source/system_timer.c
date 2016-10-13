#include "system_timer.h"

void timer_delay_us(uint32_t delayUs)
{
    // First, get the current count of the timer.
    uint32_t count = (uint32_t) sys_timer[SYS_TIMER_CLO];

    // Next, add the delay to the current count.
    // and, put that into the C0 timer register.
    sys_timer[SYS_TIMER_C0] = count + delayUs;


    // Clear the M0 timer register.
    sys_timer[SYS_TIMER_CS] |= 1;

    // Now we spin until the CS register
    // has a 1 in the 0 position, 
    // then we know our timer has expired.
    while(sys_timer[SYS_TIMER_CS] & 0x1 == 0) {}
    
    return;
}

void timer_delay_ms(uint32_t delayMs)
{
    // scale the microsecond delay appropriately
    timer_delay_ms(delayMs * 1000);
}

void timer_delay_sec(uint32_t delaySec)
{
    // scale the microsecond delay appropriately
    timer_delay_ms(delaySec * 1000);
}
