#include <gmpxx.h>
#include <gmp.h>
#include <time.h>
#include <iostream>
#include "RSA.h"
using namespace std;

RSAKey GloKey;

void test(mpz_class p, mpz_class q, mpz_class e, mpz_class mess){
    mpz_class x, y;
    GloKey.n = p*q;
    mpz_class ou_n=(p - 1)*(q - 1);
    extend_euclid(e, ou_n, x, y);
    GloKey.d = (x % ou_n + ou_n) % ou_n;
    GloKey.e = e;
    mpz_class encry = RSA(GloKey, mess, 0);
    cout<<"Encode:"<<endl<<encry<<endl;
    cout<<"Decode:"<<endl<<RSA(GloKey, encry, 1);
}

int main() {
    /*
    mpz_class a,b,c;
    cin>>a>>b>>c;
    cout<<FastPow(a,b,c);
    */
    int op;
    cout<<"Choose an opcode: 1.Test 2.Encode 3.Decode 4.Init and Run"<<endl;
    cin>>op;
    if(op==1){
        mpz_class p, q, e, mess;
        bool mode;
        cout<<"Please enter p q e and message"<<endl;
        cin>>p>>q>>e>>mess;
        test(p, q, e, mess);
    }
    else if(op==2){
        GloKey = gene_key(512);
        mpz_class mess;
        cout<<"Please enter message:"<<endl;
        cin>>mess;
        cout<<"Encode:"<<endl<<RSA(GloKey, mess, 0)<<endl;
    }
    else if(op==3){
        GloKey = gene_key(512);
        mpz_class mess;
        cout<<"Please enter message"<<endl;
        cin>>mess;
        cout<<"Decode:"<<endl<<RSA(GloKey, mess, 1)<<endl;
    }
    else{
        cout<<"Generate Keys, Please Wait..."<<endl;
        GloKey = gene_key(512);
        while(1){
            int op1;
            cout<<"Please enter opcode: 0 for encode, 1 for decode, 2 for exit"<<endl;
            cin>>op1;
            if(op1 == 0){
                mpz_class mess;
                cout<<"Please Enter the message: "<<endl;
                cin>>mess;
                cout<<"Encode:"<<endl<<RSA(GloKey, mess ,op1)<<endl;
            }
            else if(op1 == 1){
                mpz_class mess;
                cout<<"Please Enter the message: ";
                cin>>mess;
                cout<<"Decode:"<<endl<<RSA(GloKey, mess, op1)<<endl;
            }
            else{
                return 0;
            }
        }
    }
}


