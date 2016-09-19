#include "gpio.h"
#include "uart.h"

int main()
{
	
    init_uart();

    const int bufferSize = 80;

    char buffer [bufferSize];
	
	/* TO TEST PUT_CHAR AND PUT_STRING
	/	SPAM Hello World. TESTS CONSISTENCY
	/   BUFFER OVERRUN, GARBAGE CHARS, ETC...
	*/
    
    put_string("Hello, World!\r\n\0");

    put_string("Hello, World!\r\n\0");

    put_string("Hello, World!\r\n\0");

    put_string("Hello, World!\r\n\0");

    put_string("Hello, World!\r\n\0");

    put_string("Hello, World!\r\n\0");
	
	// Remove this to access code below
	while (1);

	/* 
	/ UNCOMMENT TO TEST GET_CHAR AND GET_STRING
	/ WILL ECHO INPUT FROM KEYBOARD, AND PRINT STRING
	/ IF ENTER IS PRESSED...
	/
    while (1)
    {
        size_t charsGot = get_string(buffer, bufferSize);
        for (size_t i = 0; i < charsGot; ++i)
        {
            char ch = buffer[i];
            if ((ch >= 'a') && (ch <= 'z'))
            {
                buffer[i] -= 32;
            }
        }
        put_string(buffer);
        put_string("\r\n");
    }
	*/
    
    return 0;
}
