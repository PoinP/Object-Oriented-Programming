#pragma once

#include "Person.h"
#include "BasicString.h"

class BlockData
{
public:
	BlockData(uint16_t generationId, uint64_t blockId, const Person& owner, const BasicString& password);

	// This class is quite basic. We want everything to be
	// constant when an object is created so we delete
	// the copy constructor and the copy assignment operator(operator=).
	// And we make all of the fields 'const'.
	// Note: When we have a constant field the copy operator= is always deleted
	// Note 2: The default ctor gets deleted only if we do not have a default value for the const field

	int getBlockId() const;
	int getGenerationId() const;
	const Person& getBlockOwner() const;
	const BasicString& getBlockPassword() const;

	BlockData(const BlockData&) = delete;
	BlockData& operator=(const BlockData&) = delete;

private:
	const uint16_t generationId;
	const uint64_t blockId;
	const Person blockOwner;
	const BasicString blockPassword;
};