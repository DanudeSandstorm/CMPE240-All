#include "ieee.h"

/*
This function will convert the integer and fractional number in 
“num” into an IEEE single precision (32 bit) floating point number.
*/
IEEE_FLT IeeeEncode(INT_FRACT num) {
	IEEE_FLT number;
	//Record the sign of the real number
	uint32_t sign = ((num.real >> 31) & 1);
	//then make the real number positive
	num.real &= 0x7FFFFFFF; // 011...

	// Keep track of the total number of shifts.
	uint32_t shifts = 0;
	do {
		// Shift the real number one to the left 
		// and back fill the low bit of the real number 
		// from the high bit of the fraction.
		num.real << 1;
		num.real = (num.real | (num.fraction >> 31));

		// Shift the fraction part one to the left.
		num.real = num.real << 1;
		shifts++;
		// Keep executing this shifting loop until bit 31 is a one.
	} while((num.real >> 31) != 1);

	// Shift the real number eight bits
	// to the right and remove the implied 1. 
	// This is the mantissa.
	uint32_t mantissa = ((num.real >> 8) & 0x7FFFF) ;

	// Calculate the bias exponent by subtracting 
	// the number of shifts from 158.
	uint32_t bias = 158 - shifts;

	// Shift the exponent into the correct position 
	// and combine it with the sign and mantissa.
	if ((bias == 0) && (mantissa == 0)) {
		number = 0x00000000;
	}
	else {
		number = (sign << 31) | (bias << (31-8)) | mantissa;
	} 

	// Return the IEEE number
	return number;
}

IEEE_FLT IeeeMult(IEEE_FLT a, IEEE_FLT b) {
	return 0;
}

IEEE_FLT IeeeAdd(IEEE_FLT a, IEEE_FLT b) {
	return 0;
}
