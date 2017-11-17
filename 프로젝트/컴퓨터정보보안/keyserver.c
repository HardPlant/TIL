#include <stdlib.h>

typedef struct{
    int id_pair[2];
} SERVER;

int id_compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}

SERVER* keyserver_init(){
    return NULL;
}

int keyserver_set_id(int id, int pw){
//    g_id_pair[id] = pw;
    return 1;
}

int keyserver_get_id(int index){
  //  return g_id_pair[index];
}

int keyserver_try_login(int id){
    if(id == keyserver_get_id(id)) return 1;
    return 0;
}