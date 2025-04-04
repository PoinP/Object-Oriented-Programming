#include "BasicString.h"

#include <cstring>

#pragma warning(disable:4996)

BasicString::BasicString(const char* string)
{
    if (!string)
        string = "";

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
        char* newString = new char[strlen(other.cString) + 1];
        strcpy(newString, other.cString);

        delete[] cString;
        cString = newString;
    }

    return *this;
}

unsigned BasicString::getLength() const
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

char& BasicString::at(unsigned index)
{
    return cString[index];
}

char BasicString::at(unsigned index) const
{
    return cString[index];
}
