#include <iostream>
#include <cstdlib>
#include <string>
#include "SubstChiffre.hpp"

using namespace std;
using namespace CRYPTO;

void demoCrypSys();

int main()
{
    srand(time(NULL));

    DATASOURCE::DataSource d;

    try{
    	d.init("plainAAAA_000.dat");
    }catch(string &msg){
    	cout << msg << endl;
    }catch(...){
    	cout << "unknown error\n";
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
