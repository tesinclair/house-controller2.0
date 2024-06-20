#include "utillib.h"

void utilErrorPanic(int errCode, char *exitMsg, MemoryStack *memoryStack){
    if (memoryStack != NULL && memoryStack->head != NULL){
        utilStackEmpty(memoryStack);
        free(memoryStack);
    }else if (memoryStack != NULL){
        free(memoryStack);
    }

    g_print("Aborting with error code: %d: %s", errCode, exitMsg);
    exit(errCode);
}

void utilErrorAssert(int exp, char *failMsg, int* errCode, MemoryStack *memoryStack){
    if (!exp){
        g_print("Assertion failed: %s\n", failMsg);
        if (errCode == NULL){
            utilErrorPanic(*errCode, failMsg, memoryStack);
        }
 
        if (memoryStack == NULL){
            goto exit;
        }

        if(memoryStack->head == NULL){
            free(memoryStack);
        }else{
            utilStackEmpty(memoryStack);
            free(memoryStack);
        }
    }
    exit: 
        assert(exp);
}
