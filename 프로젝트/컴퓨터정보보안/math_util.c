#include <math.h>

#define true 1
#define false 0

typedef int RSA_TYPE;

RSA_TYPE rsa_max(RSA_TYPE a, RSA_TYPE b);
RSA_TYPE rsa_min(RSA_TYPE a, RSA_TYPE b);
RSA_TYPE rsa_multi(RSA_TYPE a, RSA_TYPE b);
RSA_TYPE rsa_divide(RSA_TYPE a, RSA_TYPE b);
RSA_TYPE rsa_modular(RSA_TYPE a, RSA_TYPE b);
RSA_TYPE rsa_switch(RSA_TYPE a, RSA_TYPE b);
int rsa_equal();

int is_prime(int a){
    int boundary = sqrt(a);
    for(int i=1;i<boundary;i++){
        if(a%boundary == 0) return false;
    }
    return true;
}

RSA_TYPE euclid_gcd(RSA_TYPE a, RSA_TYPE b){
    RSA_TYPE m = a;
    RSA_TYPE n = b;
    
    while(!rsa_equal(n,0)){
        if(rsa_equal(rsa_divide(m,n),0)) return n;
        m = rsa_modular(m,n);
        rsa_switch(m,n);
    }
}

