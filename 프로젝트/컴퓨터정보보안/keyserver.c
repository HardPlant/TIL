#include <stdlib.h>

static int g_id_pair[2];

int id_compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}

int keyserver_init(){
    g_id_pair[0] = 2; // A: id : 1, pw : 2

    g_id_pair[1] = 4; // B : id : 3, pw : 4

    return 1;
}

int keyserver_get_id(int index){
    return g_id_pair[index];
}

int keyserver_try_login(int id){
    return 1;
}