#include"client.h"
#include<stdlib.h>
#include<stdio.h>

int clientSend(Request *request){
    printf("Data: %s, length: %d\n", request->data, request->length);
    return SEND_SUCCESSFUL;
}
