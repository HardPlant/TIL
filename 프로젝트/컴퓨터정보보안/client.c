#define MSG_LENGTH 1000
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

int client_init(){
    return 1;
}

char* client_send_msg(int fd){
    char sendline[MSG_LENGTH];
    bzero(sendline, MSG_LENGTH);

    fgets(sendline, MSG_LENGTH - 1, stdin);
    
    write(fd, sendline, strlen(sendline));
    return sendline;
}

int client_connect_key_server(){
    return 0;
}

int client_recv_pub_key(){
    return 0;
}

int client_send_chat_init(){

}
int client_recv_chat_init_ack(){

}