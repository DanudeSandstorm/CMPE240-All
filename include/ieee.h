#ifndef IEEE_H
#define IEEE_H

#include <stddef.h>
#include <stdint.h>

typedef struct {uint32_t real; uint32_t fraction;} INT_FRACT;

#define IEEE_FLT uint32_t

#define uint64_t unsigned long long

IEEE_FLT IeeeEncode(INT_FRACT num);

IEEE_FLT IeeeMult(IEEE_FLT a, IEEE_FLT b);

IEEE_FLT IeeeAdd(IEEE_FLT a, IEEE_FLT b);

#endif // IEEE_H
