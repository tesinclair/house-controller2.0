#ifndef CLIENT
#define CLIENT

#define SERVER "192.168.1.171"
#define PORT 6767

// Client side definitions should be between 200 and 299
#define SEND_SUCCESSFUL 201
#define SEND_FAILED -201
#define RECV_FAILED -202
#define CONNECTION_CLOSE_ERROR -205

#define SOCKET_FAILED -210
#define CONNECTION_FAILED -211

#define CLOSE_FAILED -220
#define CLOSE_SUCCESSFUL 220
#define SHUTDOWN_FAILED -221

typedef struct{
    char *data;
    int length;
}Request;

struct connection{
    int fd;
    int err;
}

// Returns a file descriptor or error code
int clientConnect();

// Returns success or error code
int clientSend(Request *request);

#endif
