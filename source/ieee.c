#include "ieee.h"

/*
This function will convert the integer and fractional number in 
“num” into an IEEE single precision (32 bit) floating point number.
*/
IEEE_FLT IeeeEncode(INT_FRACT num) {
	//Check for negative or positive 0
	if ((num.real == 0x0 || num.real == 0x80000000)
		&& (num.fraction == 0x0)) {
		return 0x00000000;
	}

	IEEE_FLT number;

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
		num.real = ((num.real | (num.fraction >> 31)) & 1);

		// Shift the fraction part one to the left.
		num.fraction = num.fraction << 1;
		shifts++;
		// Keep executing this shifting loop until bit 31 is a one.
	} while (((num.real >> 31) & 1) != 1);

	// Shift the real number eight bits
	// to the right and remove the implied 1. 
	// This is the mantissa.
	uint32_t mantissa = ((num.real >> 8) & 0x7FFFFF);

	// Calculate the bias exponent by subtracting 
	// the number of shifts from 158.
	uint32_t bias = 158 - shifts;

	// Shift the exponent into the correct position 
	// and combine it with the sign and mantissa.
	number = (sign << 31) | (bias << (31 - 8)) | mantissa;

	// Return the IEEE number
	return number;
}

IEEE_FLT IeeeMult(IEEE_FLT a, IEEE_FLT b) {
	//Check for 0 (positive/negative)
	if ((a == 0x00000000 || a == 0x80000000)
	|| (b == 0x00000000 || b == 0x80000000)) {
		return 0x00000000;
	}

	IEEE_FLT number;

	/* Sign */
	uint32_t sign = (((a >> 31) ^ (b >> 31)) & 1); //XOR

	/* Exponent */
	//((exponent - bias) + (exponent - bias))
	//remove redudent bias
	uint32_t exponent = ((((a >> (31 - 8)) & 0xFF)) + (((b >> (31 - 8)) & 0xFF)));
	exponent -= 127;

	/* Mantissa */
	//Grab mantissa, add implied 1
	//multiply mantissas
	uint64_t longmantissa = ((uint64_t)(a & 0x007FFFFF) | 0x800000) * ((uint64_t)(b & 0x007FFFFF) | 0x800000);
	//Remove implied 1
	longmantissa = longmantissa & 0x3FFFFFFFFFFF;
	
	//Re-Normilize
	if (longmantissa != 0) {
		exponent++; //increase exponent since 1 has gone over 1 place
		longmantissa = (longmantissa >> (8 + 16)); //Shift numbers back into position
	}
	
	number = (sign << 31) | (exponent << (31 - 8)) | (uint32_t) longmantissa;
	return number;
}

IEEE_FLT IeeeAdd(IEEE_FLT a, IEEE_FLT b) {
	//Check for 0 (positive/negative)
	if ((a & 0x7FFFFFFF) == 0 && (b & 0x7FFFFFFF) == 0x00000000) {
		return 0x00000000;
	}

	IEEE_FLT number;

	uint32_t exponent1 = (((a >> (31 - 8)) & 0xFF));
	uint32_t exponent2 = (((b >> (31 - 8)) & 0xFF));

	uint32_t mantissa1 = ((a & 0x007FFFFF) | 0x800000);
	uint32_t mantissa2 = ((b & 0x007FFFFF) | 0x800000);

	uint32_t shift = 1; //Used for normilization
	//Normilize mantissia
	if (exponent1 != exponent2) {
		shift = 0;

		while (exponent1 > exponent2) {
			exponent2++;
			mantissa2 = mantissa2 >> 1;
		}
		while (exponent2 > exponent1) {
			exponent1++;
			mantissa1 = mantissa1 >> 1;
		}
	}

	uint32_t exponent = exponent1; //Since they are equal, it doesn't matter

	uint32_t sign1 = ((a >> 31) & 1);
	uint32_t sign2 = ((b >> 31) & 1);

	uint32_t sign = 0;
	uint32_t mantissa = 0;
	//Subtraction
	//If one sign is negative but not both
	if ((sign1 ^ sign2) == 1) {

		if (mantissa1 == mantissa2) {
			return 0x0;
		}
		else if (mantissa1 > mantissa2) {
			sign = sign1;
			mantissa = (mantissa1 - mantissa2);
		}
		else if (mantissa2 > mantissa1) {
			sign = sign2;
			mantissa = (mantissa2 - mantissa1);
		}
	}
	else {
		//Addition
		mantissa = mantissa1 + mantissa2;

		//If both negative
		if (sign1 == 1 && sign2 == 1) {
			sign = 0x1;
		}
	}

	//Re-normilize
	mantissa = mantissa >> shift;
	exponent += shift;
	//Remove implied 1
	mantissa = (mantissa & 0x007FFFFF);

	
	number = (sign << 31) | (exponent << (31 - 8)) | mantissa;

	//Check for 0 (negative)
	if (number == 0x80000000) {
		number = 0x00000000;
	}

	return number;
}
