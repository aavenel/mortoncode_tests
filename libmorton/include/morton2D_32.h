// Libmorton - Methods to encode/decode 64-bit morton codes from/to 32-bit (x,y,z) coordinates
#ifndef MORTON2D_32_H_
#define MORTON2D_32_H_

#include <stdint.h>

#if _MSC_VER
#include <intrin.h>
#endif

// ENCODE 2D 32-bit morton code : For Loop
inline uint_fast32_t morton2D_32_Encode_for(const uint16_t x, const uint16_t y){
	uint_fast32_t answer = 0;
	for (uint_fast32_t i = 0; i < 16; ++i) {
		answer |=(x & (0x1 << i)) << (2*i)
				|(y & (0x1 << i)) << ((2*i) + 1);
	}
	return answer;
}

// ENCODE 2D 32-bit morton code : Magic bits (helper method)
inline uint_fast32_t morton2D_32_splitby2(const uint_fast16_t a){
	uint_fast32_t x = a;
	x = (x | x << 16) & 0x0000FFFF;
	x = (x | x << 8) & 0x00FF00FF;
	x = (x | x << 4) & 0x0F0F0F0F;
	x = (x | x << 2) & 0x33333333;
	x = (x | x << 1) & 0x55555555;
	return x;
}

// ENCODE 2D 64-bit morton code : Magic bits
inline uint_fast32_t morton2D_32_Encode_magicbits(const uint_fast16_t x, const uint_fast16_t y){
  return morton2D_32_splitby2(x) | (morton2D_32_splitby2(y) << 1);
}

#endif // MORTON2D_32_H_