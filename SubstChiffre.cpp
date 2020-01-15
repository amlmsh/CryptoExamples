#include "SubstChiffre.hpp"

#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;

namespace CRYPTO{


ICryptoSys *CryptoSystemFactory::getCryptoSystem(int ID){
    return new Vigenere();
}


CryptoSys::CryptoSys(){
    sizeAlphabet_ = 0;
    alphabet_ = NULL;
    initAlphabet(DEFAULT_ALPHABET);
}

void   CryptoSys::initAlphabet(string a){
    if(alphabet_ != NULL){
        delete alphabet_;
        alphabet_ = NULL;
        sizeAlphabet_ = 0;
    }
    sizeAlphabet_= a.size();
    if(sizeAlphabet_< 2) {
        throw string("Alphabet to small. It contains less than two letter.");
    }

    alphabet_= new char[sizeAlphabet_];
    for(unsigned int i=0; i <sizeAlphabet_; i++){
        alphabet_[i] = toupper(a[i]);
        if(isDuplicate(alphabet_,i-1,alphabet_[i])){
            string msg = string("Alphabet contains duplicates of '") + alphabet_[i] + string("'.");
            delete alphabet_;
            alphabet_ = NULL;
            sizeAlphabet_ = 0;
            throw msg;
        }
    }
}

bool CryptoSys::isMsgValid(string msg){
    unsigned int msgSize;
    msgSize = msg.size();

    for(unsigned int i=0; i < msgSize; i++){
        if(! isDuplicate(alphabet_,sizeAlphabet_-1,toupper(msg[i])) ) {
            return false;
        }
    }
    return true;
}


bool CryptoSys::isDuplicate(char *l, int maxIdx, char c){
    for(int i=0; i<=maxIdx;i++){
        if(l[i] == c) return true;
    }
    return false;
}

string CryptoSys::getAlphabet(){
    stringstream ss;
    ss << "";
    for(unsigned int i=0; i <sizeAlphabet_; i++){
        ss << alphabet_[i];
    }
    return ss.str();
}

string CryptoSys::encrypt(string m){
    if(!isMsgValid(m)){
        throw string("Message contains char that doesn't belong to the defined alphabet.");
    }
    return myEncryptionProc(m);
}

string CryptoSys::decrypt(string c){
    return myDecryptionProc(c);
}


Vigenere::Vigenere():Vigenere(1,5){
}

Vigenere::Vigenere(unsigned int minKeySize, unsigned int maxKeySize) : CryptoSys(){
    if( (minKeySize < 1) || (maxKeySize < minKeySize)){
        throw string("Vigenere : min / max key size worng.");
    }

    initAlphabet(DEFAULT_ALPHABET);
    minKeySize_ = minKeySize;
    maxKeySize_ = maxKeySize;
    generateRandomKey();
}

string Vigenere::myEncryptionProc(string m){
    string c("");

    // add letter values
    for(unsigned int i=0; i<m.size(); i++){
        c += ( ( M2C(m[i]) + M2C(key_[i % keySize_]) ) % sizeAlphabet_ );
        if(c[i] < 1){
            c[i] = (c[i] + sizeAlphabet_) ;
        }
    }

    // calculation results to letters
    for(unsigned int i=0; i<m.size(); i++){
        c[i] = tolower(alphabet_[c[i] % sizeAlphabet_]);
    }
    return c;
}

string Vigenere::myDecryptionProc(string c){
    string m("");

    // add letter values
    for(unsigned int i=0; i<c.size(); i++){
        m += ( ( M2C(c[i]) - M2C(key_[i % keySize_]) )  ) ;
        if(m[i] < 1){
            m[i] = (m[i] + sizeAlphabet_) ;
        }
    }

    // calculation results to letters
    for(unsigned int i=0; i<c.size(); i++){
        m[i] = alphabet_[m[i] % sizeAlphabet_];
    }
    return m;
}
void   Vigenere::generateRandomKey(){
    generateRandomKey(minKeySize_,maxKeySize_);
}

void   Vigenere::generateRandomKey(unsigned int minKeySize, unsigned int maxKeySize){
    if( (minKeySize < 1) || (maxKeySize < minKeySize)){
        throw string("Vigenere : min / max key size worng.");
    };
    minKeySize_ = minKeySize;
    maxKeySize_ = maxKeySize;
    if(maxKeySize_ == minKeySize_){
        keySize_ = minKeySize_;
    }else{
        keySize_ = ( rand() % (maxKeySize_ - minKeySize_ + 1) ) + minKeySize_;
    }
    key_ = string("");
    for(unsigned int i=0; i<keySize_; i++){
        key_ = key_ + ( alphabet_[rand() % sizeAlphabet_]);
    }
}


string Vigenere::getKey(){
    return key_;
}

void   Vigenere::setKey(string k){
    if( (k.size() < minKeySize_) || (k.size() > maxKeySize_)){
        throw string("new key is not in the given key size range.");
    };

    if(!isMsgValid(k)){
        throw string("setKey: key contains char that doesn't belong to the defined alphabet.");
    }

    key_ = string("");
    for(unsigned int i=0; i < k.size(); i++){
        key_ = key_ + k[i];
    }
    keySize_ = key_.size();
    return;
}

unsigned int CryptoSys::M2C(char c){
    for(unsigned int i=0; i < sizeAlphabet_; i++){
        if(alphabet_[i] == toupper(c) ){
            return i;
        }
    }
    throw string("M2C: given char does not belong to the current alphabet.");
}


Caesar::Caesar() : CryptoSys(){
    generateRandomKey();
}
void Caesar::generateRandomKey(){
    key_ = (rand() % (sizeAlphabet_ - 1)) + 1;
}

unsigned int Caesar::getKey(){
    return key_;
}

void Caesar::setKey(unsigned int k){
    if( (k < 1) || (k>(sizeAlphabet_ - 1)) ){
        throw string("setKey the given key value is aout of range.");
    }
    key_ = k;
}

string Caesar::myEncryptionProc(string m){
    string c("");

    // add letter values
    for(unsigned int i=0; i<m.size(); i++){
        c += ( ( M2C(m[i]) + key_) % sizeAlphabet_ );
        if(c[i] < 1){
            c[i] = (c[i] + sizeAlphabet_) ;
        }
    }

    // calculation results to letters
    for(unsigned int i=0; i<m.size(); i++){
        c[i] = tolower(alphabet_[c[i] % sizeAlphabet_]);
    }
    return c;
}

string Caesar::myDecryptionProc(string c){
    string m("");

    // add letter values
    for(unsigned int i=0; i<c.size(); i++){
        m += (M2C(c[i]) - key_);
        if(m[i] < 1){
            m[i] = (m[i] + sizeAlphabet_) ;
        }
    }

    // calculation results to letters
    for(unsigned int i=0; i<c.size(); i++){
        m[i] = alphabet_[m[i] % sizeAlphabet_];
    }
    return m;
}



SubChiffre::SubChiffre() : CryptoSys(){
    key_ = NULL;
    generateRandomKey();
}

void SubChiffre::generateRandomKey(){
    if(key_ != NULL){
        delete key_;
        key_ = NULL;
    }

    key_ = new char[sizeAlphabet_];
    for(unsigned int i=0; i<sizeAlphabet_;i++){
        key_[i] = tolower(alphabet_[i]);
    }

    char c;
    unsigned int idx;
    for(unsigned int i=0; i<sizeAlphabet_; i++){
        idx = rand() % sizeAlphabet_;
        //swap
        c = key_[i];
        key_[i] = key_[idx];
        key_[idx] = c;
    }

}

string SubChiffre::myEncryptionProc(string m){
    string c("");
    for(unsigned int i=0; i < m.size(); i++){
        c += key_[M2C(m[i])];
    }
    return c;
}

string SubChiffre::myDecryptionProc(string c){
    string m("");
    for(unsigned int i=0; i < c.size(); i++){
        m += alphabet_[C2M(c[i])];
    }
    return m;
}

unsigned int SubChiffre::C2M(char c){
    for(unsigned int i=0; i < sizeAlphabet_; i++){
        if(key_[i] == tolower(c) ){
            return i;
        }
    }
    throw string("C2M: given char does not belong to the current alphabet.");
}


string  SubChiffre::getKey(){
    stringstream ss;
    for(unsigned int i=0; i< sizeAlphabet_; i++){
        ss << "(" << alphabet_[i] << ", " << key_[i] << ")\n";
    }
    return ss.str();
}

} // end namespace CRYPTO
