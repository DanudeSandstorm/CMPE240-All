#include "ieee.h"
#include "printf.h"

/*
This function will convert the integer and fractional number in 
“num” into an IEEE single precision (32 bit) floating point number.
*/
IEEE_FLT IeeeEncode(INT_FRACT num) {
	IEEE_FLT number;

	//Check for negative or positive 0
	if ((num.real == 0x0 || num.real == 0x80000000) && (num.fraction == 0x0)) {
		number = 0x00000000;
		return number;
	}

	//Record the sign of the real number
	uint32_t sign = ((num.real >> 31) & 1);
	//then make the real number positive
	//Convert from two's compliment
	if (sign == 0x1) {
		num.real = ~num.real; //bit flip
		num.real++;
		// printf("%d\r\n", num.real);
		// printf("%08X\r\n", num.real);
	}
	// num.real &= 0x7FFFFFFF;

	// Keep track of the total number of shifts.
	uint32_t shifts = 0;
	do {
		// Shift the real number one to the left 
		// and back fill the low bit of the real number 
		// from the high bit of the fraction.
		num.real = num.real << 1;
		num.real = (num.real | (num.fraction >> 31));

		// Shift the fraction part one to the left.
		num.fraction = num.fraction << 1;
		shifts++;
	// Keep executing this shifting loop until bit 31 is a one.
	} while((num.real >> 31) != 1);

	// Shift the real number eight bits
	// to the right and remove the implied 1. 
	// This is the mantissa.
	uint32_t mantissa = ((num.real >> 8) & 0x7FFFFF) ;

	// Calculate the bias exponent by subtracting 
	// the number of shifts from 158.
	uint32_t bias = 158 - shifts;

	// Shift the exponent into the correct position 
	// and combine it with the sign and mantissa.
	number = (sign << 31) | (bias << (31-8)) | mantissa; 

	// Return the IEEE number
	return number;
}

IEEE_FLT IeeeMult(IEEE_FLT a, IEEE_FLT b) {
	IEEE_FLT number;

	//Check for 0 (positive/negative)
	if ((a == 0x00000000 || a == 0x80000000) || (b == 0x00000000 || b == 0x80000000)) {
		number = 0x00000000;
		return number;
	}

	uint32_t exponent = (((a << (31-8)) + 127) + ((b << (31-8)) + 127)) - 127;
	uint64_t mantissa = ((uint64_t)((a >> 8) | 0x800000) * (uint64_t)((b >> 8) | 0x800000));
	uint32_t sign = (a << 31) ^ (b << 31); //XOR
	
	number = (sign << 31) | (exponent << (31-8)) | (uint32_t)(mantissa); 
	return number;
}

IEEE_FLT IeeeAdd(IEEE_FLT a, IEEE_FLT b) {
	return 0x0;
}
