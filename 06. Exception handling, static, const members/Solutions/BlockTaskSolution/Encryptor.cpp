#include "Encryptor.h"

#include <cstring>

Encryptor::Encryptor(const char* key, unsigned offset)
    : offset(offset), keyLength(0)
{
    if (!key)
        key = "DefaultKey";
    // A better way is to throw an exception

    keyLength = strlen(key);
    if (keyLength > 128)
        keyLength = 128;

    for (unsigned i = 0; i < keyLength; i++)
    {
        this->key[i] = key[i];
    }
}

BasicString Encryptor::encrypt(const BasicString& toEncrypt) const
{
    BasicString encryptedStr = toEncrypt;
    
    unsigned toEncryptLen = toEncrypt.getLength();
    for (unsigned i = 0; i < toEncryptLen; i++)
    {
        unsigned keyIndex = i % keyLength;
        encryptedStr.at(i) = (toEncrypt.at(i) ^ key[keyIndex]) + offset % 3 + 1;
    }
    
    return encryptedStr;
}

BasicString Encryptor::decrypt(const BasicString& toDecrypt) const
{
    BasicString decryptedStr = toDecrypt;

    unsigned toDecryptLen = toDecrypt.getLength();
    for (unsigned i = 0; i < toDecryptLen; i++)
    {
        unsigned keyIndex = i % keyLength;
        decryptedStr.at(i) = (toDecrypt.at(i) - (offset % 3 + 1)) ^ key[keyIndex];
    }

    return decryptedStr;
}
