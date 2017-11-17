#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include "keyserver.c"
/*
#include "client.c"
#include "server.c"

*/
void startKeyServer();
void startChat();
void* keyserver_start(void* data);
void* client_start(void* data);
void* server_start(void* data);

int main(int argc, char* argv[]){
    char input = '0';

    printf("키 서버입니까?: (Y/N)");
    while(!(input == 'Y' || input == 'N'))
        input = getchar();
    
        if(input == 'Y') startKeyServer();
    if(input == 'N') startChat();

    return 0;
}

void startKeyServer(){
    pthread_t key_server;
    int server_port;

    pthread_create(&key_server, NULL, keyserver_start, (void*)&server_port);
    pthread_join(key_server, NULL);
}
void startChat(){
    void* client_args[2];
    char client_addr[100];
    int client_port;
    int server_port;

    client_args[0] = (void*)client_addr;
    client_args[1] = (void*)&client_port;


    pthread_t client;
    pthread_t server;
    pthread_create(&client, NULL, client_start, (void*)client_args);
    pthread_create(&server, NULL, server_start, (void*)server_port);
    pthread_join(client, NULL);
    pthread_join(server, NULL);
}


void* keyserver_start(void* data){
    int port = *( (int*)data );
    int listen_fd, connection_fd;
    struct sockaddr_in serve_addr;

    void* handler_args[2];
    pthread_t handler;
    printf("Keyserver\n");
    
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
        pthread_create(handler, NULL, keyserver_handler, handler_args);
    }   
}

void* keyserver_handler(void* data){
    int conn_fd = *( (int*)data[0] );
    char* client_addr = (char*)data[1];

    int server_key = 10;
    KEY_SERVER* server = keyserver_init(server_key);
    char recv[1000];
    char send[1000];

    bzero(recv, sizeof(recv));
    read(conn_fd, recv, sizeof(recv));
    int from = atoi(recv);

    bzero(recv, sizeof(recv));
    read(conn_fd, recv, sizeof(recv));
    int to = atoi(recv);

    bzero(send, sizeof(send));
    int result = keyserver_try_login(server, from, to);
    sprintf(send, "%d", result);
    write(conn_fd, send, sizeof(send));
}

void* client_start(void* data){
    char* dest_addr = (char*)data[0];
    int port = *( (int*)data[1] );
    printf("Client\n");

    int sockfd;
    struct sockaddr_in client_addr;
    pthread_t handler;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&client_addr,sizeof(client_addr));

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    inet_pton(AF_INET, dest_addr, &(client_addr.sin_addr));
    connect(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
    while(1){

    }
}

void* server_start(void* data){
    int port = *( (int*)data );
    int listen_fd, connection_fd;
    struct sockaddr_in serve_addr;
    pthread_t handler;
    printf("Server\n");
    
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serve_addr,sizeof(serve_addr));

    serve_addr.sin_family = AF_INET;
    serve_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serve_addr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr*) &serve_addr, sizeof(serve_addr));

    listen(listen_fd, 10);
    
    while(1){
        connetion_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
        pthread_create(handler, NULL, server_handler, &connetion_fd);
    }   
}
void* server_handler(void* data){
    int conn_fd = *( (int*)data );
}

