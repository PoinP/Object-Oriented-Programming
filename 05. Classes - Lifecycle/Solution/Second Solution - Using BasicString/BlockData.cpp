#include "BlockData.h"

BlockData::BlockData(int generationId, int blockId, const Person& owner, const BasicString& password)
    : generationId(generationId), blockId(blockId), blockOwner(owner), blockPassword(password)
{
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

const BasicString& BlockData::getBlockPassword() const
{
    return blockPassword;
}
