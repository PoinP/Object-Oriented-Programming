#include "SimpleString.h"

#include <cstring>

#pragma warning(disable:4996)

SimpleString::SimpleString(const char* string)
    : length(strlen(string)),
      cString(new char[length + 1])
{
    strcpy(cString, string);
}

SimpleString::SimpleString(const SimpleString& other)
    : SimpleString(other.cString)
{
}

SimpleString::~SimpleString()
{
    delete[] cString;
}

SimpleString& SimpleString::operator=(const SimpleString& other)
{
    if (this == &other)
        return *this;

    SimpleString copy(other);
    swap(copy);
    return *this;
}

size_t SimpleString::getLength() const
{
    return length;
}

const char* SimpleString::getCString() const
{
    return cString;
}

void SimpleString::swap(SimpleString& other)
{
    char* tempCString = cString;
    cString = other.cString;
    other.cString = tempCString;

    unsigned tempLength = length;
    length = other.length;
    other.length = tempLength;
}

std::ostream& operator<<(std::ostream& oStream, const SimpleString& string)
{
    return oStream << string.getCString();
}
