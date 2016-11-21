#include "uart.h"
#include "printf.h"

int testEncode();
int testMultiply();
int testAddition();

int main()
{
    // Provide a buffer size for debug prints
    const int bufferSize = 80;
    char buffer [bufferSize];
    // Init uart for debugging purposes
    init_uart();

    testEncode();

    testMultiply();

    testAddition();
    
    return 0;
}

int testEncode() {
    return 0;
}

int testMultiply() {
    return 0;
}

int testAddition() {
    return 0;
}
