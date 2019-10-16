/* Includes */

#include "memtest.h"
#include <stdlib.h>
#include <stdio.h>


uint32_t* allocateWords(size_t len)
{
	if(len > MEM_ALLOCATION_LIMIT)
	{
		// Add logger message
		return NULL;
	}

	uint32_t* address = (uint32_t*) malloc(len);

	if(!address)
	{
		return NULL;
	}

	return address;
}


void freeWords(uint32_t* src)
{
	if(src == NULL)
	{
		// Add logging warning that no memory has been allocated to loc
	}
	free(src);
	// log success
}

uint8_t* displayMemory(uint32_t* loc, size_t len)
{
	if(loc == NULL)
	{
		/* log error */
		return NULL;
	}
	if(len <= 0)
	{
		/* log error */
		return NULL;
	}

	//needs work

	uint8_t x = *loc;
	uint8_t * ptr = &x;
	return ptr;
}

mem_status writeMemory(uint32_t* loc, uint8_t value)
{
	if(loc == NULL)
	{
		/* log error */
		return INVALID_LOC;
	}

	*loc = value; // set value

	if(*loc != value)
	{
		/* log failure */
		return FAILURE;
	}
	return SUCCESS;
}

mem_status invertBlock(uint32_t* loc, size_t len)
{
	if(loc == NULL)
	{
		/* log error */
		return INVALID_LOC;
	}
	if(len <= 0)
	{
		/* log error */
		return INVALID_LEN;
	}

	size_t i = 0;
	while(i < len)
	{
		uint8_t val = *loc;
		val = ~val;
		*loc = val;

		loc++;
		i++;
	}
	return SUCCESS;
}

mem_status writePattern(uint32_t* loc, size_t len, uint8_t seed)
{
	if(loc == NULL)
	{
		/* log error */
		return INVALID_LOC;
	}
	if(len <= 0)
	{
		/* log error */
		return INVALID_LEN;
	}

	uint32_t * temp_ptr = loc;

	uint8_t pat[len];
	createPattern(len, seed, pat);

	mem_status ret = SUCCESS;
	size_t i = 0;
	while(i < len)
	{
		ret = writeMemory(temp_ptr, pat[i]);
		if(ret != SUCCESS)
		{
			printf("writeMemory failed with code %d\n", ret);
			break;
		}

		temp_ptr++;
		i++;
	}
	return ret;
}

uint32_t* verifyPattern(uint32_t* loc, size_t len, int8_t seed)
{
	if(loc == NULL)
	{
		/* log error */
		return NULL;
	}
	if(len <= 0)
	{
		/* log error */
		return NULL;
	}

	uint32_t * mismatch[len]; // Used to store addresses of mismatches

	uint8_t pat[len];

	/* generate pattern - store in pat */

	size_t i = 0, j = 0;
	while(i < len)
	{
		if(*loc != pat[i])
		{
			mismatch[j] = loc;
			j++;
		}
		i++;
		loc++;
	}
	mismatch[j] = 0; // End mismatch array with 0, check for this upon return
	return mismatch[0];
}

uint32_t* getAddress(uint32_t* loc, uint32_t offset)
{
	uint32_t * addr = loc + offset;
	return addr;
}

