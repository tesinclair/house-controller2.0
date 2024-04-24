#include"utillib.h"
#include<stdio.h>
#include<stdlib.h>

int utilFreeAll(void **memoryStack){
    if (memoryStack == NULL){
        return NO_MEMORY_STACK;
    }

    for (int i = 0; memoryStack[i] != TERMINATOR; i++){
        if (memoryStack[i] != NULL){
            free(memoryStack[i]);
        }
    }

    free(memoryStack);
    
    return FREE_SUCCESSFUL;
}

int utilPushStack(void *ptr, void ***memoryStack){
    if (ptr == NULL){
        return FAKE_POINTER;
    }

    if (memoryStack == NULL){
        return NO_MEMORY_STACK;
    }

    int length = 0;
    printf("val: %p", (void *)(*memoryStack)[length]); 

    do{
        length++;
    }while (memoryStack[length] != TERMINATOR);

    *memoryStack = realloc(*memoryStack, length * sizeof(void *));

    if (memoryStack == NULL){
        return FAILED_ALLOCATION_ERROR; 
    }

    // Put pointer in last position, and move the terminator to the end
    (*memoryStack)[length - 2] = ptr;
    (*memoryStack)[length - 1] = TERMINATOR;

    return SUCCESSFULLY_PUSHED;
}

void ***utilStackInit(){
    void **memoryStack = malloc(sizeof(void *));

    if (memoryStack == NULL){
        return (void ***)FAILED_ALLOCATION_ERROR;
    }

    memoryStack[0] = TERMINATOR;

    return (void ***)memoryStack;
}

