#include <stdlib.h>

static int g_id[100];

int id_compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}

int keyserver_init(){
    return 1;
}

int keyserver_get_id(int index){
    int* id = (int*) bsearch(&index, g_id
        , sizeof(g_id)/sizeof(int), sizeof(int), id_compare);
    return *id;
}

int keyserver_try_login(int id){
    return 1;
}