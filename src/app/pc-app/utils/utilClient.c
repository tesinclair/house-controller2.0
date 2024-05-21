#include"utillib.h"
#include<arpa/inet.h>
#include<sys/socket.h>

struct connection utilClientConnect(){
    struct sockaddr_in serverAddr;
    struct connection conn;

    conn.err = 0;
    int cli_FD;

    if ((cli_FD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Failed to create socket");
        conn.err = SOCKET_FAILED;
        return conn;
    }
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER, &serverAddr.sin_addr) != 1){
        printf("Failed to convert server address to bytes");
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    if (connect(cli_FD, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0){
        printf("Connection to server failed");
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    conn.fd = cli_FD;
    return conn;
}

void utilClientCloseConnection(int fd, MemoryStack *memoryStack){
    // Stop listening and sending
    if (shutdown(fd, 2) != 0){
        utilExitPanic(SHUTDOWN_FAILED, "Failed to shutdown socket",memoryStack);
    }

    if (close(fd) != 0){
        utilExitPanic(CLOSE_FAILED, "Failed to close socket", memoryStack);
    }
}

void utilClientSend(Request *request, MemoryStack *memoryStack){
    char buf[512] = { 0 };
    size_t bufLength = 512 - 1;
    struct connection conn = utilClientConnect();
    
    if (conn.err != 0){
        utilExitPanic(SEND_FAILED, "No Socket", memoryStack);
    }
    
    if (send(conn.fd, request->data, request->length, 0) < 0){
        utilExitPanic(SEND_FAILED, "Failed to send data to socket", memoryStack);
    }
    printf("[CLIENT]: Sent payload data: %s, of length: %d", request->data, request->length);

    if (read(conn.fd, buf, bufLength) < 0){
        utilExitPanic(RECV_FAILED, "Failed to read data from socket", memoryStack);
    }

    utilClientCloseConnection(conn.fd, memoryStack);
}
