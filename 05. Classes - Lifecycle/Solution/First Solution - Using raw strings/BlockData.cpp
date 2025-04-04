#include "BlockData.h"

#include <cstring>

#pragma warning(disable:4996)

BlockData::BlockData(int generationId, int blockId, const Person& owner, const char* password)
    : generationId(generationId), blockId(blockId), blockOwner(owner)
{
    if (!password)
        password = "";

    blockPassword = new char[strlen(password) + 1];
    strcpy(blockPassword, password);
}

BlockData::~BlockData()
{
    delete[] blockPassword;
}

int BlockData::getBlockId() const
{
    return blockId;
}

int BlockData::getGenerationId() const
{
    return generationId;
}

const Person& BlockData::getBlockOwner() const
{
    return blockOwner;
}

const char* BlockData::getBlockPassword() const
{
    return blockPassword;
}
