#include "gpio.h"
#include "system_timer.h"
#include "uart.h"

void logic(const char* h1, const char* i1, const char* h2, const char* i2, const char* h3);

uint8_t calc(uint8_t w, uint8_t x, uint8_t y, uint8_t z, const char* input);

void blink_once()
{
    // Turn on GPIO 16
    gpio[GPSET0] |= 1 << 16;

    timer_delay_ms(500);

    // Turn off GPIO 16
    gpio[GPCLR0] |= 1 << 16;

    timer_delay_ms(500);
}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        blink_once();
    }

    // Only delay 4 seconds, since we delay for 1 additional
    // second in blink_once().
    timer_delay_ms(4500);
}

int main()
{
    // Implement Lab 4 as described in the lab manual

    // Init GPIO select for external LED
    gpio[GPFSEL1] = 0x040000; // Selected pin 16

    //UART
    const int bufferSize = 80;
    init_uart();
    char buffer [bufferSize];

    logic("f", "w'x'y'z'+w'x'yz'+w'xy'z'+w'xyz+w'xyz'+wxy'z+wxyz+wxyz'+wx'y'z",
        "g", "a'd'+ac'd+bc",
        "Boolean Equivalence");

    logic("R1", "",
        "R2", "",
        "Don't Care");

    return 0;
}

/*
Params: Header1, Input1, Header2, Input2, Title
Prints truth table and the resulting values for each input
*/
void logic(const char* h1, const char* i1, const char* h2, const char* i2, const char* h3)
{
    //Truth Table
    uint8_t w[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    uint8_t x[16] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1};
    uint8_t y[16] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
    uint8_t z[16] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

    //Results array
    uint8_t r1[16], r2[16];

    //For each combonation in the truth table (16)
    for (int i = 0; i < 16; i++)
    {
        r1[i] = calc(w[i], x[i], y[i], x[i], i1);

        r2[i] = calc(w[i], x[i], y[i], x[i], i2);;
    }

    //print
    //PutString();
    
}

/*
Params: Values of w, x, y, z, and the input char array 
*/
uint8_t calc(uint8_t w, uint8_t x, uint8_t y, uint8_t z, const char* input)
{
    uint8_t result = 0, tmp = 0;
    int length = (sizeof(input) / sizeof(input[0])); //length of array

    uint8_t not = 0;
    for (int i = 0; i < length; i++)
    {
        
        // Checks next bit; check for index out of range
        if (i+1 < length)
        {
            //Checks if next character is 'not'
            if (input[i+1] == '\'')
            {
                not = 1;
            }
            // If or opperator '+', result equals bitwise or with tmp, 
            // reset tmp (tmp = 0),
            // skip next character
            else if (input[i+1] == '+')
            {
                result |= tmp;
                tmp = 0;
                i++;
            }            
        }

        //Ands temp with the corrisponding value
        //(bitwise or for when value is not)
        switch (input[i]) 
        {
            case 'w':
                tmp &= w ^ not;
                break;
            case 'x':
                tmp &= x ^ not;
                break;
            case 'y':
                tmp &= y ^ not;
                break;
            case 'z':
                tmp &= z ^ not;
                break;
        }

        //Skip next character
        //Reset not
        if (not == 1) {
            i++;
            not = 0;
        }

    }

    return result;
}