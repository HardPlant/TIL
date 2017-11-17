#include <stdlib.h>

typedef struct{
    int id_pair[2];
} KEY_SERVER;

int id_compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}

KEY_SERVER* keyserver_init(){
    return (KEY_SERVER*) malloc(sizeof(KEY_SERVER));
}

int keyserver_KEY_set_id(KEY_SERVER* server, int id, int pw){
    server->id_pair[id] = pw;
    return 1;
}

int keyserver_get_id(KEY_SERVER* server, int index){

    return server->id_pair[index];
}
/*
int keyserver_try_login(int id){
    if(id == key_server_get_id(id)) return 1;
    return 0;
}
/**/