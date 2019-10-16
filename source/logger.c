#include "logger.h"


/* Global Variables */
Logger* programLogger;


/* Private Variable */
static char LogMsgBuffer[512];


void logInit()
{
	programLogger->enabled = false;
	programLogger->message->moduleID = INIT;
	programLogger->message->priority = WARNING;
	programLogger->message->msg = LogMsgBuffer;
}


void logEnable()
{
	if(programLogger->enabled)
	{
		// Print a log message saying the logger is enabled already at NOTICE Priority
	}
	else
	{
		programLogger->enabled = true;
		// print a log message saying logger has been enabled
	}


}


void logDisable()
{
	if(!(programLogger->enabled))
	{
		// Print a log message saying the logger is disabled already at NOTICE Priority
	}
	else
	{
		programLogger->enabled = false;
		// print a log message saying logger has been enabled
	}
}


bool logStatus()
{
	return programLogger->enabled;
}


void logData(uint32_t* loc, size_t len)
{

	// Can also use Read Memory function here
	if(!programLogger->enabled)
	{
		return;
	}
	uint32_t* currLoc = loc;
	size_t i = 0;

	// Access memory directly, or read from the same buffer every time?
	// Direct access: Easier, misses memory checks (included in the memory test suite)
	// Fill buffer and read: More consistant, more work
	for(i=0; i<len; i++)
	{
#ifdef PC
		printf("Address: 0x%p		Value: 0x%04X \n", currLoc, *currLoc);
#endif

#ifdef BOARD
		PRINTF("Address: 0x%p		Value: 0x%04X \n", currLoc, *currLoc);
#endif

		currLoc++;
	}

}


void logString()
{
	if(!programLogger->enabled)
	{
		return;
	}

	size_t i = 0;
	while(LogMsgBuffer[i] != '\n')
	{
#ifdef PC
		printf("%c", LogMsgBuffer[i]);
#endif

#ifdef KL25Z
		PRINTF("%c", LogMsgBuffer[i]);
#endif
	}


}


void logInteger(uint32_t value)
{
	// Same thing here, take the integer as a parameter? read it from the buffer?

	/* Ensure Logger Enabled */
	if(!programLogger->enabled)
	{
		return;
	}

#ifdef PC
		printf("%d", value);
#endif

#ifdef KL25Z
		PRINTF("%d", value);
#endif

}


