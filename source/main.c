#include "gpio.h"
#include "system_timer.h"
#include "uart.h"
#include "printf.h"

/** Function Declerations **/
void blink_once(int pin1, int pin2);

void logic(const char* h1, const char* i1, const char* h2, const char* i2, const char* h3);

uint8_t calc(const char* input, int i);

void print_result(const char* h1, const char* h2, const char* h3,
    uint8_t* r1, uint8_t* r2);

//Global Truth Table
const uint8_t w[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};
const uint8_t x[16] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1};
const uint8_t y[16] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
const uint8_t z[16] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

//Toggle the use of LEDs
uint8_t led = 0;

// Implement Lab 4 as described in the lab manual
int main()
{
    // Init GPIO select for external LED
    gpio[GPFSEL1] = 0x040000; // Selected pin 16
    gpio[GPFSEL2] = 0x000001; // Selected pin 20

    //UART
    const int bufferSize = 80;
    init_uart();
    char buffer [bufferSize];

    while (1)
    {
        size_t charsGot = get_string(buffer, bufferSize);
        char ch = buffer[0];

        switch (ch)
        {
            case '1':
                logic("f ", "w'x'y'z'+w'x'yz'+w'xy'z'+w'xyz+w'xyz'+wxy'z+wxyz+wxyz'+wx'y'z",
                    "g ", "a'd'+ac'd+bc",
                    "Boolean Equivalence");
                break;
            case '2':
                logic("R1", "b'd'+bcd'",
                    "R2", "b'd'+a'bc",
                    "Don't Care");
                break;
            case '3':
                led ^= 1; //toggle led usage
            default:
                put_string("Invalid Input\r\n");
        }
    }

    return 0;
}

/*
Params: Header1, Input1, Header2, Input2, Title
Prints truth table and the resulting values for each input
Headers must be 2 characters wide
*/
void logic(const char* h1, const char* i1, const char* h2, const char* i2, const char* h3)
{
    //Results
    uint8_t r1[16], r2[16];

    //For each combination in the truth table (16)
    for (int i = 0; i < 16; i++)
    {
        r1[i] = calc(i1, i);
        r2[i] = calc(i2, i);
    }

    print_result(h1, h2, h3, r1, r2);
}

/*
Params: input char array, current index
*/
uint8_t calc(const char* input, int i)
{
    uint8_t result = 1, tmp = 1; //Starts 1 or result will always be 0
    int length = (sizeof(input) / sizeof(input[0])); //length of array

    uint8_t not = 0;
    for (int j = 0; j < length; j++)
    {
        
        // Checks next bit; check for index out of range
        if (j+1 < length)
        {
            //Checks if next character is 'not'
            if (input[j+1] == '\'')
            {
                not = 1;
            }
            // If or opperator '+', result equals bitwise or with tmp, 
            // reset tmp (tmp = 0),
            // skip next character
            else if (input[j+1] == '+')
            {
                result |= tmp;
                tmp = 0;
                j++;
            }            
        }

        //Ands temp with the corrisponding value
        //(bitwise or for when value is not)
        switch (input[j]) 
        {
            case 'a':
            case 'w':
                tmp &= w[i] ^ not;
                break;
            case 'b':
            case 'x':
                tmp &= x[i] ^ not;
                break;
            case 'c':
            case 'y':
                tmp &= y[i] ^ not;
                break;
            case 'd':
            case 'z':
                tmp &= z[i] ^ not;
                break;
        }

        //If not was toggled
        //Reset not
        //Skip next character
        if (not == 1) {
            not = 0;
            j++;
        }

    }

    return result;
}

void print_result(const char* h1, const char* h2, const char* h3,
    uint8_t* r1, uint8_t* r2)
{
    char line[32];

    //Print Header
    //const char* line = "W X Y Z " + h1 + " " + h2 + " – " + h3 + "\r\n\0";
    sprintf(line, "W X Y Z %s %s - %s\r\n\0", h1, h2, h3);
    put_string(line);

    for (int i = 0; i < 16; i++)
    {
        //Print results for each combination
        //line = w[i] + x[i] + y[i] + z[i] + r1[i] + r2[i] + "\r\n\0";
        sprintf(line, "%d %d %d %d  %d  %d\r\n\0", 
            w[i], x[i], y[i], z[i], r1[i], r2[i]);
        put_string(line);
        
        if (led == 1)
        {
            //LED blink code
            blink_once(r1[i], r2[i]);
            //delay 2 seconds between blink code
            timer_delay_ms(2000); 
        }
    }
}

/*
Params: the state of the pins
If set to 1, the pin turns on,
delays for .5 seconds,
and then turns off
*/
void blink_once(int pin1, int pin2)
{
    // Turn on GPIO 16 if true
    if (pin1 == 1)
        gpio[GPSET0] |= 1 << 16;

    // Turn on GPIO 20 if true
    if (pin2 == 1)
        gpio[GPSET0] |= 1 << 20;

    //Delay
    timer_delay_ms(500);

    // Turn off GPIO 16 & 20
    gpio[GPCLR0] |= 1 << 16;
    gpio[GPCLR0] |= 1 << 20;
}
