#include "gpio.h"
#include "system_timer.h"
#include "uart.h"

void blink_once()
{
    // Turn on LED

    // Turn off LED

}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        // Blink the LED

    }

    // Delay for desired time
    
}

int main()
{
    // Init GPIO select for external LED

    // Init uart for debugging purposes

    // Provide a buffer size for debug prints

    // You might need a count for something
    uint32_t count = 1;

    // Mainline loop
    while (1)
    {
        // implement error code described in lab

        // call blink_code at some point
        blink_code(     );

    }
    
    return 0;
}
