#include "ieee.h"
#include "printf.h"

/*
This function will convert the integer and fractional number in 
“num” into an IEEE single precision (32 bit) floating point number.
*/
IEEE_FLT IeeeEncode(INT_FRACT num) {
	IEEE_FLT number;

	if ((num.real == 0x0) && (num.fraction == 0x0)) {
		number = 0x00000000;
		return number;
	}

	//Record the sign of the real number
	uint32_t sign = ((num.real >> 31) & 1);
	//then make the real number positive
	if (sign == 0x1) {
		//Convert from two's compliment
		num.real ^= num.real; 
		num.real++;
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
	return 0;
}

IEEE_FLT IeeeAdd(IEEE_FLT a, IEEE_FLT b) {
	return 0;
}
