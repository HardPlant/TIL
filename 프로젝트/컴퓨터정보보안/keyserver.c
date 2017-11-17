#include <stdlib.h>

static int id[100];


int keyserver_init(){
    return 1;
}

int keyserver_get_id(int index){
    return id[index];
}

int keyserver_try_login(int id){
    return 1;
}