#pragma once

#include "Person.h"
#include "BasicString.h"

class BlockData
{
public:
	BlockData(int generationId, int blockId, const Person& owner, const BasicString& password);

	int getBlockId() const;
	int getGenerationId() const;
	const Person& getBlockOwner() const;
	const BasicString& getBlockPassword() const;

	BlockData(const BlockData&) = delete;
	BlockData& operator=(const BlockData&) = delete;

private:
	int generationId;
	int blockId;
	Person blockOwner;
	BasicString blockPassword;
};