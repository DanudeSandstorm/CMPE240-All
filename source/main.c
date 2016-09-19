/** 
* Lab 1 - GPIO Blinky
* - Drive an LED by GPIO
* - Developer - 
* - Date - 
* 
*/
#include "gpio.h"

// Write a function that will delay for n loops
// to satisfy timing constraints given in lab. 
// ....beware compiler optimization....
void delay(uint32_t count)
{
    // each instuction is 40 cycles
    // loop has 4 instructions
    // clock speed is 1200mh
    // 1,200,000,000 / (40 * 4) = 7,500,000 loops per second
    // 1 millisecond of delay = 7500 * count
	for (volatile uint32_t i = 0; i < count * 7500; i++) {}
}

int main()
{
	// Select output mode and which pin to drive
    gpio[GPFSEL1] = 0x040000;

    while (1)
    {       
        //toggle clear register for the chosen pin
        gpio[GPCLR0] = 0x010000;

        //apply a delay 
        delay(1000); //(milliseconds)
        
        //toggle set register for the chosen pin
        gpio[GPSET0] = 0x010000;

        //apply a delay
        delay(1000); //(milliseconds)

    }
    
    return 0;
}
