#include "utilib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void utilStackInit(MemoryStack *memoryStack){
    memoryStack->head = NULL;
    memoryStack->length = 0;
}

void utilStackPush(MemoryStack *memoryStack, void *ptr){
    if (memoryStack == NULL){
        printf("No Memory Stack");
        exit(BAD_MEMORY_STACK);
    }

    Node *new = malloc(sizeof *new);
    if (new == NULL){
        printf("No Memory\n");
        exit(NO_MEMORY);
    }
    new->data = ptr;
    new->next = NULL;

    if (memoryStack->head == NULL){
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
    if (utilStackIsEmpty(memoryStack) != FALSE){
        printf("No Memory Stack or No Allocations\n");
        exit(BAD_MEMORY_STACK);
    }
    if (ptr == NULL){
        printf("No Pointer\n");
        exit(FAKE_POINTER);
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
        printf("Pointer not Found!\n");
        exit(FAKE_POINTER);
    }
}

// @INFO: Does not free the linked list, just the nodes. memoryStack must be freed manually
void utilStackEmpty(MemoryStack *memoryStack){
    if (utilStackIsEmpty(memoryStack)){
        printf("MemoryStack is already empty or doesn't exist");
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
        print("DEBUG: Stack is empty\n");
        return;
    }else if(isEmpty == BAD_MEMORY_STACK){
        print("DEBUG_ERROR: No memory stack provided\n");
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
        printf("No Memory Stack\n");
        return BAD_MEMORY_STACK;
    }
    if (memoryStack->head == NULL){
        return TRUE;
    }else{
        return FALSE;
    }
}








