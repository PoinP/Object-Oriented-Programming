#pragma once

#include "Person.h"

class BlockData
{
public:
	BlockData(int generationId, int blockId, const Person& owner, const char* password);
	~BlockData();

	int getBlockId() const;
	int getGenerationId() const;
	const Person& getBlockOwner() const;
	const char* getBlockPassword() const;

	BlockData(const BlockData&) = delete;
	BlockData& operator=(const BlockData&) = delete;

private:
	int generationId;
	int blockId;
	Person blockOwner;
	char* blockPassword;
};