#ifndef KEYSERVER_H
#define KEYSERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

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

#include "keyserver.h"

void* keyserver_handler(void* data);

int id_compare(const void *a, const void *b);

KEY_SERVER* keyserver_init(int public_key);

int keyserver_set_id(KEY_SERVER* server, int id, int pw);
int keyserver_get_pw(KEY_SERVER* server, int id);
int keyserver_try_login(KEY_SERVER* server, int id, int pw);

int keyserver_set_public_key(KEY_SERVER* server, int id, int key);
int keyserver_get_public_key(KEY_SERVER* server, int id);






#endif