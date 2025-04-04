#pragma once

#include "BasicString.h"

class Encryptor
{
public:
	Encryptor(const char* key, unsigned offset);

	BasicString encrypt(const BasicString& toEncrypt) const;
	BasicString decrypt(const BasicString& toDecrypt) const;

private:
	unsigned offset;
	char key[128];
	unsigned keyLength;
};