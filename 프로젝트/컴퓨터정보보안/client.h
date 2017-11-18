#ifndef CLIENT_H
#define CLIENT_H


int client_init();
char* client_send_msg(int fd);

int client_connect_key_server();

int client_recv_pub_key();
int client_send_chat_init();
int client_recv_chat_init_ack();





#endif