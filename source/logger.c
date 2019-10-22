#include "logger.h"


/* Private Variable */
static char* LogMessage;
static bool LogEnable;


void logInit()
{
	LogEnable = false;
	LogMessage = "Log Init\n";
	printf("Logger Test\n\r");
//	printf("%s\n", LogMessage);
}


void logEnable()
{
	if(LogEnable)
	{
		LogMessage = "Logger already Enabled\n";
	}
	else
	{
		LogEnable = true;
		LogMessage = "Logger Enabled\n";
	}

	printf("%s\n", LogMessage);
}


void logDisable()
{
	LogMessage = "Disabling Logger\n\r";
	if(LogEnable)
	{
		LogEnable = false;
	}
}


bool logStatus()
{
	return LogEnable;
}


void logData(uint32_t* loc, size_t len)
{

	// Can also use Read Memory function here
	if(!LogEnable)
	{
		return;
	}
	uint32_t* currLoc = loc;
	size_t i = 0;

	// Access memory directly, or read from the same buffer every time?
	// Direct access: Easier, misses memory checks (included in the memory test suite)

	for(i=0; i<len; i++)
	{
		printf("Address: 0x%p		Value: 0x%02X \n\r", currLoc, *currLoc);
		currLoc++;
	}

}


void logString(char* message)
{
	if(!LogEnable)
	{
		return;
	}

	printf("%s\n\r", message);


}


void logInteger(uint32_t value)
{
	// Same thing here, take the integer as a parameter? read it from the buffer?

	/* Ensure Logger Enabled */
	if(!LogEnable)
	{
		return;
	}

	printf("%d\n\r", value);

}


