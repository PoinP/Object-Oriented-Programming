#include "BasicString.h"

#include <cstring>
#include <stdexcept>

#pragma warning(disable:4996)

BasicString::BasicString(const char* string)
{
    if (!string)
        throw std::logic_error("nullptr is not a valid argument!");

    length = strlen(string);
    cString = new char[length + 1];
    strcpy(cString, string);
}

BasicString::BasicString(const BasicString& other)
    : BasicString(other.cString)
{
}

BasicString::~BasicString()
{
    delete[] cString;
}

BasicString& BasicString::operator=(const BasicString& other)
{
    if (this != &other)
    {
        // Using strong exception safety rules
        char* newString = new char[other.getLength() + 1];
        strcpy(newString, other.cString);

        delete[] cString;
        cString = newString;
    }

    return *this;
}

uint64_t BasicString::getLength() const
{
    // We can also store it as a field in the class
    return strlen(cString);
}

const char* BasicString::getString() const
{
    return cString;
}

bool BasicString::isEqualTo(const BasicString& other) const
{
    return strcmp(cString, other.cString) == 0;
}

void BasicString::swap(BasicString& other)
{
    char* oldCString = cString;
    cString = other.cString;
    other.cString = oldCString;

    uint64_t oldLength = length;
    length = other.length;
    other.length = oldLength;
}

char& BasicString::at(uint64_t index)
{
    if (index > length)
        throw std::logic_error("Access out of bounds exception");

    return cString[index];
}

char BasicString::at(uint64_t index) const
{
    if (index > length)
        throw std::logic_error("Access out of bounds exception");

    return cString[index];
}
