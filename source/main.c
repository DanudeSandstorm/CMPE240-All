#include "uart.h"
#include "ieee.h"
#include "debug.h"
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

    //Run Tests
    testEncode();

    testMultiply();

    // testAddition();
    
    return 0;
}

int testEncode() {
    const char* fyi[8] = {"0.0", "1.0", "0.5", "0.75", "13.125", "0.8330078125", "-13.125", "8388608.0"};
    const uint32_t integer[8] = {0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x0000000D, 0x00000000, 0xFFFFFFF3, 0x00800000};
    const uint32_t fraction[8] = {0x00000000, 0x00000000, 0x80000000, 0xC0000000, 0x20000000, 0xD5400000, 0x20000000, 0x00000000};

    printf("Testing Encoding\r\n");
    printf("FYI Number\t| Integer\t| Fraction\t| IEEE\r\n");
    for (uint32_t i = 0; i < 8; i++) {
        INT_FRACT int_fract;
        int_fract.real = integer[i];
        int_fract.fraction = fraction[i];
        IEEE_FLT ieee = IeeeEncode(int_fract);
        printf("%-16s| 0x%08X\t| 0x%08X\t| 0x%08X\r\n", fyi[i], integer[i], fraction[i], ieee);
    }
    printf("\n");
    return 0;
}

int testMultiply() {
    const char* fyi[7] = {"0.0*1.0 = 0.0", "1.0*1.0 = 1.0", "0.5*0.5 = 0.25", 
        "13.125*13.125 = 172.26562", "-13.125*-13.125 =172.26562",
        "-13.125*0.8330078125 = -10.9332275390625", "8388608.0*1.0 = 8388608.0"};
    const uint32_t ieee1[7] = {0x00000000, 0x3f800000, 0x3f000000, 0x41520000, 0xc1520000, 0xc1520000, 0x4b000000};
    const uint32_t ieee2[7] = {0x3f800000, 0x3f800000, 0x3f000000, 0x41520000, 0xc1520000, 0x3f554000, 0x3f800000};
    
    printf("Testing Multiplication\r\n");
    printf("IEEE\t\t| IEEE\t\t| IEEE Result\t| FYI Number\r\n");
    for (uint32_t i = 0; i < 7; i++) {
        IEEE_FLT ieee = IeeeMult(ieee1[i], ieee2[i]);
        printf("0x%08X\t| 0x%08X\t| 0x%08X\t| %s\r\n", ieee1[i], ieee2[i], ieee, fyi[i]);
    }
    printf("\n");
    return 0;
}

int testAddition() {
    const char* fyi[6] = {"0.0+0.0 = 0.0", "1.0+1.0 = 2.0", "0.5+0.5 = 1.0", "13.125+13.125 = 26.25", "-13.125+-13.125 = -26.25", "8388608.0+0.5 = 8388608.0"};
    const uint32_t ieee1[6] = {0x00000000, 0x3f800000, 0x3f000000, 0x41520000, 0xc1520000, 0x4b000000};
    const uint32_t ieee2[6] = {0x00000000, 0x3f800000, 0x3f000000, 0x41520000, 0xc1520000, 0x3f000000};
    
    printf("Testing Addition\r\n");
    printf("IEEE\t\t| IEEE\t\t| IEEE Result\t| FYI Number\r\n");
    for (uint32_t i = 0; i < 6; i++) {
        IEEE_FLT ieee = IeeeAdd(ieee1[i], ieee2[i]);
        printf("0x%08X\t| 0x%08X\t| 0x%08X\t| %s\r\n", ieee1[i], ieee2[i], ieee, fyi[i]);
    }
    printf("\n");
    return 0;
}
