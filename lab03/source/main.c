#include "gpio.h"
#include "system_timer.h"
#include "uart.h"
#include "debug.h"

int mod (int a, int b)
{
   return a - b * (a / b);
}

void blink_once()
{
    // Turn on LED
    gpio[GPSET0] = 0x010000;
    
    //Delay
    timer_delay_sec(1);

    // Turn off LED
    gpio[GPCLR0] = 0x010000;

    //Delay
    timer_delay_sec(1);
}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        // Blink the LED
        blink_once();
    }

    // Delay for desired time
    timer_delay_sec(5);
    
}

int main()
{
    const int bufferSize = 80;

    // Init GPIO select for external LED
    gpio[GPFSEL1] = 0x040000; // Selected pin 16

    // Init uart for debugging purposes
    init_uart();

    // Provide a buffer size for debug prints
    char buffer [bufferSize];

    // You might need a count for something
    uint32_t blinkCount = 1;

    // Mainline loop
    while (1)
    {
        
        // Set a blink count to 0 every 10 loops
        blinkCount = blinkCount % 10;

        // If the blink count is not 0, 
        // call the blink_code function
        if (blinkCount != 0)
        {
            blink_code(blinkCount);
        }

        // Increment blink count
        blinkCount++;

    }
    
    return 0;
}
