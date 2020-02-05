#include <iostream>
#include <cstdlib>
#include <string>
#include "SubstChiffre.hpp"

using namespace std;
using namespace CRYPTO;

void demoCrypSys();
void demoVigenere();
void demoText();

int main()
{
    srand(time(NULL));
    try{

    }catch(string &msg){
    	cout << "error: " << msg << endl;
    }catch(...){
    	cout << "unknown error.\n";
    }

}

void demoText(){
    DATASOURCE::EnDeCryptedDataSource e;
    CRYPTO::ICryptoSys  *ptrS;
    Vigenere  s;
    ptrS =  (CRYPTO::ICryptoSys *) (&s);


    try{
    	e.setAlphabet("abcd");

    	//e.setCryptoSystem(ptrS);
    	//e.init("plainAAAA_000.dat");
    	//cout << e.getPlainText(10,20) << endl;
    }catch(string &msg){
    	cout << msg << endl;
    }catch(...){
    	cout << "unknown error\n";
    }
}


void demoVigenere(){
	Vigenere  s;
	s.initAlphabet("abcdefghijklmnopqrstuvwxyz0123456789_");
	string key, m, mm, c;

	cout << "key:";
	cin >> key;
	s.generateRandomKey(1,(unsigned int)key.length());

	s.setKey(key);


	while(1){
		cout << "m:";
		cin >> m;

		c  = s.encrypt(m);
		mm = s.decrypt(c);
		cout << "\n\nk :'" << key <<"'\n";
		cout << "m :'" << m <<"'\n";
		cout << "c :'" << c <<"'\n";
		cout << "mm:'" << mm <<"'\n\n\n";
	}
}

void demoCrypSys(){
    CryptoSystemFactory f;
    ICryptoSys *s;
    string c, m, mm;
    bool newProc, quit;

    cout << "USE THE FOLLOWING COMMAND AS INPUT MESSAGE ";
    cout << "TO CHANGE ENCRYPTION, CHANGE KEY AND QUIT APPLICATION:\n";
    cout << "   NEWPROC\n";
    cout << "   NEWKEY\n";
    cout << "   QUITQUIT\n\n\n";

    try{
    	while(1){
    		newProc = false;
    		s = f.getCryptoSystem();
    		cout << "PROC: " << s->name() << endl;
			s->initAlphabet("abcdefghijklmnopqrstuvwxyz_");
			cout << "USE THE FOLLOWING ALPHABET:\n'"<< s->getAlphabet() << "'" << endl << endl;

    		while(1){
    			s->generateRandomKey();
    			cout << "KEY FOR " << s->name() << ": '" << s->getKey() << "'"<< endl << endl;
    			while(1){
    				cout << "INPUT MESSAGE: ";
    				cin >> m;
    				if(m.compare(0,6,"NEWKEY")  == 0){ break;};
    				if(m.compare(0,7,"NEWPROC") == 0){ newProc = true; break;};
    				if(m.compare(0,8,"QUITQUIT") == 0){ quit    = true; break;};
    				c  = s->encrypt(m);
    				mm = s->decrypt(c);
    				cout << "m : '" << m << "'\nc : '" << c << "'\nmm: '" << mm <<"'\n\n";
    			};
    			cout << "\n\n";
    			if(newProc || quit){
    				delete s;
    				break;
    			}
    		};
    		if(quit) break;
    	};
    }catch(string &msg){
        cout << msg << endl;
    }catch(...){
        cout << "UNKNOWN ERROR\n";
    }
    cout << endl << "BYE BYE!"<< endl << endl << endl;
    return;
}
