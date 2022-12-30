#include <gmpxx.h>
#include <gmp.h>
#include <time.h>
#include <iostream>
#include "RSA.h"
using namespace std;

mpz_class FastMul(mpz_class a,mpz_class b,mpz_class mod,mpz_class ans = 0){
    for(a %= mod;b;b>>=1){
        if(b%2==1) ans = (ans+a)%mod;
        a = (a+a)%mod;
    }
    return ans;
}

//逐次平方法
mpz_class FastPow(mpz_class a, mpz_class b, mpz_class mod, mpz_class ans) {
    //cout<<mod<<endl;
    for(a %= mod;b;b>>=1){
        if(b%2==1) ans = FastMul(ans,a,mod);
        a = FastMul(a,a,mod);
    }
    return ans;
}

bool miller_rabin(mpz_class n, mpz_class u = 0, int t = 0, int s = 10){
    if(n == 2)
        return true;
    if(n<2||n%2==0)
        return false;
    for(t = 0,u = n-1;!(u%2==1);t++,u>>=1);//计算出2^t*u
    while(s--){   //进行s次验证，避免出现强伪证的情况
        mpz_class a = rand()%(n-1)+1;//取随机数
        mpz_class x = FastPow(a,u,n);//计算a^u(mod n)
        for(int i=0;i<t;i++){
            mpz_class y = FastMul(x,x,n);//计算a^2rd(mod n)
            if(y == 1&&x!=1&&x!=n-1)
                return false;
            x = y;
        }
        if(x!=1)return false;
    }
    return true;
}

prime2 gene_2bigprime(int n){
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // 设置随机数种子
    unsigned long seed = time(0);
    gmp_randseed_ui(state, seed);

    // 生成随机数
    mpz_class t;
    prime2 primes;
    int i=0;
    while(1){
        mpz_urandomb(t.get_mpz_t(), state, n);
        if(t % 2 == 0) continue;
        if(miller_rabin(t)&&i==0) {
            primes.a=t;
            i++;
        }
        else if(miller_rabin(t)&&i==1) {
            primes.b = t;
            return primes;
        }
    }
}

mpz_class euler_func(mpz_class n) {
    mpz_class result = n;
    for (mpz_class i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

mpz_class extend_euclid(mpz_class s, mpz_class n, mpz_class &x, mpz_class &y) {
    if(!n){
        x = 1, y = 0;
        return s;
    }
    mpz_class x1, y1, Gcd;
    Gcd = extend_euclid(n, s % n, x1, y1);
    x = y1;
    y = x1 - s / n * y1;
    return Gcd;
}

mpz_class RSA(RSAKey key, mpz_class mess, bool mode) {
    mpz_class out;
    if(!mode){
        out = FastPow(mess, key.e, key.n);
    }
    else{
        out = FastPow(mess, key.d, key.n);
    }
    return out;
}

RSAKey gene_key(int n) {
    RSAKey newkey;
    prime2 primes = gene_2bigprime(n);
    cout<<"Generate P and Q:"<<endl;
    cout<<"P: "<< primes.a <<endl;
    cout<<"Q: "<< primes.b <<endl;
    newkey.n = primes.a * primes.b;
    mpz_class  x, y;
    mpz_class ou_n=(primes.a - 1)*(primes.b - 1);
    extend_euclid(65537, ou_n, x, y);
    newkey.d = (x % ou_n + ou_n) % ou_n;
    newkey.e = 65537;
    return newkey;
}
