#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>


void* tcp_server(void* data){
    void* (*handler)(void*) = data[0];
    int port = *( (int*)data[1] );

    int listen_fd, connection_fd;
    struct sockaddr_in serve_addr;

    void* handler_args[2];
    pthread_t handler;
    
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serve_addr,sizeof(serve_addr));

    serve_addr.sin_family = AF_INET;
    serve_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serve_addr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr*) &serve_addr, sizeof(serve_addr));

    listen(listen_fd, 10);
    
    while(1){
        struct sockaddr* dest_addr;
        bzero(dest_addr);
        connetion_fd = accept(listen_fd, (struct sockaddr*)dest_addr, NULL);
        handler_args[0] = (void*) &connetion_fd;
        handler_args[1] = (void*) dest_addr;
        pthread_create(handler, NULL, handler, handler_args);
    }   
}

void* tcp_client(void* data){
    void* (*handler)(void*) = data[0];
    char* dest_addr = (char*)data[1];
    int port = *( (int*)data[2] );

    int sockfd;
    struct sockaddr_in client_addr;
    pthread_t handler;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&client_addr,sizeof(client_addr));

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    inet_pton(AF_INET, dest_addr, &(client_addr.sin_addr));
    while(1){
        connect(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
        handler((void*) &sockfd);
    }
}