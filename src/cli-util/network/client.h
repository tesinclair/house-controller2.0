#ifndef CLIENT
#define CLIENT

#define SERVER 192.168.1.171
#define PORT 6767

// Client side definitions should be between 200 and 299
#define SEND_SUCCESSFUL 201

typedef struct{
    char *data;
    int length;
}Request;

int clientSend(Request *request);

#endif
