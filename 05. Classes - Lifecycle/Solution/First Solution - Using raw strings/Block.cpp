#include "Block.h"

#include <cstring>

#pragma warning(disable:4996)

Block::Block(const Person& owner, const char* password, const Block& block)
    : id(block.id + 1),
      generatedReports(0),
      owner(owner), 
      parent(new Block(block)), 
      encryptor(block.encryptor),
      encryptedPassword(encryptor.encrypt(password))
{
}

Block::Block(const Person& owner, const char* password, const Encryptor& encryptor)
    : id(0),
      generatedReports(0),
      owner(owner),
      parent(nullptr),
      encryptor(encryptor),
      encryptedPassword(encryptor.encrypt(password))
{
}

Block::Block(const Block& other)
    : id(other.id),
      generatedReports(other.generatedReports),
      owner(other.owner),
      parent(nullptr),
      encryptor(other.encryptor),
      // Dangerous: other.encryptedPassword might be nullptr
      encryptedPassword(strcpy(new char[strlen(other.encryptedPassword) + 1], other.encryptedPassword))
{
    if (other.parent)
        parent = new Block(*other.parent);
}

Block::~Block()
{
    delete parent;
    delete[] encryptedPassword;
}

Block& Block::operator=(const Block& other)
{
    if (this != &other)
    {
        id = other.id;
        owner = other.owner;
        encryptor = other.encryptor;
        generatedReports = other.generatedReports;

        Block* newParent = nullptr;
        if (other.parent)
            newParent = new Block(*other.parent);

        delete parent;
        parent = newParent;

        // Dangerous: other.encryptedPassword might be nullptr
        char* newEncryptedPassword = new char[strlen(other.encryptedPassword) + 1];
        strcpy(newEncryptedPassword, other.encryptedPassword);

        delete[] encryptedPassword;
        encryptedPassword = newEncryptedPassword;
    }

    return *this;
}

unsigned Block::getId() const
{
    return id;
}

const char* Block::getOwnerFirstName() const
{
    return owner.getFirstName();
}

const Block* Block::getRoot() const
{
    const Block* root = this;
    while (root->parent != nullptr)
    {
        root = root->parent;
    }

    return root;
}

const Block* Block::getParent() const
{
    return parent;
}

BlockData* Block::getData(const char* password) const
{
    if (!password)
        return nullptr;

    if (strcmp(encryptor.encrypt(password), this->encryptedPassword) != 0)
        return nullptr;

    generatedReports += 1;
    return new BlockData(generatedReports, id, owner, password);
}
