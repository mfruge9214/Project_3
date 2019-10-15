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
	if(!src)
	{
		// Add logging warning that no memory has been allocated to loc
	}
	free(src);
	printf("Freed\n");

}


mem_status writeMemory(uint32_t* loc, uint8_t value)
{
	// Write val to loc, determine if it was successful, and return result
	mem_status result;
	*loc = value;

	if(*loc == value)
	{
		result = SUCCESS;
	}
	else
	{
		result = FAIL;
	}
	return result;
}



