#include <iostream>
#include <cstdlib>
#include "SubstChiffre.hpp"

using namespace std;
using namespace CRYPTO;

void demoVigenere();
void demoCaesar();
void demoSubChiffre();

int main()
{
    srand(time(NULL));
    //demoVigenere();
    //demoCaesar();
    demoSubChiffre();
}

void demoSubChiffre(){
    string c, m, mm;
    try{
        SubChiffre *s = new SubChiffre();
        s->initAlphabet("abcdefghijklmnopqrstuvwxyz_");
        cout << "Use the following alphabet:\n"<< s->getAlphabet() << endl << endl;

        s->generateRandomKey();
        cout << s->getKey() << endl;

        while(1){
            cout << "input message: ";
            cin >> m;
            c  = s->encrypt(m);
            mm = s->decrypt(c);
            cout << "m : '" << m << "'\nc : '" << c << "'\nmm: '" << mm <<"'\n";
        }
    }catch(string msg){
        cout << msg << endl;
    }catch(...){
        cout << "unknown error\n";
    }
    cout << endl << endl << endl;
    return;
}

void demoCaesar(){
    string c, m, mm;
    unsigned int k;
    try{
        Caesar *s = new Caesar();
        s->initAlphabet("abcdefghijklmnopqrstuvwxyz_");
        cout << "Use the following alphabet:\n"<< s->getAlphabet() << endl << endl;

        while(1){
            cout << "input message: ";
            cin >> m;
            cout << "input key: ";
            cin >> k;
            s->setKey(k);
            k = s->getKey();
            c = s->encrypt(m);
            mm = s->decrypt(c);
            cout << "m : '" << m << "'\nk : '" << k << "'\nc : '" << c << "'\nmm: '" << mm <<"'\n";
        }
    }catch(string msg){
        cout << msg << endl;
    }catch(...){
        cout << "unknown error\n";
    }
    cout << endl << endl << endl;
    return;
}

void demoVigenere(){
    string k, c, m, mm;
    try{
        Vigenere *s = new Vigenere();
        s->initAlphabet("abcdefghijklmnopqrstuvwxyz_");
        cout << "Use the following alphabet:\n"<< s->getAlphabet() << endl << endl;

        while(1){
            cout << "input message: ";
            cin >> m;
            cout << "input key: ";
            cin >> k;
            s->generateRandomKey(1,k.size());
            s->setKey(k);
            k = s->getKey();
            c = s->encrypt(m);
            mm = s->decrypt(c);
            cout << "m : '" << m << "'\nk : '" << k << "'\nc : '" << c << "'\nmm: '" << mm <<"'\n";
        }
    }catch(string msg){
        cout << msg << endl;
    }catch(...){
        cout << "unknown error\n";
    }
    cout << endl << endl << endl;
    return;
}
