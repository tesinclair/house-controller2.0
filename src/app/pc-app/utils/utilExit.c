#include "utillib.h"

void utilExitPanic(int errCode, char* exitMsg, MemoryStack *memoryStack){
    if (memoryStack != NULL && memoryStack->head != NULL){
        utilStackEmpty(memoryStack);
        free(memoryStack);
    }else if (memoryStack != NULL){
        free(memoryStack);
    }

    printf("Aborting with error code: %d: %s", errCode, exitMsg);
    exit(errCode);
}
