#include"utillib.h"
#include<stdio.h>
#include<stdlib.h>

void utilFreeAll(MemoryStack *memoryStack){
    for (int i = 0; i < memoryStack->length; i++){
        free(memoryStack->data[i]);
    }
    free(memoryStack->data);
    free(memoryStack);
}

int utilPushStack(void *ptr, MemoryStack *memoryStack){
    if (ptr == NULL){
        return FAKE_POINTER;
    }
    if (memoryStack->data == NULL && memoryStack->data > 0){
        return NO_MEMORY_STACK;
    }
    
    if (memoryStack->capacity == memoryStack->length){
        utilResizeStack(1, memoryStack);
    }
    memoryStack->data[memoryStack->length] = ptr;
    memoryStack->length++;

    return SUCCESSFULLY_PUSHED;
}

void utilResizeStack(int amount, MemoryStack *memoryStack){
    // Resize memory stack by 1
    memoryStack->capacity += amount;
    memoryStack->data = realloc(memoryStack->data, memoryStack->capacity * sizeof(void *));
    if (memoryStack->data == NULL && memoryStack->capacity > 0){
        printf("FAILED TO ALLOCATE MEMORY FOR MEMORY STACK REALLOC! ABORTING!\n");
        exit(EXIT_FAILURE);
    }
}

MemoryStack *utilStackInit(int initial_capacity){
    MemoryStack *memoryStack;

    memoryStack = malloc(sizeof(MemoryStack));

    memoryStack->data = malloc(sizeof(void *) * initial_capacity);
    if (memoryStack->data == NULL){
        printf("FAILED TO ALLOCATE MEMORY FOR MEMORY STACK! ABORTING!\n");
        exit(EXIT_FAILURE);
    }

    memoryStack->capacity = initial_capacity;
    memoryStack->length = 0;

    return memoryStack; // pass ref to array
}

void utilFree(void *ptr, MemoryStack *memoryStack){
    for (int i = 0; i < memoryStack->length; i++){
        if (memoryStack->data[i] == ptr){
            free(memoryStack->data[i]);
            for (int j = i+1; j < memoryStack->length; j++){
                memoryStack->data[j - 1] = memoryStack->data[j];
            }
            utilResizeStack(-1, memoryStack);
            memoryStack->length--;
            break;
        }
    }
}

