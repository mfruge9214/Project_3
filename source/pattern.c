#include "pattern.h"




/********************************
 * @brief Creates pseudo-random pattern through LFSR implementation
 *
 * @param[in] len	Length of array to generate, in bytes
 *
 * @param[in] seed	Starting State for the LFSR
 *
 *
 *******************************/

//static uint8_t pattern[]
uint8_t* createPattern(size_t len, int8_t seed)
{
	// Need to allocate an array, so we arent returning a local variable
	int8_t curr_state = seed;
	int8_t next_state = 0;
	uint8_t pattern[len];
	size_t i = 0;

	int8_t mult, mod, offset;
	mult = 13;
	mod = 17;
	offset = 1;

	for(i=0; i<len; i++)
	{
		next_state = ((mult*curr_state) + offset) % mod;
		pattern[i] = next_state;
		curr_state = next_state;
		printf("Value Generated: %d  Index: %d\n", next_state, i);
	}

	return pattern;
}
