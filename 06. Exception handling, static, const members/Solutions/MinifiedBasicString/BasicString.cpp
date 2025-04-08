#include "BasicString.h"

#include <cstring>
#include <stdexcept>

#pragma warning(disable:4996)

BasicString::BasicString(const char* string)
{
    if (!string)
        throw std::logic_error("nullptr is not a valid argument!");

    cString = new char[strlen(string) + 1];
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
        // This guarantees strong exception safety
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