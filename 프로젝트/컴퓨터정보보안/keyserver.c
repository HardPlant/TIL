#include <stdlib.h>
#define MAX_PEER 2

typedef int PUBLIC_KEY_TYPE;

typedef struct {
    PUBLIC_KEY_TYPE pub;
    PUBLIC_KEY_TYPE pri;
} KEY_PAIR;

typedef struct{
    int passwords[MAX_PEER];
    int publics[MAX_PEER];
    KEY_PAIR* key_pair[MAX_PEER];

    int public_key;
} KEY_SERVER;



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