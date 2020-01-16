#ifndef SUBSTCHIFFRE_HPP_INCLUDED
#define SUBSTCHIFFRE_HPP_INCLUDED

/**
 *
 * \file SubstChiffre.hpp
 *
 * \brief Contains namespace CRYPTO. Namespace CRYPTO contains the implementation
 * of simple encription and decription algorithms.
 *
 */

#include <string>
#include <vector>

using namespace std;

/**
 *
 * \namespace CRYPTO
 *
 * \brief Contains the implementation
 * of decription and encription algorithms.
 *
 */
namespace CRYPTO{


/**
 *
 * \var const string DEFAULT_ALPHABET
 *
 *	\brief This contains all possible characters of the default alphabet.
 *
 */
const string DEFAULT_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:'+-=)({}[]?!_";


/**
 *
 * \class ICryptoSys
 *
 *	\brief Interface class for encrypt and decryption systems.
 *
 */
class ICryptoSys{
public:

	/**
	 *
	 * \brief Defines a new alphabet. All char in the string will be
	 * interpreted a one character of the new alphabet. Duplicates of
	 * character will be cause an exception of type string.
	 *
	 * If the string contains one character only, a exception is thrown
	 * (type string).
	 *
	 * \param a string defining the new alphabet
	 *
	 */
    virtual void   initAlphabet(string a) = 0;

    /**
     *
     * \brief Returns the current alphabet of the crypto system.
     *
     * \return string representing the current alphabet.
     *
     */
    virtual string getAlphabet() = 0;

    /**
     *
     * \brief Returns the encrypted text of the given plaintext stored in
     * string m.
     * An exception is thrown if the plaintext contains characters
     * that don't belong the alphabet.
     *
     * \param m string plaintext
     *
     * \return string encrypted text
     *
     */
    virtual string encrypt(string m) = 0;

    /**
     *
     * \brief Returns the decrypted plain text of the given chyphertext
     * An exception is thrown if the plaintext contains characters
     * that don't belong the alphabet.
     *
     * \param c string chyphertext
     * \return string encrypted plaintext
     */
    virtual string decrypt(string c) = 0;

    /**
     *
     * Generates a new key.
     *
     */
    virtual void   generateRandomKey() = 0;

    /**
     *
     * \brief Returns the current key.
     *
     * \return string current key.
     *
     */
    virtual string getKey() = 0;

    /**
     *
     * \brief Returns the name of the encryption/decryption process.
     *
     * \return string name of the encryption/decryption algorithm
     *
     */
    virtual string name() = 0;

    virtual ~ICryptoSys();
};

/**
 *
 * \class CryptoSys
 *
 *	\brief Abstract class for encrypt and decryption systems.
 *
 */
class CryptoSys : public ICryptoSys{
public:
    CryptoSys();
    virtual ~CryptoSys();
    virtual void   initAlphabet(string a);
    virtual string encrypt(string m);
    virtual string decrypt(string c);
    string getAlphabet();
    string name();

protected:
    /**
     *
     * \brief Checks if character c is already stored in
     * array l staring with array index 0 and ending
     * at index  maxIdx (inclusive).
     *
     * \param l char* array of character
     * \param maxIdx int maximal index of the elements to be tested
     * \param c char character to be checked
     *
     * \return bool Return value is true, if character c is already stored in array l, otherwise
     * false.
     *
     */
    bool isDuplicate(char *l, unsigned int maxIdx, char c);

    /**
     *
     * \brief Checks is string msg contains only characters that belong
     * to the current alphabet of the crypto system.
     *
     * \param msg string text
     * \return bool Return value is true is msg contains only characters of the alphabet.
     *
     */
    bool isMsgValid(string msg);

    /**
     *
     * \brief Returns the index of the given character c in the current alphabet.
     *  Method throws an exception, if c can not be found in the currently stored alphabet.
     *
     */
    unsigned int M2C(char c);

    /**
     *
     * \brief Method to implement the final encryption process
     *
     * \param m string plaintext
     * \return string cyphertext
     *
     */
    virtual string myEncryptionProc(string m) = 0;

    /**
     *
     * \brief Method to implement the final decryption process
     *
     * \param c string cyphertext
     * \return string plaintext
     *
     */
    virtual string myDecryptionProc(string c) = 0;

    /**
     *
     * \brief array where the current alphabet is stored
     *
     */
    char *alphabet_;

    /**
     *
     * \brief contains number of the characters of the current alphabet
     *
     */
    unsigned int sizeAlphabet_;

    /**
     *
     * \brief Name of the encryption/decryption algorithm
     *
     */
    string name_;
};


/**
 *
 * \class Vigenere
 *
 *	\brief Implements the Vigenere encryption and decryption algorithm.
 *
 *
 */
class Vigenere : public CryptoSys{
public:
    Vigenere();

