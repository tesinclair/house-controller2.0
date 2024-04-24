#ifndef UTILLIB
#define UTILLIB

// Memory allocation identifiers should always be in the scope: 
// (-199)-(-100) (for failures)
// and 100-199 (for successful)
#define NO_MEMORY_STACK -100
#define FREE_SUCCESSFUL 100
#define FAILED_ALLOCATION_ERROR -101
#define SUCCESSFULLY_PUSHED 101
#define FAKE_POINTER -150

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

#define TERMINATOR ((void *) -199)

int utilFreeAll(void **memory_stack);

int utilPushStack(void *ptr, void ***memory_stack);

void ***utilStackInit();

#endif
