#ifndef UTILLIB
#define UTILLIB

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

// @Section: memory manager defs

// Memory allocation identifiers should always be in the scope: 
// (-199)-(-100) 
#define BAD_MEMORY_STACK -100
#define NO_MEMORY -101
#define NO_STACK_HEAD -102
#define FAKE_POINTER -150

// @Section: client defs

#define SERVER "192.168.1.171"
#define PORT 6767

// Client side definitions should be between -200 and -299
#define SEND_FAILED -201
#define RECV_FAILED -202
#define CONNECTION_CLOSE_ERROR -205
#define SOCKET_FAILED -210
#define CONNECTION_FAILED -211
#define CLOSE_FAILED -220
#define SHUTDOWN_FAILED -221

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

// @Section Memory manager code

typedef struct Node{
    void *data;
    struct Node *next;
} Node;

typedef struct MemoryStack{
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

// @Section: client socket code

typedef struct{
    char *data;
    int length;
} Request;

struct connection{
    int fd;
    int err;
};

struct connection utilClientConnect();

void utilClientSend(Request *request, MemoryStack *memoryStack);

void utilClientCloseConnection(int cli_FD, MemoryStack *memoryStack);


/*
 * @IMPORTANT: utilExitPanic cannot be called from utilStackEmpty
*/

// @Section: custom exit code

void utilExitPanic(int errCode, char *exitMsg, MemoryStack *memoryStack);

#endif

