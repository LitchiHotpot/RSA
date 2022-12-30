//
// Created by sokoface on 2022/12/26.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

struct prime2{
    mpz_class a;
    mpz_class b;
};

struct RSAKey{
    mpz_class n;
    mpz_class e;
    mpz_class d;
};

mpz_class FastPow(mpz_class a,mpz_class b,mpz_class mod,mpz_class ans = 1);
mpz_class extend_euclid(mpz_class s, mpz_class n, mpz_class &x, mpz_class &y);
mpz_class RSA(RSAKey key, mpz_class mess, bool mode);
RSAKey gene_key(int n);

#endif //RSA_RSA_H
