#include <stdio.h>
#include <pthread.h>
/*
#include "client.c"
#include "server.c"
#include "keyserver.c"
*/
void startKeyServer();
void startChat();
void keyserver_init(){ printf("Keyserver\n");}
void client_init(){ printf("Client\n");}
void server_init(){ printf("Server\n");}

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
    pthread_create(&key_server, NULL keyserver_init, NULL);

}
void startChat(){
    pthread_t client;
    pthread_t server;
    pthread_create(&client, NULL, client_init, NULL);
    pthread_create(&server, NULL, server_init, NULL);
    
}


