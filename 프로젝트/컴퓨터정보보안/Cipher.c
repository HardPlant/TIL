#include "math_util.c"


typedef struct rsa_key {
char block [128];
} RSA_KEY;

char* AES(char* block, char* key){

}

char* DES(char* block, char* key){

}

typedef struct {
    RSA_TYPE N;
    RSA_TYPE e; // public key
    RSA_TYPE d; // private key
} RSA_KEY_PAIR;

typedef struct {
    RSA_KEY_PAIR (*init)();
    RSA_TYPE (*encrypt)(RSA_TYPE msg, RSA_KEY_PAIR pair);
    RSA_TYPE (*decrypt)(RSA_TYPE enc, RSA_KEY_PAIR pair);

    RSA_KEY_PAIR pair;
} *RSA_CONTROLLER;

RSA_KEY_PAIR RSA_init(int plain, RSA_KEY key){
    RSA_TYPE p, q, N, pi, e, d;
    RSA_KEY_PAIR* pair = malloc(sizeof(RSA_KEY_PAIR));
    rsa_get_coprime(p,q);

    N = rsa_multi(p,q);
    pi = rsa_multi(rsa_minus(p,1),rsa_minus(q,1));

    e = rsa_get_minor_prime(pi);

    d = rsa_gcd(e, pi);

    rsa_set_public(pair, N, e);
    rsa_set_private(pair, d);

    return pair;
}

RSA_TYPE rsa_encrypt(RSA_TYPE msg, RSA_KEY_PAIR pair){
    return rsa_mod(rsa_exp(msg, pair->e),pair->N);
}

RSA_TYPE rsa_decrypt(RSA_TYPE enc, RSA_KEY_PAIR pair){
    return rsa_mod(rsa_exp(enc, pair->d),pair->N);
}

RSA_TYPE rsa_get_minor_prime(RSA_TYPE pi){
    
}
