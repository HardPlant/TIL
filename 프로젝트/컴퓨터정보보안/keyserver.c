#include "keyserver.h"

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


int id_compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}

KEY_SERVER* keyserver_init(int public_key){
    KEY_SERVER* server = (KEY_SERVER*) malloc(sizeof(KEY_SERVER));
    server->public_key = public_key;
    return server;
}

int keyserver_set_id(KEY_SERVER* server, int id, int pw){
    server->passwords[id] = pw;
    return 1;
}

int keyserver_get_pw(KEY_SERVER* server, int id){

    return server->passwords[id];
}

int keyserver_try_login(KEY_SERVER* server, int id, int pw){
    if(pw != keyserver_get_pw(server,id)) return 0;
    return 1;    
}

int keyserver_set_public_key(KEY_SERVER* server, int id, int key){
    if(server->key_pair[id] == NULL)
        server->key_pair[id] = (KEY_PAIR*) malloc(sizeof(KEY_PAIR));

    server->key_pair[id]->pub = key;
    return 1;
}

int keyserver_get_public_key(KEY_SERVER* server, int id){
    return server->key_pair[id]->pub;
}