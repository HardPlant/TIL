#define MSG_LENGTH 1000
#include <stdio.h>

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


