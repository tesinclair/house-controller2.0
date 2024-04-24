#ifndef CLIENT
#define CLIENT

#define SERVER 192.168.1.171
#define PORT 6767

// Client side definitions should be between 200 and 299
#define SUCCESSFUL_DATA_SENT 201

int clientSend(char data[], int length);

#endif