    /**
     *
     * \brief parameterize constructor.
     *
     * \param minKeySize unsigned int minimal size of the key
     * \param maxKeySize unsigned int maximal size of the key
     *
     * An exception is thrown if minKeySize value is smaller than 2 or
     * the maxKeySize value is smaller than minKeySize.
     *
     */
    Vigenere(unsigned int minKeySize, unsigned int maxKeySize);

    /**
     *
     * \brief Generates a new key with the given new parameters determing
     * minimal and maximal key size.
     *
     * \param minKeySize unsigned int minimal size of the key
     * \param maxKeySize unsigned int maximal size of the key
     *
     * An exception is thrown if minKeySize value is smaller than 2 or
     * the maxKeySize value is smaller than minKeySize.
     *
     */
    void   generateRandomKey(unsigned int minKeySize, unsigned int maxKeySize);

    /**
     *
     * \brief Generates a new key with the given new parameters determing
     * minimal and maximal key size.
     *
     */
    void   generateRandomKey();


    string getKey();

    /**
     *
     * \brief Defines a new key.
     *
     * \param k string representing the new key.
     *
     * An exception is thrown if string k violates the
     * current minimal and maximal key size values or
     * if it contains characters that don't belong the
     * alphabet.
     *
     */
    void   setKey(string k);

protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);

    /**
     *
     * current key of the Vigenere encryption / decryption process
     *
     */
    string key_;

    /**
     *
     * size of the current key
     *
     */
    unsigned int keySize_;

    /**
     *
     * minimal size accepted for the keys used
     *
     */
    unsigned int minKeySize_;

    /**
     *
     * maximal size accepted for the keys used
     *
     */
    unsigned int maxKeySize_;

};


/**
 *
 * \class Caesar
 *
 *	\brief Implements the Caesar encryption and decryption algorithm.
 *
 *
 */
class Caesar : public CryptoSys{
public:
    Caesar();
    void         generateRandomKey();

    /**
     *
     * \brief Returns the current caesar key.
     *
     * \return unsigned int current key.
     *
     */
    unsigned int getCaesarKey();


    string getKey();


    /**
     *
     * \brief Defines a new key.
     *
     * \param k unisgned int representing the new key.
     *
     * An exception is thrown if string k violates the
     * current minimal and maximal key size values or
     * if it contains characters that don't belong the
     * alphabet.
     *
     */
    void         setKey(unsigned int k);

protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);

    /**
     *
     * current key of the Caesar encryption / decryption
     *
     */
    unsigned int key_;
};


/**
 *
 * \class SubChiffre
 *
 *	\brief Implements the SubChiffre encryption and decryption algorithm.
 *
 *
 */
class SubChiffre : public CryptoSys{
public:
    SubChiffre();
    void    generateRandomKey();
    string  getKey();
protected:
    string myEncryptionProc(string m);
    string myDecryptionProc(string c);


    /**
     *
     * \brief Returns the index of the given character c in the current SubChiffre key.
     *  Method throws an exception, if c can not be found in the currently stored alphabet.
     *
     */
    unsigned int C2M(char c);

    /**
     *
     * current key of the SubChiffre encryption / decryption process
     *
     */
    char *key_;
};


/**
 *
 * \class ICryptoSystemFactory
 *
 *	\brief Interface of a factory that generates crypto systems.
 *
 *
 */
class ICryptoSystemFactory{
public:

	/**
	 *
	 * \brief Returns a object implementing the interface ICryptoSys.
	 * \param ID int Index determining with crypto system to be returned.
	 *
	 * \return *ICryptoSys Reference to a crypto system object.
	 *
	 */
    virtual ICryptoSys *getCryptoSystem(int ID) = 0;

	/**
	 *
	 * \brief Returns a object implementing the interface ICryptoSys.
	 * The object return is randomly selected.
	 *
	 * \return *ICryptoSys Reference to a crypto system object.
	 *
	 */
    virtual ICryptoSys *getCryptoSystem() = 0;

    virtual ~ICryptoSystemFactory();
};

/**
 *
 * \class CryptoSystemFactory
 *
 *	\brief Implements the interface ICryptoSystemFactory generation
 *	crypto systems.
 *
 *
 */
class CryptoSystemFactory : public ICryptoSystemFactory{
public:

	~CryptoSystemFactory();
    ICryptoSys *getCryptoSystem(int ID);
    ICryptoSys *getCryptoSystem();
};


} // end namespace CRYPTO







#endif // SUBSTCHIFFRE_HPP_INCLUDED
