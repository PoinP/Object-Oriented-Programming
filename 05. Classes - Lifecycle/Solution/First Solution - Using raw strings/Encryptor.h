#pragma once

class Encryptor
{
public:
	Encryptor(const char* key, unsigned offset);

	char* encrypt(const char* toEncrypt) const;
	char* decrypt(const char* toDecrypt) const;

private:
	unsigned offset;
	char key[128];
	unsigned keyLength;
};