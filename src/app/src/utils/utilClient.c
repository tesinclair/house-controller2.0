#include"utillib.h"
#include<arpa/inet.h>
#include<sys/socket.h>

struct connection utilClientConnect(){
    struct sockaddr_in serverAddr;
    struct connection conn;

    conn.err = 0;
    int cli_FD;

    if ((cli_FD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        g_print("Failed to create socket\n");
        conn.err = SOCKET_FAILED;
        return conn;
    }
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER, &serverAddr.sin_addr) != 1){
        g_print("Failed to convert server address to bytes\n");
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    if (connect(cli_FD, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0){
        g_print("Connection to server failed\n");
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    conn.fd = cli_FD;
    return conn;
}

void utilClientCloseConnection(int fd, MemoryStack *memoryStack){
    // Stop listening and sending
    if (shutdown(fd, 2) != 0){
        utilErrorPanic(SHUTDOWN_FAILED, "Failed to shutdown socket\n",memoryStack);
    }

    if (close(fd) != 0){
        utilErrorPanic(CLOSE_FAILED, "Failed to close socket\n", memoryStack);
    }
}

void utilClientSend(Request *request, MemoryStack *memoryStack){
    char buf[512] = { 0 };
    size_t bufLength = 512 - 1;
    struct connection conn = utilClientConnect();
    
    if (conn.err != 0){
        utilErrorPanic(SEND_FAILED, "No Socket\n", memoryStack);
    }
    
    if (send(conn.fd, request->data, request->length, 0) < 0){
        utilErrorPanic(SEND_FAILED, "Failed to send data to socket\n", memoryStack);
    }
    g_print("[CLIENT]: Sent payload data: %s, of length: %d\n", request->data, request->length);

    if (read(conn.fd, buf, bufLength) < 0){
        utilErrorPanic(RECV_FAILED, "Failed to read data from socket\n", memoryStack);
    }

    utilClientCloseConnection(conn.fd, memoryStack);
}
