#pragma once

#include "Person.h"
#include "Encryptor.h"
#include "BlockData.h"

class Block
{
public:
	Block(const Person& owner, const char* password, const Block& block);
	Block(const Person& owner, const char* password, const Encryptor& encryptor);
	Block(const Block& other);
	~Block();

	Block& operator=(const Block& other);

	unsigned getId() const;
	const char* getOwnerFirstName() const;

	const Block* getRoot() const;
	const Block* getParent() const;

	BlockData* getData(const char* password) const;

private:
	unsigned id;
	Person owner;
	Block* parent;
	Encryptor encryptor;
	char* encryptedPassword;

	mutable unsigned generatedReports;
};