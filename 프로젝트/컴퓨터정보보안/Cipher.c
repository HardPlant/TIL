#include "math_util.c"


typedef struct rsa_key {
char block [128];
} RSA_KEY;

char* AES(char* block, char* key){

}

char* DES(char* block, char* key){

}

char* RSA(int plain, RSA_KEY key){
int e,d;
int N = (e-1)*(d-1);
int cipher = pow (,) % N;
}