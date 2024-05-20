#include"utillib.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

struct connection utilClientConnect(){
    struct sockaddr_in serverAddr;
    struct connection conn;

    conn.fd = NULL;
    conn.err = NULL
    
    if ((cli_FD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Failed to create socket");
        conn.err = SOCKET_FAILED;
        return conn;
    }
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER, &serverAddr.sin_addr) != 1){
        printf("Failed to convert server address to bytes in %s", __function__);
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    if ((status = connect(cli_FD, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0){
        printf("Connection to server failed");
        conn.err = CONNECTION_FAILED;
        return conn;
    }

    conn.fd = cli_FD;
    return conn;
}

void utilClientCloseConnection(int cli_FD){
    // Stop listening and sending
    if (shutdown(cli_FD, 2) != 0){
        printf("Failed to shutdown socket");
        return SHUTDOWN_FAILED;
    }

    if (close(cli_FD) != 0){
        printf("Failed to close socket");
        return CLOSE_FAILED;
    }

    return CLOSE_SUCCESSFUL;

void utilClientSend(Request *request){
    char buf[512] = { 0 };
    size_t bufLength = 512 - 1; // subtract 1 for null terminator
    struct connection conn = clientConnect();
    
    if (conn.err != NULL){
        printf("No socket");
        return SEND_FAILED;
    }
    
    if (send(conn.fd, request.data, request.length, 0) < 0){
        printf("Failed to send data to socket");
        return SEND_FAILED;
    }
    printf("[CLIENT]: Sent payload data: %s, of length: %d", request.data, request.length);

    if (read(conn.fd, buf, bufLength) < 0){
        printf("Failed to read data from socket");
        return RECV_FAILED;
    }



    if (clientCloseConnection(conn.fd) != CLOSE_SUCCESSFUL){
        printf("Failed to close connection!");
        return CONNECTION_CLOSE_ERROR;
    }

    return SEND_SUCCESSFUL;
}
