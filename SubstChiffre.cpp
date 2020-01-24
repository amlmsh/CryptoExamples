#include "SubstChiffre.hpp"

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace CRYPTO{

ICryptoSystemFactory::~ICryptoSystemFactory(){
	;
}

CryptoSystemFactory::~CryptoSystemFactory(){
	;
}

ICryptoSys *CryptoSystemFactory::getCryptoSystem(int ID){
	switch(ID){
		case 0:  return new Vigenere();
		case 1:  return new Caesar();
		default: return new SubChiffre();
	}
}

ICryptoSys *CryptoSystemFactory::getCryptoSystem(){
	int r = rand() % 3;
	return getCryptoSystem(r);
}



ICryptoSys::~ICryptoSys(){
	;
}

CryptoSys::CryptoSys(){
    sizeAlphabet_ = 0;
    alphabet_ = NULL;
    initAlphabet(DEFAULT_ALPHABET);
    name_ = string("undefined");
}

CryptoSys::~CryptoSys(){
	if(alphabet_ != NULL){
		delete alphabet_;
		alphabet_ = NULL;
	}
	sizeAlphabet_= 0;
}


string CryptoSys::name(){
    return (name_);
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
        alphabet_[i] = toupper((int)a[i]);
        if(i == 0) continue;
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
        if(! isDuplicate(alphabet_,sizeAlphabet_-1,toupper((int)msg[i])) ) {
            return false;
        }
    }
    return true;
}


bool CryptoSys::isDuplicate(char *l, unsigned int maxIdx, char c){
    for(int i=0; i<=maxIdx;i++){
        if(l[i] == c){
        	return true;
        }
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
        throw string("Message contains characters that doesn't belong to the defined alphabet.");
    }
    return myEncryptionProc(m);
}

string CryptoSys::decrypt(string c){
    if(!isMsgValid(c)){
        throw string("Message contains characters that doesn't belong to the defined alphabet.");
    }
    return myDecryptionProc(c);
}


Vigenere::Vigenere():Vigenere(1,5){
}

Vigenere::Vigenere(unsigned int minKeySize, unsigned int maxKeySize) : CryptoSys(){
    if( (minKeySize < 1) || (maxKeySize < minKeySize)){
        throw string("Vigenere : min / max key size wrong.");
    }

    initAlphabet(DEFAULT_ALPHABET);
    minKeySize_ = minKeySize;
    maxKeySize_ = maxKeySize;
    generateRandomKey();
    name_ = string("Vigenere");
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
        c[i] = tolower((int) (alphabet_[c[i] % sizeAlphabet_]) );
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
        throw string("Vigenere : min / max key size wrong.");
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
    name_ = string("Caesar");
}
void Caesar::generateRandomKey(){
    key_ = (rand() % (sizeAlphabet_ - 1)) + 1;
}

unsigned int Caesar::getCaesarKey(){
    return key_;
}

void Caesar::setKey(unsigned int k){
    if( (k < 1) || (k>(sizeAlphabet_ - 1)) ){
        throw string("setKey the given key value is aout of range.");
    }
    key_ = k;
}

string Caesar::getKey(){
	stringstream ss;
	ss << "";
	ss << getCaesarKey();
	return ss.str();
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
        c[i] = tolower((int) alphabet_[c[i] % sizeAlphabet_]);
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
    name_ = string("Substitution");
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
        ss << "('" << alphabet_[i] << "' <--> '" << key_[i] << "') ";
    }
    return ss.str();
}



} // end namespace CRYPTO


namespace DATASOURCE{

DataSource::DataSource(){
	fileName_ = string("");
	cryptoSys_ = NULL;
	return;
};

DataSource::~DataSource(){
	if(cryptoSys_ != NULL){
		delete cryptoSys_;
		cryptoSys_ = NULL;
	}
	return;
};

void DataSource::init(string filename){
	fileName_ = string(filename);
};

void DataSource::setCryptoSystem(CRYPTO::ICryptoSys *cSys){
	cryptoSys_ = cSys;
	return;
};

string DataSource::getPlainText(unsigned int idx, unsigned int blockSize){
	stringstream ss;
	FILE *dataFile;
	string resStr("");
	int c, cPre, line;

	if(cryptoSys_ == NULL){
		throw string("error: no crypto system initialized.");
	}

	try{
		dataFile = fopen(fileName_.c_str(),"r");
		if(dataFile == NULL){
			throw string("error: can not open file.");
		}

	}catch(...){
		throw string ("Unable to open file: " + fileName_);
	}

	line = 0;
	cPre = 'x';
	while ((c = fgetc(dataFile)) != EOF){
		if( ((char) c) == '\n' ){
			line++;
		}
		if( (line >= idx) && (line <= (idx + blockSize) ) ){
			if((char) c == ' '){
				if(cPre != ' '){
					ss << '_';
				};
				cPre = c;
				continue;
			}
			if(isCharPartOfAlphabet((char) c, cryptoSys_->getAlphabet())){ // check if character belongs to the alphabet.
				ss << (char) c;
			}
			cPre = c;
		}
	}
	return ss.str();
};

bool DataSource::isCharPartOfAlphabet(char c, string alphabet){
	return true;
}

string DataSource::getChiffreText(unsigned int idx, unsigned int blockSize){

	return getPlainText(idx,blockSize);
};


}; // end namespace DATASOURCE
