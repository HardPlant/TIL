#include "math_util.c"


typedef struct rsa_key {
char block [128];
} RSA_KEY;

char* AES(char* block, char* key){

}

char* DES(char* block, char* key){

}

char* RSA(int plain, RSA_KEY key){
    RSA_TYPE p, q, N, pi;

    rsa_get_coprime(p,q);

    
}