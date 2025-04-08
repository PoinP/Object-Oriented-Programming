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

	// Here the rule of four must be exercised because
	// an object of this class owns dynamic memory
	// that must be copied explicitly in some way

	uint64_t getId() const;
	const BasicString& getOwnerFirstName() const;

	const Block* getRoot() const;
	const Block* getParent() const;

	BlockData* getReport(const BasicString& password) const;

private:
	uint64_t id;
	Person owner;
	Block* parent;
	Encryptor encryptor;
	BasicString encryptedPassword;

	// Quick note: It would be better for the Encryptor to be a pointer
	// that is managed by the root block (the one with id of 0).
	// For simplicity's sake, we are going to copy it for each block
	
	// The reason for this to be mutable is because it is used only
	// as a sort of a meta data that does not represent the state of
	// the object. This is one of those rare situations where 'mutable'
	// can be used and it is logical to be used.
	mutable uint16_t generatedReports;
};