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
void createPattern(size_t len, uint8_t seed, uint8_t* genList)
{
	// Need to allocate an array, so we aren't returning a local variable
	uint8_t curr_state = seed;
	uint8_t next_state = 0;
//	uint8_t pattern[len];
	size_t i = 0;

	uint8_t bit1, bit2, bit3, bit7, comp1, comp2, feedback = 0;


	for(i=0; i<len; i++)
	{
		// Obtain bit values
		bit1 = ((curr_state & BIT1_MASK) >> 1);
		bit2 = ((curr_state & BIT2_MASK) >> 2);
		bit3 = ((curr_state & BIT3_MASK) >> 3);
		bit7 = ((curr_state & BIT7_MASK) >> 7);

		// Xor Bit values
		comp1 = bit1 ^ bit2;
		comp2 = bit3 ^ bit7;
		feedback = comp1 ^ comp2;

		// Set next value by shifting +1 index and filling in 0th bit
		next_state = (curr_state << 1) | (feedback & 1);
		genList[i] = next_state;
		curr_state = next_state;
//		printf("Val %u = %u\n", i, genList[i]);
	}
}
