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








#endif