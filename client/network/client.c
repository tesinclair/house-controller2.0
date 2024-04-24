#include"client.h"
#include<stdlib.h>
#include<stdio.h>

int clientSend(char data[], int length){
    printf("Data: %s, length: %d", data, length);
    return SUCCESSFUL_DATA_SENT;
}
