#define MSG_LENGTH 1000
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

int server_init(){
    return 1;
}

char* server_recv_msg(int fd){
    char recvline[MSG_LENGTH];
    bzero(recvline, MSG_LENGTH);

    read(fd, recvline, MSG_LENGTH);
    return recvline;
}