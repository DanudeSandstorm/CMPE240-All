#include "uart.h"
#include "ieee.h"
#include "printf.h"
#include "debug.h"

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

    // testMultiply();

    // testAddition();
    
    return 0;
}

int testEncode() {
    const char* fyi[8] = {"0.0", "1.0", "0.5", "0.75", "13.125", "0.8330078125", "-13.125", "8388608.0"};
    const uint32_t integer[8] = {0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x0000000D, 0x00000000, 0xFFFFFFF3, 0x00800000};
    const uint32_t fraction[8] = {0x00000000, 0x00000000, 0x80000000, 0xC0000000, 0x20000000, 0xD5400000, 0x20000000, 0x00000000};

    printf("Number\t\t| Integer\t\t| Fraction\t\t| IEEE\r\n");
    for (uint32_t i = 0; i < 8; i++) {
        INT_FRACT int_fract;
        int_fract.real = integer[i];
        int_fract.fraction = fraction[i];
        IEEE_FLT ieee = IeeeEncode(int_fract);
        printf("%s\t\t| %X\t\t| %X\t\t| %X\r\n", fyi[i], integer[i], fraction[i], ieee);
    }

    return 0;
}

int testAddition() {
    const char* fyi[8] = {"0.0", "1.0", "0.5", "0.75", "13.125", "0.8330078125", "-13.125", "8388608.0"};
    //const uint32_t ieee1[8] = {0x00000000, 0x3f800000, 0x3f000000, 0x41520000, 0x00000000, 0x00000000};
    //const uint32_t ieee2[8] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

    printf("Number\t\t| Integer\t\t| Fraction\t\t| IEEE\r\n");
    for (uint32_t i = 0; i < 8; i++) {
    }

    return 0;
}

int testMultiply() {
    return 0;
}
