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

void displayMemory(uint32_t* loc, size_t len, uint8_t * ret)
{
	if((loc != NULL) && (len > 0))
	{
		uint32_t * mem_ptr = loc;
		for(size_t i = 0; i < len; i++)
		{
			ret[i] = *mem_ptr;
			mem_ptr++;
		}
	}
	else
	{
		//log error
	}
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
	printf("Pattern Generated\n\r");

	mem_status ret = SUCCESS;
	size_t i = 0;
	while(i < len)
	{
		ret = writeMemory(temp_ptr, pat[i]);
		printf("Wrote memory address %p with value %d\n\r", temp_ptr, *temp_ptr);
		if(ret != SUCCESS)
		{
			printf("writeMemory failed with code %d\n", ret);
			break;
		}
		if(i == 15)
		{
			break;
		}
		temp_ptr++;
		i++;
	}
	return ret;
}

void verifyPattern(uint32_t* loc, size_t len, int8_t seed, uint32_t ** ret)
{
	if((loc != NULL) && (len > 0))
	{
		uint8_t pat[len];
		/* generate pattern - store in pat */

		uint32_t * mem_ptr = loc;
		size_t i = 0;
		while(i < len)
		{
			if(*mem_ptr != pat[i])
			{
				*ret = mem_ptr;
				ret++;
			}
			i++;
			mem_ptr++;
		}
		*ret = 0; // End mismatch array with 0, check for this upon return
	}
	else
	{
		//log error
	}
}

uint32_t* getAddress(uint32_t* loc, uint32_t offset)
{
	uint32_t * addr = loc + offset;
	return addr;
}

