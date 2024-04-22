#include"utillib.h"
#include<stdio.h>
#include<stdlib.h>

int free_all(void **memory_stack){
    if (memory_stack == NULL){
        return NO_MEMORY_ALLOCATIONS;
    }

    for (int i = 0; memory_stack[i] != SENTINEL_VAL; i++){
        if (memory_stack[i] != NULL){
            free(memory_stack[i]);
        }
    }

    free(memory_stack);
    
    return FREE_SUCCESSFUL;
}

int push_mem(void *ptr, void ***memory_stack){
    if (ptr == NULL){
        return FAKE_POINTER;
    }

    if (memory_stack == NULL){
        return NO_MEMORY_STACK;
    }

    int length = 0;

    while (memory_stack[i] != SENTINEL_VAL){
        length++;
    }

    *memory_stack = realloc(*memory_stack, length++ * sizeof(void *));

    if (memory_stack == NULL){
        return FAILED_TO_PUSH_ALLOCATION_ERROR; 
    }

    void *temp = (*memory_stack)[length - 2]
    (*memory_stack)[length - 2] = ptr;
    (*memory_stack)[length - 1] = temp;

    return SUCCESSFULLY_PUSHED;
}

void **mem_alloc_init(){
    void **memory_allocations = malloc(sizeof(void *));

    if (memory_allocations == NULL){
        return (void **)FAILED_ALLOCATION_ERROR;
    }

    memory_allocations[0] = SENTINEL_VAL;

    return memory_allocations;
}

