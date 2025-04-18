#include "Block.h"

Block::Block(const Person& owner, const BasicString& password, const Block& block)
    : id(block.id + 1),
      generatedReports(0),
      owner(owner), 
      encryptor(block.encryptor),
      encryptedPassword(encryptor.encrypt(password))
{
    // This way I guarantee that no memory leaks will occur
    // if new throws an exception. We can also declare the
    // 'parent' field last and allocate memory in the
    // member initializer list
    parent = new Block(block);
}

Block::Block(const Person& owner, const BasicString& password, const Encryptor& encryptor)
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
      encryptedPassword(other.encryptedPassword)
{
    if (other.parent)
        parent = new Block(*other.parent);
}

Block::~Block()
{
    delete parent;
}

Block& Block::operator=(const Block& other)
{
    if (this != &other)
    {
        // Here we guarantee only a basic exception safety
        // Can you guess why that is?
        // Hint: Look at the comments in Person.h and Person.cpp

        id = other.id;
        owner = other.owner;
        encryptor = other.encryptor;
        encryptedPassword = other.encryptedPassword;
        generatedReports = other.generatedReports;

        Block* newParent = nullptr;
        if (other.parent)
            newParent = new Block(*other.parent);

        delete parent;
        parent = newParent;
    }

    return *this;
}

uint64_t Block::getId() const
{
    return id;
}

const BasicString& Block::getOwnerFirstName() const
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

BlockData* Block::getReport(const BasicString& password) const
{
    if (!encryptor.encrypt(password).isEqualTo(this->encryptedPassword))
        return nullptr;

    generatedReports += 1;
    return new BlockData(generatedReports, id, owner, password);
}
