#include "utillib.h"

void utilStackInit(MemoryStack *memoryStack){
    // Panics if memoryStack is bad
    if (utilStackIsEmpty(memoryStack)){
        memoryStack->head = NULL;
        memoryStack->length = 0;
    }
}

void utilStackPush(MemoryStack *memoryStack, void *ptr){
    int isEmpty = utilStackIsEmpty(memoryStack);

    Node *new = malloc(sizeof *new);
    if (new == NULL){
        utilExitPanic(NO_MEMORY, "No Memory\n", memoryStack);
    }
    new->data = ptr;
    new->next = NULL;

    if (isEmpty){
        memoryStack->head = new;
    }else{
        Node *current = memoryStack->head;

        while (current->next != NULL){
            Node *temp = current->next;
            current = temp;
        }

        current->next = new;
    }

    memoryStack->length++;
}

void utilStackFree(MemoryStack *memoryStack, void *ptr){
    if (utilStackIsEmpty(memoryStack)){
        utilExitPanic(BAD_MEMORY_STACK, "Memory Stack is empty\n", memoryStack);
    }
    if (ptr == NULL){
        utilExitPanic(FAKE_POINTER, "No Pointer\n", memoryStack);
    }

    int found = FALSE;
    Node *prev = memoryStack->head;

    // If ptr is the first node
    if (ptr == prev->data){
        found = TRUE;
        free(prev->data);
        free(prev);
        memoryStack->head = NULL;
    }else {
        Node *current;
        while ((current = prev->next)){
            if (current->data == ptr){
                found = TRUE;
                free(current->data);

                // make the node pointed to by prev the node pointed to by current (can be NULL)
                prev->next = current->next;
                free(current);
                break;
            }
            // Move along
            prev = current;
        }
    }

    if (found == TRUE){
        memoryStack->length--;
    }else {
        utilExitPanic(FAKE_POINTER, "Pointer not Found!\n", memoryStack);
    }
}

// @INFO: Does not free the linked list, just the nodes. memoryStack must be freed manually
void utilStackEmpty(MemoryStack *memoryStack){
    if (utilStackIsEmpty(memoryStack)){
        free(memoryStack);
        printf("MemoryStack is already empty");
        exit(BAD_MEMORY_STACK);
    }

    Node *current = memoryStack->head;
    Node *next = current->next;
    free(current->data);
    free(current);
    while (next != NULL){
        current = next;
        next = current->next;
        free(current->data);
        free(current);
    }
    utilStackInit(memoryStack);
}

void utilStackDump(MemoryStack *memoryStack){
    int isEmpty = utilStackIsEmpty(memoryStack);

    if (isEmpty){
        printf("DEBUG: Stack is empty\n");
        return;
    }else if(isEmpty == BAD_MEMORY_STACK){
        printf("DEBUG_ERROR: No memory stack provided\n");
        exit(BAD_MEMORY_STACK);
    }else{
        Node *current = memoryStack->head;
        printf("DEBUG: MemoryStack Head: %p", current->data);
        int index = 1;
        while ((current = current->next)){
            printf("DEBUG: MemoryStack Index: %d, points to: %p", index, current->data);
            index++;
        }
    }
}

int utilStackIsEmpty(MemoryStack *memoryStack){
    if (memoryStack == NULL){
        utilExitPanic(BAD_MEMORY_STACK, "No Memory Stack\n", NULL);
    }
    if (memoryStack->head == NULL){
        return TRUE;
    }else{
        return FALSE;
    }
}








