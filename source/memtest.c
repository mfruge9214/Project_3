/* Includes */

#include "memtest.h"
#include "stdlib.h"


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

}





