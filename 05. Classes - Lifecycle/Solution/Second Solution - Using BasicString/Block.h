#pragma once

#include "Person.h"
#include "Encryptor.h"
#include "BlockData.h"
#include "BasicString.h"

class Block
{
public:
	Block(const Person& owner, const BasicString& password, const Block& block);
	Block(const Person& owner, const BasicString& password, const Encryptor& encryptor);
	Block(const Block& other);
	~Block();

	Block& operator=(const Block& other);

	unsigned getId() const;
	const BasicString& getOwnerFirstName() const;

	const Block* getRoot() const;
	const Block* getParent() const;

	BlockData* getReport(const BasicString& password) const;

private:
	unsigned id;
	Person owner;
	Block* parent;
	Encryptor encryptor;
	BasicString encryptedPassword;

	// Quick note: It would be better for the Encryptor to be a pointer
	// that is managed by the root block (the one with id of 0).
	// For simplicity's sake, we are going to copy it for each block

	mutable unsigned generatedReports;
};