#include "system_timer.h"

void timer_delay_us(uint32_t delayUs)
{
    // First, get the current count of the timer.
    

    // Next, add the delay to the current count.
    // and, put that into the C0 timer register.
    

    // Clear the M0 timer register.
    

    // Now we spin until the CS register
    // has a 1 in the 0 position, then we know
    // our timer has expired.
    
}

void timer_delay_ms(uint32_t delayMs)
{
    // scale the microsecond delay appropriately
    
}

void timer_delay_sec(uint32_t delaySec)
{
    // scale the microsecond delay appropriately
    
}
