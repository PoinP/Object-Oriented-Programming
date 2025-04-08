#pragma once

#include "BasicString.h"

class Encryptor
{
public:
	Encryptor(const char* key, unsigned offset);

	// For this class we do not need the rule of four.
	// It also guarantees a strong exception safety.

	BasicString encrypt(const BasicString& toEncrypt) const;
	BasicString decrypt(const BasicString& toDecrypt) const;

private:
	char key[128];
	unsigned offset;
	unsigned keyLength;
};