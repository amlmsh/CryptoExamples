#ifndef SUBSTCHIFFRE_HPP_INCLUDED
#define SUBSTCHIFFRE_HPP_INCLUDED

#include <string>
#include <vector>

using namespace std;


namespace CRYPTO{

const char UNDEFINED_CHAR='\0';

const string DEFAULT_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:'+-=)({}[]?!_";

class ICryptoSys;

class ICryptoSystemFactory{
public:
    virtual ICryptoSys *getCryptoSystem(int ID) = 0;
};

class CryptoSystemFactory : public ICryptoSystemFactory{
public:
    ICryptoSys *getCryptoSystem(int ID);
};

class ICryptoSys{
public:
    virtual void   initAlphabet(string a) = 0;
    virtual string getAlphabet() = 0;
    virtual string encrypt(string m) = 0;
    virtual string decrypt(string c) = 0;
    virtual void   generateRandomKey() = 0;
};

class CryptoSys : public ICryptoSys{
public:
    CryptoSys();
    virtual void   initAlphabet(string a);
    virtual string encrypt(string m);
    virtual string decrypt(string c);
    string getAlphabet();

protected:
    bool isDuplicate(char *l, int maxIdx, char c);
    bool isMsgValid(string msg);

    virtual string myEncryptionProc(string m) = 0;
    virtual string myDecryptionProc(string c) = 0;

    unsigned int M2C(char c);

    char *alphabet_;
    unsigned int sizeAlphabet_;


};

class Vigenere : public CryptoSys{
public:
    Vigenere();
    Vigenere(unsigned int minKeySize, unsigned int maxKeysize);
    void   generateRandomKey(unsigned int minKeySize, unsigned int maxKeysize);
    void   generateRandomKey();
    string getKey();
    void   setKey(string k);
protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);
    string key_;

    unsigned int keySize_;
    unsigned int minKeySize_;
    unsigned int maxKeySize_;

};

class Caesar : public CryptoSys{
public:
    Caesar();
    void         generateRandomKey();
    unsigned int getKey();
    void         setKey(unsigned int k);
protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);
    unsigned int key_;
};


class SubChiffre : public CryptoSys{
public:
    SubChiffre();
    void         generateRandomKey();
    string       getKey();
protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);

    unsigned int C2M(char c);

    char *key_;
};


} // end namespace CRYPTO







#endif // SUBSTCHIFFRE_HPP_INCLUDED
