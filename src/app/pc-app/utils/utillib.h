#ifndef UTILLIB
#define UTILLIB

// Memory allocation identifiers should always be in the scope: 
// (-199)-(-100) 
#define BAD_MEMORY_STACK -100
#define NO_MEMORY -101
#define NO_STACK_HEAD -102
#define FAKE_POINTER -150

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

typedef struct{
    void *data;
    Node *next;
} Node;

typedef struct{
    Node *head;
    size_t length;
} MemoryStack;

/*
 * @INFO
 * Standardized to use the context (e.g. stack) before the function: (package)util (context)Stack (function)Init
*/

// Initialise the memory stack
void utilStackInit(MemoryStack *memoryStack);

// Push a new pointer to the stack
void utilStackPush(MemoryStack *memoryStack, void *ptr);

// Free the given pointer
void utilStackFree(MemoryStack *memoryStack, void *ptr);

// Free all the memory in the stack (including the stack)
void utilStackEmpty(MemoryStack *memoryStack);

// @DEBUG
// Dump the content of the stack to the console 
void utilStackDump(MemoryStack *memoryStack);

// Return true if the stack is empty
int utilStackIsEmpty(MemoryStack *memoryStack);

#endif

