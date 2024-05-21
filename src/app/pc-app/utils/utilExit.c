#include "utillib.h"

void utilExitPanic(int errCode, char* exitMsg, MemoryStack *memoryStack){
    utilStackEmpty(memoryStack);
    free(memoryStack);
    printf("Aborting with error code: %d: %s", errCode, exitMsg);
    exit(errCode);
}
