#include "Encryptor.h"

#include <cstring>

Encryptor::Encryptor(const char* key, unsigned offset)
    : offset(offset), keyLength(0)
{
    if (!key)
        key = "Default key";
    // A better way is to throw an exception

    keyLength = strlen(key);
    if (keyLength > 128)
        keyLength = 128;

    for (unsigned i = 0; i < keyLength; i++)
    {
        this->key[i] = key[i];
    }
}

char* Encryptor::encrypt(const char* toEncrypt) const
{
    if (!toEncrypt)
        return nullptr;

    unsigned toEncryptLen = strlen(toEncrypt);
    char* encryptedStr = new char[toEncryptLen + 1];
    
    for (unsigned i = 0; i < toEncryptLen; i++)
    {
        unsigned keyIndex = i % keyLength;
        encryptedStr[i] = (toEncrypt[i] ^ key[keyIndex]) + offset % 3 + 1;
    }
    
    encryptedStr[toEncryptLen] = '\0';

    return encryptedStr;
}

char* Encryptor::decrypt(const char* toDecrypt) const
{
    if (!toDecrypt)
        return nullptr;

    unsigned toDecryptLen = strlen(toDecrypt);
    char* decryptedStr = new char[toDecryptLen + 1];

    for (unsigned i = 0; i < toDecryptLen; i++)
    {
        unsigned keyIndex = i % keyLength;
        decryptedStr[i] = (toDecrypt[i] - (offset % 3 + 1)) ^ key[keyIndex];
    }

    decryptedStr[toDecryptLen] = '\0';

    return decryptedStr;
}
