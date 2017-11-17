#include <stdlib.h>
#define MAX_PEER 2
typedef struct{
    int id_pair[MAX_PEER];
    int id_state[MAX_PEER];
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
    server->id_pair[id] = pw;
    return 1;
}

int keyserver_get_id(KEY_SERVER* server, int index){

    return server->id_pair[index];
}

int keyserver_try_login(KEY_SERVER* server, int id){
    if(id == keyserver_get_id(server,id)) return 1;
    return 0;
}